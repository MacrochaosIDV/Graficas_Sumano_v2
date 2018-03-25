#include <IDV_TestApplication.h>

#include <stdio.h>

void IDVTestApplication::InitVars() {

}

void IDVTestApplication::CreateAssets() {
	XMATRIX44 VP;

	XMATRIX44 Scale;
	XMATRIX44 View;
	XMATRIX44 Projection;
	XMatViewLookAtLH(View, XVECTOR3(0.0f, 0.0f, -10.0f), XVECTOR3(0.0f, 0.0f, 1.0f), XVECTOR3(0.0f, 1.0f, 0.0f));
	XMatPerspectiveLH(Projection, Deg2Rad(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	VP = View*Projection;
	//XMatScaling(Scale, 1.0f, 1.0f, 1.0f);
	//CnstBuffer.WVP = Scale*View*Projection;

	PrimitiveMgr = new PrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);

	int index = PrimitiveMgr->CreateMesh("Models/CerdoNuevo.X");
	MeshInst.CreateInstance(PrimitiveMgr->GetPrimitive(index), &VP);

	//D3DXMATRIX View;
	//XVECTOR4 Pos = XVECTOR4(0.0f, 1.0f, 5.0f, 0.0f);
	/*QuadInst.CreateInstance(PrimitiveMgr->GetPrimitive(index), &VP);*/
}

void IDVTestApplication::DestroyAssets() {
	delete PrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {

	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	//QuadInst.Draw();
	MeshInst.Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {

}