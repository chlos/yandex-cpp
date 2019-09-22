#include "stats.h"

Stats::Stats() {
    InitMethodStats();
    InitUriStats();
}

void Stats::InitMethodStats() {
    method_stats["GET"] = 0;
    method_stats["POST"] = 0;
    method_stats["PUT"] = 0;
    method_stats["DELETE"] = 0;
    method_stats["UNKNOWN"] = 0;
}

void Stats::InitUriStats() {
    uri_stats["/"] = 0;
    uri_stats["/order"] = 0;
    uri_stats["/product"] = 0;
    uri_stats["/basket"] = 0;
    uri_stats["/help"] = 0;
    uri_stats["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
    if (method_stats.count(method) > 0) {
        ++method_stats[method];
    } else {
        ++method_stats["UNKNOWN"];
    }
}

void Stats::AddUri(string_view uri) {
    if (uri_stats.count(uri) > 0) {
        ++uri_stats[uri];
    } else {
        ++uri_stats["unknown"];
    }
}

HttpRequest ParseRequest(string_view line) {
    // "POST /order HTTP/1.1"

     HttpRequest result;

     size_t begin_method;
     size_t end_method;
     begin_method = line.find_first_not_of(' ');
     end_method = line.find_first_of(' ', begin_method);
     result.method = line.substr(begin_method, end_method - begin_method);

     size_t begin_uri;
     size_t end_uri;
     begin_uri = line.find_first_not_of(' ', end_method);
     end_uri = line.find_first_of(' ', begin_uri);
     result.uri = line.substr(begin_uri, end_uri - begin_uri);

     size_t begin_protocol;
     begin_protocol = line.find_first_not_of(' ', end_uri);
     result.protocol = line.substr(begin_protocol, line.npos);

     return result;

    //// another version:
    // HttpRequest res;

    // while (line[0] == ' ') {
    //     line.remove_prefix(1);
    // }

    // size_t pos = line.find(' ');
    // res.method = line.substr(0, pos);
    // line.remove_prefix(pos + 1);
    // pos = line.find(' ');
    // res.uri = line.substr(0, pos);
    // line.remove_prefix(pos + 1);
    // res.protocol = line.substr(0, line.npos);

    // return res;
}
