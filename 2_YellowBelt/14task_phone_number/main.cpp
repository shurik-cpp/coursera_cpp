#include <iostream>
#include "test_runner.h"
#include "phone_number.h"

using namespace std;

void Tests() {
  try {
    PhoneNumber phone1("+7-923-3004662");

    AssertEqual(phone1.GetCountryCode(), "7", "GetCountryCode()");
    AssertEqual(phone1.GetCityCode(), "923", "GetCityCode()");
    AssertEqual(phone1.GetLocalNumber(), "3004662", "GetLocalNumber()");
    AssertEqual(phone1.GetInternationalNumber(), "+7-923-3004662", "GetInternationalNumber()");
  }
  catch (const invalid_argument& ex) {
    cout << "exception: " << ex.what() << endl;
  }

}

int main() {
  TestRunner runner;
  runner.RunTest(Tests, "All tests");
  try {
    PhoneNumber phone("+7-923-3004662");
    cout << phone.GetCountryCode() << endl;
    cout << phone.GetCityCode() << endl;
    cout << phone.GetLocalNumber() << endl;
    cout << phone.GetInternationalNumber() << endl;
  }
  catch (const invalid_argument& ex) {
    cout << "exception: " << ex.what() << endl;
  }
  return 0;
}
