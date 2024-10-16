#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <locale>
typedef struct node{
    char*eng;
    char*rus;
    struct node*left;
    struct node*right;
}node;

node*find_element(node*root,char* word);

void create_dict(node**root,char*eng,char*rus){
    if(*root==nullptr){
        *root=(node*)calloc(1,sizeof(node));
        (*root)->eng=(char*)calloc(strlen(eng)+1,sizeof(char));
        (*root)->rus=(char*)calloc(strlen(rus)+1,sizeof(char));
        strcpy((*root)->eng,eng);
        strcpy((*root)->rus,rus);
        (*root)->left=nullptr;
        (*root)->right=nullptr;
    }
    else if(strcmp((*root)->eng,eng)>0){
        if((*root)->left==nullptr) {
            (*root)->left = (node *) calloc(1, sizeof(node));
            (*root)->left->eng = (char *) calloc(strlen(eng) + 1, sizeof(char));
            (*root)->left->rus = (char *) calloc(strlen(rus) + 1, sizeof(char));
            strcpy((*root)->left->eng, eng);
            strcpy((*root)->left->rus, rus);
            (*root)->left->left= nullptr;
            (*root)->left->right = nullptr;
        }
        else
            create_dict(&(*root)->left,eng,rus);
    }
    else if(strcmp((*root)->eng,eng)<0){
        if((*root)->right==nullptr) {
            (*root)->right = (node *) calloc(1, sizeof(node));
            (*root)->right->eng = (char *) calloc(strlen(eng) + 1, sizeof(char));
            (*root)->right->rus = (char *) calloc(strlen(rus) + 1, sizeof(char));
            strcpy((*root)->right->eng, eng);
            strcpy((*root)->right->rus, rus);
            (*root)->right->left= nullptr;
            (*root)->right->right = nullptr;
        }
        else
            create_dict(&(*root)->left,eng,rus);
    }
}

void print_dict(node*root){
    if(root==nullptr)
        return;
    print_dict(root->left);
    printf("%s\t---\t%s",root->eng,root->rus);
    printf("\n");
    print_dict(root->right);

}

int if_letter_eng(char c){
    if((c>'A' && c<'Z') || (c>'a' && c<'z'))
        return 1;
    return 0;
}

int if_letter_rus(unsigned char c){
    if((c>=192 && c<=255)  ||c==168 || c==184)
        return 1;
    return 0;
}


node*find_element(node*root,char* word){
    if(root==nullptr)
        return root;
    if(strcmp(root->eng,word)>0)
        find_element(root->left,word);
    else if(strcmp(root->eng,word)<0)
        find_element(root->right,word);
    else if(strcmp(root->eng,word)==0)
        return root;
    else
        return nullptr;

}