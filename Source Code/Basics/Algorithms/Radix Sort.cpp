// C++ implementation of Radix Sort 
#include<iostream> 
using namespace std;

// A utility function to get maximum value in arr[] 
int getMax(int arr[], int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void CountingSort(int arr[], int size, int div)
{
    int output[size];
    int count[10] = { 0 };

    for (int i = 0; i < size; i++)
        count[(arr[i] / div) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(arr[i] / div) % 10] - 1] = arr[i];
        count[(arr[i] / div) % 10]--;
    }

    for (int i = 0; i < size; i++)
        arr[i] = output[i];
}


void RadixSort(int arr[], int size)
{
    int m = getMax(arr, size);
    for (int div = 1; m / div > 0; div *= 10)
        CountingSort(arr, size, div);
}


int main()
{
    int size;
    cout << "Enter the size of the array: " << endl;
    cin >> size;
    int arr[size];
    cout << "Enter " << size << " integers in any order" << endl;
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    cout << endl << "Before Sorting: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    RadixSort(arr, size);

    cout << endl << "After Sorting: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}


/*
Time complexity: O(d(n+k))
Space complexity: O(n+k)

Working –
Step 1 – Take input array and find MAX number in the array
Step 2 – Define 10 queues each representing a bucket for each digit from 0 to 9.
Step 3 – Consider the least significant digit of each number in the list which is to be sorted.
Step 4 – Insert each number into their respective queue based on the least significant digit.
Step 5 – Group all the numbers from queue 0 to queue 9 in the order they have inserted into their respective queues.
Step 6 – Repeat from step 3 based on the next least significant digit.
Step 7 – Repeat from step 2 until all the numbers are grouped based on the most significant digit.