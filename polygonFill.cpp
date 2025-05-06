#include<GL/glut.h>
#include<iostream>
using namespace std;
float boundaryfillcol[3]={1.0,0.0,0.0};
float bordercol[3]={0.0,0.0,1.0};

float FloodFillc[3]={0.0,1.0,0.0};
float oldCol[3]={1.0,1.0,1.0};
int filltype=1;
void myinit()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
void setPixel(int x,int y,float colour[3])
{
    glColor3fv(colour);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void getPixel(int x,int y,float colour[3])
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,colour);
}
void BoundaryFill(int x,int y,float fillColo[3],float border[3])
{
    float interior[3];
    getPixel(x,y,interior);
    if((interior[0]!=border[0]||interior[1]!=border[1]||interior[2]!=border[2])&&(interior[0]!=fillColo[0]||interior[1]!=fillColo[1]||interior[2]!=fillColo[2]))
    {
        setPixel(x,y,fillColo);
        BoundaryFill(x+1,y,fillColo,border);
        BoundaryFill(x-1,y,fillColo,border);
        BoundaryFill(x,y+1,fillColo,border);
        BoundaryFill(x,y-1,fillColo,border);

        /*BoundaryFill(x+1,y+1,  fillColo,border);
        BoundaryFill(x-1,y+1,  fillColo,border);
        BoundaryFill(x+1,y-1,  fillColo,border);
        BoundaryFill(x-1,y-1,  fillColo,border);*/
    }
}

void FloodFill(int x,int y,float Fillcol[3],float oldCol[3])
{
    float interior[3];
    getPixel(x,y,interior);
    if(interior[0]==oldCol[0]&& interior[1]==oldCol[1]&& interior[2]==oldCol[2])
    {
        setPixel(x,y,Fillcol);
        FloodFill(x+1,y,Fillcol,oldCol);
        FloodFill(x-1,y,Fillcol,oldCol);
        FloodFill(x,y+1,Fillcol,oldCol);
        FloodFill(x,y-1,Fillcol,oldCol);
    }
}
void display()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    //glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200,200);
    glVertex2i(400,200);
    glVertex2i(400,400);
    glVertex2i(200,400);
    glEnd();
    glFlush();
}
void mouse(int btn,int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        int xi=x;
        int yi=500-y;
        if(filltype==1)
        {
            BoundaryFill(xi,yi,boundaryfillcol,bordercol);
        }
        else if(filltype==2)
        {
            FloodFill(xi,yi,FloodFillc,oldCol);
        }
    }
}
void menu(int index)
{
    if(index==1)
    {
        filltype=1;
    }
    else if(index==2)
    {
        filltype=2;
    }
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
   // glutInitWindowPosition(10,10);
    glutCreateWindow("polygon");

    glutDisplayFunc(display);
    myinit();
    
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("boundary",1);
    glutAddMenuEntry("flood",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
