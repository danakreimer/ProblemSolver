//
// Created by duni on 24/01/2020.
//

#include <netinet/in.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>
#include "MyParallelServer.h"

void runClientHandler (ClientHandler* ch, int newSocket) {
    ch->handleClient(newSocket);
    close(newSocket);
}

void acceptClients(sockaddr_in* socketAddress, ClientHandler *ch, bool *run, vector<thread>* clients,
        MyParallelServer* thisServer) {
    int newSocket;
    int addressLength = sizeof(socketAddress);
    fd_set master_set;
    FD_ZERO(&master_set);
    FD_SET(thisServer->getServerSocker(), &master_set);
    int rc;
    struct timeval time;
    int timeout_in_seconds = 120;
    time.tv_sec = timeout_in_seconds;
    time.tv_usec = 0;

    cout << "accepting clients at port " << thisServer->getServerSocker() << endl;
    while (*run) {
        // Accept clients
        rc = select(thisServer->getServerSocker() + 1, &master_set, NULL, NULL, &time);
        if (rc > 0) {
            if ((newSocket = accept(thisServer->getServerSocker(),
                    (struct sockaddr *) &socketAddress, (socklen_t *) &addressLength)) < 0) {
                if (errno == EWOULDBLOCK || errno == EAGAIN) {
                    thisServer->stop();
                } else {
                    perror("accept");
                    exit(1);
                }
            } else {
                time.tv_sec = 120;
                clients->emplace_back(thread(&runClientHandler, ch, newSocket));
            }
        } else {
            cout << "Error: Server timeout" << endl;
            break;
        }
    }

    close(thisServer->getServerSocker());
}


void MyParallelServer::open(int port, class ClientHandler * ch) {
    int serverFd, newSocket, readValue;
    struct sockaddr_in socketAddress, clientAddress;
    int optionNumber = 1;

    // Create socket
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_socket = serverFd;

    // Attaching socket
//    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optionNumber, sizeof(optionNumber))) {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//
//    if (setsockopt(serverFd, SOL_SOCKET, SO_RCVTIMEO,(const char*) &time, sizeof(time)) < 0) {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }

//    bzero((char*) &socketAddress, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr *) &socketAddress, sizeof(socketAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverFd, 20) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    acceptClients(&clientAddress, ch, &run, &this->clients, this);
}

void MyParallelServer::stop() {
    this->run = false;
    for (vector<thread>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
        it->join();
    }

    this->clients.clear();
}