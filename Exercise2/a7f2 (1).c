#include <stdio.h>
#include <stdlib.h>

#define StackLimit 25   // �� ���� �������� ��� �������, ���������� ��� �� 50


typedef int StackElementType;

typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;


void TraverseStack(StackType Stack);


void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);


void GetNthElementA(StackType *Stack, int n, StackElementType *Item);
void GetNthElementB(StackType Stack, int n, StackElementType *Item);

int main(){
    StackType S;
    StackElementType item;
    int n;
    char ch;

    CreateStack(&S);
    int i;
    for(i=1;i<=50;i++){
        if(i%2==0){
            Push(&S,i);
        }
    }
    TraverseStack(S);
    do{
        printf("Dwse n: ");
        scanf("%d%c", &n, &ch);
    }while(n<1 || n> StackLimit);

    GetNthElementA(&S,n,&item);
    printf("Top with GetNthElementA = %d\n", item);
    TraverseStack(S);

    GetNthElementB(S,n,&item);
    printf("Top with GetNthElementB = %d\n", item);
    TraverseStack(S);


    return 0;
}


void GetNthElementA(StackType *Stack, int n, StackElementType *Item){
    StackElementType tempElement;
    StackType temp;
    int i;

    CreateStack(&temp);

    for(i=0; i<n; i++){
        Pop(Stack, &tempElement);
        Push(&temp, tempElement);
    }
    *Item = tempElement;

    while(!EmptyStack(temp)){
        Pop(&temp, &tempElement);
        Push(Stack, tempElement);
    }

}

void GetNthElementB(StackType Stack, int n, StackElementType *Item){
    *Item = Stack.Element[Stack.Top-n+1];
}


void CreateStack(StackType *Stack)
/* ����������: ���������� ��� ���� ������.
   ����������: ���� ������.*
*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/* �������: ��� ������ Stack.
   ����������: ������� �� � ������ Stack ����� ����.
   ����������: True �� � Stack ����� ����, False �����������
*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* �������: ��� ������ Stack.
   ����������: ������� �� � ������ Stack ����� ������.
   ����������: True �� � Stack ����� ������, False �����������
*/
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/* �������: ��� ������ Stack ��� ��� �������� Item.
   ����������: ������� �� �������� Item ���� ������ Stack �� � Stack ��� ����� ������.
   ����������: ��� ������������� Stack.
   ������: ������ ������� �������, �� � ������ Stack ����� ������
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* �������: ��� ������ Stack.
   ����������: ��������� �� �������� Item ��� ��� ������ ��� ������� �� � ������ ��� ����� ����.
   ����������: �� �������� Item ��� ��� ������������� Stack.
   ������:  ������ ����� ������� �� � Stack ����� ����
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

 void TraverseStack(StackType Stack)
{
    int i;
    printf("plithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}




