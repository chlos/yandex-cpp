#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Human
{
public:
    Human(const string& name, const string& role) :
    name_(name),
    role_(role){

    }

    const string GetName() const{
        return name_;
    }

    const string GetRole() const{
        return role_;
    }

    string LogNameAndRole() const {
        return GetRole() + ": " + GetName();
    }

    virtual void Walk(const string& destination) const {
    cout << LogNameAndRole() << " walks to: " << destination
        << endl;
  }

private:
  const string name_;
  const string role_;
};

class Student : public Human
{
public:

    Student(const string& name, const string& song) :
    Human(name, "Student"),
    _favorite_song(song){}

    void Learn() {
        cout << LogNameAndRole()
             << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << LogNameAndRole()
             << " sings a song: "
             << _favorite_song << endl;
    }

private:
    const string _favorite_song;
};


class Teacher : public Human
{
public:

    Teacher(const string& name, const string& subject) :
    Human(name, "Teacher"),
    _subject(subject){}

    void Teach() {
        cout << LogNameAndRole() << " teaches: " << _subject << endl;
    }

private:
    const string _subject;
};


class Policeman : public Human
{
public:
    Policeman(const string& name) : Human(name, "Policeman"){}

    void Check(Human& human) {
        cout << LogNameAndRole()
        << " checks " << human.GetRole() << ". "
        << human.GetRole() << "'s name is: "
        << human.GetName() << endl;
    }
};

void VisitPlaces(Human& human, const vector<string>& places) {
    for (auto p : places) {
        human.Walk(p);
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
