#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// This function fills three arrays of size NUMBERS_SIZE
// with random integers between 0 and NUMBERS_SIZE.
void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

// This function implements the QuickSort algorithm
// with the pivot element being the middle element.
void Quicksort_midpoint(int numbers[], int i, int j) {
    int left = i, right = j;
    int tmp;
    int pivot = numbers[(i + right) / 2];

    /* partition */
    while (left <= right) {
        while (numbers[left] < pivot)
        {
            left++;
        }
        while (numbers[right] > pivot)
        {
            right--;
        }
        if (left <= right) {
            tmp = numbers[left];
            numbers[left] = numbers[right];
            numbers[right] = tmp;
            left++;
            right--;
        }
    }

    if (i < right)
    {
        // Recursively sort the left partition
        Quicksort_midpoint(numbers, i, right);
    }
    if (left < j)
    {
        // Recursively sort the right partition
        Quicksort_midpoint(numbers, left, j);
    }
}

// This function implements the QuickSort algorithm
// with the pivot element being the median of three elements.
void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    // Base case: If there are 1 or zero elements to sort,
    // array is already sorted
    if (i >= k)
    {
        return;
    }

    // Pick pivot using median-of-three method
    int low = i;
    int high = k;
    int mid = low + (high - low) / 2;
    int pivot = 0;
    if (numbers[low] < numbers[mid])
    {
        if (numbers[mid] < numbers[high])
        {
            pivot = numbers[mid];
        }
        else if (numbers[low] < numbers[high])
        {
            pivot = numbers[high];
        }
        else
        {
            pivot = numbers[low];
        }
    }
    else
    {
        if (numbers[low] < numbers[high])
        {
            pivot = numbers[low];
        }
        else if (numbers[mid] < numbers[high])
        {
            pivot = numbers[high];
        }
        else
        {
            pivot = numbers[mid];
        }
    }

    // Partition the data within the array
    int left = i;
    int right = k;
    while (left <= right)
    {
        while (numbers[left] < pivot)
        {
            left++;
        }
        while (numbers[right] > pivot)
        {
            right--;
        }
        if (left <= right)
        {
            int temp = numbers[left];
            numbers[left] = numbers[right];
            numbers[right] = temp;
            left++;
            right--;
        }
    }

    // Recursively sort the two partitions
    Quicksort_medianOfThree(numbers, i, right);
    Quicksort_medianOfThree(numbers, left, k);
}

// This function implements the insertion sort algorithm to sort an array of integers in ascending order
void InsertionSort(int numbers[], int numbersSize) {
   int i, j, key;
   // Traverse through the array starting from the second element
   for (i = 1; i < numbersSize; i++) {
        // Store the current element in a key variable
       key = numbers[i];
       // Compare the key with each element before it and shift the elements to the right if they are greater than the key
       j = i - 1;
       while (j >= 0 && numbers[j] > key) {
           numbers[j + 1] = numbers[j];
           j = j - 1;
       }
       // Insert the key at the correct position
       numbers[j + 1] = key;
   }
}

int main() {
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);

    // Test Quicksort_midpoint on unsorted array
    clock_t Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort_midpoint on unsorted array: " << elapsedTime << " ms." << endl;

    // Test Quicksort_midpoint on sorted array
    Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort_midpoint on sorted array: " << elapsedTime << " ms." << endl;

    // Test Quicksort_medianOfThree on unsorted array
    fillArrays(arr1, arr2, arr3);
    Start = clock();
    Quicksort_medianOfThree(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort_medianOfThree on unsorted array: " << elapsedTime << " ms." << endl;

    // Test Quicksort_medianOfThree on sorted array
    Start = clock();
    Quicksort_medianOfThree(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort_medianOfThree on sorted array: " << elapsedTime << " ms." << endl;

    // Test InsertionSort on unsorted array
    fillArrays(arr1, arr2, arr3);
    Start = clock();
    InsertionSort(arr1, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "InsertionSort on unsorted array: " << elapsedTime << " ms." << endl;

    // Test InsertionSort on sorted array
    Start = clock();
    InsertionSort(arr1, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "InsertionSort on sorted array: " << elapsedTime << " ms." << endl;

    return 0;
}