#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

class ReadingManager {
private:
    map<int, int> users_sorted_by_id; // <пользователь, прогресс>
    map<int, set<int>> users_sorted_by_pages; // <страница, пользоватиели> (сортировка по прочитанным страницам)

public:
    ReadingManager() {}

    // READ user page — сохранить факт того, что пользователь под номером user
    // дочитал книгу до страницы page.
    // Если ранее такой пользователь не встречался, необходимо его добавить.
    // Гарантируется, что в рамках одного пользователя номера страниц в соответствующих ему событиях
    // возрастают.
    void Read(int user_id, int page_count) {
        // если пользователь уже отмечался, надо удалить его из мапы сортированных по прогрессу,
        // чтобы потом добавить его в мапу прогресса на новую (текущую) страницу
        if (users_sorted_by_id.count(user_id)) {
            // берем его прогресс по константной ссылке
            const int& last_progress = users_sorted_by_id[user_id];
            // удаляем его из учета прогресса, т.к. юзер уже на другой странице
            users_sorted_by_pages[last_progress].erase(user_id);
            // если на этой странице никто больше не остановился, удаляем ее из мапы страниц
            if (users_sorted_by_pages[last_progress].empty()) {
                users_sorted_by_pages.erase(last_progress);
            }
        }
        // запоминаем юзера и его прогресс
        users_sorted_by_id[user_id] = page_count;
        // записываем новый прогресс этого юзера
        users_sorted_by_pages[page_count].insert(user_id);
    }

    // CHEER user — сообщить пользователю user, какая доля существующих пользователей
    // (не считая его самого) прочитала меньшую часть книги, чем он.
    // Если этот пользователь на данный момент единственный, доля считается равной 1.
    // Если для данного пользователя пока не было ни одного события READ, доля считается равной 0,
    // а сам пользователь не учитывается при вычислении долей для других пользователей до тех пор,
    // пока для него не случится событие READ.
    double Cheer(int user_id) const {
        if (!users_sorted_by_id.count(user_id)) {
            return 0;
        }
        if (users_sorted_by_id.size() == 1) {
            return 1;
        }
        // ствим итератор на прогрес текущего юзера,
        // чтобы проитеривоваться от begin(users_sorted_by_pages) до it_progress
        // и посчитать сколько юзеров прочитали меньше страниц
        auto it_progress = users_sorted_by_pages.lower_bound(users_sorted_by_id.at(user_id));
        // хранит сколько юзеров прочитали меньше страниц
        int number_of_people_who_read_less = 0;
        // итерируемся по тем страницам, которые меньше прогресса текущего юзера,
        // и считаем количество отставших юзеров
        for (auto it = begin(users_sorted_by_pages); it != it_progress; ++it) {
            number_of_people_who_read_less += it->second.size();
        }
        if (number_of_people_who_read_less == 0) {
            return 0;
        }
        int position = users_sorted_by_id.size() - number_of_people_who_read_less;
        return (users_sorted_by_id.size() - position) * 1.0 / (users_sorted_by_id.size() - 1);
    }

};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
