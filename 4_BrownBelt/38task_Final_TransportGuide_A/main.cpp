#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

using namespace std;

// Запрос на добавление остановки:
// Stop X: latitude, longitude
// Остановка с названием X и координатами latitude и longitude.
struct Stop {
	string name;
	int latitude, longitude;

};

// Bus X: описание маршрута
// Запрос на добавление автобуса номер X. Описание маршрута может задаваться в одном из двух форматов (см. пример):
// 1. stop1 - stop2 - ... - stopN: автобус следует от stop1 до stopN и обратно с указанными промежуточными остановками.
// 2. stop1 > stop2 > ... > stopN > stop1: кольцевой маршрут с конечной stop1.
enum TypeRoute {
	DIRECT,
	CIRCULAR
};

struct Bus {
	int number;
	TypeRoute type_rout;
	vector<Stop> route;
};


class DataBase {
public:
	DataBase(const vector<Stop>& stops, const vector<Bus> buses) {
		for (const auto& stop : stops) {
			stops_db_[stop.name] = move(stop);
		}
		for (const auto& bus : buses) {
			buses_db_[bus.number] = move(bus);
		}
	}
private:
	unordered_map<string_view, Stop> stops_db_;
	unordered_map<int, Bus> buses_db_;
};

class BusesManager {

};

DataBase CreateDB(istream& input = cin) {
	int q;
	input >> q;

	for (int i = 0; i < q; ++q) {
		string query;
		getline(input, query);
	}
}

int main() {
	const DataBase db = CreateDB();




	return 0;
}
