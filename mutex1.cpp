// mutex1.cpp : main project file.

#include "stdafx.h" 
#include <windows.h>

using namespace System;
using namespace System::Threading;

ref  class ThreadExample 
{
	HANDLE ghMutex; 
public:
	~ThreadExample(){
		CloseHandle(ghMutex);
	}
	ThreadExample(){
		ghMutex = CreateMutex( 
			NULL,              // default security attributes
			FALSE,             // initially not owned
			NULL);             // unnamed mutex
	}

	void ThreadProc()
	{
		int dwWaitResult = WaitForSingleObject( 
			ghMutex,     
			INFINITE);   
		Console::WriteLine("\n*************** continued start: *************** ");
		for (int i = 0; i < 10; i++) 
		{
			Console::Write("*************** continued ");
			Console::WriteLine(i);				
		}
		Console::WriteLine("*************** continued end *************** ");
		Sleep(1000);
		ReleaseMutex(ghMutex);
		
		for (int i = 10; i < 50; i++) 
		{
			Console::Write(" " + i);			
			Sleep(0);
		}
		Console::WriteLine();
	}
};       


int main(array<System::String ^> ^args)
{
	ThreadExample^  threadExample = gcnew ThreadExample();
	Console::WriteLine("Main thread: Start a second thread.");
	
	Thread^  oThread = gcnew Thread(gcnew ThreadStart(threadExample, &ThreadExample::ThreadProc));
	Thread^  vThread = gcnew Thread(gcnew ThreadStart(threadExample, &ThreadExample::ThreadProc));
	Thread^  uThread = gcnew Thread(gcnew ThreadStart(threadExample, &ThreadExample::ThreadProc));
	Thread^  xThread = gcnew Thread(gcnew ThreadStart(threadExample, &ThreadExample::ThreadProc));

	oThread->Start();
	vThread->Start();
	uThread->Start();
	xThread->Start();
	oThread->Join();
	vThread->Join();
	uThread->Join();
	xThread->Join();
	
	Console::WriteLine("Main thread: ThreadProc.Join has returned.  Press Enter to end program.");
	Console::ReadLine();
	return 0;
}
