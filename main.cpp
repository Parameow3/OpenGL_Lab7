/**
 *
 * Created on 26/06/2023 By: Tan Bunchhay
 */

// require header
#include <math.h>

using namespace std;

// pre-define header
#if __APPLE__
#include <GLUT/glut.h>
#elif _WIN64
#include <GL/glut.h>
#include <iostream>
#endif

using namespace std;

//#region VARIABLES
int submenu_ResizeClippingRegion;
int valueClippingSize;
int submenu_Color;
int valueColor;
int menu;
//#endregion

//#region PRE-DEFINE
void display(void);

void init(void);

void selectMenu(int n);

void createMenu();

void drawClippingRegion(int w, int h);

void resizeClippingRegion();
//#endregion

void display(void) {
    // clear background of current window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();// Reset the model-view matrix
    gluOrtho2D(0, 1000.0, 0, 600.0);

    glColor3f(0, 0, 0);

    resizeClippingRegion();

    glFlush();
}

//#region CLIPPING_METHOD
void resizeClippingRegion() {
    switch (valueClippingSize) {
        case 1:
            drawClippingRegion(300, 150);
            break;
        case 2:
            drawClippingRegion(500, 250);
            break;
        case 3:
            drawClippingRegion(800, 400);
            break;
    }
}

void drawClippingRegion(int w, int h) {
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    x1 = 500 - (w/2);
    y1 = 300 + (h/2);
    x2 = 500 + (w/2);
    y2 = y1;
    x3 = x2;
    y3 = 300 - (h/2);
    x4 = x1;
    y4 = y3;

    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);
    glEnd();
}
//#endregion

//#region START_PROGRAM
void init(void) {
    //Clear background color to white
    glClearColor(1.0, 0.8980, 0.8, 0.0);

    //change projection mode
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(200, 200);
    menu = glutCreateWindow("Menu");
    createMenu();
    init();
//    reqInput();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
//#endregion

//#region MENU_TAB
void selectMenu(int n) {
    // if n = 0, exit the program
    if (n == 0) {
        glutDestroyWindow(menu);
        exit(0);
    } else if (n > 0 && n < 4) {
        valueClippingSize = n;
    } else if (n > 5 && n < 9) {
        valueColor = n;
    } else if (n == 4) {

    } else if (n == 5) {

    }

    glutPostRedisplay();
}

void createMenu() {

    // for line drawing
    submenu_ResizeClippingRegion = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("300 x 150", 1);
    glutAddMenuEntry("500 x 250", 2);
    glutAddMenuEntry("800 x 400", 3);

    // for clip color
    submenu_Color = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("Red", 6);
    glutAddMenuEntry("Orange", 7);
    glutAddMenuEntry("Pink", 8);


    menu = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu

    glutAddSubMenu("Resize Clipping Region", submenu_ResizeClippingRegion);
    glutAddMenuEntry("Add Lines", 4);
    glutAddMenuEntry("Clip", 5);
    glutAddSubMenu("Clip Color", submenu_Color);
    glutAddMenuEntry("Exit", 0); // add exit to menu
    // attach menu to the right button of the mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
//#endregion