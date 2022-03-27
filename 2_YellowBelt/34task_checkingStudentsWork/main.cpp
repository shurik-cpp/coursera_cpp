#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Civilian {
public:
  const string& name;
public:
  explicit Civilian(const string &name) : name(name) {}

  virtual void Walk(const string &destination) const = 0;

  virtual string GetType() const = 0;

};

class Student : public Civilian {
public:
  Student(string name, string favouriteSong) : Civilian(name) {
    FavouriteSong = favouriteSong;
  }

  //////////////////////////////////////////////////////////////
  string GetType() const override { return "Student"; }

  void Walk(const string &destination) const override {
    cout << "Student: " << name << " walks to: " << destination << endl;
    cout << "Student: " << name << " sings a song: " << FavouriteSong << endl;
  }
  //////////////////////////////////////////////////////////////

  void Learn() {
    cout << "Student: " << name << " learns" << endl;
  }

  void SingSong() {
    cout << "Student: " << name << " sings a song: " << FavouriteSong << endl;
  }

public:
  string FavouriteSong;
};

class Teacher : public Civilian {
public:
  Teacher(string name, string subject) : Civilian(name) {Subject = subject;}

  ///////////////////////////////////////////////////////////////
  string GetType() const override { return "Teacher"; }

  void Walk(const string &destination) const override {
    cout << "Teacher: " << name << " walks to: " << destination << endl;
  }
  ///////////////////////////////////////////////////////////////

  void Teach() {
    cout << "Teacher: " << name << " teaches: " << Subject << endl;
  }

public:
  string Subject;
};

class Policeman : public Civilian {
public:
  Policeman(string name) : Civilian(name) {}

  /////////////////////////////////////////////////////////////////////
  string GetType() const override { return "Policeman"; }

  void Walk(const string &destination) const override {
    cout << "Policeman: " << name << " walks to: " << destination << endl;
  }
  ////////////////////////////////////////////////////////////////////
  void Check(Civilian &c) {
    cout << "Policeman: " << name << " checks " << c.GetType() << ". "
         << c.GetType() << "'s name is " << c.name << endl;
  }
};


void VisitPlaces(Civilian &t, vector<string> places) {
  for (auto p : places) {
    t.Walk(p);
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
