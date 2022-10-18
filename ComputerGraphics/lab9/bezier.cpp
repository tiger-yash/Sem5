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
     {100, 100, 0}, {200, 350, 0}, {400, 300, 0}, {480, 100, 0}};
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

 GLfloat bernstein(GLfloat u, int i, int n)
 {
   GLfloat choose[N] = {1, 3, 3, 1};
   GLfloat nChoosei = choose[i];
   GLfloat ui = pow(u, i);
   GLfloat oneMinusu = pow(1.0 - u, n - i);

   return (nChoosei * ui * oneMinusu);
 }

 void bezier()
 {
   cout << "Calculating Bezier Form using Bernstein polynomials..."
        << endl;

   glLineWidth(4.0);
   glColor3f(1.0f, 1.0f, 1.0f);

   glBegin(GL_LINE_STRIP);

   for (int uInt = 0; uInt <= T; uInt++)
   {
     GLfloat u = uInt / (GLfloat)T;

     GLfloat x = 0.0;
     GLfloat y = 0.0;

     for (int i = 0; i < N; i++)
     {
       GLfloat b = bernstein(u, i, N - 1);
       x += b * ctrlPoints[i][0];
       y += b * ctrlPoints[i][1];
     }
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
   bezier();
   glFlush();
 }

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
 glutCreateWindow("Beizer Curve");
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