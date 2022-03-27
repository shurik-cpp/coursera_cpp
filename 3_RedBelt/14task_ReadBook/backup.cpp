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
    map<int, set<int>> users_sorted_by_progress; // <страница, пользоватиели>

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
            // удаляем его из учета прогресса, т.к. он уже на другой странице
            users_sorted_by_progress[last_progress].erase(user_id);
            if (users_sorted_by_progress[last_progress].empty()) {
                users_sorted_by_progress.erase(last_progress);
            }
        }
        // запоминаем юзера и его прогресс
        users_sorted_by_id[user_id] = page_count;
        // записываем новый прогресс этого юзера
        users_sorted_by_progress[page_count].insert(user_id);
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
        // ствим итератор на прогрес текущего пользователя,
        // чтобы проитеривоваться от begin(users_sorted_by_progress) до it_progress
        // и посчитать сколько юзеров прочитали меньше страниц
        auto it_progress = users_sorted_by_progress.lower_bound(users_sorted_by_id.at(user_id));
        int user_rating_position = 0;
        for (auto it = begin(users_sorted_by_progress); it != it_progress; ++it) {
            user_rating_position += it->second.size();
        }
        if (user_rating_position == 0) {
            return 0;
        }
        double result = (users_sorted_by_id.size() - user_rating_position) * 1.0;
        return result;
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
            cout << setprecision(6) << manager.Cheer(user_id) << endl; //"\n";
        }
    }

    return 0;
}
