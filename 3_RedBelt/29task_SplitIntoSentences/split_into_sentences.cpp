#include "test_runner.h"

#include <vector>
#include <utility>


using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Напишите функцию, разбивающую токены на предложения:
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> result;
    vector<Token> tmp;
    bool is_end_sentence = false;

    for (auto it = begin(tokens); it != end(tokens); ++it) {
        // если встречаем знак пунктуации, заканчивающий предложение, поднимаем флаг
        if (it->IsEndSentencePunctuation()) {
            is_end_sentence = true;
        }
        tmp.push_back(move(*it));
        // пушбэчим tmp в result, если предложение закончилось и следующий токен не знак пунктуации
        if (next(it) == end(tokens) || (is_end_sentence == true && next(it)->IsEndSentencePunctuation() == false)) {
            is_end_sentence = false;
            result.push_back(move(tmp));
        }
    }
    return result;
}

// Token — шаблонный тип, про который известно лишь то, что он имеет
// константный метод IsEndSentencePunctuation, возвращающий true, если токен является знаком пунктуации,
// заканчивающим предложение, и false в противном случае.
// Объекты этого типа запрещено копировать. При наличии копирования этих объектов вы получите ошибку компиляции.
struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}


void TestSplitting() {
    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
                vector<Sentence<TestToken>>({ { {"Split"}, {"into"}, {"sentences"}, {"!"} } })
                );

    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
                vector<Sentence<TestToken>>({ { {"Split"}, {"into"}, {"sentences"}, {"!", true} } })
                );

    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true},
                                                       {"Without"}, {"copies"}, {".", true} })),
                vector<Sentence<TestToken>>({ {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                              {{"Without"}, {"copies"}, {".", true}} })
                );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
