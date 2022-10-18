#include <GL/glut.h>
#include <iostream>
using namespace std;

float x_min, x_max, y_min, y_max;
float x_start, y_start, x_end, y_end;
float x_clipped_start, y_clipped_start;
float y_clipped_end, x_clipped_end;
int case_var;

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0); // sets color of drawer
    glPointSize(1.0);
}

void clipping_window()
{
    glColor3f(0, 1, 0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_min, y_max);
    glVertex2f(x_max, y_max);
    glVertex2f(x_max, y_min);
    glEnd();
    glFlush();
}

int code(float x, float y)
{
    int c = 0;
    if (y > y_max)
        c = 8;
    if (y < y_min)
        c = 4;
    if (x > x_max)
        c = c | 2;
    if (x < x_min)
        c = c | 1;
    return c;
}

void myDisplay()
{   
    myInit();
    clipping_window();

    // Drawing Line
    glColor3f(0, 0, 0);

    if(case_var==0){
        glBegin(GL_LINES);
        glVertex2f(x_start, y_start);
        glVertex2f(x_end, y_end);
        glEnd();
    }
    else{
        glBegin(GL_LINES);
        glVertex2f(x_clipped_start, y_clipped_start);
        glVertex2f(x_clipped_end, y_clipped_end);
        glEnd();        
    }

    case_var=1;

    glFlush();
}

void cohen_sutherland()
{
    int c1 = code(x_start, y_start);
    int c2 = code(x_end, y_end);
    x_clipped_start = x_start;
    x_clipped_end = x_end;
    y_clipped_end = y_end;
    y_clipped_start = y_start;


    float m = (float)(y_end-y_start)/(x_end-x_start);
    while ((c1 | c2) > 0)
    {
        if ((c1 & c2) > 0) break;
        
        float xi = x_clipped_start;
        float yi = y_clipped_start;
        int c = c1;

        if (c == 0)
        {
            c = c2;
            xi = x_clipped_end;
            yi = y_clipped_end;
        }

        float x, y;
        if ((c & 8) > 0)
        {
            y = y_max;
            x = xi + 1.0 / m * (y_max - yi);
        }
        else if ((c & 4) > 0)
        {
            y = y_min;
            x = xi + 1.0 / m * (y_min - yi);
        }
        else if ((c & 2) > 0)
        {
            x = x_max;
            y = yi + m * (x_max - xi);
        }
        else if ((c & 1) > 0)
        {
            x = x_min;
            y = yi + m * (x_min - xi);
        }
        if (c == c1)
        {
            x_clipped_start = x;
            y_clipped_start = y;
            c1 = code(x, y);
        }
        if (c == c2)
        {
            x_clipped_end = x;
            y_clipped_end = y;
            c2 = code(x, y);
        }
    }
}


int main(int argc, char **argv)
{

    cout << "Enter Lower left of Clipping Window:\n";
    cin >> x_min >> y_min;
    cout << "Enter Upper Right of Clipping Window: \n";
    cin >> x_max >> y_max;
    cout << "Enter One Endpoint: \n";
    cin >> x_start >> y_start;
    cout << "Enter Other Endpoint: \n";
    cin >> x_end >> y_end;

    cohen_sutherland();
    cout<<"Clipped ends:\n";
    cout<<x_clipped_start<<" "<<y_clipped_start<<endl;
    cout<<x_clipped_end<<" "<<y_clipped_end<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("cohen_sutherland");
    glutDisplayFunc(myDisplay);
    
    glutInitWindowPosition(500, 500);
    glutCreateWindow("cohen_sutherland");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();

    return 0;
}