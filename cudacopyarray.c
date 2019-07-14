#define N 31 
__global__ void kernel(int *a)
{
    // Thread indexing within Grid - note these are
    // in column major order.
    int tidx = threadIdx.x + blockIdx.x * blockDim.x;
    int tidy = threadIdx.y + blockIdx.y * blockDim.y;

    // a_ij = a[i][j], where a is in row major order
    int a_ij = a[tidy +  tidx*N];
} 

int main(void)
{
    int a[N][N], *a_device;
    const size_t a_size = sizeof(int) * size_t(N*N);
    cudaMalloc((void **)&a_device, a_size); 
    cudaMemcpy(a_device, a, a_size, cudaMemcpyHostToDevice); 
    kernel<<<N,N>>>(a_device); 
} 