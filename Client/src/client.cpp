#include "client.h"

using namespace std;
#define WAIT 10

Client::Client(){


    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ADDRESS);
    server.sin_port = htons(PORT);

    if(connect(serverSock, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1){
        cerr<<"Error at connect()\n";
    }
    else{
        Client::ClientFlow();
    }
}
void Client::ClientFlow(){

    char buffer[MAX_STANDARD];
    int finish=0, option=0, length;

    //find client nickname
    cout<<"Hi, what's your nickname?\n";

    while(1){
        int flag = 0;
        memset(buffer , 0 ,sizeof buffer);
        cin.getline(buffer,MAX_STANDARD);
        length=strlen(buffer);
        if(write(serverSock,&length,4)<= 0){
            cerr<<"Error while writing data to server\n";
        }
        if(write(serverSock,&buffer,length)<= 0){
            cerr<<"Error while writing data to server\n";
        }

        int n = read(serverSock,&flag,4);
        if(n==0){
            cout<<"Server closed connection\n";
            finish = Client::Quit();
        }
        else if(n < 0) cerr<<"Error while reading\n";
            else{
                if(flag==1) {cout<<"Nickname already exits\n";fflush(stdout);}
                else break;
            }
    }
    Client::ShowMenu();

    while(!finish){

        cin>>option;
        if(write(serverSock, &option,4) <= 0 ){
            cerr<<"Error while writing...\n";
        }
        switch(option){
            case 1:finish=Client::StartGame(); break;
            case 2:finish=Client::Leaderboard(); break;
            case 3:finish=Client::ViewInstructions(); break;
            case 4:finish=Client::Quit(); break;
            default: cout<<"Comanda invalida, reincercati!\n";
        }
    }
}
int Client::StartGame(){
    //cout<<"Optiunea 1";
    int option;

    cout<<"Select a category:\n";
    cout<<"1.General\n2.Biology\n3.Geography\n4.Math\n5.Back\n";

    while(1){
        cin>>option;
        if(option >= 1 &&option<=5){
            if(write(serverSock,&option,4) <= 0){
                cerr<<"Error while writing..\n";
            }
            if(option==5){
                Client::ShowMenu();
                return 0;
            }
            else{
                int n,length;
                char question[MAX_QUESTIONS];
                //start the game
                for(int i=1;i<=NUMBER;i++){
                    //receiving questions
                    for(int j=1;j<=5;j++){
                        memset(question,0,sizeof question);
                        n = read(serverSock,&length,4);
                        if(n==0){
                            cout<<"Server closed connection\n";
                            return Client::Quit();
                        }
                        else if(n < 0) cerr<<"Error while reading\n";

                        //read the questions and answers
                        n = read(serverSock,&question,length);
                        if(n==0){
                            cout<<"Server closed connection\n";
                            return Client::Quit();
                        }
                        else if(n < 0) cerr<<"Error while reading\n";
                            else{
                                switch(j){
                                    case 1:cout<<question<<"\n";break;
                                    case 2:cout<<"1."<<question<<"\n";break;
                                    case 3:cout<<"2."<<question<<"\n";break;
                                    case 4:cout<<"3."<<question<<"\n";break;
                                    case 5:cout<<"4."<<question<<"\n";break;
                                    default: break;
                                }

                            }
                    }

                    //send the answer
                    fd_set input_set;
                    struct timeval timeout;
                    FD_ZERO(&input_set);
                    FD_SET(0,&input_set);
                    timeout.tv_sec=WAIT; //seconds
                    timeout.tv_usec = 0; //miliseconds
                    int readyForReading = 0 ;
                    int readBytes = 0, ans =0 ;
                    char answer[MAX_STANDARD]; memset(answer,0,sizeof answer);
                    readyForReading = select(2,&input_set,NULL,NULL,&timeout);

                    if(readyForReading == -1){
                        cerr<<"Error while reading..\n";
                    }

                    if(readyForReading){
                        readBytes = read(0,answer,MAX_STANDARD);
                        if(answer[readBytes-1]=='\n'){
                            readBytes--;
                            answer[readBytes]='\0';
                        }
                        if(readBytes == 0){
                            cout<<"You just submit no answer\n";
                            ans=0;
                            fflush(stdout);
                        }
                        else{
                            cout<<"You just submit the answer\n";
                            ans= atoi(answer);
                        }
                    }
                    else{
                        cout<<"Seconds are over - no answer submited\n";
                        fflush(stdout);
                        ans=0;
                    }
                    if(write(serverSock,&ans,4)<=0) cerr<<"Error while writing..";
                    /*while(1){
                        int ans=0;
                        cin>>ans;
                        if(ans>=1 && ans<=4){
                            if(write(serverSock,&ans,4)<=0){
                                cerr<<"Error while sending the answer..";
                            }
                            break;
                        }
                        else cout<<"Invalid answer.";
                    }*/
                }
                //finish game find score
                int score = 0;
                n = read(serverSock,&score,4);
                if(n == 0){
                    cout<<"Server closed connection\n";
                    return Client::Quit();
                }
                else if(n < 0) cerr<<"Error while reading\n";
                    else {cout<<"Your score: "<<score<<"\n"; Client::ShowMenu();return 0;}
            }
        }

        else{
            cout<<"Invalid option\n";
        }
    }

    return 0;
}
int Client::Leaderboard(){
    //cout<<"Optiunea 2";
    char leaderboard[MAX_LEADERBOARD];
    int length, option=0;
    int n = read(serverSock, &length, 4);
    memset(leaderboard,0,sizeof leaderboard);
    if(n==0){
        cout<<"Server closed connection\n";
        return Client::Quit();
    }
    else if(n < 0) cerr<<"Error while reading\n";

    //read the leaderboard
    n = read(serverSock,&leaderboard,length);
    if(n==0){
        cout<<"Server closed connection\n";
        return Client::Quit();
    }
    else if(n < 0) cerr<<"Error while reading\n";
    else{
        cout<<leaderboard;fflush(stdout);
        cout<<"1.Back\n";fflush(stdout);
        while(option!=1){
            cin>> option;
            switch(option){
                case 1: Client::ShowMenu();return 0;
                default: cout<<"Incorect option\n";
            }
        }
    }
    return 1;
}
int Client::ViewInstructions(){
    //cout<<"Optiunea 3";
    char instructions[MAX_INSTRUCTION];
    int length, option = 0;

    int n = read(serverSock, &length, 4);

    if(n==0){
        cout<<"Server closed connection\n";
        return Client::Quit();
    }
    else if(n < 0) cerr<<"Error while reading\n";

    //read the leaderboard
    n = read(serverSock,&instructions,length);
    if(n==0){
        cout<<"Server closed connection\n";
        return Client::Quit();
    }
    else if(n < 0) cerr<<"Error while reading\n";
    else{
        cout<<instructions;fflush(stdout);
        cout<<"1.Back\n"; fflush(stdout);
        while(option!=1){
            cin>> option;
            switch(option){
                case 1: Client::ShowMenu();return 0;
                default: cout<<"Incorect option\n";
            }
        }
    }
    return 1;
}
int Client::Quit(){
    //cout<<"Optiunea 4";
    close(serverSock);
    return 1;
}

void Client::ShowMenu(){
    cout<<"Select an option:\n"<<"1.Start game\n2.Leaderboard\n3.Instructions\n4.Quit\n";
}
