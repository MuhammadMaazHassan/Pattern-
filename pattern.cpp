#include <iostream>
#include <limits>


int main() {
    int n;
    std::cout << "Enter the size of the grid (n): ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    printDiamondPattern(n);

    return 0;
}

void printDiamondPattern(int n) {
    int mid = n / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j >= mid - i && j <= mid + i && i <= mid ||
                j >= i - mid && j <= n - 1 - (i - mid) && i > mid) {
                std::cout << 'x';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n'; 
    }
}
