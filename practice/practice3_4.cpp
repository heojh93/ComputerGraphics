#include <GL/freeglut.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static int width, height;
bool bPerspective = true;


void SetProjection()
{
	GLfloat fAspect = (GLfloat)width/(GLfloat)height;
	GLfloat nRange = height/4.0;
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (bPerspective)
		gluPerspective(60.0f, fAspect, 1.0, 400.0);
	else
	{
		if (width <= height) 
			glOrtho (-nRange, nRange, -nRange/fAspect, nRange/fAspect, -nRange*4.0f, nRange*4.0f);
		else 
			glOrtho (-nRange*fAspect, nRange*fAspect, -nRange, nRange, -nRange*4.0f, nRange*4.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	width = w;
	height = h;
	SetProjection();
}

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)			xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)		xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)		yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)		yRot += 5.0f;

	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);

	if (key == GLUT_KEY_F1)
	{
		bPerspective = !bPerspective;
		SetProjection();
	}
	glutPostRedisplay();
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -300.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCube(100.0);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Perspective Projection");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutMainLoop();

	return 0;
}
