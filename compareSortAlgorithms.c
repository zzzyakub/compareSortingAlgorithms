#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// Implement merge sort
// ExtraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r, int* temp)
{
    int i = l;
    int j = m + 1;
    int k = 0;

    while (i <= m && j <= r)
    {
        if (pData[i] <= pData[j])
            temp[k++] = pData[i++];
        else
            temp[k++] = pData[j++];
    }

    while (i <= m)
        temp[k++] = pData[i++];

    while (j <= r)
        temp[k++] = pData[j++];

    for (i = 0; i < k; ++i)
    {
        pData[l + i] = temp[i];
        extraMemoryAllocated += sizeof(int);
    }
}

void mergeSortRecursive(int pData[], int l, int r, int* temp)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortRecursive(pData, l, m, temp);
        mergeSortRecursive(pData, m + 1, r, temp);
        merge(pData, l, m, r, temp);
    }
}

void mergeSort(int pData[], int l, int r)
{
    int* temp = (int*)malloc((r - l + 1) * sizeof(int));
    extraMemoryAllocated += (r - l + 1) * sizeof(int);
    if (temp == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    mergeSortRecursive(pData, l, r, temp);

    free(temp);
}

// Implement insertion sort
// ExtraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    int i, j, key;

    for (i = 1; i < n; i++)
    {
        key = pData[i];
        j = i - 1;

        while (j >= 0 && pData[j] > key)
        {
            pData[j + 1] = pData[j];
            j = j - 1;
            extraMemoryAllocated += sizeof(int);
        }

        pData[j + 1] = key;
        extraMemoryAllocated += sizeof(int);
    }
}

// Implement bubble sort
// ExtraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (pData[j] > pData[j + 1])
            {
                // Swap elements
                temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
                extraMemoryAllocated += sizeof(int);
            }
        }
    }
}

// Implement selection sort
// ExtraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int i, j, minIdx, temp;
    for (i = 0; i < n - 1; i++)
    {
        minIdx = i;
        for (j = i + 1; j < n; j++)
        {
            if (pData[j] < pData[minIdx])
            {
                minIdx = j;
            }
        }

        // Swap elements
        temp = pData[i];
        pData[i] = pData[minIdx];
        pData[minIdx] = temp;
        extraMemoryAllocated += sizeof(int);
    }
}

// Parses input file to an integer array
int parseData(char* inputFileName, int** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int*)malloc(sizeof(int) * dataSz);
        if (*ppData == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }

        int i;
        for (i = 0; i < dataSz; ++i)
        {
            fscanf(inFile, "%d", &(*ppData)[i]);
        }

        fclose(inFile);
    }

    return dataSz;
}

// Prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i = 0; i < 100; ++i)
    {
        printf("%d ", pData[i]);
    }
    printf("\n\t");

    for (i = sz; i < dataSz; ++i)
    {
        printf("%d ", pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt" };

    for (i = 0; i < 3; ++i)
    {
        int* pDataSrc, * pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int*)malloc(sizeof(int) * dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSz);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }

    return 0;
}