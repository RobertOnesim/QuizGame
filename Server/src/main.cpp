#include <iostream>
#include "mythread.h"
#include "server.h"

using namespace std;

int main(){

    cout<<"Running...";

    Server *server;
    server= new Server();

    server->AcceptAndDispatch();

    return 0;
}
