#pragma once
#include <string>
#include <list>
#include <vector>
#ifdef LOGGER_EXPORTS 
#define LOGGER_DLL __declspec(dllexport)
#else
#define LOGGER_DLL __declspec(dllimport)
#endif 



/// <summary>
/// 로그를 남기는 클래스 인터페이스
/// </summary>
class ILogger
{
protected:

	/// <summary>
	/// 로그 변수를 담을 경량 구조체
	/// enum 과 union 을 활용해서 타입과 값을 저장한다.
	/// </summary>
	struct LogArg
	{
		enum class Type
		{
			NONE,
			Int,
			Uint,
			Float,
			Double,
			String,
			WString,
			LongLong,
			Ulonglong,
			Ptr,
			Bool,
		};

		Type m_type;
		union
		{
			int m_int;
			unsigned int m_uint;
			float m_float;
			double m_double;
			long long m_longlong;
			unsigned long long m_ulonglong;
			const wchar_t* m_wstring;
			uintptr_t m_ptr;
			bool m_bool;
		};

		// 다양한 타입에 대한 생성자 (템플릿 인자 전달용)
		LogArg() : m_type(Type::NONE), m_int(0) {}
		LogArg(int _val) : m_type(Type::Int), m_int(_val) {}
		LogArg(unsigned int _val) : m_type(Type::Uint), m_uint(_val) {}
		LogArg(float _val) : m_type(Type::Float), m_float(_val) {}
		LogArg(double _val) : m_type(Type::Double), m_double(_val) {}
		LogArg(long long _val) : m_type(Type::LongLong), m_longlong(_val) {}
		LogArg(unsigned long long _val) : m_type(Type::Ulonglong), m_ulonglong(_val) {}
		LogArg(const wchar_t* _val) : m_type(Type::WString), m_wstring(_val) {}
		LogArg(const void* _val) : m_type(Type::Ptr), m_ptr((uintptr_t)_val) {}
		LogArg(const std::wstring& _val) : m_type(Type::WString), m_wstring(_val.c_str()) {}
		LogArg(bool _val) : m_type(Type::Bool), m_bool(_val) {}
	};

	/// <summary>
	/// 로그 모듈에 넘길 데이터 묶음본
	/// </summary>
	struct LogPacket
	{
		std::wstring m_format;
		std::vector<LogArg> m_args;

		std::vector<std::wstring> m_wstrList;

		size_t argCount;
	};


	/// <summary>
	/// 실제 로그가 쓰여지는 함수
	/// </summary>
	/// <param name="_data">로그 문자열</param>
	virtual void Write(LogPacket&& _data) = 0;

public:
	ILogger() = default;
	virtual ~ILogger() = default;

	/// <summary>
	/// 로그를 남길 스트림 추가
	/// </summary>
	/// <param name="_val">스트림</param>
	virtual void AddStream(std::wostream* _val) = 0;

	/// <summary>
	/// 대기중인 모든 로그를 출력
	/// 이 함수 실행 중에는 새로운 로그 추가 불가능
	/// </summary>
	virtual void Flush() = 0;

	/// <summary>
	/// 로그 클래스 시작
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// fmt 라이브러리를 통한 로그 함수
	/// 실제 사용될 함수
	/// </summary>
	template <typename ...Args>
	void Log(const wchar_t* _format, Args&&... _data) 
	{
		LogPacket packet;
		packet.m_format = _format;

		int dummy[] = { 0, (PushArg(packet, _data), 0)... };
		(void)dummy;

		Write(std::move(packet));
	}

private:
	template <typename T>
	void PushArg(LogPacket& p, T v)
	{
		p.m_args.push_back(LogArg(v));
	}

	void PushArg(LogPacket& p, const wchar_t* v)
	{
		p.m_wstrList.push_back(v);
		p.m_args.push_back(LogArg(p.m_wstrList.back().c_str()));
	}
};

extern "C" LOGGER_DLL ILogger* CreateLoger();