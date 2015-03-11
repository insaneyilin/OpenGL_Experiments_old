/************************************************************************/
/************************************************************************/
/*
/* Filename     :	lab5.cpp
/* Abstract     :	ʵ����_3090104732_������_����
/* Reference	:	����, ͯ����, <<�����ͼ��ѧ�γ����>>, �㽭��ѧ������
/* Version      :	1.0										
/* Author       :	������											
/* Accomplished date : May. 24th, 2012
/*							
/************************************************************************/
/************************************************************************/
#define GLUT_DISABLE_ATEXIT_HACK	//����glut.h�е�˵��������Ӵ���
#include <gl/glut.h>
#include <stdlib.h>

float fTranslate;
float fRotate;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;
bool bSpec = false;    // �Ƿ����ø߹�
bool bLight0 = true;   // �Ƿ�����Դ0
bool bSpot = false;    // �Ƿ����۹��Դ


int wHeight = 0;
int wWidth = 0;

// ��ز���
GLfloat mat_desktop[] = {1.0, 0.0, 0.0, 0.0};    // �������
GLfloat mat_leg1[] = {0.0, 1.0, 0.0, 0.0};    // ����1����
GLfloat mat_leg2[] = {1.0, 1.0, 0.0, 0.0};    // ����2����
GLfloat mat_leg3[] = {0.0, 1.0, 1.0, 0.0};    // ����3����
GLfloat mat_leg4[] = {0.0, 0.0, 1.0, 0.0};    // ����4����
GLfloat mat_Teapot[] = {0.6, 0.5, 0.0, 0.0};  // �������

GLfloat mat_lightsrc[] = {1.0, 1.0, 1.0, 0.0};  // ��Դ����
GLfloat mat_spectular[] = {1.0, 1.0, 1.0, 1.0};  // �߹����

// ��Դ����
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 }; // �׹�
GLfloat light_pos[] = {5,5,5,1};    // ��Դλ��

// �۹��Դ����
float direction[] = {0, -1, 0};    // ���䷽��
float spotCutOff = 4.0;    // �ü��Ƕ�

void updateSpotProperties();

// ��ʼ���۹��Դ
void initSpot()
{
	// ���й�Դ������
	float noAmbient[] = {1.0, 1.0, 1.0, 1.0};  // ������
	float diffuse[] = {0.0, 0.0, 1.0, 1.0};    // �����
	float position[] = {0.0, 4.0, 0.0, 1.0};   // λ��
	
	// ���ù�Դ����
	glLightfv(GL_LIGHT1, GL_AMBIENT, noAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	
	// Ͳ������
	// ����Ͳ�Ʒ���ͼн�
	updateSpotProperties();
	
	// ������߻�۳̶�
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 15.0);
	
	// ����˥��������ʹ����ȱʡֵ���������˥����
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
}

void updateSpotProperties()
{
	// Ͳ�Ʒ���
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	// Ͳ�Ƽн�
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutOff);
}

void Draw_Leg();

// ������Դ
void Draw_Light()
{
	glPushMatrix();
	glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
	glColor3f(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_lightsrc);
	//glutSolidCube(1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

void Draw_Triangle() // This function draws a triangle with RGB colors
{
	glPushMatrix();
	glTranslatef(0, 0, 4+1);
	glRotatef(90, 1, 0, 0);
	// ���ò���
	GLfloat mat_old_spectular[4];
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, mat_old_spectular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_Teapot);
	if (bSpec)
	{
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spectular);	 // ���ø߹�Ч��
		glMaterialf(GL_FRONT, GL_SHININESS, 65.0);	 // ���þ���ָ��
	}
	if (!bWire)
	{
		glutSolidTeapot(1);	// �����
	}
	else
	{
		glutWireTeapot(1);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 3.0f);
		glEnd();
	}
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_old_spectular);
	// �������
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desktop);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	// ����1����
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_leg1);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	// ����2����
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_leg2);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	// ����3����
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_leg3);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	// ����4����
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_leg4);
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

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }
		
	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}
		
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
	case '0':
		{
			bLight0 = !bLight0;
			break;
		}
		// �ı��Դλ��
	case 'i':
		light_pos[2] += 0.5;
		break;
	case 'k':
		light_pos[2] -= 0.5;
		break;
	case 'j':
		light_pos[0] -= 0.5;
		break;
	case 'l':
		light_pos[0] += 0.5;
		break;
		//	�ı��Դ��ɫ
	case 'r':
		white[0] -= 0.02;
		if (white[0] <= 0.0) white[0] = 1.0;
		break;
	case 'g':
		white[1] -= 0.02;
		if (white[1] <= 0.0) white[1] = 1.0;
		break;
	case 'b':
		white[2] -= 0.02;
		if (white[2] <= 0.0) white[2] = 1.0;
		break;
		// �߹�Ч��
	case 'h':
		bSpec = !bSpec;
		break;
		// �۹��Դ
	case 't':
		bSpot = !bSpot;
		break;
		// �۹��Դ����Ƕ�
	case 'x':
		spotCutOff += 2;
		if (spotCutOff >= 60) spotCutOff = 0.0;
		break;
		// �۹��Դ����Ƕ�
	case 'm':
		direction[0] += 0.1;
		if (direction[0] >= 1.0) direction[0] = 0;
		break;
	case 'n':
		direction[2] += 0.1;
		if (direction[2] >= 1.0) direction[2] = 0;
		break;
	default:
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
			0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������
	
	if (bWire) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_LIGHTING);  // ��������
	
	glEnable(GL_NORMALIZE);	// ���÷����һ��
	glEnable(GL_DEPTH_TEST); // ������Ȳ���	

	if (bLight0)
	{
		// ��Դ0����
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, white);
		glEnable(GL_LIGHT0);  // ������Դ0
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	
	// Ͳ�ƹ�Դ
	if (bSpot)
	{
		initSpot();
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
	
	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Triangle();						// Draw triangle
	
	if (bAnim) fRotate    += 0.5f;
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("ʵ����_3090104732_������");
	
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	
	glutMainLoop();
	return 0;
}
