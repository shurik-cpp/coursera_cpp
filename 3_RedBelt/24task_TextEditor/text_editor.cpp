#include <string>
#include <list>
#include <vector>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() {}

    // сдвинуть курсор влево
    void Left() {
        if (cursor != begin(data)) {
            cursor--;
            cursor_position--;
        }
    }
    // сдвинуть курсор вправо
    void Right() {
        if (cursor != end(data)) {
            cursor++;
            cursor_position++;
        }
    }
    // вставить символ token
    void Insert(char token) {
        data.insert(cursor, token);
        Left();
        Right();

    }
    // cкопировать не более tokens символов, начиная с текущей позиции курсора
    void Copy(size_t tokens) {
        if (!buffer.empty()) {
            buffer.clear();
        }
        for (size_t i = 0; i != tokens; ++i) {
            buffer.push_back(*cursor);
            Right();
        }
    }
    // вырезать не более tokens символов, начиная с текущей позиции курсора
    void Cut(size_t tokens) {
        list<char>::iterator cursor_tmp = cursor;
        Copy(tokens);

        data.erase(cursor_tmp, cursor);
    }
    // вставить содержимое буфера в текущую позицию курсора
    void Paste() {
        for (auto& it : buffer) {
            Insert(it);
        }
    }
    // получить текущее содержимое текстового редактора
    string GetText() const {
        string result(begin(data), end(data));
        return result;
    }

private:
    list<char> data;
    list<char>::iterator cursor = begin(data);
    vector<char> buffer;
    size_t cursor_position = 0;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        // hello, world|
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        // |hello, world
        editor.Cut(first_part_len);
        // |world  buff == "hello, "
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        // world|  buff == "hello, "
        TypeText(editor, ", ");
        // world, |  buff == "hello, "
        editor.Paste();
        // "world, hello, |"
        editor.Left();
        editor.Left();
        // "world, hello|, "
        editor.Cut(3);
        // "world, hello|"

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
