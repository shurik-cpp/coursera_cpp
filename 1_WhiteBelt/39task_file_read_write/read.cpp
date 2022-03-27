#include <iostream>
#include <fstream>

using namespace std;

int main(){
  //string path = "D:/DrunkDistiller/myCodes/_myProgramsCpp/Coursera/39task_file_read_write/input.txt";
  string path = "input.txt";
  ifstream input(path);

  if (input){
    string line;
    while (getline(input, line)){
      cout << line << endl;
    }
  }
  else {
    cout << "open error";
  }

  return 0;
}
