#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
    Person(const string& type, const string& name) : Type(type), Name(name) {}

    string GetName() const {
        return Name;
    }

    string GetType() const {
        return Type;
    }

    const string Log() const {
        return GetType() + ": " + GetName();
    }

    virtual void Walk(string destination) const {
        cout << Log() << " walks to: " << destination << endl;
    }

private:
    const string Type;
    const string Name;
};


class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong)
    : Person("Student", name), FavouriteSong(favouriteSong) {}

    void Walk(string destination) const override {
        Person::Walk(destination);
        cout << Log() << " sings a song: " << FavouriteSong << endl;
    }

    void Learn() const {
        cout << Log() << " learns" << endl;
    }

    void SingSong() const {
        cout << Log() << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject)
    : Person("Teacher", name), Subject(subject) {}

    void Teach() const {
        cout << Log() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name)
    : Person("Policeman", name) {}

    void Check(const Person& p) const {
        cout << Log() << " checks " << p.GetType() << ". "
             << p.GetType() << "'s name is: " << p.GetName() << endl;
    }
};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const auto& place : places) {
        person.Walk(place);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
