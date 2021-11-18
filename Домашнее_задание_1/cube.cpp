#include <iostream>

int &cube(int &number);

int main() {

    int number;
    std:: cin >> number;
    int &result = number;
    std:: cout << cube(result);
    return 0;

}

int &cube(int &number) {

    number = number * number * number;
    return number;

}
