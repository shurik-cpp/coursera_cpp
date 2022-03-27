#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Humans {
public:
  Humans(const string& act)
      : _activity(act) {}

  virtual void Walk(const string& destination) const {
    cout << GetActivityAndName() << " walks to: " << destination << endl;
  }

  string GetActivity() const {
    return _activity;
  }

  string GetName() const {
    return _name;
  }

protected:
  string _activity;
  string _name;

  string GetActivityAndName() const {
    return _activity + ": " + _name;
  }
};

class Student : public Humans {
public:
  Student(const string& name, const string& favouriteSong)
      : Humans("Student") {
    _name = name;
    _favouriteSong = favouriteSong;
  }

  void Learn() const {
    cout << _activity << " " << _name << " learns" << endl;
  }

  void Walk(const string& destination) const override {
    Humans::Walk(destination);
    SingSong();
  }

  void SingSong() const {
    cout << GetActivityAndName() << " sings a song: " << _favouriteSong << endl;
  }

private:
  string _favouriteSong;
};

class Teacher : public Humans {
public:

  Teacher(const string& name, const string& subject)
      : Humans("Teacher") {
    _name = name;
    _subject = subject;
  }

  void Teach() const {
    cout << GetActivityAndName() << " teaches: " << _subject << endl;
  }

private:
  string _subject;
};


class Policeman : public Humans {
public:
  Policeman(const string& name)
      : Humans("Policeman") {
    _name = name;
  }

  void Check(const Humans& h) const {
    cout << GetActivityAndName() << " checks " << h.GetActivity() << ". " << h.GetActivity() << "'s name is: " << h.GetName() << endl;
  }

};

void VisitPlaces(const Humans& h, const vector<string>& places) {
  for (auto p : places) {
    h.Walk(p);
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
