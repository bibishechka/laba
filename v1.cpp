// ConsoleApplication67.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Dish {
public:
    string name;
    double price;
    string cookTime;

    Dish(const string& name, double price, const string& cookTime)
        : name(name), price(price), cookTime(cookTime) {
    }

    void display() const {
        cout << "Название: " << name << "\n";
        cout << "Цена: " << price << "\n";
        cout << "Время приготовления: " << cookTime << "\n";
    }
};



Dish parseDish(const string& input) {
    istringstream iss(input);
    string name;
    double price;
    string cookTime;


    getline(iss, name, '"');
    getline(iss, name, '"');
    iss >> price;
    iss >> cookTime;

    return Dish(name, price, cookTime);
}

int main() {
    setlocale(LC_ALL, "ru");

    ifstream inputFile("in.txt");
    if (!inputFile.is_open()) {
        cerr << "не удалось открыть файл in.txt\n";
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {

        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        try {
            Dish myDish = parseDish(line);
            myDish.display();
        }
        catch (const exception& e) {
            cout << "ошибка: " << e.what() << "\n";
        }
    }

    inputFile.close();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
