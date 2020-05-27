#ifndef TIMELOCKER_QUERYSET_H
#define TIMELOCKER_QUERYSET_H

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class QuerySet {
public:
    QuerySet() = default;
    QuerySet(const QuerySet&) = delete;
    void operator=(const QuerySet&) = delete;
    void Insert(const string& key, const string& value, bool newRow=false);
    vector<map<string, string>> GetQuerySet() const;
    map<string, string> GetQuerySetRow() const;
private:
    vector<map<string, string>> _querySet;
    map<string, string> _querySetRow;
};

#endif //TIMELOCKER_QUERYSET_H
