#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
        //printf("\n%f,%f",x,y);
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

printf("\nOutlier Bits set to 1 for the outliers.\n");

print_data_point_list();

return 0;
}
