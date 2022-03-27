#include "test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// разработайте шаблон класса Paginator
template <typename Iterator> // он имеет один шаблонный параметр — тип итератора
class Paginator { // Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
private:
  Iterator _first, _last;
  size_t _page_size;
  //--------------------------
  class IteratorRange {
  private:
    Iterator _b, _l;
  public:
    IteratorRange(Iterator b, Iterator l)
        : _b(b),
          _l(l) {}
    // сами страницы должны так же поддерживать итерацию с помощью range-based for
    Iterator begin() { return _b; }
    Iterator begin() const { return _b; }
    Iterator end() { return _l; }
    Iterator end() const { return _l; }

    // и иметь метод size_t size() const, возвращающий количество объектов в этой странице
    size_t size() const { return static_cast<size_t>(_l - _b); }
  };
  // Порождающая функция для IteratorRange
  auto Head(Iterator begin, Iterator end, size_t page_size) {
    return IteratorRange {
        begin, next(begin, min(page_size, static_cast<size_t>(end - begin)))
    };
  }
  //---------------------------
  vector<IteratorRange> pages;

public:
  // конструктор класса Paginator<Iterator> принимает 3 параметра:
  // 1. Iterator begin
  // 2. Iterator end — пара итераторов begin и end задают полуинтервал [begin; end),
  //    который мы будем нарезать на страницы
  // 3. size_t page_size — размер одной страницы
  Paginator(const Iterator& f, const Iterator& l, const size_t& ps)
      : _first(f),
        _last(l),
        _page_size(ps) {
    auto counter = _first;
    while (counter < _last) {
      //cout << *counter << ' ' << endl;
      IteratorRange page = Head(counter, _last, _page_size);
      pages.push_back(page);
      for (size_t i = 0; i < _page_size; ++i) counter++;
    }
  }
  // по объектам класса Paginator<Iterator> можно проитерироваться с помощью цикла range-based for
  auto begin() { return pages.begin(); }
  auto begin() const { return pages.begin(); }
  auto end() { return pages.end(); }
  auto end() const { return pages.end(); }
  // доступ к странице по индексу
  IteratorRange operator [](const size_t index) {
    return pages[index];
  }
  IteratorRange operator [](const size_t index) const {
    return pages[index];
  }
  // класс Paginator<Iterator> имеет метод size_t size() const, который возвращает количество страниц,
  // на которые был разбит переданный контейнер
  size_t size() const { return pages.size(); }
};

// Кроме того разработайте шаблон функции Paginate(Разбивать на страницы),
// которая принимает ссылку на контейнер и размер страницы,
// и возвращает объект класса Paginator<It>
template <typename Container>
auto Paginate(Container& c, size_t page_size) {
  return Paginator {c.begin(), c.end(), page_size};
}

void TestPageCounts();
void TestLooping();
void TestModification();
void TestPageSizes();
void TestConstContainer();
void TestPagePagination();

int main() {
//  vector<int> v(15); // создаем вектор интов с 15-ю элементами со значением 0
//  iota(begin(v), end(v), 1); // заполним его значениями от 1 до 15

//  const Paginator<vector<int>::iterator> pages = Paginate(v, 6);
//  for (const auto& it : pages) {
//    for (const auto& x : it) {
//      cout << x << ' ';
//    }
//    cout << endl;
//  }
//  cout << endl;

  TestRunner tr;
  RUN_TEST(tr, TestPageCounts);
  RUN_TEST(tr, TestLooping);
  RUN_TEST(tr, TestModification);
  RUN_TEST(tr, TestPageSizes);
  RUN_TEST(tr, TestConstContainer);
  RUN_TEST(tr, TestPagePagination);
}


void TestPageCounts() {
  vector<int> v(15); // создаем вектор интов с 15-ю элементами со значением 0

  ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
  ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
  ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
  ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
  ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

void TestLooping() {
  vector<int> v(15);
  // Заполняет диапазон [first, last) последовательно увеличивающимися значениями,
  // начиная с value и повторяя оценку ++value
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
  vector<string> vs = {"one", "two", "three", "four", "five"};
  for (auto page : Paginate(vs, 2)) {
    for (auto& word : page) {
      word[0] = toupper(word[0]);
    }
  }

  const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
  ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
  string letters(26, ' ');

  Paginator letters_pagination(letters.begin(), letters.end(), 11);
  vector<size_t> page_sizes;
  for (const auto& page : letters_pagination) {
    page_sizes.push_back(page.size());
  }

  const vector<size_t> expected = {11, 11, 4};
  ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
  const string letters = "abcdefghijklmnopqrstuvwxyz";

  vector<string> pages;
  for (const auto& page : Paginate(letters, 10)) {
    pages.push_back(string(page.begin(), page.end()));
  }

  const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
  ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
  vector<int> v(22);
  iota(begin(v), end(v), 1);

  vector<vector<int>> lines;
  for (const auto& split_by_9 : Paginate(v, 9)) {
    for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
      lines.push_back({});
      for (int item : split_by_4) {
        lines.back().push_back(item);
      }
    }
  }

  const vector<vector<int>> expected = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
  };
  ASSERT_EQUAL(lines, expected);
}

