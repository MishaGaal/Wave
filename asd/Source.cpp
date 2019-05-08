#include "screencasts.h"
/*  Globals */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
double dim = 8; /* dimension of orthogonal box */
char *windowName = "AXES+SHAPE";
int windowWidth = 800;
int windowHeight = 600;

/*  Various global state */
/*  Toggles */
int toggleAxes = 0;   /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */
int toggleMode = 0; /* projection mode */
int th = 320;   /* azimuth of view angle */
int ph = 20;   /* elevation of view angle */
int fov = 55; /* field of view for perspective */
int asp = 1;  
float X = 0.0;        //начальные значения
float Y = 0.0;
float Z = 0.0;

int objId = 2;


 float f(float x, float y)
 {
	 return sin(0.314*y) + cos (24.62/0.31*x) ;
 }

 float m(float o, float p)
 {
	 return sin(0.314*p) - cos(24.62 / 0.31*o);
 }

 float n(float h)
 {
	 return sqrt(5/h);
 }

 float x(float m)
 {
	 return sqrt(3/m );
 }
  void project()
 {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (toggleMode) {
		/* perspective */
		gluPerspective(fov, asp, dim / 4, 4 * dim);
	}
	else {
		/* orthogonal projection*/
		glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

					/*
					* drawAxes()
					* ------
					* Draw the axes
					*/
void drawAxes()
{
	if (!toggleAxes) {
		/*  Length of axes */
		double len = 6.0;
		glColor3f(0.0, 0.0, 1.0);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex3d(0, 0, 0);
		glVertex3d(len, 0, 0);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3d(0, 0, 0);
		glVertex3d(0, len, 0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, len);
		glColor3f(0.0, 0.0, 0.0);
		glEnd();
		/*  Label axes */
		glRasterPos3d(len+2, 0, 0);
		print("X");
		glRasterPos3d(0, len+2, 0);
		print("Z");
		glRasterPos3d(0, 0, len+2);
		print("Y");
		/* Axes arrows */
		glColor3f(0, 1.0, 0);
		glPushMatrix();
		glTranslated(0, 0, len);
		glutSolidCone(0.2, 1.5, 46, 46);
		glutSolidCone(0.2, -1, 16, 16);
		glPopMatrix();
		glColor3f(1.0, 0.0, 0);
		glPushMatrix();
		glTranslated(0, len, 0);
		glRotated(-90, 1, 0, 0);
		glutSolidCone(0.2, 1.5, 46, 46);
		glutSolidCone(0.2, -1, 16, 16);
		glPopMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		glTranslated(len, 0, 0);
		glRotated(90, 0, 1, 0);
		glutSolidCone(0.2, 1.5, 46, 46);
		glutSolidCone(0.2, -1, 16, 16);
		glPopMatrix();
		//draw rectangle
		glBegin(GL_LINES);

		glColor3f(1.0, 0.0, 1.0);
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glTranslatef(X, 0.0, 0.0);
		glTranslatef(0.0, Y, 0.0);
		glTranslatef(0.0, 0.0, Z);

		glVertex3f(-4.8, -1.2, 0.0);   
		glVertex3f(-4.8, 1.2, 0.0);
		glVertex3f(-4.8, 1.2, 0.0);
		glVertex3f(4.8, 1.2, 0.0);
		glVertex3f(4.8, 1.2, 0.0);
		glVertex3f(4.8, -1.2, 0.0);
		glVertex3f(4.8, -1.2, 0.0);
		glVertex3f(-4.8, -1.2, 0.0);

		glVertex3f(-4.8, -1.2, 4.8);
		glVertex3f(-4.8, 1.2, 4.8);
		glVertex3f(-4.8, 1.2, 4.8);
		glVertex3f(4.8, 1.2, 4.8);
		glVertex3f(4.8, 1.2, 4.8);
		glVertex3f(4.8, -1.2, 4.8);
		glVertex3f(4.8, -1.2, 4.8);
		glVertex3f(-4.8, -1.2, 4.8);

		glVertex3f(-4.8, -1.2, -4.8);
		glVertex3f(-4.8, 1.2, -4.8);
		glVertex3f(-4.8, 1.2, -4.8);
		glVertex3f(4.8, 1.2, -4.8);
		glVertex3f(4.8, 1.2, -4.8);
		glVertex3f(4.8, -1.2, -4.8);
		glVertex3f(4.8, -1.2, -4.8);
		glVertex3f(-4.8, -1.2, -4.8);

		glVertex3f(-4.8, 1.2, 0.0);
		glVertex3f(-4.8, 1.2, 4.8);
		glVertex3f(4.8, 1.2, 0.0);
		glVertex3f(4.8, 1.2, 4.8);

		glVertex3f(-4.8, 1.2, 0.0);
		glVertex3f(-4.8, 1.2, -4.8);
		glVertex3f(4.8, 1.2, 0.0);
		glVertex3f(4.8, 1.2, -4.8);

		glVertex3f(-4.8, -1.2, 0.0);
		glVertex3f(-4.8, -1.2, 4.8);
		glVertex3f(4.8, -1.2, -0.0);
		glVertex3f(4.8, -1.2, 4.8);

		glVertex3f(-4.8, -1.2, 0.0);
		glVertex3f(-4.8, -1.2, -4.8);
		glVertex3f(4.8, -1.2, -0.0);
		glVertex3f(4.8, -1.2, -4.8);



		glEnd();
	}
}

/*
*  drawValues()
*  ------
*  Draw the values in the lower left corner
*/
void drawValues()
{
	if (toggleValues) {
		glColor3f(0.0, 0.0, 0.0);
		printAt(1, 7, "View Angle (th, ph) =(%d, %d)", th, ph);
		printAt(1, 6, "Function is  =(W(x,z))");
		printAt(1, 5, "Projection is =(%s)", toggleMode?"prespective":"ortogonal");
	}
}

void drawShape()
{
    glColor3f(0.0, 0.0, 0.0);
	   if (objId == 1)
	    { 
		   glLineWidth(1);
		   glColor3f(1.0, 1.0, 0.0);
		   glRotatef(10.0, 1.0, 0.0, 0.0);
		   for (float o = -4.8; o < 4.8; o += 0.2)
		   {
			   glBegin(GL_LINE_STRIP);
			   for (float p = -4.8; p < 4.8; p += 0.2)
			   {
				   glVertex3f(o, m(o, p), p);
			   }
			   glEnd();
		   }
		   for (float p = -4.8; p < 4.8; p += 0.2)
		   {
			   glBegin(GL_LINE_STRIP);
			   for (float o = -4.8; o < 4.8; o += 0.2)
			   {
				   glVertex3f(o, m(o, p), p);
			   }
			   glEnd();

			   glColor3f(0.0, 0.0, 0.0);
			   for (float x = -4.8; x < 4.8; x += 0.2)
			   {
				   glBegin(GL_LINE_STRIP);
				   for (float y = -4.8; y < 4.8; y += 0.2)
				   {
					   glVertex3f(x, f(x, y), y);
				   }
				   glEnd();
			   }
			   for (float y = -4.8; y < 4.8; y += 0.2)
			   {
				   glBegin(GL_LINE_STRIP);
				   for (float x = -4.8; x < 4.8; x += 0.2)
				   {
					   glVertex3f(x, f(x, y), y);
				   }
				   glEnd();
			   }
		   }
	}

	   else if (objId == 2)
	   {
		   glLineWidth(1);
		   glColor3f(0.0, 0.0, 0.0);
		   glRotatef(10.0, 1.0, 0.0, 0.0);
		   for (float x = -4.8; x < 4.8; x += 0.2)
		   {
			   glBegin(GL_LINE_STRIP);
			   for (float y = -4.8; y < 4.8; y += 0.2)
			   {
				   glVertex3f(x, f(x, y), y);
			   }
			   glEnd();
		   }
		   for (float y = -4.8; y < 4.8; y += 0.2)
		   {
			   glBegin(GL_LINE_STRIP);
			   for (float x = -4.8; x < 4.8; x += 0.2)
			   {
				   glVertex3f(x, f(x, y), y);
			   }
			   glEnd();
		   }
	   }
	   else if (objId == 3)
	   {
		   double len = 6.0;
		   glColor3f(0.0, 0.0, 1.0);
		   glLineWidth(5);
		   glRotatef(-85.0, 1.0, 0.0, 0.0);
		   glRotatef( 25.0, 0.0, 0.0, 1.0);
		   glTranslatef(-5.0,-2.0, 0.0);
		   glBegin(GL_LINES);
		   glVertex3d(0, 0, 0);
		   glVertex3d(len, 0, 0);
	
		   glColor3f(0.0, 1.0, 0.0);
		   glVertex3d(0.0, 0.0, 0.0);
		   glVertex3d(0, 0, len);
		   glColor3f(0.0, 0.0, 0.0);
		   glEnd();

		   glRasterPos3d(len + 2, 0, 0);
		   print("k");
		   glRasterPos3d(0, 0, len + 2);
		   print("W");
		   glRasterPos3d(1, 7, 4);
		   print("Dispersion");
		   glRasterPos3d(1, 2, 2);
		   print("m=1");
		   glRasterPos3d(1, -2, 2);
		   print("n=0");

		   glColor3f(0, 1.0, 0);
		   glPushMatrix();
		   glTranslated(0, 0, len);
		   glutSolidCone(0.2, 1.5, 46, 46);
		   glutSolidCone(0.2, -1, 16, 16);
		   glPopMatrix();

		   glColor3f(0.0, 0.0, 1.0);
		   glPushMatrix();
		   glTranslated(len, 0, 0);
		   glRotated(90, 0, 1, 0);
		   glutSolidCone(0.2, 1.5, 46, 46);
		   glutSolidCone(0.2, -1, 16, 16);
		   glPopMatrix(); 

		   
		   
			   glBegin(GL_LINE_STRIP);
			   for (float h = 0; h < 7.8; h += 0.2)
			   {
				   glColor3f(1.0, 0.0, 0.0);
				   glVertex3f(h, 0, n(h));

			   }
			   glEnd();
			   glBegin(GL_LINE_STRIP);
			   for (float m = 0; m < 7.8; m += 0.2)
			   {
				   glColor3f(1.0, 0.0, 1.0);
				   glVertex3f(m, 0, x(m));
			   }
			   glEnd();
			   
	   }

	glPopMatrix();
	
}


void display()
{
	/*  Clear the image */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*  Reset previous transforms */
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glClearColor(1, 1, 1, 1);

	if (toggleMode) {
		double Ex = -2 * dim*Sin(th)*Cos(ph);
		double Ey = +2 * dim        *Sin(ph);
		double Ez = +2 * dim*Cos(th)*Cos(ph);
		/* camera/eye position, aim of camera lens, up-vector */
		gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
	}
	/*  Orthogonal - set world orientation */
	else {
		glRotatef(ph, 1, 0, 0);
		glRotatef(th, 0, 1, 0);
	}
	/*  Draw  */
	drawAxes();
	drawValues();
	drawShape();

	

	/*  Flush and swap */
	glFlush();
	glutSwapBuffers();
}

/*
*  reshape()
*  ------
*  GLUT calls this routine when the window is resized
*/
void reshape(int width, int height)
{
	double w2h = (height>0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	project();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* orthogonal projection */
	glOrtho(-dim*w2h, +dim*w2h, -dim, +dim, -dim, +dim);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
*  windowKey()
*  ------
*  GLUT calls this routine when a non-special key is pressed
*/
void windowKey(unsigned char key, int x, int y)
{
	/*  Exit on ESC */
	if (key == 27) exit(0);
	else if (key == 'a' || key == 'A') toggleAxes = 1 - toggleAxes;
	else if (key == 'v' || key == 'V') toggleValues = 1 - toggleValues;
	else if (key == 'm' || key == 'M') toggleMode = 1 - toggleMode;
	/*  Change field of view angle */
	else if (key == '-' && key>1) fov--;
	else if (key == '+' && key<179) fov++;
	/*  Change dimensions */
	else if (key == 's') dim += 0.1;
	else if (key == 'd' && dim>1) dim -= 0.1;
	else if (key == 32) {
		objId = 1;
	}
	else if (key == 'z')
		objId = 2;
	else if (key == 'c')
	{
		objId = 3;
		toggleAxes = 1;
		toggleValues = 0;
	}
	project();


	glutPostRedisplay();
}

/*
*  windowSpecial()
*  ------
*  GLUT calls this routine when an arrow key is pressed
*/
void windowSpecial(int key, int x, int y)
{
	/*  Right arrow key - increase azimuth by 5 degrees */
	if (key == GLUT_KEY_RIGHT) th += 5;
	/*  Left arrow key - decrease azimuth by 5 degrees */
	else if (key == GLUT_KEY_LEFT) th -= 5;
	/*  Up arrow key - increase elevation by 5 degrees */
	else if (key == GLUT_KEY_UP) ph -= 5;
	/*  Down arrow key - decrease elevation by 5 degrees */
	else if (key == GLUT_KEY_DOWN) ph += 5;

	/*  Keep angles to +/-360 degrees */
	th %= 360;
	ph %= 360;
	project();
	glutPostRedisplay();
}

/*
*  windowMenu
*  ------
*  Window menu is the same as the keyboard clicks
*/
void windowMenu(int value)
{
	windowKey((unsigned char)value, 0, 0);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial); 

	printf("         !!!SOME DEFINITIONS!!!          \n");
	printf("th - azimuth of view angle \n");
	printf("ph - elevation of view angle \n");
	printf("Press a or A to on/off axes \n");
	printf("Press v or V to on/off values \n");
	printf("Press d to zoomin or s to zoomout \n");
	printf("Press c to add mode \n");
	printf("Use keypad arrow keys to rotated figure \n");

	glutCreateMenu(windowMenu);
	glutAddMenuEntry("Toggle Axes [a]", 'a');
	glutAddMenuEntry("Toggle Mode [m]", 'm');
	glutAddMenuEntry("Toggle Values [v]", 'v');
	glutAddMenuEntry("by Misha Galitsky", 's');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}