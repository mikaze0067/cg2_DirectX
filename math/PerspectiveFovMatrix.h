#include "Matrix4x4.h"
#pragma once
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 ans;

	float cot = 1 / std::tan(fovY / 2);
	ans.m[0][0] = (1 / aspectRatio) * cot;
	ans.m[0][1] = 0;
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;
	ans.m[1][0] = 0;
	ans.m[1][1] = cot;
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;
	ans.m[2][0] = 0;
	ans.m[2][1] = 0;
	ans.m[2][2] = nearClip - farClip / nearClip;
	ans.m[2][3] = 1;
	ans.m[3][0] = 0;
	ans.m[3][1] = 0;
	ans.m[3][2] = (nearClip - farClip) / -farClip * nearClip;
	ans.m[3][3] = 0;

	return ans;
}
