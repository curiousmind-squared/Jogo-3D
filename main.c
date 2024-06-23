#include <GL/glut.h>
#include <stdio.h>

// Define initial viewing parameters
//GLfloat eyeX = 2.0, eyeY = 2.0, eyeZ = 2.0;
GLfloat eyeX = 1.2, eyeY = 0.6, eyeZ = 0.2;


// Define initial viewing parameters
GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
GLfloat upX = 0.0, upY = 1.0, upZ = 0.0;
GLfloat stepSize = 0.1;

int frameNumber = 0;


void init() {
    // Set the clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Set the shading model to flat
    //glShadeModel(GL_FLAT);
}

void drawFace1() {
   glBegin(GL_LINE_LOOP);
     glVertex3f(1, -1,  1);
     glVertex3f(1, -1, -1);
     glVertex3f(1,  1, -1);
     glVertex3f(1,  1,  1);
   glEnd();
}

void drawFace2() {
   glBegin(GL_LINE_LOOP);
     glVertex3f(1 , -1, 1);
     glVertex3f(-1, -1, 1);
     glVertex3f(-1,  1, 1);
     glVertex3f(1 ,  1, 1);
   glEnd();
}

void drawFace3() {
  glBegin(GL_LINE_LOOP);
     glVertex3f(-1, -1,  1);
     glVertex3f(-1, -1, -1);
     glVertex3f(-1,  1, -1);
     glVertex3f(-1,  1,  1);
  glEnd();
}

void drawFace4() {
  glBegin(GL_LINE_LOOP);
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f(-1,  1, -1 );
  glEnd();

}

void drawFace5() {
  glBegin(GL_LINE_LOOP);
    glVertex3f(1, 1,  1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
  glEnd();
}

void drawFace6() {
  glBegin(GL_LINE_LOOP);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
  glEnd();
}

void drawCube() {
   glPushMatrix();
   glTranslatef(0, 0.1, 0);
   glScalef(0.1, 0.1, 0.3);
   drawFace1();
   drawFace2();
   drawFace3();
   drawFace4();
   drawFace5();
   drawFace6();
   glPopMatrix();
}

void display() {
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Carro
    glColor3f(1.0, 1.0, 1.0);
    drawCube(); 

    // Roda 1
    /*
    glPushMatrix();
      glTranslatef(0.1, 0.0, -0.25);
      glScalef(0.1, 0.1, 0.15);
      glRotated(frameNumber*-1, 1, 0, 0);
      drawCube();
    glPopMatrix();
    */
    // Set the line width
    glLineWidth(2.0);

    // Draw the x, y, and z axes
    glBegin(GL_LINES);
    // X axis (red)
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    // Y axis (green)
    glColor3f(0.0, 1.0, 0.0); // Set color to green
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    // Z axis (blue)
    glColor3f(0.0, 0.0, 1.0); // Set color to blue
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

     

    // Flush the buffer to display the drawing
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move forward
            eyeZ -= stepSize;
            break;
        case 's': // Move backward
            eyeZ += stepSize;
            break;
        case 'a': // Move left
            eyeX -= stepSize;
            break;
        case 'd': // Move right
            eyeX += stepSize;
            break;
        case 'q': // Move up
            eyeY += stepSize;
            break;
        case 'e': // Move down
            eyeY -= stepSize;
            break;
        case 27:  // Escape key
            exit(0);
            break;
        default:
            break;
    }
    // Update the view
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    printf("eyeX: %f ; eyeY: %f ; eyeZ: %f\n", eyeX, eyeY, eyeZ);
    glutPostRedisplay();
}

void doFrame() {
	frameNumber++;
	glutPostRedisplay();
	glutTimerFunc(20, doFrame, 0);
}

int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Axes");

    // Initialize drawing settings
    init();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(20, doFrame, 0);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}

