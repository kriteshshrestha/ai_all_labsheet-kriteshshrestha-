#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define DATA_SIZE 20
#define K 3 

typedef struct {
    int age;
    int income;
    char jeans_type[20];
} Person;

typedef struct {
    float distance;
    char jeans_type[20];
} Neighbor;

// Sample datasets
Person dataset[DATA_SIZE] = {
    {18, 10000, "Skinny"},
    {21, 15000, "Skinny"},
    {25, 20000, "Regular"},
    {28, 22000, "Regular"},
    {30, 25000, "Bootcut"},
    {35, 27000, "Bootcut"},
    {40, 30000, "Relaxed"},
    {45, 35000, "Relaxed"},
    {50, 40000, "Loose"},
    {55, 45000, "Loose"},
    {22, 12000, "Skinny"},
    {24, 18000, "Regular"},
    {32, 24000, "Bootcut"},
    {38, 28000, "Relaxed"},
    {42, 33000, "Relaxed"},
    {48, 37000, "Loose"},
    {27, 21000, "Regular"},
    {36, 26000, "Bootcut"},
    {44, 34000, "Relaxed"},
    {52, 42000, "Loose"}
};


float compute_distance(int age1, int income1, int age2, int income2) {
    return sqrt(pow(age1 - age2, 2) + pow(income1 - income2, 2));
}


void sort_neighbors(Neighbor neighbors[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (neighbors[j].distance > neighbors[j + 1].distance) {
                Neighbor temp = neighbors[j];
                neighbors[j] = neighbors[j + 1];
                neighbors[j + 1] = temp;
            }
        }
    }
}


void predict_jeans_type(Neighbor neighbors[], int k, char* predicted_type) {
    int max_count = 0;
    for (int i = 0; i < k; i++) {
        int count = 1;
        for (int j = i + 1; j < k; j++) {
            if (strcmp(neighbors[i].jeans_type, neighbors[j].jeans_type) == 0)
                count++;
        }
        if (count > max_count) {
            max_count = count;
            strcpy(predicted_type, neighbors[i].jeans_type);
        }
    }
}

int main() {
    int input_age, input_income;
    printf("Enter age: ");
    scanf("%d", &input_age);
    printf("Enter monthly income (NPR): ");
    scanf("%d", &input_income);

    Neighbor neighbors[DATA_SIZE];


    for (int i = 0; i < DATA_SIZE; i++) {
        neighbors[i].distance = compute_distance(input_age, input_income, dataset[i].age, dataset[i].income);
        strcpy(neighbors[i].jeans_type, dataset[i].jeans_type);
    }

  
    sort_neighbors(neighbors, DATA_SIZE);

   
    char predicted[20];
    predict_jeans_type(neighbors, K, predicted);

    printf("\nPredicted jeans type: %s\n", predicted);
    return 0;
}
