//
//  VECTOR3D.h
//  StereoRendering
//
//  Created by Jose Maria Benito on 09/12/13.
//  Copyright (c) 2013 Jose Maria. All rights reserved.
//

#ifndef StereoRendering_VECTOR3D_h
#define StereoRendering_VECTOR3D_h

#define ABS(x) (x < 0 ? -(x) : (x))
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define TRUE  1
#define FALSE 0
#define ESC 27
#define PI 3.141592653589793238462643
#define DTOR            0.0174532925    // degrees to radians
#define RTOD            57.2957795      // radians to degrees

#include <vector>

typedef struct {
    double x,y,z;
} VECTOR3D;


typedef struct {
    double r,g,b;
} COLOUR;

typedef struct {
    VECTOR3D column0;
    VECTOR3D column1;
    VECTOR3D column2;
} MATRIX3;


typedef struct {
    float m[16];
} MATRIX4;

typedef struct {
	std::vector<VECTOR3D> P;
} CURVE;

static const COLOUR grey = {0.7,0.7,0.7};
static const COLOUR red = {1,0,0};
static const COLOUR green = {0,1,0};
static const COLOUR blue = {0,0,1};

static const COLOUR darkred = {0.6,0,0};
static const COLOUR darkgreen = {0,0.6,0};

// TODO

VECTOR3D Add(VECTOR3D a, VECTOR3D b)
{
    VECTOR3D ret;
    ret.x = a.x+b.x;
    ret.y = a.y+b.y;
    ret.z = a.z+b.z;
    return ret;
}

VECTOR3D Substract(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

VECTOR3D Multiply(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;
	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return ret;
}

VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a)
{
	VECTOR3D ret;
	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	ret.z = a.z * scalar;
	return ret;
}

double Magnitude(VECTOR3D a)
{
	double ret;
	ret = (sqrt((pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2))));
	return ret;
}

VECTOR3D Normalize(VECTOR3D a)
{
	VECTOR3D ret;
	double magn = Magnitude(a);
	ret.x = (a.x / magn);
	ret.y = (a.y / magn);
	ret.z = (a.z / magn);
	return ret;
}

VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;
	ret = {
		(a.y * b.z) - (b.y * a.z),
		(a.z * b.x) - (b.z * a.x),
		(a.x * b.y) - (b.x * a.y)
	};

	return ret;
}

double DotProduct(VECTOR3D a, VECTOR3D b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

MATRIX3 Transpose(MATRIX3 m)
{
	MATRIX3 retMatrix;
	retMatrix.column0 = { m.column0.x, m.column1.x, m.column2.x };
	retMatrix.column1 = { m.column0.y, m.column1.y, m.column2.y };
	retMatrix.column2 = { m.column0.z, m.column1.z, m.column2.z };

	return retMatrix;
}

VECTOR3D Transform (MATRIX3 m, VECTOR3D a)
{
	VECTOR3D toRet;
	toRet.x = DotProduct(Transpose(m).column0, a);
	toRet.y = DotProduct(Transpose(m).column1, a);
	toRet.z = DotProduct(Transpose(m).column2, a);

	return toRet;
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t) {
	MATRIX4 toRet;

	MATRIX3 aT = Transpose(A);
	VECTOR3D tAt = Transform(aT, t);
	
	toRet.m[0] = aT.column0.x;
	toRet.m[1] = aT.column0.y;
	toRet.m[2] = aT.column0.z;
	toRet.m[3] = 0;
	toRet.m[4] = aT.column1.x;
	toRet.m[5] = aT.column1.y;
	toRet.m[6] = aT.column1.z;
	toRet.m[7] = 0;
	toRet.m[8] = aT.column2.x;
	toRet.m[9] = aT.column2.y;
	toRet.m[10] = aT.column2.z;
	toRet.m[11] = 0;
	toRet.m[12] = -tAt.x;
	toRet.m[13] = -tAt.y;
	toRet.m[14] = -tAt.z;
	toRet.m[15] = 1;

	return toRet;
}

int fact(int x) {
	int i;
	int f = 1;

	for (i = 1; i <= x; i++)
		f *= i;
	return f;
}

double binom(int x, int y) {
	return (fact(x) / (fact(y) * fact(x - y)));
}

//generalized Bezier
VECTOR3D interpolate(CURVE curve, float t) {
	VECTOR3D toRet = { 0, 0, 0 };
	VECTOR3D vectorNI;

	unsigned short int i = 0;
	const unsigned short int n = curve.P.size();

	for (std::vector<VECTOR3D>::iterator itr = curve.P.begin(); itr != curve.P.end(); ++itr) {
		toRet = Add(toRet, MultiplyWithScalar(binom(n, i) * pow(1 - t, n - i) * pow(t, i), *itr));
		i++;
	}
	return toRet;
}

void drawCurve(CURVE curve) {
	VECTOR3D v;

	glBegin(GL_LINE_STRIP);
	for (float i = 0; i <= 1; i += 0.01) {
		v = interpolate(curve, i);
		glVertex3d(v.x, v.y, v.z);
	}
	glEnd();
}

#endif
