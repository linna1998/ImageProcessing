//#define _CRT_SECURE_NO_WARNINGS
//#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <time.h>
//#include <stdio.h>
//#include <time.h>
//#include <string.h>
//
//#include <ivec.h>//MMX  
//#include <fvec.h>//SSE(also include ivec.h)  
//#include <dvec.h>//SSE2(also include fvec.h)  
//
//#include <mmintrin.h> //MMX  
//#include <xmmintrin.h> //SSE(include mmintrin.h)  
//#include <emmintrin.h> //SSE2(include xmmintrin.h)  
//#include <pmmintrin.h> //SSE3(include emmintrin.h)  
//#include <tmmintrin.h>//SSSE3(include pmmintrin.h)  
//#include <smmintrin.h>//SSE4.1(include tmmintrin.h)  
//#include <nmmintrin.h>//SSE4.2(include smmintrin.h)  
//#include <wmmintrin.h>//AES(include nmmintrin.h)  
//#include <immintrin.h>//AVX(include wmmintrin.h)  
//#include <intrin.h>//(include immintrin.h)  
//
//#define START 0
//#define FINISH 1
//
//#define NONE 0
//#define MMX 1
//#define SSE 2
//#define AVX 3
//
//using namespace std;
//
//clock_t start = 0;
//clock_t finish = 0;
//int type = NONE;
//
//__int16 inYUV_Y[1920][1080];
//__int16 inYUV_U[1920][1080];
//__int16 inYUV_V[1920][1080];
//__int16 in2YUV_Y[1920][1080];
//__int16 in2YUV_U[1920][1080];
//__int16 in2YUV_V[1920][1080];
//
//__int16 outYUV_Y[1920][1080];
//__int16 outYUV_U[1920][1080];
//__int16 outYUV_V[1920][1080];
//
//__int16 RGB_R[1920][1080];
//__int16 RGB_G[1920][1080];
//__int16 RGB_B[1920][1080];
//__int16 RGB2_R[1920][1080];
//__int16 RGB2_G[1920][1080];
//__int16 RGB2_B[1920][1080];
//
//__int16 TEMP1[1920][1080];
//__int16 TEMP2[1920][1080];
//__int16 TEMP3[1920][1080];
//__int16 TEMP4[1920][1080];
//
//void ReadYUV(char *filename, __int16 * inYUV_Y,
//	__int16 * inYUV_U, __int16 * inYUV_V);
//void YUV2RGB(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
//	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B);
//void RGB2ARGB(int A, __int16 * RGB);
//void RGB2YUV(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
//	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B);
//void WriteYUV(char *filename, __int16 * outYUV_Y, __int16 * outYUV_U, __int16 * outYUV_V);
//void MIXRGB(int A, __int16 *RGB, __int16 *RGB2);
//
//int main(int argc, char **argv)
//{
//	/*
//	if (argc != 2) {
//	cout << "[ERROR] Need the type argument! --NONE --MMX --SSE --AVX" << endl;
//	}
//	if (!strcmp(argv[1], "--NONE")) {
//	type = NONE;
//	} else if (!strcmp(argv[1], "--MMX")) {
//	type = MMX;
//	} else if (!strcmp(argv[1], "--SSE")) {
//	type = SSE;
//	} else if (!strcmp(argv[1], "--AVX")) {
//	type = AVX;
//	}
//	*/
//	/*
//	// part 2
//	char infilename[40] = "./demo/dem1.yuv";
//	char outfilename[40] = "Part2.yuv";
//
//	ReadYUV(infilename, (__int16 *)inYUV_Y,
//		(__int16 *)inYUV_U, (__int16 *)inYUV_V);
//	cout << "dafdfa " << endl;
//	for (int A = 1; A <= 255; A = A + 3)
//	{
//		YUV2RGB((__int16 *)inYUV_Y, (__int16 *)inYUV_U, (__int16 *)inYUV_V,
//			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
//		RGB2ARGB(A, (__int16 *)RGB_R);
//		RGB2ARGB(A, (__int16 *)RGB_G);
//		RGB2ARGB(A, (__int16 *)RGB_B);
//		RGB2YUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V,
//			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
//		WriteYUV(outfilename, (__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V);
//	}
//	*/
//
//	// Part 3
//	char infilename1[40] = "./demo/dem1.yuv";
//	char infilename2[40] = "./demo/dem2.yuv";
//	char filename[40] = "Part3.yuv";
//
//	ReadYUV(infilename1, (__int16 *)inYUV_Y,
//		(__int16 *)inYUV_U, (__int16 *)inYUV_V);
//	ReadYUV(infilename2, (__int16 *)in2YUV_Y,
//		(__int16 *)in2YUV_U, (__int16 *)in2YUV_V);
//	for (int A = 1; A <= 255; A = A + 3)
//	{
//		YUV2RGB((__int16 *)inYUV_Y, (__int16 *)inYUV_U, (__int16 *)inYUV_V,
//			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
//		YUV2RGB((__int16 *)in2YUV_Y, (__int16 *)in2YUV_U, (__int16 *)in2YUV_V,
//			(__int16 *)RGB2_R, (__int16 *)RGB2_G, (__int16 *)RGB2_B);
//		type = NONE;
//		MIXRGB(A, (__int16 *)RGB_R, (__int16 *)RGB2_R);
//		MIXRGB(A, (__int16 *)RGB_G, (__int16 *)RGB2_G);
//		MIXRGB(A, (__int16 *)RGB_B, (__int16 *)RGB2_B);
//		type = NONE;
//		RGB2YUV((__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V,
//			(__int16 *)RGB_R, (__int16 *)RGB_G, (__int16 *)RGB_B);
//		WriteYUV(filename, (__int16 *)outYUV_Y, (__int16 *)outYUV_U, (__int16 *)outYUV_V);
//	}
//
//	return 0;
//}
//
//void ReadYUV(char *filename, __int16 * inYUV_Y, __int16 * inYUV_U, __int16 * inYUV_V)
//{
//	FILE *file = fopen(filename, "r");
//	for (int i = 0; i < 1920; i++)
//	{
//		for (int j = 0; j < 1080; j++)
//		{
//			fscanf(file, "%c", &inYUV_Y[i * 1080 + j]);
//		}
//	}
//	for (int i = 0; i < 960; i++)
//	{
//		for (int j = 0; j < 540; j++)
//		{
//			fscanf(file, "%c", &inYUV_U[i * 2 * 1080 + j * 2]);
//			inYUV_U[i * 2 * 1080 + j * 2 + 1] = inYUV_U[i * 2 * 1080 + j * 2];
//			inYUV_U[(i * 2 + 1) * 1080 + j * 2] = inYUV_U[i * 2 * 1080 + j * 2];
//			inYUV_U[(i * 2 + 1) * 1080 + j * 2 + 1] = inYUV_U[i * 2 * 1080 + j * 2];
//		}
//	}
//	for (int i = 0; i < 960; i++)
//	{
//		for (int j = 0; j < 540; j++)
//		{
//			fscanf(file, "%c", &inYUV_V[i * 2 * 1080 + j * 2]);
//			inYUV_V[i * 2 * 1080 + j * 2 + 1] = inYUV_V[i * 2 * 1080 + j * 2];
//			inYUV_V[(i * 2 + 1) * 1080 + j * 2] = inYUV_V[i * 2 * 1080 + j * 2];
//			inYUV_V[(i * 2 + 1) * 1080 + j * 2 + 1] = inYUV_V[i * 2 * 1080 + j * 2];
//		}
//	}
//}
//
//void YUV2RGB(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
//	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B)
//{
//	if (type == NONE)
//	{
//		for (int i = 0; i < 1920; i++)
//		{
//			for (int j = 0; j < 1080; j++)
//			{
//				RGB_R[i * 1080 + j] = YUV_Y[i * 1080 + j]
//					+ 1.140*YUV_V[i * 1080 + j];
//				RGB_G[i * 1080 + j] = YUV_Y[i * 1080 + j]
//					- 0.394*YUV_U[i * 1080 + j]
//					- 0.581*YUV_V[i * 1080 + j];
//				RGB_B[i * 1080 + j] = YUV_Y[i * 1080 + j]
//					+ 2.032*YUV_U[i * 1080 + j];
//			}
//		}
//	}
//	/*
//	else if (type == MMX)
//	{
//		for (int i = 0; i < 1920; i++)
//		{
//			for (int j = 0; j < 1080; j++)
//			{
//				TEMP1[i][j] = 1.140 * YUV_V[i * 1080 + j];
//				TEMP2[i][j] = -0.394 * YUV_U[i * 1080 + j];
//				TEMP3[i][j] = -0.581 * YUV_V[i * 1080 + j];
//				TEMP4[i][j] = 2.032 * YUV_U[i * 1080 + j];
//			}
//		}
//		cout << (int)YUV_Y << endl;
//		
//		__asm
//		{
//			// 分别在RGB中复制一遍Y
//			MOV esi, 0
//			mov cx, 129600
//
//			L1:	movq mm0, YUV_Y[esi]
//				movq mm1, TEMP1[esi]
//				paddw mm0, mm1
//				movq RGB_R[esi], mm0
//				add esi, 4
//				loop L1
//
//				mov esi, 0
//				mov cx, 129600
//				L2:	movq mm0, YUV_Y[esi]
//					paddw mm0, TEMP2[esi]
//					paddw mm0, TEMP3[esi]
//					movq RGB_G, mm0
//					add esi, 4
//					loop L2
//
//					mov esi, 0
//					mov cx, 129600
//					L3:	movq mm0, YUV_Y[esi]
//						paddw mm0, TEMP4[esi]
//						movq RGB_B, mm0
//						add esi, 4
//						loop L3
//
//						emms
//		}
//	}
//	*/
//}
//
//void RGB2ARGB(int A, __int16 * RGB)
//{
//	for (int i = 0; i < 1920; i++)
//	{
//		for (int j = 0; j < 1080; j++)
//		{
//			RGB[i * 1080 + j] = RGB[i * 1080 + j] * A / 256;
//		}
//	}
//}
//
//void RGB2YUV(__int16 * YUV_Y, __int16 * YUV_U, __int16 * YUV_V,
//	__int16 * RGB_R, __int16 * RGB_G, __int16 * RGB_B)
//{
//	if (type == NONE) {
//		for (int i = 0; i < 1920; i++)
//		{
//			for (int j = 0; j < 1080; j++)
//			{
//				YUV_Y[i * 1080 + j] = 0.299*RGB_R[i * 1080 + j]
//					+ 0.587*RGB_G[i * 1080 + j] + 0.114*RGB_B[i * 1080 + j];
//				YUV_U[i * 1080 + j] = 0.492*(RGB_B[i * 1080 + j] - YUV_Y[i * 1080 + j]);
//				YUV_V[i * 1080 + j] = 0.877*(RGB_R[i * 1080 + j] - YUV_Y[i * 1080 + j]);
//			}
//		}
//	}
//	/*
//	else if (type == MMX) {
//		// For Y
//		for (int i = 0; i < 1920; i++) {
//			for (int j = 0; j < 1080; j++) {
//				TEMP1[i][j] = 0.299 * RGB_R[i * 1080 + j];
//				TEMP2[i][j] = 0.587 * RGB_G[i * 1080 + j];
//				TEMP3[i][j] = 0.114 * RGB_B[i * 1080 + j];
//			}
//		}
//		__asm {
//			mov esi, 0
//			mov cx, 129600
//			L1:	movq mm0, TEMP1[esi]
//				paddw mm0, TEMP2[esi]
//				paddw mm0, TEMP3[esi]
//				movq YUV_Y[esi], mm0
//				add esi, 4
//				loop L1
//
//				mov esi, 0
//				mov cx, 129600
//				L2:	movq mm0, RGB_B[esi]
//					psubw mm0, YUV_Y[esi]
//					movq YUV_U[esi], mm0
//					add esi, 4
//					loop L2
//
//					mov esi, 0
//					mov cx, 129600
//					L3:	movq mm0, RGB_R[esi]
//						psubw mm0, YUV_Y[esi]
//						movq YUV_V[esi], mm0
//						add esi, 4
//						loop L3
//
//						emms
//		}
//
//		for (int i = 0; i < 1920; i++) {
//			for (int j = 0; j < 1080; j++) {
//				YUV_U[i * 1080 + j] = 0.492 * YUV_U[i * 1080 + j];
//				YUV_V[i * 1080 + j] = 0.877 * YUV_V[i * 1080 + j];
//			}
//		}
//	}
//	else if (type == SSE) {
//
//	}
//	else if (type == AVX) {
//
//	}
//	*/
//}
//
//void WriteYUV(char* filename, __int16 * outYUV_Y, __int16 * outYUV_U, __int16 * outYUV_V)
//{
//	FILE *file = fopen(filename, "w");
//	for (int i = 0; i < 1920; i++)
//	{
//		for (int j = 0; j < 1080; j++)
//		{
//			fprintf(file, "%c", (char)outYUV_Y[i * 1080 + j]);
//		}
//	}
//
//	for (int i = 0; i < 960; i++)
//	{
//		for (int j = 0; j < 540; j++)
//		{
//			fprintf(file, "%c", (char)outYUV_U[i * 2 * 1080 + j * 2]);
//		}
//	}
//	for (int i = 0; i < 960; i++)
//	{
//		for (int j = 0; j < 540; j++)
//		{
//			fprintf(file, "%c", (char)outYUV_V[i * 2 * 1080 + j * 2]);
//		}
//	}
//}
//
//void MIXRGB(int A, __int16 *RGB, __int16 *RGB2)
//{
//	if (type == NONE)
//	{
//		for (int i = 0; i < 1920; i++)
//		{
//			for (int j = 0; j < 1080; j++)
//			{
//				RGB[i * 1080 + j] = (RGB[i * 1080 + j] * A + RGB2[i * 1080 + j] * (256 - A)) / 256;
//			}
//		}
//	}
//	else if (type == MMX)
//	{
//		register int i;
//		const int nLoop = 1920 * 1080 / 4;
//		_mm_empty();
//		__m64* pRGB = (__m64*) RGB;
//		__m64* pRGB2 = (__m64*) RGB2;
//		//r0=_S0, r1=_S1, r2=_S2, r3=_S3  
//		__m64 pA = _mm_set_pi16((short)A, (short)A, (short)A, (short)A);
//		__m64 pA2 = _mm_set_pi16((short)(256 - A), (short)(256 - A), (short)(256 - A), (short)(256 - A));
//
//		for (i = 0; i < nLoop; i++, pRGB = pRGB + 4, pRGB2 = pRGB2 + 4)
//		{
//			//Multiplies four 16-bit values in _MM1 by four 16-bit values in _MM2 and produces  
//			//the low 16 bits of the four results  
//			*pRGB = _m_pmullw(*pRGB, pA);//_mm_mullo_pi16  
//			*pRGB2 = _m_pmullw(*pRGB2, pA2);//_mm_mullo_pi16  
//			//Adds the four 16-bit values in _MM1 to the four 16-bit values in _MM2  
//			_m_paddw(*pRGB2, *pRGB);//_mm_add_pi16  	
//		}
//		for (int i = 0; i < 1920; i++)
//		{
//			for (int j = 0; j < 1080; j++)
//			{
//				RGB[i * 1080 + j] = RGB[i * 1080 + j] / 256;
//			}
//		}
//	}
//}
////下面的4个函数应该统计出图像处理的时间;
////函数参数和返回值可以需要自己定.
//double process_without_simd(int start)
//{
//	if (start = START) {
//		start = clock();
//		return 0.0;
//	}
//
//	finish = clock();
//	return (double)(finish - start) / CLOCKS_PER_SEC;
//}
//
//double process_with_mmx(int start)
//{
//	if (start = START) {
//		start = clock();
//		return 0.0;
//	}
//
//	finish = clock();
//	return (double)(finish - start) / CLOCKS_PER_SEC;
//}
//
//double process_with_sse(int start)
//{
//	if (start = START) {
//		start = clock();
//		return 0.0;
//	}
//
//	finish = clock();
//	return (double)(finish - start) / CLOCKS_PER_SEC;
//}
//
//double process_with_avx(int start)
//{
//	if (start = START) {
//		start = clock();
//		return 0.0;
//	}
//
//	finish = clock();
//	return (double)(finish - start) / CLOCKS_PER_SEC;
//}
