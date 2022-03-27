#include <iostream>


using namespace std;

string AskTimeServer(){
  //throw runtime_error("Other error");
  throw system_error(error_code());
  return "14:52:43";
}

class TimeServer {
public:
  string GetCurrentTime(){
    try {
      last_fetched_time = AskTimeServer();
    }
    catch (system_error& e){
      //return last_fetched_time;
    }
    return last_fetched_time;
  }

private:
  string last_fetched_time = "00:00:00";
};

int main(){
  TimeServer ts;

  try {
    cout << ts.GetCurrentTime() << endl;
  }
  catch (exception& e) {
    cout << "Exception got: " << e.what() << endl;
  }

  return 0;
}


/*

#include <exception>
#include <system_error>

using namespace std;

class TimeServer {
public:
  string GetCurrentTime() {
    // поместим вызов функции AskTimeServer в try-catch блок
    try {
      last_fetched_time = AskTimeServer();
    } catch (const system_error&) {  // ловим только system_error
    }
    // возвращаем значение поля — либо обновлённое, либо нет
    return last_fetched_time;
  }

private:
  string last_fetched_time = "00:00:00";
};*/
