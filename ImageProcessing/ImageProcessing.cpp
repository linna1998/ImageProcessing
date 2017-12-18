//  DK 2017.12.17 18:39
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include <ivec.h>//MMX  
#include <fvec.h>//SSE(also include ivec.h)  
#include <dvec.h>//SSE2(also include fvec.h)  

#include <mmintrin.h> //MMX  
#include <xmmintrin.h> //SSE(include mmintrin.h)  
#include <emmintrin.h> //SSE2(include xmmintrin.h)  
#include <pmmintrin.h> //SSE3(include emmintrin.h)  
#include <tmmintrin.h>//SSSE3(include pmmintrin.h)  
#include <smmintrin.h>//SSE4.1(include tmmintrin.h)  
#include <nmmintrin.h>//SSE4.2(include smmintrin.h)  
#include <wmmintrin.h>//AES(include nmmintrin.h)  
#include <immintrin.h>//AVX(include wmmintrin.h)  
#include <intrin.h>//(include immintrin.h)  

using namespace std;
#define START 0
#define FINISH 1
#define NONE 0
#define MMX 1
#define SSE 2
#define AVX 3

clock_t start = 0;
clock_t finish = 0;
int type = NONE;

__int16 inYUV_Y[1920][1080];
__int16 inYUV_U[1920][1080];
__int16 inYUV_V[1920][1080];
__int16 in2YUV_Y[1920][1080];
__int16 in2YUV_U[1920][1080];
__int16 in2YUV_V[1920][1080];

__int16 outYUV_Y[1920][1080];
__int16 outYUV_U[1920][1080];
__int16 outYUV_V[1920][1080];

__int16 RGB_R[1920][1080];
__int16 RGB_G[1920][1080];
__int16 RGB_B[1920][1080];
__int16 RGB2_R[1920][1080];
__int16 RGB2_G[1920][1080];
__int16 RGB2_B[1920][1080];

__int16 TEMP1[1920][1080], TEMP2[1920][1080];
__int16 TEMP3[1920][1080], TEMP4[1920][1080];

void ReadYUV(char *filename, __int16 * inYUV_Y,
	__int16 * inYUV_U, __int16 * inYUV_V);
void YUV2RGB(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B);
void RGB2ARGB(int A, __int16 * RGB);
void RGB2YUV(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B);
void WriteYUV(__int16 * outYUV_Y, __int16 * outYUV_U, __int16 * outYUV_V);
void MIXRGB(int A, __int16 *RGB, __int16 *RGB2);
double process_time(int start);

int main()
{
	type = AVX;
	// part 2
	char infilename[40] = "./demo/dem1.yuv";
	char outfilename[40] = "Part2.yuv";
	freopen(outfilename, "wb", stdout);// 重定向标准输出
	ReadYUV(infilename, (__int16 *)inYUV_Y,
		(__int16 *)inYUV_U, (__int16 *)inYUV_V);
	process_time(START);
	for (int A = 1; A <= 255; A = A + 3)
	{
		YUV2RGB((__int16 *)inYUV_Y, (__int16 *)inYUV_U, (__int16 *)inYUV_V,
			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
		RGB2ARGB(A, (__int16 *)RGB_R);
		RGB2ARGB(A, (__int16 *)RGB_G);
		RGB2ARGB(A, (__int16 *)RGB_B);
		RGB2YUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V,
			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
		WriteYUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V);
	}	
	
	// Part 3
	char infilename1[40] = "./demo/dem1.yuv";
	char infilename2[40] = "./demo/dem2.yuv";
	char filename[40] = "Part3.yuv";
	freopen(filename, "wb", stdout);// 重定向标准输出		
	type = AVX;	
	ReadYUV(infilename1, (__int16 *)inYUV_Y,
		(__int16 *)inYUV_U, (__int16 *)inYUV_V);
	ReadYUV(infilename2, (__int16 *)in2YUV_Y,
		(__int16 *)in2YUV_U, (__int16 *)in2YUV_V);
	process_time(START);
	for (int A = 1; A <= 255; A = A + 3)
	{		
		YUV2RGB((__int16 *)inYUV_Y, (__int16 *)inYUV_U, (__int16 *)inYUV_V,
			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
		YUV2RGB((__int16 *)in2YUV_Y, (__int16 *)in2YUV_U, (__int16 *)in2YUV_V,
			(__int16 *)RGB2_R, (__int16 *)RGB2_G, (__int16 *)RGB2_B);		
		MIXRGB(A, (__int16 *)RGB_R, (__int16 *)RGB2_R);
		MIXRGB(A, (__int16 *)RGB_G, (__int16 *)RGB2_G);
		MIXRGB(A, (__int16 *)RGB_B, (__int16 *)RGB2_B);	
		RGB2YUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V,
			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);		
		WriteYUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V);
	}
	
	double runtime = process_time(FINISH);
	return 0;
}

void ReadYUV(char *filename, __int16 * inYUV_Y, __int16 * inYUV_U, __int16 * inYUV_V)
{
	freopen(filename, "rb", stdin);// 重定向标准输入	
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			scanf("%c", &inYUV_Y[i * 1080 + j]);
		}
	}
	for (int i = 0; i < 960; i++)
	{
		for (int j = 0; j < 540; j++)
		{
			scanf("%c", &inYUV_U[i * 2 * 1080 + j * 2]);
			inYUV_U[i * 2 * 1080 + j * 2 + 1] = inYUV_U[i * 2 * 1080 + j * 2];
			inYUV_U[(i * 2 + 1) * 1080 + j * 2] = inYUV_U[i * 2 * 1080 + j * 2];
			inYUV_U[(i * 2 + 1) * 1080 + j * 2 + 1] = inYUV_U[i * 2 * 1080 + j * 2];
		}
	}
	for (int i = 0; i < 960; i++)
	{
		for (int j = 0; j < 540; j++)
		{
			scanf("%c", &inYUV_V[i * 2 * 1080 + j * 2]);
			inYUV_V[i * 2 * 1080 + j * 2 + 1] = inYUV_V[i * 2 * 1080 + j * 2];
			inYUV_V[(i * 2 + 1) * 1080 + j * 2] = inYUV_V[i * 2 * 1080 + j * 2];
			inYUV_V[(i * 2 + 1) * 1080 + j * 2 + 1] = inYUV_V[i * 2 * 1080 + j * 2];
		}
	}
}

void YUV2RGB(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B)
{
	if (type == NONE)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				RGB_R[i * 1080 + j] = YUV_Y[i * 1080 + j]
					+ 1.140*YUV_V[i * 1080 + j];
				RGB_G[i * 1080 + j] = YUV_Y[i * 1080 + j]
					- 0.394*YUV_U[i * 1080 + j]
					- 0.581*YUV_V[i * 1080 + j];
				RGB_B[i * 1080 + j] = YUV_Y[i * 1080 + j]
					+ 2.032*YUV_U[i * 1080 + j];
			}
		}
	}
	else if (type == MMX)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				TEMP1[i][j] = 1.140*YUV_V[i * 1080 + j];
				TEMP2[i][j] = -0.394*YUV_U[i * 1080 + j];
				TEMP3[i][j] = -0.581*YUV_V[i * 1080 + j];
				TEMP4[i][j] = 2.032*YUV_U[i * 1080 + j];
			}
		}

		_mm_empty();
		__m64* pR = (__m64*)RGB_R;
		__m64* pG = (__m64*)RGB_G;
		__m64* pB = (__m64*)RGB_B;
		__m64* p1 = (__m64*)TEMP1[0];
		__m64* p2 = (__m64*)TEMP2[0];
		__m64* p3 = (__m64*)TEMP3[0];
		__m64* p4 = (__m64*)TEMP4[0];

		__m64* pY = (__m64*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 4; i++, pR++, pY++, p1++)
		{
			*pR = _m_paddw(*pY, *p1);
		}

		pY = (__m64*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 4; i++, pG++, pY++, p2++, p3++) 
		{
			*pG = _m_paddw(*pY, *p2);
			*pG = _m_paddw(*pG, *p3);
		}

		pY = (__m64*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 4; i++, pB++, pY++, p4++)
		{
			*pB = _m_paddw(*pY, *p4);
		}
		_mm_empty();
	}
	else if (type == SSE)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				TEMP1[i][j] = 1.140*YUV_V[i * 1080 + j];
				TEMP2[i][j] = -0.394*YUV_U[i * 1080 + j];
				TEMP3[i][j] = -0.581*YUV_V[i * 1080 + j];
				TEMP4[i][j] = 2.032*YUV_U[i * 1080 + j];
			}
		}

		_mm_empty();
		__m128i* pR = (__m128i*)RGB_R;
		__m128i* pG = (__m128i*)RGB_G;
		__m128i* pB = (__m128i*)RGB_B;
		__m128i* p1 = (__m128i*)TEMP1[0];
		__m128i* p2 = (__m128i*)TEMP2[0];
		__m128i* p3 = (__m128i*)TEMP3[0];
		__m128i* p4 = (__m128i*)TEMP4[0];

		__m128i* pY = (__m128i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pR++, pY++, p1++)
		{
			*pR = _mm_add_epi16(*pY, *p1);
		}

		pY = (__m128i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pG++, pY++, p2++, p3++)
		{
			*pG = _mm_add_epi16(*pY, *p2);
			*pG = _mm_add_epi16(*pG, *p3);
		}

		pY = (__m128i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pB++, pY++, p4++)
		{
			*pB = _mm_add_epi16(*pY, *p4);
		}
		_mm_empty();
	}
	else if (type == AVX)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				TEMP1[i][j] = 1.140*YUV_V[i * 1080 + j];
				TEMP2[i][j] = -0.394*YUV_U[i * 1080 + j];
				TEMP3[i][j] = -0.581*YUV_V[i * 1080 + j];
				TEMP4[i][j] = 2.032*YUV_U[i * 1080 + j];
			}
		}

		_mm_empty();
		__m256i* pR = (__m256i*)RGB_R;
		__m256i* pG = (__m256i*)RGB_G;
		__m256i* pB = (__m256i*)RGB_B;
		__m256i* p1 = (__m256i*)TEMP1[0];
		__m256i* p2 = (__m256i*)TEMP2[0];
		__m256i* p3 = (__m256i*)TEMP3[0];
		__m256i* p4 = (__m256i*)TEMP4[0];

		__m256i* pY = (__m256i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 16; i++, pR++, pY++, p1++)
		{
			*pR = _mm256_add_epi16(*pY, *p1);
		}

		pY = (__m256i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 16; i++, pG++, pY++, p2++, p3++)
		{
			*pG = _mm256_add_epi16(*pY, *p2);
			*pG = _mm256_add_epi16(*pG, *p3);
		}

		pY = (__m256i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pB++, pY++, p4++)
		{
			*pB = _mm256_add_epi16(*pY, *p4);
		}
		_mm_empty();
	}
}
void YUV2RGB_MMX(__int16 * YUV, __int16 * RGB)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			RGB[i * 1080 * 3 + j * 3 + 0] = YUV[i * 1080 * 3 + j * 3 + 0]
				+ 1.140*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 2];
			RGB[i * 1080 * 3 + j * 3 + 1] = YUV[i * 1080 * 3 + j * 3 + 0]
				- 0.394*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 1]
				- 0.581*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 2];
			RGB[i * 1080 * 3 + j * 3 + 2] = YUV[i * 1080 * 3 + j * 3 + 0]
				+ 2.032*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 1];
		}
	}
}

void RGB2ARGB(int A, __int16 * RGB)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			RGB[i * 1080 + j] = RGB[i * 1080 + j] * A / 256;
		}
	}
}

void RGB2YUV(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B)
{
	if (type == NONE)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				YUV_Y[i * 1080 + j] = 0.299*RGB_R[i * 1080 + j]
					+ 0.587*RGB_G[i * 1080 + j] + 0.114*RGB_B[i * 1080 + j];
				YUV_U[i * 1080 + j] = 0.492*(RGB_B[i * 1080 + j] - YUV_Y[i * 1080 + j]);
				YUV_V[i * 1080 + j] = 0.877*(RGB_R[i * 1080 + j] - YUV_Y[i * 1080 + j]);
			}
		}
	}
	else if (type == MMX)
	{	
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++) 
			{
				TEMP1[i][j] = 0.299 * RGB_R[i * 1080 + j];
				TEMP2[i][j] = 0.587 * RGB_G[i * 1080 + j];
				TEMP3[i][j] = 0.114 * RGB_B[i * 1080 + j];
			}
		}

		_mm_empty();
		__m64* pY = (__m64*)YUV_Y;
		__m64* pU = (__m64*)YUV_U;
		__m64* pV = (__m64*)YUV_V;
		__m64* pR = (__m64*)RGB_R;
		__m64* pB = (__m64*)RGB_B;
		__m64* p1 = (__m64*)TEMP1[0];
		__m64* p2 = (__m64*)TEMP2[0];
		__m64* p3 = (__m64*)TEMP3[0];

		for (int i = 0; i < 1920 * 1080 / 4; i++, pY++, p1++, p2++, p3++) 
		{
			*pY = _m_paddw(*p1, *p2);
			*pY = _m_paddw(*pY, *p3);
		}

		pY = (__m64*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 4; i++, pB++, pY++, pU++) 
		{
			*pU = _m_psubw(*pB, *pY);
		}

		pY = (__m64*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 4; i++, pR++, pY++, pV++) 
		{
			*pV = _m_psubw(*pR, *pY);
		}
		_mm_empty();

		for (int i = 0; i < 1920; i++) 
		{
			for (int j = 0; j < 1080; j++) 
			{
				YUV_U[i * 1080 + j] = 0.492 * YUV_U[i * 1080 + j];
				YUV_V[i * 1080 + j] = 0.877 * YUV_V[i * 1080 + j];
			}
		}	
	}
	else if (type == SSE)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				TEMP1[i][j] = 0.299 * RGB_R[i * 1080 + j];
				TEMP2[i][j] = 0.587 * RGB_G[i * 1080 + j];
				TEMP3[i][j] = 0.114 * RGB_B[i * 1080 + j];
			}
		}

		_mm_empty();
		__m128i* pY = (__m128i*)YUV_Y;
		__m128i* pU = (__m128i*)YUV_U;
		__m128i* pV = (__m128i*)YUV_V;
		__m128i* pR = (__m128i*)RGB_R;
		__m128i* pB = (__m128i*)RGB_B;
		__m128i* p1 = (__m128i*)TEMP1[0];
		__m128i* p2 = (__m128i*)TEMP2[0];
		__m128i* p3 = (__m128i*)TEMP3[0];

		for (int i = 0; i < 1920 * 1080 / 8; i++, pY++, p1++, p2++, p3++)
		{
			*pY = _mm_add_epi16(*p1, *p2);
			*pY = _mm_add_epi16(*pY, *p3);
		}

		pY = (__m128i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pB++, pY++, pU++)
		{
			*pU = _mm_sub_epi16(*pB, *pY);
		}

		pY = (__m128i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pR++, pY++, pV++)
		{
			*pV = _mm_sub_epi16(*pR, *pY);
		}
		_mm_empty();

		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				YUV_U[i * 1080 + j] = 0.492 * YUV_U[i * 1080 + j];
				YUV_V[i * 1080 + j] = 0.877 * YUV_V[i * 1080 + j];
			}
		}
	}
	else if (type == AVX)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				TEMP1[i][j] = 0.299 * RGB_R[i * 1080 + j];
				TEMP2[i][j] = 0.587 * RGB_G[i * 1080 + j];
				TEMP3[i][j] = 0.114 * RGB_B[i * 1080 + j];
			}
		}

		_mm_empty();
		__m256i* pY = (__m256i*)YUV_Y;
		__m256i* pU = (__m256i*)YUV_U;
		__m256i* pV = (__m256i*)YUV_V;
		__m256i* pR = (__m256i*)RGB_R;
		__m256i* pB = (__m256i*)RGB_B;
		__m256i* p1 = (__m256i*)TEMP1[0];
		__m256i* p2 = (__m256i*)TEMP2[0];
		__m256i* p3 = (__m256i*)TEMP3[0];

		for (int i = 0; i < 1920 * 1080 / 8; i++, pY++, p1++, p2++, p3++)
		{
			*pY = _mm256_add_epi16(*p1, *p2);
			*pY = _mm256_add_epi16(*pY, *p3);
		}

		pY = (__m256i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pB++, pY++, pU++)
		{
			*pU = _mm256_sub_epi16(*pB, *pY);
		}

		pY = (__m256i*)YUV_Y;
		for (int i = 0; i < 1920 * 1080 / 8; i++, pR++, pY++, pV++)
		{
			*pV = _mm256_sub_epi16(*pR, *pY);
		}
		_mm_empty();

		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				YUV_U[i * 1080 + j] = 0.492 * YUV_U[i * 1080 + j];
				YUV_V[i * 1080 + j] = 0.877 * YUV_V[i * 1080 + j];
			}
		}
	}
}

void WriteYUV(__int16 * outYUV_Y, __int16 * outYUV_U, __int16 * outYUV_V)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			cout << (char)outYUV_Y[i * 1080 + j];
		}
	}

	for (int i = 0; i < 960; i++)
	{
		for (int j = 0; j < 540; j++)
		{
			cout << (char)outYUV_U[i * 2 * 1080 + j * 2];
		}
	}
	for (int i = 0; i < 960; i++)
	{
		for (int j = 0; j < 540; j++)
		{
			cout << (char)outYUV_V[i * 2 * 1080 + j * 2];
		}
	}
}

// DEBUG
__int16 NONE_result[1920 * 1080];
void MIXRGB(int A, __int16 *RGB, __int16 *RGB2)
{
	// DEBUG
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			NONE_result[i * 1080 + j] = (RGB[i * 1080 + j] * A + RGB2[i * 1080 + j] * (256 - A)) / 256;			
		}
	}
	if (type == NONE)
	{
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				RGB[i * 1080 + j] = (RGB[i * 1080 + j] * A + RGB2[i * 1080 + j] * (256 - A)) / 256;
			}
		}
	}	
	else if (type == MMX)
	{
		register int i;
		const int nLoop = 1920 * 1080 / 4;
		_mm_empty();
		__m64* pRGB = (__m64*) RGB;
		__m64* pRGB2 = (__m64*) RGB2;
		//r0=_S0, r1=_S1, r2=_S2, r3=_S3  
		__m64 pA = _mm_set_pi16((short)A, (short)A, (short)A, (short)A);
		__m64 pA2 = _mm_set_pi16((short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A));

		for (i = 0; i < nLoop; i++, pRGB = pRGB + 1, pRGB2 = pRGB2 + 1)
		{
			//Subtracts the four 16-bit values in _MM2 from the four 16-bit values in _MM1  
			*pRGB2 = _m_psubw(*pRGB2, *pRGB);//_mm_sub_pi16 			
			//Multiplies four 16-bit values in _MM1 by four 16-bit values in _MM2 and produces  
			//the low 16 bits of the four results  
			*pRGB2 = _m_pmullw(*pRGB2, pA);//_mm_mullo_pi16  			
		}
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				RGB2[i * 1080 + j] = (RGB2[i * 1080 + j]) / 256;
			}
		}
		pRGB = (__m64*) RGB;
		pRGB2 = (__m64*) RGB2;
		for (i = 0; i < nLoop; i++, pRGB = pRGB + 1, pRGB2 = pRGB2 + 1)
		{
			//Adds the four 16-bit values in _MM1 to the four 16-bit values in _MM2  
			*pRGB = _m_paddw(*pRGB2, *pRGB);//_mm_add_pi16  			
		}
	}
	else if (type == SSE)
	{
		register int i;
		const int nLoop = 1920 * 1080 / 8;
		_mm_empty();
		__m128i* pRGB = (__m128i*) RGB;
		__m128i* pRGB2 = (__m128i*) RGB2;
		//r0=_S0, r1=_S1, r2=_S2, r3=_S3  
		__m128i pA = _mm_set_epi16((short)A, (short)A, (short)A, (short)A, 
			(short)A, (short)A, (short)A, (short)A);
		__m128i pA2 = _mm_set_epi16((short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A),
			(short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A));

		for (i = 0; i < nLoop; i++, pRGB = pRGB + 1, pRGB2 = pRGB2 + 1)
		{			
			*pRGB2 = _mm_sub_epi16(*pRGB2, *pRGB);
			*pRGB2 = _mm_mullo_epi16(*pRGB2, pA);//_mm_mullo_pi16  			
		}
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				RGB2[i * 1080 + j] = (RGB2[i * 1080 + j]) / 256;
			}
		}
		pRGB = (__m128i*) RGB;
		pRGB2 = (__m128i*) RGB2;
		for (i = 0; i < nLoop; i++, pRGB = pRGB + 1, pRGB2 = pRGB2 + 1)
		{
			//Adds the four 16-bit values in _MM1 to the four 16-bit values in _MM2  
			*pRGB = _mm_add_epi16(*pRGB2, *pRGB);//_mm_add_pi16  			
		}
	}
	else if (type == AVX)
	{
		register int i;
		const int nLoop = 1920 * 1080 / 16;
		_mm_empty();
		__m256i* pRGB = (__m256i*) RGB;
		__m256i* pRGB2 = (__m256i*) RGB2;		
		__m256i pA = _mm256_set_epi16
		((short)A, (short)A, (short)A, (short)A, (short)A, (short)A, (short)A, (short)A,
			(short)A, (short)A, (short)A, (short)A, (short)A, (short)A, (short)A, (short)A);
		__m256i pA2 = _mm256_set_epi16
		((short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A),
			(short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A), 
			(short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A),
			(short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A));

		for (i = 0; i < nLoop; i++, pRGB = pRGB + 1, pRGB2 = pRGB2 + 1)
		{
			*pRGB2 = _mm256_sub_epi16(*pRGB2, *pRGB);
			*pRGB2 = _mm256_mullo_epi16(*pRGB2, pA);
		}
		for (int i = 0; i < 1920; i++)
		{
			for (int j = 0; j < 1080; j++)
			{
				RGB2[i * 1080 + j] = (RGB2[i * 1080 + j]) / 256;
			}
		}
		pRGB = (__m256i*) RGB;
		pRGB2 = (__m256i*) RGB2;
		for (i = 0; i < nLoop; i++, pRGB = pRGB + 1, pRGB2 = pRGB2 + 1)
		{
			//Adds the four 16-bit values in _MM1 to the four 16-bit values in _MM2  
			*pRGB = _mm256_add_epi16(*pRGB2, *pRGB);//_mm_add_pi16  			
		}
	}
}
double process_time(int start)
{
	if (start = START) 
	{
		start = clock();
		return 0.0;
	}

	finish = clock();
	return (double)(finish - start) / CLOCKS_PER_SEC;
}