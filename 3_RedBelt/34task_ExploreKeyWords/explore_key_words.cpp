// мой код курсера не приняла.. :(

#include "test_runner.h"

#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <future>
#include <functional>

using namespace std;

// в Stats хранится сколько раз каждое слово из key_words суммарно встретилось в потоке input:
struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (auto& it : other.word_frequences) {
            word_frequences[move(it.first)] += it.second;
        }
    }
};

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, string lines) {
    Stats result;
    auto range_begin = begin(lines);
    while (!lines.empty()) {
        auto range_end = find(range_begin, end(lines), ' ');
        string word(make_move_iterator(range_begin), make_move_iterator(range_end));
        lines.erase(begin(lines), range_end);

        if (key_words.count(word)) {
            result.word_frequences[word]++;
        }
        while (!lines.empty() && *begin(lines) == ' ') {
            range_begin = lines.erase(begin(lines));
        }
    }
    return result;
}

// key_words — множество ключевых слов
// input — входной поток, содержащий исследуемые публикации в блогах и соц. сетях, одна строка — одна публикация.
Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    vector<future<Stats>> futures;
    string lines;

    while (input.good()) {

        for (int i = 0; i < 500; ++i) {
            string line;
            getline(input, line);
            if (!line.empty()) {
                lines += (move(line) + ' ');
            } else {
                break;
            }
        }
        getline(input, lines);

        if (!lines.empty()) {
            futures.push_back(async([&key_words, &lines] {
                return ExploreKeyWordsSingleThread(ref(key_words), move(lines));
            }));
            //result += ExploreKeyWordsSingleThread(key_words, lines);
        }
    }

    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
