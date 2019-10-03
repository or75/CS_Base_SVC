#include "svc.h"

int* msg_readcount = nullptr;
sizebuf_t* net_message = nullptr;

void SVC_Init()
{
	DWORD dwSvcDirector = (DWORD)SDK::g_pSvc[SVC_DIRECTOR].pfnParse;

	if ( dwSvcDirector )
	{
		msg_readcount = (PINT)( *(PDWORD)( dwSvcDirector + 8 ) );
		net_message = (sizebuf_t*)( *(PDWORD)( dwSvcDirector + 15 ) - 0x8 );
	}
}

svc_func_t SVC_Hook( int svc_num , svc_func_t svc_func )
{
	svc_func_t pfnResult = SDK::g_pSvc[svc_num].pfnParse;
	SDK::g_pSvc[svc_num].pfnParse = svc_func;
	return pfnResult;
}

void* SVC_GetBuffer()
{
	return net_message->data + *msg_readcount;
}

int SVC_GetBufferSize()
{
	return net_message->cursize - *msg_readcount;
}