#ifndef PLATES_H
#define PLATES_H

#include <iostream>
#include <iomanip>
#include <tuple>

struct Plate {
	char C1;
	int Number;
	char C2;
	char C3;
	int Region;
};

// чтобы распечатывать автомобильные номера
std::ostream& operator<<(std::ostream& out, const Plate& p) {
	out << p.C1;
	out << std::setw(3) << std::setfill('0') << p.Number;
	out << p.C2 << p.C3;
	out << std::setw(2) << std::setfill('0') << p.Region;
	return out;
}

// для того, чтобы тип Plate запихать в set, нужно определить operator<
bool operator<(const Plate& l, const Plate& r) {
	return std::tie(l.C1, l.Number, l.C2, l.C3, l.Region)
			< std::tie(r.C1, r.Number, r.C2, r.C3, r.Region);
}

// для того, чтобы тип Plate запихать в unordered_set, нужно написать хеш-функцию и определить operator==
// хеш-фунция лежит в main.cpp
bool operator==(const Plate& l, const Plate& r) {
	return (l.C1 == r.C1)
			&& (l.Number == r.Number)
			&& (l.C2 == r.C2)
			&& (l.C3 == r.C3)
			&& (l.Region == r.Region);
}

#endif // PLATES_H
