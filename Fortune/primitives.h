#ifndef PRIMS
#define PRIMS

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define NILL MyDouble(0)
struct Segment;
struct Point;
struct Line;
struct Polygon;


int GCD(int, int);

struct rational
{
	rational();
	rational(int, int den = 1);
	void get_int();
	bool operator==(const rational &) const;
	bool operator==(int);
	bool operator!=(const rational &);
	bool operator!=(int);

	rational operator +(const rational &) const;
	rational operator+=(const rational &);
	rational operator -();
	rational operator - (rational &) const;
	rational operator-=(rational &);
	rational operator *(const rational &) const;
	rational operator *(int);
	rational operator*=(const rational &);
	rational operator /(const rational &) const;
	rational operator/=(const rational &);

	void print();
	int nom;
	int den;
};

struct MyDouble
{
	MyDouble();
	MyDouble(double);
	operator double() const;

	MyDouble &operator =(const MyDouble&);
	MyDouble operator +(double);
	MyDouble operator+=(double);
	MyDouble operator -();
	MyDouble operator -(double);
	MyDouble operator-=(double);
	MyDouble operator *(double);
	MyDouble operator*=(double);
	MyDouble operator /(double);
	MyDouble operator/=(double);
	bool operator==(MyDouble);
	bool operator<=(MyDouble);
	bool operator>=(MyDouble);
	bool operator <(MyDouble);
	bool operator >(MyDouble);

	friend istream& operator>>(istream&, MyDouble&);
	friend ostream& operator<<(ostream&, MyDouble&);

	~MyDouble() {}

	const double eps = 1e-5;
	double value;
};


struct Segment
{
	Segment();
	Segment(MyDouble, MyDouble, MyDouble, MyDouble);
	Segment(pair<MyDouble, MyDouble>, pair<MyDouble, MyDouble>);
	Segment(Point, Point);
	Segment(Segment const &);
	Segment & operator=(Segment);

	MyDouble x_project();
	MyDouble y_project();
	Segment operator +(Segment);
	Segment operator+=(Segment);
	Segment operator -();
	Segment operator -(Segment);
	Segment operator-=(Segment);
	Segment operator *(MyDouble);
	Segment operator*=(MyDouble);

	//scalar product
	MyDouble operator *(Segment);
	//vector product
	MyDouble operator ^(Segment);
	MyDouble len();
	void print();
	bool between(Point);
	bool contain(Point);
	//пересечение отрезков
	bool cross(Segment);
	Segment normalise();

	pair<MyDouble, MyDouble> start;
	pair<MyDouble, MyDouble> end;
};


struct Point : Segment
{
	Point();
	Point(pair<MyDouble, MyDouble>);
	Point(MyDouble, MyDouble);
	Point(Segment);
	Point &operator=(Point);
	void get();

	bool operator==(Point &);
	bool operator!=(Point &);
	bool operator >(Point &);
	bool operator <(Point &);
	bool operator>=(Point &);
	bool operator<=(Point &);

	Segment operator >>(Segment);
	Segment operator <<(Segment);
	void print(bool nice = true);
	MyDouble polar_ang(Point, Point);
	MyDouble & x();
	MyDouble & y();
	friend istream& operator>>(istream&, Point&);
	friend ostream& operator<<(ostream&, Point&);
};

struct Line
{
	// guiding vector
	Line(Segment);
	// two points
	Line(Point, Point);
	// point and normal
	Line(Point, Segment);
	MyDouble operator()(Point);

	Point intersection(Line);
	int parallel(Line);
	MyDouble a;
	MyDouble b;
	MyDouble c;
	Point pnt;
	/*
	ax + by + c = 0
	*/
};

struct Polygon
{
	Polygon();
	Polygon(vector<Point>);
	Polygon(int);

	struct Comp
	{
		Comp(Point);
		bool operator()(Point &, Point &);
		Point origin;
	};
	void convex_hull(vector<Point>);
	void print();
	int n;
	vector<Point> points;
};

#endif
