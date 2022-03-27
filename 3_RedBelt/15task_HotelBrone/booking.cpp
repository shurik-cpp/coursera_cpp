#include <iostream>
#include <map>
#include <set>
#include <deque>

using namespace std;

class Book {
private:
    struct Data {
        long time;
        string hotel_name;
        int client_id;
        int room_count;
    };

    struct UniqClient {
        long time;
        set<int> clients;
    };

    deque<Data> time_queue;

    map<string, set<int>> clients_ids_of_hotel; // отель - множество_клиентов
    map<string, int> rooms_of_hotels;  // отель - занятые_комнаты

    void DeleteOldBoockings(const long& time) {
        // пусть last_time — время последнего события BOOK,
        // тогда в данном запросе нужно учесть все события с last_time − 86400 < time ⩽ last_time,
        // где 86400 — количество секунд в сутках.
        while (time - time_queue.front().time >= 86400) {
            // удалим устаревших клиентов с проверкой имени отеля
            clients_ids_of_hotel[time_queue.front().hotel_name].erase(time_queue.front().client_id);
            // освободим комнаты
            rooms_of_hotels[time_queue.front().hotel_name] -= time_queue.front().room_count;
            // удалим устаревшие записи
            time_queue.pop_front();
        }
    }

public:
    void NewBoocking(const long& time, const string& hotel_name, const int& client_id, const int& room_count) {
        // добавим занятые комнаты
        rooms_of_hotels[hotel_name] += room_count;
        // закинем в очередь запись
        time_queue.push_back({time, hotel_name, client_id, room_count});
        // удалим старые записи
        Book::DeleteOldBoockings(time);
        // и только после этого нужно добавить свежего клиента в список отеля
        clients_ids_of_hotel[hotel_name].insert(client_id);
    }

    // CLIENTS hotel_name — вывести количество различных клиентов, бронировавших номера
    // в отеле hotel_name за последние сутки.
    int GetClients(const string& hotel_name) {
        return clients_ids_of_hotel[hotel_name].size();
    }

    // ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.
    int GetRooms(const string& hotel_name) {
        return rooms_of_hotels[hotel_name];
    }
};

int main() {
    // разрываем связь между потоками ввода и вывода для ускорения программы
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Book hotels;
    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;
        // BOOK time hotel_name client_id room_count — забронировать клиентом client_id
        // room_count номеров в отеле hotel_name в момент времени time.
        // Время измеряется в секундах, отсчитываемых от некоторого момента.
        if (command == "BOOK") {
            // time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
            // hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
            // client_id — натуральное число, не превосходящее 10^9.
            // room_count — целое положительное число, не превосходящее 1000.
            long time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            hotels.NewBoocking(time, hotel_name, client_id, room_count);
        }
        // =======================
        // Формат выходных данных:
        // Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос.
        // Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.
        // =======================
        else if (command == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.GetClients(hotel_name) << '\n';
        }
        else if (command == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.GetRooms(hotel_name) << '\n';
        }
    }

    return 0;
}
