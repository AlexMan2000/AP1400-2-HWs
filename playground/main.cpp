#include <vector>
#include <iostream>

using Matrix = std::vector<std::vector<double>>;

int CONSTANT_NUM = 9000;

int main() {
    std::vector<double> temp(2, 5);
    for (double t: temp) {
        std::cout << t << std::endl;
    }
}