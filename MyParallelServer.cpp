//
// Created by duni on 24/01/2020.
//

#include <netinet/in.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>
#include "MyParallelServer.h"

// The function handle a client by the given ClientHandler
void runClientHandler(ClientHandler *ch, int newSocket) {
    // Handle given client's socket
    ch->handleClient(newSocket);
    close(newSocket);
}

// The function accepts clients
void acceptClients(sockaddr_in *socketAddress, ClientHandler *ch, bool *run, vector<thread> *clients,
                   MyParallelServer *thisServer) {
    int newSocket;
    int addressLength = sizeof(socketAddress);
    fd_set master_set;
    FD_ZERO(&master_set);
    FD_SET(thisServer->getServerSocket(), &master_set);
    int rc;
    struct timeval time;
    int timeout_in_seconds = 120;
    time.tv_sec = timeout_in_seconds;
    time.tv_usec = 0;
    cout << "accepting clients at port " << thisServer->getServerSocket() << endl;
    // while run is true (the function stop has not been called), continue handling the clients
    while (*run) {
        // Accept clients
        rc = select(thisServer->getServerSocket() + 1, &master_set, NULL, NULL, &time);
        if (rc > 0) {
            if ((newSocket = accept(thisServer->getServerSocket(),
                                    (struct sockaddr *) &socketAddress, (socklen_t *) &addressLength)) < 0) {
                if (errno == EWOULDBLOCK || errno == EAGAIN) {
                    thisServer->stop();
                } else {
                    perror("accept");
                    exit(1);
                }
            } else {
                time.tv_sec = 120;
                // Push to the clients vector the current client's thread
                clients->emplace_back(thread(&runClientHandler, ch, newSocket));
            }
        } else {
            cout << "Error: Server timeout" << endl;
            break;
        }
    }

    close(thisServer->getServerSocket());
}

// The function create a sockes and listens to clients
void MyParallelServer::open(int port, class ClientHandler *ch) {
    int serverFd, newSocket, readValue;
    struct sockaddr_in socketAddress, clientAddress;
    int optionNumber = 1;

    // Create socket
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_socket = serverFd;
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr *) &socketAddress, sizeof(socketAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen To clients
    if (listen(serverFd, 20) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    acceptClients(&clientAddress, ch, &run, &this->clients, this);
}

// Stop the connection with the clients
void MyParallelServer::stop() {
    this->run = false;
    for (auto &client : this->clients) {
        client.join();
    }

    this->clients.clear();
}