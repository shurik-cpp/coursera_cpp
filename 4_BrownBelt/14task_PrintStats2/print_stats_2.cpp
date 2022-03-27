#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <numeric>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

struct Person {
	string name;
	int age;
	int income;      // доход
	bool is_male;    // мужчина(true)/женщина(false)

};

class Population {
private:
	vector<Person> people;
	multiset<int> ages; // возраста людей
	mutable multiset<int, greater<int>> wealthy; // доходы людей с обратной сортировкой (greater<int>) , greater<int>
	mutable vector<long> wealthy_cach;  // ключевое слово "mutable" позвоняет изменять это поле класса константными методами!
	mutable bool is_cach = false;
	unordered_map<string, int> male_names;
	unordered_map<string, int> female_names;

	pair<string, int> male_top_name;
	pair<string, int> female_top_name;

	void CachWealthy() const { // O(N)
		vector<int> sorted_wealthy(begin(wealthy), end(wealthy));
		wealthy_cach.resize(wealthy.size());
		wealthy_cach[0] =  sorted_wealthy[0];
		for (size_t i = 1; i < wealthy_cach.size(); ++i) {
			wealthy_cach[i] = wealthy_cach[i - 1] + sorted_wealthy[i];
		}
	}

	void AddNameTop(vector<Person>::iterator person) {
		if (person->is_male) {
			male_names[person->name]++;
			if (male_names[person->name] > male_top_name.second) {
				male_top_name.first = person->name;
				male_top_name.second = male_names[person->name];
			}	else if (male_names[person->name] == male_top_name.second) {
				male_top_name.first = male_top_name.first < person->name ? male_top_name.first : person->name;
			}
		} else {
			female_names[person->name]++;
			if (female_names[person->name] > female_top_name.second) {
				female_top_name.first = person->name;
				female_top_name.second = female_names[person->name];
			}	else if (female_names[person->name] == female_top_name.second) {
				female_top_name.first = female_top_name.first < person->name ? female_top_name.first : person->name;
			}
		}
	}

public:
	explicit Population(){}
	explicit Population(Person& person) {
		AddPerson(person);
	}
	explicit Population(vector<Person>& people) {
		for (auto& person : people) {
			AddPerson(person);
		}
	}

	void AddPerson(Person& person) {
		is_cach = false;
		people.push_back(move(person)); // мувим персону в вектор O(1)
		auto it = prev(end(people)); // берем итератор на только что добаленный элемент
		AddNameTop(it); // поверяем имя персоны и добавляем в топчик, если его имя самое популярное и лексикографически меньше текущего топчика
		wealthy.insert(it->income); // запоминаем зарплаты с сортировкой поубыванию
		ages.insert(it->age); // запоминаем возраст с сортировкой по возрастанию
	}

	size_t GetAdult(const int adult_age) const {
		auto it = ages.lower_bound(adult_age); // O(log(N)
		return std::distance(it, end(ages));
	}

	long GetSumWealthy(const size_t number_of_rich_people) const {
		if (!is_cach && !wealthy.empty()) {
			is_cach = true;
			CachWealthy();
		}
		if (wealthy_cach.empty() || number_of_rich_people == 0) {
			return 0;
		} else if (number_of_rich_people > wealthy_cach.size()) {
			return wealthy_cach.back();
		}
		return wealthy_cach[number_of_rich_people - 1]; // O(1)
	}

	const string& GetPopularName(const char gender) const {
		if (gender == 'M') {
			return male_top_name.first;
		}
		return female_top_name.first;
	}

};

Population ReadPeople(istream& input) {
	Population people;
	int count;
	input >> count;

	for (int i = 0; i < count; ++i) {
		Person p;
		char gender;
		input >> p.name >> p.age >> p.income >> gender;
		p.is_male = gender == 'M';
		people.AddPerson(p);
	}
	return people;
}

int main() {
		vector<Person> p = {
			{"Ivon", 24, 374, true},
			{"Ivan", 25, 1000, true},
			{"Olga", 30, 623, false},
			{"Sergey", 24, 825, true},
			{"Maria", 42, 1254, false},
			{"Mikhail", 15, 215, true},
			{"Ivon", 24, 374, true},
			{"Oleg", 18, 230, true},
			{"Denis", 53, 8965, true},
			{"Maxim", 37, 9050, true},
			{"Ivan", 47, 19050, true},
			{"Ivon", 24, 374, true},
			{"Ivan", 17, 50, true},
			{"Olga", 23, 550, false},
			{"Ivon", 24, 374, true}
		};

	const Population people(p); // = ReadPeople(cin);

	for (string command; cin >> command; ) {
		if (command == "AGE") {
			int adult_age;
			cin >> adult_age;

			cout << "There are " << people.GetAdult(adult_age)
					 << " adult people for maturity age " << adult_age << '\n';
		} else if (command == "WEALTHY") {
			size_t count;
			cin >> count;

			cout << "Top-" << count << " people have total income " << people.GetSumWealthy(count) << '\n';
		} else if (command == "POPULAR_NAME") {
			char gender;
			cin >> gender;

			const string& name = people.GetPopularName(gender);
			if (name.empty()) {
				cout << "No people of gender " << gender << '\n';
			} else {
				cout << "Most popular name among people of gender " << gender << " is "
						 << name << '\n';
			}
		}
	}
}
