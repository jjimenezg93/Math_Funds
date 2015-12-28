//
//  camera.h
//  interpolation
//
//  Created by Jose Maria Benito on 28/10/14.
//  Copyright (c) 2014 Jose Maria. All rights reserved.
//

#ifndef interpolation_camera_h
#define interpolation_camera_h

typedef struct {
    VECTOR3D position;
    VECTOR3D direction;
    VECTOR3D up;
    
    double aperture;    // in degrees
    int screenwidth,screenheight;
    
} CAMERA;

typedef struct {
    double left;
    double right;
    double bottom;
    double top;
    double near;
    double far;
} FRUSTUM;

typedef struct {
	float yaw; // Rotation around the Y axis.
	float pitch; // Rotation around the X axis.
	float roll; // Rotation around the Z axis.
	QUATERNION orientation; // Cached quaternion equivalent of this euler object.
} EULER;

// TODO

 // devuelve los valores de distancia de los planos a partir del fov horizontal

FRUSTUM makeFrustum(double fovX, double aspectRatio, double near, double far)
{
    const double DEG2RAD = 3.14159265 / 180;
    
    double tangent = tan(fovX/2 * DEG2RAD); // tangent of half fovX
    double width = near * tangent; // half width of near plane
    double height = width / aspectRatio; // half height of near plane
    
    FRUSTUM ret;
    // TODO : rellenar valores de ret
	ret.left = -width;
	ret.right = width;
	ret.bottom = -height;
	ret.top = height;
	ret.near = near;
	ret.far = far;
    return ret;
}

// TODO

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector) {
	VECTOR3D forward = Normalize(Substract(target, eyePosition));

	VECTOR3D side = Normalize(CrossProduct(forward, upVector));

	VECTOR3D up = CrossProduct(side, forward);

	MATRIX3 rotMatrix;
	MATRIX4 toRet;

	rotMatrix.column0 = side;
	//rotMatrix.column0.z *= -1;
	rotMatrix.column1 = up;
	//rotMatrix.column1.z *= -1;
	rotMatrix.column2 = MultiplyWithScalar(-1, forward);
	//rotMatrix.column2 = forwardNorm;
	//rotMatrix.column1.z *= -1;

	//eyePosition.z *= -1;

	toRet = InverseOrthogonalMatrix(rotMatrix, eyePosition);

	return toRet;
}

VECTOR3D getForward(EULER euler) {
	VECTOR3D forwardRot;
	forwardRot = RotateWithQuaternion({ 0, 0, -1 }, euler.orientation);
	return forwardRot;
}

void updateEulerOrientation(EULER& euler) {
	QUATERNION qx, qy, qz;

	qx = QuaternionFromAngleAxis(euler.pitch, { 1, 0, 0 });
	qy = QuaternionFromAngleAxis(euler.yaw, { 0, 1, 0 });
	qz = QuaternionFromAngleAxis(euler.roll, { 0, 0, 1 });

	euler.orientation = Multiply(Multiply(qx, qy), qz);
}

#endif
