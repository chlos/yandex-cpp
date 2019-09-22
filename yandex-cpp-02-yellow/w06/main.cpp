#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    string event;
    getline(is, event);
    for(size_t i = 0; i<event.size(); ++i) {
        if (event[0] == ' ') {
            event.erase(0, 1);
        } else {
            return event;
        }
    }
    return event;
}

void TestAll();
void TestDatabase();
void TestNodes();
void TestDb2();

int main() {
  TestAll();
  //TestDatabase();
  //TestNodes();
  //TestDb2();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}


//
// ==================================== TEST RM 1

void AssertDbPrintOutput(const Database& db, const string& hint, const vector<string> expected) {
    stringstream str;
    db.Print(str);

    string str_print;

    size_t i = 0;
    while(getline(str, str_print)) {
        stringstream msg;
        msg << hint << ' ' << i;
        AssertEqual(str_print , expected[i], msg.str());
        i++;
    }
    stringstream eof_msg;
    eof_msg << hint << " eof";
    Assert(str.eof(), eof_msg.str());
}

void TestDatabasePrint() {
  {
    Database db;
    db.Add({ 2017,1,1 }, "Holiday");
    db.Add({ 2017,1,1 }, "Holiday");
    db.Add({ 2017,1,1 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,1,1 }, "New Year");
    db.Add({ 2017,1,1 }, "New Year");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,3,8 }, "Holiday");
    db.Add({ 2017,1,1 }, "Holiday");
    db.Add({ 2017,1,1 }, "Holiday");
    db.Add({ 2017,1,1 }, "Holiday");

    AssertDbPrintOutput(db, "print value", {
            "2017-01-01 Holiday",
            "2017-01-01 New Year",
            "2017-03-08 Holiday",
            ""
    });
  }
  {
    Database db;
    stringstream str;
    db.Print(str);

    AssertDbPrintOutput(db, "print value", {
            ""
    });
  }
}

void TestDatabaseDel() {
  {
    Database db;

    db.Add({ 2017, 6, 1 }, "1st of June");
    db.Add({ 2017, 6, 2 }, "2nd of June");
    db.Add({ 2017, 6, 3 }, "3rd of June");
    db.Add({ 2017, 6, 4 }, "4th of June");
    db.Add({ 2017, 6, 5 }, "5th of June");
    db.Add({ 2017, 7, 8 }, "8th of July");
    db.Add({ 2017, 7, 8 }, "Someone's birthday");
    db.Add({ 2017, 7, 8 }, "Buy groceries");
    db.Add({ 2017, 7, 9 }, "9th of July");
    db.Add({ 2017, 7, 10 }, "10th of July");
    db.Add({ 2017, 7, 11 }, "11th of July");
    db.Add({ 2017, 7, 12 }, "12th of July");
    db.Add({ 2017, 7, 13 }, "13th of July");
    db.Add({ 2017, 7, 14 }, "14th of July");

    auto predicate = [](const Date& date, const string& event) {
        return date == Date { 2017, 7, 8 };
    };

    int removed = db.RemoveIf(predicate);
    AssertEqual(removed, 3, "delete case 1");

    AssertDbPrintOutput(db, "delete case 1 print", {
            "2017-06-01 1st of June",
            "2017-06-02 2nd of June",
            "2017-06-03 3rd of June",
            "2017-06-04 4th of June",
            "2017-06-05 5th of June",
            "2017-07-09 9th of July",
            "2017-07-10 10th of July",
            "2017-07-11 11th of July",
            "2017-07-12 12th of July",
            "2017-07-13 13th of July",
            "2017-07-14 14th of July",
            ""
    });
  }
  {
    Database db;

    db.Add({ 2017, 6, 1 }, "1st of June");
    db.Add({ 2017, 6, 2 }, "2nd of June");
    db.Add({ 2017, 6, 3 }, "3rd of June");
    db.Add({ 2017, 6, 4 }, "4th of June");
    db.Add({ 2017, 6, 5 }, "5th of June");
    db.Add({ 2017, 7, 8 }, "8th of July");
    db.Add({ 2017, 7, 8 }, "Someone's birthday");
    db.Add({ 2017, 7, 9 }, "9th of July");
    db.Add({ 2017, 7, 10 }, "10th of July");
    db.Add({ 2017, 7, 11 }, "11th of July");
    db.Add({ 2017, 7, 12 }, "12th of July");
    db.Add({ 2017, 7, 13 }, "13th of July");
    db.Add({ 2017, 7, 14 }, "14th of July");

    auto predicate = [](const Date& date, const string& event) {
        return date >= Date { 2017, 7, 1 };
    };

    int removed = db.RemoveIf(predicate);
    AssertEqual(removed, 8, "delete case 2");

    AssertDbPrintOutput(db, "delete case 2 print", {
                "2017-06-01 1st of June",
                "2017-06-02 2nd of June",
                "2017-06-03 3rd of June",
                "2017-06-04 4th of June",
                "2017-06-05 5th of June",
                ""
        });
  }
  {
    Database db;

    db.Add({ 2017, 6, 1 }, "work");
    db.Add({ 2017, 6, 1 }, "sleep");
    db.Add({ 2017, 6, 2 }, "work");
    db.Add({ 2017, 6, 2 }, "sleep");
    db.Add({ 2017, 6, 3 }, "work");
    db.Add({ 2017, 6, 3 }, "sleep");
    db.Add({ 2017, 6, 4 }, "work");
    db.Add({ 2017, 6, 4 }, "sleep");
    db.Add({ 2017, 6, 5 }, "play computer games");
    db.Add({ 2017, 6, 5 }, "sleep");
    db.Add({ 2017, 6, 6 }, "visit parents");
    db.Add({ 2017, 6, 6 }, "sleep");
    db.Add({ 2017, 6, 7 }, "work");
    db.Add({ 2017, 6, 7 }, "sleep");
    db.Add({ 2017, 6, 8 }, "sleep");

    auto predicate = [](const Date& date, const string& event) {
        return event == "work";
    };

    int removed = db.RemoveIf(predicate);
    AssertEqual(removed, 5, "delete case 3");

    AssertDbPrintOutput(db, "delete case 3 print", {
                "2017-06-01 sleep",
                "2017-06-02 sleep",
                "2017-06-03 sleep",
                "2017-06-04 sleep",
                "2017-06-05 play computer games",
                "2017-06-05 sleep",
                "2017-06-06 visit parents",
                "2017-06-06 sleep",
                "2017-06-07 sleep",
                "2017-06-08 sleep",
                ""
        });
  }
}

void TestDatabaseLast() {
  {
    Database db;

    db.Add({ 2017, 11, 21 }, "Tuesday");
    db.Add({ 2017, 11, 20 }, "Monday");
    db.Add({ 2017, 11, 21 }, "Weekly meeting");

    db.Last({ 2017, 11, 21 });
    AssertEqual(db.Last({ 2017, 11, 20 }), Entry{{ 2017, 11, 20 }, "Monday"}, "last case 1");
    AssertEqual(db.Last({ 2017, 11, 21 }), Entry{{ 2017, 11, 21 }, "Weekly meeting"}, "last case 2");
    try {
        db.Last({ 2000, 1, 1 });
        throw domain_error("last case 3: Shouldn't get here");
    } catch(const invalid_argument& e) {

    }

    auto predicate = [](const Date& date, const string& event) {
        return event == "Weekly meeting";
    };
    db.RemoveIf(predicate);
    AssertEqual(db.Last({ 2017, 11, 21 }), Entry{{ 2017, 11, 21 }, "Tuesday"}, "last case 4");
    AssertEqual(db.Last({ 9999, 12, 31 }), Entry{{ 2017, 11, 21 }, "Tuesday"}, "last case 5");

    db.Add({ 2017, 11, 21 }, "Weekly meeting");

    AssertEqual(db.Last({ 2017, 11, 21 }), Entry{{ 2017, 11, 21 }, "Weekly meeting"}, "last case 6");
    AssertEqual(db.Last({ 9999, 12, 31 }), Entry{{ 2017, 11, 21 }, "Weekly meeting"}, "last case 7");

  }
}

void TestDatabaseFind() {
  {
    Database db;

    db.Add({ 2017, 6, 1 }, "work");
    db.Add({ 2017, 6, 1 }, "sleep");
    db.Add({ 2017, 6, 2 }, "work");
    db.Add({ 2017, 6, 2 }, "sleep");
    db.Add({ 2017, 6, 3 }, "work");
    db.Add({ 2017, 6, 3 }, "sleep");
    db.Add({ 2017, 6, 4 }, "work");
    db.Add({ 2017, 6, 4 }, "sleep");
    db.Add({ 2017, 6, 5 }, "play computer games");
    db.Add({ 2017, 6, 5 }, "sleep");
    db.Add({ 2017, 6, 6 }, "visit parents");
    db.Add({ 2017, 6, 6 }, "sleep");
    db.Add({ 2017, 6, 7 }, "work");
    db.Add({ 2017, 6, 7 }, "sleep");
    db.Add({ 2017, 6, 8 }, "sleep");

    auto predicate1 = [](const Date& date, const string& event) {
        return event == "work";
    };

    vector<Entry> found1 = db.FindIf(predicate1);
    AssertEqual(found1, vector<Entry>{
        {{ 2017, 6, 1 }, "work"},
        {{ 2017, 6, 2 }, "work"},
        {{ 2017, 6, 3 }, "work"},
        {{ 2017, 6, 4 }, "work"},
        {{ 2017, 6, 7 }, "work"}
    }, "find case 1");
  }
  {
      Database db;

      db.Add({ 2017, 6, 1 }, "work");
      db.Add({ 2017, 6, 1 }, "sleep");
      db.Add({ 2017, 6, 2 }, "work");
      db.Add({ 2017, 6, 2 }, "sleep");
      db.Add({ 2017, 6, 3 }, "work");
      db.Add({ 2017, 6, 3 }, "sleep");
      db.Add({ 2017, 6, 4 }, "work");
      db.Add({ 2017, 6, 4 }, "sleep");
      db.Add({ 2017, 6, 5 }, "play computer games");
      db.Add({ 2017, 6, 5 }, "sleep");
      db.Add({ 2017, 6, 6 }, "visit parents");
      db.Add({ 2017, 6, 6 }, "sleep");
      db.Add({ 2017, 6, 7 }, "work");
      db.Add({ 2017, 6, 7 }, "sleep");
      db.Add({ 2017, 6, 8 }, "sleep");

      auto predicate1 = [](const Date& date, const string& event) {
          return event != "work";
      };

      vector<Entry> found1 = db.FindIf(predicate1);
      AssertEqual(found1, vector<Entry>{
        {{ 2017, 6, 1 }, "sleep"},
        {{ 2017, 6, 2 }, "sleep"},
        {{ 2017, 6, 3 }, "sleep"},
        {{ 2017, 6, 4 }, "sleep"},
        {{ 2017, 6, 5 }, "play computer games"},
        {{ 2017, 6, 5 }, "sleep"},
        {{ 2017, 6, 6 }, "visit parents"},
        {{ 2017, 6, 6 }, "sleep"},
        {{ 2017, 6, 7 }, "sleep"},
        {{ 2017, 6, 8 }, "sleep"}
      }, "find case 2");
    }}

void TestDatabase() {
    TestDatabasePrint();
    TestDatabaseLast();
    TestDatabaseDel();
    TestDatabaseFind();
    cout << "TestDatabase(): OK" << endl;
}


//
// ==================================== TEST NODES

class AlwaysFalseNode : public Node {
    bool Evaluate(const Date&, const std::string& event) const override {
        return false;
    }
};

void TestDateComparisonNode() {
  {
    DateComparisonNode dcn(Comparison::Equal, {2017, 11, 18});
    Assert(dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 1");
    Assert(!dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 2");
  }
  {
    DateComparisonNode dcn(Comparison::NotEqual, {2017, 11, 18});
    Assert(dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 3");
    Assert(!dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 4");
  }
  {
    DateComparisonNode dcn(Comparison::Less, {2017, 11, 18});
    Assert(dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 5");
    Assert(!dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 6");
    Assert(!dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 7");
  }
  {
    DateComparisonNode dcn(Comparison::Greater, {2017, 11, 18});
    Assert(dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 8");
    Assert(!dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 9");
    Assert(!dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 10");
  }
  {
    DateComparisonNode dcn(Comparison::LessOrEqual, {2017, 11, 18});
    Assert(dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 11");
    Assert(dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 12");
    Assert(!dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 13");
  }
  {
    DateComparisonNode dcn(Comparison::GreaterOrEqual, {2017, 11, 18});
    Assert(dcn.Evaluate(Date{2017, 11, 19}, ""), "DateComparison 14");
    Assert(dcn.Evaluate(Date{2017, 11, 18}, ""), "DateComparison 15");
    Assert(!dcn.Evaluate(Date{2017, 11, 17}, ""), "DateComparison 16");
  }
}

void TestEventComparisonNode() {
  {
    EventComparisonNode ecn(Comparison::Equal, "abc");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 1");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "cbe"), "EventComparison 2");
  }
  {
    EventComparisonNode ecn(Comparison::NotEqual, "abc");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "cde"), "EventComparison 3");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 4");
  }
  {
    EventComparisonNode ecn(Comparison::Less, "abc");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 5");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 6");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 7");
  }
  {
    EventComparisonNode ecn(Comparison::Greater, "abc");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 8");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 9");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 10");
  }
  {
    EventComparisonNode ecn(Comparison::LessOrEqual, "abc");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 11");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 12");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 13");
  }
  {
    EventComparisonNode ecn(Comparison::GreaterOrEqual, "abc");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abd"), "EventComparison 14");
    Assert(ecn.Evaluate(Date{0, 1, 1}, "abc"), "EventComparison 15");
    Assert(!ecn.Evaluate(Date{0, 1, 1}, "abb"), "EventComparison 16");
  }
}

void TestLogicalOperationNode() {
  {
    LogicalOperationNode lon(LogicalOperation::And, make_shared<EmptyNode>(), make_shared<EmptyNode>());
    Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 1");
  }
  {
    LogicalOperationNode lon(LogicalOperation::And, make_shared<AlwaysFalseNode>(), make_shared<EmptyNode>());
    Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 2");
  }
  {
    LogicalOperationNode lon(LogicalOperation::And, make_shared<EmptyNode>(), make_shared<AlwaysFalseNode>());
    Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 3");
  }
  {
    LogicalOperationNode lon(LogicalOperation::And, make_shared<AlwaysFalseNode>(), make_shared<AlwaysFalseNode>());
    Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 4");
  }
  {
    LogicalOperationNode lon(LogicalOperation::Or, make_shared<EmptyNode>(), make_shared<EmptyNode>());
    Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 5");
  }
  {
    LogicalOperationNode lon(LogicalOperation::Or, make_shared<AlwaysFalseNode>(), make_shared<EmptyNode>());
    Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 6");
  }
  {
    LogicalOperationNode lon(LogicalOperation::Or, make_shared<EmptyNode>(), make_shared<AlwaysFalseNode>());
    Assert(lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 7");
  }
  {
    LogicalOperationNode lon(LogicalOperation::Or, make_shared<AlwaysFalseNode>(), make_shared<AlwaysFalseNode>());
    Assert(!lon.Evaluate(Date{0, 1, 1}, "abc"), "LogicalOperationNode 8");
  }
}

void TestEmptyNode() {
  {
    EmptyNode en;
    Assert(en.Evaluate(Date{0, 1, 1}, "abc"), "EmptyNode 1");
    Assert(en.Evaluate(Date{2017, 11, 18}, "def"), "EmptyNode 2");
    Assert(en.Evaluate(Date{9999, 12, 31}, "ghi"), "EmptyNode 3");
  }
}

void TestNodes() {
  TestDateComparisonNode();
  TestEventComparisonNode();
  TestLogicalOperationNode();
  TestEmptyNode();
  cout << "TestNodes(): OK" << endl;
}


//
// ==================================== TEST DB 2
int DoRemove (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    return db.RemoveIf(predicate);
}

string DoFind (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    ostringstream os;
    for (const auto& entry : entries) {
        os << entry << endl;
    }
    os << entries.size();
    return os.str();
}

void TestDbAdd() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "holiday");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 holiday\n", out.str(), "several in one day");
    }
    {
        Database db;
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n", out.str(), "uniq adding");
    }
}

void TestDbFind() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, "date == 2017-01-01"), "simple find by date");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, "date < 2017-01-31"), "multiple find by date");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(event != "xmas")"), "multiple find by holiday");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year2");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, R"(date == 2017-01-07 OR event == "new year")"),
                "complex find or");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(date == 2017-01-01 AND event == "new year")"),
                    "complex find and");
        AssertEqual("0", DoFind(db, R"(date == 2017-01-09 AND event == "new year")"),
                    "complex find and, nothing");
    }
}

void TestDbLast(){
    Database db;
    db.Add({2017, 1, 1}, "new year");
    db.Add({2017, 1, 7}, "xmas");
    {
        try {
            db.Last({2016, 12, 31});
            Assert(false, "last, found no entries");
        } catch (...){
            Assert(true, "last, found no entries");

        }
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 2});
        AssertEqual("2017-01-01 new year", os.str(), "greater than date");
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 1});
        AssertEqual("2017-01-01 new year", os.str(), "eq to date");
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 10});
        AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
    }
}

void TestDbRemoveIf () {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(0, DoRemove(db, R"(event == "something")"), "Remove nothing");
        AssertEqual(1, DoRemove(db, R"(date == "2017-01-01")"), "Remove by date");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Remove by date, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(1, DoRemove(db, R"(event == "xmas")"), "Remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "new year");
        AssertEqual(2, DoRemove(db, R"(event == "new year")"), "Multiple remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
    }
}

void TestDb2() {
  TestDbAdd();
  TestDbFind();
  TestDbLast();
  TestDbRemoveIf();
  cout << "TestDb2 OK" << endl;
}
