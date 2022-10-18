#include <GL/glut.h>
#include <bits/stdc++.h>
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
    glLineWidth(2);
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

void liang_barsky()
{
    auto lx = x_min, ly = y_min, rx = x_max, ry = y_max;
    auto lu = x_start, lv = y_start, ru = x_end, rv = y_end;

    float p[] = {
        0,
        lu - ru,
        ru - lu,
        lv - rv,
        rv - lv
    };

    float q[] = {
        0,
        lu - lx,
        rx - lu,
        lv - ly,
        ry - lv
    };

    float t1 = 0, t2 = 1;

    for (int i: {1,2,3,4}) {
        if (p[i] == 0 and q[i] < 0)
            return;

        if (p[i] < 0)
            t1 = max(t1, max(0.0f, q[i] / p[i]));
        else if (p[i] > 0)
            t2 = min(t2, min(1.0f, q[i] / p[i]));
    }

    if (t1 > t2) return;

    x_clipped_start = lu + t1 * (ru - lu);
    y_clipped_start = lv + t1 * (rv - lv);
    x_clipped_end = lu + t2 * (ru - lu);
    y_clipped_end = lv + t2 * (rv - lv);

}


int main(int argc, char **argv)
{

    cout << "Enter Lower left coordinate of Clipping Window:\n";
    cin >> x_min >> y_min;
    cout << "Enter Upper Right coordinate of Clipping Window: \n";
    cin >> x_max >> y_max;
    cout << "Enter One Endpoint: \n";
    cin >> x_start >> y_start;
    cout << "Enter Other Endpoint: \n";
    cin >> x_end >> y_end;
    
    liang_barsky();
    cout<<"Clipped ends:\n";
    cout<<x_clipped_start<<" "<<y_clipped_start<<endl;
    cout<<x_clipped_end<<" "<<y_clipped_end<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("liang_barsky");
    glutDisplayFunc(myDisplay);

    glutInitWindowPosition(0, 0);
    glutCreateWindow("clipped_line");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();

    return 0;
}