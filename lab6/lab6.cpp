/************************************************************************/
/************************************************************************/
/*
/* Filename     :	lab6.cpp
/* Abstract     :	3090104732 ������ ʵ������OpenGL����
/* Reference	:	����, ͯ����, <<�����ͼ��ѧ�γ����>>, �㽭��ѧ������
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : May 25th, 2012
/*							
/************************************************************************/
/************************************************************************/

/*********************�������ӵĿ��ļ�**************************/
#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	
/***************************************************************/
#define GLEW_STATIC		// ��glew.h�е�˵�����waring c4273
#define GLUT_DISABLE_ATEXIT_HACK	//����glut.h�е�˵��������Ӵ���
#include <gl/glew.h>
#include <gl/glext.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BITMAP_ID 0x4D42

PFNGLMULTITEXCOORD1FARBPROC     glMultiTexCoord1fARB    = NULL;   
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB    = NULL;   
PFNGLMULTITEXCOORD3FARBPROC     glMultiTexCoord3fARB    = NULL;   
PFNGLMULTITEXCOORD4FARBPROC     glMultiTexCoord4fARB    = NULL;   
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB      = NULL;   

/************************************************************************/
/*							ȫ�ֱ���                                    */
/************************************************************************/
/* �Զ����������Ϣ */
#define TEXW 64
#define TEXH 64
static GLubyte texImage[TEXW][TEXW][4];

// ��������
GLfloat lightPos[] =   {5.0, 5.0, 5.0, 0.0};
GLfloat lightAmb[4] =  {0.5, 0.5, 0.5, 1.0};
GLfloat lightDiff[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat lightSpec[4] = {1.0, 1.0, 1.0, 1.0};

// �����������
GLfloat matAmb[4] =    {1.0, 1.0, 1.0, 1.0};
GLfloat matDiff[4] =   {1.0, 0.1, 0.2, 1.0};
GLfloat matSpec[4] =   {1.0, 1.0, 1.0, 1.0};

// �������������
GLfloat matCubeAmb[4] =    {1.0, 1.0, 1.0, 1.0};
GLfloat matCubeDiff[4] =   {1.0, 1.0, 1.0, 1.0};
GLfloat matCubeSpec[4] =   {1.0, 1.0, 1.0, 1.0};

// �����ʶ�����飬����4������ı�ʶ��
unsigned int texture[4];

// ��������ģʽ��0��1��ʾһ������2��ʾ�����������
unsigned int nTexMode = 0;

// ѡ��������0��ʾbmpͼƬ�ж�ȡ������1��ʾ�Լ����ɵ�����
unsigned int nTeapotTex = 0;

float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bText = true;  // �Ƿ�������ӳ��
bool bLight = true;  // �Ƿ�������
bool bBlend = true;  // �Ƿ�����������ں�
bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

// �۲����۲�����
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};


/************************************************************************/
/*							��������                                    */
/************************************************************************/

// �Զ�����������ĺ���
void makeTexImage(void);

// ��������
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

// ��������ĺ���
void texload(int i,char *filename);

// ��������ĺ���
void init();

// ������
void Draw_Leg();

// ������Ҫ��ͼ����
void Draw_Triangle();

// �Լ���������MySolidCube�ĺ���
void MySolidCube(GLdouble size);

// glut�ص�����
void redraw();
void updateView(int width, int height);
void reshape(int width, int height);
void idle();
void key(unsigned char k, int x, int y);

/************************************************************************/
/*							     ������                                 */
/************************************************************************/
int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("ʵ����_3090104732_������");
	
	init();  // ��������
	
	// ��ʼ����������Ԫ
	glMultiTexCoord1fARB = 
		(PFNGLMULTITEXCOORD1FARBPROC) wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord2fARB = 
		(PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord3fARB = 
		(PFNGLMULTITEXCOORD3FARBPROC) wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord4fARB = 
		(PFNGLMULTITEXCOORD4FARBPROC) wglGetProcAddress("glMultiTexCoord4fARB");
	glActiveTextureARB = 
		(PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
	
	// ��ӡ����Ԫ��
	GLint maxTextureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTextureUnits);
	printf("TextureUnits available =%d\n", maxTextureUnits);
	
	// �鿴֧�ֵ���չ
	const GLubyte *extensions = glGetString(GL_EXTENSIONS);
	printf("%s\n", extensions);
	
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	
	glutMainLoop(); 
	
	return 0;
}


/************************************************************************/
/*							     ��������                               */
/************************************************************************/
/** 
* ����������
* �����ʾ�����飬������������ı�ʾ��
* ����: ͨ��ָ�룬����filename ָ����bitmap�ļ������ݡ�
* ͬʱҲ����bitmap��Ϣͷ.(��֧��-bitλͼ)
*/
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;	// �ļ�ָ��
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap�ļ�ͷ
	unsigned char	*bitmapImage;		// bitmapͼ������
	int	imageIdx = 0;		// ͼ��λ������
	unsigned char	tempRGB;	// ��������
	
	// �ԡ�������+����ģʽ���ļ�filename 
	filePtr = fopen(filename, "rb"); 
	if (filePtr == NULL) return NULL;
	// ����bitmap�ļ�ͼ
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr); 
	// ��֤�Ƿ�Ϊbitmap�ļ�
	if (bitmapFileHeader.bfType != BITMAP_ID) 
	{
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// ����bitmap��Ϣͷ
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); 
	// ���ļ�ָ������bitmap����
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// Ϊװ��ͼ�����ݴ����㹻���ڴ�
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage]; 
	// ��֤�ڴ��Ƿ񴴽��ɹ�
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	
	// ����bitmapͼ������
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr); 
	// ȷ�϶���ɹ�
	if (bitmapImage == NULL) 
	{
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//����bitmap�б���ĸ�ʽ��BGR�����潻��R��B��ֵ���õ�RGB��ʽ
	for ( imageIdx = 0; 
		  (bitmapInfoHeader->biSizeImage) > (DWORD)imageIdx; 
		  imageIdx+=3 ) 
	{ 
		tempRGB = bitmapImage[imageIdx]; 
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2]; 
		bitmapImage[imageIdx + 2] = tempRGB; 
	}
	// �ر�bitmapͼ���ļ�
	fclose(filePtr); 
	return bitmapImage; 
}

// ��������ĺ�����
void texload(int i,char *filename)
{
	
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap��Ϣͷ
	unsigned char*   bitmapData;                                       // ��������
	
	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 
		0, 	    //mipmap���(ͨ��Ϊ����ʾ���ϲ�) 
		GL_RGB,	//����ϣ���������к졢�̡�������
		bitmapInfoHeader.biWidth, //��������������n�����б߿�+2 
		bitmapInfoHeader.biHeight, //����߶ȣ�������n�����б߿�+2 
		0, //�߿�(0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,	//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE, //ÿ����ɫ���ݵ�����
		bitmapData);	//bitmap����ָ��  
	
	
}

// ��������ĺ�����
void init()
{	           
	glGenTextures(4, texture);    // ��һ��������Ҫ���ɱ�ʾ���ĸ���, �ڶ������Ƿ��ر�ʾ��������
	texload(0,"Monet.bmp");
    texload(1,"Crack.bmp");
	texload(2,"Spot.bmp");

	// ���������Զ�������
	makeTexImage();		
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //�������ش洢ģʽ��������ȡ��ͼ�����ݵ��ж��뷽ʽ.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,TEXW,TEXH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Draw_Triangle()
{
	// ���ò������
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0);

	// ��������ջ��
	// GL_MODULATE��ʾ���������Ч�����
	// GL_REPLACE����ȫ����������ɫ
	if (bBlend)
	{
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	}
	else
	{
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
	}

	// Ϊ�����������
	// ����ת��������ѡ��ǰ����
	if (nTeapotTex == 0)
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]); 
	}
	else if (nTeapotTex == 1)
	{
		glBindTexture(GL_TEXTURE_2D, texture[3]); 
	}
	// ����ǰ��ɫ����Ϊ��ɫ(��Ҫ)������������Ϊ��ɫЧ�����
	glColor3f(1.0f,1.0f,1.0f); 
	
	
	glPushMatrix();
	glTranslatef(0, 0, 4+1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	
	// �������������
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	MySolidCube(1.0);
	glPopMatrix();
	
	// �������������
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	// �������������
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	// �������������
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	// �������������
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
}

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport
	
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	
	float whRatio = (GLfloat)width/(GLfloat)height;
	if (bPersp) 
	{
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	} 
	else 
	{
		glOrtho(-3 ,3, -3, 3,-100,100);
	}
	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
	
	wHeight = height;
	wWidth = width;
	
	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }
		
	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}
		
	case 'a': 
		{
			eye[0] -= 0.2f;
			center[0] -= 0.2f;
			break;
		}
	case 'd': 
		{
			eye[0] += 0.2f;
			center[0] += 0.2f;
			break;
		}
	case 'w': 
		{
			eye[1] -= 0.2f;
			center[1] -= 0.2f;
			break;
		}
	case 's': 
		{
			eye[1] += 0.2f;
			center[1] += 0.2f;
			break;
		}
	case 'z': 
		{
			eye[2] -= 0.2f;
			center[2] -= 0.2f;
			break;
		}
	case 'c': 
		{
			eye[2] += 0.2f;
			center[2] += 0.2f;
			break;
		}
	case 'l':   // ����/�رչ���
		bLight = !bLight;
		break;

	case 'b':
		bBlend = ! bBlend;
		break;
		
	case 't':  // ����/�ر�����
		bText = !bText;
		break;
		
	case 'm':  // ��������ģʽ
		nTexMode = (nTexMode+1)%3;
		break;
	case 'n':  // ѡ��������
		nTeapotTex = (nTeapotTex+1)%2;
		break;
	}
	
	updateView(wHeight, wWidth);
}

void redraw()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ����(0��0��0)���ӵ����� (0,5,50)��Y������
	
	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_DEPTH_TEST);
	if (bLight)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
	if (bText)
	{
		glEnable(GL_TEXTURE_2D);	
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Triangle();						// Draw triangle
	
	if (bAnim) fRotate    += 0.5f;
	glutSwapBuffers();
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	MySolidCube(1.0);
}

// ����д��������ĺ�����Ϊÿһ����ָ����������
static void MydrawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;
	
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
	
	for (i = 5; i >= 0; i--) 
	{
		if (nTexMode == 0)
		{
			// ����ת��������ѡ��ǰ����
			glBindTexture(GL_TEXTURE_2D, texture[1]); 
			// ����ǰ��ɫ����Ϊ��ɫ(��Ҫ)������������Ϊ��ɫЧ�����
			glColor3f(1.0f,1.0f,1.0f); 
			glBegin(type);
			glNormal3fv(&n[i][0]);
			
			glTexCoord2f(1.0,1.0);
			glVertex3f(v[faces[i][0]][0], v[faces[i][0]][1], v[faces[i][0]][2]);
			
			glTexCoord2f(1.0,0.0);
			glVertex3f(v[faces[i][1]][0], v[faces[i][1]][1], v[faces[i][1]][2]);
			
			glTexCoord2f(0.0,0.0);
			glVertex3f(v[faces[i][2]][0], v[faces[i][2]][1], v[faces[i][2]][2]);
			
			glTexCoord2f(0.0,1.0);
			glVertex3f(v[faces[i][3]][0], v[faces[i][3]][1], v[faces[i][3]][2]);
			
			glEnd();
		}
		else if (nTexMode == 1)
		{
			// ����ת��������ѡ��ǰ����
			glBindTexture(GL_TEXTURE_2D, texture[2]); 
			// ����ǰ��ɫ����Ϊ��ɫ(��Ҫ)������������Ϊ��ɫЧ�����
			glColor3f(1.0f,1.0f,1.0f); 
			glBegin(type);
			glNormal3fv(&n[i][0]);
			
			glTexCoord2f(1.0,1.0);
			glVertex3f(v[faces[i][0]][0], v[faces[i][0]][1], v[faces[i][0]][2]);
			
			glTexCoord2f(1.0,0.0);
			glVertex3f(v[faces[i][1]][0], v[faces[i][1]][1], v[faces[i][1]][2]);
			
			glTexCoord2f(0.0,0.0);
			glVertex3f(v[faces[i][2]][0], v[faces[i][2]][1], v[faces[i][2]][2]);
			
			glTexCoord2f(0.0,1.0);
			glVertex3f(v[faces[i][3]][0], v[faces[i][3]][1], v[faces[i][3]][2]);
			
			glEnd();
		}
		else if (nTexMode == 2)    // ��������ģʽ
		{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			// ����ת��������ѡ��ǰ����
			glBindTexture(GL_TEXTURE_2D, texture[1]); 
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			// ����ת��������ѡ��ǰ����
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			
			glBegin(type);
			glNormal3fv(&n[i][0]);

			// Ϊ��ͬ����Ԫ�е�����ָ����������
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0, 1.0);
			glVertex3f(v[faces[i][0]][0], v[faces[i][0]][1], v[faces[i][0]][2]);
			
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0, 0.0);
			glVertex3f(v[faces[i][1]][0], v[faces[i][1]][1], v[faces[i][1]][2]);
			
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0, 0.0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0, 0.0);
			glVertex3f(v[faces[i][2]][0], v[faces[i][2]][1], v[faces[i][2]][2]);
			
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0, 1.0);
			glVertex3f(v[faces[i][3]][0], v[faces[i][3]][1], v[faces[i][3]][2]);
			
			glEnd();
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}
	}
}

void MySolidCube(GLdouble size)
{
	MydrawBox(size, GL_QUADS);
}

// �Զ�����������ĺ���
void makeTexImage(void)
{
	int i, j, c;
	for (i = 0; i < TEXH; i++) 
	{
		for (j = 0; j < TEXW; j++) 
		{
			c = ((((i&0x8)==0)^((j&0x8))==0))*255;
			if (c == 0)
			{
				texImage[i][j][0] = (GLubyte) c;
				texImage[i][j][1] = (GLubyte) c;
				texImage[i][j][2] = (GLubyte) c;
				texImage[i][j][3] = (GLubyte) 255;
			}
			else
			{
				texImage[i][j][0] = (GLubyte) 225;
				texImage[i][j][1] = (GLubyte) 50;
				texImage[i][j][2] = (GLubyte) 50;
				texImage[i][j][3] = (GLubyte) 255;
			}
		}
	}
}
