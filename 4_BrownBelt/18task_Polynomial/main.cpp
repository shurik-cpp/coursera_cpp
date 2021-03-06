#include "test_runner.h"
#include "profile.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
void PrintCoeff(std::ostream& out, int i, const T& coef, bool printed) {
	bool coeffPrinted = false;
	if (coef == 1 && i > 0) {
		out << (printed ? "+" : "");
	} else if (coef == -1 && i > 0) {
		out << "-";
	} else if (coef >= 0 && printed) {
		out << "+" << coef;
		coeffPrinted = true;
	} else {
		out << coef;
		coeffPrinted = true;
	}
	if (i > 0) {
		out << (coeffPrinted ? "*" : "") << "x";
	}
	if (i > 1) {
		out << "^" << i;
	}
}

template<typename T>
class Polynomial {
private:
	std::vector<T> coeffs_ = {0};

	void Shrink() {
		while (coeffs_.size() > 1 && coeffs_.back() == 0) {
			coeffs_.pop_back();
		}
	}

	class Proxy {
	private:
		Polynomial& poly; // ссылка на Polynomial::std::vector<T> coeffs_
		size_t degree;    // для неявного преобразования из Polynomial::Proxy в тип Т

	public:
		Proxy(Polynomial& p, size_t d)
			:	poly(p)
			, degree(d) {}

		Proxy& operator=(T value) {  // присваиваем новое значение в ячейку coeffs_[degree]
			if (degree >= poly.coeffs_.size()) {
				poly.coeffs_.resize(degree + 1, 0);
			}
			poly.coeffs_[degree] = value;
			poly.Shrink();
			return *this;
		}

		// Вы можете перегружать операторы типа, чтобы ваш тип мог быть неявно преобразован в указанный тип.
		// Оператор преобразования должен быть определен в class / struct :
		// operator T() const { /* return something */ }
		operator T() const { // перегрузка оператора неявного преобразования для сравнения, например с int'ом в ASSERT_EQUAL
			return std::as_const(poly)[degree]; // возвращаем значение из ячейки degree
		}
	};

public:
	// Создаёт многочлен, все коэффициенты которого равны нулю
	Polynomial() = default;
	// Принимает вектор коэффициентов (коэффициенты задаются от младшего к старшим)
	// Например, Polynomial({10, 2, 3, 4}) создаёт многочлен 4*x^3 + 3*x^2 + 2*x + 10
	explicit Polynomial(vector<T> coeffs)
		: coeffs_(std::move(coeffs)) {
		Shrink();
	}
	// Аналогичен конструктору от вектора, но принимает пару итераторов
	template<typename Iterator>
	explicit Polynomial(Iterator first, Iterator last)
		: coeffs_(first, last) {
		Shrink();
	}
	// Операторы проверки на равенство и неравенство. Два многочлена равны тогда и только тогда,
	// когда их соответствующие коэффициенты попарно равны
	bool operator ==(const Polynomial& other) const {
		return coeffs_ == other.coeffs_;
	}
	bool operator !=(const Polynomial& other) const {
		return !operator==(other);
	}
	// Возвращает степень многочлена -- максимальную степень, коэффициент при которой не равен нулю.
	// Например, степень многочлена 2*x равна 1, степень многочлена 4*x^5 + x^3 - 10 равна 5,
	// степень многочлена 5 равна нулю.
	// Метод работает за O(1)
	int Degree() const {
		return coeffs_.size() - 1;
	}

	Polynomial& operator +=(const Polynomial& r) {
		if (r.coeffs_.size() > coeffs_.size()) {
			coeffs_.resize(r.coeffs_.size());
		}
		for (size_t i = 0; i != r.coeffs_.size(); ++i) {
			coeffs_[i] += r.coeffs_[i];
		}
		Shrink();
		return *this;
	}

	Polynomial& operator -=(const Polynomial& r) {
		if (r.coeffs_.size() > coeffs_.size()) {
			coeffs_.resize(r.coeffs_.size());
		}
		for (size_t i = 0; i != r.coeffs_.size(); ++i) {
			coeffs_[i] -= r.coeffs_[i];
		}
		Shrink();
		return *this;
	}
	// Возвращает значение коэффициента при заданной степени.
	// Если переданное значение больше степени многочлена, метод возвращает 0
	const T operator [](const size_t degree) const {
		return coeffs_.size() > degree ? coeffs_[degree] : 0;
	}

	Proxy operator [](const size_t degree) {
		return Proxy{*this, degree}; // создаем и возвращаем объект класса Polynomial::Proxy
	}

	// Вычисляет значение многочлена в точке с переданным значением
	T operator ()(const T& x) const {
		T res = 0;
		for (auto it = coeffs_.rbegin(); it != coeffs_.rend(); ++it) {
			res *= x;
			res += *it;
		}
		return res;
	}

	using const_iterator = typename std::vector<T>::const_iterator;

	// Итераторы на коэффициенты многочлена
	const_iterator begin() const {
		return coeffs_.cbegin();
	}
	const_iterator end() const {
		return coeffs_.cend();
	}
};

template <typename T>
std::ostream& operator <<(std::ostream& out, const Polynomial<T>& p) {
	bool printed = false;
	for (int i = p.Degree(); i >= 0; --i) {
		if (p[i] != 0) {
			PrintCoeff(out, i, p[i], printed);
			printed = true;
		}
	}
	return out;
}

template <typename T>
Polynomial<T> operator +(Polynomial<T> lhs, const Polynomial<T>& rhs) {
	lhs += rhs;
	return lhs;
}

template <typename T>
Polynomial<T> operator -(Polynomial<T> lhs, const Polynomial<T>& rhs) {
	lhs -= rhs;
	return lhs;
}

void TestCreation() {
	{
		Polynomial<int> default_constructed;
		ASSERT_EQUAL(default_constructed.Degree(), 0);
		ASSERT_EQUAL(default_constructed[0], 0);
	}
	{
		Polynomial<double> from_vector({1.0, 2.0, 3.0, 4.0});
		ASSERT_EQUAL(from_vector.Degree(), 3);
		ASSERT_EQUAL(from_vector[0], 1.0);
		ASSERT_EQUAL(from_vector[1], 2.0);
		ASSERT_EQUAL(from_vector[2], 3.0);
		ASSERT_EQUAL(from_vector[3], 4.0);
	}
	{
		const vector<int> coeffs = {4, 9, 7, 8, 12};
		Polynomial<int> from_iterators(begin(coeffs), end(coeffs));
		ASSERT_EQUAL(from_iterators.Degree(), coeffs.size() - 1);
		ASSERT(std::equal(cbegin(from_iterators), cend(from_iterators), begin(coeffs)));
	}
}

void TestEqualComparability() {
	Polynomial<int> p1({9, 3, 2, 8});
	Polynomial<int> p2({9, 3, 2, 8});
	Polynomial<int> p3({1, 2, 4, 8});

	ASSERT_EQUAL(p1, p2);
	ASSERT(p1 != p3);
}

void TestAddition() {
	Polynomial<int> p1({9, 3, 2, 8});
	Polynomial<int> p2({1, 2, 4});

	p1 += p2;
	ASSERT_EQUAL(p1, Polynomial<int>({10, 5, 6, 8}));

	auto p3 = p1 + p2;
	ASSERT_EQUAL(p3, Polynomial<int>({11, 7, 10, 8}));

	p3 += Polynomial<int>({-11, 1, -10, -8});
	ASSERT_EQUAL(p3.Degree(), 1);
	const Polynomial<int> expected{{0, 8}};
	ASSERT_EQUAL(p3, expected);
}

void TestSubtraction() {
	Polynomial<int> p1({9, 3, 2, 8});
	Polynomial<int> p2({1, 2, 4});

	p1 -= p2;
	ASSERT_EQUAL(p1, Polynomial<int>({8, 1, -2, 8}));

	auto p3 = p1 - p2;
	ASSERT_EQUAL(p3, Polynomial<int>({7, -1, -6, 8}));

	p3 -= Polynomial<int>({7, -5, -6, 8});
	ASSERT_EQUAL(p3.Degree(), 1);
	const Polynomial<int> expected{{0, 4}};
	ASSERT_EQUAL(p3, expected);
}

void TestEvaluation() {
	const Polynomial<int> default_constructed;
	ASSERT_EQUAL(default_constructed(0), 0);
	ASSERT_EQUAL(default_constructed(1), 0);
	ASSERT_EQUAL(default_constructed(-1), 0);
	ASSERT_EQUAL(default_constructed(198632), 0);

	const Polynomial<int64_t> cubic({1, 1, 1, 1});
	ASSERT_EQUAL(cubic(0), 1);
	ASSERT_EQUAL(cubic(1), 4);
	ASSERT_EQUAL(cubic(2), 15);
	ASSERT_EQUAL(cubic(21), 9724);
}

void TestConstAccess() {
	const Polynomial<int> poly(std::initializer_list<int> {1, 2, 3, 4, 5});

	ASSERT_EQUAL(poly[0], 1);
	ASSERT_EQUAL(poly[1], 2);
	ASSERT_EQUAL(poly[2], 3);
	ASSERT_EQUAL(poly[3], 4);
	ASSERT_EQUAL(poly[4], 5);
	ASSERT_EQUAL(poly[5], 0);
	ASSERT_EQUAL(poly[6], 0);
	ASSERT_EQUAL(poly[608], 0);
}

void TestNonconstAccess() {
	Polynomial<int> poly;

	// Polynomial<int> имеет перегрузку operator[], который позвращает только что созданный Polynomial<int>::Proxy, т.е.:
	// сперва выполняется poly[x], возвращает тип Polynomial<int>::Proxy, затем работает Proxy::operator=
	poly[0] = 1;
	poly[3] = 12;
	poly[5] = 4;
	ASSERT_EQUAL(poly.Degree(), 5);

	// здесь же выполняется poly[x], возвращает тип Polynomial<int>::Proxy, затем происходит неявное преобразование
	// типа из Polynomial<int>::Proxy в int при помощи Proxy::operator T()
	ASSERT_EQUAL(poly[0], 1);
	ASSERT_EQUAL(poly[1], 0);
	ASSERT_EQUAL(poly[2], 0);
	ASSERT_EQUAL(poly[3], 12);
	ASSERT_EQUAL(poly[4], 0);
	ASSERT_EQUAL(poly[5], 4);
	ASSERT_EQUAL(poly[6], 0);
	ASSERT_EQUAL(poly[608], 0);

	ASSERT_EQUAL(poly.Degree(), 5);

	poly[608] = 0;
	ASSERT_EQUAL(poly.Degree(), 5);

	{
		LOG_DURATION("Iteration over const");
		for (size_t i = 10; i < 50000; ++i) {
			ASSERT_EQUAL(std::as_const(poly)[i], 0);
			ASSERT_EQUAL(poly.Degree(), 5);
		}
	}
	{
		LOG_DURATION("Iteration over non-const");
		for (size_t i = 10; i < 50000; ++i) {
			ASSERT_EQUAL(poly[i], 0);
			ASSERT_EQUAL(poly.Degree(), 5);
		}
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCreation);
	RUN_TEST(tr, TestEqualComparability);
	RUN_TEST(tr, TestAddition);
	RUN_TEST(tr, TestSubtraction);
	RUN_TEST(tr, TestEvaluation);
	RUN_TEST(tr, TestConstAccess);
	RUN_TEST(tr, TestNonconstAccess);
	return 0;
}
