#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

struct Point   // This structure is used for a storing different points of the polygon
{
	GLint x;   // x coordinate
	GLint y;   // y coordinate
}p1,p2,point_,point__;

struct Color   // this structure stores the color 
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void init() // Initializes the window.
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 650, 0, 450);
}

Color getPixelColor(GLint x, GLint y) // this returns the color of the given point.
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color)  // this functions sets the new color to the point.
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

int isNotEqual(Color c1,Color c2) // this function checks if two colours are equal or not.
{
        if(c1.r!=c2.r|| c1.g!=c2.g||c1.b!=c2.b)
           return 1;
        else
           return 0;
}

int isBoundary(Color currentColor) // this function checks if boundary is reached or not.
{
        if(currentColor.g==1.0 && currentColor.b==0.0 && currentColor.r==0.0)
           return 1;
        else
           return 0;
}

void BoundaryFill(int x, int y, Color fillColor, Color boundaryColor)    // Boundary Fill Algorithm. This will recursively fill color in the polygon.
{
        Color currentColor = getPixelColor(x, y);
        Color c1=getPixelColor(x-1, y);  // takes color of the points in all directions - UP , Down , Left , Right.
        Color c2=getPixelColor(x+1, y);
        Color c3=getPixelColor(x, y-1);
        Color c4=getPixelColor(x, y+1);
        if(isBoundary(c1) || isBoundary(c2)||isBoundary(c3)||isBoundary(c4)) // checks if boundary is reached.
              return;
	
        if( isNotEqual(currentColor,fillColor)&&isNotEqual(boundaryColor,currentColor)) // if boundary is not reached and color is not equal then it fill color.
        {
                 setPixelColor(x, y, fillColor);
                 BoundaryFill(x-1, y, fillColor, boundaryColor);
                 BoundaryFill(x, y-1, fillColor, boundaryColor);
                 BoundaryFill(x+1, y, fillColor, boundaryColor);
                 BoundaryFill(x, y+1, fillColor, boundaryColor);
         }

}

void draw_dda(int  xx1,int yy1,int  xx2,int  yy2)// this functions takes coordinate of two vertices and then draws a line.
{
      glBegin(GL_LINES);
	      glVertex2i(xx1,yy1);
              glVertex2i(xx2,yy2);
      glEnd();
}

#define PI 3.14
int n=600;//no of side of polygon
float angle;
float R=100.0;//radius 
int MyPoint[100000][2];  // this 2D matrix will store coordinates of the vertices of the polygon.


float get_angle(int k)     // this function takes the no of the i-th vertex and returns the angle formed with the center of the polygon.
{
	
	angle=(k*2.0*PI)/n;
	return angle;
}

void Polygon(int X,int Y)    // This function creates the polygon after taking the center of the polygon.
{
	for(int i=1;i<=n;i++)
	{	
		float x=X+R*cos(get_angle(i-1)); // calculation of x coordinate 
		float y=Y+R*sin(get_angle(i-1));  // calculation of y coordinate
                MyPoint[i][0]=(int)x; //storing x and y coordinate in 2D array
                MyPoint[i][1]=(int)y;
        }
	for(int i=2;i<=n;i++)
	{
                draw_dda(MyPoint[i-1][0],MyPoint[i-1][1],MyPoint[i][0],MyPoint[i][1]); // calling dda function to draw the polygon.
	}

        draw_dda(MyPoint[1][0],MyPoint[1][1],MyPoint[n][0],MyPoint[n][1]); // this draws line between initial and final vertices.	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  // clearing color buffer
        glColor3f(0,1,0);   // specifying the boundary color of the polygon
	glBegin(GL_POINTS);
		Polygon(325,225);	// Creating the polygon
	glEnd();	
        Color fillColor = {0.0f, 0.0f, 1.0f};		//blue color will be filled
	Color boundaryColor = {0.0f, 1.0f, 0.0f}; // green- boundary
	Point p = {350, 250};                     // a point inside polygon
	BoundaryFill(p.x,p.y, fillColor, boundaryColor); // calling boundaryfill function to start filling color inside the polygon
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(650, 450);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
