#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <vector>

std::mutex mtx;
std::condition_variable bufferNotEmpty, bufferNotFull;

const int BUFFER_SIZE = 10;
std::queue<std::pair<int, int>> buffer; // Pair to store data and producer ID

void producerFunc(int id, int data) {
    std::unique_lock<std::mutex> lock(mtx);
    bufferNotFull.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

    buffer.push(std::make_pair(data, id));
    std::cout << "Producer " << id << ": Data " << data << " is inserted in the buffer. Empty space: "<< BUFFER_SIZE - buffer.size() << std::endl;

    std::cout << "Full space: " << buffer.size() << std::endl;
    bufferNotEmpty.notify_all();
    lock.unlock();
}

void consumerFunc(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    bufferNotEmpty.wait(lock, [] { return !buffer.empty(); });

    std::pair<int, int> item = buffer.front();
    buffer.pop();
    std::cout << "Consumer " << id << ": Consumed Data " << item.first << " from the buffer. Full space: "<< buffer.size() << std::endl;

    bufferNotFull.notify_all();
    lock.unlock();
}

int main() {
    // Simulating the input data
    std::vector<std::pair<int, int>> inputData;

    // Manually input data into the buffer
    int producerId, data;
    while (true) {
        std::cout << "Enter Producer ID and Data  ";
        std::cin >> producerId;
        if (producerId == -1) break;

        std::cin >> data;
        inputData.push_back(std::make_pair(producerId, data));
    }

    for (auto& input : inputData) {
        if (input.first == 1) {
            producerFunc(input.first, input.second);
        } else {
            producerFunc(input.first, input.second);
            consumerFunc(0);
            consumerFunc(3);
        }
    }
return 0;
}
