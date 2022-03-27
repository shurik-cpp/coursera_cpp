#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <utility>

#include "database.h" // DONE
#include "date.h"  // DONE
#include "node.h" // DONE
#include "condition_parser.h"
#include "test_runner.h"

using namespace std;

string ParseEvent(istream& is) {
  string result;
  while (is.peek() == ' ') {
    is.ignore(1);
  }
  getline(is, result);

  return result;
}

//void TestAll();

int main() {
//TestAll();

  Database db;

//  db.Add({1, 1, 1}, "event2");
//  db.Add({2, 2, 2}, "event1");

//  db.Add({3, 3, 3}, "event 3");
//  db.Add({3, 3, 3}, "event1");
//  db.Add({1, 1, 1}, "event 1");
//  db.Add({3, 3, 3}, "event2");

//  db.Add({3, 3, 3}, "event 6");
//  db.Add({3, 3, 3}, "event4");
//  db.Add({3, 3, 3}, "event 8");
//  db.Add({3, 3, 3}, "event5");

//  db.Add({3, 3, 3}, "event7");

//  db.Add({4, 4, 4}, "event1");
//  db.Add({4, 4, 4}, "event2");
//  db.Add({4, 4, 4}, "event 4");
//  db.Add({4, 4, 4}, "event3");

//  db.Add({2, 2, 2}, "event 2");


  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {  // DONE
      const auto date = ParseDate(is);   // const Date
      const auto event = ParseEvent(is); // const string
      db.Add(date, event);
    }
    else if (command == "Print") { // DONE
      db.Print(cout);
    }
    else if (command == "Find") {
      shared_ptr<Node> condition = ParseCondition(is);  // shared_ptr<Node> (условие)
      // мы ничего не кладем в переменную predicate.
      // мы объявляем лямбда-выражение с именем predicate,
      // которое принимает дату и событие,
      // захватывает condition и
      // возвращает condition->Evaluate(date, event);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      // entries - записи
      const vector<pair<Date, string>> entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    }
    else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    }

    else if (command == "Last") { // DONE
      try {
        cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
        cout << "No entries" << endl;
      }
    }
    else if (command.empty()) {
      continue;
    }
    else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

//void TestParseEvent() {
//  {
//    istringstream is("event--\n hello");
//    AssertEqual(ParseEvent(is), "event--", "Parse event without leading spaces");
//  }
//  {
//    istringstream is("   sport event ");
//    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
//  }
//  {
//    istringstream is("  first event  \n  second event");
//    vector<string> events;
//    events.push_back(ParseEvent(is));
//    events.push_back(ParseEvent(is));
//    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
//  }
//}


//void TestAll() {
//  TestRunner tr;
//  tr.RunTest(TestParseEvent, "TestParseEvent");
//  tr.RunTest(TestParseCondition, "TestParseCondition");
//}
