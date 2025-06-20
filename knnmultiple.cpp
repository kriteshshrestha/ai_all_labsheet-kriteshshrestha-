#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define DATA_SIZE 10
#define K 3
#define MAX_LABEL 20

typedef struct {
    int age;
    int income;
    int height_cm;
    int weight;
    char jeans_type[MAX_LABEL];
} Person;

typedef struct {
    double distance;
    char jeans_type[MAX_LABEL];
} Neighbor;

// Sample dataset
Person dataset[DATA_SIZE] = {
    {18, 10000, 165, 55, "Skinny"},
    {25, 15000, 170, 60, "Skinny"},
    {30, 22000, 175, 70, "Regular"},
    {35, 25000, 178, 75, "Regular"},
    {40, 28000, 180, 80, "Bootcut"},
    {45, 32000, 175, 85, "Bootcut"},
    {50, 36000, 170, 90, "Relaxed"},
    {55, 40000, 165, 95, "Relaxed"},
    {60, 42000, 160, 100, "Loose"},
    {65, 45000, 158, 105, "Loose"}
};

// Feature scaling constants
double min_age = 18, max_age = 65;
double min_income = 10000, max_income = 45000;
double min_height = 158, max_height = 180;
double min_weight = 55, max_weight = 105;

double compute_distance(Person a, Person b) {
    double norm_age    = (a.age    - b.age)    / (max_age    - min_age);
    double norm_income = (a.income - b.income) / (max_income - min_income);
    double norm_height = (a.height_cm - b.height_cm) / (max_height - min_height);
    double norm_weight = (a.weight - b.weight) / (max_weight - min_weight);

    return sqrt(norm_age * norm_age +
                norm_income * norm_income +
                norm_height * norm_height +
                norm_weight * norm_weight);
}

int cmp_neighbors(const void *a, const void *b) {
    double d1 = ((Neighbor*)a)->distance;
    double d2 = ((Neighbor*)b)->distance;
    return (d1 > d2) - (d1 < d2);
}

void predict_jeans_type(Neighbor neighbors[], char *result) {
    int skinny = 0, regular = 0, bootcut = 0, relaxed = 0, loose = 0;

    for (int i = 0; i < K; i++) {
        if      (strcmp(neighbors[i].jeans_type, "Skinny")  == 0) ++skinny;
        else if (strcmp(neighbors[i].jeans_type, "Regular") == 0) ++regular;
        else if (strcmp(neighbors[i].jeans_type, "Bootcut") == 0) ++bootcut;
        else if (strcmp(neighbors[i].jeans_type, "Relaxed") == 0) ++relaxed;
        else if (strcmp(neighbors[i].jeans_type, "Loose")   == 0) ++loose;
    }

    int max = skinny;
    strcpy(result, "Skinny");
    if (regular > max) { max = regular; strcpy(result, "Regular"); }
    if (bootcut > max) { max = bootcut; strcpy(result, "Bootcut"); }
    if (relaxed > max) { max = relaxed; strcpy(result, "Relaxed"); }
    if (loose   > max) {                 strcpy(result, "Loose");   }
}

int main() {
    Person input;
    int feet, inches;

    printf("Enter your age: ");
    scanf("%d", &input.age);

    printf("Enter your monthly income (NPR): ");
    scanf("%d", &input.income);

    printf("Enter your height (feet inches): ");
    scanf("%d %d", &feet, &inches);
    input.height_cm = (feet * 30.48) + (inches * 2.54);

    printf("Enter your weight (kg): ");
    scanf("%d", &input.weight);

    // Distance calculation
    Neighbor neighbors[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        neighbors[i].distance = compute_distance(input, dataset[i]);
        strcpy(neighbors[i].jeans_type, dataset[i].jeans_type);
    }

    // Sort neighbors by distance
    qsort(neighbors, DATA_SIZE, sizeof(Neighbor), cmp_neighbors);

    // Predict jeans type
    char predicted[MAX_LABEL];
    predict_jeans_type(neighbors, predicted);

    printf("\nPredicted jeans type: %s\n", predicted);
    return 0;
}

