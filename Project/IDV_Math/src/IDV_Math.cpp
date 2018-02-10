// This is the main DLL file.
#include <stdio.h>
#include <IDV_Math.h>
///////////////////////////////////////////////////////////////////////
////////////////////////// Matrix 4x4 stuffs //////////////////////////
///////////////////////////////////////////////////////////////////////

////////// Functions take Matrixes and modify then returning nothing //////////

void XMatViewLookAtLH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = lookAt - camPos;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatViewLookAtRH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = camPos - lookAt;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatPerspectiveLH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane) {
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (FarPlane - NearPlane);
	mpout.m[2][3] = 1.0;
	mpout.m[3][2] = -(NearPlane*FarPlane) / (FarPlane - NearPlane);
	mpout.m[3][3] = 0.0f;

}

void XMatPerspectiveRH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane)
{
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (NearPlane - FarPlane);
	mpout.m[2][3] = -1.0;
	mpout.m[3][2] = (NearPlane*FarPlane) / (NearPlane - FarPlane);
	mpout.m[3][3] = 0.0f;
}

void XMatOrthoLH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zf - zn);
	m.m[3][2] = -zn / (zf - zn);
	m.m[3][3] = 1.0f;
}

void XMatOrthoRH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zn - zf);
	m.m[3][2] = zn / (zn - zf);
	m.m[3][3] = 1.0f;
}

void XMATRIX44::Inverse(XMATRIX44 *o) {
#if DOUBLE_FOR_INVERSE
	XMATRIX44_64 tmp64 = XMATRIX44_64(this);
	double det =
#else
	XMATRIX44 tmp64 = *this;
	float det =
#endif
		tmp64.m11*tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m11*tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m11*tmp64.m24*tmp64.m32*tmp64.m43
		+ tmp64.m12*tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m12*tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m33*tmp64.m41
		+ tmp64.m13*tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m13*tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m13*tmp64.m24*tmp64.m31*tmp64.m42
		+ tmp64.m14*tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m14*tmp64.m23*tmp64.m32*tmp64.m41
		- tmp64.m11*tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m11*tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m11*tmp64.m24*tmp64.m33*tmp64.m42
		- tmp64.m12*tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m12*tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m12*tmp64.m24*tmp64.m31*tmp64.m43
		- tmp64.m13*tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m13*tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m32*tmp64.m41
		- tmp64.m14*tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m14*tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m14*tmp64.m23*tmp64.m31*tmp64.m42;
#if DOUBLE_FOR_INVERSE
	if (det == 0.0) {
#else
	if (det == 0.0f) {
#endif
		printf("\n\nThe Universe stopped, no det for Matrix, all ends here.\n\n");
		exit(666);
	}
#if DOUBLE_FOR_INVERSE
	det = 1.0 / det;
	XMATRIX44_64 out;
#else
	det = 1.0f / det;
	XMATRIX44 out;
#endif

	out.m11 = tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m24*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m24*tmp64.m33*tmp64.m42;
	out.m12 = tmp64.m12*tmp64.m34*tmp64.m43 + tmp64.m13*tmp64.m32*tmp64.m44 + tmp64.m14*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m33*tmp64.m44 - tmp64.m13*tmp64.m34*tmp64.m42 - tmp64.m14*tmp64.m32*tmp64.m43;
	out.m13 = tmp64.m12*tmp64.m23*tmp64.m44 + tmp64.m13*tmp64.m24*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m24*tmp64.m43 - tmp64.m13*tmp64.m22*tmp64.m44 - tmp64.m14*tmp64.m23*tmp64.m42;
	out.m14 = tmp64.m12*tmp64.m24*tmp64.m33 + tmp64.m13*tmp64.m22*tmp64.m34 + tmp64.m14*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m23*tmp64.m34 - tmp64.m13*tmp64.m24*tmp64.m32 - tmp64.m14*tmp64.m22*tmp64.m33;
	out.m21 = tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m24*tmp64.m33*tmp64.m41 - tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m24*tmp64.m31*tmp64.m43;
	out.m22 = tmp64.m11*tmp64.m33*tmp64.m44 + tmp64.m13*tmp64.m34*tmp64.m41 + tmp64.m14*tmp64.m31*tmp64.m43 - tmp64.m11*tmp64.m34*tmp64.m43 - tmp64.m13*tmp64.m31*tmp64.m44 - tmp64.m14*tmp64.m33*tmp64.m41;
	out.m23 = tmp64.m11*tmp64.m24*tmp64.m43 + tmp64.m13*tmp64.m21*tmp64.m44 + tmp64.m14*tmp64.m23*tmp64.m41 - tmp64.m11*tmp64.m23*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m41 - tmp64.m14*tmp64.m21*tmp64.m43;
	out.m24 = tmp64.m11*tmp64.m23*tmp64.m34 + tmp64.m13*tmp64.m24*tmp64.m31 + tmp64.m14*tmp64.m21*tmp64.m33 - tmp64.m11*tmp64.m24*tmp64.m33 - tmp64.m13*tmp64.m21*tmp64.m34 - tmp64.m14*tmp64.m23*tmp64.m31;
	out.m31 = tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m24*tmp64.m31*tmp64.m42 - tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m24*tmp64.m32*tmp64.m41;
	out.m32 = tmp64.m11*tmp64.m34*tmp64.m42 + tmp64.m12*tmp64.m31*tmp64.m44 + tmp64.m14*tmp64.m32*tmp64.m41 - tmp64.m11*tmp64.m32*tmp64.m44 - tmp64.m12*tmp64.m34*tmp64.m41 - tmp64.m14*tmp64.m31*tmp64.m42;
	out.m33 = tmp64.m11*tmp64.m22*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m41 + tmp64.m14*tmp64.m21*tmp64.m42 - tmp64.m11*tmp64.m24*tmp64.m42 - tmp64.m12*tmp64.m21*tmp64.m44 - tmp64.m14*tmp64.m22*tmp64.m41;
	out.m34 = tmp64.m11*tmp64.m24*tmp64.m32 + tmp64.m12*tmp64.m21*tmp64.m34 + tmp64.m14*tmp64.m22*tmp64.m31 - tmp64.m11*tmp64.m22*tmp64.m34 - tmp64.m12*tmp64.m24*tmp64.m31 - tmp64.m14*tmp64.m21*tmp64.m32;
	out.m41 = tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m23*tmp64.m32*tmp64.m41 - tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m23*tmp64.m31*tmp64.m42;
	out.m42 = tmp64.m11*tmp64.m32*tmp64.m43 + tmp64.m12*tmp64.m33*tmp64.m41 + tmp64.m13*tmp64.m31*tmp64.m42 - tmp64.m11*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m31*tmp64.m43 - tmp64.m13*tmp64.m32*tmp64.m41;
	out.m43 = tmp64.m11*tmp64.m23*tmp64.m42 + tmp64.m12*tmp64.m21*tmp64.m43 + tmp64.m13*tmp64.m22*tmp64.m41 - tmp64.m11*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m23*tmp64.m41 - tmp64.m13*tmp64.m21*tmp64.m42;
	out.m44 = tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m13*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m13*tmp64.m22*tmp64.m31;

	for (int i = 0; i < 16; i++) {
#if DOUBLE_FOR_INVERSE
		double val = det*out.mat[i];
		(*o).mat[i] = static_cast<float>(val);
#else
		(*o).mat[i] = det*out.mat[i];
#endif
	}
}

void XMatMultiply(XMATRIX44 &outM, const XMATRIX44 &inputA, const XMATRIX44 &inputB) {
	memset(&outM.m[0], 0, sizeof(outM));
	outM.m11 = (inputA.m11*inputB.m11 + inputA.m12*inputB.m21 + inputA.m13*inputB.m31 + inputA.m14*inputB.m41);
	outM.m12 = (inputA.m11*inputB.m12 + inputA.m12*inputB.m22 + inputA.m13*inputB.m32 + inputA.m14*inputB.m42);
	outM.m13 = (inputA.m11*inputB.m13 + inputA.m12*inputB.m23 + inputA.m13*inputB.m33 + inputA.m14*inputB.m43);
	outM.m14 = (inputA.m11*inputB.m14 + inputA.m12*inputB.m24 + inputA.m13*inputB.m34 + inputA.m14*inputB.m44);

	outM.m21 = (inputA.m21*inputB.m11 + inputA.m22*inputB.m21 + inputA.m23*inputB.m31 + inputA.m24*inputB.m41);
	outM.m22 = (inputA.m21*inputB.m12 + inputA.m22*inputB.m22 + inputA.m23*inputB.m32 + inputA.m24*inputB.m42);
	outM.m23 = (inputA.m21*inputB.m13 + inputA.m22*inputB.m23 + inputA.m23*inputB.m33 + inputA.m24*inputB.m43);
	outM.m24 = (inputA.m21*inputB.m14 + inputA.m22*inputB.m24 + inputA.m23*inputB.m34 + inputA.m24*inputB.m44);

	outM.m31 = (inputA.m31*inputB.m11 + inputA.m32*inputB.m21 + inputA.m33*inputB.m31 + inputA.m34*inputB.m41);
	outM.m32 = (inputA.m31*inputB.m12 + inputA.m32*inputB.m22 + inputA.m33*inputB.m32 + inputA.m34*inputB.m42);
	outM.m33 = (inputA.m31*inputB.m13 + inputA.m32*inputB.m23 + inputA.m33*inputB.m33 + inputA.m34*inputB.m43);
	outM.m34 = (inputA.m31*inputB.m14 + inputA.m32*inputB.m24 + inputA.m33*inputB.m34 + inputA.m34*inputB.m44);

	outM.m41 = (inputA.m41*inputB.m11 + inputA.m42*inputB.m21 + inputA.m43*inputB.m31 + inputA.m44*inputB.m41);
	outM.m42 = (inputA.m41*inputB.m12 + inputA.m42*inputB.m22 + inputA.m43*inputB.m32 + inputA.m44*inputB.m42);
	outM.m43 = (inputA.m41*inputB.m13 + inputA.m42*inputB.m23 + inputA.m43*inputB.m33 + inputA.m44*inputB.m43);
	outM.m44 = (inputA.m41*inputB.m14 + inputA.m42*inputB.m24 + inputA.m43*inputB.m34 + inputA.m44*inputB.m44);
}
void XMatTranslation(XMATRIX44 & outM, const float & dx, const float & dy, const float & dz) {
	outM.m41 += dx, outM.m42 += dy, outM.m43 += dz;
}
void XMatScaling(XMATRIX44 &outM, const float &sx, const float &sy, const float &sz) {
	outM.m11 *= sx, outM.m22 *= sy, outM.m33 *= sz;
}
void XMatRotationXLH(XMATRIX44 &outM, const float &theta) {
	outM.m22 = outM.m33 = cos(theta);
	outM.m23 = sin(theta);
	outM.m32 = -outM.m23;
}
void XMatRotationYLH(XMATRIX44 &outM, const float &theta) {
	outM.m11 = outM.m33 = cos(theta);
	outM.m31 = sin(theta);
	outM.m13 = -outM.m31;
}
void XMatRotationZLH(XMATRIX44 &outM, const float &theta) {
	outM.m11 = outM.m22 = cos(theta);
	outM.m12 = sin(theta);
	outM.m21 = -outM.m12;
}
//////////////////////////////////////////////////////////////////////////
////////////////////////// Matrix 4x4 operators //////////////////////////
//////////////////////////////////////////////////////////////////////////

XMATRIX44 & XMATRIX44::operator*=(const XMATRIX44 &M)
{
	XMATRIX44 res;
	XMatMultiply(res, *this, M);
	return res;
}

XMATRIX44 XMATRIX44::operator*(const XMATRIX44 &M) const
{
	XMATRIX44 res;
	XMatMultiply(res, *this, M);
	return res;
}


//////////////////////////////////////////////////////////////////////////
////////////////////////// Vector 3 operators //////////////////////////
//////////////////////////////////////////////////////////////////////////
void XVECTOR3::Normalize(){
	float mag = x*x + y*y + z*z;
	x /= mag;
	y /= mag;
	z /= mag;
}
XVECTOR3 XVECTOR3::operator-(const XVECTOR3 & vec_other) const {
	XVECTOR3 V;
	V.x = this->x - vec_other.x;
	V.y = this->y - vec_other.y;
	V.z = this->z - vec_other.z;
	return V;
}
XVECTOR3 XVECTOR3::operator-() const
{
	return XVECTOR3();
}

void XVecDot(float &aux, const XVECTOR3 &vec_a, const XVECTOR3 &vec_b) {
	aux = vec_a.x*vec_b.x + vec_a.y*vec_b.y + vec_a.z*vec_b.z;
}

void XVecCross(XVECTOR3 &aux, const XVECTOR3 &vec_a, const XVECTOR3 &vec_b) {
	aux = { vec_a.y*vec_b.z - vec_a.z*vec_b.y,
		 vec_a.z*vec_b.x - vec_a.x*vec_b.z,
		 vec_a.x*vec_b.y - vec_a.y*vec_b.x,0 };
}
