/* 
 * sombrero_gl.c
 * depends: freeglut3-dev
 * build: gcc sombrero_gl.c -lGL -lGLU -lglut -lm -o sombrero_gl
 */

#include <GL/glut.h>
#include <math.h>

#define NX 100          // grid columns
#define NY 100          // grid rows
#define SPACING 0.15f   // distance between points

float angle = 0.0f;

// ----- STEP 1: Define the sombrero function -----
float sombrero(float x, float y) {
    float r = sqrtf(x*x + y*y);
    return (r < 1e-6f) ? 1.0f : (sinf(r) / r) * 4.0f;
}

// ----- STEP 2: Display function -----
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // camera setup
    glTranslatef(0.0f, 0.0f, -12.0f); // distance
    glRotatef(32.0f, 1.0f, 0.0f, 0.0f); // tilt
    glRotatef(angle, 0.0f, 1.0f, 0.0f);  // spin

    // draw mesh
    for(int j = 0; j < NY-1; j++){
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < NX; i++){
            for(int row = j; row <= j+1; row++){
                float x = (i - NX/2) * SPACING;
                float y = (row - NY/2) * SPACING;
                float z = sombrero(x, y);
                float z_norm = (z/3.0f + 0.5f);
                // color
                glColor3f(
                    1.0f * z_norm,          // R: 0 → 1
                    0.5f * z_norm,          // G: 0 → 0.5
                    0.5f * (1.0f - z_norm)  // B: 0.5 → 0
                );
                glVertex3f(x, z, y);
            }
        }
        glEnd();
    }
    glutSwapBuffers();
}

// ----- STEP 3: Idle function for rotation -----
void idle(void) {
    angle += 0.3f;
    if(angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

// ----- STEP 4: Window reshape -----
void reshape(int w, int h){
    if(h==0) h=1;
    float ratio = (float)w / (float)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
}

// ----- STEP 5: Main function -----
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spinning Sombrero");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
