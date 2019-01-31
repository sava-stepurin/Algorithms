#include <iostream>
#include <vector>

using namespace std;

int Partition(std::vector<unsigned int>& array, int left, int right) {
    unsigned int value = array[left];
    int curr_left = left - 1;
    int curr_right = right + 1;
    bool flag = true;
    while (flag) {
        do {
            ++curr_left;
        } while (array[curr_left] < value);
        do {
            --curr_right;
        } while (array[curr_right] > value);

        if (curr_left >= curr_right) {
            flag = false;
            return curr_right;
        }

        std::swap(array[curr_left], array[curr_right]);
    }
    return curr_right;
}


void QuickSort(std::vector<unsigned int>& array, int left, int right, int middle) {
    if (left >= right) {
        return;
    }
    int pivot = Partition(array, left, right);
    QuickSort(array, left, pivot, middle);
    QuickSort(array, pivot + 1, right, middle);
}


int main() {
  size_t size;
  cin >> size;
  vector<unsigned int> array(size);
  for (int i = 0; i < size; i++) {
    cin >> array[i];
  }
  QuickSort(array, 0, size - 1);
  for (int i = 0; i < size; i++) {
    cout << array[i] << ' ';
  }
  return 0;
}
