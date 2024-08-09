#include "Matrix4x4.h"

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 ans = { 0 };
	ans.m[0][0] = width / 2;
	ans.m[1][1] = -height / 2;
	ans.m[2][2] = maxDepth - minDepth;
	ans.m[3][0] = left + width / 2;
	ans.m[3][1] = top + height / 2;
	ans.m[3][2] = minDepth;
	ans.m[3][3] = 1;
	return ans;
}