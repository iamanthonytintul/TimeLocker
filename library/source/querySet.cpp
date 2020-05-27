#include "querySet.h"

void QuerySet::Insert(const string& key, const string& value, bool newRow) {
    if (_querySetRow[key].empty()) {
        _querySetRow[key] = value;
    }
    if (newRow) {
        _querySet.resize(_querySet.size() + 1);
    }
    _querySet.back()[key] = value;
}

vector<map<string, string>> QuerySet::GetQuerySet() const {
    return _querySet;
}

map<string, string> QuerySet::GetQuerySetRow() const {
    return _querySetRow;
}

