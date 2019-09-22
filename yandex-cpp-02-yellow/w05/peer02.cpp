#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
 public:
  explicit Person(string name, string job)
      : name_(move(name)), job_(move(job)) {}

  string Name() const {
    return name_;
  }

  string Information() const {
    return job_ + ": " + Name();
  }

  virtual string Profession() const {
    return job_;
  }

  virtual void Walk(const string &destination) const {
    cout << Information() << ": " << Name() <<
          " walks to: " << destination << endl;
  }

 protected:
  string name_;
  string job_;
};

 class Student : public Person {
 public:
  Student(string name, string favourite_song)
  : Person(move(name), "Student"), favourite_song_(move(favourite_song)) {}

  void Learn() const {
    cout << Information() + " learns" << endl;
  }

   void SingSong() const {
     cout << Information() << " sings a song: " << favourite_song_ << endl;
   }

  void Walk(const string& destination) const override {
    Person::Walk(destination);
    SingSong();
  }

 private:
  string favourite_song_;
};

class Teacher : public Person {
 public:
  Teacher(string name, string subject) :
  Person(move(name), "Teacher"), subject_(move(subject)) {}

  void Teach() const {
    cout << Information() << " teaches: " << subject_ << endl;
  }

 private:
  string subject_;
};

class Policeman : public Person {
 public:
  explicit Policeman(string name) : Person(move(name), "Policeman") {}

  void Check(const Person& person) const {
    cout << Information() << " checks" << person.Profession() <<". "
    << person.Profession() << "'s name is: " << person.Name() << endl;
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
