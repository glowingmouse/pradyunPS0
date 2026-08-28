#include <stdio.h>

int total(int array[], int n);
int max(int array[], int n);
int min(int array[], int n);

int main(void)
{
    int C, N;

    printf("Enter capacity: ");
    scanf("%i", &C);

    printf("Number of containers: ");
    scanf("%i", &N);

    int weights[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%i", &weights[i]);
    }

    int sum = total(weights, N);

    int class = 0;

    if (sum >= 200)
    {
        class = 1;
    }

    printf("Total Shipment Weight: %i\n", sum);
    printf("Average Container Weight: %i\n", sum / N);
    printf("Heaviest Container: %i\n", max(weights, N));
    printf("Lightest Container: %i\n", min(weights, N));
    if (class == 1)
    {
        printf("Classification: Heavy\n");
    }
    else
    {
        printf("Classification: Light\n");
    }
    printf("Port Capacity: %i\n", C);
    if (sum <= C)
    {
        printf("Status: Shipment can be unloaded\n");
    }
    else
    {
        printf("Status: Shipment exceeds port capacity\n");
    }
}

int total(int array[], int n)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        k += array[i];
    }
    return k;
}

int max(int array[], int n)
{
    int dummy = 0;
    
    for (int i = 0; i < n; i++)
    {
        if (array[i] > dummy)
        {
            dummy = array[i];
        }
    }
    
    return dummy;
}
int min(int array[], int n)
{
    int dummy = array[0];
    
    for (int i = 0; i < n; i++)
    {
        if (array[i] < dummy)
        {
            dummy = array[i];
        }
    }
    
    return dummy;
}
