#include <thread>
#include <vector>
#include <iostream>
#include <windows.h>

#include "ILogger.h"

#define THREAD_COUNT 10
#define LOG_COUNT 500

ILogger* g_logger;

void LogTestFunction(int _tid)
{
	int m_int = -1;
	unsigned int m_uint = 1;
	float m_float = 1.1f;
	double m_double = 1.1;
	long long m_longlong = -2;
	unsigned long long m_ulonglong = 2;
	const wchar_t* m_wstring = L"log test";
	uintptr_t m_ptr = (uintptr_t)(&m_int);
	bool m_bool = true;

	for (int i = 0; i < LOG_COUNT; ++i)
	{
		g_logger->Log(L"[TID: {}] Loop: {} | Int: {} | UInt: {} | Float: {:.2f} | Double: {:.2f} | LL: {} | ULL: {} | WStr: {} | Ptr: 0x{:X} | Bool: {}",
			_tid, i, m_int, m_uint, m_float, m_double, m_longlong, m_ulonglong, m_wstring, m_ptr, m_bool);
	}
}

int main()
{
#ifdef _DEBUG
	HMODULE m_dll = ::LoadLibraryA("./TLoggerD.dll");
#else
	HMODULE m_dll = ::LoadLibraryA("./TLogger.dll");
#endif
	if (nullptr == m_dll)
	{
		std::cout << "log dll is not ready yet\n";
		return 0;
	}

	g_logger = ((ILogger * (*)())::GetProcAddress(m_dll, "CreateLoger"))();

	if (nullptr == g_logger)
	{
		std::cout << "create logger fail\n";
		return 0;
	}

	g_logger->AddStream(&std::wcout);

	std::vector<std::thread> logThreads;

	unsigned long long TPS;
	unsigned long long logStart;
	unsigned long long logEnd;
	unsigned long long wirteEnd;

	QueryPerformanceFrequency((LARGE_INTEGER*)&TPS);
	QueryPerformanceCounter((LARGE_INTEGER*)&logStart);

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		logThreads.push_back(std::thread(&LogTestFunction, i));
	}
	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		logThreads[i].join();
	}
	QueryPerformanceCounter((LARGE_INTEGER*)&logEnd);

	g_logger->Flush();

	QueryPerformanceCounter((LARGE_INTEGER*)&wirteEnd);

	std::cout << "Log Thread End : " << (logEnd - logStart) / (double)TPS << "\n";
	std::cout << "Log Write End : " << (wirteEnd - logStart) / (double)TPS << "\n";

	return 0;
}