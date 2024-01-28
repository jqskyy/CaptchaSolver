#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

struct Account {
    std::string login;
    std::string passwd;
    int level = 1;
    int exp = 0;
    double balance = 0;
    int correctCaptcha = 0;
    int wrongCaptcha = 0;
    int allCaptcha = 0;
    std::vector<double> ratesPerCaptcha = {0.0001, 0.00015, 0.000185, 0.0002, 0.00024, 0.000275, 0.00035, 0.0005, 0.001, 0.00175};


    void levelUp() {
        if(exp >= calcRequiredExp()) {
            level++;
            exp = 0;
        }
    }

    int calcRequiredExp() const {
        return level;
    }

    double calcRatePerCaptcha() const {
        switch(level) {
            case 1:
                return ratesPerCaptcha.at(0);
            case 2:
                return ratesPerCaptcha.at(1);
            case 3:
                return ratesPerCaptcha.at(2);
            case 4:
                return ratesPerCaptcha.at(3);
            case 5:
                return ratesPerCaptcha.at(4);
            case 6:
                return ratesPerCaptcha.at(5);
            case 7:
                return ratesPerCaptcha.at(6);
            case 8:
                return ratesPerCaptcha.at(7);
            case 9:
                return ratesPerCaptcha.at(8);
            case 10:
                return ratesPerCaptcha.at(9);
            default:
                throw std::runtime_error("Invalid level!");
        }
    };

};

void displayMenu(Account &acc) {
    std::cout << "====================== MENU ======================" << std::endl;
    std::cout << "Poziom: " << acc.level << std::endl;
    std::cout << "Doswiadczenie: " << acc.exp << "   (Doswiadczenie wymagane do awansu poziomu: " << acc.calcRequiredExp() << ")" << std::endl;
    std::cout << "Saldo: " << acc.balance << " pln" << std::endl;
    std::cout << "Stawka: " << acc.calcRatePerCaptcha() << " pln" << std::endl << std::endl;

    std::cout << "[1] Rozwiaz captche" << std::endl;
    std::cout << "[2] Sprawdz stawki" << std::endl;
    std::cout << "[3] Statystyki" << std::endl;
    std::cout << "[4] Wyloguj" << std::endl;
    std::cout << "====================== MENU ======================" << std::endl;
}

void displayStatistics(Account &acc) {
    if(acc.correctCaptcha != 0 && acc.wrongCaptcha != 0) {
        std::cout << std::endl << "====================== STATYSTYKI ======================" << std::endl;
        std::cout << "Poprawne captcha: " << acc.correctCaptcha;
        std::cout << "   (" << round((static_cast<double>(acc.correctCaptcha) / acc.allCaptcha) * 100) << "%)" << std::endl;

        std::cout << "Bledne captcha: " << acc.wrongCaptcha;
        std::cout << "     (" << round((static_cast<double>(acc.wrongCaptcha) / acc.allCaptcha) * 100) << "%)" << std::endl;

        std::cout << "Wszystkie captcha: " << acc.allCaptcha << std::endl;
        std::cout << "====================== STATYSTYKI ======================" << std::endl;


    } else if(acc.correctCaptcha != 0 && acc.wrongCaptcha == 0) {
        std::cout << std::endl << "====================== STATYSTYKI ======================" << std::endl;
        std::cout << "Poprawne captcha: " << acc.correctCaptcha;
        std::cout << "   (" << round((static_cast<double>(acc.correctCaptcha) / acc.allCaptcha) * 100) << "%)" << std::endl;

        std::cout << "Bledne captcha: " << acc.wrongCaptcha << std::endl << std::endl;

        std::cout << "Wszystkie captcha: " << acc.allCaptcha << std::endl;
        std::cout << "====================== STATYSTYKI ======================" << std::endl;


    } else if(acc.wrongCaptcha != 0 && acc.correctCaptcha == 0) {
        std::cout << std::endl << "====================== STATYSTYKI ======================" << std::endl;
        std::cout << "Poprawne captcha: " << acc.correctCaptcha << std::endl;

        std::cout << "Bledne captcha: " << acc.wrongCaptcha;
        std::cout << "     (" << round((static_cast<double>(acc.wrongCaptcha) / acc.allCaptcha) * 100) << "%)" << std::endl;

        std::cout << "Wszystkie captcha: " << acc.allCaptcha << std::endl;
        std::cout << "====================== STATYSTYKI ======================" << std::endl;


    } else {
        std::cout << std::endl << "====================== STATYSTYKI ======================" << std::endl;
        std::cout << "Poprawne captcha: " << acc.correctCaptcha << std::endl;

        std::cout << "Bledne captcha: " << acc.wrongCaptcha << std::endl;

        std::cout << "Wszystkie captcha: " << acc.allCaptcha << std::endl;
        std::cout << "====================== STATYSTYKI ======================" << std::endl;
    }
}

void displayRatesPerCaptcha(Account &acc) {
    int counter = 1;

    std::cout << "================= STAWKI =================" << std::endl;
    for(double rate  : acc.ratesPerCaptcha) {
        std::cout << "[" << counter << " level]" << " --- " << rate << " pln" << std::endl;
        counter++;
    }
    std::cout << "================= STAWKI =================" << std::endl;
}

int choice(Account &acc) {
    displayMenu(acc);

    int userChoice;

    std::cout << "Wybierz opcje [1-4]: ";
    std::cin >> userChoice;

    return userChoice;
}

bool loggingIn(Account &acc) {
    std::string login;
    std::string passwd;

    while(true) {
        std::cout << "Podaj login: ";
        std::cin >> login;

        std::cout << "Podaj haslo: ";
        std::cin >> passwd;

        if(login == acc.login && passwd == acc.passwd) {
            std::cout << "Pomyslnie zalogowano!" << std::endl << std::endl;
            return true;
        } else {
            std::cout << "Podales nieprawidlowe dane logowania!" << std::endl << std::endl;
            return false;
        }
    }
}

int quantityOfCaptcha() {
    int quantity;

    while(true) {
        std::cout << std::endl << "Ile captch chcesz rozwiazac? [1-10]: ";
        std::cin >> quantity;

        if(quantity < 1 || quantity > 10) {
            std::cout << "Prosimy wybrac ilosc captch z zakresu [1-10]" << std::endl << std::endl;
            continue;
        } else {
            return quantity;
        }
    }
}

std::string generatingCaptcha() {
    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    std::string captcha;

    int randomIndex;

    std::srand(time(0));

    for(int i = 0; i < 8; i++) {
        randomIndex = std::rand() % characters.size();
        captcha += characters[randomIndex];
    }
    return captcha;
}

std::string userCaptcha() {
    std::string captcha;

    std::cout << "Rozwiazanie: ";
    std::cin >> captcha;

    return captcha;
}

int main() {
    Account acc = {"test", "test123."};
    bool isUserLogged = loggingIn(acc);

    if(!isUserLogged) {
        std::cout << "Tresc tylko dla zalogowanych uzytkownikow!";
        std::exit(211);
    }

    while(true) {
        int userChoice = choice(acc);

        switch(userChoice) {
            case 1: {
                std::string currentCorrectCaptcha;
                std::string currentUserCaptcha;

                int quantity = quantityOfCaptcha();

                for(int i=0; i<quantity; i++) {
                    currentCorrectCaptcha = generatingCaptcha();
                    std::cout << std::endl << "CAPTCHA --->  " << currentCorrectCaptcha << std::endl;
                    currentUserCaptcha = userCaptcha();

                    if(currentCorrectCaptcha == currentUserCaptcha) {
                        std::cout << "Pomyslnie rozwiazano captche!" << std::endl;
                        acc.allCaptcha++;
                        acc.correctCaptcha++;
                        acc.exp++;
                        acc.levelUp();
                        acc.balance += acc.calcRatePerCaptcha();
                    } else {
                        std::cout << "Podana captcha jest nieprawidlowa!" << std::endl;
                        acc.allCaptcha++;
                        acc.wrongCaptcha++;
                    }
                }
                break;
            }
            case 2:
                displayRatesPerCaptcha(acc);
                break;
            case 3:
                displayStatistics(acc);
                break;
            case 4:
                std::exit(0);
            default:
                std::cout << "Nieprawidlowa wartosc! Wybierz opcje [1-4]" << std::endl << std::endl;
        }
    }
}
