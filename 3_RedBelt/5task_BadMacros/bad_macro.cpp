#include "test_runner.h"

#include <ostream>
using namespace std;

/* Вам дан макрос, который распечатывает два переданных ему значения в переданный поток вывода.
 * В реализации макроса есть недостаток, ограничивающий его применимость в реальных программах.
 * Вам требуется найти и устранить недостаток.
 *
 * #define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl
*/

// применим однопроходный цикл do-while(0), для возможности использования макроса
// в конструкциях if-else и циклах с одним вызовом макроса без {}
// https://www.iar.com/knowledge/learn/programming/advanced-preprocessor-tips-and-tricks
#define PRINT_VALUES(out, x, y) \
do {                            \
  out << (x) << endl;           \
  out << (y) << endl;           \
} while(0)

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
//    cout << output.str() << endl;
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");

}
