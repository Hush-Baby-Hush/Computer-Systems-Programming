#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 

Shape::Shape(string name)
{
	name_ = name;
}

string Shape::getName() 
{
	return name_;
}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width , double length ):Shape("Rectangle")
{
	width_ = width;
	length_ = length;
}

double Rectangle::getArea() const
{
	return width_*length_;
}

double Rectangle::getVolume() const
{
	return 0;
}

Rectangle Rectangle::operator + (const Rectangle& rec)
{
	Rectangle R3(width_+rec.getWidth(),length_+rec.getLength());
	return R3;
}

Rectangle Rectangle::operator - (const Rectangle& rec)
{
	Rectangle R3(max(0.0,width_-rec.getWidth()),max(0.0,length_-rec.getLength()));
	return R3;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Circle::Circle(double radius):Shape("Circle")
{
	radius_ = radius;
}

double Circle::getArea() const
{
	return pow(radius_,2) * M_PI;
}

double Circle::getVolume() const
{
	return 0;
}

Circle Circle::operator + (const Circle& cir)
{
	Circle R3(radius_+cir.getRadius());
	return R3;
}

Circle Circle::operator - (const Circle& cir)
{
	Circle R3(max(0.0,radius_-cir.getRadius()));
	return R3;
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere")
{
	radius_ = radius;
}

double Sphere::getVolume() const
{
	return (4.0 / 3.0) * pow(radius_,3) * M_PI;
}

double Sphere::getArea() const
{
	return 4 * M_PI * pow(radius_,2);
}

Sphere Sphere::operator + (const Sphere& sph)
{
	Sphere R3(radius_+sph.getRadius());
	return R3;
}

Sphere Sphere::operator - (const Sphere& sph)
{
	Sphere R3(max(0.0,radius_-sph.getRadius()));
	return R3;
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism")
{
	width_ = width;
	length_ = length;
	height_ = height;
}

double RectPrism::getVolume() const
{
	return length_ * width_ * height_;
}

double RectPrism::getArea() const
{
	return 2 * (length_ *  width_  + length_ * height_ + width_ * height_);
}

RectPrism RectPrism::operator + (const RectPrism& rectp)
{
	RectPrism R3(width_+rectp.getWidth(),length_+rectp.getLength(),height_+rectp.getHeight());
	return R3;
}

RectPrism RectPrism::operator - (const RectPrism& rectp)
{
	RectPrism R3(max(0.0, width_-rectp.getWidth()), max(0.0, length_-rectp.getLength()), max(0.0, height_-rectp.getHeight()));
	return R3;
}



double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name)
{
	//@@Insert your code here
	int number;
	vector<Shape*> creat_;
	ifstream file;
	file.open(file_name,std::ifstream::in);
	file >> number;
	int i;
	for( i = 0; i < number; i++)
	{
		string ss;
		file >> ss;

		if(ss=="Rectangle")
		{
			double w,l;
			file >> w >> l;
			Rectangle* rect = new Rectangle(w,l);
			creat_.push_back(rect);
		}

		if(ss=="Circle")
		{
			double r;
			file >> r;
			Circle* cir = new Circle(r);
			creat_.push_back(cir);
		}

		if(ss=="Sphere")
		{
			double r;
			file >> r;
			Sphere* sph = new Sphere(r);
			creat_.push_back(sph);
		}

		if(ss=="RectPrism")
		{
			double w,l,h;
			file >> w >> l >> h;
			RectPrism* rprism = new RectPrism(w,l,h);
			creat_.push_back(rprism);
		}
	}

	file.close();
	return creat_; // please remeber to modify this line to return the correct value
}









// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	int i;
	for ( i = 0; i < shapes.size(); i++)
	{
		if (max_area < shapes[i]->getArea())
		{
			max_area = shapes[i]->getArea();
		}
		
	}
	
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	int i;
	for ( i = 0; i < shapes.size(); i++)
	{
		if (max_volume < shapes[i]->getVolume())
		{
			max_volume = shapes[i]->getVolume();
		}
		
	}
	
	return max_volume;
}

