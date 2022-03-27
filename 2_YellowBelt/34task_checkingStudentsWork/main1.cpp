#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person
{
public:
  Person(string name, string profession) :
                _name(name), _profession(profession) {};
  virtual void Walk(string destination) const
    {
    cout << _profession << ": " << _name << " walks to: " << destination << endl;
  }
  const string _name;
  const string _profession;
};

class Student : public Person
{
  const string _favourite_song;
public:
  Student(string name, string favourite_song) :
                                                Person(name, "Student"), _favourite_song(favourite_song) {}

  void Learn() const
  {
    cout << "Student: " << _name << " learns" << endl;
  }

  void SingSong() const
  {
    cout << "Student: " << _name << " sings a song: " << _favourite_song << endl;
  }

  void Walk(string destination) const override
  {
    Person::Walk(destination);
    SingSong();
  }
};

class Teacher : public Person
{
  const string _subject;
public:
  Teacher(string name, string subject) :
            Person(name, "Teacher"), _subject(subject) {}

  void Teach() const
    {
    cout << "Teacher: " << _name << " teaches: " << _subject << endl;
  }
};

class Policeman : public Person
{
public:
  Policeman(string name) : Person(name, "Policeman") {}

  void Check(const Person &p) const
    {
    cout << "Policeman: " << _name << " checks " << p._profession << ". "
                    << p._profession << "'s name is: " << p._name << endl;
  }
};

void VisitPlaces(const Person &person, vector<string> places)
{
  for(auto p : places)
  {
    person.Walk(p);
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
