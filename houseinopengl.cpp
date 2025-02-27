#include <GL/glut.h>

// Function to display the house
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //house - Rectangle
    glColor3f(1.8, 0.8, 0.2);
    glBegin(GL_POLYGON);
    glVertex2i(30, 20);
    glVertex2i(70, 20);
    glVertex2i(70, 50);
    glVertex2i(30, 50);
    glEnd();

    //Roof -Triangle
    glColor3f(0.6, 0.2, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2i(25, 50);
    glVertex2i(75, 50);
    glVertex2i(50, 75);
    glEnd();

    // Door - Rectangle
    glColor3f(0.4, 0.2, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(45, 20);
    glVertex2i(55, 20);
    glVertex2i(55, 35);
    glVertex2i(45, 35);
    glEnd();

    // Window  - Rectangle
    glColor3f(0.0, 0.6, 0.8);
    glBegin(GL_POLYGON);
    glVertex2i(35, 35);
    glVertex2i(43, 35);
    glVertex2i(43, 43);
    glVertex2i(35, 43);
    glEnd();

    //Window - Rectangle
    glBegin(GL_POLYGON);
    glVertex2i(57, 35);
    glVertex2i(65, 35);
    glVertex2i(65, 43);
    glVertex2i(57, 43);
    glEnd();

    glFlush();
}


void init() {
    glClearColor(0.5, 1.8, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("House in OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
