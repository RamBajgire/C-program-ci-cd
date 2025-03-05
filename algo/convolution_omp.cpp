#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

int main(int argc, char** argv) {
    // Take width and height input from user
    size_t width = 3, height = 3;
    width = atoi (argv[2]);
    height = atoi ( argv[1]);

    printf(" width : %d, height: %d \n" , width, height); 
  
   struct timespec begin, end;
   clock_gettime(CLOCK_REALTIME, &begin);
    
    // Initialize the image vector with sequential values
    std::vector<int> image(width * height);
    for (size_t i = 0; i < width * height; ++i) {
        image[i] = i + 1; // Example initialization with sequential values
    }

    // Kernel remains the same
    const std::vector<int> kernel = {
        1, 0, -1,
        2, 0, -2,
        1, 0, -1
    };

    // Initialize the result vector
    std::vector<int> result(width * height, 0);

//    struct timespec begin, end;
//    clock_gettime(CLOCK_REALTIME, &begin);
    
   #pragma omp parallel for collapse(2)
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < height; ++x) {
            int sum = 0;
            for (int kx = -1; kx <= 1; ++kx) {
                for (int ky = -1; ky <= 1; ++ky) {
                    int imageX = y + kx;
                    int imageY = x + ky;
                    if (imageX >= 0 && imageX < width && imageY >= 0 && imageY < height) {
                        sum += image[imageX * width + imageY] * kernel[(kx + 1) * 3 + ky + 1];
                    }
                }
            }
            result[y * width + x] = sum;
        }
    }
    
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;
    printf("Time measured: %lf sec\n", elapsed);
  
/*    std::cout << "Convolution Result:" << std::endl;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            std::cout << result[i * width + j] << " ";
        }
        std::cout << std::endl;
    }
*/
    return 0;
}
