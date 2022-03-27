#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(){
  //string path = "D:/DrunkDistiller/myCodes/_myProgramsCpp/Coursera/41task_table/";
  string path = "";
  string read_file_name = "input.txt";

  ifstream input(path + read_file_name);
  int lines, columns;


  if (input){
    input >> lines >> columns;
    //cout << lines << '|' << columns;
    for (int l = 0; l < lines; ++l){
      for (int c = 0; c < columns; ++c){
        int number;
        input >> number;
        input.ignore(1);
        cout << setfill(' ');
        cout << setw(10) << number;
        if (c != columns - 1) cout << ' ';
      }
      if (l != lines - 1) cout << endl;
    }
  }
  else cout << "read file error!";

  return 0;
}
