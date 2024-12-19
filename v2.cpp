#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // для std::sort
#include <iomanip>   // для std::setprecision

using namespace std;

class Dish {
public:
    string name;
    double price;
    int cookTime; // Изменяем тип на int для удобства

    Dish(const string& name, double price, int cookTime)
        : name(name), price(price), cookTime(cookTime) {
    }

    void display() const {
        cout << "Название: " << name << "\n";
        cout << "Цена: " << fixed << setprecision(2) << price << "\n";
        cout << "Время приготовления: " << cookTime << " минут\n";
    }
};

Dish parseDish(const string& input) {
    istringstream iss(input);
    string name;
    double price;
    int cookTime;

    getline(iss, name, '"');
    getline(iss, name, '"');
    iss >> price >> cookTime;

    return Dish(name, price, cookTime);
}

bool compareByPrice(const Dish& a, const Dish& b) {
    return a.price < b.price; // Сортировка по цене (возрастанию)
}

int main() {
    setlocale(LC_ALL, "ru");

    ifstream inputFile("in.txt");
    if (!inputFile.is_open()) {
        cerr << "не удалось открыть файл in.txt\n";
        return 1;
    }

    vector<Dish> dishes;
    string line;
    
    while (getline(inputFile, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        try {
            Dish myDish = parseDish(line);
            dishes.push_back(myDish);
        }
        catch (const exception& e) {
            cout << "ошибка: " << e.what() << "\n";
        }
    }

    inputFile.close();

    // Сортируем блюда по цене
    sort(dishes.begin(), dishes.end(), compareByPrice);

    // Выводим отсортированные блюда
    cout << "\nБлюда отсортированные по цене:\n";
    for (const auto& dish : dishes) {
        dish.display();
        cout << "---------------------\n";
    }

    // Запрашиваем у пользователя время
    int availableTime;
    cout << "Введите доступное время для приготовления блюд (в минутах): ";
    cin >> availableTime;

    // Выводим максимальное количество блюд, которые можно приготовить за указанное время
    cout << "\nМаксимальное количество блюд за " << availableTime << " минут:\n";
    int totalPrice = 0;
    int count = 0;

    for (const auto& dish : dishes) {
        if (dish.cookTime <= availableTime) {
            dish.display();
            totalPrice += dish.price; // Считаем общий доход
            count++;
            availableTime -= dish.cookTime; // Уменьшаем доступное время
        }
        if (availableTime <= 0) break; // Прекращаем, если время закончилось
    }

    cout << "Всего блюд: " << count << "\n";
    cout << "Общий доход: " << fixed << setprecision(2) << totalPrice << "\n";

    return 0;
}
