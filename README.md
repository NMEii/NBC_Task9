# ChatX

Unreal Engine 5.5 기반의 멀티플레이어 채팅 시스템 예제 프로젝트입니다. C++ 및 UMG(Unreal Motion Graphics)를 활용하여 클라이언트와 서버 간의 텍스트 채팅 기능을 구현했습니다.

## 🛠 사용된 기술 (Tech Stack)
- **Engine:** Unreal Engine 5.5
- **Language:** C++ / Blueprints
- **UI:** UMG (Slate, SlateCore)
- **Network:** Server & Client RPC (Remote Procedure Call)

## 📌 주요 기능 (Features)
- **멀티플레이어 네트워크 동기화:** 
  - `ServerRPC`와 `ClientRPC`를 사용하여 채팅 메시지를 서버에서 검증하고 모든 클라이언트로 전파하는 기본적인 채팅 시스템을 구현했습니다.
- **UMG UI 시스템:** 
  - `UEditableTextBox`와 `UUserWidget` 베이스 클래스에 C++ 클래스를 바인딩하여 채팅 입력창(`WBP_ChatInput`) 및 알림창(`WBP_NotificationText`)을 구현했습니다.
- **C++ 클래스 및 블루프린트 연동:**
  - `CXPlayerController`: 채팅 메시지의 RPC 통신 및 위젯(채팅창, 텍스트 알림) 생성/관리를 담당합니다.
  - `CXChatInput`: UMG 위젯 이벤트 처리를 위한 C++ UI 클래스로, 텍스트 입력 커밋 시 컨트롤러로 이벤트를 전달합니다.
  - 이외 게임 모드(`CXGameModeBase`), 게임 스테이트(`CXGameStateBase`), 폰(`CXPawn`) 등이 구현되어 있습니다.

## 📁 프로젝트 구조 (Project Structure)
- `Source/ChatX/Game`: 게임 모드 및 게임 스테이트 클래스
- `Source/ChatX/Player`: 폰, 플레이어 컨트롤러, 플레이어 스테이트 클래스 (RPC 로직 포함)
- `Source/ChatX/UI`: 채팅 위젯 및 알림 UI 베이스 C++ 클래스
- `Content/ChatX/Blueprint`: UI 위젯, 게임 룰, 플레이어 캐릭터 등의 블루프린트 애셋 
  - `WBP_ChatInput`, `WBP_NotificationText`, `BP_PlayerController` 등
- `Content/ChatX/Maps`: 데모 맵 (`L_Chatting`)

## 🚀 실행 방법 (Getting Started)
1. 프로젝트 루트의 `ChatX.uproject`를 우클릭하여 **Generate Visual Studio project files**를 실행합니다.
2. 생성된 솔루션 파일(`ChatX.sln`)을 열고 프로젝트를 빌드합니다.
3. Unreal Editor에서 프로젝트를 실행하고, 기본 맵(`L_Chatting`)을 엽니다.
4. Net Mode를 **Play As Listen Server** 혹은 **Play As Client**로 설정하고 다수의 플레이어를 배치한 뒤 실행하여 채팅 시스템을 테스트할 수 있습니다.
