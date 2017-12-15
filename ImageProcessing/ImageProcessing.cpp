#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

unsigned char inYUV[1920][1080][3] = { 0 };  //[][][0]:Y [][][1]:U [][][2]:V
unsigned char in2YUV[1920][1080][3] = { 0 };
unsigned char outYUV[1920][1080][3] = { 0 };

int RGB[1920][1080][3] = { 0 };  // //[][][0]:R [][][1]:G [][][2]:B
int RGB2[1920][1080][3] = { 0 };  // //[][][0]:R [][][1]:G [][][2]:B

void ReadYUV(char * filename, unsigned char * inYUV);
void YUV2RGB(unsigned char * YUV, int * RGB);
void RGB2ARGB(int A, int * RGB);
void RGB2YUV(unsigned char * YUV, int * RGB);
void WriteYUV(unsigned char * outYUV);
void MIXRGB(int A, int *RGB, int *RGB2);

int main()
{
	// part 2
	char infilename[40] = "./demo/dem1.yuv";
	char outfilename[40] = "Part2.yuv";
	freopen(outfilename, "wb", stdout);// 重定向标准输出			
	ReadYUV(infilename, (unsigned char *)inYUV);
	for (int A = 1; A <= 255; A = A + 3)
	{
		YUV2RGB((unsigned char *)inYUV, (int *)RGB);
		RGB2ARGB(A, (int *)RGB);
		RGB2YUV((unsigned char *)outYUV, (int *)RGB);
		WriteYUV((unsigned char *)outYUV);
	}


	// Part 3
	char inputfilename1[40] = "./demo/dem1.yuv";
	char inputfilename2[40] = "./demo/dem2.yuv";
	char filename[40] = "Part3.yuv";
	freopen(filename, "wb", stdout);// 重定向标准输出			
	ReadYUV(inputfilename1, (unsigned char *)inYUV);
	ReadYUV(inputfilename2, (unsigned char *)in2YUV);
	for (int A = 1; A <= 255; A = A + 3)
	{
		YUV2RGB((unsigned char *)inYUV, (int *)RGB);
		YUV2RGB((unsigned char *)in2YUV, (int *)RGB2);
		MIXRGB(A, (int *)RGB, (int *)RGB2);
		RGB2YUV((unsigned char *)outYUV, (int *)RGB);
		WriteYUV((unsigned char *)outYUV);
	}
	return 0;
}

void ReadYUV(char * filename, unsigned char * inYUV)
{
	freopen(filename, "rb", stdin);// 重定向标准输入	
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			scanf("%c", &inYUV[i * 1080 * 3 + j * 3 + 0]);
		}
	}
	for (int t = 1; t <= 2; t++)
	{
		for (int i = 0; i < 960; i++)
		{
			for (int j = 0; j < 540; j++)
			{
				scanf("%c", &inYUV[i * 1080 * 3 + j * 3 + t]);
			}
		}
	}
}

void YUV2RGB(unsigned char * YUV, int * RGB)
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

void RGB2ARGB(int A, int * RGB)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			for (int t = 0; t <= 2; t++)
			{
				RGB[i * 1080 * 3 + j * 3 + t] = RGB[i * 1080 * 3 + j * 3 + t] * A / 256;
			}
		}
	}
}

void RGB2YUV(unsigned char * YUV, int * RGB)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{

			YUV[i * 1080 * 3 + j * 3 + 0] = 0.299*RGB[i * 1080 * 3 + j * 3 + 0]
				+ 0.587*RGB[i * 1080 * 3 + j * 3 + 1] + 0.114*RGB[i * 1080 * 3 + j * 3 + 2];
			YUV[i * 1080 * 3 + j * 3 + 1] = 0.492*(RGB[i * 1080 * 3 + j * 3 + 2] - YUV[i * 1080 * 3 + j * 3 + 0]);
			YUV[i * 1080 * 3 + j * 3 + 2] = 0.877*(RGB[i * 1080 * 3 + j * 3 + 0] - YUV[i * 1080 * 3 + j * 3 + 0]);

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

void WriteYUV(unsigned char * outYUV)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			cout << (char)outYUV[i * 1080 * 3 + j * 3 + 0];
		}
	}
	for (int t = 1; t <= 2; t++)
	{
		for (int i = 0; i < 960; i++)
		{
			for (int j = 0; j < 540; j++)
			{
				// cout << (char)outYUV[i * 2 * 1080 * 3 + j * 2 * 3 + t];
				cout << (char)outYUV[i * 1080 * 3 + j * 3 + t];
			}
		}
	}
}

void MIXRGB(int A, int *RGB, int *RGB2)
{
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			for (int t = 0; t <= 2; t++)
			{
				RGB[i * 1080 * 3 + j * 3 + t] = (RGB[i * 1080 * 3 + j * 3 + t] * A + RGB2[i * 1080 * 3 + j * 3 + t] * (256 - A)) / 256;
			}
		}
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