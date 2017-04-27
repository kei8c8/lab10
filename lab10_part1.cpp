//============================================================================
// Name        : lab10_part1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class BaseConic{
	protected: //so the derived classes have access to these
		double x;
		double y;
	public:
		BaseConic();
		virtual ~BaseConic();
		void Move(double nx, double ny){x=nx;y=ny;};
		virtual double Area() const = 0; //pure virtual function
		//virtual void Resize();
		virtual void Display() const = 0; //pure virtual function

};

class Ellipse : public BaseConic{
	private:
		double a; //semi-major axis
		double b; //semi-minor axis
		double angle; //orientation
		vector <double> a1;
		vector <double> a2;

	public:
	Ellipse();
	~Ellipse();
	void rotate(double new_angle){angle += new_angle;}; //rotates ellipse
	void Resize(double na, double nb){a=na; b=nb;}; //sets new axis lengths
	void vertices_position(void); //finds the positions of the major-axis vertices
	virtual double Area() const {return 3.14159*a*b;};
	virtual void Display() const;
};

class Circle : public BaseConic{
	private:
		double r; //radius
	public:
	Circle();
	~Circle();
	void pointLocation(double x_loc, double y_loc); //determines if point is inside, outside, or on the circle
	virtual double Area() const {return 3.14159*r*r;}
	virtual void Display() const;
	void Resize(double nr){r=nr;}; //sets new radius
};

BaseConic::BaseConic(void){
	x = 0; //initializes x to zero
	y = 0; //initializes y to zero
}

BaseConic::~BaseConic(void){
	//destructor
}

Ellipse::Ellipse(void){
	//initializes variables
	a = 0;
	b = 0;
	angle = 0;
}

Ellipse::~Ellipse(void){
	//destructor

}

Circle::Circle(void){
	//initializes variables
	r = 0;
}

Circle::~Circle(void){
	//destructor
}

int main() {
	Circle cir;
	cir.Resize(4.0); //tests resize method
	cir.Area();
	cir.pointLocation(1,3); //should be in circle
	cir.Display();
	cir.Move(3.0,5.0); //move from baseconic
	cir.Display();

	Ellipse e;
	e.Resize(4.0,2.0); //declares a and b
	//e.vertices_position(); //sets vertices
	e.Area(); //calculates area
	e.Display(); //first print
	e.Move(1.0, 0.0); //move to the right one
	e.rotate(90); //rotates at 90 degrees
	e.Display();


	//makes abc ppointers to the objects
	BaseConic* bc1;
	bc1 = &cir;
	BaseConic* bc2;
	bc2 = &e;

	bc1->Display(); //tests dynamic binding for printing to screen
	bc2->Display();

	return 0;
}

void Circle::Display(void) const{
	cout << "\nOrigin: (" << x << "," << y << ") \nRadius: " << r << endl;

	double ar = Area(); //gets the area if the circle
	cout << "Area: " << ar << endl;

	return;
}

void Ellipse::Display(void) const{
	cout << "\nOrigin: (" << x << "," << y << ") \nAngle: " << angle
		 << "\nSemi-major axis length: " << a << "\nSemi-minor axis length: " << b
		 << endl;

	double ar = Area(); //gets the area if the circle
	cout << "Area: " << ar << endl;

	/*cout << "\nVertices 1: (" << a1[0] << "," << a1[1] << ")\nVertices 2: ("
		 << a2[0] << "," << a2[1] << ")" <<endl;*/

	return;
}

void Circle::pointLocation(double x_loc, double y_loc){
	if((x_loc-x)>r || (y_loc-y)>r){ //if any of its components are greater than the radius
		cout << "\nThis point is outside the circle." << endl;
	}
	else if((x_loc-x)<r && (y_loc-y)<r){ //if both of its components are greater than the radius
		cout << "\nThis point is inside the circle." << endl;
	}
	else{
		cout << "\nThis point is on the circle." << endl; //default is on the circle
	}

	return;
}

void Ellipse::vertices_position(void){

	//initializes at 0,0
	if(x==0 && y==0){
		a1[0] = -a;
		a1[1] = 0;
		a2[0] -= a;
		a2[1] = 0;
	}
	else{
		double s = sin(angle);
		double c = cos(angle);

		/*a1[0] -= x; //subtract the origin from the point
		a1[1] -= y;
		a2[0] -= x;
		a2[1] -= y;*/

		  // rotate point
		  float a1xnew = (a1[0] * c) - (a1[1] * s);
		  float a1ynew = (a1[0] * s) + (a1[1] * c);
		  float a2xnew = (a2[0] * c) - (a2[1] * s);
		  float a2ynew = (a2[0] * s) + (a2[1] * c);

		  // translate point back:
		  a1[0] = a1xnew + x;
		  a1[1] = a1ynew + y;
		  a2[0] = a2xnew + x;
		  a2[1] = a2ynew + y;
	}

	  return;
}
