#include <string>
#include <vector>

using namespace std;

/* Разработать макрос UNIQ_ID, который будет формировать идентификатор,
 * уникальный в пределах данного cpp-файла.
 * Например, следующий код должен компилироваться и работать:
 * int UNIQ_ID = 5;
 * string UNIQ_ID = "hello!";
*/

#define STEP_ONE(name, line) STEP_TWO(name, line)
#define STEP_TWO(name,line) name##line

#define UNIQ_ID STEP_ONE(variable_, __LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};

  return 0;
}
