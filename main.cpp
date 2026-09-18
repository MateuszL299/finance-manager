#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include <windows.h>
#include <limits>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::setlocale(LC_ALL, "polish");

    std::cout << "===== FINANCE MANAGER =====" << std::endl;
    std::cout << "Choose an option: " << std::endl
              << "1. Dodaj przychód" << std::endl
              << "2. Dodaj wydatek" << std::endl
              << "3. Pokaż saldo" << std::endl
              << "4. Pokaż transkacje" << std::endl
              << "0. Wyjdź" << std::endl;

    int choose;
    long double saldo = 0;
    long double przychody = 0;
    long double wydatki = 0;
    std::vector<long double> transakcje = {};
    std::vector<std::string> opisy = {};

    do {
        std::cin >> choose;

        switch(choose) {
            case 1: {
                std::cout << "Podaj kwote przychodu: " << std::endl;

                long double przychod;
                while(true){
                    std::cin >> przychod;
                    if(std::cin.fail()) {
                        std::cin.clear();

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << '\n' << "Podaj poprawną liczbę: ";
                    } else {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                }
                saldo += przychod;
                przychody += przychod;
                transakcje.push_back(przychod);
                std::cout << '\n' << "Dodaj opis transkacji: ";
                std::string nowa; //transakcja
                std::cin.ignore();
                std::getline(std::cin, nowa);
                opisy.push_back(nowa);
                

                break;
            }
            case 2: {
                std::cout << '\n' << "Podaj kwotę wydatku: " << std::endl;
                long double wydatek;
                while(true){
                    std::cin >> wydatek;
                    if(std::cin.fail()) {
                        std::cin.clear();

                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << '\n' << "Podaj poprawną liczbę: ";
                    } else {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                }
                saldo -= wydatek;
                wydatki += wydatek;
                wydatek = wydatek * (-1);
                transakcje.push_back(wydatek);

                std::cout << '\n' << "Dodaj opis transkacji: ";
                std::string nowa; //transakcja
                std::cin.ignore();
                std::getline(std::cin, nowa);
                opisy.push_back(nowa);

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

                for(int i = 0; i < transakcje.size(); ++i) {
                    if(transakcje.empty()) {
                        std::cout << '\n' << "Nie masz żadnych transakcji";
                    }
                    else std::cout << transakcje[i] << "-" << opisy[i] << std::endl;
                }
            }

        }

        std::cout << '\n' << "Choose an option: " << std::endl
              << "1. Dodaj przychód" << std::endl
              << "2. Dodaj wydatek" << std::endl
              << "3. Pokaż saldo" << std::endl
              << "4. Pokaż transkacje" << std::endl
              << "0. Wyjdź" << std::endl;

    } while(choose != 0);

    return 0;
}