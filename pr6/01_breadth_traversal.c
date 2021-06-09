#include <stdio.h>
#include <stdlib.h>
#define foreach(item, list) \
    for(node_list *item = list->pHead; item != NULL; item = item->pNext)


typedef struct node_list {
    struct node_t *ref_node;
    struct node_list *pNext;
} node_list;

typedef struct list {
    int size;
    struct node_list *pHead;
} list;

typedef struct node_t {
	int value;         
	struct node_t *pLeft;       
	struct node_t *pRight;       
    struct node_t *pParent;      
} node_t;

typedef struct tree {
	int size;        
	struct node_t *pRoot;    
} tree;


void init_l(list* l) {
    l->pHead = NULL;
    l->size = 1;
}

void init_t(tree* t) {
	t->pRoot = NULL;
	t->size = 0;
}

node_list* find(list *l, int value) {
	foreach(i, l) {
		if (i->ref_node->value == value) {
			return i;
		}
	}
	return NULL;
}

int insert(tree* t, int value) {
    if (t->pRoot == NULL) { // tree is empty
        node_t *temp_root = (node_t*)malloc(sizeof(node_t));
        t->size = 1;
        t->pRoot = temp_root;
        temp_root->pLeft = NULL;
        temp_root->pRight = NULL;
        temp_root->value = value;
        temp_root->pParent = NULL;
        return 0;
    } else { // tree is not empty
        node_t *temp = t->pRoot;
        for (int i = 0; i < t->size; i++) {
            if (value == temp->value) {
                return 1;
            } else if (value < temp->value && temp->pLeft != NULL) {
                temp = temp->pLeft;
            } else if (value > temp->value && temp->pRight != NULL) {
                temp = temp->pRight;
            } else {
                break;
            }
        }
        node_t *new_node = (node_t*)malloc(sizeof(node_t));
        t->size++;
        new_node->pLeft = NULL;
        new_node->pRight = NULL;
        new_node->value = value;
        new_node->pParent = temp;
        if (value < temp->value) {
            temp->pLeft = new_node;
            return 0;
        } else {
            temp->pRight = new_node;
            return 0;
        }
        return 2;
    }
}

int push_back(list *l, node_t* ref_node) {
    if (l->pHead == NULL) {
        node_list *temp = (node_list*)malloc(sizeof(node_list));
        temp->ref_node = ref_node;
        temp->pNext = NULL;
        l->pHead = temp;
        l->size = 1;
        return 0;
    } else {
        foreach(i, l) {
			if (i->pNext == NULL) {
				node_list *temp = (node_list*)malloc(sizeof(node_list));
				temp->ref_node = ref_node;
				temp->pNext = NULL;
				i->pNext = temp;
                l->size++;
				return 0;
			}
		}
    }
    return 1;
}

void breadth_first(tree* t) {
    if (t->pRoot == NULL) {
        return;
    } 
    list l;
    list *pList = &l;
    init_l(pList);
    node_t* temp_t = t->pRoot;
    push_back(pList, temp_t);
    while(1) {
        if (temp_t->pLeft) {
            push_back(pList, temp_t->pLeft);
        }
        if (temp_t->pRight) {
            push_back(pList, temp_t->pRight);
        }
        node_list* temp_dl = pList->pHead;
        for (int i = 0; i < pList->size; i++) {
            if (temp_dl->ref_node->pLeft) {
                if (find(pList, temp_dl->ref_node->pLeft->value) == NULL) {
                    push_back(pList, temp_dl->ref_node->pLeft);
                }
            }
            if (temp_dl->ref_node->pRight) {
                if(find(pList, temp_dl->ref_node->pRight->value) == NULL) {
                    push_back(pList, temp_dl->ref_node->pRight);
                }
            }
            temp_dl = temp_dl->pNext;
        }
        if (pList->size == t->size) {
            break;
        }
    }
    foreach(i, pList) {
        printf("%d ", i->ref_node->value);
    }
}

int main(void) {
    tree T;
    tree* pTree = &T;
    init_t(pTree);
    int n;
    for (int i = 0; i < 7; i++) {
        (void)scanf("%d", &n);
        insert(pTree, n);
    }
    breadth_first(pTree);
    return 0;
}