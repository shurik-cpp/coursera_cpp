#include <iostream>
#include <cstdint>
#include <limits>
#include <fstream>
#include <iomanip>

using namespace std;


int main() {
  string path = "D:/DrunkDistiller/myCodes/_myProgramsCpp/types_size.txt";

  ofstream output(path);

  output << sizeof(char) << " byte:   "
       << "   char: " << numeric_limits<char>::min() << " - " << numeric_limits<char>::max() << endl
       << endl
       << sizeof(int16_t) << " bytes:  "
       << "int16_t: " << numeric_limits<int16_t>::min() << " - " << numeric_limits<int16_t>::max() << endl
       << "         "
       << "uint16_t:      " << numeric_limits<uint16_t>::min() << " - " << numeric_limits<uint16_t>::max() << endl
       << endl
       << sizeof(int32_t) << " bytes:  "
       << "int32_t: " << numeric_limits<int32_t>::min() << " - " << numeric_limits<int32_t>::max() << endl
       << "         "
       << "uint32_t:           " << numeric_limits<uint32_t>::min() << " - " << numeric_limits<uint32_t>::max() << endl
       << endl
       << sizeof(int64_t) << " bytes:  "
       << "int64_t: " << numeric_limits<int64_t>::min() << " - " << numeric_limits<int64_t>::max() << endl
       << "         "
       << "uint64_t:                    " << numeric_limits<uint64_t>::min() << " - " << numeric_limits<uint64_t>::max() << endl
       << endl
       << endl;


  //cout << fixed;
  output << sizeof(float) << " bytes:  "
       << "  float: " << numeric_limits<float>::min() << " - " << numeric_limits<float>::max() << endl
       << sizeof(double) << " bytes:  "
       << " double: " << numeric_limits<double>::min() << " - " << numeric_limits<double>::max() << endl;

  cout << path << " - refreshed" << endl;

  return 0;
}
