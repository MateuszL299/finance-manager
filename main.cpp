#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <functional>

template<typename T>
T readValidation(const std::string& errorMsg, std::function<bool(const T&)> isValid) {
    T value;
    while(true) { 
        std::cin >> value;
        if(std::cin.fail() || !isValid(value)) {                                //walidacja danych
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << '\n' << errorMsg;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

enum class Type {
    Income,
    Expense
};

enum class Category {
    food,
    fees,
    entertainment,
    other
};

struct Transaction {
    long double price;
    std::string name;
    Category category;
    Type type;
};


void showMenu();
void addCategory(Transaction& trans);

void addTransaction(std::vector<Transaction>& transactions) {

    Transaction fresh; //nowa transkacja

    fresh.price = readValidation<long double>(
        "Kwota musi byc wieksza od 0. Sprobuj ponownie: ",
        [](const long double& n) { return n > 0;}
    );

    std::cout << "Dodaj opis transakcji: " << std::endl;
    std::getline(std::cin, fresh.name);

    addCategory(fresh);

    transactions.push_back(fresh);
}

std::string categoryToString(Category category) {
    switch(category) {
        case Category::food:
            return "Jedzenie";
        
        case Category::fees:
            return "Oplaty";
        
        case Category::entertainment:
            return "Rozrywka";
        
        case Category::other:
            return "Inne";
    }

    return "Nieznana";
}

int main() {

    std::cout << "===== FINANCE MANAGER =====" << std::endl;
    showMenu();

    std::vector<Transaction> transactions; //wektor przechowujuacy transkacje

    int choose;
    long double saldo = 0;
    long double przychody = 0;
    long double wydatki = 0;

    do {
        choose = readValidation<int> (
            "Podaj poprawna liczbe: ",
            [](const int& n) { return n >= 0 && n <= 4; }
        );

        switch(choose) {
            case 1: {
                std::cout << "Podaj kwote przychodu: " << std::endl;

                addTransaction(transactions);

                saldo += transactions.back().price;
                przychody += transactions.back().price;
        
                break;
            }
            case 2: {
                std::cout << '\n' << "Podaj kwota wydatku: " << std::endl;
                
                addTransaction(transactions);

                saldo -= transactions.back().price;
                wydatki += transactions.back().price;

                break;
            }
            case 3: {
                std::cout << '\n' << "Twoje saldo wynosi: " << saldo << " zloty" << std::endl;
                std::cout << '\n' << "Twoje przychody wynosza: " << przychody << " zloty" << std::endl;
                std::cout << '\n' << "Twoje wydatki wynosza: " << wydatki << " zloty" << std::endl;
                break;
            }
            case 4: {
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
                        << std::endl;
                    }
                }
                break;
            }

            default: {
                break;
            }
        }

        showMenu();

    } while(choose != 0);

    return 0;
}



void showMenu() {
    std::cout << "Choose an option: " << std::endl
              << "1. Dodaj przychod" << std::endl
              << "2. Dodaj wydatek" << std::endl
              << "3. Pokaz saldo" << std::endl
              << "4. Pokaz transkacje" << std::endl
              << "0. Wyjdz" << std::endl;
}

void addCategory(Transaction& trans) {

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
            trans.category = Category::other;
            break;
        }
    }
}