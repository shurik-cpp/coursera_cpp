#include "test_runner.h"
#include <vector>

using namespace std;


// У класса должен быть шаблонный параметр T — тип элемента в ячейке
template<typename T>
// Класс должен называться Table
class Table {
private:
  size_t _line, _column;
  vector<vector<T>> _table;  // first-line, second-column

public:
  // У класса должен быть конструктор, получающий на входе два числа
  // типа size_t — количество строк и столбцов соответственно.
  Table(size_t line, size_t column) {
    Table::Resize(line, column);
  }

  // У класса должна быть константная функция Size, возвращающая
  // pair<size_t, size_t> — размер таблицы
  // (в том же порядке, в котором эти аргументы передавались в конструктор).
  // При этом, если у таблицы Table один из размеров нулевой,
  // то необходимо считать таковым и второй размер таблицы.
  pair<size_t, size_t> Size() const {
    return make_pair(_line, _column);
  }

  // У класса должна быть функция Resize, получающая на вход два параметра типа size_t
  // и меняющая размер таблицы. Старые данные, умещающиеся в новый размер,
  // должны при этом сохраниться.
  void Resize(size_t line, size_t column) {
    if (line == 0 || column == 0) {
      _line = 0;
      _column = 0;
    } else {
      _column = column;
      _line = line;
    }
    // изменяем количество горизонтальных элементов (строк)
    _table.resize(line);
    // изменяем в каждом горизонтальном количество вертикальных элементов (столбцов)
    for (auto& it : _table) {
      it.resize(column);
    }
  }

  // У класса должны быть константная и неконстантная версии оператора [],
  // возвращающего нечто такое, к чему снова можно было бы применить оператор [].
  // То есть, должны работать конструкции вида cout << table[i][j];и table[i][j] = value;.
  // Проверять корректность индексов при этом не нужно.
  vector<T>& operator [](size_t index) {
    return _table[index];
  }
  const vector<T>& operator [](size_t index) const {
    return _table[index];
  }

};



void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
