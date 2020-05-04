#include <iostream>
#include "storage.cpp"

int main() {
    //  строки ниже для проверки работы, позже нужно удалить, когда тесты напишу
    std::map<string, string> result;
    StorageMySQL< std::map<string,string> > database;
    database.saveData("FourthFile", "1289", "2020-03-03");
    database.saveData("FirstFile", "1289", "2020-03-03");
    database.saveData("SixthFile", "1289", "2020-03-03");
    database.saveData("SeventhFile", "1289", "2020-03-03");
    result = database.getData("FirstFile");
    cout << result["Key"] << endl;
    cout << result["Password"] << endl;
    cout << result["DeletionDate"] << endl;
    result.clear();
    result = database.getData("SeventhFile");
    cout << result["Key"] << endl;
    cout << result["Password"] << endl;
    cout << result["DeletionDate"] << endl;
    return 0;
}
