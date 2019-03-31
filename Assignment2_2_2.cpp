#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

struct Point 
{
	GLint x;
	GLint y;
}p1,p2,point_,point__;

struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void init()
{
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 650, 0, 450);
}

Color getPixelColor(GLint x, GLint y)
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();

}

int isNotEqual(Color c1,Color c2)
{
        if(c1.r!=c2.r|| c1.g!=c2.g||c1.b!=c2.b)
              return 1;
        else
              return 0;
}

int Equal(Color currentColor,Color green)
{
        if(currentColor.g==1.0 && currentColor.b==0.0 && currentColor.r==0.0)
               return 1;
        else
               return 0;
}

void Fill( Point point,Color fillColor,Color boundaryColor)
{
        stack<Point> My_bucket;
        My_bucket.push(point );
        while(My_bucket.size()>0)
        {
             point_=My_bucket.top();
             My_bucket.pop();

             Color color;
             color = getPixelColor(point_.x, point_.y);
             Color green={0,1,0};

             if(Equal(getPixelColor(point_.x+1, point.y),green )|| Equal(getPixelColor(point_.x, point_.y+1),green)||Equal(getPixelColor(point_.x-1, point_.y),green)||Equal(getPixelColor(point_.x, point_.y-1),green))
                  continue;
	
             if((isNotEqual(fillColor,color))&&(isNotEqual(boundaryColor,color)))
	     {
		     setPixelColor(point_.x,point_.y , fillColor);
                     point__.x=point_.x-1;
                     point__.y=point_.y; 

                     My_bucket.push(point__);
                     point__.x=point_.x+1;
                     point__.y=point_.y;


                     My_bucket.push(point__);
                     point__.x=point_.x;
                     point__.y=point_.y-1;

                     My_bucket.push(point__);
                     point__.x=point_.x;
                     point__.y=point_.y+1;


                     My_bucket.push(point__);

             }

          }

}

void draw_dda(int  xx1,int yy1,int  xx2,int  yy2)
{


	glBegin(GL_LINES);
	glVertex2i(xx1,yy1);
	glVertex2i(xx2,yy2);
	glEnd();
}

#define PI 3.14
int n=4;//no of side of polygon
float angle;
float R=100.0;//radius 
int MyPoint[100000][2];


float get_angle(int k)
{	
	angle=(k*2.0*PI)/n;
	return angle;
}

void Polygon(int X,int Y)
{
	
	for(int i=1;i<=n;i++)
	{
		
		float x=X+R*cos(get_angle(i-1));
		float y=Y+R*sin(get_angle(i-1));
                MyPoint[i][0]=(int)x;
		MyPoint[i][1]=(int)y;
        }
	for(int i=1;i<=n;i++)
                draw_dda(MyPoint[i-1][0],MyPoint[i-1][1],MyPoint[i][0],MyPoint[i][1]);
        draw_dda(MyPoint[1][0],MyPoint[1][1],MyPoint[n][0],MyPoint[n][1]);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0,1,0);
	glBegin(GL_POINTS);
		Polygon(325,225);
	glEnd();
        Color fillColor = {1.0f, 1.0f, 0.0f};		// yellow color will be filled
	Color boundaryColor = {0.0f, 1.0f, 0.0f}; // green- boundary
	Point p = {325, 225}; // a point inside polygon
	Fill(p, fillColor, boundaryColor);
	glFlush();
}

int main(int argc, char** argv)
{
	n=6;
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
