#include "Triangle.h"

#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

int Triangle::objectCount = 0;

namespace
{
    const double EPS = 1e-9;

    bool equalDouble(double left, double right)
    {
        return fabs(left - right) < EPS;
    }

    double minOf(double x, double y, double z)
    {
        double m = x;
        if (y < m) m = y;
        if (z < m) m = z;
        return m;
    }

    double maxOf(double x, double y, double z)
    {
        double m = x;
        if (y > m) m = y;
        if (z > m) m = z;
        return m;
    }
}

Triangle::Point::Point() : x(0.0), y(0.0)
{
}

Triangle::Point::Point(double xValue, double yValue) : x(xValue), y(yValue)
{
}

Triangle::Point::~Point()
{
}

void Triangle::Point::setPoint(double xValue, double yValue)
{
    x = xValue;
    y = yValue;
}

void Triangle::Point::show() const
{
    cout << "(" << x << ", " << y << ")";
}

Triangle::Triangle()
    : sideA(3.0), sideB(4.0), sideC(5.0),
      vertexA(0.0, 0.0), vertexB(4.0, 0.0), vertexC(0.0, 3.0), vertexAValid(true)
{
    ++objectCount;
}

Triangle::Triangle(double a, double b, double c)
    : sideA(a), sideB(b), sideC(c),
      vertexA(0.0, 0.0), vertexB(4.0, 0.0), vertexC(0.0, 3.0), vertexAValid(true)
{
    ++objectCount;
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
    : sideA(0.0), sideB(0.0), sideC(0.0),
      vertexA(p1), vertexB(p2), vertexC(p3), vertexAValid(true)
{
    sideA = sqrt(pow(p2.getX() - p3.getX(), 2) + pow(p2.getY() - p3.getY(), 2));
    sideB = sqrt(pow(p1.getX() - p3.getX(), 2) + pow(p1.getY() - p3.getY(), 2));
    sideC = sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
    ++objectCount;
}

Triangle::Triangle(const Triangle& other)
    : sideA(other.sideA), sideB(other.sideB), sideC(other.sideC),
      vertexA(other.vertexA), vertexB(other.vertexB), vertexC(other.vertexC),
      vertexAValid(other.vertexAValid)
{
    ++objectCount;
}

Triangle::~Triangle()
{
    --objectCount;
}

Triangle& Triangle::operator=(const Triangle& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

void Triangle::copyFrom(const Triangle& other)
{
    sideA = other.sideA;
    sideB = other.sideB;
    sideC = other.sideC;
    vertexA = other.vertexA;
    vertexB = other.vertexB;
    vertexC = other.vertexC;
    vertexAValid = other.vertexAValid;
}

bool Triangle::setSideA(double a)
{
    double old = sideA;
    sideA = a;
    if (!isValid())
    {
        sideA = old;
        return false;
    }
    return true;
}

bool Triangle::setSideB(double b)
{
    double old = sideB;
    sideB = b;
    if (!isValid())
    {
        sideB = old;
        return false;
    }
    return true;
}

bool Triangle::setSideC(double c)
{
    double old = sideC;
    sideC = c;
    if (!isValid())
    {
        sideC = old;
        return false;
    }
    return true;
}

bool Triangle::setSides(double a, double b, double c)
{
    double oldA = sideA;
    double oldB = sideB;
    double oldC = sideC;

    sideA = a;
    sideB = b;
    sideC = c;

    if (!isValid())
    {
        sideA = oldA;
        sideB = oldB;
        sideC = oldC;
        return false;
    }
    return true;
}

void Triangle::show() const
{
    cout << "边 a = " << sideA << "，边 b = " << sideB << "，边 c = " << sideC << endl;
    cout << "周长 = " << perimeter() << "，面积 = " << area() << endl;
    cout << "类型 = " << typeName() << endl;
    if (vertexAValid)
    {
        cout << "顶点 A = ";
        vertexA.show();
        cout << "，顶点 B = ";
        vertexB.show();
        cout << "，顶点 C = ";
        vertexC.show();
        cout << endl;
    }
}

string Triangle::toString() const
{
    ostringstream buffer;
    buffer << "三边为 " << sideA << "、" << sideB << "、" << sideC
           << "（周长 " << perimeter() << "，面积 " << area()
           << "，" << typeName() << "）";
    return buffer.str();
}

bool Triangle::isValid() const
{
    return sideA > 0.0 && sideB > 0.0 && sideC > 0.0 &&
           sideA + sideB > sideC &&
           sideA + sideC > sideB &&
           sideB + sideC > sideA;
}

double Triangle::perimeter() const
{
    return sideA + sideB + sideC;
}

double Triangle::area() const
{
    if (!isValid())
    {
        return 0.0;
    }
    double s = perimeter() / 2.0;
    double value = s * (s - sideA) * (s - sideB) * (s - sideC);
    if (value < 0.0)
    {
        value = 0.0;
    }
    return sqrt(value);
}

bool Triangle::isRight() const
{
    if (!isValid())
    {
        return false;
    }
    double longest = maxOf(sideA, sideB, sideC);
    double sum = sideA * sideA + sideB * sideB + sideC * sideC;

    return equalDouble(2.0 * longest * longest, sum);
}

bool Triangle::isEquilateral() const
{
    return isValid() &&
           equalDouble(sideA, sideB) &&
           equalDouble(sideB, sideC);
}

bool Triangle::isIsosceles() const
{
    return isValid() &&
           (equalDouble(sideA, sideB) ||
            equalDouble(sideB, sideC) ||
            equalDouble(sideA, sideC));
}

string Triangle::typeName() const
{
    if (!isValid())
    {
        return "不是三角形（三边不能构成三角形）";
    }
    if (isEquilateral())
    {
        return "等边三角形";
    }

    string name;
    if (isIsosceles())
    {
        name = "等腰三角形";
    }
    else
    {
        name = "一般三角形";
    }

    if (isRight())
    {
        name += "（同时是直角三角形）";
    }
    return name;
}
