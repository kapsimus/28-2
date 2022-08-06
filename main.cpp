#include <iostream>
#include <thread>
#include <mutex>

bool stationIsFree = true;
std::mutex station_access;

void train(const int travelTime, const std::string& trainName) {
    station_access.lock();
    std::cout << "The train " << trainName << " has left. Travel time: " << travelTime << "." << std::endl;
    station_access.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(travelTime));
    station_access.lock();
    std::cout << "The train " << trainName << " arrived at the station." << std::endl;
    std::string command;
    do {
        std::cout << "Enter command (depart): " << std::endl;
        std::cin >> command;
    } while (command != "depart");
    std::cout << "The train " << trainName << " left the station." << std::endl;
    station_access.unlock();
}

int main() {
    int timeA, timeB, timeC;
    std::cout << "Enter time for train A, B, C (sec.):" << std::endl;
    std::cin >> timeA >> timeB >> timeC;
    std::thread trainA(train, timeA, "A");
    std::thread trainB(train, timeB, "B");
    std::thread trainC(train, timeC, "C");
    trainA.join();
    trainB.join();
    trainC.join();
    return 0;
}
