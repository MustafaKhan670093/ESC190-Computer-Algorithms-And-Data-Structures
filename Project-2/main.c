#include "seamcarving.h"

#include <stdio.h>

typedef struct rgb_img image_t;


int main(int argc, char* argv[])
{
    image_t *im, *grad;

    read_in_img(&im, "HJoceanSmall.bin");
    calc_energy(im,  &grad);
    
    // print_grad(grad);

   
    double *best;
    dynamic_seam(grad, &best);

    size_t i=0,j;
    for(;i<5;++i)
    {
        j=0;
        for(;j<6;++j)
        {
            printf("%.0lf ", best[i*6+j]);
        }
        printf("\n");
    }
    
    int *path;
    recover_path(best, 5, 6, &path);
    for (i=0;i<5;++i)
        printf("%d ", path[i]);
    printf("\n");

    //answer to recover_path by passing in 6x5.png should be: [3, 4, 3, 2, 2]
    
    destroy_image(im);
    destroy_image(grad);
    free(best);
    free(path);
}