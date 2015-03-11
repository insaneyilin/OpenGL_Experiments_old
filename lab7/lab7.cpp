/************************************************************************/
/************************************************************************/
/*
/* Filename     :	all-bunny.cpp
/* Abstract     :	实验七_3090104732_桂义林_代码
/* Reference	:	唐敏, 童若峰, <<计算机图形学课程设计>>, 浙江大学出版社
/* Version      :	1.0										
/* Author       :	桂义林											
/* Accomplished date : May. 26th, 2012
/*							
/************************************************************************/
/************************************************************************/

#define GLUT_DISABLE_ATEXIT_HACK	//按照glut.h中的说明解决连接错误
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/************************************************************************/
/*							全局变量定义                                */
/************************************************************************/
float fTranslate;
float fRotate = 156.5f;
float fScale     = 1.0f;	// set inital scale value to 1.0f

float whRatio;

bool bPersp = true;
bool bAnim = false;
bool bWire = false;

// 表示物体是否被选中
bool bSelectBunny = false;
bool bSelectDesk = false;

int wHeight = 0;
int wWidth = 0;

// 显示列表标识
GLint dl = 0;

// 相关材质
GLfloat mat_desk1[] = {0.3, 0.3, 0.3, 0.0};    // 桌子材质
GLfloat mat_bunny1[] = {0.3, 0.3, 0.3, 0.0};  // Bunny材质
GLfloat mat_desk2[] = {1.0, 0.0, 0.0, 0.0};    // 桌子材质
GLfloat mat_bunny2[] = {0.6, 0.5, 0.0, 0.0};  // Bunny材质

// 观察位置与观察中心
float center[] = {0, -0.8, -6};
float eye[] = {0, 1.2, 2};

// 绘制模式，0、1、2分别对应naive、顶点数组、显示列表三种方式
int  drawMode = 0;


/************************************************************************/
/*								函数声明                                */
/************************************************************************/
void Draw_Leg();

extern void drawNaive();
extern void drawVA();
extern GLint Gen3DObjectList();

void drawDL();

void drawBunny();

void Draw_Desk();

void Draw_Triangle(GLenum mode = GL_RENDER);

void Draw_Leg();

//  处理击中记录的函数
void ProcessPicks(GLint nPicks, GLuint pickBuffer[]);

/************************************************************************/
/*							回调函数声明                                */
/************************************************************************/
void updateView(int width, int height);
void reshape(int width, int height);
void idle();
void key(unsigned char k, int x, int y);
void getFPS();
void redraw();
// 鼠标点击响应函数
void MouseClick(int button,int action,int xMouse,int yMouse);

/************************************************************************/
/*							主函数                                      */
/************************************************************************/
int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("实验七_3090104732_桂义林");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutMouseFunc(MouseClick);  // 鼠标点击响应函数

	dl = Gen3DObjectList();  // 生成显示列表

	glutMainLoop();
	return 0;
}

/************************************************************************/
/*							函数定义                                    */
/************************************************************************/
#define BUFSIZE 512

//  处理击中记录的函数
void ProcessPicks(GLint nPicks, GLuint pickBuffer[])
{
	if (nPicks <= 0)
	{
		return;
	}
	GLint i;
	GLuint name, *ptr, minZ, *ptrNames, numberOfNames;
    minZ = 0xffffffff;
	printf("选中的数目为%d个\n",nPicks);
	ptr=pickBuffer;
	
	for(i = 0; i < nPicks; i++)
	{
		name = *ptr;    // 击中记录的名字数
		ptr++;  // 最小深度记录
		if (*ptr < minZ)  // 找到最小深度的物体名字
		{
			numberOfNames = name;
			minZ = *ptr;
			ptrNames = ptr+2;  // 当前ptr指向最小深度记录，ptr+1指向最大深度记录，ptr+2指向击中记录中的第一个名字
		}
		ptr += name + 2; // ptr 移动到下一个击中记录
	}
	if (*ptrNames == 1)
	{
		printf("你选择了Bunny\n");
		bSelectBunny = !bSelectBunny;
	}
	if(*ptrNames == 2)
	{
		printf("你选择了Desk\n");
		bSelectDesk = !bSelectDesk;
	}
	printf("\n\n");
}

// 鼠标点击响应函数
void MouseClick(int button,int action,int xMouse,int yMouse)
{
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)  // 鼠标左键按下
	{
		GLuint selectBuf[BUFSIZE];
		GLint hits;
		GLint viewport[4];		
		glGetIntegerv (GL_VIEWPORT, viewport);
		glSelectBuffer (BUFSIZE, selectBuf);  //设置选择缓冲区
		
		// 进入选择模式
		glRenderMode(GL_SELECT);				// Enter the SELECT render mode
		glInitNames();   //初始化名字堆栈
		glPushName(-1);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
        glLoadIdentity();
		
		//定义一个2×2的选择区域
		gluPickMatrix((GLdouble) xMouse, (GLdouble) (viewport[3] - yMouse), 2.0, 2.0, viewport);
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);
		
		// 绘图
		Draw_Triangle(GL_SELECT);
		
		glPopMatrix ();
		glFlush ();
		
		// 恢复投影变换
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0,0,wWidth,wHeight);
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
		
		// 获得击中记录并处理
		hits = glRenderMode (GL_RENDER);
		
		ProcessPicks(hits, selectBuf);
		updateView(wHeight, wWidth);
	}
}

void drawDL()
{
	glCallList(dl);
}

void drawBunny()
{
	// 根据物体的选中状态设置材质以改变颜色
	if (bSelectBunny)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_bunny2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_bunny1);
	}
	glRotatef(90, 1, 0, 0);
	glScalef(3, 3, 3);
	if (drawMode == 0)
		drawNaive();
	else if (drawMode == 1)
		drawVA();
	else
		drawDL();
}

void Draw_Triangle(GLenum mode) // This function draws a triangle with RGB colors
{
	if(mode == GL_SELECT) glLoadName(1); //压入名字堆栈
	
	glPushMatrix();
	glTranslatef(-1, -1, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -1, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, -1, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1, 1, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 1, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 1, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1, 0, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, 5.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 0, 5.5);
	drawBunny();
	glPopMatrix();
	
	//###################################
	
	glPushMatrix();
	glTranslatef(-1, -1, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -1, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, -1, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1, 1, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 1, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 1, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1, 0, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, 7.5);
	drawBunny();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 0, 7.5);
	drawBunny();
	glPopMatrix();
	
	if(mode == GL_SELECT) glLoadName(2); //压入名字堆栈
	Draw_Desk();
}

void Draw_Desk()
{
	// 根据物体的选中状态设置材质以改变颜色
	if (bSelectDesk)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
	}
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();
	
	if (bSelectDesk)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
	}
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	if (bSelectDesk)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
	}
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	if (bSelectDesk)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
	}
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	if (bSelectDesk)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
	}
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	whRatio = (GLfloat)width/(GLfloat)height;
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
	case '0': {drawMode++; drawMode %= 3; break;}

	case 'a': {
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;
			  }
	case 'd': {
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
			  }
	case 'w': {
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
			  }
	case 's': {
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
			  }
	case 'z': {
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
			  }
	case 'c': {
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
			  }
	}

	updateView(wHeight, wWidth);
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (drawMode == 0)
		strcpy(mode, "naive");
	else if (drawMode == 1)
		strcpy(mode, "vertex array");
	else
		strcpy(mode, "display list");

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) 
	{
		sprintf(buffer,"FPS:%4.2f %s",
			frame*1000.0/(time-timebase), mode);
		timebase = time;		
		frame = 0;
	}

	// glutSetWindowTitle(buffer);
	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);// 选择投影矩阵
	glPushMatrix();// 保存原矩阵
	glLoadIdentity();// 装入单位矩阵
	glOrtho(0,480,0,480,-1,1);// 位置正投影
	glMatrixMode(GL_MODELVIEW);// 选择Modelview矩阵
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
	glPushMatrix();// 保存原矩阵
	glLoadIdentity();// 装入单位矩阵*/
	glRasterPos2f(10,10);
	for (c=buffer; *c != '\0'; c++) 
	{		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);// 选择投影矩阵
	glPopMatrix();// 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);// 选择Modelview矩阵
	glPopMatrix();// 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);	
}

void redraw()
{
	glClearColor(0.0,0.0,0.0,0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);	// 启用法向归一化
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = {5,5,5,1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Triangle();						// Draw triangle

	if (bAnim) fRotate    += 0.5f;

	getFPS();

	glutSwapBuffers();
}
