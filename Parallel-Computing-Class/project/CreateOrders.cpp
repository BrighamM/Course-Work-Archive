#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>

using namespace std;

int main(){

    srand(time(0));
    std::ofstream outfile ("UnifiedOutput.txt");
    int numberOfIncomingDeliveries = 900;

    for(int i = 0; i < numberOfIncomingDeliveries; i++) {
        outfile << rand() % 25000 << " " << rand() % 25000 << " " << (rand() % 3) + 1 << " " << i << endl;
    }

    outfile.close();

    return 0;
}