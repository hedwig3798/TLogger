#pragma once
#include "ILogger.h"
#include <mutex>
#include <thread>
#include <string>
#include <iosfwd>
#include <queue>
#include <fstream>
#include "fmt\core.h"
#include "fmt\args.h"
#include "fmt\format.h"
#include "fmt\xchar.h"

/// <summary>
/// 단순 로그 시스템
/// </summary>
class TLogger :
	public ILogger
{
private:
	std::vector<std::wostream*> m_streams;
	std::queue<LogPacket> m_logQueue;
	std::mutex m_logMutex;
	std::mutex m_fileMutex;
	std::thread m_logThread;
	std::condition_variable m_cv;
	bool m_isExit;

public:
	TLogger();
	virtual ~TLogger();

	virtual void AddStream(std::wostream* _val) override { m_streams.push_back(_val); };
	virtual void Flush() override;
	virtual void Initialize() override;

protected:
	virtual void Write(LogPacket&& _data) override;

private:
	/// <summary>
	/// 큐에 저장된 로그를 가져옴
	/// </summary>
	void WriteLog();
	
	/// <summary>
	/// 로그 데이터를 실제 스트림에 푸쉬
	/// </summary>
	/// <param name="_msg"></param>
	void WriteAtStreams(LogPacket& _msg);
};
