#include <IDV_TestApplication.h>

#include <stdio.h>

void IDVTestApplication::InitVars() {

}

void IDVTestApplication::CreateAssets() {
	D3DXMATRIX VP;

	PrimitiveMgr = new PrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);

	int index = PrimitiveMgr->CreateQuad();
	QuadInst.CreateInstance(PrimitiveMgr->GetPrimitive(index), &VP);
}

void IDVTestApplication::DestroyAssets() {
	delete PrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {

	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	QuadInst.Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {

}