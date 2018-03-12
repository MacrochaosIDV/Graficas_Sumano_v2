#include <IDVDefs.h>
//
#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>
//
//#include<IDVParser.h>
#include<iostream>
#include<IDV_Math.h>

IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main() {

	g_pApplication = new IDVTestApplication();
	g_pWindow = new IDVWin32Manager((IDVBaseApplication*)g_pApplication);
	g_pWindow->InitGlobalVars();
	g_pWindow->OnCreateApplication();

	g_pWindow->UpdateApplication();

	g_pWindow->OnDestroyApplication();

	delete g_pWindow;
	delete g_pApplication;


	//PrintFromLibrary();
	//ReadFile("CerdoNuevo.X");

	//XVECTOR3()
	//XMATRIX44 test_Math;

	//XMATRIX44 trasl;
	//XMATRIX44 scale;
	//XMATRIX44 rotX;
	//XMATRIX44 rotY;
	//XMATRIX44 rotZ;
	//XMATRIX44 persp;

	//XMatTranslation(trasl, 15.0f, -5.0f, 0.0f);
	//XMatRotationXLH(rotX, Deg2Rad(90.0f));
	//XMatRotationYLH(rotY, Deg2Rad(15.0f));
	//XMatRotationZLH(rotZ, Deg2Rad(120.0f));
	//XMatScaling(scale, 1.1f, 1.1f, 1.1f);
	//XMatPerspectiveLH(persp, Deg2Rad(60.0f), 1280.0f/720.0f, 1.0f, 10000.0f);

	//XMATRIX44 Final = persp*scale*rotX*rotY*rotZ*trasl;

	//std::cout << Final.m11 << "//////////" << Final.m12 << "//////////" << Final.m13 << "//////////" << Final.m14 << std::endl;
	//std::cout << Final.m21 << "//////////" << Final.m22 << "//////////" << Final.m23 << "//////////" << Final.m24 << std::endl;
	//std::cout << Final.m31 << "//////////" << Final.m32 << "//////////" << Final.m33 << "//////////" << Final.m34;
	//std::cout << Final.m41 << "//////////" << Final.m42 << "//////////" << Final.m43 << "//////////" << Final.m44;
	return 0;
}