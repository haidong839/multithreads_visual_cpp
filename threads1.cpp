// threads1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <process.h>
#include <windows.h> 
using namespace std;

void test(void *param)
{
	cout << "In thread function" << endl;
	Sleep(1000); // sleep for 1 second
	cout << "Thread function ends" << endl;
	_endthread();
}

int _tmain(int argc, _TCHAR* argv[])
{
	char c;
	HANDLE hThread;
	for(int ii=0; ii<10; ii++){
		cout << "Starting thread" << endl;
		cout << (hThread = (HANDLE)_beginthread(test,0,NULL));
		WaitForSingleObject( hThread, INFINITE );
	}

	cout << "Main ends" << endl;
	cin>>c;
	return 0;
}

