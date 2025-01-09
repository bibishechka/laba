#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>

using namespace std;

struct tema {
    string name;     
    string title;    
    string date;    
};

// Функция для проверки строки
bool validateLine(const string& name, const string& title, const string& date) {
    regex date_regex(R"(\d{2}\.\d{2}\.\d{4})"); 
    if (!regex_match(date, date_regex)) {
        cout << "Ошибка: Некорректная дата: " << date << "\n";
        return false;
    }
    if (name.empty()) {
        cout << "Ошибка: Имя студента не указано.\n";
        return false;
    }
    if (title.empty()) {
        cerr << "Ошибка: Название темы не указано.\n";
        return false;
    }
    return true;
}

// Функция для чтения данных из файла
vector<tema> readDataFromFile(const string& filename) {
    ifstream ist(filename);
    if (!ist) {
        cout << "Ошибка: Не удалось открыть файл: " << filename << "\n";
        return {};
    }

    vector<tema> data;
    string line;

    // Регулярные выражения для разных форматов
    regex format1(R"((\d{2}\.\d{2}\.\d{4})\s+(.+)\s+(.+))"); // Дата "Название" "Имя"
    regex format2(R"((.+)\s+(\d{2}\.\d{2}\.\d{4})\s+(.+))"); // "Имя" Дата "Название"
    regex format3(R"((.+)\s+(.+)\s+(\d{2}\.\d{2}\.\d{4}))"); // "Название" "Имя" Дата

    while (getline(ist, line)) {
        smatch match;
        tema obj;

        if (regex_match(line, match, format1)) {
            obj.date = match[1];
            obj.title = match[2];
            obj.name = match[3];
        }
        else if (regex_match(line, match, format2)) {
            obj.name = match[1];
            obj.date = match[2];
            obj.title = match[3];
        }
        else if (regex_match(line, match, format3)) {
            obj.title = match[2];
            obj.name = match[1];
            obj.date = match[3];
        }
        else {
            cout << "Ошибка: Строка не соответствует ни одному формату: " << line << "\n";
            continue;
        }

        // Проверка корректности данных
        if (validateLine(obj.name, obj.title, obj.date)) {
            data.push_back(obj);
        }
    }
    return data;
}

void printData(const vector<tema>& data) {
    if (data.empty()) {
        cout << "Данные отсутствуют или некорректны.\n";
        return;
    }

    for (const auto& entry : data) {
        cout << "Тема работы:\n";
        cout << "Имя студента: " << entry.name << "\n";
        cout << "Название темы: " << entry.title << "\n";
        cout << "Дата: " << entry.date << "\n\n";
    }
}

// Функция для сортировки студентов по имени
void sort_name(vector<tema>& data) {
    sort(data.begin(), data.end(), [](const tema& a, const tema& b) {
        return a.name < b.name;
        });
}

// Функция для поиска студентов по дате
void findByDate(const vector<tema>& data, const string& date) {
    bool found = false;
    for (const auto& entry : data) {
        if (entry.date == date) {
            cout << "Имя студента: " << entry.name << "\n";
            cout << "Название темы: " << entry.title << "\n";
            cout << "Дата: " << entry.date << "\n\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Студенты с датой " << date << " не найдены.\n";
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    string filename = "1.txt";
    vector<tema> data = readDataFromFile(filename);
    
    sort_name(data);
    printData(data);

    string inputDate;
    cout << "Введите дату (DD.MM.YYYY): ";
    cin >> inputDate;
    findByDate(data, inputDate);

    return 0;
}
