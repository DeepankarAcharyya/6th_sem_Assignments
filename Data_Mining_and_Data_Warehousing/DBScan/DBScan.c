//C program to implement DBScan
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Max 30

//=======================================Global Variables & Data-Structures===========================================
struct data_point{
    int x;
    int y;
};

struct data_nodes{
    struct data_point data;
    int cluster_id;
    int core;                            //1 if its a core ; 0 otherwise
    int visited;                         //1 if visited ; 0 otherwise
    struct data_nodes* neighbours[Max];  //pointer to the list of neighbours
    struct data_nodes* next;
};

struct data_nodes* head_data_list; //pointer to the list of stored data-points
int no_of_data_points;             //variable to store the total number of data points
int cluster_id_count;              //variable to keep track of the number of clusters found
int eps;                           //the value of epsilon       -----------------------------Universal
int min_points;                    //the value of min-points    -----------------------------Universal

//=====================================================Functions======================================================
//function to take the input and store it
void input(){
    FILE* in;
    in=fopen("input.txt","r");
    
    int i,x,y;
    struct data_nodes* prev;
    
    //first read the first line that indicate the total number of data-points available
    fscanf(in,"%d\n",&no_of_data_points);

    //get into a loop
    for(i=0;i<no_of_data_points;i++){
        //create a new data_nodes
        struct  data_nodes* new_node=(struct  data_nodes*)malloc(sizeof(struct  data_nodes));
        //read the x and y and put it in a data_point
        fscanf(in,"%d,%d",&x,&y);
        new_node->data.x=x;
        new_node->data.y=y;
        //set the initial values of cluster-ids will be -1 and core will be 0
        new_node->cluster_id=-1;
        new_node->core=0;
        new_node->visited=0;
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
float calculate_distance(int x1,int y1,int x2,int y2){
    float dis=pow((x1-x2),2);
    dis+=pow((y1-y2),2);
    return sqrt(dis);
}

//function to find the epsilon neighbourhood of a data point and returns if its a core point or not
int create_eps_neighbourhood(struct data_nodes n01){
    
    int neighbour_count=0;
    struct data_nodes* head=head_data_list;
    int x,y,i,distance;

    for(i=0;i<no_of_data_points;i++){
        //get the x,y co-ordinates
        x=head->data.x;
        y=head->data.y;
        //calculate the distance-> if less than eps && skip the point if distance=0->add to the neighbours' list + increase the neighbour_count ->move to the next data node
        distance=calculate_distance(n01.data.x,n01.data.y,x,y);
        if(distance-eps<0 && distance!=0){
            n01.neighbours[neighbour_count]=head;
            neighbour_count++;
        }
        head=head->next;
    }
    //if neighbour_count>=min_points->set core=1
    if(neighbour_count>=min_points)
        n01.core=1;

}

void print_data_point_list(){
    int i;
    struct data_nodes* head=head_data_list;
    printf("\nTotal Number of Data-Points: %d\n",no_of_data_points);
    for(i=0;i<no_of_data_points;i++){
        printf("\n\nData Point No.: %d",i+1);
        printf("\nx: %d y: %d",head->data.x,head->data.y);
        printf("\nCluster-ID: %d",head->cluster_id);
        printf("\nCore Bit Value: %d",head->core);
        printf("\nVisited Bit Value: %d",head->visited);
        head=head->next;
    }  
}

void density_rechable_clustering(){

}

//=====================================================THE MAIN FUNCTION======================================================
int main(){
    eps=1;
    min_points=5;
    
    //take the input
    input();
    //print the input
    print_data_point_list();

    //the data-points with cluster-id=-1 will be the outliers

    return 0;
}
