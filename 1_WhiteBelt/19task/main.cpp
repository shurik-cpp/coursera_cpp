/* У каждого из нас есть повторяющиеся ежемесячные дела,
 * каждое из которых нужно выполнять в конкретный день каждого месяца:
 * оплата счетов за электричество, абонентская плата за связь и пр.
 * Вам нужно реализовать работу со списком таких дел на месяц, а именно,
 * реализовать набор следующих операций:
 *
 * ADD i s     Назначить дело с названием s на день i текущего месяца.
 *
 * DUMP i      Вывести все дела, запланированные на день i текущего месяца.
 *
 * NEXT        Перейти к списку дел на новый месяц. При выполнении данной команды вместо текущего (старого)
 *             списка дел на текущий месяц создаётся и становится активным (новый)
 *             список дел на следующий месяц: все дела со старого списка дел копируются в новый список.
 *             После выполнения данной команды новый список дел и следующий месяц становятся текущими,
 *             а работа со старым списком дел прекращается.
 *             При переходе к новому месяцу необходимо обратить внимание на разное количество дней в месяцах:
 *                - если следующий месяц имеет больше дней, чем текущий,
 *                  «дополнительные» дни необходимо оставить пустыми (не содержащими дел);
 *                - если следующий месяц имеет меньше дней, чем текущий, дела со всех «лишних» дней
 *                  необходимо переместить на последний день следующего месяца.
 *
 * Замечания:
 * Историю списков дел хранить не требуется, работа ведется только с текущим списком дел текущего месяца.
 * Более того, при создании списка дел на следующий месяц, он «перетирает» предыдущий список.
 *
 * Обратите внимание, что количество команд NEXT в общей последовательности команд
 * при работе со списком дел может превышать 11.
 *
 * Начальным текущим месяцем считается январь.
 * Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
 *
 * Формат ввода:
 * Сначала число операций Q, затем описания операций.
 *
 * Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания.
 * Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.
 *
 * Формат вывода:
 * Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день,
 * а затем их названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.
 *
 * ====================================
 * Пример:
 * -------
 * Ввод
 * -------
 * 12
 * ADD 5 Salary
 * ADD 31 Walk
 * ADD 30 WalkPreparations
 * NEXT
 * DUMP 5
 * DUMP 28
 * NEXT
 * DUMP 31
 * DUMP 30
 * DUMP 28
 * ADD 28 Payment
 * DUMP 28
 * -------
 * Вывод
 * -------
 * 1 Salary
 * 2 WalkPreparations Walk
 * 0
 * 0
 * 2 WalkPreparations Walk
 * 3 WalkPreparations Walk Payment
 * ====================================
 *
 * Указание:
 * Для дописывания всех элементов вектора v2 в конец вектора v1 удобно использовать метод insert:
 * v1.insert(end(v1), begin(v2), end(v2));
 *
 * Кроме того, элементом вектора может быть любой тип, в том числе и другой вектор.
 * Например, vector<vector<int>> — это вектор, элементами которого являются вектора
 * целых чисел (то есть двумерный массив).
 *
 * Пример использования:
 * vector<vector<int>> m(10); // Создаём вектор из десяти векторов целых чисел
 * m[0].push_back(5);  // Добавляем элементы в первый вектор
 * m[0].push_back(15);
 * cout << m[0][1]; // Выведет 15 — второй элемент первого вектора
 *
 * m[1].push_back(3);
 * for (int x : m[1]) {
 *     // Перебираем все элементы второго
 * }
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

  vector<vector<string>> tasksOfMonth(31); //создадим вектор векторов заданий первого месяца (январь) с 31 днем
  int counterMonth = 1;
  bool longMonth = true; // true - когда в месяце 31 день
  int Q;
  cin >> Q;

  for (int i = 0; i < Q; ++i) {
    string command, task;
    int day;
    cin >> command;
    if (command == "ADD") {
      cin >> day >> task;
      tasksOfMonth[day -1].push_back(task);
    }
    else if (command == "DUMP") {
      cin >> day;
      cout << tasksOfMonth[day -1].size(); // выводим, сколько заданий на этот день
      for (const auto& t : tasksOfMonth[day -1]) {
        cout << " " << t;
      }
      cout << endl;
    }
    else if (command == "NEXT") {
      if (counterMonth != 7 && counterMonth != 12) longMonth = !longMonth;

      if (counterMonth == 12) counterMonth = 1;
      else ++counterMonth;
      //cout << "counterMonth = " << counterMonth << endl << "longMonth = " << longMonth << endl;

      if (longMonth) {
        tasksOfMonth.resize(31);
        //cout << "tasksOfMonth.size(" << tasksOfMonth.size() << ')' << endl;
      }
      else {
        if (counterMonth == 2) { // проверка на февраль
          for (int t = 28; t <= 30; ++t) {
            for (auto s : tasksOfMonth[t]) {
              tasksOfMonth[27].push_back(s);
            }
          }
          tasksOfMonth.resize(28); // меняем размер оригинального вектора
          //cout << "tasksOfMonth.size(" << tasksOfMonth.size() << ')' << endl;
        }
        else {
          for (auto s : tasksOfMonth[30]) {
            tasksOfMonth[29].push_back(s);
          }
          tasksOfMonth.resize(30); // меняем размер оригинального вектора
          //cout << "tasksOfMonth.size(" << tasksOfMonth.size() << ')' << endl;
        }
      }
    }
  }

  return 0;
}

/*
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// глобальные (доступные во всей программе) константы
// часто принято называть ЗАГЛАВНЫМИ_БУКВАМИ
const vector<int> MONTH_LENGTHS =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int main() {
  int q;
  cin >> q;

  // номер текущего месяца (от 0 до 11)
  int month = 0;

  // внешний вектор должен иметь длину, равную количеству дней в первом месяце;
  // все внутренние векторы по умолчанию пусты, потому что дел изначально нет
  vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "ADD") {

      int day;
      string concern;
      cin >> day >> concern;
      --day;  // элементы вектора нумеруются с нуля
      days_concerns[day].push_back(concern);

    } else if (operation_code == "NEXT") {

      // перед переходом к следующему месяцу запомним длину предыдущего
      // обьявляем эту переменную константной, потому что менять её не планируем
      const int old_month_length = MONTH_LENGTHS[month];

      // номер месяца должен увеличиться на 1, но после декабря идёт январь:
      // например, (5 + 1) % 12 = 6, но (11 + 1) % 12 = 0
      month = (month + 1) % MONTH_COUNT;

      const int new_month_length = MONTH_LENGTHS[month];

      // если новый месяц больше предыдущего, достаточно сделать resize;
      // иначе перед resize надо переместить дела с «лишних» последних дней
      if (new_month_length < old_month_length) {

        // далее понадобится добавлять новые дела в последний день нового месяца
        // чтобы не писать несколько раз days_concerns[new_month_length - 1],
        // создадим ссылку с более коротким названием для этого вектора
        vector<string>& last_day_concerns = days_concerns[new_month_length - 1];

        // перебираем все «лишние» дни в конце месяца
        for (int day = new_month_length; day < old_month_length; ++day) {
          // копируем вектор days_concerns[day]
          // в конец вектора last_day_concerns
          last_day_concerns.insert(
              end(last_day_concerns),
              begin(days_concerns[day]), end(days_concerns[day]));
        }
      }
      days_concerns.resize(new_month_length);

    } else if (operation_code == "DUMP") {

      int day;
      cin >> day;
      --day;

      // выводим список дел в конкретный день в нужном формате
      cout << days_concerns[day].size() << " ";
      for (const string& concern : days_concerns[day]) {
        cout << concern << " ";
      }
      cout << endl;

    }
  }

  return 0;
}
*/
