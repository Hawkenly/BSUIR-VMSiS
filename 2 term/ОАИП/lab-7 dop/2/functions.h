#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
typedef struct node{
    char*eng;
    char*rus;
    struct node*left;
    struct node*right;
}node;

void create_dict(node**root,char*eng,char*rus){
    if(*root==NULL){
        *root=(node*)calloc(1,sizeof(node));
        (*root)->eng=(char*)calloc(strlen(eng)+1,sizeof(char));
        (*root)->rus=(char*)calloc(strlen(rus)+1,sizeof(char));
        strcpy((*root)->eng,eng);
        strcpy((*root)->rus,rus);
        (*root)->left=NULL;
        (*root)->right=NULL;
    }
    else if(strcmp((*root)->eng,eng)>0){
        if((*root)->left==NULL) {
            (*root)->left = (node *) calloc(1, sizeof(node));
            (*root)->left->eng = (char *) calloc(strlen(eng) + 1, sizeof(char));
            (*root)->left->rus = (char *) calloc(strlen(rus) + 1, sizeof(char));
            strcpy((*root)->left->eng, eng);
            strcpy((*root)->left->rus, rus);
            (*root)->left->left= NULL;
            (*root)->left->right = NULL;
        }
        else
            create_dict(&(*root)->left,eng,rus);
    }
    else if(strcmp((*root)->eng,eng)<0){
        if((*root)->right==NULL) {
            (*root)->right = (node *) calloc(1, sizeof(node));
            (*root)->right->eng = (char *) calloc(strlen(eng) + 1, sizeof(char));
            (*root)->right->rus = (char *) calloc(strlen(rus) + 1, sizeof(char));
            strcpy((*root)->right->eng, eng);
            strcpy((*root)->right->rus, rus);
            (*root)->right->left= NULL;
            (*root)->right->right = NULL;
        }
        else
            create_dict(&(*root)->left,eng,rus);
    }
}

void print_dict(node*root){
    if(root==NULL)
        return;
    print_dict(root->left);
    printf("%s\t---\t%s",root->eng,root->rus);
    printf("\n");
    print_dict(root->right);

}

int if_letter(char c){
    if((c>'A' && c<'Z') || (c>'a' && c<'z'))
        return 1;
    return 0;
}



