#include "Triangle.h"

#include <algorithm>
#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace sgs {

namespace {

void sortSides(double& x, double& y, double& z) {
    if (x > y) std::swap(x, y);
    if (y > z) std::swap(z, y);
    if (x > y) std::swap(x, y);
}

bool nearlyEqual(double p, double q, double eps) {
    const double scale = std::max({1.0, std::fabs(p), std::fabs(q)});
    return std::fabs(p - q) <= eps * scale;
}

double heronArea(double a, double b, double c) {
    const double s = (a + b + c) / 2.0;
    const double v = s * (s - a) * (s - b) * (s - c);
    return v > 0.0 ? std::sqrt(v) : 0.0;
}

}

int Triangle::liveCount_ = 0;

Triangle::Triangle() : a_(3.0), b_(4.0), c_(5.0) {
    ++liveCount_;
}

Triangle::Triangle(double side) : a_(side), b_(side), c_(side) {
    if (!isSidesValid(a_, b_, c_)) {
        std::ostringstream oss;
        oss << "非法的边长: side=" << side << "（必须为正数）";
        throw std::invalid_argument(oss.str());
    }
    ++liveCount_;
}

Triangle::Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
    if (!isSidesValid(a_, b_, c_)) {
        std::ostringstream oss;
        oss << "非法的三边: a=" << a << ", b=" << b << ", c=" << c
            << "（三边必须为正数，且任意两边之和大于第三边）";
        throw std::invalid_argument(oss.str());
    }
    ++liveCount_;
}

Triangle::Triangle(const Triangle& other) : a_(other.a_), b_(other.b_), c_(other.c_) {
    ++liveCount_;
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        a_ = other.a_;
        b_ = other.b_;
        c_ = other.c_;
    }
    return *this;
}

Triangle::~Triangle() {
    --liveCount_;
}

int Triangle::liveCount() {
    return liveCount_;
}

bool Triangle::isSidesValid(double a, double b, double c) {
    if (!std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c)) {
        return false;
    }
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    const double tol = kEps * std::max(1.0, a + b + c);
    return (a + b - c) > tol && (a + c - b) > tol && (b + c - a) > tol;
}

bool Triangle::isTriangle() const {
    return isSidesValid(a_, b_, c_);
}

bool Triangle::setSides(double a, double b, double c) {
    if (!isSidesValid(a, b, c)) {
        return false;
    }
    a_ = a;
    b_ = b;
    c_ = c;
    return true;
}

bool Triangle::setSideA(double a) { return setSides(a, b_, c_); }
bool Triangle::setSideB(double b) { return setSides(a_, b, c_); }
bool Triangle::setSideC(double c) { return setSides(a_, b_, c); }

double Triangle::sideA() const { return a_; }
double Triangle::sideB() const { return b_; }
double Triangle::sideC() const { return c_; }

double Triangle::longestSide() const { return std::max({a_, b_, c_}); }
double Triangle::shortestSide() const { return std::min({a_, b_, c_}); }

double Triangle::perimeter() const {
    return a_ + b_ + c_;
}

double Triangle::area() const {
    return isTriangle() ? heronArea(a_, b_, c_) : 0.0;
}

bool Triangle::isEquilateral() const {
    return nearlyEqual(a_, b_, kEps) && nearlyEqual(b_, c_, kEps);
}

bool Triangle::isIsosceles() const {
    return nearlyEqual(a_, b_, kEps) || nearlyEqual(b_, c_, kEps) || nearlyEqual(a_, c_, kEps);
}

bool Triangle::isRight() const {
    if (!isTriangle()) return false;
    double x = a_, y = b_, z = c_;
    sortSides(x, y, z);
    const double lhs = x * x + y * y;
    const double rhs = z * z;
    return std::fabs(lhs - rhs) <= kEps * std::max(1.0, lhs + rhs);
}

bool Triangle::isObtuse() const {
    if (!isTriangle()) return false;
    double x = a_, y = b_, z = c_;
    sortSides(x, y, z);
    const double lhs = x * x + y * y;
    const double rhs = z * z;
    return rhs - lhs > kEps * std::max(1.0, lhs + rhs);
}

bool Triangle::isAcute() const {
    return isTriangle() && !isRight() && !isObtuse();
}

int Triangle::typeCode() const {
    if (!isTriangle()) return 0;
    const bool eq = isEquilateral();
    const bool iso = isIsosceles();
    const bool rt = isRight();
    if (eq) return 1;
    if (iso && rt) return 2;
    if (iso) return 3;
    if (rt) return 4;
    return 5;
}

const char* Triangle::typeCodeName(int code) {
    switch (code) {
        case 1: return "等边三角形";
        case 2: return "等腰直角三角形";
        case 3: return "等腰三角形";
        case 4: return "直角三角形";
        case 5: return "一般三角形";
        default: return "非三角形";
    }
}

std::string Triangle::typeName() const {
    return typeCodeName(typeCode());
}

std::string Triangle::toString() const {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(2);
    oss << "三角形[a=" << a_ << ", b=" << b_ << ", c=" << c_
        << " | 周长=" << perimeter()
        << ", 面积=" << area()
        << ", 类型=" << typeName() << "]";
    return oss.str();
}

void Triangle::print(std::ostream& os) const {
    os << toString();
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    t.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& t) {
    double a = 0.0, b = 0.0, c = 0.0;
    if (!(is >> a >> b >> c)) {
        return is;
    }
    if (!t.setSides(a, b, c)) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

}
