#include <iostream>
#include <cmath>     // math функцүүд ашиглахын тулд
#include <cstring>   // string хувиргах, хуулбарлахад ашиглана
using namespace std;

// 1. Shape класс

// Энэ бол бүх дүрсүүдийн хамгийн ерөнхий класс
// Дүрс болгон нэртэй байдаг тул энд нэрийг хадгална.
// Мөн талбай ба периметрийг олох функцуудыг дараа нь удамшсан
class Shape {
protected:
    char *name; // дүрсний нэр
public:
    Shape() {
        // default constructor — анхны утга онооно
        name = new char[20]; // name-д санах ой нөөцлөх
        strcpy(name, "No name");
    }

    Shape(const char *n) {
        // параметртэй constructor — нэрийг гадаад утгаас авна
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    ~Shape() {
        // destructor — name-д нөөцөлсөн санах ойг чөлөөлнө
        delete [] name;
    }

    void set_name(const char *n) {
        // нэрийг солих setter функц
        delete [] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    char* get_name() {
        // нэрийг буцаах getter функц
        return name;
    }

    // Талбай ба периметрийг ерөнхий байдлаар тодорхойлно.
    float area() {
        cout << "Shape-д area байхгүй!" << endl;
        return 0;
    }

    float perimeter() {
        cout << "Shape-д perimeter байхгүй!" << endl;
        return 0;
    }
};

// 2. 2DShape класс

// Shape-ээс удамшина.
// Бүх 2 хэмжээст дүрсүүд координаттай байдаг.

// Энэ класс нь бүх 2 хэмжээст дүрсүүдийн суурь класс юм.
// Өмнө нь зөвхөн нэг координат (x, y) хадгалдаг байсан бол
// одоо олон оройн координатыг хадгалах чадвартай болголоо.
// Өөрөөр хэлбэл:
//   - Тойрог 1 цэгтэй (төв)
//   - Квадрат 4 оройтой
//   - Гурвалжин 3 оройтой
// гэх мэт дүрсүүд бүгд нэг ижил бүтэцтэйгээр координатаа
// удирдах боломжтой болсон.
class TwoDShape : public Shape {
protected:
    float *x;   // x координатын массив (жишээ нь x[0], x[1], x[2], ...)
    float *y;   // y координатын массив (жишээ нь y[0], y[1], y[2], ...)
    int point_count; // дүрсийн оройн тоо (жишээ нь квадрат бол 4)
public:
    
    // Constructor: оройн тоог параметрээр авч, массив үүсгэнэ
    TwoDShape(int n = 1, const char *nname = "2DShape") : Shape(nname) {
        point_count = n;              // оройн тоо хадгална
        x = new float[point_count];   // x массивт санах ой нөөцлөнө
        y = new float[point_count];   // y массивт санах ой нөөцлөнө
        // бүх координатыг 0 болгоно
        for (int i = 0; i < point_count; i++) {
            x[i] = 0;
            y[i] = 0;
        }
    }

    // Destructor: new-ээр нөөцөлсөн санах ойг чөлөөлнө
    ~TwoDShape() {
        delete [] x;
        delete [] y;
    }

    // оройн тоог буцаах функц
    int get_point_count() const { return point_count; }

    // Тухайн оройн координатыг өөрчлөх функц
    void set_point(int i, float _x, float _y) {
        if (i >= 0 && i < point_count) {
            x[i] = _x;
            y[i] = _y;
        }
    }

    // Тухайн оройн координатыг авах getter функцууд
    
    float get_x(int i) const { return x[i]; }
    float get_y(int i) const { return y[i]; }
};
// 3. Circle класс

// Тойрог нь төв, радиустай дүрс.
class Circle : public TwoDShape {
private:
    float radius;
public:
    Circle(float _x, float _y, float _r, const char *n)
        : TwoDShape(1, n)
    {
        x[0] = _x;
        y[0] = _y;
        radius = _r;
    }

    float area() { return M_PI * radius * radius; }
    float perimeter() { return 2 * M_PI * radius; }

    void show_info() {
        cout << "Toirgiin medeelel: " << endl;
        cout << "Ner: " << name << endl;
        cout << "Tuv: (" << x[0] << ", " << y[0] << ")" << endl;
        cout << "Radius: " << radius << endl;
        cout << "Talbai: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};

// 4. Square класс

// Квадрат нь нэг талын урт, нэг оройгоор тодорхойлогдоно.
class Square : public TwoDShape {
private:
    float side;
public:
    Square(float _x, float _y, float _side, const char *n)
        : TwoDShape(4, n) // квадрат 4 оройтой
    {
        side = _side;

        // Оройнуудыг тодорхойлох (зүүн дээдээс эхэлнэ)
        x[0] = _x;         y[0] = _y;          // зүүн дээд
        x[1] = _x + side;  y[1] = _y;          // баруун дээд
        x[2] = _x + side;  y[2] = _y - side;   // баруун доод
        x[3] = _x;         y[3] = _y - side;   // зүүн доод
    }

    float area() { return side * side; }
    float perimeter() { return 4 * side; }

    void show_info() {
        cout << "Kvadratiin medeelel: " << endl;
        cout << "Ner: " << name << endl;
        cout << "Taliin urt: " << side << endl;
        cout << "Oroinuud: " << endl;
        for (int i = 0; i < point_count; i++) {
            cout << "  (" << x[i] << ", " << y[i] << ")" << endl;
        }
        cout << "Talbai: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};


// 5. Triangle класс

// Зөв гурвалжин нь нэг талын урт, дээд оройн координатаар тодорхойлогдоно.
class Triangle : public TwoDShape {
private:
    float side;
public:
    Triangle(float _x, float _y, float _side, const char *n)
        : TwoDShape(3, n) // гурвалжин 3 оройтой
    {
        side = _side;
        float h = (sqrt(3) / 2) * side;
        x[0] = _x;          y[0] = _y;         // дээд орой
        x[1] = _x - side/2; y[1] = _y - h;     // зүүн доод
        x[2] = _x + side/2; y[2] = _y - h;     // баруун доод
    }

    float area() { return (sqrt(3)/4) * side * side; }
    float perimeter() { return 3 * side; }

    void show_info() {
        cout << "Gurvaljnii medeelel: " << endl;
        cout << "Ner: " << name << endl;
        cout << "Oroinuud: " << endl;
        for (int i = 0; i < point_count; i++) {
            cout << "  (" << x[i] << ", " << y[i] << ")" << endl;
        }
        cout << "Talbai: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};


// 6. Програмын гол хэсэг

int main() {
    // Тойрог үүсгэж, мэдээллийг хэвлэнэ
    Circle c(0, 0, 5, "Toirog");
    c.show_info();

    cout << endl;

    // Квадрат үүсгэж, мэдээллийг хэвлэнэ
    Square s(0, 5, 4, "Kvadrat");
    s.show_info();

    cout << endl;

    // Зөв гурвалжин үүсгэж, мэдээллийг хэвлэнэ
    Triangle t(0, 10, 6, "Gurvaljin");
    t.show_info();

    return 0;
}
