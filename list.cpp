#include <iostream>
#include <cstring>
using namespace std;

struct LNode {
	int info;
	LNode *next;
	LNode *prev;
};

struct List {
	LNode *head;
	LNode *tail;
	int size;
};

void initList(List *L) {
	L->head = L->tail = NULL;
	L->size = 0;
}

bool isEmpty(List *L) {
	return L->head == NULL;
}

void append(List *L, int value) {
	LNode *n = new LNode;
	n->info = value;
	n->next = n->prev = NULL;
	if (L->tail == NULL) {
		L->head = L->tail = n;
	}
	else {
		L->tail->next = n;
		n->prev = L->tail;
		L->tail = n;
	}
	L->size++;
}

void insert(List *L, int value, LNode *after) {
	LNode *n = new LNode;
	n->info = value;
	if (after == L->tail) {
		return append(L, value);
	}
	else {
		n->prev = after;
		n->next = after->next;
		after->next = n;
		after->next->next->prev = n;
	}
	L->size++;
}

int remove(List *L) {
	int info = L->head->info;
	LNode *oldHead = L->head;
	L->head = L->head->next;
	if (L->head == NULL) {
		L->tail = NULL;
	}
	else {
		L->head->prev = NULL;
	}
	oldHead = NULL;
	delete oldHead;
	L->size--;
	return info;
}

void clear(List *L) {
	LNode *temp = L->head;
	while (temp != NULL) {
		LNode *oldHead = temp;
		temp = temp->next;
		delete oldHead;
	}
	delete temp;
	L->head = NULL;
	L->tail = NULL;
	L->size = 0;
}

int main() {
	List *L = new List;
	LNode *after = new LNode;
	initList(L);
	int n, value;
	cin >> n;
	char oper;
	for (int i = 0; i < n; i++) {
		cin >> oper;
		if (oper == '-') {
			cout << remove(L) << endl;
			if (L->size % 2 == 1 && L->size != 1) {
				after = after->next;
			}
			else if (L->size == 1) {
				after = L->head;
			}
		}
		else if (oper == '+') {
			if (isEmpty(L)) {
				cin >> value;
				append(L, value);
				after = L->head;
			}
			else {
				cin >> value;
				append(L, value);
				if (L->size % 2 == 1) {
					after = after->next;
				}
			}
		}
		else if (oper == '*') {
			cin >> value;
			if (isEmpty(L)) {
				append(L, value);
				after = L->head;
			}
			else {
				insert(L, value, after);
				if (L->size % 2 == 1) {
					after = after->next;
				}
			}
		}
	}
	after = NULL;
	clear(L);
	delete after;
	delete L;
	return 0;
}