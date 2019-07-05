#include <thread>

int main() {
    uint8_t* random_num = nullptr;

    std::thread([](uint8_t* something) {
        auto x = *something; // Will crash
    }, random_num).join();

    return 0;
}
