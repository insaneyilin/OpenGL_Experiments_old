/************************************************************************/
/************************************************************************/
/*
/* Filename     :	SixRayStar.cpp
/* Abstract     :	A simple example of drawing a six-ray star with OpenGL,
/*					Press left button of the mouse will change the color.
/* Reference	:	����, ͯ����, <<�����ͼ��ѧ�γ����>>, �㽭��ѧ������
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : March. 8th, 2012
/*							
/************************************************************************/
/************************************************************************/
#define GLUT_DISABLE_ATEXIT_HACK	//����glut.h�е�˵��������Ӵ���
#include <gl/glut.h>

static int iColorflag = 1; /* �����ж��Ƿ�Ϊ��������ɫ */

/************************************************************************/
/*								��������                                */
/************************************************************************/
/* ��������ɫ�������� */
void DrawSixRayStar();

/* ���Ʋ�ɫ�������� */
void DrawColoredSixRayStar();

/* �����¼��ص����� */
void display();

/* ��������Ӧ����, �������л���ʾͼ�� */
void processMouse(int button,int state,int x,int y);


/************************************************************************/
/*								������									*/
/************************************************************************/
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);	/* ��ʼ��glut */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); /* RGBA��ɫģʽ; ˫���� */
	
	int windowHandle = glutCreateWindow("Colored Six-Ray Star"); /* �������� */

	glutDisplayFunc(display); /* ���ûص����� */
	glutMouseFunc(processMouse);

	glutMainLoop();
	return 0;
}

/************************************************************************/
/*								��������                                */
/************************************************************************/
/* �����¼��ص����� */
void display()
{
	/* ��ʼ������ɫ */
	if (iColorflag == 0) 
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	/* ���ɫ��������Ϊ��ɫ */
		glColor3f(0.0f, 0.0f, 0.0f);	/* ��ͼɫ */
	}
	else 
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	/* ���ɫ��������Ϊ��ɫ */
		glColor3f(0.0f, 0.0f, 0.0f);	/* ��ͼɫ */
	}
	
	glClear(GL_COLOR_BUFFER_BIT); /* �����ɫ���� */
	
	if (iColorflag == 0)
	{
		DrawColoredSixRayStar();
	}
	else
	{
		DrawSixRayStar();
	}
	
	glFlush();		/* ˢ��������� */
	glutSwapBuffers();  /* �������������� */
}

/* ��������Ӧ����, �������л���ʾͼ�� */
void processMouse(int button,int state,int x,int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		iColorflag = !iColorflag;
	
	//ˢ�´���
	glutPostRedisplay(); 
}

/* ����δ��ɫ�������� */
void DrawSixRayStar()
{
	glShadeModel(GL_FLAT);	/* ���ö������ɫģʽ */

	glColor3f(1, 1, 1);	/* ʹ�ð�ɫ��ͼɫ */

	/* ����12������������������� */
	/* ��һ�������� */
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(0.0f, 0.5f);
	glVertex2d(0.13f, 0.3f);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(0.13f, 0.3f);
	glVertex2f(0.4f, 0.3f);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2f(0.4f, 0.3f);
	glVertex2d(0.26, 0);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(0.4f, -0.3f);
	glVertex2d(0.26, 0);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(0.13f, -0.3f);
	glVertex2f(0.4f, -0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2f(0.0f, -0.5f);
	glVertex2d(0.13f, -0.3f);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(0.0f, 0.5f);
	glVertex2d(-0.13f, 0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(-0.13f, 0.3f);
	glVertex2f(-0.4f, 0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2f(-0.4f, 0.3f);
	glVertex2d(-0.26, 0);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(-0.4f, -0.3f);
	glVertex2d(-0.26, 0);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(-0.13f, -0.3f);
	glVertex2f(-0.4f, -0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2f(0.0f, -0.5f);
	glVertex2d(-0.13f, -0.3f);
	glEnd(); 
}

/* ���Ʋ�ɫ�������� */
void DrawColoredSixRayStar() 
{
	glShadeModel(GL_SMOOTH);	/* ���ö������ɫģʽ */

	/* ����12�������������������, Ϊ��Ӧ�������ò�ͬ��ɫ��ʵ��Ҫ���Ч�� */
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(1, 0, 0);
	glVertex2d(0.0f, 0.5f);
	glColor3f(1, 0, 0);
	glVertex2d(0.13f, 0.3f);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(1, 0, 0);
	glVertex2d(0.13f, 0.3f);
	glColor3f(0.98, 0.04, 0.70);
	glVertex2f(0.4f, 0.3f);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0.98, 0.04, 0.70);
	glVertex2f(0.4f, 0.3f);
	glColor3f(0.98, 0.04, 0.70);
	glVertex2d(0.26, 0);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0, 0, 1);
	glVertex2d(0.4f, -0.3f);
	glColor3f(0.98, 0.04, 0.70);
	glVertex2d(0.26, 0);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0, 0, 1);
	glVertex2d(0.13f, -0.3f);
	glColor3f(0, 0, 1);
	glVertex2f(0.4f, -0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0, 1, 1);
	glVertex2f(0.0f, -0.5f);
	glColor3f(0, 0, 1);
	glVertex2d(0.13f, -0.3f);
	glEnd(); 

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(1, 0, 0);
	glVertex2d(0.0f, 0.5f);
	glColor3f(1, 1, 0);
	glVertex2d(-0.13f, 0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(1, 1, 0);
	glVertex2d(-0.13f, 0.3f);
	glColor3f(1, 1, 0);
	glVertex2f(-0.4f, 0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(1, 1, 0);
	glVertex2f(-0.4f, 0.3f);
	glColor3f(0, 1, 0);
	glVertex2d(-0.26, 0);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0, 1, 0);
	glVertex2d(-0.4f, -0.3f);
	glColor3f(0, 1, 0);
	glVertex2d(-0.26, 0);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0, 1, 1);
	glVertex2d(-0.13f, -0.3f);
	glColor3f(0, 1, 0);
	glVertex2f(-0.4f, -0.3f);
	glEnd(); 
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2d(0, 0);
	glColor3f(0, 1, 1);
	glVertex2f(0.0f, -0.5f);
	glColor3f(0, 1, 1);
	glVertex2d(-0.13f, -0.3f);
	glEnd(); 
}
