/************************************************************************/
/************************************************************************/
/*
/* Filename     :	main.cpp
/* Abstract     :	实验三_3090104732_桂义林_代码
/* Reference	:	唐敏, 童若峰, <<计算机图形学课程设计>>, 浙江大学出版社
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : March. 8th, 2012
/*							
/************************************************************************/
/************************************************************************/
#include <stdlib.h>
#include <gl/glut.h>


float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

// 对茶壶进行移动的参数
bool bTeaPotAnim = false;
float fX = 0.0, fZ = 0.0, fAngle = 0.0;

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	glPushMatrix();
	glTranslatef(0, 0, 4+1);
	glRotatef(90, 1, 0, 0);		// notice the rotation here, you may have a TRY removing this line to see what it looks like.

	// todo; hint: when operate the teapot, you may need to change some parameters

	glRotatef(fAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(fX, 0.0f, fZ);
	if (!bWire)
	{
		glutSolidTeapot(1);
	}
	else
	{
		//线宽等属性的设置必须在glBegin()...glEnd()外
		GLfloat lineWidth = 0.0f;
		glGetFloatv(GL_LINE_WIDTH, &lineWidth);
		glLineWidth(3.0f);

		glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);	// 设置材质
		glEnable(GL_COLOR_MATERIAL);

		glColor3f(1.0f, 0.0f, 0.0f);

		glBegin(GL_LINES);
			glNormal3f(0.0f, 3.0f, 0.0f);	// 未指定法向前颜色总是不正常
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 3.0f, 0.0f);
		glEnd();
		
		glColor3f(0.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
			glNormal3f(3.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(3.0f, 0.0f, 0.0f);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
			glNormal3f(0.0f, 0.0f, 3.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 3.0f);	
		glEnd();

		glLineWidth(lineWidth);

		glColor3f(1.0f, 1.0f, 1.0f);
		glutWireTeapot(1);
		glDisable(GL_COLOR_MATERIAL);
	}
	glPopMatrix();

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

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;
	
	if (bPersp)
	{
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
	    //glFrustum(-3, 3, -3, 3, 3,100);
	}
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

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};
//todo; hint: you may need another ARRAY when you operate the teapot

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}

	case 'a': 
		{//todo, hint: eye[] and center[] are the keys to solve the problems
			eye[0] -= 0.2f;
			center[0] -= 0.2f;
			break;
		}
	case 'd': 
		{//todo
			eye[0] += 0.2f;
			center[0] += 0.2f;
			break;
		}
	case 'w': 
		{//todo
			eye[1] -= 0.2f;
			center[1] -= 0.2f;
			break;
		}
	case 's': 
		{//todo
			eye[1] += 0.2f;
			center[1] += 0.2f;
			break;
		}
	case 'z': 
		{//todo
			eye[2] -= 0.2f;
			center[2] -= 0.2f;
			break;
		}
	case 'c': 
		{//todo
			eye[2] += 0.2f;
			center[2] += 0.2f;
			break;
		}

  //茶壶相关操作
	case 'l': 
		{//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
			if (fX >= 2.5) fX = 2.5;
			else fX += 0.25;
			break;
		}
	case 'j': 
		{//todo
			if (fX <= -2.5) fX = -2.5;
			else fX -= 0.25;
			break;
		}
	case 'i': 
		{//todo
			if (fZ >= 2.0) fZ = 2.0;
			else fZ += 0.2;
			break;
		}
	case 'k': 
		{//todo
			if (fZ <= -2.0) fZ = -2.0;
			else fZ -= 0.2;
			break;
		}
	case 'e': 
		{//todo
			bTeaPotAnim = !bTeaPotAnim;
			break;
		}
	}
}


void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = {5,5,5,1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate    += 0.5f;

	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	if (bTeaPotAnim) fAngle += 0.5f;

	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("实验三_3090104732_桂义林");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


