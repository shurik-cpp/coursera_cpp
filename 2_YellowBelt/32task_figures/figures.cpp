#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

// базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
class Figure {
public:
  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;
};

// классы Triangle, Rect и Circle,
// которые являются наследниками класса Figure и переопределяют его виртуальные методы;
class Triangle : public Figure {
public:
  Triangle(const string& name,
           const int a,
           const int b,
           const int c)
      : _name(name), _a(a), _b(b), _c(c) {}

  string Name() const override {
    return _name;
  }
  double Perimeter() const override {
    return _a + _b + _c;
  }
  double Area() const override {
    double p = Perimeter() / 2;
    return sqrt(p * (p - _a) * (p - _b) * (p - _c));
  }

private:
  const string _name;
  const int _a, _b, _c;
};

class Rect : public Figure {
public:
  Rect(const string& name,
       const int a,
       const int b)
      : _name(name), _a(a), _b(b) {}
  string Name() const override {
    return _name;
  }
  double Perimeter() const override {
    return (_a + _b) * 2;
  }
  double Area() const override {
    return _a * _b;
  }

private:
  const string _name;
  int _a, _b;
};

class Circle : public Figure {
public:
  Circle(const string& name,
         const int& r)
      : _name(name), _r(r) {}

  string Name() const override {
    return _name;
  }
  double Perimeter() const override {
    return 2 * _pi * _r;
  }
  double Area() const override {
    return _pi * _r * _r;
  }

private:
  const string _name;
  const int _r;
  const double _pi = 3.14;
};

// функцию CreateFigure, которая в зависимости от содержимого входного потока
// создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.
shared_ptr<Figure> CreateFigure(istringstream& stream) {
  shared_ptr<Figure> f;
  string name;
  int a, b, c;
  stream >> name;

  if (name == "TRIANGLE") {
    stream >> a >> b >> c;
    f = make_shared<Triangle>(name, a, b, c);
  } else if (name == "RECT") {
    stream >> a >> b;
    f = make_shared<Rect>(name, a, b);
  } else if (name == "CIRCLE") {
    stream >> a;
    f = make_shared<Circle>(name, a);
  }

  return f;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
