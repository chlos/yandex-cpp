#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Person {
  public:
    virtual string Proffesion() const = 0;

    virtual void Walk(const string& destination) const {
        cout << Iam() << " walks to: " << destination << endl;
    }

    string Name() const { return name_; }

  protected:
    Person(const string& name) : name_{name} {};

    string Iam() const {
        ostringstream oss;
        oss << Proffesion() << ": " << Name();
        return oss.str();
    }

  private:
    const string name_;
};

class Student : public Person {
  public:
    Student(const string& name, const string& favouriteSong)
        : Person{name}, FavouriteSong{favouriteSong} {}

    void Learn() const { cout << Iam() << " learns" << endl; }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Iam() << " sings a song: " << FavouriteSong << endl;
    }

    string Proffesion() const override { return "Student"; }

  private:
    const string FavouriteSong;
};

class Teacher : public Person {
  public:
    Teacher(const string& name, const string& subject) : Person{name}, Subject{subject} {}

    void Teach() const { cout << Iam() << " teaches: " << Subject << endl; }

    string Proffesion() const override { return "Teacher"; }

  private:
    const string Subject;
};

class Policeman : public Person {
  public:
    Policeman(const string& name) : Person{name} {}

    void Check(Person& p) const {
        cout << Iam() << " checks " << p.Proffesion() << ". " << p.Proffesion()
             << "'s name is: " << p.Name() << endl;
    }

    string Proffesion() const override { return "Policeman"; }
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const auto& p : places) {
        person.Walk(p);
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
