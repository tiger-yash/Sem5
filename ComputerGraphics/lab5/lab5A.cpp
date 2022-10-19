// compilation cmd- g++ -lGL -lGLU -lglut filename.cpp -o filename
#include <GL/glut.h> 
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)

template <typename T>
class matrix
{
public:
   vector<vector<T>> val;
   int n;
   matrix(int s)
   {
       n = s;
       val.resize(n);
       for (int i = 0; i < n; i++)
           val[i].resize(n);
   }
   matrix<T> &operator=(const matrix<T> &b)
   {
       val = b.val;
       n = b.n;
       return *this;
   }
   vector<T> column_multiply(const vector<T> &col)
   {
       int n = col.size();
       vector<T> row(n);
       for (int i = 0; i < n; i++)
       {
           for (int j = 0; j < n; j++)
           {
               row[i] += this->val[i][j] * col[j];
           }
       }
       return row;
   }
   void print()
   {
       rep(i, 0, n)
       {
           rep(j, 0, n)
           {
               cout << val[i][j] << " ";
           }
           cout << endl;
       }
   }
   matrix<T> operator*(const matrix<T> &b) const
   {
       matrix<T> ans(b.n);
       for (int i = 0; i < b.n; i++)
       {
           for (int j = 0; j < b.n; j++)
           {
               for (int k = 0; k < b.n; k++)
               {
                   ans.val[i][j] += this->val[i][k] * b.val[k][j];
               }
           }
       }
       return ans;
   }
   matrix<T> identity(int N)
   {
       matrix<T> ans(N);
       for (int i = 0; i < N; i++)
       {
           ans.val[i][i] = 1;
       }

       return ans;
   }
};

namespace Geometry
{
   vector<vector<float>> a = {{40, 40, -50}, {90, 40, -50}, {90, 90, -50}, {40, 90, -50}, {30, 30, 0}, {80, 30, 0}, {80, 80, 0}, {30, 80, 0}};
   vector<vector<float>> colors = {{0.7, 0.4, 0.7}, {0.2, 0.5, 0.3}, {0.2, 0.4, 0.7}, {0.5, 0.4, 0.3}, {0.5, 0.7, 0.2}, {0.2, 0.3, 0.4}};

   void display(vector<vector<float>> a)
   {
       int i;
       glColor3f(1.0, 0.0, 0.0);
       glBegin(GL_POLYGON);
       glVertex3f(a[0][0], a[0][1], a[0][2]);
       glVertex3f(a[1][0], a[1][1], a[1][2]);
       glVertex3f(a[2][0], a[2][1], a[2][2]);
       glVertex3f(a[3][0], a[3][1], a[3][2]);
       glEnd();
       i = 0;
       glColor3f(1.0, 0, 0);
       glBegin(GL_POLYGON);
       glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
       glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
       glVertex3f(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
       glVertex3f(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
       glEnd();
       glColor3f(0, 1, 0);
       glBegin(GL_POLYGON);
       glVertex3f(a[0][0], a[0][1], a[0][2]);
       glVertex3f(a[3][0], a[3][1], a[3][2]);
       glVertex3f(a[7][0], a[7][1], a[7][2]);
       glVertex3f(a[4][0], a[4][1], a[4][2]);
       glEnd();
       i = 1;
       glColor3f(0, 0, 1);
       glBegin(GL_POLYGON);
       glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
       glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
       glVertex3f(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
       glVertex3f(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
       glEnd();
       i = 2;
       glColor3f(1.0, 0.4, 0.1);
       glBegin(GL_POLYGON);
       glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
       glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
       glVertex3f(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
       glVertex3f(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
       glEnd();
       i = 4;
       glColor3f(0.4, 1.0, 0.4);
       glBegin(GL_POLYGON);
       glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
       glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
       glVertex3f(a[2 + i][0], a[2 + i][1], a[2 + i][2]);
       glVertex3f(a[3 + i][0], a[3 + i][1], a[3 + i][2]);
       glEnd();
   }
   void draw_axes()
   {
       glColor3f(0.0, 0.0, 0.0); // Set the color to BLACK
       glBegin(GL_LINES);        // Plotting X-Axis
       glVertex2s(-1000, 0);
       glVertex2s(1000, 0);
       glEnd();
       glBegin(GL_LINES); // Plotting Y-Axis
       glVertex2s(0, -1000);
       glVertex2s(0, 1000);
       glEnd();
   }

   int type;
   float x, y, z;
   float theta;
   vector<float> hx(2), hy(2), hz(2);
   int choice;

   void Main()
   {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       draw_axes();
       display(a);

       auto transalte = [&](float x, float y, float z)
       {
           matrix<float> mat(4);
           mat.val = {{1, 0, 0, x},
                      {0, 1, 0, y},
                      {0, 0, 1, z},
                      {0, 0, 0, 1}};

           return mat;
       };
       auto scaling = [&](float x, float y, float z)
       {
           matrix<float> mat(4);
           mat.val = {{x, 0, 0, 0}, {
                                        0,
                                        y,
                                        0,
                                        0,
                                    },
                      {0, 0, z, 0},
                      {0, 0, 0, 1}};
           return mat;
       };
       auto shearing = [&](float y, float z)
       {
           matrix<float> mat(4);
           mat.val = {{1, 0, 0, 0}, {y, 1, 0, 0}, {z, 0, 1, 0}, {0, 0, 0, 1}};
           return mat;
       };
       auto rotation = [&](float theta)
       {
           matrix<float> mat(4);
           mat.val = {{cos(theta), -sin(theta), 0, 0}, {sin(theta), cos(theta), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
           return mat;
       };
       auto reflection = [&](int choice)
       {
           matrix<float> mat(4);
           mat = mat.identity(4);
           if (choice == 1)
           {
               //xy
               mat.val[2][2] = -1;
           }
           else if (choice == 2)
           {
               //xz
               mat.val[1][1] = -1;
           }
           else
           {
               //yz
               mat.val[0][0] = -1;
           }
           return mat;
       };
       matrix<float> mat(4);
       if (type == 1)
       {
           mat = transalte(x, y, z);
       }
       else if (type == 2)
       {
           float th = acos(-1);
           th /= 180;
           mat = rotation(th * theta);
       }
       else if (type == 3)
       {
           mat = reflection(choice);
       }
       else if (type == 4)
       {
           mat = scaling(x, y, z);
       }
       else
       {
           assert(type == 5);
           mat = shearing(y, z);
       }
       vector<vector<float>> a2 = a;
       for (auto &i : a2)
       {
           vector<float> col = {i[0], i[1], i[2], 1};
           col = mat.column_multiply(col);
           i = {col[0], col[1], col[2]};
       }
       display(a2);
       glFlush();
   }
} // namespace Geometry

using namespace Geometry;

int main(int argc, char **argv)
{

   cout << "Enter 1 for translation" << endl;
   cout << "Enter 2 for rotation(around z-axis)" << endl;
   cout << "Enter 3 for reflection" << endl;
   cout << "Enter 4 for scaling" << endl;
   cout << "Enter 5 for shearing(X-axis)" << endl;
   cout << "Your choice: ";
   cin >> type;
   if (type == 1)
   {
       cout << "Enter Translation Paramters(tx,ty,tz): ";
       cin >> x >> y >> z;
   }
   else if (type == 2)
   {
       cout << "Enter Rotation Paramters(theta in degrees): ";
       cin >> theta;
   }
   else if (type == 3)
   {
       cout << "1 for reflection around x-y plane" << endl;
       cout << "2 for reflection around x-z plane" << endl;
       cout << "3 for reflection around z-y plane" << endl;
       cin >> choice;
       if (choice != 1 and choice != 2 and choice != 3)
       {
           cout << "Wrong option" << endl;
           exit(0);
       }
   }
   else if (type == 4)
   {
       cout << "Enter Scaling Paramters(sx,sy,sz): ";
       cin >> x >> y >> z;
   }
   else if (type == 5)
   {
       cout << "Enter Shearing Paramters(Shy,Shz): ";
       cin >> y >> z;
   }
   else
   {
       cout << "Wrong option" << endl;
       exit(0);
   }

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1362, 750);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Transformations ");
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glOrtho(-50, 400.0, -50.0, 400.0, -50.0, 400.0);
   glEnable(GL_DEPTH_TEST);
   glutDisplayFunc(Main);
   glutMainLoop();
}