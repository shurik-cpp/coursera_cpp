// продолжение темы "Пользовательские типы в ассоциативных контейнерах"
// первый проект этой темы: Plate
#include <iostream>
#include <set>
#include <unordered_set>

#include "plates.h"

using namespace std;

// хешер для типа Plate
struct PlateHasher {
	size_t operator()(const Plate& p) const {
		size_t result = p.Number;
		result *= 100;
		result += p.Region;

		int s1 = p.C1 - 'A';
		int s2 = p.C2 - 'A';
		int s3 = p.C3 - 'A';
		int s = (s1 * 100 * s2) * 100 +s3;

		result *= 1000;
		result += s;
		return result;
	}
};

// какой-то еще пользовательский тип..
struct MyType {
	// стандартные типы
	double d;
	string str;
	// плюс пользовательский тип
	Plate plate;
};

// хешер для MyType
struct MyTypeHasher {
	// будем использовать стандартные хешеры из библиотеки:
	hash<double> dhash;
	hash<string> shash;

	// и пользовательский хешер:
	PlateHasher phash;

	// сама хеш-функция:
	size_t operator()(const MyType& mt) {
		size_t r1 = dhash(mt.d);
		size_t r2 = shash(mt.str);
		size_t r3 = phash(mt.plate);

		// универсальный совет:
		// взять какой-нибудь многочлен с несколькими коэффициентами и посчитать его значение
		// например: Ax^2 + Bx + C
		// для значения x принято брать какое-нибудь простое число:
		const size_t x = 37;

		return (r1 * x * x + r2 * x + r3);
	}
};

int main() {
	unordered_set<MyType, MyTypeHasher> ht;

	return 0;
}
