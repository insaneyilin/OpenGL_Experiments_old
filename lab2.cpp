/************************************************************************/
/************************************************************************/
/*
/* Filename     :	Desk.cpp
/* Abstract     :	A simple example of Geometry Transformation in OpenGL
/* Reference	:	����, ͯ����, <<�����ͼ��ѧ�γ����>>, �㽭��ѧ������;
/*					ʵ����ο�����;
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

// ��������
void DrawDesktop()
{
	glScalef(1.0f, 0.2f, 0.8f);
	glutWireCube(5.0f);
}

// ��������1
void DrawLeg1()
{
	glTranslatef(-1.5, -2.0*5.0, 1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	
	glutWireCube(1.0f);
}

// ��������2
void DrawLeg2()
{
	glTranslatef(1.5, -2.0*5.0, 1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	glutWireCube(1.0f);
}

// ��������3
void DrawLeg3()
{
	glTranslatef(1.5, -2.0*5.0, -1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	glutWireCube(1.0f);
}

// ��������4
void DrawLeg4()
{
	glTranslatef(-1.5, -2.0*5.0, -1.0*1.0/0.8);
	glScalef(1.0f, 3.0f, 1.0f);
	glScalef(1.0f, 5.0f, 1.0f/0.8f);
	glutWireCube(1.0f);
}

// ʹ�ò�ν�ģ����������
void Draw_Desk()
{
	DrawDesktop();		// ������
	glPushMatrix();
	
	DrawLeg1();			// ������1
	glPopMatrix();
	glPushMatrix();
	
	DrawLeg2();			// ������2
	glPopMatrix();
	glPushMatrix();
	
	DrawLeg3();			// ������3
	glPopMatrix();
	glPushMatrix();
	
	DrawLeg4();			// ������4
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
		glTranslatef(-9.0f, 0.0f,-24.0f);		// ��ߵ�����
		glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		Draw_Desk();							// ��������
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-24.0f);		// �м������
		glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		Draw_Desk();							// ��������
	glPopMatrix();


	glPushMatrix();
		glTranslatef(9.0f,0.0f,-24.0f);			// �ұߵ�����
		glScalef(fScale, fScale, fScale);		// Scale with the same value in x,y,z direction
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		Draw_Desk();							// ��������
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
	int windowHandle = glutCreateWindow("ʵ���_by������ 3090104732");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);			
	glutIdleFunc(idle);					

	glutMainLoop();

	return 0;
}
