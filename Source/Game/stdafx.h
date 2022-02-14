// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "targetver.h"
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/imguiinterface/CImGuiInterface.h>



#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (800)

#define SCREEN_WIDTH_F (800.f)
#define SCREEN_HEIGHT_F (800.f)


#define DRAW_LINE(aStartPosX, aStartPosY, anEndPosX, anEndPosY) Tga2D::CDebugDrawer::DrawLine({ aStartPosX, aStartPosY}, { anEndPosY, anEndPosY }, { 1.0f, 1.0f, 1.0f, 1.0f })
#define DRAW_CIRCLE(aPositionX, aPositionY, aRadius) Tga2D::CDebugDrawer::DrawCircle({ aPositionX, aPositionY }, aRadius, { 1.0f, 1.0f, 1.0f, 1.0f })

#define DRAW_BOX_WHITE(aPositionX, aPositionY, aWidth, aHeight) Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY - aHeight * .5f });
#define DRAW_BOX_WHITE_FADE(aPositionX, aPositionY, aWidth, aHeight) Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { 1.0f, 1.0f, 1.0f, 0.25f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { 1.0f, 1.0f, 1.0f, 0.25f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { 1.0f, 1.0f, 1.0f, 0.25f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { 1.0f, 1.0f, 1.0f, 0.25f });
#define DRAW_BOX_RED(aPositionX, aPositionY, aWidth, aHeight) Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { 1.0f, 0.0f, 0.0f, 0.5f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { 1.0f, 0.0f, 0.0f, 0.5f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { 1.0f, 0.0f, 0.0f, 0.5f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { 1.0f, 0.0f, 0.0f, 0.5f });
#define DRAW_BOX_YELLOW(aPositionX, aPositionY, aWidth, aHeight) Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { 1.0f, 1.0f, 0.0f, 1.0f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY - aHeight * .5f }, { aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { 1.0f, 1.0f, 0.0f, 1.0f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX + aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { 1.0f, 1.0f, 0.0f, 1.0f }); Tga2D::CDebugDrawer::DrawLine({ aPositionX - aWidth * .5f, aPositionY + aHeight * .5f }, { aPositionX - aWidth * .5f, aPositionY - aHeight * .5f }, { 1.0f, 1.0f, 0.0f, 1.0f });

#define BUFLEN 576

#include "Vector.h"
#include "InputHandler.h"
#include "NetworkManager.h"
#include "ClientManager.h"
#include "Server.h"

namespace CU = CommonUtilities;


// TODO: reference additional headers your program requires here
