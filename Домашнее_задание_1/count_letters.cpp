#include <iostream>

void count_letters(char str[], int& n_letters, int& n_digits, int& n_other);

int main() {

    char str[100];
    std:: cin >> str;
    int n_letters = 0,  n_digits = 0,  n_other = 0;
    count_letters(str, n_letters, n_digits, n_other);
    std:: cout << n_letters << std:: endl << n_digits << std:: endl << n_other << std:: endl;
    return 0;

}

void count_letters(char str[], int& n_letters, int& n_digits, int& n_other) {

    int i = 0;
    while(str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9')
            n_digits++;
        else if ((str[i] >= 'a' && str[i] <='z') || (str[i] >= 'A' && str[i] <='Z'))
            n_letters++;
        else
            n_other++;
        i++;
    }
}
