#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
  //string path = "D:/DrunkDistiller/myCodes/_myProgramsCpp/Coursera/40task_cout_accuracy/";
  string path = "";
  string file_name_read = "input.txt";
  //string file_name_write = "output.txt";

  ifstream input(path + file_name_read);
  //ofstream output(path + file_name_write);

  double number = 0;

  cout << fixed << setprecision(3);

  if (input){
    while (input >> number) {
      cout << number << '\n';
    }

  }
  else cout << "read error!";
  return 0;
}
