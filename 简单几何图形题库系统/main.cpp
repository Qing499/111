#include "QuizBank.h"
#include "Question.h"
#include "Triangle.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <stdexcept>

#ifdef _WIN32
#define NOMINMAX

#include <windows.h>
#endif

using namespace std;

void prepareConsole()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

double readDouble(const string& prompt)
{
    double value = 0.0;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            return value;
        }
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << "输入不合法，请输入一个数字。" << endl;
    }
}

int readInt(const string& prompt)
{
    int value = 0;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            return value;
        }
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << "输入不合法，请输入一个整数。" << endl;
    }
}

void printLine()
{
    cout << "==============================================================" << endl;
}

void addPresetQuestions(QuizBank& bank)
{
    int added = 0;

    if (bank.addQuestion(Triangle(3.0, 4.0, 5.0), "直角三角形"))
    {
        added++;
        cout << "已添加：直角三角形（3，4，5）" << endl;
    }
    if (bank.addQuestion(Triangle(6.0, 8.0, 10.0), "直角三角形"))
    {
        added++;
        cout << "已添加：直角三角形（6，8，10）" << endl;
    }
    if (bank.addQuestion(Triangle(5.0, 5.0, 6.0), "等腰三角形"))
    {
        added++;
        cout << "已添加：等腰三角形（5，5，6）" << endl;
    }
    if (bank.addQuestion(Triangle(7.0, 7.0, 7.0), "等边三角形"))
    {
        added++;
        cout << "已添加：等边三角形（7，7，7）" << endl;
    }
    if (bank.addQuestion(Triangle(9.0, 10.0, 11.0), "一般三角形"))
    {
        added++;
        cout << "已添加：一般三角形（9，10，11）" << endl;
    }

    cout << "本次共成功添加 " << added << " 道题，题库里现有 "
         << bank.getCount() << " 道题。" << endl;
}

void addCustomQuestion(QuizBank& bank)
{
    double a = readDouble("请输入三角形的边 a：");
    double b = readDouble("请输入三角形的边 b：");
    double c = readDouble("请输入三角形的边 c：");

    Triangle triangle(a, b, c);
    if (!triangle.isValid())
    {
        cout << "这三条边构不成三角形，出题失败。" << endl;
        return;
    }

    Question question(bank.getMaxNumber() + 1, triangle);
    question.checkAnswer(triangle, 1);
    if (bank.addQuestion(question))
    {
        cout << "出题成功！" << endl;
        question.show();
    }
    else
    {
        cout << "出题失败：题号重复或者题库已经满了。" << endl;
    }
}

void demoConstructionOrder()
{
    printLine();
    cout << "【演示】组合关系中整体类构造函数的调用过程" << endl;
    printLine();
    cout << "构造一个 QuizBank 对象时，内部 50 个 Question 成员会被依次构造；" << endl;
    cout << "每个 Question 里的 Triangle 成员又会被构造；Triangle 里的 3 个 Point 也会被构造。" << endl;
    cout << "调用顺序是：由内到外（先构造成员，再执行自己的构造函数体）。" << endl;
    cout << "析构顺序正好相反：由外到内（先执行自己的析构函数体，再析构成员）。" << endl;
    cout << endl;

    cout << "构造前，活着的 Triangle 对象个数 = " << Triangle::aliveCount() << endl;
    {
        cout << ">>> 进入大括号，开始构造 QuizBank 对象：" << endl;
        QuizBank demoBank("演示题库", 3);
        cout << "    QuizBank 构造完成，活着的 Triangle 对象个数 = "
             << Triangle::aliveCount()
             << "（QuizBank 的成员数组里有 " << QuizBank::MAX_QUESTION
             << " 个 Question 对象，每个 Question 里各有一个 Triangle 对象）" << endl;
        cout << "    注意：Question 对象在对象数组定义时就已经全部构造完成，" << endl;
        cout << "          而且每个 Question 里的 Triangle 又是通过拷贝构造得到的。" << endl;
    }
    cout << "<<< 离开大括号后，活着的 Triangle 对象个数 = "
         << Triangle::aliveCount() << "（全部被析构）" << endl;

    cout << endl;
    cout << "再演示一次：先构造一个三角形，再把它组合进题目对象里。" << endl;
    {
        cout << ">>> 定义 Triangle t1(3.0, 4.0, 5.0)" << endl;
        Triangle t1(3.0, 4.0, 5.0);
        cout << "    活着 = " << Triangle::aliveCount() << endl;

        cout << ">>> 定义 Question q1(1, t1)" << endl;
        Question q1(1, t1);
        cout << "    t1 被拷贝构造了一次，活着 = " << Triangle::aliveCount() << endl;

        cout << ">>> 定义 QuizBank demoBank2(\"演示题库2\", 2)" << endl;
        QuizBank demoBank2("演示题库2", 2);
        cout << "    活着 = " << Triangle::aliveCount() << endl;
        demoBank2.addQuestion(q1);
        cout << "    把 q1 加到题库里（调用赋值运算符），活着 = "
             << Triangle::aliveCount() << endl;
        cout << "<<< 即将离开大括号：析构顺序与构造顺序相反。" << endl;
    }
    cout << "全部析构完成，活着的 Triangle 对象个数 = "
         << Triangle::aliveCount() << endl;
    printLine();
}

int main()
{
    prepareConsole();
    cout << fixed << setprecision(4);

    printLine();
    cout << "      实验二  组合关系、依赖关系（设计报告 1）" << endl;
    cout << "  题目 1：题库类组合三角形题目类（简单几何图形题库系统）" << endl;
    printLine();

    QuizBank bank("简单几何图形题库", 20);
    cout << "已创建题库：" << bank << endl;
    cout << "提示：题库里每一个题目对象内部都有一个三角形对象（组合关系）。" << endl;

    cout << endl << "是否立即载入 5 道示例题目？（1 = 是，0 = 否）：";
    int load = readInt("");
    if (load == 1)
    {
        addPresetQuestions(bank);
    }

    int choice = 0;
    do
    {
        printLine();
        cout << "请选择要进行的操作：" << endl;
        cout << "  1. 查看题库情况" << endl;
        cout << "  2. 载入 5 道示例题目" << endl;
        cout << "  3. 自定义出题（输入三条边）" << endl;
        cout << "  4. 查看全部题目（含答案）" << endl;
        cout << "  5. 开始练习（练习一道题就反馈）" << endl;
        cout << "  6. 开始练习（练习完所有题再反馈）" << endl;
        cout << "  7. 查看错题" << endl;
        cout << "  8. 按题号查询题目" << endl;
        cout << "  9. 删除题目" << endl;
        cout << " 10. 清空答题记录" << endl;
        cout << " 11. 演示组合关系中整体类构造函数的调用过程" << endl;
        cout << "  0. 退出程序" << endl;
        choice = readInt("请输入选项编号：");

        switch (choice)
        {
        case 1:
        {
            bank.show();
            break;
        }
        case 2:
        {
            addPresetQuestions(bank);
            cout << "当前题库：" << bank << endl;
            break;
        }
        case 3:
        {
            addCustomQuestion(bank);
            break;
        }
        case 4:
        {
            bank.showAllQuestions();
            break;
        }
        case 5:
        {
            bank.startPractice(true);
            bank.show();
            break;
        }
        case 6:
        {
            bank.startPractice(false);
            bank.show();
            break;
        }
        case 7:
        {
            bank.showWrongQuestions();
            break;
        }
        case 8:
        {
            int number = readInt("请输入要查询的题号：");
            bank.queryQuestion(number);
            break;
        }
        case 9:
        {
            int number = readInt("请输入要删除的题号：");
            if (bank.removeQuestionByNumber(number))
            {
                cout << "删除成功。当前题库：" << bank << endl;
            }
            else
            {
                cout << "删除失败：没有找到这个题号。" << endl;
            }
            break;
        }
        case 10:
        {
            bank.resetRecord();
            break;
        }
        case 11:
        {
            demoConstructionOrder();
            break;
        }
        case 0:
        {
            cout << "程序结束，再见！" << endl;
            break;
        }
        default:
        {
            cout << "没有这个选项，请重新输入。" << endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
