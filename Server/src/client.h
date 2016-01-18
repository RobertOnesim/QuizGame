#ifndef _client_h_
#define _client_h_

#include <iostream>

#include <cstdio>
#include <cstdlib>

#define MAX_NAME_LENGHT 20

using namespace std;

class Client{

    private:
        char *name;
        int id,score;

        //socket
        int sock;
    public:
        Client();
        void SetName(const char *name);
        void SetId(int id);
        void SetScore(int score);
        void SetSock(int sock);
        int getId();
        int getSock();
        int getScore();
        char* getName();
};

#endif // _client_h_
