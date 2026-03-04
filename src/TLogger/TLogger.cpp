#include "pch.h"
#include "TLogger.h"

TLogger::TLogger()
	: m_isExit(false)
{
}

TLogger::~TLogger()
{
	m_isExit = true;
	m_cv.notify_all();

	m_logThread.join();
}

void TLogger::Flush()
{
	// 큐에 저장된 모든 로그를 전부 출력
	// 출력중에는 큐에 접근 불가능
	std::unique_lock<std::mutex> lock(m_logMutex);

	while (false == m_logQueue.empty())
	{
		LogPacket& msg = m_logQueue.front();
		WriteAtStreams(msg);
		m_logQueue.pop();
	}

	lock.unlock();
}

void TLogger::Initialize()
{
	// 로그 출력스레드 활성화
	m_logThread = std::thread(&TLogger::WriteLog, this);
	m_isExit = false;
}

void TLogger::Write(LogPacket&& _data)
{
	std::unique_lock<std::mutex> lock(m_logMutex);

	// 단순히 로그 문자열을 큐에 넣는다
	m_logQueue.push(std::move(_data));
	lock.unlock();
	m_cv.notify_one();
}

void TLogger::WriteLog()
{
	while (true)
	{
		// 큐에 접근해야 한다.
		std::unique_lock<std::mutex> logLock(m_logMutex);
		// 로그를 남길 수 있는지 확인
		m_cv.wait(logLock, [this]()
			{
				return true == m_isExit
					|| false == m_logQueue.empty();
			}
		);

		// 로그 기록이 종료되었고, 큐가 비었으면 탈출
		if (true == m_isExit
			&& true == m_logQueue.empty())
		{
			break;
		}

		// 로그 데이터를 가져오고 락을 해제한다
		LogPacket& msg = m_logQueue.front();
		m_logQueue.pop();
		logLock.unlock();

		// 로그 출력
		WriteAtStreams(msg);
	}
}

void TLogger::WriteAtStreams(LogPacket& _msg)
{
	// 입력받은 모든 스트림에 대해 로그 출력
	for(auto* stream : m_streams)
	{
		if (nullptr == stream
			|| false == stream->good())
		{
			continue;
		}

		fmt::dynamic_format_arg_store<fmt::wformat_context> store;
		for(auto& itr : _msg.m_args)
		{
			switch (itr.m_type)
			{
			case ILogger::LogArg::Type::Int:
			{
				store.push_back(itr.m_int);
				break;
			}
			case ILogger::LogArg::Type::Uint:
			{
				store.push_back(itr.m_uint);
				break;
			}
			case ILogger::LogArg::Type::Float:
			{
				store.push_back(itr.m_float);
				break;
			}
			case ILogger::LogArg::Type::Double:
			{
				store.push_back(itr.m_double);
				break;
			}
			case ILogger::LogArg::Type::WString:
			{
				std::wstring ws = itr.m_wstring;
				store.push_back(ws);
				break;
			}
			case ILogger::LogArg::Type::LongLong:
			{
				store.push_back(itr.m_longlong);
				break;
			}
			case ILogger::LogArg::Type::Ulonglong:
			{
				store.push_back(itr.m_ulonglong);
				break;
			}
			case ILogger::LogArg::Type::Ptr:
			{
				store.push_back(itr.m_ptr);
				break;
			}
			case ILogger::LogArg::Type::Bool:
			{
				store.push_back(itr.m_bool);
				break;
			}
			default:
				break;
			}
		}
		fmt::text_style ts;
		std::wstring formatMsg = fmt::vformat(ts, _msg.m_format, fmt::wformat_args(store));
		*(stream) << formatMsg << L'\n';
	}	
}
