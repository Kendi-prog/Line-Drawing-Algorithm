#include <GL/glut.h>
#include <math.h>


static void setPixel(int x, int y, float brightness) {
    glColor3f(brightness, brightness, brightness);  
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Xiaolin Wu's Line Algorithm
static void drawWuLine(float x1, float y1, float x2, float y2) {
    bool steep = fabs(y2 - y1) > fabs(x2 - x1);

    // Swap x and y if the line is steep
    if (steep) {
        float temp;
        temp = x1; x1 = y1; y1 = temp;
        temp = x2; x2 = y2; y2 = temp;
    }

    // Swap start and end points if necessary
    if (x1 > x2) {
        float temp;
        temp = x1; x1 = x2; x2 = temp;
        temp = y1; y1 = y2; y2 = temp;
    }

    float dx = x2 - x1;
    float dy = y2 - y1;
    float gradient = dy / dx;

    // Handle the first endpoint
    float xEnd = round(x1);
    float yEnd = y1 + gradient * (xEnd - x1);
    float xGap = 1.0 - fmod(x1 + 0.5, 1.0);
    int xPixel1 = (int)xEnd;
    int yPixel1 = (int)yEnd;

    if (steep) {
        setPixel(yPixel1, xPixel1, (1 - fmod(yEnd, 1.0)) * xGap);
        setPixel(yPixel1 + 1, xPixel1, fmod(yEnd, 1.0) * xGap);
    }
    else {
        setPixel(xPixel1, yPixel1, (1 - fmod(yEnd, 1.0)) * xGap);
        setPixel(xPixel1, yPixel1 + 1, fmod(yEnd, 1.0) * xGap);
    }

    // Iterate over pixels
    float interY = yEnd + gradient;  // Starting Y-intercept
    for (int x = xPixel1 + 1; x < x2; x++) {
        if (steep) {
            setPixel((int)interY, x, 1 - fmod(interY, 1.0));
            setPixel((int)interY + 1, x, fmod(interY, 1.0));
        }
        else {
            setPixel(x, (int)interY, 1 - fmod(interY, 1.0));
            setPixel(x, (int)interY + 1, fmod(interY, 1.0));
        }
        interY += gradient;
    }
}

// OpenGL display function
static void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);  // Set pixel size
    drawWuLine(1, 1, 3, 5);
    glFlush();
}

// Initialize OpenGL
static void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 10);  // Define coordinate system
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Xiaolin Wu's Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

