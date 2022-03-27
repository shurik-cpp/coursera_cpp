#include <iostream>

using namespace std;

struct Specialization {
  explicit Specialization(string new_value){
    value = new_value;
  }
  string value;
};
struct Course {
  explicit Course(string new_value){
    value = new_value;
  }
  string value;
};
struct Week {
  explicit Week(string new_value){
    value = new_value;
  }
  string value;
};

struct LectureTitle {
  LectureTitle(Specialization new_specialization, Course new_course, Week new_week){
    specialization = new_specialization.value;
    course = new_course.value;
    week = new_week.value;
  }

  string specialization;
  string course;
  string week;
};

int main(){
//  LectureTitle lecture_title = {Specialization("C++"), Course("White belt"), Week("4th")};
//  cout << lecture_title.specialization << ", " << lecture_title.course << ", "
//       << lecture_title.week << '\n';

  return 0;
}
