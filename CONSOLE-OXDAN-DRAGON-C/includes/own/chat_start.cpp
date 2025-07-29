#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <mutex>
#include <conio.h>  // Required for _kbhit and _getch on Windows
//#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996).

std::mutex mtx;

struct ServerDetails {
    std::string ip;
    int port;
    std::string pin;
    std::vector<SOCKET> clients;
};

std::map<std::string, ServerDetails> servers;

void broadcast(const std::string& message, SOCKET _client, ServerDetails& serverDetails) {
    std::lock_guard<std::mutex> lock(mtx);
    for (SOCKET client : serverDetails.clients) {
        if (client != _client) {
            send(client, message.c_str(), message.length(), 0);
        }
    }
}

void handleClient(SOCKET clientSocket, sockaddr_in clientAddr, ServerDetails& serverDetails) {
    char buffer[1024];
    int bytesReceived;

    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';
    std::string clientPin(buffer);
    if (clientPin != serverDetails.pin) {
        std::string response = "Invalid PIN";
        send(clientSocket, response.c_str(), response.length(), 0);
        closesocket(clientSocket);
        std::cout << "\033[0;31m[DISCONNECTED]\033[0;37m Client from IP: " << inet_ntoa(clientAddr.sin_addr) << " disconnected due to invalid PIN." << std::endl;
        return;
    }
    else {
        std::string response = "OK";
        send(clientSocket, response.c_str(), response.length(), 0);
    }

    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';
    std::string clientName(buffer);
    std::cout << clientName << " has joined the chat." << std::endl;

    bool clientConnected = true;
    while (clientConnected) {
        if (_kbhit() && _getch() == 27) {  // ESC key is pressed
            closesocket(clientSocket);
            clientConnected = false;
            check_start_start();
            break;
        }
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string message = clientName + ": " + buffer;
            std::cout << message << std::endl;
            broadcast(message, clientSocket, serverDetails);
        }
        else {
            clientConnected = false;
        }
    }

    std::cout << clientName << " has left the chat." << std::endl;
    closesocket(clientSocket);
    {
        std::lock_guard<std::mutex> lock(mtx);
        serverDetails.clients.erase(std::remove(serverDetails.clients.begin(), serverDetails.clients.end(), clientSocket), serverDetails.clients.end());
    }
}

void startServer() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    std::string ipAddress = "127.0.0.1";
    string port_2;
    std::string pin;

    std::cout << "\033[0;33mEnter port to host the server: \033[0;37m";
    std::cin >> port_2;
    std::cout << "\033[0;33mCreate PIN for this server: \033[0;37m";
    std::cin >> pin;
    //boost::to_lower(port_2);
    //boost::trim(port_2);
    //boost::to_lower(pin);
    //boost::trim(pin);
    int port = stoi(port_2);
    if (port_2 == "esc" || pin == "esc")
    {
        check_start_start();
    }
    if (std::any_of(servers.begin(), servers.end(), [&](const std::pair<std::string, ServerDetails>& s) {
        return (s.second.ip == ipAddress && s.second.port == port) || (s.second.pin == pin);
        })) {
        //std::cerr << "Error: IP, port, or PIN already in use." << std::endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!IP, Port or PIN already in use!)\n");
        printf("\033[0;37m");
        WSACleanup();
        check_start_start();
        //return;
    }

    ServerDetails serverDetails = { ipAddress, port, pin };
    servers[pin] = serverDetails;

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    serverAddr.sin_port = htons(port);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    std::cout << "\033[0;33m[LISTENING]\033[0;37m Server is listening on IP: " << ipAddress << ", PORT: " << port << ", PIN: " << pin << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        {
            std::lock_guard<std::mutex> lock(mtx);
            serverDetails.clients.push_back(clientSocket);
        }

        std::thread clientThread(handleClient, clientSocket, clientAddr, std::ref(serverDetails));
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
}

void receiveMessages(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived;

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer << std::endl;
    }
}

void startClient() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    std::string serverIp;
    string serverPort_2;
    std::string serverPin;
    std::string name;

    std::cout << "\033[0;33mEnter server IP Address: \033[0;37m";
    std::cin >> serverIp;
    std::cout << "\033[0;33mEnter server Port: \033[0;37m";
    std::cin >> serverPort_2;
    std::cout << "\033[0;33mEnter server PIN: \033[0;37m";
    std::cin >> serverPin;
    std::cout << "\033[0;33mEnter your Name: \033[0;37m";
    std::cin >> name;
    //boost::to_lower(serverIp);
    //boost::trim(serverIp);
    //boost::to_lower(serverPort_2);
    //boost::trim(serverPort_2);
    //boost::to_lower(serverPin);
    //boost::trim(serverPin);
    //boost::to_lower(name);
    //boost::trim(name);
    int serverPort = stoi(serverPort_2);
    if (serverIp == "esc" || serverPort_2 == "esc" || serverPin == "esc" || name == "esc")
    {
        check_start_start();
    }
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIp.c_str());
    serverAddr.sin_port = htons(serverPort);

    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    send(clientSocket, serverPin.c_str(), serverPin.length(), 0);
    char response[1024];
    int bytesReceived = recv(clientSocket, response, sizeof(response), 0);
    response[bytesReceived] = '\0';

    if (std::string(response) == "OK") {
        send(clientSocket, name.c_str(), name.length(), 0);

        std::thread receiveThread(receiveMessages, clientSocket);
        receiveThread.detach();

        while (true) {
            if (_kbhit() && _getch() == 27) {  // ESC key is pressed
                closesocket(clientSocket);
                check_start_start();
                break;
            }
            else {
                std::string message;
                std::getline(std::cin, message);
                if (message.empty()) continue;
                send(clientSocket, message.c_str(), message.length(), 0);
            }
        }
    }
    else {
        //std::cout << "Invalid PIN. Connection refused." << std::endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Invalid PIN!)\n");
        printf("\033[0;37m");
        closesocket(clientSocket);
        check_start_start();
    }

    WSACleanup();
}

void chat_start() {
    std::string mode;
    printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n");
    std::cout << "\033[0;33mEnter '1' to start server or '2' to start client: \033[0;37m";
    std::cin >> mode;
    //boost::to_lower(mode);
    //boost::trim(mode);
    if (mode == "1") {
        startServer();
    }
    else if (mode == "2") {
        startClient();
    }
    if (mode == "esc")
    {
        check_start_start();
    }
    else {
        //std::cout << "Invalid mode selected." << std::endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Invalid option!)\n");
        printf("\033[0;37m");
        check_start_start();
    }

    //return 0;
}
