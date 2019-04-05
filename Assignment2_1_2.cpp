#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;


struct Point {
	GLint x;
	GLint y;
}p1,p2,point_,point__;

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void draw_dda(int  xx1,int yy1,int  xx2,int  yy2) {

p1.x=xx1;
p1.y=yy1;
p2.x=xx2;
p2.y=yy2;
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;

	GLfloat step = 0;

	if(abs(dx) > abs(dy)) {
		step = abs(dx);
	} else {
		step = abs(dy);
	}

	GLfloat xInc = dx/step;
	GLfloat yInc = dy/step;

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}

#define PI 3.14
int n=4;//no of side of polygon
float angle;
float R=200.0;//radius 
int MyPoint[100000][2];


float get_angle(int k){
	
	angle=(k*2.0*PI)/n;
	return angle;
}void Polygon(int X,int Y){
	
	for(int i=1;i<=n;i++){
		
		float x=X+R*cos(get_angle(i-1));
		float y=Y+R*sin(get_angle(i-1));
MyPoint[i][0]=(int)x;

MyPoint[i][1]=(int)y;

	
}
	for(int i=2;i<=n;i++)
draw_dda(MyPoint[i-1][0],MyPoint[i-1][1],MyPoint[i][0],MyPoint[i][1]);
draw_dda(MyPoint[1][0],MyPoint[1][1],MyPoint[n][0],MyPoint[n][1]);
	
	
	
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

int Equal(Color c1,Color c2){
if(c1.r!=c2.r ||c1.g!=c2.g||c1.b!=c2.b)
return 0;
else 
return 1;

}
Color black={0,0,0};
void Fill( Point point,Color oldColor,Color newColor){

stack<Point> My_bucket;
My_bucket.push(point );
while(My_bucket.size()>0)
{

  point_=My_bucket.top();
My_bucket.pop();

Color color;
color = getPixelColor(point_.x, point_.y);

//if(Equal(getPixelColor(point_.x+1, point.y),black )|| Equal(getPixelColor(point_.x, point_.y+1),black)||Equal(getPixelColor(point_.x-1, point_.y),black)||Equal(getPixelColor(point_.x, point_.y-1),black))
//continue;
	


if(Equal(oldColor,color))
	{setPixelColor(point_.x,point_.y , newColor);

point__.x=point_.x-1;
point__.y=point_.y;

My_bucket.push(point__);
point__.x=point_.x+1;
point__.y=point_.y;


My_bucket.push(point__);
point__.x=point_.x;
point__.y=point_.y-1;

My_bucket.push(point__ );
point__.x=point_.x;
point__.y=point_.y+1;


My_bucket.push(point__);

}

}

}

void display(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
glBegin(GL_POLYGON);

Polygon(320,240);
	
glEnd();
Color oldColor={0,0,0};
Color newColor={0,1,0};
point_={300,220};
Fill(point_,oldColor,newColor);
	glFlush();
}

int main(int argc, char** argv)
{scanf("%d",&n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}


