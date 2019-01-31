#include <iostream>
#include <cstring>
using namespace std;

struct Heap {
	int size;
	int length;
	int *arr;
};

void initHeap(Heap *h) {
	h->size = 200000;
	h->length = 0;
	h->arr = new int[h->size];
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int left_child(int i) {
	return 2 * i + 1;
}

int right_child(int i) {
	return 2 * i + 2;
}

int parent(int i) {
	return (i - 1) / 2;
}

void sift_down(Heap *h, int index) {
	int left = left_child(index);
	int right = right_child(index);
	int imin = index;
	if (left < h->length && h->arr[left] < h->arr[imin]) {
		imin = left;
	}
	if (right < h->length && h->arr[right] < h->arr[imin]) {
		imin = right;
	}
	if (imin != index) {
		swap(h->arr[index], h->arr[imin]);
		sift_down(h, imin);
	}
}

void sift_up(Heap *h, int index) {
	int target = index;
	while (target > 0 && h->arr[target] < h->arr[parent(target)]) {
		swap(h->arr[target], h->arr[parent(target)]);
		target = parent(target);
	}
}

int size_Heap(Heap *h) {
	return h->length;
}

int get_min(Heap *h) {
	return h->arr[0];
}

void clear(Heap *h) {
	h->length = 0;
	cout << "ok" << endl;
}

int main() {
	int m;
	cin >> m;
	Heap *h = new Heap;
	initHeap(h);
	char s[20];
	for (int i = 0; i < m; i++) {
		cin >> s;
		if (strcmp(s, "insert") == 0) {
			int n;
			cin >> n;
			h->arr[h->length] = n;
			sift_up(h, h->length);
			h->length++;
			cout << "ok" << endl;
		}
		else if (strcmp(s, "extract_min") == 0) {
			if (h->length != 0) {
				cout << h->arr[0] << endl;
				swap(h->arr[h->length - 1], h->arr[0]);
				h->length--;
				sift_down(h, 0);
			}
			else {
				cout << "error" << endl;
			}
		}
		else if (strcmp(s, "get_min") == 0) {
			if (h->length != 0) {
				cout << get_min(h) << endl;
			}
			else {
				cout << "error" << endl;
			}
		}
		else if (strcmp(s, "clear") == 0) {
			clear(h);
		}
		else if (strcmp(s, "size") == 0) {
			cout << size_Heap(h) << endl;
		}
	}
	delete[]h->arr;
	delete[]h;
	return 0;
}