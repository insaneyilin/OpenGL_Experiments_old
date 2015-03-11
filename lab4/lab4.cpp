/************************************************************************/
/************************************************************************/
/*
/* Filename     :	main.cpp
/* Abstract     :	3090104732 ������ ʵ���ģ�OpenGL��ʾ�б�
/* Reference	:	����, ͯ����, <<�����ͼ��ѧ�γ����>>, �㽭��ѧ������
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : April 26th, 2012
/*							
/************************************************************************/
/************************************************************************/
#define GLUT_DISABLE_ATEXIT_HACK   
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stanford_bunny.h"

float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f
float fDistance = 0.2f;

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

// ����Ƿ�ʹ����ʾ�б�
bool bDrawList = false;

// �ֱ����Ƿ����Bunny��Desk��TeaPot
bool bDrawBunny = true;
bool bDrawDesk = true;
bool bDrawTeaPot = true;

int wHeight = 0;
int wWidth = 0;

// �ֱ�����ʾ�б�ı�ʶ��
GLint tableList = 0;
GLint bunnylist = 1;
GLint TeaPotlist = 2;

void Draw_Leg();

// �������ӵ���ʾ�б�
GLint GenTableList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

    glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glEndList();

	return lid;
}

// ����Bunny����ʾ�б�
GLint GenBunnyList()
{
	GLint lib = glGenLists(2);
	glNewList(lib, GL_COMPILE);

	glPushMatrix();
	glTranslatef(1.5, 0, 4+1);
	glRotatef(90, 1, 0, 0);
	glScalef(4,4,4);
	glColor3f(0.5,0.5,0.5);
	DrawBunny();
	glPopMatrix();	
	
	glEndList();
	
	return lib;
}

// �����������ʾ�б�
GLint GenTeaPotList()
{
	GLint lit = glGenLists(3);
	glNewList(lit, GL_COMPILE);
	
	glPushMatrix();
	glTranslatef(-1.5, 0, 4+1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();	
	glEndList();
	
	return lit;
}

// ʹ����ʾ�б�ʽ����
void Draw_Table_List()
{
	if (bDrawDesk) glCallList(tableList);
	if (bDrawBunny) glCallList(bunnylist);
	if (bDrawTeaPot) glCallList(TeaPotlist);
}

// ����ʾ�б�ʽ����
void Draw_Table() // This function draws a table and bunny with RGB colors
{
	if (bDrawBunny)
	{
		glPushMatrix();
		glTranslatef(1.5, 0, 4+1);
		glRotatef(90, 1, 0, 0);
		glScalef(4,4,4);
		glColor3f(0.5,0.5,0.5);
		DrawBunny();
		glPopMatrix();
	}
	
	if (bDrawTeaPot)
	{
		glPushMatrix();
		glTranslatef(-1.5, 0, 4+1);
		glRotatef(90, 1, 0, 0);
		glutSolidTeapot(1);
		glPopMatrix();
	}

	if (bDrawDesk)
	{
		glPushMatrix();
		glTranslatef(0, 0, 3.5);
		glScalef(5, 4, 1);
		glutSolidCube(1.0);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(1.5, 1, 1.5);
		Draw_Leg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-1.5, 1, 1.5);
		Draw_Leg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(1.5, -1, 1.5);
		Draw_Leg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-1.5, -1, 1.5);
		Draw_Leg();
		glPopMatrix();
	}

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

	float whRatio = (GLfloat)width/(GLfloat)height;
	if (bPersp==1)
        gluPerspective(45,1,1,100);	
	else  
	    glOrtho(-3 ,3, -3, 3,-100,100);

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

// ����۲��͹۲�����
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

// ������Ӧ����
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }

	case 'p': {bPersp = !bPersp; updateView(560,560);break; }

	case ' ': {bAnim = !bAnim; break;}

	case 'o': {bWire = !bWire; break;}

	case 'a': {eye[0]=eye[0]+fDistance;center[0]=center[0]+fDistance;
		break;
			  }
	case 'd': {eye[0]=eye[0]-fDistance;center[0]=center[0]-fDistance;
		break;
			  }
	case 'w': {eye[1]=eye[1]-fDistance;center[1]=center[1]-fDistance;
        break;
			  }
	case 's': {eye[1]=eye[1]+fDistance;center[1]=center[1]+fDistance;
		break;
			  }
	case 'z': {eye[2]=eye[2]*0.95;
		break;
			  }
	case 'c': {eye[2]=eye[2]*1.05;
		break;
			  }
	case 'l': bDrawList = !bDrawList;	// 'l'���л���ʾ�б�ͷ���ʾ�б���Ʒ�ʽ
		break;
	case '1':							// ���ּ�'1'��Ӧ����Bunny
		bDrawBunny = !bDrawBunny;
		break;
	case '2':							// ���ּ�'2'��Ӧ���Ʋ��
		bDrawTeaPot = !bDrawTeaPot;
		break;
	case '3':							// ���ּ�'3'��Ӧ��������
		bDrawDesk = !bDrawDesk;
		break;
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy(mode, "display list");
	else
		strcpy(mode, "naive");

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) 
	{
		sprintf(buffer,"FPS:%4.2f %s",
			frame*1000.0/(time-timebase), mode);
		timebase = time;		
		frame = 0;
	}

	//glutSetWindowTitle(buffer);
	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);// ѡ��ͶӰ����
	glPushMatrix();// ����ԭ����
	glLoadIdentity();// װ�뵥λ����
	glOrtho(0,480,0,480,-1,1);// λ����ͶӰ
	glMatrixMode(GL_MODELVIEW);// ѡ��Modelview����
	glPushMatrix();// ����ԭ����
	glLoadIdentity();// װ�뵥λ����*/
	glRasterPos2f(10,10);
	for (c=buffer; *c != '\0'; c++) 
	{		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);// ѡ��ͶӰ����
	glPopMatrix();// ����Ϊԭ�������
	glMatrixMode(GL_MODELVIEW);// ѡ��Modelview����
	glPopMatrix();// ����Ϊԭ�������
	glEnable(GL_DEPTH_TEST);	
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������

	if (bWire) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST); // ������Ȳ���
	glEnable(GL_LIGHTING);   // ��������
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = {5,5,5,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,white);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	
	
//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);

	if(!bDrawList)
		Draw_Table();						// old way
	else 
		Draw_Table_List();                  // new way

//	Gen3DObjectList();

	
	if (bAnim) fRotate    += 0.5f;

	getFPS();

	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("3090104732 ������ ʵ����");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	// ������ʾ�б�
	tableList = GenTableList();
	bunnylist = GenBunnyList();
	TeaPotlist = GenTeaPotList();

	glutMainLoop();
	return 0;
}


