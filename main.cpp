#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include <windows.h>
#include <limits>

void showMenu() {
    std::cout << "Choose an option: " << std::endl
              << "1. Dodaj przychód" << std::endl
              << "2. Dodaj wydatek" << std::endl
              << "3. Pokaż saldo" << std::endl
              << "4. Pokaż transkacje" << std::endl
              << "0. Wyjdź" << std::endl;
}

struct Transaction {
    long double price;
    std::string name;
};

void addTransaction(std::vector<Transaction>& transactions) {

    Transaction fresh; //nowa transkacja

    while(true){
        std::cin >> fresh.price;
        if(std::cin.fail()) {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << '\n' << "Podaj poprawną liczbę: ";
            }
            else if(fresh.price <= 0){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Kwota musi być większa od 0. Spróbuj ponownie: ";
            } 
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
    }

    std::cout << "Dodaj opis transakcji: " << std::endl;
    std::getline(std::cin, fresh.name);

    transactions.push_back(fresh);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::setlocale(LC_ALL, "polish");

    std::cout << "===== FINANCE MANAGER =====" << std::endl;
    showMenu();

    std::vector<Transaction> transactions; //wektor przechowujuacy transkacje

    int choose;
    long double saldo = 0;
    long double przychody = 0;
    long double wydatki = 0;

    do {
        while(true){    
            std::cin >> choose;
            if(std::cin.fail() || choose < 0 || choose > 4) {
                std::cin.clear();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << '\n' << "Podaj poprawną liczbę: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

        switch(choose) {
            case 1: {
                std::cout << "Podaj kwote przychodu: " << std::endl;

                addTransaction(transactions);

                saldo += transactions.back().price;
                przychody += transactions.back().price;
        
                break;
            }
            case 2: {
                std::cout << '\n' << "Podaj kwotę wydatku: " << std::endl;
                
                addTransaction(transactions);

                saldo -= transactions.back().price;
                wydatki += transactions.back().price;

                break;
            }
            case 3: {
                std::cout << '\n' << "Twoje saldo wynosi: " << saldo << " złoty" << std::endl;
                std::cout << '\n' << "Twoje przychody wynoszą: " << przychody << " złoty" << std::endl;
                std::cout << '\n' << "Twoje wydatki wynoszą: " << wydatki << " złoty" << std::endl;
                break;
            }
            case 4: {
                std::cout << '\n' << "Twoje transakcje są nastepujące: " << std::endl;

                if(transactions.empty()) {
                    std::cout << '\n' << "Nie masz żadnych transakcji" << std::endl;
                } else {
                    for(size_t i = 0; i < transactions.size(); ++i) {
                        std::cout << transactions[i].price << " - " << transactions[i].name << std::endl;
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