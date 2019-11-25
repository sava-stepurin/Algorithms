#include <iostream>
#include <cstring>
using namespace std;

struct DNode {
	int info;
	DNode *prev;
	DNode *next;
};

struct Deque {
	DNode *head;
	DNode *tail;
	int size;
};

void initDeque(Deque *d) {
	d->head = d->tail = NULL;
	d->size = 0;
}

bool isEmpty(Deque *d) {
	return d->head == NULL;
}

void push_front(Deque *d, int value) {
	DNode *n = new DNode;
	n->next = n->prev = NULL;
	n->info = value;
	if (d->tail == NULL) {
		d->tail = d->head = n;
	}
	else {
		d->head->prev = n;
		n->next = d->head;
		d->head = n;
	}
	d->size++;
	cout << "ok" << endl;
}

void push_back(Deque *d, int value) {
	DNode *n = new DNode;
	n->info = value;
	n->next = n->prev = NULL;
	if (d->tail == NULL) {
		d->head = d->tail = n;
	}
	else {
		d->tail->next = n;
		n->prev = d->tail;
		d->tail = n;
	}
	d->size++;
	cout << "ok" << endl;
}

int pop_front(Deque *d) {
	DNode *temp = d->head;
	int info = d->head->info;
	d->head = d->head->next;
	if (d->head == NULL) {
		d->tail = NULL;
	}
	else {
		d->head->prev = NULL;
	}
	delete temp;
	d->size--;
	return info;
}

int pop_back(Deque *d) {
	DNode *temp = d->tail;
	int info = d->tail->info;
	d->tail = d->tail->prev;
	if (d->tail == NULL) {
		d->head = NULL;
	}
	else {
		d->tail->next = NULL;
	}
	delete temp;
	d->size--;
	return info;
}

int front(Deque *d) {
	return d->head->info;
}

int back(Deque *d) {
	return d->tail->info;
}

int size(Deque *d) {
	return d->size;
}

void clear(Deque *d) {
	DNode *temp = d->head;
	while (temp != NULL) {
		DNode *oldHead = temp;
		temp = temp->next;
		delete oldHead;
	}
	delete temp;
	d->head = NULL;
	d->tail = NULL;
	d->size = 0;
}

int main() {
	Deque *d = new Deque;
	initDeque(d);
	int m;
	cin >> m;
	char command[20];
	for (int i = 0; i < m; i++) {
		cin >> command;
		if (strcmp(command, "push_front") == 0) {
			int n;
			cin >> n;
			push_front(d, n);
		}
		else if (strcmp(command, "push_back") == 0) {
			int n;
			cin >> n;
			push_back(d, n);
		}
		else if (strcmp(command, "pop_front") == 0) {
			if (isEmpty(d)) {
				cout << "error" << endl;
			}
			else {
				cout << pop_front(d) << endl;
			}
		}
		else if (strcmp(command, "pop_back") == 0) {
			if (isEmpty(d)) {
				cout << "error" << endl;
			}
			else {
				cout << pop_back(d) << endl;
			}
		}
		else if (strcmp(command, "back") == 0) {
			if (isEmpty(d)) {
				cout << "error" << endl;
			}
			else {
				cout << back(d) << endl;
			}
		}
		else if (strcmp(command, "front") == 0) {
			if (isEmpty(d)) {
				cout << "error" << endl;
			}
			else {
				cout << front(d) << endl;
			}
		}
		else if (strcmp(command, "size") == 0) {
			cout << size(d) << endl;
		}
		else if (strcmp(command, "clear") == 0) {
			clear(d);
			cout << "ok" << endl;
		}
	}
	clear(d);
	delete d;
	return 0;
}
