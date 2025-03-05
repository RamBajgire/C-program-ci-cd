#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <time.h>

int main(int argc, char** argv) {
    // Take width and height input from user
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <height> <width>\n";
        return 1;
    }

    size_t height = atoi(argv[1]);
    size_t width = atoi(argv[2]);

    std::cout << "Width: " << width << ", Height: " << height << std::endl;

    // Initialize the image vector with sequential values
    std::vector<int> image(width * height);
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < width * height; ++i) {
        image[i] = i + 1;
    }

    // Sobel Kernel
    const std::vector<int> kernel = {
        1, 0, -1,
        2, 0, -2,
        1, 0, -1
    };

    // Initialize result vector
    std::vector<int> result(width * height, 0);

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    // OpenMP optimized parallel loop
    #pragma omp parallel
    {
        std::vector<int> local_result(width * height, 0);  // Per-thread local buffer

        #pragma omp for schedule(static)
        for (int x = 1; x < height - 1; ++x) {
            for (int y = 1; y < width - 1; ++y) {
                int sum = 0;
                for (int kx = -1; kx <= 1; ++kx) {
                    for (int ky = -1; ky <= 1; ++ky) {
                        int imageX = x + kx;
                        int imageY = y + ky;
                        sum += image[imageX * width + imageY] * kernel[(kx + 1) * 3 + ky + 1];
                    }
                }
                local_result[x * width + y] = sum;
            }
        }

        // Reduce local buffers into global `result`
        #pragma omp critical
        for (int i = 0; i < width * height; ++i) {
            result[i] += local_result[i];
        }
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double elapsed = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) * 1e-9;
    
    std::cout << "Time measured: " << elapsed << " sec" << std::endl;

    return 0;
}

