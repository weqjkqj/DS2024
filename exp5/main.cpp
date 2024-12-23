#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <locale>
using namespace std;

// 1. 起泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. 选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 4. 归并排序辅助函数，合并两个已排序的子数组
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序主体函数
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 封装后的mergeSort函数，用于适配testSortAlgorithm的参数要求
void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

// 5. 快速排序辅助函数，划分操作
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// 快速排序主体函数
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 封装后的quickSort函数，用于适配testSortAlgorithm的参数要求
void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

// 6. 堆排序辅助函数，维护最大堆性质
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest!= i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// 堆排序主体函数
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

// 测试函数，用于测试不同排序算法在不同顺序数据下的性能
void testSortAlgorithm(void (*sortFunc)(int[], int), int arr[], int n, string algoName) {
    int* copyArr = new int[n];
    for (int i = 0; i < n; i++)
        copyArr[i] = arr[i];

    clock_t start = clock();
    sortFunc(copyArr, n);
    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << algoName << " 排序花费时间: " << time_taken << " 秒" << endl;

    delete[] copyArr;
}

// 生成随机数组
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

// 生成顺序数组
void generateAscendingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

// 生成逆序数组
void generateDescendingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

int main() {
    setlocale(LC_ALL, "");
    const int arraySize = 10000;
    int arr[arraySize];

    // 顺序数组测试
    generateAscendingArray(arr, arraySize);
    testSortAlgorithm(bubbleSort, arr, arraySize, "起泡排序");
    generateAscendingArray(arr, arraySize);
    testSortAlgorithm(insertionSort, arr, arraySize, "插入排序");
    generateAscendingArray(arr, arraySize);
    testSortAlgorithm(selectionSort, arr, arraySize, "选择排序");
    generateAscendingArray(arr, arraySize);
    testSortAlgorithm(mergeSortWrapper, arr, arraySize, "归并排序");
    generateAscendingArray(arr, arraySize);
    testSortAlgorithm(quickSortWrapper, arr, arraySize, "快速排序");
    generateAscendingArray(arr, arraySize);
    testSortAlgorithm(heapSort, arr, arraySize, "堆排序");

    // 逆序数组测试
    generateDescendingArray(arr, arraySize);
    testSortAlgorithm(bubbleSort, arr, arraySize, "起泡排序");
    generateDescendingArray(arr, arraySize);
    testSortAlgorithm(insertionSort, arr, arraySize, "插入排序");
    generateDescendingArray(arr, arraySize);
    testSortAlgorithm(selectionSort, arr, arraySize, "选择排序");
    generateDescendingArray(arr, arraySize);
    testSortAlgorithm(mergeSortWrapper, arr, arraySize, "归并排序");
    generateDescendingArray(arr, arraySize);
    testSortAlgorithm(quickSortWrapper, arr, arraySize, "快速排序");
    generateDescendingArray(arr, arraySize);
    testSortAlgorithm(heapSort, arr, arraySize, "堆排序");

    // 随机数组测试
    generateRandomArray(arr, arraySize);
    testSortAlgorithm(bubbleSort, arr, arraySize, "起泡排序");
    generateRandomArray(arr, arraySize);
    testSortAlgorithm(insertionSort, arr, arraySize, "插入排序");
    generateRandomArray(arr, arraySize);
    testSortAlgorithm(selectionSort, arr, arraySize, "选择排序");
    generateRandomArray(arr, arraySize);
    testSortAlgorithm(mergeSortWrapper, arr, arraySize, "归并排序");
    generateRandomArray(arr, arraySize);
    testSortAlgorithm(quickSortWrapper, arr, arraySize, "快速排序");
    generateRandomArray(arr, arraySize);
    testSortAlgorithm(heapSort, arr, arraySize, "堆排序");

    return 0;
}