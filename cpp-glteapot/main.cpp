// Author: mardonet
// Date: 2025-08-03

#include <GL/glut.h>
#include <string.h>

// Rotation angle
static float angle = 0.0f;

// Window dimensions
static int windowWidth = 800;
static int windowHeight = 600;

void init() {
    // Set light properties
    GLfloat light_pos[] = { 4.0, 4.0, 4.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// Function to draw text at 3D world coordinates, centered
void drawText3D(const char *text, float x, float y, float z) {
    glDisable(GL_LIGHTING); // Disable lighting for text
    glColor3f(1.0, 1.0, 1.0); // Set text color to white

    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble screenX, screenY, screenZ;
    gluProject(x, y, z, modelview, projection, viewport, &screenX, &screenY, &screenZ);

    // Calculate text width for centering
    int textWidth = glutBitmapLength(GLUT_BITMAP_9_BY_15, (const unsigned char*)text);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(screenX - (textWidth / 2.0), screenY);
    for (size_t i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING); // Re-enable lighting
}

// Function to draw small text at 2D screen coordinates
void drawSmallText2D(const char *text, float x, float y) {
    glDisable(GL_LIGHTING); // Disable lighting for text
    glColor3f(1.0, 1.0, 1.0); // Set text color to white
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x, y);
    for (size_t i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING); // Re-enable lighting
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // --- 1. Flat Shading ---
    glPushMatrix();
    glTranslatef(-3.0, 0.0, 0.0);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    GLfloat mat_flat[] = {0.2f, 0.2f, 0.8f, 1.0f}; // Dark Blue
    GLfloat mat_flat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_flat_shininess[] = {0.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_flat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_flat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_flat_shininess);
    glutSolidTeapot(1.0);
    glPopMatrix();
    drawText3D("Flat Shading", -3.0, -1.5, 0.0); // Position text below teapot

    // --- 2. Gouraud Shading ---
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    GLfloat mat_gouraud[] = {0.3f, 0.5f, 1.0f, 1.0f}; // Light Blue
    GLfloat mat_gouraud_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat mat_gouraud_shininess[] = {30.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_gouraud);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_gouraud_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_gouraud_shininess);
    glutSolidTeapot(1.0);
    glPopMatrix();
    drawText3D("Gouraud Shading", 0.0, -1.5, 0.0); // Position text below teapot

    // --- 3. Phong Shading (Simulated with high shininess) ---
    glPushMatrix();
    glTranslatef(3.0, 0.0, 0.0);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    GLfloat mat_phong[] = {0.1f, 0.3f, 0.6f, 1.0f}; // Deeper Blue
    GLfloat mat_phong_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_phong_shininess[] = {100.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_phong);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_phong_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_phong_shininess);
    glutSolidTeapot(1.0);
    glPopMatrix();
    drawText3D("Phong Shading", 3.0, -1.5, 0.0); // Position text below teapot

    // Draw legend in the lower-left corner
    drawSmallText2D("@mardonet", 10, 10);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);

    // Update global window dimensions
    windowWidth = w;
    windowHeight = h;
}

void idle() {
    angle += 0.2f; // Increment rotation angle
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    glutPostRedisplay(); // Redraw the scene
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shading Comparison: Flat, Gouraud, Phong");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle); // Set the idle function for animation
    glutMainLoop();
    return 0;
}
