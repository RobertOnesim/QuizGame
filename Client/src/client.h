#ifndef _client_h_
#define _client_h_

#include <iostream>
#include <vector>
#include <list>

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include <netinet/in.h>

#define PORT 2016
#define ADDRESS "127.0.0.1"

#define MAX_INSTRUCTION 5000
#define MAX_STANDARD 256
#define MAX_LEADERBOARD 2000
#define MAX_QUESTIONS 2000
#define NUMBER 5

using namespace std;

class Client{

    private:
        int serverSock;
        struct sockaddr_in server;

    public:
        Client();
        void ClientFlow();
    private:
        int StartGame();
        int Leaderboard();
        int ViewInstructions();
        int Quit();
        void ShowMenu();
};

#endif // _client_h_
