#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int A[], int n);
void countSort(int A[], int n);
void printArray(int A[], int n);
void generateInFile(int n);

int main()
{
    int n = 100000;
    size_t read;
    int num;

    //1. Call generateInFile function to generate integer random numbers and store them in a text file
    generateInFile(n);
    
    //2. Copy the numbers from the file to an array A1 and another array A2 (A1=A2). Use dynamic allocation to declare A1 and A2
    int* A;
    A = (int *)malloc(n * sizeof(int));

    // open the file
    FILE *input = fopen("A1.txt", "r");

    // read the size of the input
    fscanf(input, "%zu", &read);

    // read the random numbers
    for (size_t i = 0; i < n; i++) {
        fscanf(input, "%d", &A[i]);
    }
    // close the input file
    fclose(input);

    // copy A to B
    int* B;
    B = (int *)malloc(n * sizeof(int));
    B = A;
    
    //3. Define two variables start1 and end1 of type clock_t.
    clock_t selectStart;
    clock_t selectStop;

    //4. Keep the following code to measure the running time of the selection sort algorithm.
    selectStart = clock();
    selectionSort(A, n);
    selectStop = clock();
    double time_spent1 = (double)(selectStop - selectStart) / CLOCKS_PER_SEC;
    printf("Time taken by selectionSort algorithm is %f sec.\n",time_spent1);
    printf("\n");

    //5. repeat steps 3. and 4. to measure the running time of the counting sort algorithm
    // Step 3.
    clock_t countStart;
    clock_t countStop;

    // Step 4.
    countStart = clock();
    countSort(B, n);
    countStop = clock();
    double time_spent2 = (double)(countStop - countStart) / CLOCKS_PER_SEC;
    printf("Time taken by countSort algorithm if %f sec.\n", time_spent2);
    
    return 0;
}

//selection sort function
void selectionSort(int A[], int n) // n is the size of A
{
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
            if (min != i) {
                int hold = A[i];
                A[i] = A[min];
                A[min] = hold;
            }
        }
    }
}

//counting sort function
void countSort(int A[], int n) // n is the size of A
{
    int k, *B, *C;
    //Write a code to find the value of k that is equal to the maximum value of A
    k = A[0];
    for (int i = 1; i < n; i++) {
        if (k < A[i]) {
            k = A[i];
        }
    }

    B = (int*)malloc(n * sizeof(int)); //Dynamic allocation of two temporarily arrays B and C.
    C = (int*)malloc((k+1) * sizeof(int));

    //continue the implementation of the counting sort algorithm here.
    // assign all C indices to 0
    for (int i = 0; i < k; i++) {
        C[i] = 0;
    }

    // c indices now contain the number of elements equal to i
    for (int i = 0; i < n; i++) {
        C[A[i]] = C[A[i]] + 1;
    }

    // c indices contain number of elements less than or equal to
    for (int i = 1; i < k; i++) {
        C[i] = C[i] + C[i-1];
    }

    // place elements in A in final position in B
    for (int i = n - 1; i >= 0; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

//Function to print the content of an array
void printArray(int A[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

 //Function to generate n random integer numbers in the range 0 to RAND_MAX = 32767
 void generateInFile(int n)
 {
    int x;
    FILE *out;
    out = fopen("A1.txt", "r+");
    fprintf(out, "%d\n", n);
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        x = rand();
        fprintf(out, "%d ", x);
    }
    fclose(out);
 }
