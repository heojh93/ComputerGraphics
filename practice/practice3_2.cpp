#include <GL/freeglut.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

static int Day = 0, Time = 0, DayMars = 0, TimeMars = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT
		|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.0);
	/***지구***/
	glPushMatrix();
	//지구의공전
	glRotatef((float)Day, 0.0, 1.0, 0.0);
	glTranslatef(0.7, 0.0, 0.0);
	//지구의자전
	glRotatef((float)Time, 0.0, 1.0, 0.0); 
	glColor3f(0.0, 0.0, 1.0);
	glutWireSphere(0.1, 30, 8); 
	/***달***/
	glPushMatrix();
	//달의공전	
	glRotatef((float)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidSphere(0.04, 30, 8);
	glPopMatrix();
	glPopMatrix();
    /***화성***/
    //화성공전
    glPushMatrix();
    glRotatef((float)DayMars, 0.0, 1.0, 0.0);
    glTranslatef(1.4, 0.0, 0.0);
    //화성자전
    glRotatef((float)TimeMars, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(0.1, 30, 8);
    glPopMatrix();
	/***태양***/
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(0.2, 30, 16); 
	glutSwapBuffers();
}
void MyTimer(int value)
{
	Day = (Day + 10) % 360;
	Time = (Time + 15) % 360;
    DayMars = (DayMars + 5) % 360;
    TimeMars = (TimeMars + 30) % 360;
	glutTimerFunc(100, MyTimer, 1);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Solar system");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 6.0);	glutDisplayFunc(MyDisplay);
	glutTimerFunc(100, MyTimer, 1);
	glutMainLoop();
	return 0;
}
