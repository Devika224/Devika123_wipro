#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>

// Mutex for synchronizing access to the log file
std::mutex logMutex;

// Function to write log messages to a file
void logMessage(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::ofstream logFile("shopping_log.txt", std::ios::app);
    if (logFile.is_open()) {
        auto timestamp = std::chrono::system_clock::now();
        std::time_t timestamp_c = std::chrono::system_clock::to_time_t(timestamp);
        logFile << std::ctime(&timestamp_c) << message << std::endl;
    } else {
        std::cerr << "Log file is not open." << std::endl;
    }
}

// Real-time thread function to simulate various shopping events
void shoppingEvent(const std::string& event) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    logMessage(event);
}

int main() {
    // Log user login event
    logMessage("Customer logged in");

    // Array of products to suggest
    std::vector<std::string> products = {"Gua sha tool", "Sheet masks", "Dr.sheth's sunscreen"};

    // Display the products as suggestions
    std::cout << "Products you might like:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << ". " << products[i] << std::endl;
    }

    // Handle user input for product selection
    int choice;
    std::cout << "Choose a product to buy (enter the number): ";
    std::cin >> choice;

    // Validate user input and process
    std::string chosenProduct;
    if (choice >= 1 && choice <= 3) {
        switch (choice) {
            case 3:
                chosenProduct = "Dr.sheth's sunscreen";
                break;
            case 1:
                chosenProduct = "Gua sha tool";
                break;
            case 2:
                chosenProduct = "Sheet masks";
                break;
        }
        logMessage("Customer purchased " + chosenProduct);
    } else {
        std::cout << "Invalid choice. Please choose a number between 1 and 3." << std::endl;
    }

    // Log user logout event
    logMessage("Customer logged out");

    std::cout << "Logging of events completed." << std::endl;
    return 0;
}
