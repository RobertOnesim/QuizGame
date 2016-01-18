#include "mythread.h"

using namespace std;

//Need to actually "allocate" static member
pthread_mutex_t MyThread::mutex;

MyThread::MyThread() {
}

int MyThread::Create(void *Callback, void *args) {
  int tret=0;

  //typecast
  tret = pthread_create(&this->tid, NULL, (void *(*)(void *))Callback, args);

  if(tret) {
    cerr << "Error while creating threads." << endl;
    return tret;
  }
  else {
    cout << "[SERVER] Thread successfully created." << endl;
    return 0;
  }
}

int MyThread::Join() {
  pthread_join(this->tid, NULL);
  return 0;
}

int MyThread::InitMutex() {

  if(pthread_mutex_init(&MyThread::mutex, NULL) < 0) {
    cerr << "Error while initializing mutex" << endl;
    return -1;
  }
  else {
    cout<<"\n" << "[SERVER] Server initialized." << endl;
    return 0;
  }
}
