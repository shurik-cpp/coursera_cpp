#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
    Person(string profession, string name)
        : Name(name)
        , Profession(profession) {}
    const string Name;
    const string Profession;

    void virtual Walk(const string& destination) const {
        cout << Profession << ": " << Name << " walks to: " << destination << endl;
    }
};


class Student : public Person {
public:
    Student(string name, string favouriteSong) : Person("Student", name) {
        FavouriteSong = favouriteSong;
    }

    void Learn() {
        cout << Profession << ": " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Profession << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(string name, string subject) : Person("Teacher", name)  {
        Subject = subject;
    }

    void Teach() {
        cout << Profession << ": " << Name << " teaches: " << Subject << endl;
    }

public:
    string Subject;
};


class Policeman : public Person {
public:
    Policeman(string name) : Person("Policeman", name) {}

    void Check(const shared_ptr<Person>& p) {
        cout << Profession << ": " << Name << " checks "<< p->Profession << ". "
            << p->Profession << "'s name is: " << p->Name << endl;
    }
};


void VisitPlaces(const shared_ptr<Person>& person, vector<string> places) {
    for (const string& p : places) {
        person->Walk(p);
    }
}


int main() {
    shared_ptr<Teacher> t = make_shared<Teacher>("Jim", "Math");
    shared_ptr<Student> s = make_shared<Student>("Ann", "We will rock you");
    shared_ptr<Policeman> p = make_shared<Policeman>("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p->Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
