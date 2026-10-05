#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <iostream>

class Triangle
{
public:
    class Point
    {
    public:
        Point();
        Point(double xValue, double yValue);
        ~Point();

        void setPoint(double xValue, double yValue);
        double getX() const { return x; }
        double getY() const { return y; }
        void show() const;

    private:
        double x;
        double y;
    };

    Triangle();
    Triangle(double sideA, double sideB, double sideC);
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    Triangle(const Triangle& other);
    ~Triangle();

    Triangle& operator=(const Triangle& other);

    bool setSides(double sideA, double sideB, double sideC);
    bool setSideA(double sideA);
    bool setSideB(double sideB);
    bool setSideC(double sideC);

    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }

    bool   hasVertexA() const { return vertexAValid; }
    Point  getVertexA() const { return vertexA; }
    Point  getVertexB() const { return vertexB; }
    Point  getVertexC() const { return vertexC; }

    void show() const;
    std::string toString() const;

    bool   isValid() const;
    double perimeter() const;
    double area() const;
    bool   isRight() const;
    bool   isEquilateral() const;
    bool   isIsosceles() const;
    std::string typeName() const;

    static int aliveCount() { return objectCount; }

private:
    double sideA;
    double sideB;
    double sideC;

    Point  vertexA;
    Point  vertexB;
    Point  vertexC;
    bool   vertexAValid;

    static int objectCount;

    void copyFrom(const Triangle& other);
};

#endif
