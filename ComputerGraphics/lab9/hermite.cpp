#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

namespace Geometry
{
#define N 4   // number of control points
#define D 2   // number of dimensions
#define T 100 // number of u subintervals

 static GLfloat ctrlPoints[N][3] = {
     {100, 100, 0}, {200, 350, 0}, {~400, 300, 0}, {480, 100, 0}};
 GLUnurbsObj *theNurb;

 int ww = 1000;
 int wh = 800;
 int MOVENAME = -1;
 int pickRadius = 50;

 void display2DControlPolyline()
 {
   glLineWidth(2.0);
   glColor3f(1.0f, 0.0f, 0.0f);

   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < N; i++)
   {
     glVertex2i(ctrlPoints[i][0], ctrlPoints[i][1]);
   }
   glEnd();
   glFlush();
 }

 void display2DControlPoints()
 {
   glPointSize(3.0);
   glColor3f(0.0f, 1.0f, 0.0f);

   glBegin(GL_POINTS);
   for (int i = 0; i < N; i++)
   {
     glVertex2i(ctrlPoints[i][0], ctrlPoints[i][1]);
   }
   glEnd();
   glFlush();
 }

 void hermite()
 {
   cout << "Calculating Hermite Form with specific endpoint tangents..."
        << endl;

   glLineWidth(4.0);
   glColor3f(1.0f, 1.0f, 1.0f);

   GLfloat fu[N];

   glBegin(GL_LINE_STRIP);

   for (int uInt = 0; uInt <= T; uInt++)
   {
     GLfloat u = uInt / (GLfloat)T;
     GLfloat u2 = u * u;
     GLfloat u3 = u2 * u;
     fu[0] = 2.0 * u3 - 3.0 * u2 + 1.0;
     fu[1] = -2.0 * u3 + 3.0 * u2;
     fu[2] = u3 - 2.0 * u2 + u;
     fu[3] = u3 - u2;

     GLfloat x = 0.0;
     GLfloat y = 0.0;

     // p0 = ctrlPoints[0]
     x += fu[0] * ctrlPoints[0][0];
     y += fu[0] * ctrlPoints[0][1];

     // p1 = ctrlPoints[3]
     x += fu[1] * ctrlPoints[3][0];
     y += fu[1] * ctrlPoints[3][1];

     //  tangent at p0 = ctrlPoints[1]-ctrlPoints[0]
     x += fu[2] * (3.0 * (ctrlPoints[1][0] - ctrlPoints[0][0]));
     y += fu[2] * (3.0 * (ctrlPoints[1][1] - ctrlPoints[0][1]));

     //  tangent at p1 = ctrlPoints[3]-ctrlPoints[2]
     x += fu[3] * (6.0 * (ctrlPoints[3][0] - ctrlPoints[2][0]));
     y += fu[3] * (6.0 * (ctrlPoints[3][1] - ctrlPoints[2][1]));

     cout << "x = " << x << " , "
          << "y = " << y << endl;
     glVertex2i(x, y);
   }

   glEnd();
   glFlush();
 }

 void myDisplay()
 {
   glClear(GL_COLOR_BUFFER_BIT);
   display2DControlPolyline();
   display2DControlPoints();
   hermite();
   glFlush();
 }

 void init() {}

 // mouse function
 void myPick(int button, int state, int xPosition, int yPosition)
 {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
     GLuint newX = xPosition;
     GLuint newY = wh - yPosition;
     int choiceFound = 0;

     for (int i = 0; i < N && !choiceFound; i++)
     {
       if ((abs(ctrlPoints[i][0] - newX) <= pickRadius) &&
           (abs(ctrlPoints[i][1] - newY) <= pickRadius))
       {
         MOVENAME = i;
         choiceFound = 1;
       }
     }
   }
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
   {
     MOVENAME = -1;
   }
   glutPostRedisplay();
 }

 void myMouseMove(int xPosition, int yPosition)
 {
   if (MOVENAME > -1)
   {
     GLuint newX = xPosition;
     GLuint newY = wh - yPosition;
     ctrlPoints[MOVENAME][0] = newX;
     ctrlPoints[MOVENAME][1] = newY;
     glutPostRedisplay();
   }
 }

 void reshape(int w, int h)
 {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   ww = w;
   wh = h;
 }

} // namespace Geometry
using namespace Geometry;

int main(int argc, char **argv)
{

 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(ww, wh);
 glutInitWindowPosition(0, 0);
 glutCreateWindow("Hermite Curve");
 glutDisplayFunc(myDisplay);
 glutMouseFunc(myPick);
 glutMotionFunc(myMouseMove);
 glutReshapeFunc(reshape);
 glClearColor(0.0, 0.0, 1.0, 0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0.0, ww, 0.0, wh);

 glutMainLoop();
 return 0;
}