// main.c
#include <stdio.h>

int calculate_sum(int a, int b) {
    return a + b;
}

int main() {
    int result = calculate_sum(5, 7);
    
    // Save result to a file
    FILE *file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "%d\n", result);
    fclose(file);
    
    printf("Result calculated and saved to result.txt\n");
    return 0;
}
