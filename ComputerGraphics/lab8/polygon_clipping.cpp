#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

int n_clip, n_poly;
using point = pair<float, float>;
vector<point> poly, clip, final;
int case_var=0;

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glPointSize(1.0);
    glLineWidth(2);
}

void clipping_window()
{
    glColor3f(0.8, 0, 1);
    glBegin(GL_LINE_LOOP);

    for (auto [x, y]: clip)
    	glVertex2f(x, y);

    glEnd();
    glFlush();
}



void myDisplay()
{   
    myInit();
    clipping_window();

    // Drawing Poly
    glColor3f(0.07f, 0.59f, 0.59f);
    glBegin(GL_POLYGON);

    for (auto [x, y]: poly)
    	glVertex2f(x, y);

    glEnd();
    glFlush();
}



float cross (const point A, const point B) {
	return A.first * B.second - A.second * B.first;
};

point subtract (const point A, const point B) {
	return point(A.first - B.first, A.second - B.second);
};

point intersection (const pair<point, point> A, const pair<point, point> B) {
	const point A_ = subtract(A.second, A.first);
	const point B_ = subtract(B.second, B.first);

	const point AB = subtract(A.first, B.first);

	float t = cross(B_, AB) / cross(A_, B_);

	return point(A.first.first * (1 - t) + A.second.first * t,
				 A.first.second * (1 - t) + A.second.second * t);
};

void clip_polygon(const point p0, const point p1)
{
	vector<point> list;

	for (int i = 0; i < final.size(); i++) {
		const point A = final[i],
					B = final[(i + 1) % final.size()];

		const auto pA = cross(subtract(p1, p0), subtract(A, p0));
		const auto pB = cross(subtract(p1, p0), subtract(B, p0));

		if (pA > 0 and pB > 0)	// both outside
			continue;
		if (pA < 0 and pB < 0)	// both inside
			list.push_back(B);
		else if (pA > 0)		// first inside, then outside
			list.push_back(intersection(pair(A, B), pair(p0, p1))),
			list.push_back(B);
		else  					// first outside, then inside
			list.push_back(intersection(pair(A, B), pair(p0, p1)));
	}

	final = list;
}

void myDisplay2(){
    final = poly;
        
            for (int i = 0; i < clip.size(); i++) {
                clip_polygon(clip[i], clip[(i + 1) % n_clip]);
            }
        
            myInit();
            clipping_window();
        
            // Drawing Poly
            glColor3f(0.07f, 0.59f, 0.59f);
            glBegin(GL_POLYGON);
        
            for (auto [x, y]: final)
                glVertex2f(x, y);
        
            glEnd();
}

int main(int argc, char **argv)
{

	cout << "Enter the number of points in clipping polygon (convex)\n";
	cin >> n_clip;
	clip.resize(n_clip);

	cout << "Enter the number of points in polygon to be clipped\n";
	cin >> n_poly;
	poly.resize(n_poly);

	cout << "Enter the sequence of vertices of clipping polygon (convex) in clockwise order\n";
	for (auto& [x, y]: clip)
		cin >> x >> y;

	cout << "Enter the sequence of vertices of polygon to be clipped\n";
	for (auto& [x, y]: poly)
		cin >> x >> y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("polygon_clipping");
    glutDisplayFunc(myDisplay);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Clipped polygon");
    glutDisplayFunc(myDisplay2);
    myInit();
    glutMainLoop();

    return 0;
}
