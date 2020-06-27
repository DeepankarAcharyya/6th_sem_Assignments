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
    int strip;
};

//global variables
int pi,r,n;
int b1_count=0;
int b2_count=0;
int c_count=0;

struct data_nodes *head_data_list; //pointer to the list of stored data-points
float maxX, maxY;                  //to keep track of the maximum value of X and Y

//function to take the input and store it
void input()
{
    FILE *in;
    in = fopen("input.txt", "r");

    int i;
    float x, y;
    struct data_nodes *prev;

    //first read the first line that indicate the total number of data-points available
    fscanf(in, "%d\n", &n);

    //get into a loop
    for (i = 0; i < n; i++)
    {
        //create a new data_nodes
        struct data_nodes *new_node = (struct data_nodes *)malloc(sizeof(struct data_nodes));
        //read the x and y and put it in a data_point
        fscanf(in, "%f,%f", &x, &y);

        new_node->data.x = x;
        new_node->data.y = y;

        maxX = (maxX > x) ? maxX : x;
        maxY = (maxY > y) ? maxY : y;

        //set the initial values of the attributes will be -1
        new_node->outlier=-1;
        new_node->strip=-1;
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
    struct data_nodes *head = head_data_list;
    printf("\nTotal Number of Data-Points: %d\n", n);
    for (i = 0; i < n; i++)
    {
        printf("\n\nData Point No.: %d", i + 1);
        printf("\nx: %f y: %f", head->data.x, head->data.y);
        printf("\noutlier bit: %d", head->outlier);
        printf("\nstrip: %d", head->strip);
        head = head->next;
    }
}
