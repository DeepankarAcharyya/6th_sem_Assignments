#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

__global__ void convolution(float *mat_input1, float *mat_conv_input1, float *mat_output1, int mat_dim);

__global__ void
convolution(float *mat_input1, float *mat_conv_input1, float *mat_output1, int mat_dim)
{
    // Note this has to be a 1D kernel implementation. Check host program for corresponding launch parameters. 
    
    int x1=blockIdx.x * blockDim.x + threadIdx.x;
    int y1=blockIdx.y * blockDim.y + threadIdx.y;
    int i=y1*mat_dim+x1;
    int   j = i/mat_dim;
    int   k = i%mat_dim;

    float avg_val = 0;

    for(int r=0;r<=2;r++){
          for(int c=0;c<=2;c++){
                    if((j-1+r)>=0 && (j-1+r)<mat_dim && (k-1+c)>=0 && (k-1+c)<mat_dim){
                        avg_val += (mat_input1[mat_dim*(j-1+r)+(k-1+c)]*mat_conv_input1[3*r + c]);
                    }
                }
            }
            mat_output1[mat_dim*j + k] = avg_val;
}

void print_matrix(float *A,int m,int n)
{
    for(int i =0;i<m;i++)
    {
        for(int j=0;j<n;j++)
            printf("%.2f ",A[i*n+j]);
        printf("\n");
    }

}

//------------------------------------------------------------------------------------------------------------------------------
int main(void){
    cudaError_t err = cudaSuccess;

    int i, j, k;
    int t;
    scanf("%d",&t);
    while(t--){
        int mat_dim;
        //float conv_total=0.0;
        scanf("%d",&mat_dim);
        int mat_num_eles = mat_dim*mat_dim;
        size_t mat_size = mat_num_eles*sizeof(float);
        
        float *h_mat_input1 = (float *)malloc(mat_num_eles*sizeof(float));
        float *h_mat_output1 = (float *)malloc(mat_num_eles*sizeof(float));
        float *h_mat_output2 = (float *)malloc(mat_num_eles*sizeof(float));

        int mat_conv_dim = 3;
        int mat_conv_num_eles = mat_conv_dim*mat_conv_dim;
        size_t mat_conv_size = mat_conv_num_eles*sizeof(float);
        float *h_mat_conv_input = (float *)malloc(mat_conv_num_eles*sizeof(float));

        if (h_mat_input1 == NULL || h_mat_output1 == NULL || h_mat_output2 == NULL || h_mat_conv_input == NULL){
            fprintf(stderr, "Failed to allocate host vectors!\n");
            exit(EXIT_FAILURE);
        }
//--------------------storing the elements--------------------------------
        for(i=0;i<mat_num_eles;i++){
            j = i/mat_dim;
            k = i%mat_dim;

            scanf("%f",&h_mat_input1[mat_dim*j + k]); // = (float)(rand()%10);
        }

        for(i=0;i<mat_conv_num_eles;i++)
        {
            j = i/mat_conv_dim;
            k = i%mat_conv_dim;
            h_mat_conv_input[mat_conv_dim*j + k] = 1.0/9.0;
            
        }

//------------------------------------------------------------------------
        
        //Code for allocating device buffers
        float *d_mat_input1= NULL;
        err=cudaMalloc (( void **) &d_mat_input1 , mat_size );

        float *d_mat_conv_input= NULL;
        err=cudaMalloc (( void **) &d_mat_conv_input , mat_conv_size );

        float *d_mat_output1=NULL;
        err=cudaMalloc (( void **) &d_mat_output1 , mat_size );
//------------------------------------------------------------------------
        
        //Code for copying data buffers to device
        err = cudaMemcpy (d_mat_input1 , h_mat_input1 , mat_size , cudaMemcpyHostToDevice );
        err = cudaMemcpy (d_mat_conv_input , h_mat_conv_input , mat_conv_size , cudaMemcpyHostToDevice );

//------------------------------------------------------------------------        

        //Code for launching the kernel

        // Hint we have fixed the threads per block for this problem. Note it's a 1D kernel. Design your implementation accordingly
        
        int mat_block_dim = 16;
        int mat_grid_dim = ceil(mat_num_eles/float(mat_block_dim));
        convolution<<<mat_grid_dim, mat_block_dim>>>(d_mat_input1, d_mat_conv_input, d_mat_output1, mat_dim);
       
        err = cudaGetLastError();
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to launch process_kernel2 kernel (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }

        //Code for getting back results to host
        err = cudaMemcpy (h_mat_output1 , d_mat_output1 , mat_size , cudaMemcpyDeviceToHost );
       
//-----------------------------------------------------------------------------------------------------------------
        // Do operations serially
        
        for(i=0;i<mat_num_eles;i++)
        {
            j = i/mat_dim;
            k = i%mat_dim;

            float avg_val = 0;

            for(int r=0;r<=2;r++)
            {
                for(int c=0;c<=2;c++)
                {
                    if((j-1+r)>=0 && (j-1+r)<mat_dim && (k-1+c)>=0 && (k-1+c)<mat_dim)
                    {
                        avg_val += (h_mat_input1[mat_dim*(j-1+r)+(k-1+c)]*h_mat_conv_input[3*r + c]);
                    }
                }
            }

            h_mat_output2[mat_dim*j + k] = avg_val;
        }

        // Code to Verify that the output matrices are as expected
        
      for (int i = 0; i < mat_num_eles; i++)
        {
            if (fabs(h_mat_output1[i]- h_mat_output2[i]) > 1e-5)
            {
                fprintf(stderr, "Result verification failed at element %d!\n", i);
                fprintf(stderr, "Ideal:%.2f  calculated: %.2f\n",h_mat_output2[i],h_mat_output1[i] );
                exit(EXIT_FAILURE);
            }
        }
        
        
        err = cudaFree(d_mat_input1);
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to free device vector d_mat_input1 (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
        err = cudaFree(d_mat_conv_input);
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to free device vector d_mat_conv_input (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
        err = cudaFree(d_mat_output1);
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to free device vector d_mat_output1 (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
        
        print_matrix(h_mat_output1,mat_dim,mat_dim);
        
        free(h_mat_input1);
        free(h_mat_output1);
        free(h_mat_output2);
        free(h_mat_conv_input);

        err = cudaDeviceReset();
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to deinitialize the device! error=%s\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }

        // printf("Done\n");
    }
    return 0;
}