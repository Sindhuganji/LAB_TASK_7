#include <stdio.h>
void sort_by_ratio(int weights[], int profits[], int indices[], int n) {
    int i, j, temp_idx, temp_p, temp_w;
    double ratio[100], temp_r;
    for (i = 0; i < n; i++) {
        ratio[i] = (double)profits[i] / weights[i];
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (ratio[j] > ratio[i]) {
                
                temp_r = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp_r;

                temp_p = profits[i];
                profits[i] = profits[j];
                profits[j] = temp_p;

                temp_w = weights[i];
                weights[i] = weights[j];
                weights[j] = temp_w;

                temp_idx = indices[i];
                indices[i] = indices[j];
                indices[j] = temp_idx;
            }
        }
    }
}

double fractional_knapsack(int n, int weights[], int profits[], int capacity, double solution[]) {
    int indices[100], i, current_weight = 0;
    double total_profit = 0.0;

    for (i = 0; i < n; i++) {
        indices[i] = i;
        solution[i] = 0.0;
    }

    sort_by_ratio(weights, profits, indices, n);

    double temp_solution[100];
    for (i = 0; i < n; i++) {
        if (current_weight + weights[i] <= capacity) {
            temp_solution[i] = 1.0;   // take full item
            current_weight += weights[i];
            total_profit += profits[i];
        } else {
            temp_solution[i] = (double)(capacity - current_weight) / weights[i]; // fraction
            total_profit += profits[i] * temp_solution[i];
            current_weight = capacity;
            i++;
            while (i < n) {
                temp_solution[i] = 0.0;
                i++;
            }
            break;
        }
    }

    for (i = 0; i < n; i++) {
        solution[indices[i]] = temp_solution[i];
    }
    return total_profit;
}

int main() {
    int M, n, i;
    printf("Enter Maximum Capacity of Bag: ");
    scanf("%d", &M);
    printf("Enter Number of Items: ");
    scanf("%d", &n);

    int profits[100], weights[100];
    double Solution[100];

    for (i = 0; i < n; i++) {
        printf("Enter Weight of Item %d: ", i + 1);
        scanf("%d", &weights[i]);
        printf("Enter Profit of Item %d: ", i + 1);
        scanf("%d", &profits[i]);
    }

    double max_profit = fractional_knapsack(n, weights, profits, M, Solution);

    printf("Fractions of items taken:\n");
    for (i = 0; i < n; i++) {
        printf("%.2f ", Solution[i]);
    }
    printf("\nMaximum Profit: %.2f\n", max_profit);

    return 0;
}