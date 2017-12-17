//  DK 2017.12.17 18:39
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <time.h>
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

void ReadYUV(char *filename, __int16 * inYUV_Y,
	__int16 * inYUV_U, __int16 * inYUV_V);
void YUV2RGB(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B);
void RGB2ARGB(int A, __int16 * RGB);
void RGB2YUV(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B);
void WriteYUV(__int16 * outYUV_Y, __int16 * outYUV_U, __int16 * outYUV_V);
void MIXRGB(int A, __int16 *RGB, __int16 *RGB2);

int main()
{
	/*
	// part 2
	char infilename[40] = "./demo/dem1.yuv";
	char outfilename[40] = "Part2.yuv";
	freopen(outfilename, "wb", stdout);// 重定向标准输出
	ReadYUV(infilename, (__int16 *)inYUV_Y,
		(__int16 *)inYUV_U, (__int16 *)inYUV_V);
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
	*/

	// Part 3
	char infilename1[40] = "./demo/dem1.yuv";
	char infilename2[40] = "./demo/dem2.yuv";
	char filename[40] = "Part3.yuv";
	freopen(filename, "wb", stdout);// 重定向标准输出			
	ReadYUV(infilename1, (__int16 *)inYUV_Y,
		(__int16 *)inYUV_U, (__int16 *)inYUV_V);
	ReadYUV(infilename2, (__int16 *)in2YUV_Y,
		(__int16 *)in2YUV_U, (__int16 *)in2YUV_V);
	for (int A = 1; A <= 255; A = A + 3)
	{
		YUV2RGB((__int16 *)inYUV_Y, (__int16 *)inYUV_U, (__int16 *)inYUV_V,
			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
		YUV2RGB((__int16 *)in2YUV_Y, (__int16 *)in2YUV_U, (__int16 *)in2YUV_V,
			(__int16 *)RGB2_R, (__int16 *)RGB2_G, (__int16 *)RGB2_B);
		type = SSE;
		MIXRGB(A, (__int16 *)RGB_R, (__int16 *)RGB2_R);
		MIXRGB(A, (__int16 *)RGB_G, (__int16 *)RGB2_G);
		MIXRGB(A, (__int16 *)RGB_B, (__int16 *)RGB2_B);
		type = NONE;
		RGB2YUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V,
			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
		WriteYUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V);
	}

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

			/*
			RGB[i * 1080 * 3 + j * 3 + 0] = 1.164*(YUV[i * 1080 * 3 + j * 3 + 0] - 16)
			+ 1.596*(YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 2] - 128);
			RGB[i * 1080 * 3 + j * 3 + 1] = 1.164*(YUV[i * 1080 * 3 + j * 3 + 0] - 16)
			- 0.391*(YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 1] - 128)
			- 0.813*(YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 2] - 128);
			RGB[i * 1080 * 3 + j * 3 + 2] = 1.164*(YUV[i * 1080 * 3 + j * 3 + 0] - 16)
			+ 2.018*(YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 1] - 128);
			*/
			/*
			RGB[i * 1080 * 3 + j * 3 + 0] = YUV[i * 1080 * 3 + j * 3 + 0]
			+ 1.4017*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 2];
			RGB[i * 1080 * 3 + j * 3 + 1] = 1 * YUV[i * 1080 * 3 + j * 3 + 0]
			- 0.3437*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 1]
			- 0.7142*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 2];
			RGB[i * 1080 * 3 + j * 3 + 2] = YUV[i * 1080 * 3 + j * 3 + 0]
			+ 1.7722*YUV[(i / 2) * 1080 * 3 + (j / 2) * 3 + 1];
			*/
		}
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
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			YUV_Y[i * 1080 + j] = 0.299*RGB_R[i * 1080 + j]
				+ 0.587*RGB_G[i * 1080 + j] + 0.114*RGB_B[i * 1080 + j];
			YUV_U[i * 1080 + j] = 0.492*(RGB_B[i * 1080 + j] - YUV_Y[i * 1080 + j]);
			YUV_V[i * 1080 + j] = 0.877*(RGB_R[i * 1080 + j] - YUV_Y[i * 1080 + j]);

			/*
			YUV[i * 1080 * 3 + j * 3 + 0] = 0.257*RGB[i * 1080 * 3 + j * 3 + 0]
			+ 0.504*RGB[i * 1080 * 3 + j * 3 + 1] + 0.098*RGB[i * 1080 * 3 + j * 3 + 2] + 16;
			YUV[i * 1080 * 3 + j * 3 + 1] = 0.148*RGB[i * 1080 * 3 + j * 3 + 0]
			- 0.291*RGB[i * 1080 * 3 + j * 3 + 1] + 0.439*RGB[i * 1080 * 3 + j * 3 + 2] + 128;
			YUV[i * 1080 * 3 + j * 3 + 2] = 0.439*RGB[i * 1080 * 3 + j * 3 + 0]
			- 0.368*RGB[i * 1080 * 3 + j * 3 + 1] - 0.071*RGB[i * 1080 * 3 + j * 3 + 2] + 128;
			*/
			/*
			YUV[i * 1080 * 3 + j * 3 + 0] = 0.299*RGB[i * 1080 * 3 + j * 3 + 0]
			+ 0.587*RGB[i * 1080 * 3 + j * 3 + 1] + 0.114*RGB[i * 1080 * 3 + j * 3 + 2];
			YUV[i * 1080 * 3 + j * 3 + 1] = -0.169*RGB[i * 1080 * 3 + j * 3 + 0]
			- 0.331*RGB[i * 1080 * 3 + j * 3 + 1] + 0.5*RGB[i * 1080 * 3 + j * 3 + 2];
			YUV[i * 1080 * 3 + j * 3 + 2] = 0.5*RGB[i * 1080 * 3 + j * 3 + 0]
			- 0.419*RGB[i * 1080 * 3 + j * 3 + 1] - 0.081*RGB[i * 1080 * 3 + j * 3 + 2];
			*/
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
	
	}
}
//下面的4个函数应该统计出图像处理的时间;
//函数参数和返回值可以需要自己定.
int process_without_simd()
{
	int time = 0;

	/*处理过程*/

	return time;
}

int process_with_mmx()
{
	int time = 0;

	/*处理过程*/

	return time;
}

int process_with_sse()
{
	int time = 0;

	/*处理过程*/

	return time;
}

int process_with_avx()
{
	int time = 0;
	/*处理过程*/


	return time;
}