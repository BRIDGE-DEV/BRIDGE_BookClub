#include <iostream>

int main() {
    int *arr = new int[100];

    delete[] arr;

    std::unique_ptr<int> p = std::make_unique<int>();
    std::unique_ptr<int[]> q = std::make_unique<int[]>(100);

    std::shared_ptr<int> ps = std::make_shared<int>();
    std::shared_ptr<int[]> qs = std::make_shared<int[]>(100);
}
