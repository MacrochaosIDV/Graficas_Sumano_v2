#ifndef IDV_PRIMITIVE_INSTANCE_H
#define IDV_PRIMITIVE_INSTANCE_H


#include <IDVScene/IDVPrimitive.h>
#include <IDVVideo/IDVBaseDriver.h>
#include <IDV_Math.h>

#include <d3dx9math.h>

class PrimitiveInst {
	public:
		void	CreateInstance(PrimitiveBase *pPrim, XMATRIX44 *pVP) {
			pBase = pPrim;
			pViewProj = pVP;
			Visible = true;
		}

		void	TranslateAbsolute(float x, float y, float z);
		void	RotateXAbsolute(float ang);
		void	RotateYAbsolute(float ang);
		void	RotateZAbsolute(float ang);
		void	ScaleAbsolute(float sc);

		void	TranslateRelative(float x, float y, float z);
		void	RotateXRelative(float ang);
		void	RotateYRelative(float ang);
		void	RotateZRelative(float ang);
		void	ScaleRelative(float sc);

		void	SetSignature(unsigned int f);

		void	Update();
		void	Draw();

		void ToogleVisible() { Visible = !Visible; }
		void SetVisible(bool f) { Visible = f; }
		bool Visible;

		XMATRIX44		Position;
		XMATRIX44		Scale;
		XMATRIX44		RotationX;
		XMATRIX44		RotationY;
		XMATRIX44		RotationZ;
		XMATRIX44		Final;

		XMATRIX44		*pViewProj;

		PrimitiveBase	*pBase;
};


#endif
