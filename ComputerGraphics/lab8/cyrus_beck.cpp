#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<vector<float>> window(2,vector<float>());
vector<vector<float>> normal(2,vector<float>());

vector<float> t_pos,t_neg;

void add_point(float x, float y){
    window[0].push_back(x);
    window[1].push_back(y);
}

float x_0, y_0, x_1, y_1;

float x_clipped_start, y_clipped_start;
float y_clipped_end, x_clipped_end;
int case_var,n;

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
        for(int i=0; i<window[0].size(); i++){
            glVertex2f(window[0][i],window[1][i]);
        }
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
        glVertex2f(x_0, y_0);
        glVertex2f(x_1, y_1);
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

float dot_prod(float a1, float a2, float b1, float b2){
    return a1*b1 + a2*b2;
}



void cyrus_beck()
{
    float p1_p0_x = x_1-x_0;


    float p1_p0_y = y_1-y_0;

    for(int i=0; i<n; i++){

        float p_x,p_y;
        p_x = (float)(window[0][i] + window[0][(i+1)%n])/2;
        p_y = (float)(window[1][i] + window[1][(i+1)%n])/2;

        float p0_pe_x = x_0 - p_x;
        float p0_pe_y = y_0 - p_y;
        
        float dot_1 = dot_prod(normal[0][i],normal[1][i],p0_pe_x,p0_pe_y);

        float dot_2 = dot_prod(normal[0][i],normal[1][i],p1_p0_x,p1_p0_y);

        cout<<i<<" : "<<dot_1<<" "<<dot_2<<" ";
        float t = -1.0 * ((float)dot_1/dot_2);
        cout<<t<<"----";
        cout<<x_0 + t*p1_p0_x<<" ";
        cout<<y_0 + t*p1_p0_y<<endl;

        if(dot_2>0)t_pos.push_back(t);
        else if(dot_2<0)t_neg.push_back(t);
    }
    float t_start = *min_element(t_pos.begin(),t_pos.end());
    float t_end = *max_element(t_neg.begin(),t_neg.end());
    t_start = min(t_start,1.0f);
    t_end = max(t_end,0.0f);



    cout<<t_start<<endl;
    x_clipped_start = x_0 + t_start*p1_p0_x;
    y_clipped_start = y_0 + t_start*p1_p0_y;

    cout<<t_end<<endl;
    x_clipped_end = x_0 + t_end*p1_p0_x;
    y_clipped_end = y_0 + t_end*p1_p0_y;

}


int main(int argc, char **argv)
{

    cout<<"Enter no of vertex of window: \n";
    cin>>n;

    cout<<"Enter vertices of window in clockwise order:\n";
    for(int i=0; i<n; i++){
        float t1,t2;
        cin>>t1>>t2;  
        add_point(t1,t2);
    }

    cout << "Enter One Endpoint: \n";
    cin >> x_0 >> y_0;
    cout << "Enter Other Endpoint: \n";
    cin >> x_1 >> y_1;
    

    //dot product of edge vector with -k vector;
    for(int i=0; i<n; i++){
        float xi,yi;
        xi = window[0][(i+1)%n] - window[0][i];
        yi = window[1][(i+1)%n] - window[1][i];

        float normalise = sqrt(xi*xi + yi*yi);
        xi /= normalise;
        yi /= normalise;


        normal[0].push_back(-yi);
        normal[1].push_back(xi);
    }
    
    cyrus_beck();
    
    for(int i=0; i<n; i++){
        cout<<normal[0][i]<<" "<<normal[1][i]<<endl;
    }

    cout<<"Clipped ends:\n";
    cout<<x_clipped_start<<" "<<y_clipped_start<<endl;
    cout<<x_clipped_end<<" "<<y_clipped_end<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cyrus_beck");
    glutDisplayFunc(myDisplay);
    glutInitWindowPosition(500,500);
    glutCreateWindow("Clipped_line");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();

    return 0;
}
