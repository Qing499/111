#ifndef QUESTION_H
#define QUESTION_H

#include "Triangle.h"

#include <string>
#include <iostream>

class Question
{
public:
    Question();
    Question(int number, const Triangle& triangle);
    Question(int number, const Triangle& triangle,
             double answer, double score);
    Question(const Question& other);
    ~Question();

    Question& operator=(const Question& other);

    bool setTriangle(const Triangle& triangle);
    void setNumber(int number);
    void setUserAnswer(double answer);
    void setScore(double score);
    void setAnswered(bool flag);

    int    getNumber() const { return number; }
    double getUserAnswer() const { return userAnswer; }
    double getScore() const { return score; }
    bool   isAnswered() const { return answered; }

    double computeCorrectAnswer(const Triangle& triangle, int target) const;
    bool   checkAnswer(const Triangle& triangle, int target) const;

    double correctAnswer(int target) const;
    double judge();
    bool   isValid() const;
    void   show() const;
    void   showDetail() const;

    std::string describe() const;

    friend std::ostream& operator<<(std::ostream& out, const Question& question);

private:
    int      number;
    Triangle triangle;
    double   correct;
    double   userAnswer;
    double   score;
    bool     answered;
};

#endif
