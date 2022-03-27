#include "phone_number.h"
#include <sstream>
#include <exception>


/* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument.
     Проверять, что номер содержит только цифры, не нужно.

Примеры:
    * +7-495-111-22-33
    * +7-495-1112233
    * +323-22-460002
    * +1-2-coursera-cpp
    * 1-2-333 - некорректный номер - не начинается на '+'
    * +7-1233 - некорректный номер - есть только код страны и города
    */
PhoneNumber::PhoneNumber(const std::string &international_number) {
  std::string error = "Wrong phone format: ";

  if (international_number[0] != '+' /* || international_number[1] == '+'*/ ) {
    throw std::invalid_argument(error + international_number);
  }
  else {
    std::stringstream stream(international_number); // создаем поток из строки s


    // парсим поток
    stream.ignore(1);
    if (getline(stream, country_code_,'-')) {}
    else throw std::invalid_argument(error + international_number);
    if (getline(stream, city_code_,'-')) {}
    else throw std::invalid_argument(error + international_number);
    if (getline(stream, local_number_,'\n')) {}
    else throw std::invalid_argument(error + international_number);

    if (country_code_.empty()) {
      throw std::runtime_error("country code is invalid! " + country_code_);
    }
    else if (city_code_.empty()) {
      throw std::runtime_error("city code is empty! " + city_code_);
    }
    else if (local_number_.empty()) {
      throw std::runtime_error("local number is empty! " + local_number_);
    }
  }
}

std::string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

std::string PhoneNumber::GetCityCode() const {
  return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
  return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}
