// Author: mardonet
// Date: 2025-08-05

#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio> // For sprintf

// Camera rotation
float camAngleX = 48.0f;
float camAngleY = 30.0f;
int lastMouseX, lastMouseY;
bool isDragging = false;

// Toaster structure
struct Toaster {
    float x, y, z;
    float speed;
    float wingAngle;
};

std::vector<Toaster> toasters;
const int NUM_TOASTERS = 20;

void drawWing() {
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f); // Light grey for wings
    glScalef(0.8f, 0.1f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawToaster(float wingAngle) {
    glPushMatrix();

    // Body
    glColor3f(0.7f, 0.7f, 0.7f); // Silver
    glScalef(1.0f, 0.6f, 0.5f);
    glutSolidCube(1.0);

    // Slot
    glColor3f(0.2f, 0.2f, 0.2f); // Dark grey
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    glScalef(0.6f, 0.2f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix(); // Pop body matrix

    // Wings
    float flapAngle = sin(wingAngle) * 45.0f; // Flap between -45 and 45 degrees

    // Front Wing
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.25f); // Move wing to the front
    glRotatef(flapAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.4f);
    drawWing();
    glPopMatrix();

    // Back Wing
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.25f); // Move wing to the back
    glRotatef(-flapAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.4f);
    drawWing();
    glPopMatrix();
}

void initToasters() {
    toasters.resize(NUM_TOASTERS);
    for (int i = 0; i < NUM_TOASTERS; ++i) {
        toasters[i].x = (rand() % 40) + 20; // Start off-screen right
        toasters[i].y = (rand() % 20) - 10; // Random y
        toasters[i].z = (rand() % 40) - 20; // Random z
        toasters[i].speed = 0.01f + (rand() % 5) / 100.0f;
        toasters[i].wingAngle = (float)(rand() % 360);
    }
}

void update() {
    for (int i = 0; i < NUM_TOASTERS; ++i) {
        // Move along X axis only
        toasters[i].x -= toasters[i].speed;
        toasters[i].wingAngle += 0.1f;

        // Reset when off-screen
        if (toasters[i].x < -20) {
            toasters[i].x = 20 + (rand() % 20);
            toasters[i].y = (rand() % 20) - 10;
            toasters[i].z = (rand() % 40) - 20;
        }
    }
    glutPostRedisplay();
}

void renderText(float x, float y, void* font, const char* text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 800, 0.0, 800);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f); // White text
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}

void drawAxes() {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    // X-axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    // Y-axis in green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    // Z-axis in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera
    gluLookAt(0.0, 0.0, 40.0,  // eye position
              0.0, 0.0, 0.0,   // look at position
              0.0, 1.0, 0.0);  // up vector

    // Apply mouse rotation
    glRotatef(camAngleY, 1.0f, 0.0f, 0.0f);
    glRotatef(camAngleX, 0.0f, 1.0f, 0.0f);

    drawAxes();

    // Draw all toasters
    for (int i = 0; i < NUM_TOASTERS; ++i) {
        glPushMatrix();
        glTranslatef(toasters[i].x, toasters[i].y, toasters[i].z);
        drawToaster(toasters[i].wingAngle);
        glPopMatrix();
    }

    // Draw camera coordinates
    char buffer[50];
    sprintf(buffer, "Cam X: %.1f, Cam Y: %.1f", camAngleX, camAngleY);
    renderText(10, 780, GLUT_BITMAP_9_BY_15, buffer);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = false;
        }
    }
}

void motion(int x, int y) {
    if (isDragging) {
        camAngleX += (x - lastMouseX) * 0.5f;
        camAngleY += (y - lastMouseY) * 0.5f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_pos[] = {0.0f, 20.0f, 20.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

int main(int argc, char** argv) {
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Flying Toasters 3D");

    initGL();
    initToasters();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}