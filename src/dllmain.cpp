#include "windows.h"
#include <iostream>
#include <d3d9.h>
#include <d3d9types.h>


#include "classes.h"

using namespace std;

void MainThread(LPVOID)
{
	AllocConsole();
	SetConsoleTitle("MyConsole");
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	while (1)
	{
		if (GetAsyncKeyState(VK_NUMPAD5))
		{
			CGameLogic* pGameLogic = CGameLogic::GetInstance();
			if (pGameLogic)
			{
				BaseEntity* pLocalPlayer = pGameLogic->GetLocalPlayer();
				if (pLocalPlayer)
				{
					EntityContainer* pEntityCont = EntityContainer::GetInstance();
					if (pEntityCont)
					{
						cout << pEntityCont->EntityCount;
						if (pEntityCont->BaseEntitysArray)
						{
							for (int Counter = 0; Counter < pEntityCont->EntityCount; Counter++)
							{
								BaseEntity* pEntity = pEntityCont->BaseEntitysArray[Counter];
								if (pEntity)
								{
									//cout << "---------------\nPlayer: " << Counter << " " << pEntity->Name << "\n";
									Bone* pBone = pEntity->pBone;
									if (pBone)
									{
										D3DVECTOR Coord = pBone->Coord;
										cout << "---------------\nPlayer: " << Counter << " " << pEntity->Name << " health: "
											<< pEntity->CurrentHealth << "\n" << "x: " << Coord.x << " y: " << Coord.y << " z: " << Coord.z << "\n-------end-------\n";
									}
								}
							}
							Aimer*pAim = Aimer::GetInstance();
							if (pAim)
							{
								cout << "-------\nCurrent Yaw: " << pAim->Yaw << " Pitch: " << pAim->Pitch << "\n";
								pAim->Pitch = 0;
								pAim->Yaw = 0;
								cout<<"Changed Yaw:" << pAim->Yaw << " Pitch: " << pAim->Pitch << "\n--------\n";
							}
							Camera *pCam = Camera::GetInstance();
							if (pCam)
							{
								cout << "----------------\nCamera Position x:" << pCam->CamPos.x <<" y : " << pCam->CamPos.y << " z : " << pCam->CamPos.z << "\n--------\n";
							}
						}
					}
				}
			}
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_NUMPAD6))
		{

		}
		else if (GetAsyncKeyState(VK_NUMPAD7))
		{

		}

		Sleep(5);
	}
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

