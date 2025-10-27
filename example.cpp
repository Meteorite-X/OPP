_2D o;
Square s;
Circle c;
Triangle t;
    o = s; o = c; o = t
_2D *p[10];
for(int i = 0; i < 10; i++) {
    if(i % 3 == 0) p[i] = new Circle(rand());
    if(i % 3 == 1) p[i] = new Square(rand());
    if(i % 3 == 2) p[i] = new Triangle(rand());
}
    for(int i = 0; i < 10; i++) {
        for(int j =i; j < 10; j++) {
            if(p[j]->area() > p[j + 1]->area()) {
                _2D *tmp;
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
