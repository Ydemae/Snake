#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

int RandomNumber(int l, int h){
    srand( time(NULL));

    int RandId = rand() % (h-l) + l;

    return RandId;
}

int main(){
    std::cout << RandomNumber(30, 60);
    std::cout << "\n";
}