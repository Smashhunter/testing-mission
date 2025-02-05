// program2/main.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "lib.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
    
    if (bytesRead > 0) {
        std::string receivedData(buffer, bytesRead);
        bool isValid = lib::checkLength(receivedData);
        
        if (isValid) {
            std::cout << "Успешные данные: " << receivedData << std::endl;
        } else {
            std::cerr << "Ошибка: недопустимая длина данных" << std::endl;
        }
    }
    close(clientSocket);
}

int main() {
    int serverFd, clientSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Создание сокета
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    // Настройка параметров сокета
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Ошибка настройки сокета");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Привязка сокета к порту
    if (bind(serverFd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Ошибка привязки");
        exit(EXIT_FAILURE);
    }

    // Прослушивание порта
    if (listen(serverFd, 3) < 0) {
        perror("Ошибка прослушивания");
        exit(EXIT_FAILURE);
    }

    std::cout << "Сервер запущен. Ожидание подключений..." << std::endl;

    // Основной цикл сервера
    while (true) {
        if ((clientSocket = accept(serverFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Ошибка подключения");
            continue;
        }
        
        std::cout << "Новое подключение" << std::endl;
        handleClient(clientSocket);
    }

    return 0;
}