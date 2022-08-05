#include <iostream>
#include <thread>
#include <mutex>

bool stationIsFree = true;
std::mutex station_access;

void train(const int travelTime, const std::string& trainName) {
    std::cout << "The train " << trainName << " has left. Travel time: " << travelTime << "." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(travelTime));
    station_access.lock();
    stationIsFree = false;
    std::cout << "The train " << trainName << " arrived at the station." << std::endl;
    std::string command;
    do {
        std::cout << "Enter command (depart): " << std::endl;
        std::cin >> command;
    } while (command != "depart");
    std::cout << "The train " << trainName << " left the station." << std::endl;
    stationIsFree = false;
    station_access.unlock();
}

int main() {
    int timeA, timeB, timeC;
    std::cout << "Enter time for train A, B, C (sec.):" << std::endl;
    std::cin >> timeA >> timeB >> timeC;
    std::thread trainA(train, timeA, "A");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread trainB(train, timeB, "B");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::thread trainC(train, timeC, "C");
    trainA.join();
    trainB.join();
    trainC.join();
    return 0;
}
