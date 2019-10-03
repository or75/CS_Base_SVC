#include "client.h"

vector<cl_entity_s> g_EntityList;

void DrawBox( int x , int y , int w , int h , int linewidth , int r , int g , int b , int a )
{
	SDK::g_Engine.pfnTintRGBA( x , y , w , linewidth , r , g , b , a );
	SDK::g_Engine.pfnTintRGBA( x + w - linewidth , y + linewidth , linewidth , h - linewidth , r , g , b , a );
	SDK::g_Engine.pfnTintRGBA( x , y + linewidth , linewidth , h - linewidth , r , g , b , a );
	SDK::g_Engine.pfnTintRGBA( x + linewidth , y + h - linewidth , w - linewidth * 2 , linewidth , r , g , b , a );
}

void HUD_Frame( double time )
{
	static bool FirstFrame = false;

	if ( !FirstFrame )
	{
		SDK::g_pEngine->Con_Printf( "\n\n\t\t\t[ -> CS BASE 2017 LOAD SUCCESS <- ]" );

		FirstFrame = true;
	}

	SDK::g_Client.HUD_Frame( time );
}

void HUD_Redraw( float time , int intermission )
{
	SDK::g_Client.HUD_Redraw( time , intermission );

	for each ( auto pEntity in g_EntityList )
	{
		float Screen[2];

		if ( SDK::WorldToScreen( pEntity.origin , Screen ) )
		{
			int x = (int)Screen[0];
			int y = (int)Screen[1];

			if ( x && y )
				DrawBox( x , y , 10 , 10 , 1 , 0 , 255 , 0 , 255 );
		}
	}

	g_EntityList.clear();
}

int HUD_AddEntity ( int type , struct cl_entity_s *ent , const char *modelname )
{
	int iRet = SDK::g_Client.HUD_AddEntity( type , ent , modelname );

	g_EntityList.push_back( *ent );

	return iRet;
}

void HookFunction()
{
	SDK::g_pClient->HUD_Frame = HUD_Frame;
	SDK::g_pClient->HUD_Redraw = HUD_Redraw;
	SDK::g_pClient->HUD_AddEntity = HUD_AddEntity;
}