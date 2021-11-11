/*
Seam-carving is a content-aware image resizing technique where the image is reduced in size by one pixel of width (or height) at a time. A vertical seam in an image is a path of pixels connected from the top to the bottom with one pixel in each row; a horizontal seam is a path of pixels connected from the left to the right with one pixel in each column. Below left is the original 505-by-287 pixel image; below right is the result after removing 150 vertical seams, resulting in a 30% narrower image. Unlike standard content-agnostic resizing techniques (such as cropping and scaling), seam carving preserves the most interest features (aspect ratio, set of objects present, etc.) of the image. Although the underlying algorithm is simple and elegant, it was not discovered until 2007. Now, it is now a core feature in Adobe Photoshop and other computer graphics applications.

In this assignment, you will create a data type that resizes a H-by-W image using the seam-carving technique.You will first compute the dual-gradient energy function, and then find vertical “seams” – paths from the top to the bottom of the image – such that the sum of the dual-gradient energy values in the pixels along the path is as small as possible
*/


// Notation. In image processing, pixel (y, x) refers to the pixel in column x and row y, with pixel (0,0) at the upper-left corner and pixel (H-1, W-1) at the lower-right corner: 

#include "seamcarving.h"

// Energy calculation. The first step is to calculate the energy of a pixel, which is a measure of its perceptual importance – the higher the energy, the less likely that the pixel will be included as part of a seam (as you will see in the next step). In this project, you will use the dual-gradient energy function, which is described below. Here is the dual-gradient energy function of the surfing image above: 
// The energy is high (white) for pixels in the image where there is a rapid color gradient (such as the boundary between the sea and sky and the boundary between the surfing Josh Hug (the original author of this assignment) on the left and the ocean behind him). The seam carving technique avoids removing such high-energy pixels.

// Seam identification. The next step is to find a vertical seam of minimum total energy. The seam is a path through pixels from top to bottom such that the sum of the energies of the pixels is minimal. You will identify the minimum-energy seam using dynamic programming.

// Seam removal. The final step is removing from the image all the pixels along the vertical seam.

#define DEBUG

#define INDEX(i,j) (i)*width+(j)
#define SQ(i) (i)*(i)

// pixel value 
#define RED 0
#define GREEN 1
#define BLUE 2

#define WRAP(i,limit) (i) == -1 ? (limit-1) : ((i) == limit ? 0 : i)

#define INF (double) 0x7fffffff

#include <assert.h> // assert
#include <math.h> // sqrt

typedef struct rgb_img img_t;


/* The function will compute the dual-gradient energy function, and place it in the struct rgb_img *grad. */
void calc_energy(img_t *im, img_t **grad)
{
    create_img(grad, im->height, im->width);

    size_t width, height;
    width = im->width;
    height = im->height;

    size_t i, j;
    
    double energy_square; // dummy to store intermediate calculation
    size_t i_, j_, _i, _j; // dummys for storing adjacent pixel
    uint8_t energy;

    for (i=0;i<width;++i)
    {
        for (j=0;j<height;++j)
        {
            energy_square = 0.0; // zero the energy

            //initializing wrap transform on indexes
            j_ = WRAP(j+1, height);
            _j = WRAP(j-1, height);
            i_ = WRAP(i+1, width);
            _i = WRAP(i-1, width);

            // calculate the Ry, Gy, By
            energy_square += SQ(get_pixel(im, j_, i, RED) - get_pixel(im, _j, i, RED));
            energy_square += SQ(get_pixel(im, j_, i, GREEN) - get_pixel(im, _j, i, GREEN));
            energy_square += SQ(get_pixel(im, j_, i, BLUE) - get_pixel(im, _j, i, BLUE));
            
            // calculate the Rx, Gx, Bx
            energy_square += SQ(get_pixel(im, j, i_, RED) - get_pixel(im, j, _i, RED));
            energy_square += SQ(get_pixel(im, j, i_, GREEN) - get_pixel(im, j, _i, GREEN));
            energy_square += SQ(get_pixel(im, j, i_, BLUE) - get_pixel(im, j, _i, BLUE));
            
            energy = (uint8_t)(sqrt(energy_square) / 10.0);

            set_pixel(*grad, j, i, energy, energy, energy);
        }
    }
}

/* Define the function dynamic_seam(struct rgb_img *grad, double **best_arr) which allocates and computes the dunamic array *best_arr */
void dynamic_seam(img_t *grad, double **best_arr)
{
    *best_arr = (double*)calloc(grad->height*grad->width,sizeof(double));
    assert(*best_arr);
    // do the base problem 
    // y is j

    // set the top row
    for (size_t j = 0; j < grad->width; ++j)
        (*best_arr)[j] = get_pixel(grad, 0, j, RED);
    

    double dummy;

    for (size_t i = 0; i+1 < grad->height; ++i)
    {
        for (size_t j = 0; j < grad->width; ++j)
        {
            // compute min
            dummy = (*best_arr)[i*grad->width + j];

            if (j > 0 && dummy > (*best_arr)[i*grad->width + j-1])
                dummy = (*best_arr)[i*grad->width + j-1];
            if (j + 1 < grad->width && dummy > (*best_arr)[i*grad->width + j+1])
                dummy = (*best_arr)[i*grad->width + j+1];
            
            // now dummy is the min value
            (*best_arr)[(i+1)*grad->width + j] = dummy + (double)get_pixel(grad, i+1, j, RED);
        }
    }
}

void recover_path(double *best, int height, int width, int **path)
{
    *path = (int*)calloc(height,sizeof(int));
    assert(*path);

    // find min on the bottom row (i.e total weight)
    double dummy = best[(height-1)*width];
    int dummy_index = 0, _dummy_index;
    for (int j = 1; j < width; ++j)
    {
        if(dummy > best[(height-1)*width+j])
        {
            dummy = best[(height-1)*width+j];
            dummy_index = j;
        }
    }
    (*path)[height-1] = dummy_index; 

    int i = height - 2; // we are starting at the 2nd row to the bottom height-2
    for (;i>=0;--i)
    {
        dummy = best[i*width+dummy_index]; // this one is directly above the previous one
        _dummy_index = dummy_index;
        if (dummy_index > 0 && dummy > best[i*width+dummy_index-1]) // left
        {
            dummy = best[i*width+dummy_index-1];
            _dummy_index = dummy_index - 1;
        }
        if (dummy_index + 1 < width && dummy > best[i*width+dummy_index+1])
        {
            dummy = best[i*width+dummy_index+1];
            _dummy_index = dummy_index + 1;
        }
        dummy_index = _dummy_index;

        (*path)[i] = dummy_index;
    }
}

void remove_seam(img_t *src, img_t **dest, int* path)
{
    create_img(dest, src->height, src->width - 1);
    int dummy; // if you are on the left of the seam, then 0. if you are on the right, then 1
    for(int i=0; i<src->height; ++i)
    {
        dummy = 0;
        for(int j=0; j<src->width; ++j)
        {
            if(j == path[i])
                dummy = 1;
            else 
                set_pixel(*dest, i, j-dummy, get_pixel(src, i, j, RED), get_pixel(src, i, j, GREEN), get_pixel(src, i, j, BLUE));
        }
    }    
}

/*
for i in range(len(row)):
    for j in row[i]:
        if row[i] 

/*
***-****
***-****
****-***
*/
