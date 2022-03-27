#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    struct Data;

    using Id = unsigned long;

    struct Data {
        T object;
        int priority = -1;
    };


    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        data.push_back({move(object), 0});

        return data.size() - 1;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        // ids_begin - начальный итератор для записи идентификаторов по порядку
        for (auto it = range_begin; it != range_end; ++it) {
            *ids_begin = PriorityCollection::Add(move(*it));
            ids_begin++;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return data.size() >= id;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return data[id].object;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        data[id].priority++;
    }

    // Получить объект с максимальным приоритетом и его приоритет
    // При наличии нескольких элементов с одинаковым максимальным приоритетом
    // необходимо выбирать и извлекать тот, который был добавлен позже остальных.
    pair<const T&, int> GetMax() const {
        Id id = FindMax();
        return { data[id].object, data[id].priority };
    }

    // Аналогично GetMax, но сперва удаляет max-элемент из контейнера
    pair<T, int> PopMax() {
        Id it = FindMax();
        data[it].priority = -1;
        Id id = FindMax();
        return { move(data[id].object), data[id].priority };
    }

private:
    using Iterator = typename vector<Data>::iterator;

    vector<Data> data; // основное хранилище

    Id FindMax() const {
        Id runner = 0;
        Id id = 0;
        int priority = 0;
        for (auto& it : data) {
            if (priority <= it.priority) {
                priority = it.priority;
                id = runner;
            }
            runner++;
        }
        return id;
    }

};


class StringNonCopyable : public string {
public:
    using string::string;
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;

    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.GetMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}



int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);

    return 0;
}
