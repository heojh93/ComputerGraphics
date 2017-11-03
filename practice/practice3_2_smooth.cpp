#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>

static int Day = 0, Time = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

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
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 30, 8); 
	/***달***/
	glPushMatrix();
	//달의공전	
	glRotatef((float)Time, 0.0, 1.0, 0.0);
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutSolidSphere(0.04, 30, 8);
	glPopMatrix();
	glPopMatrix();
	/***태양***/
	glColor3f(1.0, 0.3, 0.4);
	glutSolidSphere(0.2, 30, 16); 
	glutSwapBuffers();
}
void MyTimer(int value)
{
	Day = (Day + 5) % 360;
	Time = (Time + 10) % 360;
	glutTimerFunc(100, MyTimer, 1);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH| GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Solar system");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 30.0);	glutDisplayFunc(MyDisplay);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// set properties of the surface material
	GLfloat mat_ambient [] = {0.7f, 0.7f, 0.7f, 1.0f};   //gray
	//GLfloat mat_ambient [] = {0.7f, 0.0f, 0.0f, 1.0f};   //red
	GLfloat mat_diffuse [] = {0.6f, 0.6f, 0.6f, 1.0f};
	//GLfloat mat_diffuse [] = {0.6f, 0.0f, 0.0f, 1.0f};//red
	GLfloat mat_specular [] = {1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat mat_specular [] = {1.0f, 0.0f, 0.0f, 1.0f};//red
	GLfloat mat_shininess [] = {50.0f};
	//
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// set the light source properties
	GLfloat lightIntensity [] = {0.7f, 0.7f, 0.7f, 1.0f};
	//GLfloat lightIntensity [] = {0.9f, 0.0f, 0.0f, 1.0f};
	GLfloat light_position [] = {2.0f, 6.0f, 3.0f, 0.0f};
	//GLfloat light_position [] = {2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.1, 0.1, 0.1, 0.0); // light grey
	glDisable(GL_CULL_FACE);
	//gluPerspective(45,4/3,0.1,2); glutDisplayFunc(MyDisplay);
	glutTimerFunc(100, MyTimer, 1);
	glutMainLoop();
	return 0;
}
