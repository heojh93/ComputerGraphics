#include <GL/freeglut.h>

bool bDrag = false;
float g_fDistance = -300.0f;
float g_fSpinX    =  0.0f;
float g_fSpinY    =  0.0f;
int ptLastMousePositX, ptLastMousePositY;
int ptCurrentMousePositX, ptCurrentMousePositY;

void ChangeSize(GLsizei width, GLsizei height)
{
	GLfloat fAspect = (GLfloat)width/(GLfloat)height;
	GLfloat nRange = height/4.0;
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height) 
		glOrtho (-nRange, nRange, -nRange/fAspect, nRange/fAspect, -nRange*4.0f, nRange*4.0f);
	else 
		glOrtho (-nRange*fAspect, nRange*fAspect, -nRange, nRange, -nRange*4.0f, nRange*4.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
	if(Button == GLUT_LEFT_BUTTON )
	{
		if (State == GLUT_DOWN)
		{
			ptLastMousePositX = ptCurrentMousePositX = X;
			ptLastMousePositY = ptCurrentMousePositY = Y;
			bDrag = true;
		}
		else if (State == GLUT_UP)
			bDrag = false;
	}
}
void MyMouseMove(GLint X, GLint Y)
{
	ptCurrentMousePositX = X;
	ptCurrentMousePositY = Y;

	if( bDrag )
	{
		g_fSpinX -= (ptCurrentMousePositX - ptLastMousePositX);
		g_fSpinY -= (ptCurrentMousePositY - ptLastMousePositY);
	}

	ptLastMousePositX = ptCurrentMousePositX;
	ptLastMousePositY = ptCurrentMousePositY;
	glutPostRedisplay(); 
}


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, g_fDistance);
	glRotatef( -g_fSpinY, 1.0f, 0.0f, 0.0f );
	glRotatef( -g_fSpinX, 0.0f, 1.0f, 0.0f );
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireTeapot(100.0);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Rotate an object using mouse");
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutDisplayFunc(RenderScene);
	glutMainLoop();

	return 0;
}
