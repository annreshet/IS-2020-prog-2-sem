#pragma once
#include <cmath>

class Point {
private:
    int x, y;
public:
    Point(); //default constructor
    Point(int x, int y); //constructor using coords
    Point(const Point &other); //copy constructor
    Point& operator = (const Point &other); //overloading of =
    int getX() const;
    int getY() const;
};

double distance(const Point &first, const Point &second);
bool isCosZero(const Point &p1, const Point &p2);

class PolygonalChain {
private:
    int size;
    Point *points;
public:
    PolygonalChain(); //default constructor
    // fixed int by value
    PolygonalChain(int size, Point* newPoints); //constructor using data
    PolygonalChain(const PolygonalChain &other); //copy constructor
    PolygonalChain& operator=(const PolygonalChain &other); //overloading of =
    int getN() const;
    Point getPoint(int i) const;
    virtual double perimeter() const;
    virtual ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain(int newSize, Point *newPoints);  //constructor using data
    double perimeter() const override;
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon(int size, Point *newPoints); //constructor using data
    //fixed virtual
    virtual double area() const;
};

class Triangle : public Polygon {
public:
    Triangle(int size, Point *newPoints); //constructor using data
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid(int size, Point *newPoints); //constructor using data
    double height() const;
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(int size, Point *newPoints); //constructor using data
    double perimeter() const override;
    double area() const override;
};
