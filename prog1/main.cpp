// prog1/main.cpp
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include "lib.h"

std::mutex mtx;
std::condition_variable cv;
std::string shared_buffer;
bool data_ready = false;
bool program_running = true;

// Функция для проверки корректности ввода
bool isValidInput(const std::string& str) {
    if (str.empty() || str.length() > 64) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Поток 1: Ввод и обработка данных
void inputThread() {
    
    while (program_running) {
        std::string input;
        std::cout << "Введите строку (только цифры, до 64 символов): ";
        std::getline(std::cin, input);

        if (!isValidInput(input)) {
            std::cerr << "Ошибка: некорректный ввод!\n";
            continue;
        }

        lib::processString(input);

        {
            std::lock_guard<std::mutex> lock(mtx);
            shared_buffer = input;
            data_ready = true;
        }
        cv.notify_one();
    }
}

// Функция для отправки данных через сокет
void sendToProgram2(const std::string& data) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Ошибка создания сокета\n";
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Ошибка адреса\n";
        return;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Соединение с Программой 2 не установлено\n";
        close(sock);
        return;
    }

    send(sock, data.c_str(), data.size(), 0);
    close(sock);
}

// Поток 2: Обработка и отправка данных
void processingThread() {
    while (program_running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return data_ready || !program_running; });

        if (!program_running) break;

        std::string data = shared_buffer;
        shared_buffer.clear();
        data_ready = false;

        int sum = lib::calculateSum(data);
        //std::cout << "Обработанные данные: " << data << "\nСумма: " << sum << std::endl;

        lock.unlock();

        sendToProgram2(data);
    }
}

int main() {
    std::thread t1(inputThread);
    std::thread t2(processingThread);

    t1.join();
    t2.join();

    return 0;
}