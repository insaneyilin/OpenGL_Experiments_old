/************************************************************************/
/************************************************************************/
/*
/* Filename     :	SixRayStar.cpp
/* Abstract     :	A simple example of drawing a six-ray star with OpenGL,
/*					Press left button of the mouse will change the color.
/* Reference	:	唐敏, 童若峰, <<计算机图形学课程设计>>, 浙江大学出版社
/* Version      :	1.0										
/* Author       :	Gui Yilin											
/* Accomplished date : March. 8th, 2012
/*							
/************************************************************************/
/************************************************************************/
#define GLUT_DISABLE_ATEXIT_HACK	//按照glut.h中的说明解决连接错误
#include <gl/glut.h>

static int iColorflag = 1; /* 用于判断是否为六角星上色 */

/************************************************************************/
/*								函数声明                                */
/************************************************************************/
/* 绘制无颜色的六角星 */
void DrawSixRayStar();

/* 绘制彩色的六角星 */
void DrawColoredSixRayStar();

/* 绘制事件回调函数 */
void display();

/* 添加鼠标响应函数, 点击左键切换显示图形 */
void processMouse(int button,int state,int x,int y);


/************************************************************************/
/*								主函数									*/
/************************************************************************/
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);	/* 初始化glut */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); /* RGBA颜色模式; 双缓冲 */
	
	int windowHandle = glutCreateWindow("Colored Six-Ray Star"); /* 创建窗口 */

	glutDisplayFunc(display); /* 设置回调函数 */
	glutMouseFunc(processMouse);

	glutMainLoop();
	return 0;
}

/************************************************************************/
/*								函数定义                                */
/************************************************************************/
/* 绘制事件回调函数 */
void display()
{
	/* 初始化背景色 */
	if (iColorflag == 0) 
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	/* 清除色（背景）为白色 */
		glColor3f(0.0f, 0.0f, 0.0f);	/* 绘图色 */
	}
	else 
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	/* 清除色（背景）为黑色 */
		glColor3f(0.0f, 0.0f, 0.0f);	/* 绘图色 */
	}
	
	glClear(GL_COLOR_BUFFER_BIT); /* 清空颜色缓存 */
	
	if (iColorflag == 0)
	{
		DrawColoredSixRayStar();
	}
	else
	{
		DrawSixRayStar();
	}
	
	glFlush();		/* 刷新命令队列 */
	glutSwapBuffers();  /* 交换缓冲区数据 */
}

/* 添加鼠标响应函数, 点击左键切换显示图形 */
void processMouse(int button,int state,int x,int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		iColorflag = !iColorflag;
	
	//刷新窗口
	glutPostRedisplay(); 
}

/* 绘制未上色的六角星 */
void DrawSixRayStar()
{
	glShadeModel(GL_FLAT);	/* 设置多边形着色模式 */

	glColor3f(1, 1, 1);	/* 使用白色绘图色 */

	/* 绘制12个三角形来组成六角星 */
	/* 第一个三角形 */
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

/* 绘制彩色的六角星 */
void DrawColoredSixRayStar() 
{
	glShadeModel(GL_SMOOTH);	/* 设置多边形着色模式 */

	/* 绘制12个三角形来组成六角星, 为相应顶点设置不同颜色以实现要求的效果 */
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
