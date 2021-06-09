#include <stdio.h>
#include <stdlib.h>


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

void init_t(tree* t) {
	t->pRoot = NULL;
	t->size = 0;
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

void postorder(node_t* pRoot) {
    if (pRoot) {
        postorder(pRoot->pLeft);
        postorder(pRoot->pRight);
        printf("%d ", pRoot->value);
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
    postorder(pTree->pRoot);
    return 0;
}