#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib> // rand() ашиглахад
#include <ctime>   // time() ашиглахад
using namespace std;

// ===== Shape класс =====
class Shape {
protected:
    char *name;
public:
    Shape() {
        name = new char[20];
        strcpy(name, "No name");
    }
    Shape(const char *n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    virtual ~Shape() {
        delete [] name;
    }
    virtual float area() { return 0; }        // virtual функц — override-д ашиглана
    virtual float perimeter() { return 0; }
    char* get_name() { return name; }
};

// ===== 2DShape класс =====
class TwoDShape : public Shape {
protected:
    float *x;
    float *y;
    int point_count;
public:
    TwoDShape(int n = 1, const char *nname = "2DShape") : Shape(nname) {
        point_count = n;
        x = new float[point_count];
        y = new float[point_count];
        for (int i = 0; i < point_count; i++) {
            x[i] = 0;
            y[i] = 0;
        }
    }
    ~TwoDShape() {
        delete [] x;
        delete [] y;
    }
    virtual void show_info() {
        cout << "2DShape: " << name << endl;
    }
};

// ===== Circle класс =====
class Circle : public TwoDShape {
    float radius;
public:
    Circle(float _r = 1) : TwoDShape(1, "Circle") {
        radius = _r;
        x[0] = rand() % 10;
        y[0] = rand() % 10;
    }
    float area() override { return M_PI * radius * radius; }
    float perimeter() override { return 2 * M_PI * radius; }
    void show_info() override {
        cout << "Circle - radius: " << radius << "  area: " << area() << endl;
    }
};

// ===== Square класс =====
class Square : public TwoDShape {
    float side;
public:
    Square(float _s = 1) : TwoDShape(4, "Square") {
        side = _s;
    }
    float area() override { return side * side; }
    float perimeter() override { return 4 * side; }
    void show_info() override {
        cout << "Square - side: " << side << "  area: " << area() << endl;
    }
};

// ===== Triangle класс =====
class Triangle : public TwoDShape {
    float side;
public:
    Triangle(float _s = 1) : TwoDShape(3, "Triangle") {
        side = _s;
    }
    float area() override { return (sqrt(3)/4) * side * side; }
    float perimeter() override { return 3 * side; }
    void show_info() override {
        cout << "Triangle - side: " << side << "  area: " << area() << endl;
    }
};

// ===== Гол програм =====
int main() {
    srand(time(0));

    // Объект үүсгэх, хуулах жишээ
    TwoDShape o;
    Square s;
    Circle c;
    Triangle t;
    o = s; o = c; o = t;   // энгийн даалгаврын санааг дүрслэв

    // Олон дүрсийн массив үүсгэх
    TwoDShape *p[10];

    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0) p[i] = new Circle(rand() % 10 + 1);
        if (i % 3 == 1) p[i] = new Square(rand() % 10 + 1);
        if (i % 3 == 2) p[i] = new Triangle(rand() % 10 + 1);
    }

    // Талбайгаар эрэмбэлэх (bubble sort)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            if (p[j]->area() > p[j + 1]->area()) {
                TwoDShape *tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }

    cout << "\n=== Talbaigaar erembelsen dursuud ===\n";
    for (int i = 0; i < 10; i++) {
        p[i]->show_info();
    }

    // Санах ойг чөлөөлнө
    for (int i = 0; i < 10; i++) delete p[i];

    return 0;
}
