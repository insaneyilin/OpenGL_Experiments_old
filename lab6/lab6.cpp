/************************************************************************/
/************************************************************************/
/*
/* Filename     :	lab6.cpp
/* Abstract     :	3090104732 桂义林 实验六，OpenGL纹理
/* Reference	:	唐敏, 童若峰, <<计算机图形学课程设计>>, 浙江大学出版社
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : May 25th, 2012
/*							
/************************************************************************/
/************************************************************************/

/*********************包含链接的库文件**************************/
#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	
/***************************************************************/
#define GLEW_STATIC		// 按glew.h中的说明解决waring c4273
#define GLUT_DISABLE_ATEXIT_HACK	//按照glut.h中的说明解决连接错误
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
/*							全局变量                                    */
/************************************************************************/
/* 自定义纹理的信息 */
#define TEXW 64
#define TEXH 64
static GLubyte texImage[TEXW][TEXW][4];

// 光照属性
GLfloat lightPos[] =   {5.0, 5.0, 5.0, 0.0};
GLfloat lightAmb[4] =  {0.5, 0.5, 0.5, 1.0};
GLfloat lightDiff[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat lightSpec[4] = {1.0, 1.0, 1.0, 1.0};

// 茶壶材质属性
GLfloat matAmb[4] =    {1.0, 1.0, 1.0, 1.0};
GLfloat matDiff[4] =   {1.0, 0.1, 0.2, 1.0};
GLfloat matSpec[4] =   {1.0, 1.0, 1.0, 1.0};

// 立方体材质属性
GLfloat matCubeAmb[4] =    {1.0, 1.0, 1.0, 1.0};
GLfloat matCubeDiff[4] =   {1.0, 1.0, 1.0, 1.0};
GLfloat matCubeSpec[4] =   {1.0, 1.0, 1.0, 1.0};

// 纹理标识符数组，保存4个纹理的标识符
unsigned int texture[4];

// 多重纹理模式，0、1表示一张纹理，2表示两张纹理叠加
unsigned int nTexMode = 0;

// 选择茶壶纹理，0表示bmp图片中读取的纹理，1表示自己生成的纹理
unsigned int nTeapotTex = 0;

float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bText = true;  // 是否开启纹理映射
bool bLight = true;  // 是否开启光照
bool bBlend = true;  // 是否光照与纹理融合
bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

// 观察点与观察中心
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};


/************************************************************************/
/*							函数声明                                    */
/************************************************************************/

// 自定义生成纹理的函数
void makeTexImage(void);

// 读纹理函数
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

// 加载纹理的函数
void texload(int i,char *filename);

// 定义纹理的函数
void init();

// 画桌腿
void Draw_Leg();

// 包含主要绘图代码
void Draw_Triangle();

// 自己定义的替代MySolidCube的函数
void MySolidCube(GLdouble size);

// glut回调函数
void redraw();
void updateView(int width, int height);
void reshape(int width, int height);
void idle();
void key(unsigned char k, int x, int y);

/************************************************************************/
/*							     主函数                                 */
/************************************************************************/
int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("实验六_3090104732_桂义林");
	
	init();  // 加载纹理
	
	// 初始化多重纹理单元
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
	
	// 打印纹理单元数
	GLint maxTextureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &maxTextureUnits);
	printf("TextureUnits available =%d\n", maxTextureUnits);
	
	// 查看支持的扩展
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
/*							     函数定义                               */
/************************************************************************/
/** 
* 读纹理函数：
* 纹理标示符数组，保存两个纹理的标示符
* 描述: 通过指针，返回filename 指定的bitmap文件中数据。
* 同时也返回bitmap信息头.(不支持-bit位图)
*/
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;	// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
	unsigned char	*bitmapImage;		// bitmap图像数据
	int	imageIdx = 0;		// 图像位置索引
	unsigned char	tempRGB;	// 交换变量
	
	// 以“二进制+读”模式打开文件filename 
	filePtr = fopen(filename, "rb"); 
	if (filePtr == NULL) return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr); 
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) 
	{
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); 
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage]; 
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	
	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr); 
	// 确认读入成功
	if (bitmapImage == NULL) 
	{
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for ( imageIdx = 0; 
		  (bitmapInfoHeader->biSizeImage) > (DWORD)imageIdx; 
		  imageIdx+=3 ) 
	{ 
		tempRGB = bitmapImage[imageIdx]; 
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2]; 
		bitmapImage[imageIdx + 2] = tempRGB; 
	}
	// 关闭bitmap图像文件
	fclose(filePtr); 
	return bitmapImage; 
}

// 加载纹理的函数：
void texload(int i,char *filename)
{
	
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
	unsigned char*   bitmapData;                                       // 纹理数据
	
	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 
		0, 	    //mipmap层次(通常为，表示最上层) 
		GL_RGB,	//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2 
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2 
		0, //边框(0=无边框, 1=有边框) 
		GL_RGB,	//bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的类型
		bitmapData);	//bitmap数据指针  
	
	
}

// 定义纹理的函数：
void init()
{	           
	glGenTextures(4, texture);    // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
	texload(0,"Monet.bmp");
    texload(1,"Crack.bmp");
	texload(2,"Spot.bmp");

	// 下面生成自定义纹理
	makeTexImage();		
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //设置像素存储模式控制所读取的图像数据的行对齐方式.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,TEXW,TEXH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Draw_Triangle()
{
	// 设置茶壶材质
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0);

	// 纹理与光照混合
	// GL_MODULATE表示纹理与光照效果混合
	// GL_REPLACE则完全采用纹理颜色
	if (bBlend)
	{
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	}
	else
	{
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
	}

	// 为茶壶加载纹理
	// 从已转载纹理中选择当前纹理
	if (nTeapotTex == 0)
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]); 
	}
	else if (nTeapotTex == 1)
	{
		glBindTexture(GL_TEXTURE_2D, texture[3]); 
	}
	// 将当前颜色设置为白色(重要)，可以试试设为红色效果如何
	glColor3f(1.0f,1.0f,1.0f); 
	
	
	glPushMatrix();
	glTranslatef(0, 0, 4+1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	
	// 设置立方体材质
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	MySolidCube(1.0);
	glPopMatrix();
	
	// 设置立方体材质
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	// 设置立方体材质
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	// 设置立方体材质
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCubeDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCubeSpec);
	
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	// 设置立方体材质
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
	case 'l':   // 开启/关闭光照
		bLight = !bLight;
		break;

	case 'b':
		bBlend = ! bBlend;
		break;
		
	case 't':  // 开启/关闭纹理
		bText = !bText;
		break;
		
	case 'm':  // 多重纹理模式
		nTexMode = (nTexMode+1)%3;
		break;
	case 'n':  // 选择茶壶纹理
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
		0, 1, 0);				// 场景(0，0，0)的视点中心 (0,5,50)，Y轴向上
	
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

// 重新写画立方体的函数，为每一个面指定纹理坐标
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
			// 从已转载纹理中选择当前纹理
			glBindTexture(GL_TEXTURE_2D, texture[1]); 
			// 将当前颜色设置为白色(重要)，可以试试设为红色效果如何
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
			// 从已转载纹理中选择当前纹理
			glBindTexture(GL_TEXTURE_2D, texture[2]); 
			// 将当前颜色设置为白色(重要)，可以试试设为红色效果如何
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
		else if (nTexMode == 2)    // 多重纹理模式
		{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			// 从已转载纹理中选择当前纹理
			glBindTexture(GL_TEXTURE_2D, texture[1]); 
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			// 从已转载纹理中选择当前纹理
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			
			glBegin(type);
			glNormal3fv(&n[i][0]);

			// 为不同纹理单元中的纹理指定纹理坐标
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

// 自定义生成纹理的函数
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
