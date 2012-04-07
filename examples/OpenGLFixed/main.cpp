/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

 // Modified by Borislav Stanimirov for MathGP, April 2012

#include <GL/gl.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <mathgp/mathgp.h>

using namespace mathgp;

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    matrix projection =
        //matrix::perspective_rh(2*ar, 2, 2, 100);
        //matrix::ortho_rh(0, 5*ar, 0, 5, 2, 100);
        //matrix::ortho_rh(0, 2.5f*ar, 0, 2.5f, 2, 100);
        //matrix::perspective_rh(0, 2*ar, 0, 2, 2, 100);
        matrix::perspective_fov_rh(constants<float>::PI()/3, ar, 2, 100);
    glLoadMatrixf(projection.as_array());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const float4 light_ambient  = v(0.0f, 0.0f, 0.0f, 1.0f);
const float4 light_diffuse  = v(1.0f, 1.0f, 1.0f, 1.0f);
const float4 light_specular = v(1.0f, 1.0f, 1.0f, 1.0f);
const float4 light_position = v(2.0f, 5.0f, 5.0f, 0.0f);

const float4 mat_ambient     = v(0.7f, 0.7f, 0.7f, 1.0f);
const float4 mat_diffuse     = v(0.8f, 0.8f, 0.8f, 1.0f);
const float4 mat_specular    = v(1.0f, 1.0f, 1.0f, 1.0f);
const GLfloat high_shininess = 100.0f;

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient.as_array());
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse.as_array());
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular.as_array());
    glLightfv(GL_LIGHT0, GL_POSITION, light_position.as_array());

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient.as_array());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse.as_array());
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular.as_array());
    glMaterialfv(GL_FRONT, GL_SHININESS, &high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
