#include <iostream>
#include <tuple>
#include <map>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
private:
  map<string, TasksInfo> personsTask; // имя разработчика, данные о его текущих заданиях

  void EraseZeroes(TasksInfo& task_info) {
    if (task_info[TaskStatus::NEW] == 0) task_info.erase(TaskStatus::NEW);
    if (task_info[TaskStatus::IN_PROGRESS] == 0) task_info.erase(TaskStatus::IN_PROGRESS);
    if (task_info[TaskStatus::TESTING] == 0) task_info.erase(TaskStatus::TESTING);
    if (task_info[TaskStatus::DONE] == 0) task_info.erase(TaskStatus::DONE);
  }

public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return personsTask.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
    TasksInfo task_info_by_person;

    if (personsTask.count(person)) { // если такой разработчик существует
      task_info_by_person = personsTask[person]; // берем его задания
    }

    ++task_info_by_person[TaskStatus::NEW]; // добавляем одно новое задание
    personsTask[person] = task_info_by_person; // сохраняем

    // решение в одну строчку:
    // ++personsTask[person][TaskStatus::NEW];
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  /* Метод PerformPersonTasks должен реализовывать следующий алгоритм:
   *
   * 1. Рассмотрим все невыполненные задачи разработчика person.
   * 2. Упорядочим их по статусам: сначала все задачи в статусе NEW,
   *    затем все задачи в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
   * 3. Рассмотрим первые task_count задач и переведём каждую из них
   *    в следующий статус в соответствии с естественным порядком:
   *    NEW → IN_PROGRESS → TESTING → DONE.
   * 4. Вернём кортеж из двух элементов:
   *    информацию о статусах обновившихся задач (включая те, которые оказались в статусе DONE)
   *    и информацию о статусах остальных не выполненных задач.
   *
   * В случае отсутствия разработчика с именем person
   * метод PerformPersonTasks должен вернуть кортеж из двух пустых TasksInfo
   *
   * Если task_count превышает текущее количество невыполненных задач разработчика,
   * достаточно считать, что task_count равен количеству невыполненных задач:
   * дважды обновлять статус какой-либо задачи в этом случае не нужно.
  */
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
    TasksInfo updated, other; // создадим два словаря: обновленные задачи и остальные

    if (personsTask.count(person)) {
      other = personsTask[person];
      TasksInfo& currentPerson = personsTask[person];
      while (task_count > 0) {
        if (currentPerson[TaskStatus::NEW] > 0) {
          --currentPerson[TaskStatus::NEW];
          ++currentPerson[TaskStatus::IN_PROGRESS];
          ++updated[TaskStatus::IN_PROGRESS];
          --other[TaskStatus::NEW];
        }
        else if (currentPerson[TaskStatus::IN_PROGRESS] > 0) {
          --currentPerson[TaskStatus::IN_PROGRESS];
          ++currentPerson[TaskStatus::TESTING];
          ++updated[TaskStatus::TESTING];
          --other[TaskStatus::IN_PROGRESS];
        }
        else if (currentPerson[TaskStatus::TESTING] > 0) {
          --currentPerson[TaskStatus::TESTING];
          ++currentPerson[TaskStatus::DONE];
          ++updated[TaskStatus::DONE];
          --other[TaskStatus::TESTING];
        }
        else if (currentPerson[TaskStatus::DONE] > 0) {
          --currentPerson[TaskStatus::DONE];
          --other[TaskStatus::DONE];
        }
        --task_count;
      }

      // подчищаем нули
      EraseZeroes(currentPerson);
      EraseZeroes(other);
      // исключаем выполненные
      other.erase(TaskStatus::DONE);
      // сохраняем
      // personsTask[person] = currentPerson;
      // закоментировал, т.к. currentPerson - обращается к personsTask[person] по ссылке: TasksInfo& currentPerson = personsTask[person];
    }
    else personsTask.erase(person);

    return make_tuple(updated, other);
  }

};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
