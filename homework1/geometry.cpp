#include "geometry.h"

double distance(const Point &first, const Point &second) {
    return sqrt((double(second.getX()) - double(first.getX())) * (double(second.getX()) - double(first.getX())) + (double(second.getY()) - double(first.getY())) * (double(second.getY()) - double(first.getY())));
}

bool isCosZero(const Point &p1, const Point &p2) {
    double cosAngle = p1.getX() * p2.getX() + p1.getX() * p2.getY();
    return cosAngle == 0;
}

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(const int &valueX, const int &valueY) : x(valueX), y(valueY) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point &other) {
    x = other.x;
    y = other.y;
    return *this;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

PolygonalChain::PolygonalChain() { //default constructor
    size = 0;
    points = nullptr;
}

PolygonalChain::PolygonalChain(const int &newSize, Point* newPoints) { //constructor using data
    size = newSize;
    points = new Point[newSize];
    for (int i = 0; i < size; i++) {
        points[i] = newPoints[i];
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain &other) { //copy constructor
    this->size = other.size;
    this->points = new Point[other.size];
    for (int i = 0; i < other.size; i++) {
        this->points[i] = other.points[i];
    }
}

PolygonalChain& PolygonalChain::operator=(const PolygonalChain &other) { //overloading of =
    //todo memory leak
    this->size = other.size;
    this->points = new Point[other.size];
    for (int i = 0; i < other.size; i++) {
        this->points[i] = other.points[i];
    }
    return *this;
}

int PolygonalChain::getN() const {
    return size;
}

Point PolygonalChain::getPoint(int i) const {
    return points[i];
}

double PolygonalChain::perimeter() const {
    double per = 0;
    for (int i = 0; i < size - 1; i++) {
        per += distance(points[i],points[i + 1]);
    }
    return per;
}

PolygonalChain::~PolygonalChain() {
    delete[] points;
}

ClosedPolygonalChain::ClosedPolygonalChain(const int &size, Point *newPoints) : PolygonalChain(size, newPoints) {}

double ClosedPolygonalChain::perimeter() const {
    double per = 0;
    per += this->PolygonalChain::perimeter();
    Point first = this->getPoint(0);
    Point second = this->getPoint(getN() - 1);
    per += distance(first, second);
    return per;
}

//Polygon::Polygon() : ClosedPolygonalChain() {}

Polygon::Polygon(const int &size, Point* newPoints) : ClosedPolygonalChain(size, newPoints) {}

double Polygon::area() const {
	//todo ar int
    double ar = 0;
    for (int i = 0; i < this->getN() - 1; i++) {
        ar += this->getPoint(i).getX() * this->getPoint(i + 1).getY() -
              this->getPoint(i + 1).getX() * this->getPoint(i).getY();
    }
    ar += this->getPoint(getN() - 1).getX() * this->getPoint(0).getY() -
            this->getPoint(0).getX() * this->getPoint(getN() - 1).getY();
    return fabs(ar) * 0.5;
}

Triangle::Triangle(const int &size, Point *newPoints) : Polygon(size, newPoints) {}

bool Triangle::hasRightAngle() const {
    Point p1 (this->getPoint(0).getX() - this->getPoint(1).getX(), this->getPoint(0).getY() - this->getPoint(1).getY());
    Point p2 (this->getPoint(1).getX() - this->getPoint(2).getX(), this->getPoint(1).getY() - this->getPoint(2).getY());
    Point p3 (this->getPoint(0).getX() - this->getPoint(2).getX(), this->getPoint(0).getY() - this->getPoint(2).getY());
    //todo return expression
    if (isCosZero(p1, p2) || isCosZero(p2, p3) || isCosZero(p1, p3))
        return true;
    else
        return false;
}

Trapezoid::Trapezoid(const int &size, Point *newPoints) : Polygon(size, newPoints) {}

double Trapezoid::height() const {
    Point p1 = this->getPoint(0);
    Point p2 = this->getPoint(1);
    Point p3 = this->getPoint(2);
    Point p4 = this->getPoint(3);
    return (2 * this->area()) / (distance(p2, p3) + distance(p1, p4));
}

RegularPolygon::RegularPolygon(const int &size, Point *newPoints) : Polygon(size, newPoints) {}

double RegularPolygon::perimeter() const {
    return getN() * distance(getPoint(0), getPoint(1));
}

double RegularPolygon::area() const {
    double side = distance(getPoint(0), getPoint(1));
    return (getN() * side * side) / (4 * tan(M_PI / getN()));
}