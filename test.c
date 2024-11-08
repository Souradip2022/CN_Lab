#include<stdio.h>

int binarySearch(int el, int arr[], int size) {
  int start = 0, end = size - 1;
  int mid = start + (end - start) / 2;

  while (start <= end) {
    if (arr[mid] == el) {
      return mid;
    } else if (el < arr[mid]) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }

    mid = start + (end - start) / 2;
  }
  return -1;
}

int main() {
  int arr[] = {9, 8, 7, 6, 5, 5, 4, 3, 3, 1};

  int res = binarySearch(7, arr, 10);
  printf("%d", res);

  return 0;
}
