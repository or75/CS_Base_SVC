#include "main.h"

DWORD WINAPI CheatEntry( LPVOID lpThreadParameter )
{
	if ( !CSX::Utils::IsModuleLoad( HW_DLL ) )
		return 0;

	if ( !CSX::Utils::IsModuleLoad( CLIENT_DLL ) )
		return 0;

	if ( !CSX::Utils::IsModuleLoad( GAMEUI_DLL ) )
		return 0;

	SDK::g_pClient = FindClient();

	if ( !SDK::g_pClient )
	{
		CSX::Log::LogApp::Add( "[-] Find Client Error" );
		return 0;
	}

	SDK::g_pEngine = FindEngine();

	if ( !SDK::g_pEngine )
	{
		CSX::Log::LogApp::Add( "[-] Find Engine Error" );
		return 0;
	}

	SDK::g_pStudio = FindStudio();

	if ( !SDK::g_pStudio )
	{
		CSX::Log::LogApp::Add( "[-] Find Studio Error" );
		return 0;
	}

	SDK::CopyClient();
	SDK::CopyEngine();
	SDK::CopyStudio();

	SDK::g_pSvc = FindSvc();

	if ( !SDK::g_pSvc )
	{
		CSX::Log::LogApp::Add( "[-] Find Svc Error" );
		return 0;
	}

	SVC_Init();

	CSX::Log::LogApp::Add( "g_pClient: %X" , SDK::g_pClient );
	CSX::Log::LogApp::Add( "g_pEngine: %X" , SDK::g_pEngine );
	CSX::Log::LogApp::Add( "g_pStudio: %X" , SDK::g_pStudio );
	CSX::Log::LogApp::Add( "g_pSvc: %X" , SDK::g_pSvc );

	HookFunction();

	return 0;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL , DWORD fdwReason , LPVOID lpReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hinstDLL );

		CSX::Log::LogApp::LogFile = CSX::Utils::GetModuleBaseDir( hinstDLL ) + "\\debug.log";
		DeleteFileA( CSX::Log::LogApp::LogFile.c_str() );
		CreateThread( 0 , 0 , CheatEntry , hinstDLL , 0 , 0 );
	}

	return TRUE;
}