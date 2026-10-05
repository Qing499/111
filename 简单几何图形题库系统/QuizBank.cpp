#include "QuizBank.h"

#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

const int QuizBank::MAX_QUESTION;

QuizBank::QuizBank()
    : name("未命名题库"), count(0), capacity(MAX_QUESTION),
      answeredCount(0), totalScore(0.0), practiceTimes(0)
{
}

QuizBank::QuizBank(const string& bankName)
    : name(bankName), count(0), capacity(MAX_QUESTION),
      answeredCount(0), totalScore(0.0), practiceTimes(0)
{
}

QuizBank::QuizBank(const string& bankName, int capacityValue)
    : name(bankName), count(0),
      capacity(capacityValue > 0 && capacityValue <= MAX_QUESTION ? capacityValue : MAX_QUESTION),
      answeredCount(0), totalScore(0.0), practiceTimes(0)
{
}

QuizBank::QuizBank(const QuizBank& other)
    : name(other.name), count(other.count), capacity(other.capacity),
      answeredCount(other.answeredCount), totalScore(other.totalScore),
      practiceTimes(other.practiceTimes)
{
    for (int i = 0; i < capacity; ++i)
    {
        questions[i] = other.questions[i];
    }
}

QuizBank::~QuizBank()
{
}

QuizBank& QuizBank::operator=(const QuizBank& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

void QuizBank::copyFrom(const QuizBank& other)
{
    name = other.name;
    count = other.count;
    capacity = other.capacity;
    answeredCount = other.answeredCount;
    totalScore = other.totalScore;
    practiceTimes = other.practiceTimes;
    for (int i = 0; i < capacity; ++i)
    {
        questions[i] = other.questions[i];
    }
}

void QuizBank::setName(const string& bankName)
{
    if (!bankName.empty())
    {
        name = bankName;
    }
}

bool QuizBank::addQuestion(const Question& question)
{
    if (!question.isValid())
    {
        return false;
    }
    if (isFull())
    {
        return false;
    }
    if (findQuestion(question.getNumber()) != -1)
    {
        return false;
    }

    questions[count] = question;
    count++;
    refreshAnsweredCount();
    return true;
}

bool QuizBank::addQuestion(const Triangle& triangle, const string& type)
{
    if (!triangle.isValid())
    {
        return false;
    }
    if (isFull())
    {
        return false;
    }

    int number = getMaxNumber() + 1;
    Question question(number, triangle);
    (void)type;
    questions[count] = question;
    count++;
    refreshAnsweredCount();
    return true;
}

bool QuizBank::removeQuestion(int index)
{
    if (index < 0 || index >= count)
    {
        return false;
    }
    for (int i = index; i < count - 1; ++i)
    {
        questions[i] = questions[i + 1];
    }
    questions[count - 1] = Question();
    count--;
    refreshAnsweredCount();
    return true;
}

bool QuizBank::removeQuestionByNumber(int number)
{
    int index = findQuestion(number);
    if (index == -1)
    {
        return false;
    }
    return removeQuestion(index);
}

void QuizBank::clear()
{
    for (int i = 0; i < count; ++i)
    {
        questions[i] = Question();
    }
    count = 0;
    answeredCount = 0;
    totalScore = 0.0;
}

void QuizBank::refreshAnsweredCount()
{
    answeredCount = 0;
    for (int i = 0; i < count; ++i)
    {
        if (questions[i].isAnswered())
        {
            answeredCount++;
        }
    }
}

Question& QuizBank::getQuestion(int index)
{
    if (index < 0 || index >= count)
    {
        throw out_of_range("题目下标超出范围！");
    }
    return questions[index];
}

const Question& QuizBank::getQuestion(int index) const
{
    if (index < 0 || index >= count)
    {
        throw out_of_range("题目下标超出范围！");
    }
    return questions[index];
}

int QuizBank::findQuestion(int number) const
{
    for (int i = 0; i < count; ++i)
    {
        if (questions[i].getNumber() == number)
        {
            return i;
        }
    }
    return -1;
}

int QuizBank::getMaxNumber() const
{
    int maxNumber = 0;
    for (int i = 0; i < count; ++i)
    {
        if (questions[i].getNumber() > maxNumber)
        {
            maxNumber = questions[i].getNumber();
        }
    }
    return maxNumber;
}

double QuizBank::getTotalScore() const
{
    return totalScore;
}

double QuizBank::getAverageScore() const
{
    if (practiceTimes == 0)
    {
        return 0.0;
    }
    return totalScore / practiceTimes;
}

int QuizBank::getAnsweredCount() const
{
    return answeredCount;
}

double QuizBank::getFullScore() const
{
    return count * 10.0;
}

void QuizBank::show() const
{
    cout << "题库名称：" << name << endl;
    cout << "题目数量：" << count << " / " << capacity << endl;
    cout << "已做题目：" << answeredCount << " 道" << endl;
    cout << "练习次数：" << practiceTimes << " 次" << endl;
    cout << "累计得分：" << totalScore << " 分"
         << "，平均分：" << getAverageScore() << " 分" << endl;
    if (count > 0)
    {
        cout << "全部做对可以得：" << getFullScore() << " 分" << endl;
    }
}

void QuizBank::showAllQuestions() const
{
    if (isEmpty())
    {
        cout << "题库里还没有题目。" << endl;
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        questions[i].showDetail();
    }
}

void QuizBank::showWrongQuestions() const
{
    int wrongCount = 0;
    for (int i = 0; i < count; ++i)
    {
        if (questions[i].isAnswered() && questions[i].getScore() <= 0.0)
        {
            wrongCount++;
            questions[i].showDetail();
        }
    }
    if (wrongCount == 0)
    {
        cout << "太棒了，目前没有错题（或者还没有做过题）。" << endl;
    }
    else
    {
        cout << "共 " << wrongCount << " 道错题。" << endl;
    }
}

void QuizBank::startPractice(bool immediateFeedback)
{
    if (isEmpty())
    {
        cout << "题库里还没有题目，请先添加题目。" << endl;
        return;
    }

    practiceTimes++;
    cout << "本次共 " << count << " 道题，每题 10 分，满分 " << getFullScore() << " 分。" << endl;

    double sessionScore = 0.0;

    for (int i = 0; i < count; ++i)
    {
        cout << endl;
        cout << "------------------------------------------" << endl;
        questions[i].show();

        double answer = 0.0;
        cout << "请输入这个三角形的周长：";
        while (!(cin >> answer))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入不合法，请重新输入周长：";
        }

        questions[i].setUserAnswer(answer);
        questions[i].setAnswered(true);

        double score = questions[i].judge();
        sessionScore += score;

        if (immediateFeedback)
        {
            if (score > 0.0)
            {
                cout << "回答正确！本题得 " << score << " 分。" << endl;
            }
            else
            {
                cout << "回答错误。正确答案是 " << questions[i].correctAnswer(1)
                     << "，本题得 0 分。" << endl;
            }
        }
    }

    if (!immediateFeedback)
    {
        cout << endl;
        cout << "==================== 本次练习成绩 ====================" << endl;
        cout << "总得分：" << sessionScore << " / " << getFullScore() << " 分" << endl;
        cout << "本次平均分：" << (sessionScore / count) << " 分" << endl;
        for (int i = 0; i < count; ++i)
        {
            cout << "第 " << questions[i].getNumber() << " 题：";
            if (questions[i].getScore() > 0.0)
            {
                cout << "正确（你的答案 " << questions[i].getUserAnswer() << "）" << endl;
            }
            else
            {
                cout << "错误（你的答案 " << questions[i].getUserAnswer()
                     << "，正确答案 " << questions[i].correctAnswer(1) << "）" << endl;
            }
        }
        cout << "======================================================" << endl;
    }

    totalScore += sessionScore;
    refreshAnsweredCount();
}

void QuizBank::queryQuestion(int number) const
{
    int index = findQuestion(number);
    if (index == -1)
    {
        cout << "题库里没有第 " << number << " 题。" << endl;
        return;
    }
    cout << "查询结果如下：" << endl;
    questions[index].showDetail();
}

void QuizBank::resetRecord()
{
    for (int i = 0; i < count; ++i)
    {
        questions[i].setUserAnswer(0.0);
        questions[i].setScore(0.0);
        questions[i].setAnswered(false);
    }
    answeredCount = 0;
    totalScore = 0.0;
    practiceTimes = 0;
    cout << "答题记录已经全部清除。" << endl;
}

ostream& operator<<(ostream& out, const QuizBank& bank)
{
    out << "【题库】" << bank.name
        << "，共 " << bank.count << " 道题"
        << "，已做 " << bank.answeredCount << " 道"
        << "，累计得分 " << bank.totalScore << " 分";
    return out;
}
