# TLogger

**TLogger**는 `fmt` 라이브러리를 기반으로 한 가볍고 직관적인 C++ 인터페이스 기반 로깅 시스템입니다. 게임 엔진이나 대규모 솔루션에서 유연하게 연동할 수 있도록 설계되었습니다.

---

## 🚀 주요 특징

- **고성능 로깅**: `fmt` 라이브러리를 활용하여 빠르고 타입 안정적인 문자열 포매팅을 지원합니다.
- **인터페이스 기반 설계**: `ILogger` 인터페이스를 통해 로깅 구현체를 유연하게 교체하거나 확장할 수 있습니다.
- **CMake 빌드 시스템**: 표준화된 배포(dist) 구조를 제공하며, 환경에 구속받지 않는 빌드 자동화를 지원합니다.
- **DLL 아키텍처**: Shared Library 형태의 DLL 배포를 지원하여 프로젝트 간 결합도를 낮췄습니다.
- **유니코드 및 최신 규격 지원**: MSVC 환경에서 UTF-8 인코딩을 지원하며 C++17 표준을 준수합니다.

---

## 🛠 사전 요구 사항

빌드를 위해 다음 도구들이 설치되어 있어야 합니다:

* **C++ 컴파일러**: C++17 이상 지원 (Visual Studio 2022 권장)
* **CMake**: 버전 3.16 이상
* **Git**: 외부 의존성 라이브러리(`fmt`)를 불러오기 위해 필요

---

## 📦 프로젝트 구조

```text
TLogger/
├── TLogger/           # 로깅 라이브러리 핵심 소스 코드
├── LoggerTest/        # 기능 검증용 테스트 어플리케이션
├── External/          # 외부 라이브러리 소스 (FetchContent로 관리)
├── dist/              # 배포용 SDK (빌드 및 설치 후 생성됨)
└── CMakeLists.txt     # 프로젝트 루트 CMake 설정 파일
```
---

## 🔨 빌드 및 설치 방법

### 1. 저장소 클론

```bash
git clone [https://github.com/your-username/TLogger.git](https://github.com/your-username/TLogger.git)
cd TLogger
```

### 2. 프로젝트 구성 및 빌드 (CLI)

``` bash
# 빌드용 폴더 생성
mkdir Build
cd Build

# 프로젝트 구성 (Visual Studio 솔루션 생성)
cmake ..

# 빌드 실행 (Release 모드)
cmake --build . --config Release
```

### 3. 배포용 SDK 설치 (Install)
빌드가 완료된 후, 필요한 헤더와 바이너리만 추출하여 배포용 구조를 만들려면 다음 명령어를 입력하세요.
``` bash
cmake --install . --config Release
```

실행이 완료되면 루트의 `/dist` 폴더 안에 사용 가능한 `bin`, `lib`, `include` 폴더가 생성됩니다.

---

