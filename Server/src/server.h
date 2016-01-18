#ifndef _server_h_
#define _server_h_

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>


#include "mythread.h"
#include "client.h"
#include "database.h"

//database
#include <sqlite3.h>

#define PORT 2016

#define MAX_INSTRUCTION 5000
#define MAX_STANDARD 256
#define MAX_LEADERBOARD 2000
#define MAX_QUESTIONS 2000
#define NUMBER 5

using namespace std;

class Server {

  private:
    static vector<Client> clients;
    static vector<Client> leaderboard;
    //Socket stuff
    int serverSock, clientSock;
    struct sockaddr_in serverAddr, clientAddr;

  public:
    Server();
    void AcceptAndDispatch();
    static void * HandleClient(void *args);

  private:
    static int AddClient(Client *client);
    static void RemoveClient(Client *client);
    static int StartGame(Client *client);
    static int ViewLeaderboard(Client *client);
    static int SendInstructions(Client *client);
    static int PlayGame(int option, Client *client);
    static bool compareMyData(Client a, Client b){
        return a.getScore()<=b.getScore();
    }
};

#endif
