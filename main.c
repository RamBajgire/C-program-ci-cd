 // main.c
#include <stdio.h>

int calculate_sum(int a, int b) {
    return a + b;
}

int main() {
    int num1, num2, result;

    // Prompt user for input
 //ram
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Calculate sum
    result = calculate_sum(num1, num2);

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
