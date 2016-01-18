#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "server.h"
using namespace std;

#define DATABASE "Quiz.db"
//Actually allocate clients
vector<Client> Server::clients;
vector<Client> Server::leaderboard;


Database *db;
Server::Server() {


  db = new Database(DATABASE);
  //Initialize static mutex from MyThread
  MyThread::InitMutex();

  //REUSEADDR
  int yes = 1;

  //Init serverSock and start listen()
  serverSock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, 0, sizeof(sockaddr_in));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  //Avoid bind error if the socket was not close()'d last time;
  setsockopt(serverSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));

  if(bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0)
    cerr << "Failed to bind";

  listen(serverSock, 5);
}

void Server::AcceptAndDispatch() {

  Client *client;
  MyThread *thread;

  socklen_t cliSize = sizeof(sockaddr_in);

  while(1) {

      client = new Client();
	  thread = new MyThread();

      client->SetSock(accept(serverSock, (struct sockaddr *) &clientAddr, &cliSize));
	  if(client->getSock() < 0) {
	    cerr << "Error on accept";
	  }
	  else {
	    thread->Create((void *) Server::HandleClient, client);
	  }
  }
}

//Static
void *Server::HandleClient(void *args) {

    int option=0;
    //Pointer to accept()'ed Client
    Client *client = (Client *) args;

    //Add client in Static clients <vector>
    int finish=Server::AddClient(client);

    while(!finish){

        int n = read(client->getSock(),&option, 4);
        if(n == 0){
            cout<<"[SERVER] Client "<<client->getName()<<" has been disconnected..\n"; fflush(stdout);
            Server::RemoveClient(client);
            finish=1;
            break;
        }
        else if(n<=0) cerr<<"Error while reading..";
            else{
                switch(option){
                    case 1: finish=Server::StartGame(client); break;
                    case 2: finish=Server::ViewLeaderboard(client); break;
                    case 3: finish=Server::SendInstructions(client);break;
                    case 4: Server::RemoveClient(client); finish=1; break;
                    default: cout<<"[SERVER] Comanda incorecta";
                }
        }
    }
  return NULL;
}
int Server::AddClient(Client *client){

    int n, length;
    char buffer[MAX_STANDARD];
    client->SetId(Server::clients.size());
    client->SetScore(0);
    cout<<"[SERVER] Adding client with id: "<<client->getId()<<"\n";
    Server::clients.push_back(*client);

    //find name
    while(1){

        int flag=0;
        n =  read(client->getSock(),&length,4);
        if(n == 0 ){
             cout<<"[SERVER] Client "<<client->getName()<<" has been disconnected..\n"; fflush(stdout);
             Server::RemoveClient(client);
             return 1;
        }
        else if(n<0) cerr<<"Error while reading...\n";

        n =  read(client->getSock(),&buffer,length);
        if(n == 0 ){
             cout<<"[SERVER] Client "<<client->getName()<<" has been disconnected..\n"; fflush(stdout);
             return 1;
        }
        else if(n<0) cerr<<"Error while reading...\n";
            else {
                for(vector<Client>::iterator it=Server::clients.begin(); it!=Server::clients.end();++it){
                        if(strcmp(buffer,it->getName())== 0 )
                        {
                            flag=1;
                            cout<<flag;fflush(stdout);
                            if(write(client->getSock(),&flag,4)<= 0){
                                  cerr<<"Error while writing data to server\n";
                            }
                        }
                }

                if(flag==0){
                    if(write(client->getSock(),&flag,4)<= 0){
                        cerr<<"Error while writing data to server\n";
                    }
                    client->SetName(buffer);
                    break;
                }
            }
    }
    return 0;
}
void Server::RemoveClient(Client *client){

    cout<<"[SERVER] Client "<<client->getName()<<" has been removed\n"; fflush(stdout);

    int id;
    vector<Client>::iterator it;
    for(it=Server::clients.begin();it!=Server::clients.end();++it){
        if(it->getId() == client->getId()){
            Server::clients.erase(it);
            id=it->getId();
            break;
        }
    }

    for(it=Server::clients.begin();it!=Server::clients.end();++it)
        if(it->getId() > id) it->SetId(it->getId()-1);
}
int Server::StartGame(Client *client){

    cout<<"[SERVER] Client "<<client->getName()<<" has chosen option number 1\n";fflush(stdout);

    int n,option=0;
    //server's logic
    //read type of the game
    while(1){
        n = read(client->getSock(),&option,4);
        if(n == 0 ){
            cout<<"[SERVER] Client "<<client->getName()<<" has been disconnected..\n"; fflush(stdout);
            Server::RemoveClient(client);
            return 1;
        }
        else if(n<0) cerr<<"Error while reading..";
            else{
                if(option>=1 && option<=5) break;
            }
    }
    //client select option back
    if(option == 5) return 0;
    //client want to play
    client->SetScore(Server::PlayGame(option,client));
    if(client->getScore() >=0)  {
        cout<<"[SERVER] Client has "<<client->getScore()<<" points\n";
        fflush(stdout);
        int score=client->getScore();
        leaderboard.push_back(*client);
        if(write(client->getSock(),&score,4)<=0) cerr<<"Error while writing..\n";
        return 0;
    }
    else return 1;
    return 0;
}
int Server::ViewLeaderboard(Client *client){

    cout<<"[SERVER] Client "<<client->getName()<<" has chosen option number 2\n"; fflush(stdout);

    char message[MAX_LEADERBOARD], auxMessage[MAX_STANDARD];
    int poz=1;
    sort(leaderboard.begin(),leaderboard.end(),compareMyData);
    reverse(leaderboard.begin(),leaderboard.end());

    memset(message,0,sizeof message);
    if(leaderboard.size()==0) strcpy(message,"No results\n");
    else{
        for(vector<Client>::iterator it=leaderboard.begin();it!=leaderboard.end() && poz<=10;++it){
            memset(auxMessage,0,sizeof auxMessage);
            sprintf(auxMessage,"Place %d. Score %d: %s\n",poz++,it->getScore(), it->getName());
            strcat(message,auxMessage);
        }
    }
    int length = strlen(message);
    if(write(client->getSock(),&length,4)<= 0){
        cerr<<"Error while writing data to server\n";
    }
    if(write(client->getSock(),&message,length)<= 0){
        cerr<<"Error while writing data to server\n";
    }
    return 0;
}
int Server::SendInstructions(Client *client){

    cout<<"[SERVER] Client "<<client->getName()<<" has chosen option number 3\n";fflush(stdout);
    char instructions[MAX_INSTRUCTION],auxInstruc[MAX_STANDARD];
    int length;
    memset(instructions,0,sizeof instructions);
    memset(auxInstruc,0,sizeof auxInstruc);

    ifstream fin("instructions.txt");
    while(fin.getline(auxInstruc,MAX_STANDARD)){
        int auxLength = strlen(auxInstruc);
        auxInstruc[auxLength] = '\n';
        strcat(instructions,auxInstruc);
        memset(auxInstruc,0,sizeof auxInstruc);
    }
    length = strlen(instructions);
    if(write(client->getSock(),&length,4)<= 0){
        cerr<<"Error while writing data to server\n";
    }
    if(write(client->getSock(),&instructions,length)<= 0){
        cerr<<"Error while writing data to server\n";
    }
    fin.close();
    return 0;
}
int Server::PlayGame(int option, Client *client){

    char questions[MAX_QUESTIONS];
    vector<vector<string> > result;
    int score=0,length,n,ans;
    switch(option){
        case 1: result =  db->query("SELECT * from general"); break;
        case 2: result =  db->query("SELECT * from biology"); break;
        case 3: result =  db->query("SELECT * from geography"); break;
        case 4: result =  db->query("SELECT * from math"); break;
        default: break;
    }
    random_shuffle(result.begin(),result.end());
    for(int i=1;i<=NUMBER;i++){
        //int quest = rand() % mod;
        vector<string> row = result[i];
        for(int j=1;j<=5;j++){

            memset(questions,0,sizeof questions);
            strcpy(questions,row.at(j).c_str());
            length=strlen(questions);

            if(write(client->getSock(),&length,4) <=0) cerr<<"Error while writing..";
            if(write(client->getSock(),&questions,length) <=0) cerr<<"Error while writing..";
        }
        n = read(client->getSock(),&ans,4);
         if(n == 0 ){
            cout<<"[SERVER] Client "<<client->getName()<<" has been disconnected..\n"; fflush(stdout);
            Server::RemoveClient(client);
            return -1;
        }
        else if(n<0) cerr<<"Error while reading..";
        else{
            if(ans == atoi(row.at(6).c_str())) score+=10;
        }
    }
    return score;
}
