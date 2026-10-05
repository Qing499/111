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
    cout << "--------------------------------------------------------------" << endl;
}

void demoConstructors()
{
    printLine();
    cout << "【演示】重载的构造函数与对象的产生 / 消亡" << endl;
    printLine();
    cout << "进入函数时，当前活着的 Triangle 对象个数 = "
         << Triangle::aliveCount() << endl;

    {
        cout << endl << ">>> 进入第 1 层大括号：" << endl;
        Triangle t1;
        cout << "  Triangle t1;              默认构造 -> ";
        t1.show();
        cout << "  此时活着的对象个数 = " << Triangle::aliveCount() << endl;

        Triangle t2(6.0, 8.0, 10.0);
        cout << endl << "  Triangle t2(6.0, 8.0, 10.0); 带参构造 -> ";
        t2.show();
        cout << "  此时活着的对象个数 = " << Triangle::aliveCount() << endl;

        {
            cout << endl << "  >>> 进入第 2 层大括号：" << endl;
            Triangle::Point p1(0.0, 0.0);
            Triangle::Point p2(4.0, 0.0);
            Triangle::Point p3(0.0, 3.0);
            Triangle t3(p1, p2, p3);
            cout << "  Triangle t3(p1, p2, p3); 由顶点构造 -> ";
            t3.show();
            cout << "  此时活着的对象个数 = " << Triangle::aliveCount() << endl;

            Triangle t4(t3);
            cout << endl << "  Triangle t4(t3);        拷贝构造 -> ";
            t4.show();
            cout << "  此时活着的对象个数 = " << Triangle::aliveCount() << endl;
            cout << "  <<< 即将离开第 2 层大括号，t3、t4 与三个 Point 被析构" << endl;
        }

        cout << "  回到第 1 层，活着的对象个数 = " << Triangle::aliveCount() << endl;
        cout << "  <<< 即将离开第 1 层大括号，t1、t2 被析构" << endl;
    }

    cout << "回到 demoConstructors 函数末尾，活着的对象个数 = "
         << Triangle::aliveCount() << endl;
    printLine();
}

int main()
{
    prepareConsole();
    cout << fixed << setprecision(4);

    printLine();
    cout << "        实验一  类与对象" << endl;
    cout << "  题目 1：三角形题目类（简单几何图形题库系统）" << endl;
    printLine();

    Triangle triangle;
    cout << "已用【默认构造函数】创建一个三角形对象，初始状态：" << endl;
    triangle.show();

    Triangle custom(5.0, 5.0, 6.0);
    cout << endl << "已用【带参构造函数】创建另一个三角形对象，初始状态：" << endl;
    custom.show();

    Triangle copyOfCustom(custom);
    cout << endl << "已用【拷贝构造函数】复制上面这个对象，副本状态：" << endl;
    copyOfCustom.show();

    int choice = 0;
    do
    {
        printLine();
        cout << "请选择要进行的操作：" << endl;
        cout << "  1. 初始化 / 修改三条边长" << endl;
        cout << "  2. 获取（查看）三条边长" << endl;
        cout << "  3. 输出三角形的全部信息" << endl;
        cout << "  4. 求周长与面积" << endl;
        cout << "  5. 判断三角形的类型" << endl;
        cout << "  6. 比较两个三角形的面积大小" << endl;
        cout << "  7. 演示构造函数重载与对象生命周期" << endl;
        cout << "  0. 退出程序" << endl;
        choice = readInt("请输入选项编号：");

        switch (choice)
        {
        case 1:
        {
            double a = readDouble("请输入边 a：");
            double b = readDouble("请输入边 b：");
            double c = readDouble("请输入边 c：");
            if (triangle.setSides(a, b, c))
            {
                cout << "修改成功（已通过是否能构成三角形的检查）。" << endl;
                triangle.show();
            }
            else
            {
                cout << "修改失败：三条边 " << a << "、" << b << "、" << c
                     << " 不能构成三角形，仍保持原来的值。" << endl;
                triangle.show();
            }
            break;
        }
        case 2:
        {
            cout << "当前对象的三条边为：a = " << triangle.getSideA()
                 << "，b = " << triangle.getSideB()
                 << "，c = " << triangle.getSideC() << endl;
            break;
        }
        case 3:
        {
            triangle.show();
            break;
        }
        case 4:
        {
            cout << "周长 = " << triangle.perimeter() << endl;
            cout << "面积 = " << triangle.area() << "（海伦公式计算）" << endl;
            break;
        }
        case 5:
        {
            cout << "是否直角三角形：" << (triangle.isRight() ? "是" : "否") << endl;
            cout << "是否等腰三角形：" << (triangle.isIsosceles() ? "是" : "否") << endl;
            cout << "是否等边三角形：" << (triangle.isEquilateral() ? "是" : "否") << endl;
            cout << "类型判定结果：" << triangle.typeName() << endl;
            break;
        }
        case 6:
        {
            cout << "对象 1：" << triangle.toString() << endl;
            cout << "对象 2：" << custom.toString() << endl;
            if (triangle.area() > custom.area())
            {
                cout << "对象 1 的面积更大。" << endl;
            }
            else if (triangle.area() < custom.area())
            {
                cout << "对象 2 的面积更大。" << endl;
            }
            else
            {
                cout << "两个三角形的面积相等。" << endl;
            }
            break;
        }
        case 7:
        {
            demoConstructors();
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

    cout << "main 结束前，活着的 Triangle 对象个数 = "
         << Triangle::aliveCount() << "（通常是 main 里定义的那几个）" << endl;
    return 0;
}
