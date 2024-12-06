#pragma once

#include "Matrix4x4.h"

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 ans = { 0 };
	float cot = 1 / std::tan(fovY / 2);
	ans.m[0][0] = (1 / aspectRatio) * cot;
	ans.m[1][1] = cot;
	ans.m[2][2] = nearClip - farClip / nearClip;
	ans.m[2][3] = 1;
	ans.m[3][2] = (nearClip - farClip) / -farClip * nearClip;
	return ans;
}

//Matrix4x4 Matrix4x4::MakePerspectiveMatrix(float y, float a, float n, float f)
//{
//    return Matrix4x4::MakeMatrix4x4(
//        1 / a * 1 / (tanf(y / 2)), 0, 0, 0,
//        0, 1 / tanf(y / 2), 0, 0,
//        0, 0, f / (f - n), 1,
//        0, 0, -n * f / (f - n), 0
//    );
//}