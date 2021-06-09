#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define foreach_back(item, list) \
    for(node *item = list->pTail; item != NULL; item = item->pPrev)
#define foreach_forward(item, list) \
    for(node *item = list->pHead; item != NULL; item = item->pNext)


typedef struct node {
        int value;              // значение, которое хранит узел
        struct node *pNext;     // ссылка на следующий элемент списка
        struct node *pPrev;     // ссылка на предыдущий элемент списка
} node;

typedef struct list {
        int size;                // длина списка
        struct node *pHead;      // начало списка (ссылка на 1й элемент)
        struct node *pTail;      // конец списка (ссылка на последний элемент)
} list;

// инициализация пустого списка
void init(list *l) {
    l->pHead = NULL;
    l->pTail = NULL;
    l->size = 0;
}

// удалить все элементы из списка5
void clean(list *l) {
    node *temp;
    while (l->pHead->pNext) {
        temp = l->pHead;
        l->pHead = l->pHead->pNext;
        free(temp);
    }
    temp = l->pHead;
    l->pHead = NULL;
    l->pTail = NULL;
    free(temp);
    l->size = 0;
}

// проверка на пустоту списка
bool is_empty(list *l) {
    if (l->pHead == NULL) {
        return true;
    } else {
        return false;
    }
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value) {
	foreach_forward(i, l) {
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
    if (l->pHead == NULL) {
        node *temp = (node*)malloc(sizeof(node));
        temp->value = value;
        temp->pPrev = NULL;
        temp->pNext = NULL;
        l->pHead = temp;
        l->pTail = temp;
        l->size = 1;
        return 0;
    } else {
        node *temp = (node*)malloc(sizeof(node));
        temp->value = value;
        temp->pNext = NULL;
        temp->pPrev = l->pTail;
        l->pTail->pNext = temp;
        l->pTail = temp;
        l->size++;
        return 0;
    }
    return 1;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value) {
    if (l->pHead == NULL) {
        node *temp = (node*)malloc(sizeof(node));
        temp->value = value;
        temp->pPrev = NULL;
        temp->pNext = NULL;
        l->pHead = temp;
        l->pTail = temp;
        l->size = 1;
        return 0;
    } else {
        node *temp = (node*)malloc(sizeof(node));
        temp->value = value;
        temp->pPrev = NULL;
        temp->pNext = l->pHead;
        l->pHead->pPrev = temp;
        l->pHead = temp;
        l->size++;
        return 0;
    }
    return 1;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value) {
    if (n->pNext == NULL) {
        push_back(l, value);
        return 0;
    }
    node *temp = (node*)malloc(sizeof(node));
    temp->pNext = n->pNext;
    temp->pPrev = n;
    temp->value = value;
    n->pNext->pPrev = temp;
    n->pNext = temp;
    l->size++;
    return 0;
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value) {
    if (n->pPrev == NULL) {
        push_front(l, value);
        return 0;
    }
    node *temp = (node*)malloc(sizeof(node));
    temp->pPrev = n->pPrev;
    temp->pNext = n;
    temp->value = value;
    n->pPrev->pNext = temp;
    n->pPrev = temp;
    l->size++;
    return 0;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value) {
	if (l->pHead == NULL) { return 1; }
	node *prev = l->pHead;
    foreach_forward(i, l) {
        if (i->value == value && i->pPrev == NULL) {
            node *temp = i;
            l->pHead = i->pNext;
            i->pNext->pPrev = NULL;
            free(temp);
            l->size--;
            return 0;
        } else if (i->value == value && i->pNext == NULL) {
            node *temp = i;
            l->pTail = i->pPrev;
            i->pPrev->pNext = NULL;
            free(temp);
            l->size--;
            return 0;
        } else if (i->value == value) {
            node *temp = i;
            prev->pNext = i->pNext;
            i->pNext->pPrev = prev;
            free(temp);
            l->size--;
            return 0;
        } else {
            prev = i;
        }
    }
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value) {
    if (l->pHead == NULL) { return 1; }
	node *prev = l->pTail;
	foreach_back(i, l) {
		if (i->value == value && i->pNext == NULL) {	
            node *temp = i;
            l->pTail = i->pPrev;
            i->pPrev->pNext = NULL;
            free(temp);
            l->size--;
            return 0;
		} else if (i->value == value && i->pPrev == NULL) {
            node *temp = i;
            l->pHead = i->pNext;
            i->pNext->pPrev = NULL;
            free(temp);
            l->size--;
            return 0;
        } else if (i->value == value) {
			node *temp = i;
			prev->pPrev = i->pPrev;
            i->pPrev->pNext = prev;
			free(temp);
            l->size--;
			return 0;
        } else {
    	    prev = i;
        }
	}
	return 1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
    foreach_forward(i, l) {
        printf("%d ", i->value);
    }
    printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l) {
    foreach_back(i, l) {
        printf("%d ", i->value);
    }
    printf("\n");
}

// поиск середины списка
int get_middle_list(list *l) {
    if (l->size % 2 == 0) {
        return l->size / 2;
    } else {
        return (l->size / 2) + 1;
    }
}

// поиск узла по его номеру
node *el_find(list *l, int elnum) {
    node *temp;
    if (get_middle_list(l) >= elnum) {
        temp = l->pHead;
    	for (int i = 0; i != elnum - 1; i++) {
            if (temp->pNext == NULL) {
                break;
            }
		    temp = temp->pNext;
	    }
        return temp;
    } else {
        temp = l->pTail;
        for (int i = l->size; i != elnum; i--) {
            if (temp->pPrev == NULL) {
                break;
            }
            temp = temp->pPrev;
        }
        return temp;
    }
}

int main(void) {
	int n, a, k1, k2, k3, m, t, x, j, z, y, u, r;
    list List;
    list *pList = &List;
    init(pList);
    (void)scanf("%d", &n);
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
	print_invers(pList);
	(void)scanf("%d", &t);
	push_front(pList, t);
	print(pList);
    (void)scanf("%d", &j);
	(void)scanf("%d", &x);
    node *temp = el_find(pList, j);
	insert_after(pList, temp, x);
	print_invers(pList);
    (void)scanf("%d", &u);
    (void)scanf("%d", &y);
	temp = el_find(pList, u);
    insert_before(pList, temp, y);
    print(pList);
	(void)scanf("%d", &z);
	remove_first(pList, z);
	print_invers(pList);
    (void)scanf("%d", &r);
    remove_last(pList, r);
    print(pList);
    clean(pList);
	return 0;
};