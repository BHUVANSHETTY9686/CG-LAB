#include <stdio.h>
#include <GL/glut.h>
#define outcode int
#define true  1
#define false 0
double xmin=50,ymin=50, xmax=100,ymax=100; 
double xvmin=200,yvmin=200,xvmax=300,yvmax=300; 
const int TOP = 8;
const int LEFT = 2;
const int BOTTOM = 4;
const int RIGHT = 1;

outcode ComputeOutCode (double x, double y)
{
	outcode code = 0;
	if (y > ymax)              
		code |= TOP;
	else if (y < ymin)         
		code |= BOTTOM;
	if (x > xmax)              
		code |= RIGHT;
	else if (x < xmin)         
		code |= LEFT;
	return code;
}

void draw(double x0, double y0,double x1, double y1)
{
	//this is for line passing
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2d (x0, y0);
		glVertex2d (x1, y1);
	glEnd();
	
	//this is for that window...
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
  		glVertex2f(xmin, ymin);
  		glVertex2f(xmax, ymin);
 		glVertex2f(xmax, ymax);
 		glVertex2f(xmin, ymax);
	glEnd();
}




void CohenSutherlandLineClipAndDraw (double x0, double y0,double x1, double y1)
{
	outcode outcode0, outcode1, outcodeOut;
	
            int accept = false, done = false;
	outcode0 = ComputeOutCode (x0, y0);
	outcode1 = ComputeOutCode (x1, y1);

	do{
	 
     if (outcode0==0 && outcode1==0)      

		{
			accept = true;
			done = true;
		}
		 
    else if ((outcode0 & outcode1)!=0)
			done = true;
		else
		{	
			double x, y;
			outcodeOut = outcode0? outcode0: outcode1;			
 
              if (outcodeOut & TOP)          
			{
				x = x0 + (x1 - x0) * (ymax - y0)/(y1 - y0);
				y = ymax;
			}
			else if (outcodeOut & BOTTOM) 
			{
				x = x0 + (x1 - x0) * (ymin - y0)/(y1 - y0);
				y = ymin;
			}
			else if (outcodeOut & RIGHT)
			{
				y = y0 + (y1 - y0) * (xmax - x0)/(x1 - x0);
				x = xmax;
			}
			else                           
			{
				y = y0 + (y1 - y0) * (xmin - x0)/(x1 - x0);
				x = xmin;
			}			
			if (outcodeOut == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode (x0, y0);
			}
			else 
			{
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode (x1, y1);
			}
                         }
}while (!done);

if (accept)
{                
		
		glViewport(xvmin,yvmin,xvmax,yvmax);
	
		glPushMatrix();
		glScalef(3,3,0);
		draw(x0,y0,x1,y1);
		glPopMatrix();
}
}

void display()
{
	double x0=120,y0=10,x1=40,y1=130;
	glClear(GL_COLOR_BUFFER_BIT);	
	
        draw(x0,y0,x1,y1);
	CohenSutherlandLineClipAndDraw(x0,y0,x1,y1);
	
	glFlush();
}

void myinit()
{	
            glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}





int  main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("LAB5_4MT19CS038");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
} 
