#pragma once

#include <iosfwd>
#include <string>

namespace sgs {

class Triangle {
public:
    Triangle();
    Triangle(double side);
    Triangle(double a, double b, double c);
    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);
    ~Triangle();

    static bool isSidesValid(double a, double b, double c);

    bool setSides(double a, double b, double c);
    bool setSideA(double a);
    bool setSideB(double b);
    bool setSideC(double c);

    double sideA() const;
    double sideB() const;
    double sideC() const;
    double longestSide() const;
    double shortestSide() const;

    double perimeter() const;
    double area() const;

    bool isTriangle() const;
    bool isEquilateral() const;
    bool isIsosceles() const;
    bool isRight() const;
    bool isObtuse() const;
    bool isAcute() const;

    static constexpr int kTypeCount = 5;
    int typeCode() const;
    static const char* typeCodeName(int code);
    std::string typeName() const;

    std::string toString() const;
    void print(std::ostream& os) const;

    static int liveCount();

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
    friend std::istream& operator>>(std::istream& is, Triangle& t);

    static constexpr double kEps = 1e-9;

private:
    double a_;
    double b_;
    double c_;

    static int liveCount_;
};

}
