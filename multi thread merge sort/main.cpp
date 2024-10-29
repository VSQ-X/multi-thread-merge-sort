#include <iostream>
#include <future>
#include <chrono>
#include <random>
void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;
    // создаем временные массивы
    int* left = new int[nl];
    int* right = new int[nr];

    // копируем данные во временные массивы
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  // начало левой части

    while (i < nl && j < nr) {
        // записываем минимальные элементы обратно во входной массив
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }
    delete[] left;
    delete[] right;
}
void mergeSort(int* arr, int l, int r)
{
    if (l >= r)
        return; //выход из рекурсии

    int m = (l + r - 1) / 2;
    if (m - l > 1000)
    {

        std::future<void> f = std::async(std::launch::async, [&]() {
            mergeSort(arr, l, m);
            });
        mergeSort(arr, m + 1, r);
    }
    else
    {
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
}
auto main() -> int {
    srand(0);
    int arr_size = 1000000;
    int* arr = new int[arr_size];
    std::cout << "Generating and putting numbers in array\n";
    for (size_t i = 0; i < arr_size; i++)
    {
        arr[i] = rand() % 4200;
    }
    mergeSort(arr, 0, arr_size - 1);

    std::cout << "finished";
    delete[] arr;
    return 0;
}