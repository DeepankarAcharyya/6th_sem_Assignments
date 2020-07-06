// command to compile:g++ DBScan.cpp -o graph -lglut -lGLU -lGL

//C program to implement DBScan and DBOutlier
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include<time.h>

#define Max 60

//=======================================Global Variables & Data-Structures===========================================
struct data_point{
    float x;
    float y;
};

struct data_nodes{
    struct data_point data;
    int cluster_id;
    int core;                            //1 if its a core ; 0 otherwise
    int visited;                         //1 if visited ; 0 otherwise
    struct data_nodes* neighbours[Max];  //pointer to the list of neighbours
    struct data_nodes* next;
    int neighbour_count;                 //total number of neighbours the current data-points has
    int visit_token;
};

struct data_nodes* head_data_list;   //pointer to the list of stored data-points
int no_of_data_points;               //variable to store the total number of data points
int cluster_id_count;                //variable to keep track of the number of clusters found
int eps;                             //the value of epsilon       -----------------------------Universal
int min_points;                      //the value of min-points    -----------------------------Universal
int no_of_core_objects;              //keep track of the total number of core objects
int token;                           //access token
float maxX,maxY;                     //to keep track of the maximum value of X and Y
 
//=====================================================Functions======================================================
//function to take the input and store it
void input(){
    FILE* in;
    in=fopen("input.txt","r");
    
    int i;
    float x,y;
    struct data_nodes* prev;
    
    //first read the first line that indicate the total number of data-points available
    fscanf(in,"%d\n",&no_of_data_points);

    //get into a loop
    for(i=0;i<no_of_data_points;i++){
        //create a new data_nodes
        struct  data_nodes* new_node=(struct  data_nodes*)malloc(sizeof(struct  data_nodes));
        //read the x and y and put it in a data_point
        fscanf(in,"%f,%f",&x,&y);
        
        new_node->data.x=x;
        new_node->data.y=y;
        
        maxX=(maxX>x)?maxX:x;
        maxY=(maxY>y)?maxY:y;
        
        //set the initial values of cluster-ids will be -1 and core will be 0
        new_node->cluster_id=-1;
        new_node->core=0;

        new_node->visited=0;
        new_node->neighbour_count=0;
        new_node->visit_token=0;
        
        //set next=Null
        new_node->next=NULL;
        //link the data-point to the prev->next
        if(i==0){
            head_data_list=new_node;
            prev=new_node;
        }
        else{
            prev->next=new_node;
            prev=new_node;
        }   
    }
}

//function to calculate the distance
float calculate_distance(float x1,float y1,float x2,float y2){
    float dis=pow((x1-x2),2);
    dis+=pow((y1-y2),2);
    return sqrt(dis);
}

//function to find the epsilon neighbourhood of a data point and sets if its a core point or not
void create_eps_neighbourhood(struct data_nodes* n01){
    //printf("\nInto the create_eps_neighbourhood() with %d and %d",n01->data.x,n01->data.y);
    
    int neighbour_count=0,i;
    struct data_nodes* head=head_data_list;
    float x,y,distance;

    while(head!=NULL){
        //get the x,y co-ordinates
        x=head->data.x;
        y=head->data.y;
        //calculate the distance-> if less than eps && skip the point if distance=0->add to the neighbours' list + increase the neighbour_count ->move to the next data node
        distance=calculate_distance(n01->data.x,n01->data.y,x,y);
    
        //printf("\nInto the for loop of create_eps with x=%d y=%d distance=%f",x,y,distance);
    
        if(distance-eps<0 && distance!=0){
            n01->neighbours[neighbour_count]=head;
            neighbour_count++;
        }
        head=head->next;
    }

    n01->neighbour_count=neighbour_count;

    //printf("\nTotal number of neighbours=%d",neighbour_count);
    
    //if neighbour_count>=min_points->set core=1
    if(neighbour_count>=min_points){
        n01->core=1;
        no_of_core_objects++;
    }
}

//function to print the data nodes
void print_data_point_list(){
    int i;
    struct data_nodes* head=head_data_list;
    printf("\nTotal Number of Data-Points: %d\n",no_of_data_points);
    printf("\nTotal Number of Core-Points: %d\n",no_of_core_objects);
    for(i=0;i<no_of_data_points;i++){
        printf("\n\nData Point No.: %d",i+1);
        printf("\nx: %f y: %f",head->data.x,head->data.y);
        printf("\nCluster-ID: %d",head->cluster_id);
        printf("\nCore Bit Value: %d",head->core);
        printf("\nVisited Bit Value: %d",head->visited);
        printf("\nNumber of Neighbours: %d",head->neighbour_count);
        head=head->next;
    }  
}

//function to assign the cluster_id to a data-node and to its neighbours
void set_cluster_id(struct data_nodes* n01,int id){
    //printf("\nEntered into the set_cluster_id()");
    int i,j,prev_id;

    //set the cluster_id of the current node
    n01->cluster_id=id;
    n01->visited=1;
    n01->visit_token=token;    
    j=n01->neighbour_count;
    struct data_nodes* head=n01;

    for(i=0;i<j;i++){
        if(n01->neighbours[i]->visit_token!=token)
            set_cluster_id(n01->neighbours[i],id);
    }
}

//function to cluster together the data_nodes which are density rechable from one-another
void density_rechable_clustering(){
    //printf("\nEntered into the density_reachable_clustering()");
    struct data_nodes* node=head_data_list;
    int i=0;
    token++;
    while(node!=NULL){
        //printf("\nEntered into the while loop with drc i=%d",i++);
        //select a core and unvisited data object
        if(node->core==1 && node->visited==0){
            //form a cluster by setting the cluster-id
            set_cluster_id(node,++cluster_id_count);
        }
        node=node->next;
    }
}

void create_neighbourhood(){
    //printf("\nEntered the create_neighbourhood()");
    struct data_nodes* node=head_data_list;
    //int i=0;
    while(node!=NULL){    
        //printf("\nInto the while loop of the create_neighbourhood() with i=%d",i++);
        create_eps_neighbourhood(node);
        node=node->next;        
    }
}

//=============================================================Plotting in a Graph================================================
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
    glutCreateWindow("Clusters of the Data-points");
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
    
    double rgb[no_of_core_objects][3];
    int i,id;

    for(i=0;i<no_of_core_objects;i++){
        r = rand() / double(RAND_MAX);
        g = rand() / double(RAND_MAX);
        b = rand() / double(RAND_MAX);
        
        rgb[i][0]=r;
        rgb[i][1]=g;
        rgb[i][2]=b;
    }    

    srand(time(0));

    struct data_nodes* head=head_data_list;

    while(head!=NULL){
        x=head->data.x;
        y=head->data.y;
        id=head->cluster_id;

        if(head->cluster_id==-1){
            glColor3f(0,0,0);
            drawPoint(x,y);
        }
        else{
            r=rgb[id][0];
            g=rgb[id][1];
            b=rgb[id][2];
            
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

//=====================================================THE MAIN FUNCTION======================================================
int main(int argc, char *argv[]){
    //STEP 0 :initializing the global variables
    eps=2;
    min_points=4;
    cluster_id_count=-1;
    no_of_core_objects=0;
    token=0;
    maxX=0;
    maxY=0;

    //STEP 1 :load the input
    input();                        
    //STEP 2 :create the epsilon neighbourhood
    create_neighbourhood();         
    //STEP 3 :start the clustering
    density_rechable_clustering();
    //STEP 4 :print the input
    print_data_point_list();      
    printf("\n");
    //STEP 5 :plotting the clusters
    showCluster(argc, argv);
    
    return 0;
}
/*
                    CHARACTERISTICS OF AN OUTLIER
            - No of neighbours=0 i.e. density unreachable
            - Visited bit =0
            - cluster-ids will still be set to -1
            - color: Black
*/
