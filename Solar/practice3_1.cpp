#include <stdio.h>
#include <GL/freeglut.h>

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay()
{
	glViewport(0, 0, 300, 300);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glLoadIdentity();
	glBegin(GL_POLYGON);

		glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
		glVertex3f(TopLeftX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
		glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
		glVertex3f(BottomRightX / 300.0, (300 - TopLeftY) / 300.0, 0.0);

	glEnd();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.5,-0.5,0.0);
	glutSolidCube(0.3);
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
	glutMainLoop();
	return 0;
}
