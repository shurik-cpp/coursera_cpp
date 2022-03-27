#include <iostream>
#include <vector>

using namespace std;
void BadRequest(){
  cout << "bad request" << endl;
}

int main(){
  struct Student{
    string first_name;
    string last_name;
    int day_birth;
    int month_birth;
    int year_birth;
  };

  vector<Student> students;
  // занимаем нулевую ячейку вектора пустым студентом, т.к нумерация их будет от 1
  Student reserved_cell;
  students.push_back(reserved_cell);

  int q;
  //while (true) {
    cin >> q; // количество запросов добавления студента
    if (q < 0 || q > 10000){
      BadRequest();
      return -1;
    }
    //else break;
  //}

  for (int i = 0; i < q; ++i){
    Student student;
    cin >> student.first_name >> student.last_name
        >> student.day_birth >> student.month_birth >> student.year_birth;

    if (student.first_name.length() < 1 || student.first_name.length() > 15 ||
        student.last_name.length() < 1 || student.last_name.length() > 15 ||
        student.day_birth < 0 || student.day_birth > 1000000000 ||
        student.month_birth < 0 || student.month_birth > 1000000000 ||
        student.year_birth < 0 || student.year_birth > 1000000000) {

      BadRequest();
    }
    else students.push_back(student);
  }

  cin >> q; // количество запросов на вывод информации о студенте
  if (q < 0 || q > 10000) {
    BadRequest();
    return -1;
  }

  for (int i = 0; i < q; ++i){
    string command;
    unsigned long student_number;
    cin >> command >> student_number;

    if (command.length() < 1 || command.length() > 15 ||
        student_number < 1 || student_number > 1000000000 ||
        student_number > students.size() - 1){

      BadRequest();
    }
    else {
      if (command == "name"){
        cout << students[student_number].first_name << ' ' << students[student_number].last_name << endl;
      }
      else if (command == "date") {
        cout << students[student_number].day_birth << '.' << students[student_number].month_birth
             << '.' << students[student_number].year_birth << endl;
      }
      else BadRequest();
    }
  }
  return 0;
}

/*
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
  string first_name;
  string last_name;

  int day;
  int month;
  int year;
};

int main() {
  int n;
  cin >> n;

  string first_name, last_name;
  int day, month, year;
  vector<Student> students;

  for (size_t i = 0; i < n; ++i) {
    cin >> first_name >> last_name >> day >> month >> year;

    students.push_back(Student{
        first_name,
        last_name,
        day,
        month,
        year
    });
  }

  int m;
  cin >> m;
  string query;
  int student_number;

  for (int i = 0; i < m; ++i) {
    cin >> query >> student_number;
    --student_number;

    if (query == "name" && student_number >= 0 && student_number < n) {
      cout << students[student_number].first_name << " "
           << students[student_number].last_name << endl;
    } else if (query == "date" && student_number >= 0 && student_number < n) {
      cout << students[student_number].day << "."
           << students[student_number].month << "."
           << students[student_number].year << endl;
    } else {
      cout << "bad request" << endl;
    }
  }

  return 0;
}


*/
