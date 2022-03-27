class FunctionPart {
public:
  FunctionPart(char new_operation, double new_value) {
    operation = new_operation;
    value = new_value;
  }
  // применяет эту операцию к какому-то введенному числу
  double Apply(double source_value) const {
    if (operation == '+') return source_value + value;
    else return source_value - value;
  }
  // инвертирует элементарные операции
  void Invert() {
    if (operation == '+') operation = '-';
    else operation = '+';
  }
private:
  char operation;
  double value;
};

class Function {
public:
  // добавляем очередную часть в нашу функцию
  void AddPart(char operation, double value){
    parts.push_back(FunctionPart(operation, value));
    // или можно так:
    // part.push_back({operation, value});
  }

  // возвращает вещественное число,
  // применяя текущую операцию к некоторому данному числу
  double Apply(double value) const { // метод константный
    for (const FunctionPart& part : parts) {
      value = part.Apply(value); // применили элементарную операцию к value
    }
    return value;
  }
  // меняет текущую функцию
  void Invert() {
    for (FunctionPart& part : parts) {
      part.Invert(); // инвертируем каждую элементарную операцию
    }
    reverse(parts.begin(), parts.end()); // разворачиваем задом на перед
  }

private:
  // поле для хранения элементарных операций
  vector<FunctionPart> parts;
};
