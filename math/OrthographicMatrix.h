#pragma once
#include "Matrix4x4.h"

Matrix4x4 MakeOrthograhicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 ans;
	ans.m[0][0] = 2 / (right - left);
	ans.m[0][1] = 0;
	ans.m[0][2] = 0;
	ans.m[0][3] = 0;
	ans.m[1][0] = 0;
	ans.m[1][1] = 2 / (top - bottom);
	ans.m[1][2] = 0;
	ans.m[1][3] = 0;
	ans.m[2][0] = 0;
	ans.m[2][1] = 0;
	ans.m[2][2] = 1 / (farClip - nearClip);
	ans.m[2][3] = 0;
	ans.m[3][0] = (left + right) / (left - right);
	ans.m[3][1] = (top + bottom) / (bottom - t);
	ans.m[3][2] = nearClip / (nearClip - farClip);
	ans.m[3][3] = 1;
	return ans;
}