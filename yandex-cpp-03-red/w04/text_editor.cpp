#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() {}

    void Left() {
        if (cursor != text.begin()) {
            --cursor;
        }
    }

    void Right() {
        if (cursor != text.end()) {
            ++cursor;
        }
    }

    void Insert(char token) {
        text.insert(cursor, token);
    }

    void Cut(size_t tokens = 1) {
        auto end_of_block = next(cursor, tokens);
        if (distance(cursor, next(cursor, tokens)) > distance(cursor, text.end())) {
            end_of_block = text.end();
        }

        Copy(tokens);
        cursor = text.erase(cursor, end_of_block);
    }

    void Copy(size_t tokens = 1) {
        auto end_of_block = next(cursor, tokens);
        if (distance(cursor, next(cursor, tokens)) > distance(cursor, text.end())) {
            end_of_block = text.end();
        }

        buffer.clear();
        buffer.insert(buffer.begin(), cursor, end_of_block);
    }

    void Paste() {
        text.insert(cursor, buffer.begin(), buffer.end());
    }

    string GetText() const {
        string text_str;
        for (auto ch : text) {
            text_str += ch;
        }
        return text_str;
    }

    string GetCursor() const {
        string cursor_str;
        if (cursor != text.end()) {
            cursor_str =  *cursor;
            cursor_str = "|" + cursor_str;
        } else {
            cursor_str = "...|";
        }

        return cursor_str;
    }

private:
    list<char> text;
    list<char> buffer;
    list<char>::iterator cursor = text.begin();
};

void TypeText(Editor& editor, const string& text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

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
    for (char c : text) {
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

void SmokeTest() {
    Editor editor;
    const string text = "hello, world";
    for (char c : text) {
        editor.Insert(c);
        cout << editor.GetCursor() << endl;
    }
    // `hello, world|`
    cout << editor.GetText() << endl;

    for (size_t i = 0; i < text.size(); ++i) {
        editor.Left();
        cout << editor.GetCursor() << endl;
    }
    // `|hello, world`
    editor.Cut(7);
    // `|world`
    cout << editor.GetText() << endl;
    cout << editor.GetCursor() << endl;

    // buffer: `hello, `
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
        cout << editor.GetCursor() << endl;
    }
    // `world|`
    editor.Insert(',');
    cout << editor.GetText() << endl;
    cout << editor.GetCursor() << endl;
    editor.Insert(' ');
    // `world, |`
    cout << editor.GetText() << endl;
    cout << editor.GetCursor() << endl;

    editor.Paste();
    // `world, hello, |`
    cout << editor.GetText() << endl;
    cout << editor.GetCursor() << endl;

    editor.Left();
    cout << editor.GetCursor() << endl;
    editor.Left();
    cout << editor.GetCursor() << endl;
    // `world, hello|, `
    editor.Cut(3); // cut 2 symbols
    // `world, hello|`
    cout << editor.GetText() << endl;
    cout << editor.GetCursor() << endl;

    //cout << editor.GetText();
}

int main() {
    //SmokeTest();

    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
