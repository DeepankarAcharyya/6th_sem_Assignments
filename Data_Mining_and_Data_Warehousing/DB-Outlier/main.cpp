#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include<time.h>

//data structures to store the information regarding the points
struct data_point{
    float x;
    float y;
};

struct data_node{
    struct data_point data;
    int outlier;
    int neighbour_count;
    struct data_node *next;
};

//global variables
int r,n,thres;
float pi;

struct data_node *head_data_list; //pointer to the list of stored data-points
float maxX, maxY;                  //to keep track of the maximum value of X and Y

//============================================================Functions to show the results on a graph======================================================================================================================================
void showCluster(int, char **);
static void display(void);
void drawline(int);
void showPoints(void);
void drawPoint(float, float);

void showCluster(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(10, 10);
    maxX += 5;
    maxY += 5;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("DB_Outlier");
    glutDisplayFunc(display);
    glutMainLoop();
}

// Display Function to show the axes
static void display(void){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(-1, maxX, -1, maxY);
    glPointSize(3);
    drawline(1);
    drawline(0);
    showPoints();
    glFlush();
}

// Function to show the points belonging to different clusters
void showPoints(){
    float x,y;
    double r,g,b;
    
    int id;
    
    struct data_node *head = head_data_list;
	
    while(head!=NULL){
        x=head->data.x;
        y=head->data.y;
        id=head->outlier;

        if(id==1){
            glColor3f(0,0,0);
            drawPoint(x,y);
        }
        else if(id==0){
        	r = rand() / double(RAND_MAX);
    		g = rand() / double(RAND_MAX);
    		b = rand() / double(RAND_MAX);
            glColor3f(r, g, b);
            drawPoint(x,y);
        }
        head=head->next;
    }
}

// Function to draw the axes
void drawline(int x){
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    
    if (x == 1){
        glVertex2f(-1, 0);
        glVertex2f(maxX, 0);
    }
    else{
        glVertex2f(0, -1);
        glVertex2f(0, maxY);
    }
    glEnd();
}

// Function to draw the points
void drawPoint(float x, float y){
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

//=============================================================================================================================================================================================================================================

//function to take the input and store it
void input()
{
    FILE *in;
    in = fopen("input.txt", "r");

    int i;
    float x, y;
    struct data_node *prev;

    //first read the first line that indicate the total number of data-points available
    fscanf(in, "%d\n", &n);

    //get into a loop
    for (i = 0; i < n; i++)
    {
        //create a new data_nodes
        struct data_node *new_node = (struct data_node *)malloc(sizeof(struct data_node));
        //read the x and y and put it in a data_point
        fscanf(in, "%f,%f", &x, &y);
        printf("\n%f,%f",x,y);
        new_node->data.x = x;
        new_node->data.y = y;

        maxX = (maxX > x) ? maxX : x;
        maxY = (maxY > y) ? maxY : y;

        //set the initial values of the attributes will be -1
        new_node->neighbour_count=0;
        new_node->outlier=0;
        new_node->next = NULL;
        //link the data-point to the prev->next
        if (i == 0)
        {
            head_data_list = new_node;
            prev = new_node;
        }
        else
        {
            prev->next = new_node;
            prev = new_node;
        }
    }
}

//function to calculate the distance
float calculate_distance(float x1, float y1, float x2, float y2)
{
    float dis = pow((x1 - x2), 2);
    dis += pow((y1 - y2), 2);
    return sqrt(dis);
}

//function to print the data nodes
void print_data_point_list()
{
    int i;
    struct data_node *head = head_data_list;
    printf("\nTotal Number of Data-Points: %d\n", n);
    for (i = 0; i < n; i++)
    {
        printf("\n\nData Point No.: %d", i + 1);
        printf("\nx: %f y: %f", head->data.x, head->data.y);
        printf("\noutlier bit: %d", head->outlier);
        printf("\nNo. of Neighbours: %d\n\n", head->neighbour_count);
        head = head->next;
    }
}

int main(int argc, char *argv[]){
//initial values of max x and y
maxX=0;
maxY=0;

//First take the input
input();
//set the values of pi and r
pi=0.07;
r=2;
thres=floor(pi*n)+1;


//Nested Loop Method
struct data_node *loop1=head_data_list;
struct data_node *loop2;
float dis=0;

while(loop1!=NULL){
	loop2=head_data_list;
	while(loop2!=NULL){
		dis=calculate_distance(loop1->data.x,loop1->data.y,loop2->data.x,loop2->data.y);
		if (r-dis>=0){
			loop1->neighbour_count=loop1->neighbour_count+1;
		}
		loop2=loop2->next;
	}
	
	if (loop1->neighbour_count<thres){
		loop1->outlier=1;
	}	
	loop1=loop1->next;
	}

print_data_point_list();

showCluster(argc, argv);


return 0;
}

