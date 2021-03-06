#include "sdk.h"
#include "CSX/CSX.h"

namespace SDK
{
	cl_clientfunc_t*		g_pClient	= nullptr;
	cl_enginefunc_t*		g_pEngine	= nullptr;
	engine_studio_api_t*	g_pStudio	= nullptr;
	svc_msg_t*				g_pSvc		= nullptr;

	cl_clientfunc_t		g_Client;
	cl_enginefunc_t		g_Engine;
	engine_studio_api_t	g_Studio;

	void CopyClient()
	{
		CSX::Memory::nt_memcpy( &g_Client , g_pClient , sizeof( cl_clientfunc_t ) );
	}

	void CopyEngine()
	{
		CSX::Memory::nt_memcpy( &g_Engine , g_pEngine , sizeof( cl_enginefunc_t ) );
	}

	void CopyStudio()
	{
		CSX::Memory::nt_memcpy( &g_Studio , g_pStudio , sizeof( engine_studio_api_t ) );
	}

	bool WorldToScreen( float *pflOrigin , float *pflVecScreen )
	{
		int iResult = g_Engine.pTriAPI->WorldToScreen( pflOrigin , pflVecScreen );

		SCREENINFO g_Screen;
		g_Screen.iSize = sizeof( SCREENINFO );
		SDK::g_Engine.pfnGetScreenInfo( &g_Screen );

		if ( pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult )
		{
			pflVecScreen[0] = pflVecScreen[0] * ( g_Screen.iWidth / 2 ) + ( g_Screen.iWidth / 2 );
			pflVecScreen[1] = -pflVecScreen[1] * ( g_Screen.iHeight / 2 ) + ( g_Screen.iHeight / 2 );
			return true;
		}

		return false;
	}
}