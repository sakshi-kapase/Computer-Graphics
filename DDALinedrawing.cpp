#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int w = 1200;
int h = 700;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0, 0, 0); // Black drawing color
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w, w, -h, h);
}

//Sign Function
int sign(int num) {
    if (num > 0) return 1;
    else if (num < 0) return -1;
    else return 0;
}

void ddaAlgorithm(int x1, int y1, int x2, int y2, int LineType) {

    if (x1 == x2 && y1 == y2) {
        cout << "Error: Source and Destination points are the same! Line cannot be drawn." << endl;
        return;
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int length;

    if (abs(dx) > abs(dy)) {
        length = abs(dx);
    } else {
        length = abs(dy);
    }

    float Xinc = (float)dx / length;
    float Yinc = (float)dy / length;

    //Adjusted initial point using sign function
    float x = x1 + 0.5 * sign(Xinc);
    float y = y1 + 0.5 * sign(Yinc);

    glBegin(GL_POINTS);
    for (int i = 0; i <= length; i++) {
        if (LineType == 1) {  //solid line
            glVertex2i(round(x), round(y));
        } else if (LineType == 2) {  //Dashed Line
            if (((i%10)<5)) glVertex2i(round(x), round(y));
        } else if (LineType == 3) { //Dotted Line
            if (i % 10 == 0) glVertex2i(round(x), round(y));
        }
        x=x+Xinc;
        y=y+Yinc;
    }
    glEnd();
    glFlush();
}
void drawAxis() {
    glColor3f(1, 0, 0); // Red color for axis
    ddaAlgorithm(-w, 0, w, 0, 1);
    ddaAlgorithm(0, -h, 0, h, 1);
}

void drawBoat()
{
    ddaAlgorithm(400, 200, 700, 200, 1);
    ddaAlgorithm(400, 200, 450, 250, 1);
    ddaAlgorithm(700, 200, 650, 250, 1);
    ddaAlgorithm(450, 250, 650, 250, 1);

    ddaAlgorithm(550, 250, 550, 400, 1);

    ddaAlgorithm(550, 400, 650, 350, 1);
    ddaAlgorithm(650, 350, 550, 300, 1);

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
}

void menu(int index) {
    if (index == 1) {
        ddaAlgorithm(100, 100,200,200, 1); // Simple Line
    } else if (index == 2) {
        ddaAlgorithm(-100, -200, -500, -300, 2); // Dashed Line
    } else if (index == 3) {
        ddaAlgorithm(200, -100, 500, -200, 3); // Dotted Line
    } else if (index == 4) {
        drawBoat(); // Draw  boat
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("DDA Algorithm");

    glutDisplayFunc(display);
    myInit();

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 1);
    glutAddMenuEntry("Dashed Line", 2);
    glutAddMenuEntry("Dotted Line", 3);
    glutAddMenuEntry("Boat", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
