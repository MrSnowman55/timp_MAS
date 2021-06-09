#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define foreach(item, list) \
	for(node *item = list->pHead; item != NULL; item = item->pNext)

typedef struct node {
	int value;           // значение, которое хранит узел 
	struct node *pNext;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *pHead;  // начало списка
} list;


// инициализация пустого списка
void init(list *l) {
	l->pHead = NULL;
}

// удалить все элементы из списка
void clean(list *l) {
    node* prev = NULL;
    while (l->pHead->pNext) {
        prev = l->pHead;
        l->pHead = l->pHead->pNext;
        free(prev);
    }
    l->pHead = NULL;
}

// проверка на пустоту списка
bool is_empty(list *l) {
	if (l->pHead == NULL) {
		printf("True\n");
		return true;
	} else {
		printf("False\n");
		return false;
	}
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value) {
	foreach(i, l) {
		if (i->value == value) {
			printf("1 ");
			return i;
		}
	}
	printf("0 ");
	return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value) {
	if (l->pHead == NULL) { // list is empty
		node *temp = (node*)malloc(sizeof(node));
		temp->value = value;
		temp->pNext = NULL;
		l->pHead = temp;
		return 0;
	} else { // not empty
		foreach(i, l) {
			if (i->pNext == NULL) {
				node *temp = (node*)malloc(sizeof(node));
				temp->value = value;
				temp->pNext = NULL;
				i->pNext = temp;
				return 0;
			}
		}
	}
	return 1;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value) {
	node *temp = (node*)malloc(sizeof(node));
	temp->value = value;
	if (l->pHead == NULL) {
		temp->pNext = NULL;
		l->pHead = temp;
		return 0;
	} else {
		temp->pNext = l->pHead;
		l->pHead = temp;
		return 0;
	}
	return 1;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value) {
	node *temp = (node*)malloc(sizeof(node));
	temp->pNext = n->pNext;
	temp->value = value;
	n->pNext = temp;
	return 0;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int value) {
	if (l->pHead == NULL) {
		return 1;
	} else if (l->pHead->value == value) {
		node *temp = l->pHead;
		l->pHead = l->pHead->pNext;
		free(temp);
		return 0;
	} else {
		node *prev = l->pHead;
		foreach(i, l) {
			if (i->value == value) {	
				node *temp = i;
				prev->pNext = i->pNext;
				free(temp);
				return 0;
			}
			prev = i;
		}
		return 1;
	}
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
	foreach(i, l) {
		printf("%d ", i->value);
	}
	printf("\n");
}


int main(void) {
	int n, a, k1, k2, k3, m, t, x, j, z;
	list List;
	list *pList = &List;
	(void)scanf("%d", &n);
	init(pList);
	for (int i = 0; i != n; i++) {
		(void)scanf("%d", &a);
		push_back(pList, a);
	}
	print(pList);
	(void)scanf("%d", &k1);
	(void)scanf("%d", &k2);
	(void)scanf("%d", &k3);
	find(pList, k1);
	find(pList, k2);
	find(pList, k3);
	printf("\n");
	(void)scanf("%d", &m);
	push_back(pList, m);
	print(pList);
	(void)scanf("%d", &t);
	push_front(pList, t);
	print(pList);
	(void)scanf("%d", &j);
	(void)scanf("%d", &x);
	node *temp = pList->pHead;
	for (int i = 0; i != j - 1; i++) {
		if (temp->pNext == NULL) { 
			break;
		}
		temp = temp->pNext;
	}
	insert_after(temp, x);
	print(pList);
	(void)scanf("%d", &z);
	remove_node(pList, z);
	print(pList);
	clean(pList);
	return 0;
}