#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream)
      : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }

  void SetFile(const string& file) { _file = file; }
  void SetLine(int line) { _line = line; }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
  string _file;
  int _line;
};


void Logger::Log(const string& message) {
  if (log_file && log_line) {
    os << _file << ":" << _line << " ";
  }
  else if (log_file) {
    os << _file << " ";
  }
  else if (!log_line) {
    os << "Line " << _line << ' ';
  }
  os << message << endl;
}

/* Параметры макроса LOG — объект класса Logger и строковое сообщение,
 * которое должно быть передано в метод Log.
 * В зависимости от настроек объекта класса Logger логируемое сообщение должно
 * предваряться именем файла или номером строки.
 * Смотрите юнит-тесты в заготовке решения для более подробного описания поведения.
 *
 * Реализуйте макрос LOG так, чтобы он добавлял в логируемое сообщение
 * имя файла и номер строки в зависимости от настроек объекта logger.
*/
// __FILE__ - возвращает string
// __LINE__ - возвращает int
#define LOG(logger, message)     \
  logger.SetFile(__FILE__);      \
  logger.SetLine(__LINE__);      \
  logger.Log(message);


void TestLog() {
  // Директива #line используется для изменения содержимого __LINE__  и __FILE__,
  // являющихся пред­определенными макросами.
  // #line число "имя_файла"
  #line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);

  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
