#include <stdio.h>
#include <stdlib.h>


// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
	int value;                 // значение узла
	struct node *pLeft;        // указатель на левую ветку
	struct node *pRight;       // указатель на правую ветку
    struct node *pParent;      // указатель на родительский узел
} node;


// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
	int size;                  // длина дерева
	struct node *pRoot;        // указатель на ссылку корня дерева
} tree;


// Инициализация дерева
void init(tree* t) {
	t->pRoot = NULL;
	t->size = 0;
}

// Удалить все элементы из дерева
void clean(tree* t) {
    if (t->pRoot == NULL) {
        return;
    }
    node *temp = t->pRoot;
    while(1) {
        if (temp->pLeft) {
            temp = temp->pLeft;
        } else if (temp->pRight) {
            temp = temp->pRight;
        } else if (temp->pLeft == NULL && temp->pRight == NULL && temp->pParent != NULL) {
            node *temp2 = temp;
            temp = temp->pParent;
            if (temp->pLeft != NULL) {
                temp->pLeft = NULL;
                free(temp2);
            } else {
                temp->pRight = NULL;
                free(temp2);
            }
        } else {
            t->pRoot = NULL;
            t->size = 0;
            free(temp);
            return;
        }
    }
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value) {
    node *temp = t->pRoot;
    for (int i = 0; i < t->size; i++) {
        if (temp == NULL) {
            return NULL;
        } else if (value == temp->value) {
            return temp;
        } else if (value > temp->value) {
            temp = temp->pRight;
        } else if (value < temp->value) {
            temp = temp->pLeft;
        } else {
            return NULL;
        }
    }
    return NULL;
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value) {
    if (t->pRoot == NULL) { // tree is empty
        node *temp_root = (node*)malloc(sizeof(node));
        t->size = 1;
        t->pRoot = temp_root;
        temp_root->pLeft = NULL;
        temp_root->pRight = NULL;
        temp_root->value = value;
        temp_root->pParent = NULL;
        return 0;
    } else { // tree is not empty
        node *temp = t->pRoot;
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
        node *new_node = (node*)malloc(sizeof(node));
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

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value) {
    if (t->pRoot == NULL) {
        return 1;
    } else if (t->pRoot->value == value) {
        node* temp = t->pRoot;
        if (t->pRoot->pLeft == NULL && t->pRoot->pRight == NULL) {
            t->pRoot = NULL;
        } else if (t->pRoot->pLeft && t->pRoot->pRight == NULL) {
            t->pRoot->pLeft->pParent = NULL;
            t->pRoot = t->pRoot->pLeft;
        } else if (t->pRoot->pLeft == NULL && t->pRoot->pRight) {
            t->pRoot->pRight->pParent = NULL;
            t->pRoot = t->pRoot->pRight;
        } else {
            if (t->pRoot->pRight->pLeft) {
                node* temp2 = t->pRoot->pRight->pLeft;
                while (temp2->pLeft) {
                    temp2 = temp2->pLeft;
                }
                t->pRoot = temp2;
                temp->pRight->pLeft = NULL;
                t->pRoot->pParent = NULL;
                t->pRoot->pLeft = temp->pLeft;
                t->pRoot->pRight = temp->pRight;
                temp->pLeft = temp->pRight = NULL;
            } else {
                t->pRoot = temp->pRight;
                t->pRoot->pParent = NULL;
                t->pRoot->pLeft = temp->pLeft;
                temp->pLeft->pParent = t->pRoot;
                temp->pLeft = temp->pRight = NULL;
            }
        }
        free(temp);
        t->size--;
        return 0;
    } else {
        node* temp = find(t, value);
        if (temp == NULL) {
            return 1;
        }
        if (temp->pLeft && temp->pRight == NULL) {
            if (temp->pParent->value > temp->value) {  // node on left
                temp->pParent->pLeft = temp->pLeft;
            } else {
                temp->pParent->pRight = temp->pLeft;  // node on right
            }
            temp->pLeft->pParent = temp->pParent;
            temp->pLeft = temp->pParent = NULL;
        } else if (temp->pRight && temp->pLeft == NULL) {
            if (temp->pParent->value > temp->value) {
                temp->pParent->pLeft = temp->pRight;
            } else {
                temp->pParent->pRight = temp->pRight;
            }
            temp->pRight->pParent = temp->pParent;
            temp->pRight = temp->pParent = NULL;
        } else if (temp->pLeft == NULL && temp->pRight == NULL) {
            if (temp->pParent->value > temp->value) {
                temp->pParent->pLeft = NULL;
            } else {
                temp->pParent->pRight = NULL;
            }
            temp->pParent = NULL;
        } else {
            if (temp->pLeft->pLeft == NULL && temp->pLeft->pRight == NULL) {
                temp->pLeft->pParent = temp->pParent;
                temp->pLeft->pRight = temp->pRight;
                temp->pRight->pParent = temp->pLeft;
                if (temp->pParent->value > temp->value) {
                    temp->pParent->pLeft = temp->pLeft;
                } else {
                    temp->pParent->pRight = temp->pLeft;
                }
            } else if (temp->pRight->pLeft) {
                node* temp2 = temp->pRight->pLeft;
                node* temp_parent;
                while (temp2->pLeft) {
                    temp2 = temp2->pLeft;
                    temp_parent = temp2->pParent;
                }
                temp2->pParent = temp->pParent;
                temp2->pRight = temp->pRight;
                temp->pRight->pParent = temp2;
                temp_parent->pLeft = NULL;
                temp2->pLeft = temp->pLeft;
                temp->pLeft->pParent = temp2;
                if (temp->pParent->value > temp->value) {
                    temp->pParent->pLeft = temp2;
                } else {
                    temp->pParent->pRight = temp2;
                }
            } else {
                temp->pRight->pParent = temp->pParent;
                temp->pLeft->pParent = temp->pRight;
                temp->pRight->pLeft = temp->pLeft;
                if (temp->pParent->value > temp->value) {
                    temp->pParent->pLeft = temp->pRight;
                } else {
                    temp->pParent->pRight = temp->pRight;
                }
            }
        }
        temp->pLeft = temp->pRight = temp->pParent = NULL;
        free(temp);
        t->size--;
        return 0;
    }
    return 1;
}

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n, tree* t) {
    if (t->pRoot == NULL) {
        return 0;
    }
    if (n->pLeft == NULL) {
        node* temp = n;
        int val = n->value;
        if (n->pParent == NULL) {
            t->pRoot = NULL;
            free(temp);
            t->size--;
            return val;
        }
        if (n->pRight != NULL) {
            n->pRight = n->pParent;
            n->pParent = n->pRight;
        } else {
            n->pParent->pLeft = NULL;
            n->pParent = NULL;
        }
        t->size--;
        free(temp);
        return val;
    } else {
        return remove_min(n->pLeft, t);
    }
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(node* n, tree* t) {
    if (n == NULL) {
        return 1;
    } else if (n->pLeft == NULL) {
        return 1;
    } else {
        node* temp_root = n->pLeft;
        if (temp_root->pRight) {
            n->pLeft = temp_root->pRight;
            temp_root->pRight->pParent = n;
        } else {
            n->pLeft = NULL;
        }
        if (n->pParent != NULL) {
            temp_root->pParent = n->pParent;
        } else {
            temp_root->pParent = NULL;
        }
        n->pParent = temp_root;
        temp_root->pRight = n;
        t->pRoot = temp_root;
        return 0;
    }
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n, tree *t) {
    if (n == NULL) {
        return 1;
    } else if (n->pRight == NULL) {
        return 1;
    } else {
        node* temp_root = n->pRight;
        if (temp_root->pLeft) {
            n->pRight = temp_root->pLeft;
            temp_root->pLeft->pParent = n;
        } else {
            n->pRight = NULL;
        }
        if (n->pParent != NULL) {
            temp_root->pParent = n->pParent;
        } else {
            temp_root->pParent = NULL;
        }
        n->pParent = temp_root;
        temp_root->pLeft = n;
        t->pRoot = temp_root;
        return 0;
    }
}

// Определить глубину
int define_deep(node* n, int deep) {
    if (n == NULL) {
        return deep;
    }
    int d1 = define_deep(n->pLeft, deep + 1);
    int d2 = define_deep(n->pRight, deep + 1);

    return (d1 > d2) ? d1 : d2;
}

void print_node(node* n, int current, int deep, int first) {
    if (current == deep) {
        if (first > 0) {
            printf(" ");
        }
        if (n == NULL){
            printf("_");
        } else {
            printf("%d", n->value);
        }
    } else if (n != NULL) {
        print_node(n->pLeft, current + 1, deep, first);
        print_node(n->pRight, current + 1, deep, first + 1);
    } else {
        print_node(n, current + 1, deep, first);
        print_node(n, current + 1, deep, first + 1);
    }
}


// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n) {
    int m = define_deep(n, 0);
    for (int i = 1; i <= m; i++) {
        print_node(n, 1, i, 0);
        printf("\n");
    }
}



// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t) {
    if (t->pRoot == NULL) {
        printf("-"); 
        return;
    }
    print(t->pRoot);
}


int main(void) {
    tree Tree;
    tree *pTree = &Tree;
    init(pTree);
    int n, m1, m2, m3;
    for (int i = 0; i < 4; i++) {
        (void)scanf("%d", &n);
        insert(pTree, n);
    }
    print_tree(pTree);
    printf("\n");
    for (int i = 0; i < 3; i++) {
        (void)scanf("%d", &n);
        insert(pTree, n);
    }
    print_tree(pTree);
    printf("\n");
    (void)scanf("%d", &m1);
    node *temp = find(pTree, m1);
    if (temp == NULL) {
        printf("-");
    } else {
        if (temp->pParent != NULL) {
            printf("%d ", temp->pParent->value);
        } else {
            printf("_ ");
        }
        if (temp->pLeft != NULL) {
            printf("%d ", temp->pLeft->value);
        } else {
            printf("_ ");
        }
        if (temp->pRight != NULL) {
            printf("%d ", temp->pRight->value);
        } else {
            printf("_ ");
        }
    }
    printf("\n\n");
    (void)scanf("%d", &m2);
    temp = find(pTree, m2);
    if (temp == NULL) {
        printf("-");
    } else {
        if (temp->pParent != NULL) {
            printf("%d ", temp->pParent->value);
        } else {
            printf("_ ");
        }
        if (temp->pLeft != NULL) {
            printf("%d ", temp->pLeft->value);
        } else {
            printf("_ ");
        }
        if (temp->pRight != NULL) {
            printf("%d ", temp->pRight->value);
        } else {
            printf("_ ");
        }
    }
    printf("\n\n");
    (void)scanf("%d", &m3);
    remove_node(pTree, m3);
    print_tree(pTree);
    printf("\n\n");
    while (rotate_left(pTree->pRoot, pTree) != 1);
    print_tree(pTree);
    printf("\n\n");
    while (rotate_right(pTree->pRoot, pTree) != 1);
    print_tree(pTree);
    printf("\n\n\n");
    printf("%d", pTree->size);
    printf("\n\n");
    clean(pTree);
    printf("\n");
    print_tree(pTree);
    printf("\n\n");
	return 0;
};