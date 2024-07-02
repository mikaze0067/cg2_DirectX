#include "Matrix4x4.h"
#pragma once
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
