// Пользовательские типы в ассоциативных контейнерах

#include <iostream>
#include <set>
#include <unordered_set>

#include "plates.h"
#include "generator.h"
#include "profile.h"

using namespace std;

// для того, чтобы тип Plate запихать в unordered_set, нужно написать хеш-функцию и определить operator==
// хеш-фунция выглядит так:
struct PlateHasher {
	// хеш-функция должна возвращать size_t для определения индекса "корзины" хеша

	// пример простейшей хеш-функции:
/*
	size_t operator()(const Plate& p) const {
		return p.Number;
	}
*/

	// для того, чтобы unordered_set работал быстро (чтобы было меньше колизий), нужно как можно лучше определить хеш-функцию!

	// улучшим ее, добавив еще обработку региона:
/*
	size_t operator()(const Plate& p) const {
		size_t result = p.Number;
		result *= 100;
		result += p.Region;
		return result;
	}
*/

	// а теперь, сделаем хещ-функцию еще хитрее, добавив обработку букв:
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

int main() {
	PlateGenerator pg;
	set<Plate> s_plates; // для set нужно определить operator<
	unordered_set<Plate, PlateHasher> h_plates; // для unordered_set нужна хеш-функция и operator==
	const int N = 100'000;

	{ LOG_DURATION("set")
		for (int i = 0; i < N; ++i) {
			s_plates.insert(pg.GetRandomPlate());
		}
	}

	{ LOG_DURATION("unordered_set")
		for (int i = 0; i < N; ++i) {
			h_plates.insert(pg.GetRandomPlate());
		}
	}

//	for (const auto& plate : s_plates) {
//		cout << plate << '\n';
//	}
	cout << "s_plates.size() = "  << s_plates.size() << endl;
	cout << "h_plates.size() = "  << h_plates.size() << endl;


	return 0;
}
