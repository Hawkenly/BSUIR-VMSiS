#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>




typedef struct tree{
    int num;
    struct tree * left;
    struct tree * right;
}tree;

void create_tree(tree **node, int value);
tree* find_element(tree*node,int value);
tree* delete_element(tree*node, int value);
void change_element(tree *root,tree*node,int value);
tree* minimum(tree*node);
void print(tree*node);

int check_int();
void check_7(int*choice);


int findLevel(tree* root, tree* node, int level);
tree* find_prev(tree* root, tree* x, tree* y);
void findDistance(tree* node);



int check_int(){
    char ch;
    while((ch=(char)getchar())!='\n'){
        if(ch<'0' || ch>'9'){
            printf("Wrong input\n");
            fflush(stdin);
            return -1;
        }
    }
    return 1;
}
void check_7(int*choice){
    int sr;
    do {
        scanf_s("%d", choice);
        sr = check_int();
        if (sr == 1) {
            if (*choice < 1 || *choice > 7) {
                printf("Wrong input\n");
                sr = -1;
                fflush(stdin);
            }
        }
    }while(sr==-1);
    fflush(stdin);
}

tree*find_element(tree*node,int value){
    if(node==NULL)
        return node;
    if(value<node->num)
         find_element(node->left,value);
    else if(value>node->num)
         find_element(node->right,value);
    else if(value==node->num)
       return node;
    else
        return NULL;

}

void change_element(tree *root,tree*node,int value){
    int sr,rc;
    tree *p;
    int n;
    if(node==NULL)
        return;
    if(value<node->num) {
        change_element(root, node->left, value);
    }
    else if(value>node->num) {
        change_element(root, node->right, value);
    }
    else if(value==node->num) {
        do {
            do {
                printf("Choose new element\n");
                sr = scanf_s("%d", &n);
                rc=check_int();
            }while(sr==0 || rc==-1);
            p = find_element(root, n);
        } while (p != NULL);
        delete_element(root,node->num);
        create_tree(&root,n);
    }
}

tree* delete_element(tree*node, int value)
{
    if(node==NULL)
        return node;
    if(value< node->num)
        node->left=delete_element(node->left,value);
    else if(value>node->num)
        node->right= delete_element(node->right,value);
    else if(node->left!=NULL && node->right!=NULL) //если нашли элемент и у него есть потомки
    {
        node->num= minimum(node->right)->num; //заменяем его на минимальный элемент правого поддерева (или максимальный левого)
        node->right= delete_element(node->right,node->num); //двигаемся к этому минимальному ( максимальному ) элементу
    }
    else
        if(node->left!=NULL) //если только 1 поддерево
            node=node->left; //
        else                 //
            node=node->right;// иначе правый, либо NULL (если наш node это лист)

        return node;
}

void create_tree(tree **node, int value){
    if(*node==NULL){
        *node=(tree*)calloc(1,sizeof(tree));
        (*node)->num=value;
        (*node)->right=NULL;
        (*node)->left=NULL;
    }
    else if(value<(*node)->num){
        if( (*node)->left!=NULL)
            create_tree(&(*node)->left,value);
        else{
            (*node)->left=(tree*)calloc(1,sizeof(tree));
            (*node)->left->num=value;
            (*node)->left->left=NULL;
            (*node)->left->right=NULL;
        }
    }
    else if(value >(*node)->num){
        if((*node)->right!=NULL)
            create_tree(&(*node)->right,value);
        else{
            (*node)->right=(tree*)calloc(1,sizeof(tree));
            (*node)->right->num=value;
            (*node)->right->left=NULL;
            (*node)->right->right=NULL;
        }
    }
}

void print(tree*node){
    if(node==NULL)
        return;
    print(node->left);
    printf("%d  ",node->num);
    print(node->right);
}

tree* minimum(tree*node){
    if(node->left==NULL)
        return node;
    return minimum(node->left);
}



int findLevel(tree* root, tree* node, int level)
{
    //int lev=level;
    if(node->num<root->num){
        findLevel(root->left,node,level+1);
    }
    else if(node->num>root->num)
        findLevel(root->right,node,level+1);
    else if(node->num==root->num)
        return level;
  /*  if (root == NULL) {
        return -1;
    }

    if (root == node) {
        return level;
    }

    int left = findLevel(root->left, node, level + 1);


    if (left != -1) {
            return left;
    }

    return findLevel(root->right, node, level + 1);*/
}


tree* find_prev(tree* root, tree* x, tree* y)
{
    if (root == NULL) {
        return NULL;
    }

    if (root == x || root == y) {
        return root;
    }

    tree* left = find_prev(root->left, x, y);

    tree* right = find_prev(root->right, x, y);


    if (left!=NULL && right!=NULL) {
            return root;
    }

    if (left!=NULL) {
        return left;
    }

    if (right!=NULL) {
        return right;
    }
}


void findDistance(tree* node) {
    if(node==NULL)
        return;

    tree *prev = NULL; //общий предок
    int n, c,sr,rc;
    tree *x, *y;
    do {
        printf("Input a first element\n");
        sr = scanf_s("%d", &n);
        rc=check_int();
    } while (sr == 0 || rc==-1);
    x = find_element(node, n);
    do {
        printf("Input a second element\n");
        sr = scanf_s("%d", &c);
        rc=check_int();
    } while (sr == 0 || rc==-1);
    y = find_element(node, c);

    if (x != NULL && y != NULL)
        prev = find_prev(node, x, y);
    else {
        return;
    }
    int dist=findLevel(prev, x, 0) + findLevel(prev, y, 0);

    printf("Distance between nodes %d and %d is %d",x->num, y->num,dist);

}