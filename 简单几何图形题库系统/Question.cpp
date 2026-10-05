#include "Question.h"

#include <cmath>
#include <sstream>

using namespace std;

namespace
{
    const double FULL_SCORE = 10.0;
    const double ANSWER_EPS = 1e-6;
}

Question::Question()
    : number(0), triangle(), correct(0.0), userAnswer(0.0), score(0.0), answered(false)
{
}

Question::Question(int numberValue, const Triangle& t)
    : number(numberValue), triangle(t), correct(0.0), userAnswer(0.0), score(0.0), answered(false)
{
}

Question::Question(int numberValue, const Triangle& t, double answer, double scoreValue)
    : number(numberValue), triangle(t), correct(0.0),
      userAnswer(answer), score(scoreValue), answered(true)
{
}

Question::Question(const Question& other)
    : number(other.number), triangle(other.triangle), correct(other.correct),
      userAnswer(other.userAnswer), score(other.score), answered(other.answered)
{
}

Question::~Question()
{
}

Question& Question::operator=(const Question& other)
{
    if (this != &other)
    {
        number = other.number;
        triangle = other.triangle;
        correct = other.correct;
        userAnswer = other.userAnswer;
        score = other.score;
        answered = other.answered;
    }
    return *this;
}

bool Question::setTriangle(const Triangle& t)
{
    if (!t.isValid())
    {
        return false;
    }
    triangle = t;
    return true;
}

void Question::setNumber(int numberValue)
{
    number = numberValue;
}

void Question::setUserAnswer(double answer)
{
    userAnswer = answer;
    answered = true;
}

void Question::setScore(double scoreValue)
{
    score = scoreValue;
}

void Question::setAnswered(bool flag)
{
    answered = flag;
}

double Question::computeCorrectAnswer(const Triangle& t, int target) const
{
    if (!t.isValid())
    {
        return 0.0;
    }
    if (target == 1)
    {
        return t.perimeter();
    }
    if (target == 2)
    {
        return t.area();
    }
    return 0.0;
}

bool Question::checkAnswer(const Triangle& t, int target) const
{
    double right = computeCorrectAnswer(t, target);
    return fabs(userAnswer - right) < ANSWER_EPS;
}

double Question::correctAnswer(int target) const
{
    return computeCorrectAnswer(triangle, target);
}

double Question::judge()
{
    correct = correctAnswer(1);
    if (answered && fabs(userAnswer - correct) < ANSWER_EPS)
    {
        score = FULL_SCORE;
    }
    else
    {
        score = 0.0;
    }
    return score;
}

bool Question::isValid() const
{
    return number > 0 && triangle.isValid();
}

string Question::describe() const
{
    ostringstream buffer;
    buffer << "第 " << number << " 题：求下面三角形的周长与面积 -> " << triangle.toString();
    return buffer.str();
}

void Question::show() const
{
    cout << describe() << endl;
}

void Question::showDetail() const
{
    cout << describe() << endl;
    cout << "        正确答案：周长 = " << triangle.perimeter()
         << "，面积 = " << triangle.area() << endl;
    if (answered)
    {
        cout << "        你的答案：周长 = " << userAnswer
             << "，本题得分 = " << score << " 分" << endl;
    }
    else
    {
        cout << "        你还没有做过这道题。" << endl;
    }
}

ostream& operator<<(ostream& out, const Question& question)
{
    out << question.describe();
    return out;
}
