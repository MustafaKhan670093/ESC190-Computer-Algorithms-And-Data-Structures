#include "c_img.h"
#include <stdio.h>

typedef struct rgb_img img_t;

__global__ void brighten(float adj_factor, int height, int width, uint8_t* in, uint8_t* out)
{
    // threadIdx thread number (0-M)
    // blockDim is how many threads per block
    // blockIdx is block number (0-N)
    int index = threadIdx.x + blockDim.x * blockIdx.x; 

    if (index < height*width*3)
    {
        out[index] = ((float)in[index] * adj_factor) > 256.0f ? 
                        (uint8_t)255 : (uint8_t)((float)in[index] * adj_factor);
    }
}

int main(int argc, char* argv[])
{
    img_t *im, *out50, *out10, *out200, *out400, *out120;
    read_in_img(&im, "UofTPresidentMericGertler-smaller.bin");


    // create the images
    create_img(&out50, im->height, im->width);
    create_img(&out10, im->height, im->width);
    create_img(&out200, im->height, im->width);
    create_img(&out400, im->height, im->width);
    create_img(&out120, im->height, im->width);


    uint8_t *d_raster, *d_out50, *d_out10, *d_out200, *d_out400, *d_out120;
    // allocate memory 
    cudaMalloc((void**)&d_raster, sizeof(uint8_t)*im->width*im->height*3);
    cudaMalloc((void**)&d_out10, sizeof(uint8_t)*im->width*im->height*3);
    cudaMalloc((void**)&d_out50, sizeof(uint8_t)*im->width*im->height*3);
    cudaMalloc((void**)&d_out400, sizeof(uint8_t)*im->width*im->height*3);
    cudaMalloc((void**)&d_out200, sizeof(uint8_t)*im->width*im->height*3);
    cudaMalloc((void**)&d_out120, sizeof(uint8_t)*im->width*im->height*3);
    


    cudaMemcpy(d_raster, im->raster, sizeof(uint8_t)*im->width*im->height*3, cudaMemcpyHostToDevice);

    brighten <<<(im->height*im->width*3 + 1023)/1024,1024>>> (0.1f, im->height, im->width, d_raster, d_out10);
    brighten <<<(im->height*im->width*3 + 1023)/1024,1024>>> (4.0f, im->height, im->width, d_raster, d_out400);
    brighten <<<(im->height*im->width*3 + 1023)/1024,1024>>> (2.0f, im->height, im->width, d_raster, d_out200);
    brighten <<<(im->height*im->width*3 + 1023)/1024,1024>>> (1.2f, im->height, im->width, d_raster, d_out120);
    brighten <<<(im->height*im->width*3 + 1023)/1024,1024>>> (0.5f, im->height, im->width, d_raster, d_out50);

    //Blocks have threads. First number above is how many blocks you want to launch, second is number of threads
    // [012345]  [012345]  [012345]

    cudaMemcpy(out10->raster, d_out10, sizeof(uint8_t)*im->width*im->height*3, cudaMemcpyDeviceToHost);
    cudaMemcpy(out50->raster, d_out50, sizeof(uint8_t)*im->width*im->height*3, cudaMemcpyDeviceToHost);
    cudaMemcpy(out400->raster, d_out400, sizeof(uint8_t)*im->width*im->height*3, cudaMemcpyDeviceToHost);
    cudaMemcpy(out200->raster, d_out200, sizeof(uint8_t)*im->width*im->height*3, cudaMemcpyDeviceToHost);
    cudaMemcpy(out120->raster, d_out120, sizeof(uint8_t)*im->width*im->height*3, cudaMemcpyDeviceToHost);
    
    cudaFree(d_raster);
    cudaFree(d_out10);
    cudaFree(d_out120);
    cudaFree(d_out200);
    cudaFree(d_out400);
    cudaFree(d_out50);

    write_img(out10, "Level0.1.bin");
    write_img(out50, "Level0.5.bin");
    write_img(out120, "Level1.2.bin");
    write_img(out400, "Level4.0.bin");
    write_img(out200, "Level2.0.bin");

    destroy_image(im);
    destroy_image(out10);
    destroy_image(out50);
    destroy_image(out120);
    destroy_image(out200);
    destroy_image(out400);
}