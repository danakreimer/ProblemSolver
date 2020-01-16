//
// Created by duni on 12/01/2020.
//

#include "MySerialServer.h"

#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <algorithm>


MySerialServer::MySerialServer() {
    this->run = true;
}

void MySerialServer::stop() {
    this->run = false;
}

void acceptClients(bool *run, ClientHandler *ch, int serverFd, sockaddr_in* socketAddress) {
    int newSocket;
    int addressLength = sizeof(socketAddress);
    struct timeval time;
    int timeout_in_seconds = 120;
    time.tv_sec = timeout_in_seconds;

    while (run) {
        // Accept clients
        cout << "accepting clients" << endl;

        if (setsockopt(serverFd, SOL_SOCKET, SO_RCVTIMEO,(const char*) &time, sizeof(time))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if ((newSocket = accept(serverFd, (struct sockaddr *) &socketAddress, (socklen_t *) &addressLength)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        cout << "client connected, listen for messages" << endl;

        ch->handleClient(newSocket);
        close(newSocket);
    }
    close(serverFd);
}

void MySerialServer::open(int port, ClientHandler *ch) {

    int serverFd, newSocket, readValue;
    struct sockaddr_in socketAddress;
    int optionNumber = 1;
    int addressLength = sizeof(socketAddress);
    char *message;

    // Create socket
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optionNumber, sizeof(optionNumber))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr *) &socketAddress, sizeof(socketAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Open the thread
    thread threadServer(acceptClients, &run, ch, serverFd, &socketAddress);
    threadServer.join();
}
