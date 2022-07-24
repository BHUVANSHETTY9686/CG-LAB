//Experiment :- 6 To draw a simple shaded scene consisting of a tea pot on a table. Define suitably the 
/*position and properties of the light source along with the properties of the surfaces of the 
solid object used in the scene. */
#include<stdio.h>
#include<GL/glut.h>


void tableLeg(double thick,double len)
{
	glPushMatrix();
	glScaled(thick,len,thick);
	glutSolidCube(1.0);
	glPopMatrix();
}


void table(double topWid,double topThick,double legThick,double legLen)
{
	glPushMatrix();
	glTranslated(0,legLen,0);
	glScaled(topWid,topThick,topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.28,0.15,0.28);
	tableLeg(legThick,legLen);

	glTranslated(0.0,0.0,-2*0.28);
	tableLeg(legThick,legLen);

	glTranslated(-2*0.28,0.0,0.0);
	tableLeg(legThick,legLen);

	glTranslated(0.0,0.0,2*0.28);
	tableLeg(legThick,legLen);
	glPopMatrix();
}


void displaySolid()
{
	GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat mat_diffuse[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat mat_specular[]={0.0f,1.0f,0.0f,1.0f};
	GLfloat mat_shininess[]={50.0f};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	
	GLfloat lightIntensity[]={0.7f,0.7f,0.7f,0.0f};
	GLfloat lightPosition[]={2.0f,6.0f,3.0f,0.0f};
	
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glTranslated(0.6,0.38,0.5);
	glRotated(30,0,1,0);
	glutSolidTeapot(0.08);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.4,0,0.4);
	table(0.6,0.02,0.02,0.3);
	glPopMatrix();
	glFlush();
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Teapot");
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0,0.0,0.0,0.0);
	glutMainLoop();
	return 0;
}
