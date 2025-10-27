#include <iostream>
#include <cmath>      // тоон функцууд (sqrt, M_PI гэх мэт)
#include <cstring>    // string хувиргах, хуулбарлахад
#include <cstdlib>    // rand() функц ашиглахад
#include <ctime>      // time() функц ашиглахад (санамсаргүй тоог үүсгэхэд)
using namespace std;

// ===== Shape класс =====
// Энэ бол бүх дүрсний хамгийн ерөнхий (суурь) класс юм.
// Бүх дүрсүүд нэртэй байх тул энд name-г хадгална.
// Түүнчлэн area() ба perimeter() функцийг дараа нь удамшсан классууд override хийнэ.
class Shape {
protected:
    char *name;   // дүрсний нэрийг хадгалах хувьсагч
public:
    Shape() {
        // default constructor — нэрийг "No name" гэж анхны утгаар онооно
        name = new char[20];
        strcpy(name, "No name");
    }
    Shape(const char *n) {
        // параметрт орж ирсэн утгаар нэрийг онооно
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    virtual ~Shape() {
        // destructor — new-ээр нөөцөлсөн санах ойг чөлөөлнө
        delete [] name;
    }

    // virtual функц — дараа нь удамшсан класст дахин тодорхойлох боломжтой
    virtual float area() { return 0; }
    virtual float perimeter() { return 0; }

    // нэрийг буцаах getter функц
    char* get_name() { return name; }
};

// ===== 2DShape класс =====
// Энэ класс нь 2 хэмжээст дүрсүүдийн суурь класс юм.
// Shape классыг удамшуулсан бөгөөд бүх дүрсүүд координаттай байх тул
// x[], y[] гэсэн массивуудыг ашиглан оройн байршлыг хадгална.
class TwoDShape : public Shape {
protected:
    float *x;          // x координатуудын массив
    float *y;          // y координатуудын массив
    int point_count;   // дүрсний оройн тоо (жишээ нь: гурвалжин = 3, квадрат = 4)
public:
    // параметрт оройн тоо болон нэрийг авч, Shape-ийн байгуулагчийг дуудна
    TwoDShape(int n = 1, const char *nname = "2DShape") : Shape(nname) {
        point_count = n;               // оройн тоог хадгална
        x = new float[point_count];    // x массивт санах ой нөөцлөнө
        y = new float[point_count];    // y массивт санах ой нөөцлөнө
        // бүх координатыг 0 болгож анхны утгаар онооно
        for (int i = 0; i < point_count; i++) {
            x[i] = 0;
            y[i] = 0;
        }
    }

    ~TwoDShape() {
        // new-ээр нөөцөлсөн массивуудыг устгана
        delete [] x;
        delete [] y;
    }

    // дүрсний мэдээлэл хэвлэх виртуал функц (дараа нь override хийнэ)
    virtual void show_info() {
        cout << "2DShape: " << name << endl;
    }
};

// ===== Circle класс =====
// Энэ класс нь TwoDShape-ээс удамшсан бөгөөд тойргийн төв ба радиусыг хадгална.
class Circle : public TwoDShape {
    float radius;   // радиус
public:
    // параметрт радиус авна, эцэг классын байгуулагчийг (TwoDShape(1, "Circle")) дуудаж ажиллуулна
    Circle(float _r = 1) : TwoDShape(1, "Circle") {
        radius = _r;
        // төвийн координатыг 0–9 хооронд санамсаргүйгээр онооно
        x[0] = rand() % 10;
        y[0] = rand() % 10;
    }

    // Талбайг бодох — πr²
    float area() override { return M_PI * radius * radius; }

    // Периметр — 2πr
    float perimeter() override { return 2 * M_PI * radius; }

    // Мэдээлэл хэвлэх
    void show_info() override {
        cout << "Circle - radius: " << radius << "  area: " << area() << endl;
    }
};

// ===== Square класс =====
// Энэ класс нь квадрат дүрсийг тодорхойлно.
// Эцэг классын байгуулагчийг дуудан 4 оройтой дүрс үүсгэнэ.
class Square : public TwoDShape {
    float side;  // квадратын талын урт
public:
    Square(float _s = 1) : TwoDShape(4, "Square") {
        side = _s;
    }

    // Талбай — side²
    float area() override { return side * side; }

    // Периметр — 4 * side
    float perimeter() override { return 4 * side; }

    // Дүрсний мэдээлэл хэвлэх
    void show_info() override {
        cout << "Square - side: " << side << "  area: " << area() << endl;
    }
};

// ===== Triangle класс =====
// Энэ класс нь зөв гурвалжинг тодорхойлно.
class Triangle : public TwoDShape {
    float side;  // гурвалжны талын урт
public:
    Triangle(float _s = 1) : TwoDShape(3, "Triangle") {
        side = _s;
    }

    // Талбай — (√3 / 4) * side²
    float area() override { return (sqrt(3)/4) * side * side; }

    // Периметр — 3 * side
    float perimeter() override { return 3 * side; }

    // Мэдээлэл хэвлэх
    void show_info() override {
        cout << "Triangle - side: " << side << "  area: " << area() << endl;
    }
};

// ===== Гол програм =====
int main() {
    srand(time(0));  // rand() функцийг одоогийн цагт суурилан randomize хийнэ

    // Объект үүсгэх ба утгыг хуулах жишээ
    TwoDShape o;     // 2 хэмжээст дүрсний объект
    Square s;        // квадрат
    Circle c;        // тойрог
    Triangle t;      // гурвалжин
    o = s; o = c; o = t;   // объект хооронд хуулах үйлдэл (жишээ болгон)

    // Олон дүрсийн массив үүсгэх — полиморфизм ашиглана
    TwoDShape *p[10];   // 10 ширхэг TwoDShape төрлийн заагчийн массив

    // Массивт санамсаргүй дүрсүүдийг оруулна
    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0) p[i] = new Circle(rand() % 10 + 1);   // тойрог
        if (i % 3 == 1) p[i] = new Square(rand() % 10 + 1);   // квадрат
        if (i % 3 == 2) p[i] = new Triangle(rand() % 10 + 1); // гурвалжин
    }

    // Талбайгаар эрэмбэлэх (bubble sort арга)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            if (p[j]->area() > p[j + 1]->area()) {
                // Солих үед түр зуурын заагч tmp ашиглана
                TwoDShape *tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }

    // Эцсийн үр дүн — талбайгаар эрэмбэлэгдсэн дүрсүүдийг хэвлэнэ
    cout << "\nTalbaigaar erembelsen dursuud: \n";
    for (int i = 0; i < 10; i++) {
        p[i]->show_info();   // полиморфик функц — дүрсийн төрлөөс хамаарч зөв show_info() ажиллана
    }

    // Динамик санах ойг чөлөөлнө
    for (int i = 0; i < 10; i++) delete p[i];

    return 0;
}
