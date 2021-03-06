// GraphicRestore.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"

#include "concrt.h"
#include "Main.h"
#include "Debug.h"
#include "FrameLimiter.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);

		Main();

		break;
	case DLL_PROCESS_DETACH:

		break;
	}

	return TRUE;
}

void Main()
{
	HANDLE hThread;

	Debug::Initialize("GraphicLog.txt");

	DEBUG << "그래픽 리스토어를 로드합니다." << std::endl;

	main = new GraphicRestore();

	DEBUG << "그래픽 리스토어 로드를 완료했습니다." << std::endl;

	hThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Timer), 0, 0, 0);

	if (hThread == NULL)
	{
		ExitProcess(GetLastError());

		DEBUG << "초기화에 실패했습니다." << std::endl;

		return;
	}

	SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST);
}

static void WINAPI Timer()
{
	while (*(reinterpret_cast<int*>(0x00B6F5F0)) == 0)
		Sleep(100);

	main->ApplyGraphicSettings();

	DEBUG << "적용 됨" << std::endl;
}
