#include <iostream>

using namespace std;

class Animal {
public:
  Animal(const string& n) : Name(n) {
    //cout << "+ Animal with name: " << Name << endl;
  }

  ~Animal() {
    //cout << "- Animal" << endl;
  }

  const string Name;
};


class Dog : public Animal { // Класс Dog должен являться наследником класса Animal
public:
  Dog(const string& n) : Animal(n) { //Конструктор класса Dog должен принимать параметр типа string и инициализировать им поле Name в классе Animal.
    //cout << "+ Dog with name: " << n << endl;
  }

  ~Dog() {
    //cout << "- Dog" << endl;
  }

  void Bark() {
    cout << Name << " barks: woof!" << endl;
  }

};

int main () {
  Dog dog("Jack");
  return 0;
}
