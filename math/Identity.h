#pragma once
#include "Matrix4x4.h"

Matrix4x4 MakeIdentity4x4()
{
	Matrix4x4 identity = { 0 };
	identity.m[0][0] = 1.0f;
	identity.m[1][1] = 1.0f;
	identity.m[2][2] = 1.0f;
	identity.m[3][3] = 1.0f;
	return identity;
}