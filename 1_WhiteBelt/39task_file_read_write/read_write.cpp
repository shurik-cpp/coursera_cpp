#include <iostream>
#include <fstream>

using namespace std;

int main(){
  string path = "D:/DrunkDistiller/myCodes/_myProgramsCpp/Coursera/39task_file_read_write/";
  //string path = "";
  string file_name_read = "input.txt";
  string file_name_write = "output.txt";

  ifstream input(path + file_name_read);
  ofstream output(path + file_name_write);

  if (input){
    string line;
    while (getline(input, line)){
      output << line << endl;
    }
  }
  else {
    cout << "open error";
  }



  return 0;
}
