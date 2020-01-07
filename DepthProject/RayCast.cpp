#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <cstring>
#include "gmath.h"
#include "usr\include\GL\freeglut.h"

#define PI 3.141592

// ���� ������
int Width;
int Height;
int Depth;
unsigned char *pVolData;
unsigned char *pImage;
unsigned char *pScaledImage;
GVec3 *pNormal;
float *pColor;
float *pOpacity;
int N = 3;
int d0 = 40, d1 = 100;
float alpha = 0.1;

GVec3 L(0, -1, 0);

// �׽�Ʈ 1
// unsigned char d0 = 70, d1 = 120;
// float alpha = 0.7;

// �׽�Ʈ 2
// unsigned char d0 = 120, d1 = 190;
// float alpha = 0.7;

// �׽�Ʈ 3
// unsigned char d0 = 190, d1 = 255;
// float alpha = 0.8;
// �ݹ� �Լ� ����
void Render();
void Reshape(int w, int h);

void LoadData(char *file_name);
void ComputeNormal();
void AssignOpacity();
void ComputeColor();
void CreateImage();
int GetPixelIdx(int i, int j);
int GetVoxelIdx(int i, int j, int k);

float lerp(float ori, float x1, float x2, float q00, float q01);
float triLerp(float x, float y, float z, float q000, float q001, float q010, float q011, float q100, float q101, float q110, float q111);
double getRadian(int _num);

int count;
int Acount;
int Ccount;
int main(int argc, char **argv)
{
	//triLerp(float x, float y, float z, float q000, float q001, float q010, float q011, float q100, float q101, float q110, float q111)
	//lerp(float ori, float x1, float x2, float q00, float q01)

	printf("������ %f",lerp(1.6,1.0,2.0,3,4)); //check

	printf("�Ｑ ������ %f \n", triLerp(0.5, 0.5, 0.5, 2, 1,1,1,1,1,1,1));// check



	// ���� ������ �ε�
	LoadData("..\\data\\bighead.txt");

	// OpenGL �ʱ�ȭ, ������ ũ�� ����, ���÷��� ��� ����
	glutInit(&argc, argv);
	glutInitWindowSize(Width * N, Depth * N);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// ������ ���� �� �ݹ� �Լ� ���
	glutCreateWindow("Volume Renderer");
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	
	printf("�������� �������� ���ÿ� ���� : 1, ���� : 2 �밢�� : 3 \n\n");
	scanf("%d", &count);
	
	
	printf("�������� �����ΰ���? : 1, ��ΰ���? : 2 \n\n");
	scanf("%d", &Acount);
	
	printf("Į��� �ұ��? �� : 1, �ƴϿ� : 2\n\n");
	scanf("%d", &Ccount);
	
	if (count == 1)
		L.Set(0, -1, 0);
	else if (count == 2)
		L.Set(0, 0, -1);
	else if (count == 3)
	{
		L.Set(0, 0, -1);
		L.Normalize();
	}

	ComputeNormal();	// �������� ���
	AssignOpacity();	// ������ �Ҵ�
	ComputeColor();		// ������ ���� ���



	CreateImage();		// �̹����� ����

						// �̺�Ʈ�� ó���� ���� ���� ������ �����Ѵ�.
	glutMainLoop();
	delete[] pVolData;
	delete[] pNormal;
	delete[] pOpacity;
	delete[] pColor;
	delete[] pImage;
	delete[] pScaledImage;
	return 0;



}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Render()
{
	// Į�� ���ۿ� ���� ���� �����
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < Depth * N; ++i)
	{
		for (int j = 0; j < Width * N; ++j)
		{
			unsigned char r = pImage[(i / N * Width + j / N) * 3];
			unsigned char g = pImage[(i / N * Width + j / N) * 3 + 1];
			unsigned char b = pImage[(i / N * Width + j / N) * 3 + 2];
			pScaledImage[(i * Width * N + j) * 3] = r;
			pScaledImage[(i * Width * N + j) * 3 + 1] = g;
			pScaledImage[(i * Width * N + j) * 3 + 2] = b;
		}
	}

	// Į�� ���ۿ� Image �����͸� ���� �׸���.
	glDrawPixels(Width * N, Depth * N, GL_RGB, GL_UNSIGNED_BYTE, pScaledImage);

	// Į�� ���� ��ȯ�Ѵ�
	glutSwapBuffers();

	printf("(f0, f1) and alpha = ? ");
	scanf("%d%d%f", &d0, &d1, &alpha);

	AssignOpacity();
	ComputeColor();
	CreateImage();

	glutPostRedisplay();
}

int GetPixelIdx(int i, int j) //����X
{
	return ((Depth - 1 - i) * Width + j) * 3;
}

int GetVoxelIdx(int i, int j, int k)
{
	return i * (Width * Height) + j * Width + k;
}

void LoadData(char *file_name)
{
	// ���� ���(*.txt) ������ �д´�.
	FILE *fp;
	fopen_s(&fp, file_name, "r");
	fscanf_s(fp, "%d%d%d", &Width, &Height, &Depth);
	char vol_file_name[256];
	fscanf(fp, "%s", vol_file_name);
	fclose(fp);

	// ���� ���丮�� ��� ������ �ִ� ������ �����Ѵ�.
	std::string file_path(file_name);
	int idx = file_path.rfind("\\");
	file_path = file_path.substr(0, idx);
	_chdir(file_path.c_str());

	// �������� �ʿ��� �迭�� �Ҵ��Ѵ�.
	pVolData = new unsigned char[Depth * Height * Width];
	pNormal = new GVec3[Depth * Height * Width];
	pColor = new float[Depth * Height * Width];
	pOpacity = new float[Depth * Height * Width];
	pImage = new unsigned char[Depth * Width * 3];//*3
	pScaledImage = new unsigned char[Depth * N * Width * N * 3];

	// ���� �����͸� ���̳ʸ� ���·� �д´�.
	fopen_s(&fp, vol_file_name, "rb");
	fread(pVolData, sizeof(unsigned char), Depth * Height * Width, fp);
	fclose(fp);
}

void ComputeNormal()
{
	for (int i = 1; i < Depth - 1; ++i)
	{
		for (int j = 1; j < Height - 1; ++j)
		{
			for (int k = 1; k < Width - 1; ++k)
			{
				int vidx = GetVoxelIdx(i, j, k);
				double dx = (pVolData[GetVoxelIdx(i + 1, j, k)] - pVolData[GetVoxelIdx(i - 1, j, k)]) / 2;
				double dy = (pVolData[GetVoxelIdx(i, j + 1, k)] - pVolData[GetVoxelIdx(i, j - 1, k)]) / 2;
				double dz = (pVolData[GetVoxelIdx(i, j, k + 1)] - pVolData[GetVoxelIdx(i, j, k - 1)]) / 2;
				// �����ϼ���...
				pNormal[vidx].Set(-dx, -dy, -dz);
				pNormal[vidx].Normalize();
				//printf("p : %lf,%lf,%lf \n", dx, dy, dz);
			}
		}
	}
}

void AssignOpacity()
{
	for (int i = 0; i < Depth; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			for (int k = 0; k < Width; ++k)
			{
				if (Acount == 1)
				{
					int vidx = GetVoxelIdx(i, j, k);

					if (pVolData[GetVoxelIdx(i, j, k)] >= d0 && pVolData[GetVoxelIdx(i, j, k)] < ((d0 + d1) / 2)) //���
					{
						//double a = pImage[GetVoxelIdx(i, j, k)]
						pOpacity[vidx] = (pVolData[GetVoxelIdx(i, j, k)] - d0) * (alpha / ((d0 + d1) / 2));
						//printf("��� : %f \n", pOpacity[vidx]);
					}


					/*
					else if(pVolData[GetVoxelIdx(i, j, k)] > d0+10 && pVolData[GetVoxelIdx(i, j, k)] < d1-10) //����
					{
					pOpacity[vidx] = alpha;
					}
					*/


					else if (pVolData[GetVoxelIdx(i, j, k)] >= ((d1 + d0) / 2) && pVolData[GetVoxelIdx(i, j, k)] <= d1)//�ϰ�
					{
						pOpacity[vidx] = alpha - ((pVolData[GetVoxelIdx(i, j, k)] - 90) * (alpha / ((d0 + d1) / 2)));

						//printf("�ϰ� : %f \n", pOpacity[vidx]);
					}


					else
					{
						pOpacity[vidx] = 0;
					}
				}

			

				else if (Acount == 2)
			{


				int vidx = GetVoxelIdx(i, j, k);

				if (pVolData[GetVoxelIdx(i, j, k)] >= d0 && pVolData[GetVoxelIdx(i, j, k)] < ((d0 + d1) / 2)) //���
				{
					
					//double a = pImage[GetVoxelIdx(i, j, k)]
					pOpacity[vidx] = pow((pVolData[GetVoxelIdx(i, j, k)] - d0) * (alpha / ((d0 + d1) / 2)),2);
					//printf("��� : %f \n", pOpacity[vidx]);
				}


				/*
				else if(pVolData[GetVoxelIdx(i, j, k)] > d0+10 && pVolData[GetVoxelIdx(i, j, k)] < d1-10) //����
				{
				pOpacity[vidx] = alpha;
				}
				*/


				else if (pVolData[GetVoxelIdx(i, j, k)] >= ((d1 + d0) / 2) && pVolData[GetVoxelIdx(i, j, k)] <= d1)//�ϰ�
				{
					pOpacity[vidx] = pow(alpha - (pVolData[GetVoxelIdx(i, j, k)] - 90) * (alpha / ((d0 + d1) / 2)),2);

					//printf("�ϰ� : %f \n", pOpacity[vidx]);
				}


				else
				{
					pOpacity[vidx] = 0;
				}


			}


			}
		}
	}
}

void ComputeColor()
{
	GVec3 V(0, 0, 1);

	GVec3 ld(1.0, 1.0, 1.0);
	GVec3 ls(1.0, 1.0, 1.0);
	GVec3 kd(1.0, 1.0, 1.0);
	GVec3 ks(1.0, 1.0, 1.0);

	double ns = 16.0;
	for (int i = 0; i < Depth; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			for (int k = 0; k < Width; ++k)
			{
				int vidx = GetVoxelIdx(i, j, k);
				GVec3 N = pNormal[vidx];
				GVec3 R = (2 * (L*N)*N - L);

				GVec3 diff = GVec3(ld[0] * kd[0], ld[1] * kd[1], ld[2] * kd[2]);
				GVec3 spec = GVec3(ls[0] * ks[0], ls[1] * ks[1], ls[2] * ks[2]);


				GVec3 result = (diff * MAX(0.0, N * L) + (spec * pow(MAX(0.0, V * R), ns)));

				pColor[vidx] = (result[0] + result[1] + result[2]) / 3.0;

				//pColor[3 * vidx] = result[0];
				//pColor[3 * vidx + 1] = result[1];
				//pColor[3 * vidx + 2] = result[2];


				//printf("pColor : %f \n", pColor[vidx]);
				//�����Ʈ ����
				// �����ϼ���...

			}
		}
	}
}

void CreateImage()
{//��� ����, ���� ����, �Ｑ���������� general �ϰ� �����ص� �Ǵ���..



	int MaxIdx = Width * Height * Depth;


	int y = 0;
	for (int i = 0; i < Depth; ++i)
	{

		for (int j = 0; j < Width; ++j)
		{
			GPos3 p(i, 0, j);
			GLine ray(p, GVec3(0, 1, 0));

			if (count == 1)
			{

				GPos3 p(i, 0, j);
				GLine ray(p, GVec3(0, 1, 0));


				double t = 0.0;

				//float alpha_out = 0.0;
				//GVec3 color_out = 0.0;
				float color_out = 0.0;


				GPos3 wis = ray.Eval(t); //��� �ִ���


										 //int vidx2 = GetVoxelIdx(wis[0], wis[2], wis[1]); //j,t�� �ƴ� t,j ����
										 //int vidx2 = GetVoxelIdx(i, t, j); //j,t�� �ƴ� t,j
										 //int a=floor(2.5); //2
										 //int b=ceil(4.4);//5
				float op = 0.0;
				float pc = 0.0;


				while (true)
				{


					//(num / 1.00 == (int)num
					wis = ray.Eval(t); //��� �ִ���

									   //float triLerp(float x, float y, float z, float q000, float q001, float q010, float q011, float q100, float q101, float q110, float q111)



									   //vidx2 = GetVoxelIdx(wis[0], wis[2], wis[1]); ����
									   //printf("wis[0] : %lf wis2 : %lf wis1 : %lf \n", wis[0], wis[2], wis[1]);



					float ovidx2 = pOpacity[GetVoxelIdx(floor(wis[0]), floor(wis[1]), floor(wis[2]))]; //000

					float oq001 = pOpacity[GetVoxelIdx(floor(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float oq010 = pOpacity[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float oq011 = pOpacity[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), ceil(wis[2]))];
					float oq100 = pOpacity[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), floor(wis[2]))];
					float oq101 = pOpacity[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float oq110 = pOpacity[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float oq111 = pOpacity[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), ceil(wis[2]))];

					float pvidx2 = pColor[GetVoxelIdx(floor(wis[0]), floor(wis[1]), floor(wis[2]))]; //000

					float pq001 = pColor[GetVoxelIdx(floor(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float pq010 = pColor[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float pq011 = pColor[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), ceil(wis[2]))];
					float pq100 = pColor[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), floor(wis[2]))];
					float pq101 = pColor[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float pq110 = pColor[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float pq111 = pColor[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), ceil(wis[2]))];

					//Ʈ���� ������ ���� �Ϸ�





					//GVec3 temp=GVec3(pColor[3*vidx2], pColor[3 * vidx2+1], pColor[3 * vidx2+2]);
					//vidx2 = GetVoxelIdx(i, t, j); //j,t�� �ƴ� t,j
					//wis[0]  x
					//wis[1]  y
					//wis[2]  z



					float opresult = triLerp(wis[0], wis[2], wis[1], ovidx2, oq001, oq010, oq011, oq100, oq101, oq110, oq111);
					//if(opresult>0)
					//printf("%f", opresult);

					float ppresult = triLerp(wis[0], wis[2], wis[1], pvidx2, pq001, pq010, pq011, pq100, pq101, pq110, pq111);
					//if (ppresult > 0)
					//printf("%f", ppresult);
					//�� op

					//float pcresult = ;
					//�� pc




					op = (op + (opresult * (1 - op)));
					//if(op>0)
					//printf("%f", op);
					pc = (pc + ((opresult * (1 - op))*ppresult));
					//if(pc>0)
					//printf("%f", pc);

					if (op >= 1)
					{

						break;
					}

					t = t + 0.1;

					if (t >= Height)
					{
						break;
					}
				}

				color_out = pc;

				int idx = GetPixelIdx(i, j);

				color_out = MIN(color_out, 1.0);
				//color_out = MIN(color_out[0], 1.0);
				//color_out = MIN(color_out[1], 1.0);
				//color_out = MIN(color_out[2], 1.0);

				if (Acount == 1)
				{
					if (color_out > 0.7)
					{
						pImage[idx] = color_out * 255;

					}
					else if (color_out > 0.5)
					{
						pImage[idx + 1] = color_out * 255;
					}
					else if (color_out > 0.3)
					{
						pImage[idx + 1] = color_out * 255;
						pImage[idx + 2] = color_out * 255;

					}
					else
					{
						pImage[idx] = color_out * 255;
						pImage[idx + 1] = color_out * 255;
						pImage[idx + 2] = color_out * 255;
					}
				}
				else if (Ccount == 2)
				{
					pImage[idx] = color_out * 255;
					pImage[idx + 1] = color_out * 255;
					pImage[idx + 2] = color_out * 255;
				}


				t = 0;
				op = 0;
				pc = 0;


			}
			else if (count == 2)
			{
			// *****
				GPos3 p(i, Width-j, 0);
				GLine ray(p, GVec3(0, 0, 1));

				//std::cout << p << std::endl;

				double t = 0.0;

				//float alpha_out = 0.0;
				//GVec3 color_out = 0.0;
				float color_out = 0.0;


				GPos3 wis = ray.Eval(t); //��� �ִ���


										 //int vidx2 = GetVoxelIdx(wis[0], wis[2], wis[1]); //j,t�� �ƴ� t,j ����
										 //int vidx2 = GetVoxelIdx(i, t, j); //j,t�� �ƴ� t,j
										 //int a=floor(2.5); //2
										 //int b=ceil(4.4);//5
				float op = 0.0;
				float pc = 0.0;


				while (true)
				{


					//(num / 1.00 == (int)num
					wis = ray.Eval(t); //��� �ִ���

									   //float triLerp(float x, float y, float z, float q000, float q001, float q010, float q011, float q100, float q101, float q110, float q111)



									   //vidx2 = GetVoxelIdx(wis[0], wis[2], wis[1]); ����
									   //printf("wis[0] : %lf wis2 : %lf wis1 : %lf \n", wis[0], wis[2], wis[1]);



					float ovidx2 = pOpacity[GetVoxelIdx(floor(wis[0]), floor(wis[1]), floor(wis[2]))]; //000

					float oq001 = pOpacity[GetVoxelIdx(floor(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float oq010 = pOpacity[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float oq011 = pOpacity[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), ceil(wis[2]))];
					float oq100 = pOpacity[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), floor(wis[2]))];
					float oq101 = pOpacity[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float oq110 = pOpacity[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float oq111 = pOpacity[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), ceil(wis[2]))];

					float pvidx2 = pColor[GetVoxelIdx(floor(wis[0]), floor(wis[1]), floor(wis[2]))]; //000

					float pq001 = pColor[GetVoxelIdx(floor(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float pq010 = pColor[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float pq011 = pColor[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), ceil(wis[2]))];
					float pq100 = pColor[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), floor(wis[2]))];
					float pq101 = pColor[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float pq110 = pColor[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float pq111 = pColor[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), ceil(wis[2]))];

					//Ʈ���� ������ ���� �Ϸ�





					//GVec3 temp=GVec3(pColor[3*vidx2], pColor[3 * vidx2+1], pColor[3 * vidx2+2]);
					//vidx2 = GetVoxelIdx(i, t, j); //j,t�� �ƴ� t,j
					//wis[0]  x
					//wis[1]  y
					//wis[2]  z



					float opresult = triLerp(wis[0], wis[2], wis[1], ovidx2, oq001, oq010, oq011, oq100, oq101, oq110, oq111);
					//if(opresult>0)
					//printf("%f", opresult);

					float ppresult = triLerp(wis[0], wis[2], wis[1], pvidx2, pq001, pq010, pq011, pq100, pq101, pq110, pq111);
					//if (ppresult > 0)
					//printf("%f", ppresult);
					//�� op

					//float pcresult = ;
					//�� pc




					op = (op + (opresult * (1 - op)));
					//if(op>0)
					//printf("%f", op);
					pc = (pc + ((opresult * (1 - op))*ppresult));
					//if(pc>0)
					//printf("%f", pc);

					if (op >= 1)
					{

						break;
					}

					t = t + 0.1;

					if (t >= Height)
					{
						break;
					}
				}

				color_out = pc;

				int idx = GetPixelIdx(i, j);

				color_out = MIN(color_out, 1.0);
				//color_out = MIN(color_out[0], 1.0);
				//color_out = MIN(color_out[1], 1.0);
				//color_out = MIN(color_out[2], 1.0);

				if (Acount == 1)
				{
					if (color_out > 0.7)
					{
						pImage[idx] = color_out * 255;

					}
					else if (color_out > 0.5)
					{
						pImage[idx + 1] = color_out * 255;
					}
					else if (color_out > 0.3)
					{
						pImage[idx + 1] = color_out * 255;
						pImage[idx + 2] = color_out * 255;

					}
					else
					{
						pImage[idx] = color_out * 255;
						pImage[idx + 1] = color_out * 255;
						pImage[idx + 2] = color_out * 255;
					}
				}
				else if (Ccount == 2)
				{
					pImage[idx] = color_out * 255;
					pImage[idx + 1] = color_out * 255;
					pImage[idx + 2] = color_out * 255;
				}


				t = 0;
				op = 0;
				pc = 0;


			}
			else if (count == 3)
			{

				///�ٽ�

				GPos3 p(i, (Width-cos(getRadian(45))*j - (Width/2)*(sqrt(2)-1) - 10), (cos(getRadian(45))*j) - (Width / 2)*(sqrt(2) - 1));
				GLine ray(p, GVec3(0, cos(getRadian(45)), sin(getRadian(45))));
				//std::cout<<p<<std::endl;

				double t = 0.0;

				//float alpha_out = 0.0;
				//GVec3 color_out = 0.0;
				float color_out = 0.0;


				GPos3 wis = ray.Eval(t); //��� �ִ���


										 //int vidx2 = GetVoxelIdx(wis[0], wis[2], wis[1]); //j,t�� �ƴ� t,j ����
										 //int vidx2 = GetVoxelIdx(i, t, j); //j,t�� �ƴ� t,j
										 //int a=floor(2.5); //2
										 //int b=ceil(4.4);//5
				float op = 0.0;
				float pc = 0.0;


				while (true)
				{
					if (op >= 0.95)
					{

						break;
					}


					if (t >= Height)
					{
						break;
					}
					
					

					if ( wis[0] >= Depth || wis[1] >= Width || wis[2] >= Height)
					{
						break;
					}


					
					wis = ray.Eval(t); //��� �ִ���

									   //float triLerp(float x, float y, float z, float q000, float q001, float q010, float q011, float q100, float q101, float q110, float q111)



									   //vidx2 = GetVoxelIdx(wis[0], wis[2], wis[1]); ����
									   //printf("wis[0] : %lf wis2 : %lf wis1 : %lf \n", wis[0], wis[2], wis[1]);



					float ovidx2 = pOpacity[GetVoxelIdx(floor(wis[0]), floor(wis[1]), floor(wis[2]))]; //000

					float oq001 = pOpacity[GetVoxelIdx(floor(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float oq010 = pOpacity[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float oq011 = pOpacity[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), ceil(wis[2]))];
					float oq100 = pOpacity[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), floor(wis[2]))];
					float oq101 = pOpacity[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float oq110 = pOpacity[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float oq111 = pOpacity[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), ceil(wis[2]))];

					float pvidx2 = pColor[GetVoxelIdx(floor(wis[0]), floor(wis[1]), floor(wis[2]))]; //000

					float pq001 = pColor[GetVoxelIdx(floor(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float pq010 = pColor[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float pq011 = pColor[GetVoxelIdx(floor(wis[0]), ceil(wis[1]), ceil(wis[2]))];
					float pq100 = pColor[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), floor(wis[2]))];
					float pq101 = pColor[GetVoxelIdx(ceil(wis[0]), floor(wis[1]), ceil(wis[2]))];
					float pq110 = pColor[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), floor(wis[2]))];
					float pq111 = pColor[GetVoxelIdx(ceil(wis[0]), ceil(wis[1]), ceil(wis[2]))];

					//Ʈ���� ������ ���� �Ϸ�





					//GVec3 temp=GVec3(pColor[3*vidx2], pColor[3 * vidx2+1], pColor[3 * vidx2+2]);
					//vidx2 = GetVoxelIdx(i, t, j); //j,t�� �ƴ� t,j
					//wis[0]  x
					//wis[1]  y
					//wis[2]  z



					float opresult = triLerp(wis[0], wis[2], wis[1], ovidx2, oq001, oq010, oq011, oq100, oq101, oq110, oq111);
					//if(opresult>0)
					//printf("%f", opresult);

					float ppresult = triLerp(wis[0], wis[2], wis[1], pvidx2, pq001, pq010, pq011, pq100, pq101, pq110, pq111);
					//if (ppresult > 0)
					//printf("%f", ppresult);
					//�� op

					//float pcresult = ;
					//�� pc




					op = (op + (opresult * (1 - op)));
					//if(op>0)
					//printf("%f", op);
					pc = (pc + ((opresult * (1 - op))*ppresult));
					//if(pc>0)
					//printf("%f", pc);

					
					t = t + 0.3;
					
					
					if (wis[1] < - Width/2*cos(getRadian(45)) || wis[2] < - Width/2*cos(getRadian(45)))
					{
						continue;
					}

					if (wis[0] < 0|| wis[1] < 0 || wis[2] < 0)
					{
						continue;
					}

					
				}

				color_out = pc;

				int idx = GetPixelIdx(i, j);

				color_out = MIN(color_out, 1.0);
				//color_out = MIN(color_out[0], 1.0);
				//color_out = MIN(color_out[1], 1.0);
				//color_out = MIN(color_out[2], 1.0);
				
				if (Acount == 1)
				{
					if (color_out > 0.7)
					{
						pImage[idx] = color_out * 255;

					}
					else if (color_out > 0.5)
					{
						pImage[idx + 1] = color_out * 255;
					}
					else if (color_out > 0.3)
					{
						pImage[idx + 1] = color_out * 255;
						pImage[idx + 2] = color_out * 255;

					}
					else
					{
						pImage[idx] = color_out * 255;
						pImage[idx + 1] = color_out * 255;
						pImage[idx + 2] = color_out * 255;
					}
				}
				else if (Ccount == 2)
				{
					pImage[idx] = color_out * 255;
					pImage[idx + 1] = color_out * 255;
					pImage[idx + 2] = color_out * 255;
				}
				
				


				t = 0;
				op = 0;
				pc = 0;

			}
			//GPos3 p(i, j, 0);
			//GLine ray(p, GVec3(0.0, 0, 1.0));



		}
	}
}
//printf("������ %f", lerp(1.6, 1.0, 2.0, 3, 4)); //check
float lerp(float ori, float x1, float x2, float q00, float q01)
{
	//printf("lerp ����\n");
	if ((x2 - ori) == 0)
	{
		//printf("1�������� : %f \n", q00);
		return q00;
	}
	else if ((ori - x1) == 0)
	{
		//printf("2�������� : %f \n", q01);
		return q01;
	}
	else
	{
		return ((x2 - ori)) * q00 + ((ori - x1) * q01);
	}


}
//float x1, float x2, float y1, float y2, float z1, float z2
float triLerp(float x, float y, float z, float q000, float q001, float q010, float q011, float q100, float q101, float q110, float q111)
{
	//x,y,z �ش���
	//x1,y1,z1 ���� ������
	//x2,y2,z2 ���� ū��

	float x1 = floor(x);
	float y1 = floor(y);
	float z1 = floor(z);

	float x2 = ceil(x);
	float y2 = ceil(y);
	float z2 = ceil(z);

	float x00 = lerp(x, x1, x2, q000, q100);
	float x10 = lerp(x, x1, x2, q010, q110);

	float x01 = lerp(x, x1, x2, q001, q101);
	float x11 = lerp(x, x1, x2, q011, q111);

	float r0 = lerp(y, y1, y2, x00, x01);
	float r1 = lerp(y, y1, y2, x10, x11);

	return lerp(z, z1, z2, r0, r1);
}

double getRadian(int _num)
{
	return _num * (PI / 180);
}
