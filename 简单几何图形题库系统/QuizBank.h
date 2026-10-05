#ifndef QUIZBANK_H
#define QUIZBANK_H

#include "Question.h"
#include "Triangle.h"

#include <string>
#include <iostream>

class QuizBank
{
public:
    static const int MAX_QUESTION = 50;

    QuizBank();
    QuizBank(const std::string& bankName);
    QuizBank(const std::string& bankName, int capacity);
    QuizBank(const QuizBank& other);
    ~QuizBank();
    QuizBank& operator=(const QuizBank& other);

    void setName(const std::string& bankName);

    bool addQuestion(const Question& question);
    bool addQuestion(const Triangle& triangle, const std::string& type);
    bool removeQuestion(int index);
    bool removeQuestionByNumber(int number);
    void clear();

    std::string getName() const { return name; }
    int  getCapacity() const { return capacity; }
    int  getCount() const { return count; }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }

    Question& getQuestion(int index);
    const Question& getQuestion(int index) const;
    int  findQuestion(int number) const;
    int  getMaxNumber() const;

    double getTotalScore() const;
    double getAverageScore() const;
    int    getAnsweredCount() const;
    double getFullScore() const;

    void show() const;
    void showAllQuestions() const;
    void showWrongQuestions() const;

    void startPractice(bool immediateFeedback);

    void queryQuestion(int number) const;
    void resetRecord();

    friend std::ostream& operator<<(std::ostream& out, const QuizBank& bank);

private:
    std::string name;
    Question    questions[MAX_QUESTION];
    int         count;
    int         capacity;

    int         answeredCount;
    double      totalScore;
    int         practiceTimes;

    void copyFrom(const QuizBank& other);
    void refreshAnsweredCount();
};

#endif
