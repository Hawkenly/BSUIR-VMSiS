#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include<ctime>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//0 - 15 black background and all colors of foreground
//16 - 31 next backgrouns amd all color of foreground




struct list{
    int*element;
    int color;
    struct list*next;
    struct list*prev;
};
int check_before(list*head,int*element);

list* push( list **head,int color,int *element){
    struct list*temp=(struct list*)calloc(1,sizeof(struct list));
    temp->element=element;
    temp->color=color;
    temp->next=nullptr;
    temp->prev=nullptr;
    if(*head==nullptr){
       *head=temp;
    }
    else {
        struct list *p = *head;
        while (p->next != nullptr)
            p = p->next;
        p->next=temp;
        temp->prev=p;
    }
    return temp;
}

//рекурсивно добавить элементы в массив списков и далее при выводе сравнивать наличие в том или ином списке

void find_island(int color,list**head,int** matrix,int n, int m, int x, int y){
    if(x==n || y==m ||x==-1 || y==-1 || matrix[x][y]==0 || check_before(*head,&matrix[x][y])==1)
        return;
    push(head,color,&matrix[x][y]);

    find_island(color,head,matrix,n,m,x-1,y);
    find_island(color,head,matrix,n,m,x,y-1);
    find_island(color ,head, matrix,n,m,x+1,y);
    find_island(color,head,matrix,n,m,x,y+1);
}

int check_before(list*head,int*element){
   list*p=head;
   while(p!=nullptr){
       if(p->element==element)
           return 1;
       p=p->next;
   }
    return 0;
}


int main(){
    srand(time(nullptr));
    int n,m;
    cout<<"Input the size of matrix: n"<<endl;
    cin >> n;
    cout<<"Input the size of matrix: m"<<endl;
    cin>>m;
    int **matrix;
    matrix=(int**)calloc(n,sizeof(int*));
    for(int i=0;i<n;i++)
        matrix[i]=(int*)calloc(m,sizeof(int));

    struct list**lists;
    int size=m*n/2;
    if(m*n%2==1)
        size++;
    //выделение памяти на массив списков
    lists=(struct list**)calloc(size,sizeof(struct list*));
   for(int i=0;i<size;i++)
       lists[i]=nullptr;
//заполнение матрицы
   /* for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            printf("Input [%d][%d] element:" ,i,j);
               scanf_s("%d",&matrix[i][j]);
        }*/

   for(int i=0;i<n;i++)
       for(int j=0;j<m;j++)
           matrix[i][j]=rand()%2;

    /*for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;*/

    int num_color=31;
    int col_list=-1;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            if(matrix[i][j]==0)
                continue;
            else{
                list*p;
                int fl=0;
                for(int k=0;k<size;k++) {
                    p = lists[k];
                    while ( p!= nullptr){
                        if(&matrix[i][j]==p->element) {
                            fl = 1;
                            break;
                        }
                        p=p->next;
                    }
                }
                if(fl==1)
                    continue;
                else {
                    num_color+=16;
                    if(num_color==255)
                        num_color=31;
                    col_list++;
                    find_island(num_color,&lists[col_list],matrix,n,m,i,j);
                }

            }
        }

    for(int i=0;i<n;i++) {
        for (int j = 0; j < m; j++){
            if(matrix[i][j]==0) {
                SetConsoleTextAttribute(console,15);
                cout << matrix[i][j] << " ";
            }
            else{
                list*p;
                for(int k=0;k<size;k++){
                    int fl=0;
                    p=lists[k];
                    while(p!=nullptr){
                        if(&matrix[i][j]==p->element){
                            SetConsoleTextAttribute(console,p->color);
                            cout<<matrix[i][j]<<" ";
                            fl=1;
                            break;
                        }
                        p=p->next;
                    }
                    if(fl==1)
                        break;
                }
            }
        }
        cout<<endl;
    }

    /*for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }*/
   /*
    string text="It is a good day today! gggggggggggggggg hhhhhhh h j huh hguhaurh hrahirjhgruwiogfjvbnrpiueo";
    size_t len=text.length();
    int y=1;
    for(size_t x=0;x<len;x++)
    {
        SetConsoleTextAttribute(console,y);
        cout<<text[x];
        y++;
        if(y>15)
            y=1;
        Sleep(100);
    }
    SetConsoleTextAttribute(console,15); // return to normal console(black and white)*/
    _getch();
    return 0;
}
