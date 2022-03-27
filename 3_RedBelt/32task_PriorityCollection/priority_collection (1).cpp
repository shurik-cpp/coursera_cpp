#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <list>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    struct Data;

    using Id = Data*;

    struct Data {
        T object;
        int priority = 0;
        Id id; // будет указывать сам на себя чтобы удалить из ids в PopMax()
    };


    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        Data tmp;
        tmp.object = move(object);
        data.push_back(move(tmp));
        data.back().id = &(data.back()); // берем адрес только что запушбэченного объекта
        ids.insert(data.back().id); // закидываем адрес (id) в коллекцию
        return data.back().id;
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
        return ids.count(id);
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return id->object;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        (id->priority)++;
        max_priority = FindMax();
    }

    // Получить объект с максимальным приоритетом и его приоритет
    // При наличии нескольких элементов с одинаковым максимальным приоритетом
    // необходимо выбирать и извлекать тот, который был добавлен позже остальных.
    pair<const T&, int> GetMax() const {
        return {max_priority->object, max_priority->priority};
    }

    // Аналогично GetMax, но сперва удаляет max-элемент из контейнера
    pair<T, int> PopMax() {
        Data tmp = move(*max_priority);
        data.erase(max_priority);
        ids.erase(tmp.id);
        max_priority = FindMax();
        return {move(max_priority->object), max_priority->priority};
    }

private:
    using Iterator = typename list<Data>::iterator;

    list<Data> data; // основное хранилище
    Iterator max_priority; // указывает на последний максимальный приоритет
    set<Id> ids; // для быстрого поиска валидности id
    set<pair<int, Id>> priorities; // сортируем по приоритетам

    Iterator FindMax() {
        int priority = 0;
        Iterator it = begin(data);
        for (Iterator runner = it; runner != end(data); ++runner) {
            if (priority <= runner->priority) {
                priority = runner->priority;
                it = runner;
            }
        }
        return it;
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
