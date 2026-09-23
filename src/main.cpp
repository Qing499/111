#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "ConsoleIO.h"
#include "ConsoleSetup.h"
#include "Triangle.h"

using namespace sgs;

namespace {

std::string fixed2(double value) {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(2);
    oss << value;
    return oss.str();
}

int liveInsideByValue(Triangle copy) {
    (void)copy;
    return Triangle::liveCount();
}

int liveInsideByRef(const Triangle& ref) {
    (void)ref;
    return Triangle::liveCount();
}

void printBanner(std::ostream& out) {
    out << "####################################################\n";
    out << "#        简 单 几 何 图 形 题 目 系 统             #\n";
    out << "#        阶段一：类与对象（实验一 阶段性代码）     #\n";
    out << "####################################################\n";
    out << "本阶段范围：只完成“题目1：三角形题目类”的单个类设计，\n";
    out << "           不做继承、图形界面与完整题库（后续阶段递增实现）。\n";
}

void printMenu(std::ostream& out) {
    out << "\n=============== 阶段一 · 主 菜 单 ===============\n";
    out << "  1. 类与对象要点演示（构造/验证/修改/获取/输出/生命周期）\n";
    out << "  2. 交互式验收：输入三边，构造三角形对象并查看结果\n";
    out << "  3. 运行内置自检（自动检查类设计是否符合实验要求）\n";
    out << "  0. 退出\n";
    out << "=================================================\n";
}

void demoClassAndObject(std::istream& in, std::ostream& out) {
    out << "\n=========== 类与对象要点演示（对应实验验收点）===========\n";

    out << "\n【演示1】默认构造函数：把数据成员初始化为一定的值（实验要求 4-(3)）\n";
    Triangle t0;
    out << "    Triangle t0;                -> " << t0 << "\n";
    out << "    当前存活对象数 liveCount() = " << Triangle::liveCount() << "\n";

    out << "\n【演示2】重载构造函数：用相应参数构造需要的对象（实验要求 4-(4)）\n";
    Triangle t1(5.0);
    Triangle t2(6.0, 8.0, 10.0);
    out << "    Triangle t1(5.0);           -> " << t1 << "\n";
    out << "    Triangle t2(6.0, 8.0, 10.0) -> " << t2 << "\n";

    out << "\n【演示3】合法性验证：非法数据不能进入对象（实验要求 3）\n";
    out << "    静态验证函数（先验证、再构造）：\n";
    out << "      Triangle::isSidesValid(3, 4, 5) = "
        << (Triangle::isSidesValid(3.0, 4.0, 5.0) ? "true" : "false") << "\n";
    out << "      Triangle::isSidesValid(1, 2, 3) = "
        << (Triangle::isSidesValid(1.0, 2.0, 3.0) ? "true" : "false")
        << "   （1+2=3，不满足“任意两边之和大于第三边”）\n";
    out << "    构造函数内再做一次校验，违规直接抛异常：\n";
    try {
        Triangle bad(1.0, 2.0, 3.0);
        out << "      Triangle bad(1, 2, 3);  -> 竟然成功（不应该发生）：" << bad << "\n";
    } catch (const std::exception& e) {
        out << "      Triangle bad(1, 2, 3);  -> 抛出异常：" << e.what() << "\n";
        out << "      注意：构造未完成，这个对象根本没有产生，析构函数也不会被调用。\n";
    }

    out << "\n【演示4】基本操作：修改与获取（实验要求 3-(1)）\n";
    out << "    修改前：" << t2 << "\n";
    out << "    t2.setSides(1, 1, 5) -> " << (t2.setSides(1.0, 1.0, 5.0) ? "true" : "false")
        << "，非法修改被拒绝，对象保持原值：" << t2 << "\n";
    out << "    t2.setSides(5, 5, 6) -> " << (t2.setSides(5.0, 5.0, 6.0) ? "true" : "false")
        << "，修改成功：" << t2 << "\n";
    out << "    逐个获取：sideA()=" << t2.sideA() << ", sideB()=" << t2.sideB()
        << ", sideC()=" << t2.sideC()
        << "，longestSide()=" << t2.longestSide()
        << "，shortestSide()=" << t2.shortestSide() << "\n";

    out << "\n【演示5】其他操作：周长、面积（海伦公式）、类型判断\n";
    const Triangle samples[] = {
        Triangle(3.0, 4.0, 5.0),
        Triangle(2.0, 2.0, 2.0),
        Triangle(5.0, 5.0, 5.0 * std::sqrt(2.0)),
        Triangle(3.0, 3.0, 4.0),
        Triangle(2.0, 3.0, 4.0)
    };
    for (const Triangle& t : samples) {
        out << "    " << t << "\n";
    }
    out << "    类型编号：1=等边 2=等腰直角 3=等腰(非直角) 4=直角(非等腰) 5=一般\n";

    out << "\n【演示6】输出：toString() 与运算符重载 operator<<（实验要求 3-(4)）\n";
    out << "    t2.toString() -> " << t2.toString() << "\n";
    out << "    std::cout << t2 -> " << t2 << "\n";

    out << "\n【演示7】输入：运算符重载 operator>>（输入三边，用空格分隔）\n";
    out << "    例如输入： 6 8 10\n    > ";
    out.flush();
    std::string line;
    if (readLine(in, line) && !line.empty()) {
        std::istringstream iss(line);
        Triangle t3;
        iss >> t3;
        if (iss.fail()) {
            out << "    输入的三边无法构成三角形，读入失败，对象保持默认值：" << t3 << "\n";
        } else {
            out << "    读入成功：" << t3 << "\n";
        }
    } else {
        out << "（已跳过输入演示）\n";
    }

    out << "\n【演示8】对象的生命周期（实验思考题 2 的实证）\n";
    out << "    演示前 liveCount() = " << Triangle::liveCount() << "\n";
    {
        Triangle local1(3.0, 4.0, 5.0);
        Triangle local2(6.0, 8.0, 10.0);
        out << "    进入局部作用域并构造两个对象后 liveCount() = " << Triangle::liveCount() << "\n";
        out << "      local1 = " << local1 << "\n";
        out << "      local2 = " << local2 << "\n";
    }
    out << "    离开作用域后 liveCount() = " << Triangle::liveCount()
        << "（局部对象已按构造的逆序析构）\n";

    out << "\n【演示9】拷贝构造与拷贝赋值：得到的是彼此独立的另一份对象\n";
    Triangle src(3.0, 4.0, 5.0);
    Triangle copy(src);
    Triangle assigned;
    assigned = src;
    src.setSides(6.0, 8.0, 10.0);
    out << "    修改原对象后：src      = " << src << "\n";
    out << "                  copy     = " << copy << "（不受影响）\n";
    out << "                  assigned = " << assigned << "（不受影响）\n";

    out << "\n【演示10】底层原理：按值传参会拷贝，const 引用不会\n";
    const int base = Triangle::liveCount();
    {
        Triangle t(3.0, 4.0, 5.0);
        out << "    定义 t 之后 liveCount() = " << Triangle::liveCount() << "（比演示前多 1）\n";
        out << "    按值传参：形参是副本，函数内 liveCount() = "
            << liveInsideByValue(t) << "，调用结束副本析构 -> liveCount() = "
            << Triangle::liveCount() << "\n";
        out << "    按 const 引用传参：不拷贝，函数内 liveCount() = "
            << liveInsideByRef(t) << "\n";
    }
    out << "    离开作用域后 liveCount() = " << Triangle::liveCount()
        << "，与演示前的 " << base << " 相同\n";

    out << "\n=========== 演示结束 ===========\n";
}

void interactiveCheck(std::istream& in, std::ostream& out) {
    out << "\n=========== 交互式验收：自己构造一个三角形对象 ===========\n";
    out << "请输入三条边长（空格分隔，例如 6 8 10；输入 0 0 0 结束）：\n";

    for (;;) {
        out << "> ";
        out.flush();
        std::string line;
        if (!readLine(in, line)) {
            out << "\n输入已结束，返回主菜单。\n";
            return;
        }
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        double a = 0.0, b = 0.0, c = 0.0;
        std::string rest;
        if (!(iss >> a >> b >> c) || (iss >> rest)) {
            out << "  格式不正确：请输入三个数，例如 3 4 5\n";
            continue;
        }
        if (a == 0.0 && b == 0.0 && c == 0.0) {
            out << "  结束交互式验收。\n";
            return;
        }

        if (!Triangle::isSidesValid(a, b, c)) {
            out << "  验证未通过：三边 " << a << ", " << b << ", " << c
                << " 不能构成三角形。\n  原因：";
            if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
                out << "边长必须为正数。\n";
            } else {
                const double longest = std::max({a, b, c});
                out << "最长边 " << longest << " 不小于另外两边之和 "
                    << (a + b + c - longest) << "。\n";
            }
            out << "  对象没有被构造出来（若直接构造，构造函数会抛 std::invalid_argument）。\n";
            continue;
        }

        Triangle t(a, b, c);
        out << "  构造成功：" << t << "\n";
        out << "  周长 = " << fixed2(t.perimeter())
            << "，面积 = " << fixed2(t.area())
            << "，类型 = " << t.typeName() << "（编号 " << t.typeCode() << "）\n";
        out << "  局部对象 t 将在本次循环结束时析构，此刻 liveCount() = "
            << Triangle::liveCount() << "\n";
    }
}

int g_pass = 0;
int g_fail = 0;

void check(bool condition, const std::string& what, std::ostream& out) {
    if (condition) {
        ++g_pass;
        out << "  [通过] " << what << "\n";
    } else {
        ++g_fail;
        out << "  [失败] " << what << "\n";
    }
}

template <typename T>
bool nearly(T x, T y, double tol = 1e-9) {
    const double dx = std::fabs(static_cast<double>(x) - static_cast<double>(y));
    const double scale = std::max({1.0, std::fabs(static_cast<double>(x)),
                                   std::fabs(static_cast<double>(y))});
    return dx <= tol * scale;
}

int runSelfTest(std::ostream& out) {
    g_pass = 0;
    g_fail = 0;

    out << "\n==================== 内 置 自 检（阶段一） ====================\n";

    out << "[1] 三边合法性验证 isSidesValid\n";
    check(Triangle::isSidesValid(3.0, 4.0, 5.0), "(3,4,5) 合法", out);
    check(Triangle::isSidesValid(1.0, 1.0, 1.0), "(1,1,1) 合法", out);
    check(Triangle::isSidesValid(2.0, 3.0, 4.0), "(2,3,4) 合法", out);
    check(!Triangle::isSidesValid(1.0, 2.0, 3.0), "(1,2,3) 退化，应判为非法", out);
    check(!Triangle::isSidesValid(1.0, 1.0, 2.0), "(1,1,2) 退化，应判为非法", out);
    check(!Triangle::isSidesValid(0.0, 1.0, 1.0), "含 0 边，应判为非法", out);
    check(!Triangle::isSidesValid(-3.0, 4.0, 5.0), "含负边，应判为非法", out);
    check(!Triangle::isSidesValid(std::nan(""), 4.0, 5.0), "含 NaN，应判为非法", out);

    out << "[2] 构造函数（默认构造 / 重载构造 / 构造失败）\n";
    const int base = Triangle::liveCount();
    {
        Triangle d;
        check(nearly(d.sideA(), 3.0) && nearly(d.sideB(), 4.0) && nearly(d.sideC(), 5.0),
              "默认构造把三边初始化为 3-4-5", out);
        check(nearly(d.perimeter(), 12.0), "默认三角形周长 = 12", out);
        check(nearly(d.area(), 6.0), "默认三角形面积 = 6", out);
        check(d.isRight() && d.typeCode() == 4, "默认三角形是直角三角形（编号 4）", out);

        Triangle eq(2.0);
        check(eq.isEquilateral() && eq.typeCode() == 1, "单参数构造得到等边三角形", out);

        Triangle t(6.0, 8.0, 10.0);
        check(nearly(t.perimeter(), 24.0) && nearly(t.area(), 24.0),
              "(6,8,10) 周长 = 24，面积 = 24", out);

        bool threw = false;
        try {
            Triangle bad(1.0, 2.0, 3.0);
            (void)bad;
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        check(threw, "非法三边构造抛出 std::invalid_argument", out);

        check(Triangle::liveCount() == base + 3, "存活对象计数随构造递增", out);
    }
    check(Triangle::liveCount() == base, "离开作用域后对象析构，存活计数复原", out);

    out << "[3] 修改与获取（非法修改被拒绝，且不改变原值）\n";
    Triangle t(3.0, 4.0, 5.0);
    check(!t.setSides(1.0, 2.0, 3.0), "setSides(1,2,3) 返回 false", out);
    check(nearly(t.sideA(), 3.0) && nearly(t.sideB(), 4.0) && nearly(t.sideC(), 5.0),
          "修改失败后对象保持原值 3-4-5", out);
    check(t.setSides(6.0, 8.0, 10.0) && nearly(t.perimeter(), 24.0), "setSides(6,8,10) 成功", out);
    check(!t.setSideA(-1.0), "setSideA(-1) 被拒绝", out);
    check(nearly(t.longestSide(), 10.0) && nearly(t.shortestSide(), 6.0),
          "longestSide()/shortestSide() 正确", out);

    out << "[4] 周长 / 面积 / 类型判断\n";
    const Triangle eq(5.0, 5.0, 5.0);
    const Triangle isoRight(5.0, 5.0, 5.0 * std::sqrt(2.0));
    const Triangle iso(3.0, 3.0, 4.0);
    const Triangle right(3.0, 4.0, 5.0);
    const Triangle scalene(2.0, 3.0, 4.0);
    check(eq.typeCode() == 1 && eq.isAcute(), "(5,5,5) 编号 1（等边、锐角）", out);
    check(isoRight.typeCode() == 2 && isoRight.isRight(), "(5,5,5√2) 编号 2（等腰直角）", out);
    check(iso.typeCode() == 3 && iso.isIsosceles(), "(3,3,4) 编号 3（等腰）", out);
    check(right.typeCode() == 4, "(3,4,5) 编号 4（直角）", out);
    check(scalene.typeCode() == 5 && scalene.isObtuse(), "(2,3,4) 编号 5（一般、钝角）", out);
    check(std::string(Triangle::typeCodeName(2)) == std::string("等腰直角三角形"),
          "类型名称字符串正确", out);
    check(nearly(iso.area(), std::sqrt(20.0), 1e-12), "(3,3,4) 面积 = √20（海伦公式）", out);
    check(nearly(isoRight.area(), 12.5, 1e-12), "(5,5,5√2) 面积 = 12.5", out);
    check(nearly(right.perimeter(), 12.0), "(3,4,5) 周长 = 12", out);

    out << "[5] 拷贝构造与拷贝赋值（对象之间彼此独立）\n";
    Triangle a(3.0, 4.0, 5.0);
    Triangle b(a);
    a.setSides(6.0, 8.0, 10.0);
    check(nearly(b.perimeter(), 12.0), "拷贝得到的副本与原对象相互独立", out);
    Triangle c;
    c = a;
    check(nearly(c.perimeter(), 24.0), "拷贝赋值结果正确", out);

    out << "[6] 输入输出运算符重载\n";
    std::istringstream in1("6 8 10");
    Triangle t6;
    in1 >> t6;
    check(!in1.fail() && nearly(t6.perimeter(), 24.0), "operator>> 读入 (6,8,10)", out);
    std::istringstream in2("1 2 3");
    Triangle t7;
    in2 >> t7;
    check(in2.fail(), "operator>> 读入非法三边时置位 failbit", out);
    std::ostringstream os1;
    os1 << Triangle(3.0, 4.0, 5.0);
    check(os1.str().find("三角形") != std::string::npos, "operator<< 输出包含图形名称", out);

    out << "[7] 值语义：按值传参会拷贝对象，const 引用不会\n";
    {
        const int before = Triangle::liveCount();
        const Triangle tv(3.0, 4.0, 5.0);
        check(Triangle::liveCount() == before + 1, "定义对象时构造 1 个对象", out);
        check(liveInsideByValue(tv) == before + 2 && nearly(tv.perimeter(), 12.0),
              "按值传参：形参是副本（计数 +1）", out);
        check(Triangle::liveCount() == before + 1, "函数返回后副本被析构", out);
        check(liveInsideByRef(tv) == before + 1 && nearly(tv.perimeter(), 12.0),
              "按 const 引用传参：不产生副本", out);
    }

    out << "[8] 控制台输入工具（非法输入不卡死、兼容 BOM）\n";
    {
        std::istringstream bomIn("\xEF\xBB\xBF" "42\r\n");
        std::string lineText;
        check(readLine(bomIn, lineText) && lineText == "42",
              "readLine 去掉 UTF-8 BOM 与行尾 \\r", out);

        int parsed = 0;
        std::istringstream badIn("abc\n7\n");
        check(askInt(badIn, out, "", 1, 9, parsed) && parsed == 7,
              "askInt 对非法输入重新读取，不会死循环", out);

        double value = 0.0;
        std::istringstream numIn("3.5\n");
        check(askDouble(numIn, out, "", value) && nearly(value, 3.5),
              "askDouble 正确读入小数", out);
    }

    out << "---------------------------------------------------------------\n";
    out << "自检结束：通过 " << g_pass << " 项，失败 " << g_fail << " 项。\n";
    if (g_fail == 0) {
        out << "结论：阶段一（类与对象）的类设计符合实验要求。\n";
    } else {
        out << "结论：存在未通过项，请检查上面的输出。\n";
    }
    out << "===============================================================\n";
    return g_fail == 0 ? 0 : 1;
}

}

int main(int argc, char* argv[]) {
    setupConsole();

    if (argc > 1) {
        const std::string arg = argv[1];
        if (arg == "--selftest" || arg == "-t") {
            return runSelfTest(std::cout);
        }
        if (arg == "--help" || arg == "-h") {
            std::cout << "简单几何图形题目系统 · 阶段一：类与对象\n"
                         "用法：GeoQuizSystem [--selftest]\n"
                         "  --selftest  运行内置自检并输出每项检查结果\n";
            return 0;
        }
    }

    std::istream& in = std::cin;
    std::ostream& out = std::cout;

    printBanner(out);
    out << "本阶段只实现一个类：sgs::Triangle（实验一 题目1：三角形题目类）。\n";

    for (;;) {
        printMenu(out);
        int choice = -1;
        if (!askInt(in, out, "请选择功能：", 0, 3, choice)) {
            out << "\n输入已结束，退出系统。\n";
            break;
        }
        out << "\n";
        switch (choice) {
            case 1:
                demoClassAndObject(in, out);
                break;
            case 2:
                interactiveCheck(in, out);
                break;
            case 3:
                (void)runSelfTest(out);
                break;
            case 0:
                out << "感谢使用，再见！\n";
                return 0;
            default:
                break;
        }
    }
    return 0;
}
