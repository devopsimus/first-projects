#include <iostream>
#include <string>
#include <gmp.h>

using namespace std;

mpz_t fact(mpz_t number) {
    if(number < 0) 
        return 0; 
    if (number == 0) 
        return 1; 
    else 
        return number * fact(number - 1); 
}

int main(int argc, char *argv[]){
    if(argc != 2){cout << "Error! \nExample: program.exe | number" << endl;}
    mpz_t number = atoi(argv[1]);
    cout << "Factorial " << " = " << fact(number) << endl << endl;
    return 0;
}