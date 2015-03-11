/************************************************************************/
/************************************************************************/
/*
/* Filename     :	Desk.cpp
/* Abstract     :	A simple example of Geometry Transformation in OpenGL
/* Reference	:	唐敏, 童若峰, <<计算机图形学课程设计>>, 浙江大学出版社;
/*					实验二参考代码;
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : March. 22th, 2012
/*							
/************************************************************************/
/************************************************************************/
#include <gl/glut.h>
#include <stdlib.h>

float fTranslate;
float fRotate;
float fScale = 1.0f;// set inital scale value to 1.0f

// 绘制桌面
void DrawDesktop()
{
	glScalef(1.0f, 0.2f, 0.8f);
	glutWireCube(5.0f);
}

// 绘制桌腿1
void DrawLeg1()
{
	glTranslatef(-1.5, -2.0*5.0, 1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	
	glutWireCube(1.0f);
}

// 绘制桌腿2
void DrawLeg2()
{
	glTranslatef(1.5, -2.0*5.0, 1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	glutWireCube(1.0f);
}

// 绘制桌腿3
void DrawLeg3()
{
	glTranslatef(1.5, -2.0*5.0, -1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	glutWireCube(1.0f);
}

// 绘制桌腿4
void DrawLeg4()
{
	glTranslatef(-1.5, -2.0*5.0, -1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	glutWireCube(1.0f);
}

// 使用层次建模法绘制桌子
void Draw_Desk()
{
	DrawDesktop();		// 画桌面
	glPushMatrix();
	
	DrawLeg1();			// 画桌腿1
	glPopMatrix();
	glPushMatrix();
	
	DrawLeg2();			// 画桌腿2
	glPopMatrix();
	glPushMatrix();
	
	DrawLeg3();			// 画桌腿3
	glPopMatrix();
	glPushMatrix();
	
	DrawLeg4();			// 画桌腿4
	glPopMatrix();
	glPushMatrix();

	glPopMatrix();		// Don't forget this!
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
// If want display in wireframe mode
// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();							// Reset The Current Modelview Matrix
	
	glPushMatrix();
		glTranslatef(-9.0f, 0.0f,-24.0f);		// 左边的桌子
		glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		Draw_Desk();							// 绘制桌子
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-24.0f);		// 中间的桌子
		glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		Draw_Desk();							// 绘制桌子
	glPopMatrix();


	glPushMatrix();
		glTranslatef(9.0f,0.0f,-24.0f);			// 右边的桌子
		glScalef(fScale, fScale, fScale);		// Scale with the same value in x,y,z direction
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		Draw_Desk();							// 绘制桌子
	glPopMatrix();


	fTranslate += 0.015f;
	fRotate    += 0.5f;
	fScale     -= 0.005f;

	if(fTranslate > 1.5f) fTranslate = 0.0f;
	if(fScale < 0.5f)     fScale     = 1.0f;
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);                                                     
	int windowHandle = glutCreateWindow("实验二_by桂义林 3090104732");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);			
	glutIdleFunc(idle);					

	glutMainLoop();

	return 0;
}
