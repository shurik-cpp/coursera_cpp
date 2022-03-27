#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

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

// функция, которая описывает саму формулу
Function MakeWeightFunction(const Params& params,
                            const Image& image) {
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params,
                          const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
//  Image image = {10, 2, 6};
//  Params params = {4, 2, 6};
//  cout << ComputeImageWeight(params, image) << endl;
//  cout << ComputeQualityByWeight(params, image, 46) << endl;
  return 0;
}
