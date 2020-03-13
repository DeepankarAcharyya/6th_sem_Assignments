%%cuda --name week4_Programming_Assignment_b.cu
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

void print_matrix(float *A, int N,int M){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            printf("%.2f ",A[i*N+j]);}
        printf("\n");
    }
}

__global__ void
swap_it(float *A,int M,int N){
    //swapping the even and odd positions

    //calculate the index
    int i=threadIdx.z*(blockDim.x* blockDim.y)+threadIdx.y*blockDim.x+threadIdx.x;

    if(i<M*N){
        if(i%2==1){
            int temp;
            temp=A[i];
            A[i]=A[i-1];
            A[i-1]=temp;
        }

        __syncthreads();
    }
}

__global__ void
diagonal_swap(float *A,int M,int N){
    //taking the transpose
    int i=blockIdx.y*blockDim.y+threadIdx.y;
    int j=blockIdx.x*blockDim.x+threadIdx.x;
    int t=i*N+j;
    int k=j*M+i;
    
    if(i<M && j<N){   
        if(i<j){
          float temp=A[t];
          A[t]=A[k];
          A[k]=temp;
        }
    }
}

int main(void){

    cudaError_t err = cudaSuccess;

    int t;
    scanf("%d",&t);
    
    while(t--){
        int m,n;
        scanf("%d %d",&m,&n);
        size_t size = m*n * sizeof(float);

        float *h_A=(float *)malloc(size);
        
        // Verify that allocations succeeded
        if (h_A == NULL){
            fprintf(stderr, "Failed to allocate host vectors!\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n*m; ++i){
            scanf("%f",&h_A[i]);
        }
        
        // Allocate the device input vector A
        float *d_A = NULL;
        err=cudaMalloc (( void **) &d_A , size );

        // Copy the host input vectors A and B in host memory to the device input vectors in device memory
        err = cudaMemcpy (d_A , h_A , size , cudaMemcpyHostToDevice );
        
        swap_it<<<1, dim3(512,2,1)>>>(d_A, m, n);
        err = cudaGetLastError();

        if (err != cudaSuccess){
            fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
        err = cudaMemcpy (h_A , d_A , size , cudaMemcpyDeviceToHost );
//--------------------------------------------------------------------------------------------------------------------------------------
//         print_matrix(h_A,m,n);
//         printf("\n----------------------------\n");
//--------------------------------------------------------------------------------------------------------------------------------------
        diagonal_swap<<<1, dim3(m,n)>>>(d_A, m, n);
        err = cudaGetLastError();

        if (err != cudaSuccess){
            fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
        // Copy the device result vector in device memory to the host result vector in host memory.
        err = cudaMemcpy (h_A , d_A , size , cudaMemcpyDeviceToHost );
//--------------------------------------------------------------------------------------------------------------------------------------
         print_matrix(h_A,m,n);
        
        // Free memory
        cudaFree(d_A);
        free(h_A);

        err = cudaDeviceReset();

        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to deinitialize the device! error=%s\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}