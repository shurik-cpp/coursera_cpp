#include <iostream>
#include <vector>

#include "demographic.h"
#include "print_stats.h"

using namespace std;

/* Вам необходимо написать функцию PrintStats, получающую вектор людей, вычисляющую и
 * выводящую медианный возраст для каждой из следующих групп людей:
 *
 * все люди;
 * все женщины;
 * все мужчины;
 * все безработные женщины;
 * все занятые женщины;
 * все безработные мужчины;
 * все занятые мужчины.
 *
 * Подсказка:
 * Используйте алгоритм partition.
 *
 * В этой задаче вам надо прислать на проверку файл с реализацией функции PrintStats.
 * Этот файл не должен содержать определения функции ComputeMedianAge и типов Person и Gender.
 * В противном случае вы получите ошибку компиляции.
*/


int main() {
	vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}
