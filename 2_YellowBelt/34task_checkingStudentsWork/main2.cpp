#include <iostream>
#include <string>
#include <vector>
using namespace std;



class Person {
public:
  Person(const string& name, const string& occupation)
      :name(name)
        , occupation(occupation)
  {}
  virtual string Name() const { return name;}
  virtual void Walk(const string& destination) const { cout << Occupation() << ": " << Name() << " walks to: " << destination << endl;};
  virtual string Occupation() const {return occupation; }
  virtual string OcupationAndName() const {
    return Occupation() + ": " + name;
  }

private:
  const string name;
  const string occupation;
};


class Student : public Person {
public:
  Student(const string& name, const string& song)
      : Person(name, "Student")
        , favorte_song(song)
  {}
  void Sing() const {
    cout << this->OcupationAndName() << " sings a song " << favorte_song << endl;
  }
  void Walk(const string& destination) const override{
    Person::Walk(destination);
    Sing();
  }
private:
  const string favorte_song;
};

class Teacher : public Person {
public:
  Teacher( const string& name, const string& subject)
      : Person(name, "Teacher")
        , subject(subject)
  {}

  [[maybe_unused]] void Teach() const {
    cout << OcupationAndName() << " teaches: " << subject << endl;
  }

private:
  const string subject;
};

class Policeman : public Person {
public:
  Policeman(const string& name)
      : Person(name, "Policeman")
  {}

  void Check(const  Person& p) const {
    cout << OcupationAndName() << " checks " << p.Occupation() << ". " <<
        p.Occupation() << "'s name is: " << p.Name() << endl;
  }
};
void VisitPlaces(const Person& person, const vector<string>& places) {
  for(const auto& place: places) {
    person.Walk(place);
  }

}
int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});
  return 0;
}
