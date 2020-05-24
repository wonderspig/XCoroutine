#include <iostream>
#include "scheduler.h"
using namespace std;

int test0(void *){
	cout<<"test0 0"<<endl;
	yield;
	cout<<"test0 0"<<endl;
}

int test1(void *){
	cout<<"test1 1"<<endl;
	yield;
	cout<<"test1 1"<<endl;
}

int test2(void *){
	cout<<"test2 2"<<endl;
	yield;
	cout<<"test2 2"<<endl;
}

int main(){
	envInitialize();
	createCoroutine(test0, NULL);
	createCoroutine(test1, NULL);
	createCoroutine(test2, NULL);
	schedule();
	envDestroy();
}
