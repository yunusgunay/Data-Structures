#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

static long long comparisons = 0;
static long long shifts = 0;
static long long swaps = 0;
const int comparisonTime = 1;
const int shiftTime = 5;
const int swapTime = shiftTime * 3;
const double payPerHour = 100.0;

struct Worker{
    long long workerComparisons = 0;
    long long workerSwaps = 0;

    void reset(){
        workerComparisons = 0;
        workerSwaps = 0;
    }

    long long calculateTime() const{
        return (workerComparisons * comparisonTime) + (workerSwaps * swapTime);
    }
};


int* generate_random_array(int size){
    srand((unsigned int)time(NULL));
    int* arr = new int[size];
    for(int i = 0; i < size; i++){
        arr[i] = rand();
    }

    return arr;
}

void quickSort(int arr[], int first, int last);
int* generate_almost_sorted_array(int size){
    srand((unsigned int)time(NULL));
    int* random_array = generate_random_array(size);
    quickSort(random_array, 0, size - 1);

    int swap_count = size * 0.03;
    if(swap_count < 1){
        swap_count = 1;
    }

    for(int i = 0; i < swap_count; i++){
        int first_index = rand() % size;
        int second_index = size - first_index - 1; //to avoid situations where first_index = 0

        int temp = random_array[first_index];
        random_array[first_index] = random_array[second_index];
        random_array[second_index] = temp;
    }

    return random_array;
}


void swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}


void insertionSort(int arr[], int length){
    comparisons = shifts = 0;
    for(int unsorted = 1; unsorted < length; ++unsorted){
        int nextItem = arr[unsorted];
        shifts++;
        int loc = unsorted;
        for(; (loc > 0) && (arr[loc - 1] > nextItem); --loc){
            comparisons++;
            arr[loc] = arr[loc - 1];
            shifts++;
        }
        arr[loc] = nextItem;
        shifts++;
        if(loc == unsorted)
            comparisons++;
    }
}


int indexOfLargest(const int arr[], int size){
    int indexSoFar = 0;
    for(int currentIndex = 1; currentIndex < size; ++currentIndex){
        comparisons++;
        if(arr[currentIndex] > arr[indexSoFar])
            indexSoFar = currentIndex;
    }
    return indexSoFar;
}

void selectionSort(int arr[], int length){
    comparisons = swaps = 0;
    for(int last = length - 1; last >= 1; --last){
        int largest = indexOfLargest(arr, last + 1);
        swap(arr[largest], arr[last]);
        swaps++;
    }
}


void bubbleSort(int arr[], int length){
    comparisons = swaps = 0;
    bool sorted = false;
    for(int pass = 1; (pass < length) && !sorted; ++pass){
        sorted = true;
        for(int index = 0; index < length - pass; ++index){
            comparisons++;
            int nextIndex = index + 1;
            if(arr[index] > arr[nextIndex]){
                swap(arr[index], arr[nextIndex]);
                swaps++;
                sorted = false;
            }
        }
    }
}


//For Task 1 & Task 2:
void quickPartition(int arr[], int first, int last, int& pivotIndex){
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first + 1;

    for(; firstUnknown <= last; ++firstUnknown){
        comparisons++;
        if(arr[firstUnknown] < pivot){
            lastS1++;
            swap(arr[firstUnknown], arr[lastS1]);
            swaps++;
        }
    }
    swap(arr[first], arr[lastS1]);
    swaps++;

    pivotIndex = lastS1;
}

void quickSort(int arr[], int first, int last){
    int pivotIndex;
    if(first < last){
        quickPartition(arr, first, last, pivotIndex);
        quickSort(arr, first, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, last);
    }
}


//For Task 3:
void quickPartitionWorker(int arr[], int first, int last, int& pivotIndex, Worker& worker){
    int pivot = arr[first];
    int lastS1 = first;
    int firstUnknown = first + 1;

    for(; firstUnknown <= last; ++firstUnknown){
        worker.workerComparisons++;
        if(arr[firstUnknown] < pivot){
            lastS1++;
            swap(arr[firstUnknown], arr[lastS1]);
            worker.workerSwaps++;
        }
    }
    swap(arr[first], arr[lastS1]);
    worker.workerSwaps++;

    pivotIndex = lastS1;
}

void quickSortWorker(int arr[], int first, int last, Worker& worker){
    int pivotIndex;
    if(first < last){
        quickPartitionWorker(arr, first, last, pivotIndex, worker);
        quickSortWorker(arr, first, pivotIndex - 1, worker);
        quickSortWorker(arr, pivotIndex + 1, last, worker);
    }
}

void quickSortWorkDistribution(int arr[], int first, int last, Worker& worker1, Worker& worker2){
    int pivotIndex;
    if(first < last){
        quickPartitionWorker(arr, first, last, pivotIndex, worker1);
        quickSortWorker(arr, first, pivotIndex - 1, worker1);
        quickSortWorker(arr, pivotIndex + 1, last, worker2);
    }
}


//Task 1
void calculateRandom(int truckSize){
    //Insertion Sort
    int* arrInsertion = generate_random_array(truckSize);
    insertionSort(arrInsertion, truckSize);
    cout << "Insertion Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + shifts * shiftTime
         << " seconds (comparisons: " << comparisons << ", shifts: " << shifts << ")" << endl;
    delete[] arrInsertion;

    //Selection Sort
    int* arrSelection = generate_random_array(truckSize);
    selectionSort(arrSelection, truckSize);
    cout << "Selection Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + swaps * swapTime
         << " seconds (comparisons: " << comparisons << ", swaps: " << swaps << ")" << endl;
    delete[] arrSelection;

    //Bubble Sort
    int* arrBubble = generate_random_array(truckSize);
    bubbleSort(arrBubble, truckSize);
    cout << "Bubble Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + swaps * swapTime
         << " seconds (comparisons: " << comparisons << ", swaps: " << swaps << ")" << endl;
    delete[] arrBubble;

    //Quick Sort
    int* arrQuick = generate_random_array(truckSize);
    comparisons = swaps = 0;
    quickSort(arrQuick, 0, truckSize - 1);
    cout << "Quick Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + swaps * swapTime
         << " seconds (comparisons: " << comparisons << ", swaps: " << swaps << ")" << endl;
    delete[] arrQuick;

    cout << endl;
}

//Task 2
void calculateAssumption(int truckSize){
    //Insertion Sort
    int* arrInsertion = generate_almost_sorted_array(truckSize);
    insertionSort(arrInsertion, truckSize);
    cout << "Insertion (Almost) Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + shifts * shiftTime
         << " seconds (comparisons: " << comparisons << ", shifts: " << shifts << ")" << endl;
    delete[] arrInsertion;

    //Selection Sort
    int* arrSelection = generate_almost_sorted_array(truckSize);
    selectionSort(arrSelection, truckSize);
    cout << "Selection (Almost) Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + swaps * swapTime
         << " seconds (comparisons: " << comparisons << ", swaps: " << swaps << ")" << endl;
    delete[] arrSelection;

    //Bubble Sort
    int* arrBubble = generate_almost_sorted_array(truckSize);
    bubbleSort(arrBubble, truckSize);
    cout << "Bubble (Almost) Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + swaps * swapTime
         << " seconds (comparisons: " << comparisons << ", swaps: " << swaps << ")" << endl;
    delete[] arrBubble;

    //Quick Sort
    int* arrQuick = generate_almost_sorted_array(truckSize);
    comparisons = swaps = 0;
    quickSort(arrQuick, 0, truckSize - 1);
    cout << "Quick (Almost) Sort for truck size " << truckSize << ": "
         << comparisons * comparisonTime + swaps * swapTime
         << " seconds (comparisons: " << comparisons << ", swaps: " << swaps << ")" << endl;
    delete[] arrQuick;

    cout << endl;
}

//Task 3
void calculateWorker(int truckSize){
    int* arr = generate_random_array(truckSize);
    Worker worker1, worker2;
    worker1.reset();
    worker2.reset();

    quickSortWorkDistribution(arr, 0, truckSize - 1, worker1, worker2);

    double hours1 = worker1.calculateTime() / 3600.0;
    double cost1 = hours1 * payPerHour;
    double hours2 = worker2.calculateTime() / 3600.0;
    double cost2 = hours2 * payPerHour;

    cout << "Worker 1 took: " << worker1.calculateTime() << " seconds, Cost: " << cost1 << " TL" << endl;
    cout << "Worker 2 took: " << worker2.calculateTime() << " seconds, Cost: " << cost2 << " TL" << endl;
    cout << "Total Cost: " << (cost1 + cost2) << " TL" << endl;
    delete[] arr;
}


int main(){
    for(int i = 3; i <= 12; ++i){
        int truckSize = pow(2, i);
        cout << "TASK 1:" << endl;
        calculateRandom(truckSize);
        cout << "TASK 2:" << endl;
        calculateAssumption(truckSize);
        cout << "TASK 3:" << endl;
        calculateWorker(truckSize);
        cout << "\n------------------------------\n" << endl;
    }

    return 0;
}
