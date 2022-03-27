#include "stats.h"

/*
    const string input =
            R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";
***
Stats ServeRequests(istream& input) {
    Stats result;
    for (string line; getline(input, line); ) {
        const HttpRequest req = ParseRequest(line);
        result.AddUri(req.uri);
        result.AddMethod(req.method);
    }
    return result;
}
*/

void Stats::AddMethod(string_view method) {
    string_view wrong_method("UNKNOWN");
    if (!data_methods.count(method)) {
        method = wrong_method;
    }
    data_methods[method]++;
}
void Stats::AddUri(string_view uri) {
    string_view wrong_uri("unknown");
    if (!data_uris.count(uri)) {
        uri = wrong_uri;
    }
    data_uris[uri]++;
}
const map<string_view, int>& Stats::GetMethodStats() const {
    return data_methods;
}
const map<string_view, int>& Stats::GetUriStats() const {
    return data_uris;
}


HttpRequest ParseRequest(string_view line) {
    // HttpRequest содержит полный запрос, но разбитый на string_view method, uri, protocol
    HttpRequest result;

    // проверка на пробелы в начале запроса и удаляем, пока они есть
    while (line[0] == ' ') {
        line.remove_prefix(1);
    }

    // FIXME хорошо бы перед циклом добавить проверку на наличе запроса,
    // FIXME а то вдруг это были лишь пробелы o_O, если были, конечно..

    for (size_t parse_stage = 0; parse_stage < 3; ++parse_stage) {
        size_t space = line.find(' '); // ищем ближайшиий пробел
        switch (parse_stage) {
        case 0:
            result.method = line.substr(0, space);
            line.remove_prefix(space + 1); // удаляем кусок от 0 до space + 1
            break;
        case 1:
            result.uri = line.substr(0, space);
            line.remove_prefix(space + 1); // удаляем кусок от 0 до space + 1
            break;
        case 2:
            result.protocol = line;
            break;
        }
    }

    return result;
}
