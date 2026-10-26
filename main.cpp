#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <fstream>

template<typename T>
T readValidation(const std::string& errorMsg, std::function<bool(const T&)> isValid);

enum class Type {
    Income,
    Expense
};

enum class Category {
    food, fees, entertainment, otherExpense,

    salary, gift, sale, otherIncome
};

struct Transaction {
    long double price;
    std::string name;
    Category category;
    Type type;
};


void showMenu();
void addCategory(Transaction& trans);
void addTransaction(std::vector<Transaction>& transactions);
void saveTransaction(std::ofstream& file, const Transaction& transaction);
void showAmount(const std::vector<Transaction>& transactions);
std::string categoryToString(Category category);
std::string typeToString(Type type);
void showTransactions(const std::vector<Transaction>& transactions);

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::ofstream file("transactions.csv", std::ios::app);
    try {
        std::cout << "===== FINANCE MANAGER =====" << std::endl;
        std::vector<Transaction> transactions; //wektor przechowujuacy transkacje
        int choose;

        do {
            showMenu();
            choose = readValidation<int> (
                "Podaj poprawna liczbe: ",
                [](const int& n) { return n >= 0 && n <= 3; }
            );

            switch(choose) {
                case 1: {
                    addTransaction(transactions);
                    saveTransaction(file, transactions.back());
                    break;
                    }
                case 2: {
                    showAmount(transactions);
                    break;
                }
                case 3: {
                    showTransactions(transactions);
                    break;
                } 

                default: {
                    break;
                }
            }

        } while(choose != 0);

    } catch(const std::runtime_error& e) {
        std::cout << '\n' << "Zakonczono: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}




//FUNCKJE

template<typename T>
T readValidation(const std::string& errorMsg, std::function<bool(const T&)> isValid) {
    std::string line;
    while(true) { 
        if(!std::getline(std::cin, line)) {                                //walidacja danych
            throw std::runtime_error("Koniec wejscia");
        }

        std::replace(line.begin(), line.end(), ',', '.');

        std::istringstream iss(line);
        T value{};
        char extra;

        if(iss >> value && !(iss >> extra) && isValid(value)) {
            return value;
        }

        std::cout << errorMsg;
    
    }
}



void showMenu() {
    std::cout << "Wybierz opcje: " << std::endl
              << "1. Dodaj transakcje" << std::endl
              << "2. Pokaz saldo" << std::endl
              << "3. Pokaz transakcje" << std::endl
              << "0. Wyjdz" << std::endl;
}

void addTransaction(std::vector<Transaction>& transactions) {

    Transaction fresh{}; //nowa transkacja

    std::cout << "Wybierz co chcesz zrobic: " << std::endl 
              << "1. Przychod" << std::endl
              << "2. Wydatek" << std::endl;

    int choice = readValidation<int> ( 
        "Wprowadz 1 lub 2: ",
        [](const int& p) { return p == 1 || p == 2;}
    );

    switch(choice) {
        case 1: {
            fresh.type = Type::Income;
            break;
        }
        case 2: {
            fresh.type = Type::Expense;
            break;
        }
    }

    std::cout << "Podaj kwote: " << std::endl;
    fresh.price = readValidation<long double>(
        "Kwota musi byc wieksza od 0. Sprobuj ponownie: ",
        [](const long double& n) { return n > 0;}
    );

    std::cout << "Dodaj opis transakcji: " << std::endl;
    std::getline(std::cin, fresh.name);

    addCategory(fresh);

    transactions.push_back(fresh);
}

void saveTransaction(std::ofstream& file, const Transaction& transaction) {
    file << std::fixed << std::setprecision(2)
         << typeToString(transaction.type)  << ";"
         << categoryToString(transaction.category) << ";"
         << transaction.price << ";"
         << transaction.name << std::endl;
}

void showAmount(const std::vector<Transaction>& transactions) {
    long double przychody = 0;
    long double wydatki = 0;

    for(size_t i = 0; i < transactions.size(); ++i) {
        if(transactions[i].type == Type::Income) przychody += transactions[i].price;
        else wydatki += transactions[i].price;
    }

    std::cout << '\n' << "Twoje saldo wynosi: " << przychody - wydatki << " zloty" << std::endl;
    std::cout << '\n' << "Twoje przychody wynosza: " << przychody << " zloty" << std::endl;
    std::cout << '\n' << "Twoje wydatki wynosza: " << wydatki << " zloty" << std::endl;
}

void addCategory(Transaction& trans) {

    if(trans.type == Type::Expense) {
        std::cout << "Dodaj kategorie: " << std::endl;
        std::cout << "1. Jedzenie" << std::endl
                << "2. Oplaty" << std::endl
                << "3. Rozrywka" << std::endl
                << "4. Inne" << std::endl;

        int categoryChoice = readValidation<int> (
            "Podaj poprawny numer: ",
            [](const int& n) { return n >= 1 && n <= 4; }
        );


        switch(categoryChoice) {
            case 1: {
                trans.category = Category::food;
                break;
            }
            case 2: {
                trans.category = Category::fees;
                break;
            }
            case 3: {
                trans.category = Category::entertainment;
                break;
            }
            case 4: {
                trans.category = Category::otherExpense;
                break;
            }
        }
    }
    else if(trans.type == Type::Income) {
        std::cout << "Dodaj kategorie: " << std::endl;
        std::cout << "1. Wyplata" << std::endl
                << "2. Prezent" << std::endl
                << "3. Sprzedaz" << std::endl
                << "4. Inne" << std::endl;

        int categoryChoice = readValidation<int> (
            "Podaj poprawny numer: ",
            [](const int& n) { return n >= 1 && n <= 4; }
        );


        switch(categoryChoice) {
            case 1: {
                trans.category = Category::salary;
                break;
            }
            case 2: {
                trans.category = Category::gift;
                break;
            }
            case 3: {
                trans.category = Category::sale;
                break;
            }
            case 4: {
                trans.category = Category::otherIncome;
                break;
            }
        }
    }
}

std::string categoryToString(Category category) {
    switch(category) {
        case Category::food:
            return "Jedzenie";
        
        case Category::fees:
            return "Oplaty";
        
        case Category::entertainment:
            return "Rozrywka";
        
        case Category::otherExpense:
            return "Inne";

        case Category::salary:
            return "Wyplata";
        
        case Category::gift:
            return "Prezent";
        
        case Category::sale:
            return "Sprzedaz";
        
        case Category::otherIncome:
            return "Inne";
    }

    return "Nieznana";
}

std::string typeToString(Type type) {
    switch(type) {
        case Type::Income:
            return "Przychod";

        case Type::Expense:
            return "Wydatek";
    }

    return "Nieznany";
}

void showTransactions(const std::vector<Transaction>& transactions) {
    std::cout << '\n' << "Twoje transakcje sa nastepujace: " << std::endl;

    if(transactions.empty()) {
        std::cout << '\n' << "Nie masz zadnych transakcji" << std::endl;
    } else {
        for(size_t i = 0; i < transactions.size(); ++i) {
            std::cout << transactions[i].price 
            << " - " 
            << transactions[i].name 
            << " - " 
            << categoryToString(transactions[i].category)
            << " - "
            << typeToString(transactions[i].type)
            << std::endl;
        }
    }
}