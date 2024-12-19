#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
using namespace std;

struct tema {
    string name;     // Имя студента
    string nazvanie; // Название темы
    string date;     // Дата выдачи
};

// Удаление лишних пробелов
void trim(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end());
}

// Функция для проверки строки (дополнительная валидация)
bool validateLine(const string& name, const string& nazvanie, const string& date) {
    regex date_regex(R"(\d{2}\.\d{2}\.\d{4})"); // Формат DD.MM.YYYY
    if (!regex_match(date, date_regex)) {
        cout << "Ошибка: Некорректная дата: " << date << "\n";
        return false;
    }
    if (name.empty()) {
        cout << "Ошибка: Имя студента не указано.\n";
        return false;
    }
    if (nazvanie.empty()) {
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
        trim(line); // Убираем пробелы
        smatch match;
        tema obj;

        // Проверка строки на соответствие каждому формату
        if (regex_match(line, match, format1)) {
            obj.date = match[1];
            obj.nazvanie = match[2];
            obj.name = match[3];
        }
        else if (regex_match(line, match, format2)) {
            obj.name = match[1];
            obj.date = match[2];
            obj.nazvanie = match[3];
        }
        else if (regex_match(line, match, format3)) {
            obj.nazvanie = match[2];
            obj.name = match[1];
            obj.date = match[3];
        }
        else {
            cout << "Ошибка: Строка не соответствует ни одному формату: " << line << "\n";
            continue;
        }

        // Проверка корректности данных
        if (validateLine(obj.name, obj.nazvanie, obj.date)) {
            data.push_back(obj);
        }
    }
    return data;
}

// Функция для вывода данных
void printData(const vector<tema>& data) {
    if (data.empty()) {
        cout << "Данные отсутствуют или некорректны.\n";
        return;
    }

    for (const auto& entry : data) {
        cout << "Тема работы:\n";
        cout << "Имя студента: " << entry.name << "\n";
        cout << "Название темы: " << entry.nazvanie << "\n";
        cout << "Дата: " << entry.date << "\n\n";
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    string filename = "1.txt";
    vector<tema> data = readDataFromFile(filename);
    printData(data);

    return 0;
}
