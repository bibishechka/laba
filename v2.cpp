#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Dish {
public:
    string name;
    double price;
    int cookTime;

    Dish(const string& name, double price, int cookTime)
        : name(name), price(price), cookTime(cookTime) {}

    void display() const {
        cout << "Название: " << name << "\n"
             << "Цена: " << fixed << setprecision(2) << price << "\n"
             << "Время приготовления: " << cookTime << " минут\n";
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
    return a.price < b.price;
}

void readDishesFromFile(const string& filename, vector<Dish>& dishes) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл " << filename << "\n";
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        try {
            Dish myDish = parseDish(line);
            dishes.push_back(myDish);
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n";
        }
    }
    inputFile.close();
}

void displaySortedDishes(const vector<Dish>& dishes) {
    cout << "\nБлюда отсортированные по цене:\n";
    for (const auto& dish : dishes) {
        dish.display();
        cout << "---------------------\n";
    }
}

void calculateMaxDishes(const vector<Dish>& dishes, int availableTime) {
    cout << "\nмаксимальное количество блюд за " << availableTime << " минут: " endl;
    double totalPrice = 0;
    int count = 0;

    for (const auto& dish : dishes) {
        if (dish.cookTime <= availableTime) {
            dish.display();
            totalPrice += dish.price;
            count++;
            availableTime -= dish.cookTime;
        }
        if (availableTime <= 0) break;
    }
    //kveufof
    //lcmkajuhifh
    cout << "всего блюд: " << count << endl;
    cout << "общий доход: " << fixed << setprecision(2) << totalPrice << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    vector<Dish> dishes;
    readDishesFromFile("in.txt", dishes);

    sort(dishes.begin(), dishes.end(), compareByPrice);
    
    displaySortedDishes(dishes);

    int availableTime;
    cout << "Введите доступное время для приготовления блюд (в минутах): ";
    cin >> availableTime;

    calculateMaxDishes(dishes, availableTime);

    return 0;
}
