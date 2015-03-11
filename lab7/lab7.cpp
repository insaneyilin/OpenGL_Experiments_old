/************************************************************************/
/************************************************************************/
/*
/* Filename     :	all-bunny.cpp
/* Abstract     :	ʵ����_3090104732_������_����
/* Reference	:	����, ͯ����, <<�����ͼ��ѧ�γ����>>, �㽭��ѧ������
/* Version      :	1.0										
/* Author       :	������											
/* Accomplished date : May. 26th, 2012
/*							
/************************************************************************/
/************************************************************************/

#define GLUT_DISABLE_ATEXIT_HACK	//����glut.h�е�˵��������Ӵ���
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/************************************************************************/
/*							ȫ�ֱ�������                                */
/************************************************************************/
float fTranslate;
float fRotate = 156.5f;
float fScale     = 1.0f;	// set inital scale value to 1.0f

float whRatio;

bool bPersp = true;
bool bAnim = false;
bool bWire = false;

// ��ʾ�����Ƿ�ѡ��
bool bSelectBunny = false;
bool bSelectDesk = false;

int wHeight = 0;
int wWidth = 0;

// ��ʾ�б��ʶ
GLint dl = 0;

// ��ز���
GLfloat mat_desk1[] = {0.3, 0.3, 0.3, 0.0};    // ���Ӳ���
GLfloat mat_bunny1[] = {0.3, 0.3, 0.3, 0.0};  // Bunny����
GLfloat mat_desk2[] = {1.0, 0.0, 0.0, 0.0};    // ���Ӳ���
GLfloat mat_bunny2[] = {0.6, 0.5, 0.0, 0.0};  // Bunny����

// �۲�λ����۲�����
float center[] = {0, -0.8, -6};
float eye[] = {0, 1.2, 2};

// ����ģʽ��0��1��2�ֱ��Ӧnaive���������顢��ʾ�б����ַ�ʽ
int  drawMode = 0;


/************************************************************************/
/*								��������                                */
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

//  ������м�¼�ĺ���
void ProcessPicks(GLint nPicks, GLuint pickBuffer[]);

/************************************************************************/
/*							�ص���������                                */
/************************************************************************/
void updateView(int width, int height);
void reshape(int width, int height);
void idle();
void key(unsigned char k, int x, int y);
void getFPS();
void redraw();
// �������Ӧ����
void MouseClick(int button,int action,int xMouse,int yMouse);

/************************************************************************/
/*							������                                      */
/************************************************************************/
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
	glutMouseFunc(MouseClick);  // �������Ӧ����

	dl = Gen3DObjectList();  // ������ʾ�б�

	glutMainLoop();
	return 0;
}

/************************************************************************/
/*							��������                                    */
/************************************************************************/
#define BUFSIZE 512

//  ������м�¼�ĺ���
void ProcessPicks(GLint nPicks, GLuint pickBuffer[])
{
	if (nPicks <= 0)
	{
		return;
	}
	GLint i;
	GLuint name, *ptr, minZ, *ptrNames, numberOfNames;
    minZ = 0xffffffff;
	printf("ѡ�е���ĿΪ%d��\n",nPicks);
	ptr=pickBuffer;
	
	for(i = 0; i < nPicks; i++)
	{
		name = *ptr;    // ���м�¼��������
		ptr++;  // ��С��ȼ�¼
		if (*ptr < minZ)  // �ҵ���С��ȵ���������
		{
			numberOfNames = name;
			minZ = *ptr;
			ptrNames = ptr+2;  // ��ǰptrָ����С��ȼ�¼��ptr+1ָ�������ȼ�¼��ptr+2ָ����м�¼�еĵ�һ������
		}
		ptr += name + 2; // ptr �ƶ�����һ�����м�¼
	}
	if (*ptrNames == 1)
	{
		printf("��ѡ����Bunny\n");
		bSelectBunny = !bSelectBunny;
	}
	if(*ptrNames == 2)
	{
		printf("��ѡ����Desk\n");
		bSelectDesk = !bSelectDesk;
	}
	printf("\n\n");
}

// �������Ӧ����
void MouseClick(int button,int action,int xMouse,int yMouse)
{
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)  // ����������
	{
		GLuint selectBuf[BUFSIZE];
		GLint hits;
		GLint viewport[4];		
		glGetIntegerv (GL_VIEWPORT, viewport);
		glSelectBuffer (BUFSIZE, selectBuf);  //����ѡ�񻺳���
		
		// ����ѡ��ģʽ
		glRenderMode(GL_SELECT);				// Enter the SELECT render mode
		glInitNames();   //��ʼ�����ֶ�ջ
		glPushName(-1);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
        glLoadIdentity();
		
		//����һ��2��2��ѡ������
		gluPickMatrix((GLdouble) xMouse, (GLdouble) (viewport[3] - yMouse), 2.0, 2.0, viewport);
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);
		
		// ��ͼ
		Draw_Triangle(GL_SELECT);
		
		glPopMatrix ();
		glFlush ();
		
		// �ָ�ͶӰ�任
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0,0,wWidth,wHeight);
		gluPerspective(45.0f, whRatio,0.1f,100.0f);
		
		// ��û��м�¼������
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
	// ���������ѡ��״̬���ò����Ըı���ɫ
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
	if(mode == GL_SELECT) glLoadName(1); //ѹ�����ֶ�ջ
	
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
	
	if(mode == GL_SELECT) glLoadName(2); //ѹ�����ֶ�ջ
	Draw_Desk();
}

void Draw_Desk()
{
	// ���������ѡ��״̬���ò����Ըı���ɫ
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
	glMatrixMode(GL_PROJECTION);// ѡ��ͶӰ����
	glPushMatrix();// ����ԭ����
	glLoadIdentity();// װ�뵥λ����
	glOrtho(0,480,0,480,-1,1);// λ����ͶӰ
	glMatrixMode(GL_MODELVIEW);// ѡ��Modelview����
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_desk1);
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
	glClearColor(0.0,0.0,0.0,0.0);

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

	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);	// ���÷����һ��
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
