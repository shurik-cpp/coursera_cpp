#include "student.h"
//#include "test_runner.h"
//#include "profile.h"

#include <algorithm>

using namespace std;


// Для сортировки студентов по рейтингу используется функция сравнения,
// возвращающая true, если рейтинг студента first выше рейтинга студента second.
// Было выявлено, что эта функция является узким местом процесса сортировки,
// и именно её нужно оптимизировать.
//
// Пришлите на проверку файл, содержащий оптимизированную версию функции Compare.
// Если ваша реализация будет недостаточно эффективной, то решение не уложится в ограничение по времени.
inline bool Compare(const Student& first, const Student& second) {
  return first.rating > second.rating; // first.Less(second);
}



//void TestComparison() {
//  Student newbie {
//      "Ivan", "Ivanov", {{"c++", 1.0}, {"algorithms", 3.0}}, 2.0
//  };

//  Student cpp_expert {
//      "Petr", "Petrov", {{"c++", 9.5}, {"algorithms", 6.0}}, 7.75
//  };

//  Student guru {
//      "Sidor", "Sidorov", {{"c++", 10.0}, {"algorithms", 10.0}}, 10.0
//  };

//  ASSERT(Compare(guru, newbie));
//  ASSERT(Compare(guru, cpp_expert));
//  ASSERT(!Compare(newbie, cpp_expert));
//}

//void TestSorting() {
//  set<Student> students {
//      {"Sidor", "Sidorov", {{"maths", 2.}}, 2.7},
//      {"Semen", "Semenov", {{"maths", 4.}}, 4.3},
//      {"Ivan", "Ivanov", {{"maths", 5.}}, 5.1},
//      {"Petr", "Petrov", {{"maths", 3.}}, 3.2},
//      {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.6}
//  };
//  //sort(students.begin(), students.end(), Compare);
//  ASSERT(is_sorted(students.begin(), students.end(),
//                   [](const Student& first, const Student& second) {
//                     return  first < second;
//                   })
//         );
//  //------------------------
//  for (const auto& it : students) {
//    cout << it << endl;
//  }
//  //------------------------
//}

//int main() {
//  TestRunner tr;
//  {
//    LOG_DURATION("TestComparison");
//    RUN_TEST(tr, TestComparison);
//  }
//  {
//    LOG_DURATION("TestSorting");
//    RUN_TEST(tr, TestSorting);
//  }
//  return 0;
//}
