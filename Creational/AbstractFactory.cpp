/*
https://sourcemaking.com/design_patterns/abstract_factory/cpp/2

Discussion. "Think of constructors as factories that churn out objects". Here we are allocating the constructor
responsibility to a factory object, and then using inheritance and virtual member functions to provide a
"virtual constructor" capability. So there are two dimensions of decoupling occurring. The client uses the
factory object instead of "new" to request instances; and, the client "hard-wires" the family, or class,
of that factory only once, and throughout the remainder of the application only relies on the abstract base class.

*/
#include <iostream>
using namespace std;

class Shape {
    protected:
    int id_;
    static int total_;

    public:
        Shape(){
            id_ = total_++;
        }
        virtual void draw() = 0;
};
int Shape::total_ = 0;

class Circle : public Shape {
    public:
        void draw(){
            cout << "Circle " << id_ << ": draw" << endl;
        }
};

class Square : public Shape {
    public:
        void draw(){
            cout << "Square " << id_ << ": draw" << endl;
        }
};

class Ellipse : public Shape {
    public:
        void draw(){
            cout << "Ellipse " << id_ << ": draw" << endl;
        }
};

class Rectangle : public Shape {
    public:
        void draw(){
            cout << "Rectangle " << id_ << ": draw" << endl;
        }
};

class Factory{
    public:
        virtual Shape* createCurvedInstance() = 0;
        virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory {
    public:
        Shape* createCurvedInstance(){
            return new Circle;
        }
        Shape* createStraightInstance(){
            return new Square;
        }
};

class RobustShapedFactory : public Factory {
    public:
        Shape* createCurvedInstance(){
            return new Ellipse;
        }
        Shape* createStraightInstance(){
            return new Rectangle;
        }
};

int main() {
    #ifdef SIMPLE
        Factory* factory = new SimpleShapeFactory;
    #elif ROBUST
        Factory* factory = new RobustShapedFactory;
    #else
        Factory* factory = new SimpleShapeFactory;
    #endif
    Shape* shapes[3];

    shapes[0] = factory->createCurvedInstance();
    shapes[1] = factory->createStraightInstance();
    shapes[2] = factory->createCurvedInstance();

    for(int i = 0; i < sizeof(shapes)/sizeof(shapes[0]); i++){
        shapes[i]->draw();
    }

}