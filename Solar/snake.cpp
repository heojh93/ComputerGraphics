#include <stdio.h>
#include <GL/freeglut.h>

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
GLUquadric *quadric ;

void drawCylinder(float radius, float height)
{
	glBegin(GL_POLYGON);

		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(-height/2, -radius/2, 0);
		glVertex3f(-height/2, radius/2 , 0);
		glVertex3f(height/2 , radius/2 , 0);
		glVertex3f(height/2 , -radius/2, 0);
	glEnd();
}
void MyDisplay()
{
	glViewport(0, 0, 300, 300);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glLoadIdentity();
	double height=0.3;
	double radius=0.03;
	double alpha=-45;

	glPushMatrix();
	glRotatef(alpha, 0,0,1);
	glTranslatef(-0.5*height, 0,0);
	drawCylinder(radius, height);
	glTranslatef(-0.5*height, 0,0);

	for(int i=0; i<3; i++)
	{
		if(i%2==1)
			glRotatef(2*alpha, 0,0,1);
		else
			glRotatef(-2*alpha,0,0,1);
		glTranslatef(-0.5*height,0,0);
		drawCylinder(radius, height);
		glTranslatef(-0.5*height,0,0);
	}
	glPopMatrix();



	glFlush();
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
	if(Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		TopLeftX = X;
		TopLeftY = Y;
	}
}
void MyMouseMove(GLint X, GLint Y)
{
	BottomRightX = X;
	BottomRightY = Y;
	glutPostRedisplay();   // marks the current window as needing to be redisplayed.
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1., 1., 1., 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	quadric = gluNewQuadric();
	glutMainLoop();
	return 0;
}
