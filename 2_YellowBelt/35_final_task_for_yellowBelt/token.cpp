#include "token.h"

#include <stdexcept>

using namespace std;

vector<Token> Tokenize(istream& cl) {
  vector<Token> tokens;

  char c;
  while (cl >> c) {
    // Макрос isdigit() возвращает ненулевое значение, если аргумент ch является цифрой от 0 до 9,
    // в противном случае возвращается 0.
    // если встречаем цифру, собираем дату
    if (isdigit(c)) {
      string date(1, c); // string(size_t n, char c) - повторение символа c заданное число n раз.
      for (int i = 0; i < 3; ++i) { // разбирается дата и записывается в string date
        // istream::peek достает символ, а не число.
        while (isdigit(cl.peek())) {
          // фунция get(), извлекает символ из входного потока
          date += cl.get();
        }
        if (i < 2) {
          date += cl.get(); // добавляем '-'
        }
      }
      tokens.push_back({date, TokenType::DATE});
    }
    // если натфкаемся на кавычку ' " ', собираем событие
    else if (c == '"') {
      string event;
      getline(cl, event, '"');
      tokens.push_back({event, TokenType::EVENT});
    }
    // Find date или Del date
    else if (c == 'd') {
      if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') {
        tokens.push_back({"date", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // Find event или Del event
    else if (c == 'e') {
      if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
          cl.get() == 't') {
        tokens.push_back({"event", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // определяем логику AND
    else if (c == 'A') {
      if (cl.get() == 'N' && cl.get() == 'D') {
        tokens.push_back({"AND", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
    // определяем логику OR
    else if (c == 'O') {
      if (cl.get() == 'R') {
        tokens.push_back({"OR", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
    else if (c == '(') {
      tokens.push_back({"(", TokenType::PAREN_LEFT});
    }
    else if (c == ')') {
      tokens.push_back({")", TokenType::PAREN_RIGHT});
    }
    else if (c == '<') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({"<=", TokenType::COMPARE_OP});
      }
      else {
        tokens.push_back({"<", TokenType::COMPARE_OP});
      }
    }
    else if (c == '>') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({">=", TokenType::COMPARE_OP});
      }
      else {
        tokens.push_back({">", TokenType::COMPARE_OP});
      }
    }
    else if (c == '=') {
      if (cl.get() == '=') {
        tokens.push_back({"==", TokenType::COMPARE_OP});
      }
      else {
        throw logic_error("Unknown token");
      }
    }
    else if (c == '!') {
      if (cl.get() == '=') {
        tokens.push_back({"!=", TokenType::COMPARE_OP});
      }
      else {
        throw logic_error("Unknown token");
      }
    }
  }

  return tokens;
}
