#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
  int num_rows_;
  int num_columns_;

  vector<vector<int>> elements_;

public:
  Matrix() {
    num_rows_ = 0;
    num_columns_ = 0;
  }

  Matrix(int num_rows, int num_columns) {
    Reset(num_rows, num_columns);
  }

  void Reset(int num_rows, int num_columns) {
    if (num_rows < 0) {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_columns < 0) {
      throw out_of_range("num_columns must be >= 0");
    }
    if (num_rows == 0 || num_columns == 0) {
      num_rows = num_columns = 0;
    }

    num_rows_ = num_rows;
    num_columns_ = num_columns;
    elements_.assign(num_rows, vector<int>(num_columns));
  }

  int& At(int row, int column) {
    return elements_.at(row).at(column);
  }

  int At(int row, int column) const {
    return elements_.at(row).at(column);
  }

  int GetNumRows() const {
    return num_rows_;
  }

  int GetNumColumns() const {
    return num_columns_;
  }
};

bool operator==(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    return false;
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    return false;
  }

  for (int row = 0; row < one.GetNumRows(); ++row) {
    for (int column = 0; column < one.GetNumColumns(); ++column) {
      if (one.At(row, column) != two.At(row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(one.GetNumRows(), one.GetNumColumns());
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
  for (int row = 0; row < matrix.GetNumRows(); ++row) {
    for (int column = 0; column < matrix.GetNumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << endl;
  }

  return out;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}

// почти мой код:
/*
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
  int num_rows_;
  int num_columns_;

  vector<vector<int>> matrix2D; // первый вектор - строки, вложенный вектор - столбцы матрицы

public:
  // Если количество строк или количество столбцов, переданное
  // в конструктор класса Matrix или метод Reset, оказалось отрицательным,
  // то должно быть выброшено стандартное исключение out_of_range.
  // Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
  Matrix() {
    num_rows_ = 0;
    num_columns_ = 0;
  }

  // следующий конструктор задает количество строк и столбцов матрицы соответственно
  Matrix(const int& rows, const int& col) {
    Reset(rows, col);
  }

  // метод Reset меняет размеры матрицы на заданные и обнуляет все её элементы
  void Reset(int new_rows, int new_columns) {
    if (new_rows >= 0 && new_columns >= 0) {
      if (new_rows == 0 || new_rows == 0) {
        new_rows = new_columns = 0;
      }
      num_rows_ = new_rows;
      num_columns_ = new_columns;
      matrix2D.assign(new_rows, vector<int> (new_columns, 0)); // изменение размера вектора
    }
    else {
      // бросаем исключение в случае отрицательных значений
      throw out_of_range("");
    }
  }

  // константный метод At, который принимает номер строки и номер столбца
  // (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и
  // возвращает значение в соответствущей ячейке матрицы
  int At(const int& row, const int& column) const {
    if (row >= 0 && column >= 0) {
      if (matrix2D.size() == 0 || matrix2D[0].size()) return 0;

      unsigned int r = row, c = column;
      if (r <= matrix2D.size() && c <= matrix2D[row].size()) {
        return matrix2D[row][column];
      }
      else {
        // бросаем исключение в случае выхода за пределы матрицы
        throw out_of_range("");
      }
    }
    else {
      // бросаем исключение в случае выхода за пределы матрицы
      throw out_of_range("");
    }
    return matrix2D.at(row).at(column);
  }

  // неконстантный метод At с такими же параметрами, но
  // возвращающий ссылку на значение в соответствущей ячейке матрицы
  int& At(const int& row, const int& column) {

    if (row >= 0 && column >= 0) {
      if (matrix2D.size() == 0 || matrix2D[0].size()) return 0;

    unsigned int r = row, c = column;
    if (r <= matrix2D.size() && c <= matrix2D[row].size()) {
      return matrix2D[row][column];
    }
    else {
      // бросаем исключение в случае выхода за пределы матрицы
      throw out_of_range("");
    }
  }
  else {
    // бросаем исключение в случае выхода за пределы матрицы
    throw out_of_range("");
  }
    return matrix2D.at(row).at(column);
  }

  // константный метод GetNumRows возвращает количество строк матрицы
  int GetNumRows() const {
    return num_rows_;
  }

  // константный метод GetNumColumns возвращают количество столбцов матрицы
  int GetNumColumns() const {
    return num_columns_;
  }
};

// оператор ввода из потока istream;
// формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке),
// а затем все элементы матрицы: сначала элемент первой строки и первого столбца,
// затем элемент первой строки и второго столбца и так далее
istream& operator>>(istream& stream, Matrix& m) {
  int num_row, num_column;
  stream >> num_row >> num_column;

  if (num_row >= 0 && num_column >= 0) {
    // создадим матрицу с num_row - строк и num_column - столбцов
    vector<vector<int>> newMatrix(num_row, vector<int> (num_column));
    if (num_row > 0) {
      for (int i = 0; i < num_row; ++i) {
        if (num_column > 0) {
          for (int j = 0; j < num_column; ++j) {
            cin >> value;
            newMatrix[i][j] = value;
          }
        }
      }
    }
    m.FillMatix(newMatrix);
  }
  else {
    // бросаем исключение в случае отрицательных значений
    throw out_of_range("");
  }
  m.Reset(num_row, num_column);
  for (int row = 0; row < num_row; ++row) {
    for (int column = 0; column < num_column; ++column) {
      stream >> m.At(row, column);
    }
  }
  return stream;
}

// оператор вывода в поток ostream;
// он должен выводить матрицу в том же формате, в каком её читает оператор ввода, —
// в первой строке количество строк и столбцов,
// во второй — элементы первой строки,
// в третьей — элементы второй строки и т.д.
ostream& operator<<(ostream& stream, const Matrix& m) {
  stream << m.GetNumRows() << ' ' << m.GetNumColumns() << endl;
  for (int i = 0; i < m.GetNumRows(); ++i) {
    for (int j = 0; j < m.GetNumColumns(); ++j) {
      stream << m.At(i, j) << ' ';
    }
    stream << endl;
  }
  return stream;
}

// сравним размеры матриц
bool CompareSizeMatrix(const Matrix& m1, const Matrix& m2) {
  if (m1.GetNumRows() == m2.GetNumRows() &&
      m1.GetNumColumns() == m2.GetNumColumns()) {
    return true;
  }
  return false;
}

// оператор проверки на равенство (==):
// он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер
// и все их соответствующие элементы равны между собой,
// в противном случае он должен возвращать false.
bool operator==(const Matrix& m1, const Matrix& m2) {
  bool flag = true;
  if (CompareSizeMatrix(m1, m2)) {
    for (int i = 0; i < m1.GetNumRows(); ++i) {
      for (int j = 0; j < m1.GetNumColumns(); ++j) {
        if (m1.At(i, j) != m2.At(i, j)) flag = false;
      }
    }
    return flag;
  }
  return false;
}

// оператор сложения: он должен принимать две матрицы и возвращать новую матрицу,
// которая является их суммой;
// если переданные матрицы имеют разные размеры этот оператор должен
// выбрасывать стандартное исключение invalid_argument.
Matrix operator+(const Matrix& m1, const Matrix& m2) {
  if (m1.GetNumRows() != m2.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (m1.GetNumColumns() != m2.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix sum(m1.GetNumRows(), m1.GetNumColumns());
    for (int i = 0; i < m1.GetNumRows(); ++i) {
      for (int j = 0; j < m1.GetNumColumns(); ++j) {
        sum.At(i, j) = m1.At(i, j) + m2.At(i, j);
      }
    }

  return sum;
}

int main() {
  Matrix one;
  Matrix two;

  try {
    cin >> one;// >> two;
    cout << one << endl;// + two << endl;
    cin >> two;
    bool eqTest = (one == two);
    cout << "equality test: " << eqTest << endl;
    cout << "sum = " << one + two << endl;

  }
  catch (out_of_range& ex) {
    cout << "out of range" << endl;
  }
  catch (invalid_argument& ex) {
    cout << "invalid argument" << endl;
  }

  return 0;
}*/
