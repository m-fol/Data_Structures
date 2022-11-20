#include <stdio.h>
#include <stdlib.h>

#define StackLimit 6


typedef int StackElementType;   // � ����� ��� ���������  ��� �������
                                //���������� ����� int
typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);



void TraverseStack(StackType Stack);

int main(){
    StackType Stack, minStack;
    StackElementType temp, min;
    int i;
    char ch;

    CreateStack(&Stack);
    CreateStack(&minStack);

    printf("Dwse to epomeno stoixeio: ");

    scanf("%d%c", &temp, &ch);
    Push(&Stack, temp);
    min = temp;
    Push(&minStack, min);
    TraverseStack(Stack);
    printf("Min=%d", min);
    for(i=0;i<5;i++){
        printf("\nDwse to epomeno stoixeio: ");
        scanf("%d%c", &temp, &ch);
        Push(&Stack, temp);
        if(temp<=min){
            min = temp;
            Push(&minStack, min);
        }
        TraverseStack(Stack);
        printf("Min=%d", min);
    }

    printf("\n\nEmptying stack\n");

    while(!EmptyStack(Stack)){
        Pop(&Stack, &temp);
        if(temp == min){
            Pop(&minStack, &min);
            if(!EmptyStack(minStack)){
                Pop(&minStack, &min);
                Push(&minStack, min);
                printf("Min=%d\n", min);
            }
        }
        TraverseStack(Stack);

    }











    return 0;
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




