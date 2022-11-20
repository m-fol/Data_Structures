#include <stdio.h>

#define QueueLimit 22
#define StackLimit 21

typedef float StackElementType;



typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {FALSE, TRUE} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

typedef float QueueElementType;   /* ο τύπος δεδομένων των στοιχείων της ουράς
                                  ενδεικτικά τύπος int */


typedef struct {
	int Front, Rear;
	QueueElementType Element[QueueLimit];
} QueueType;



void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);

void TraverseQ(QueueType Queue);
void ReverseQ(QueueType *Queue);

int main(){

    QueueType AQ;
    int i;
    float num;

    CreateQ(&AQ);
    for(i=0;i<21;i++){
        num = (float)i/2.0;
        AddQ(&AQ, num);
    }
    TraverseQ(AQ);
    ReverseQ(&AQ);
    printf("\n");
    printf("Reverse Queue\n");
    TraverseQ(AQ);

    return 0;

}


void CreateQ(QueueType *Queue)
/*  Λειτουργία:  Δημιουργεί μια κενή ουρά.
    Επιστρέφει:  Κενή ουρά
*/
{
	Queue->Front = 0;
	Queue->Rear = 0;
}

boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, False διαφορετικά
*/
{
	return (Queue.Front == Queue.Rear);
}

boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
	return ((Queue.Front) == ((Queue.Rear +1) % QueueLimit));
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Αφαιρεί το στοιχείο Item από την εμπρός άκρη της ουράς
                αν η ουρά δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα κενής ουρά αν η ουρά είναι κενή
*/
{
	if(!EmptyQ(*Queue))
	{
		*Item = Queue ->Element[Queue -> Front];
		Queue ->Front  = (Queue ->Front + 1) % QueueLimit;
	}
	else
		printf("Empty Queue\n");
}

void AddQ(QueueType *Queue, QueueElementType Item)
/* Δέχεται:    Μια ουρά Queue και ένα στοιχείο Item.
   Λειτουργία: Προσθέτει το στοιχείο Item στην ουρά Queue
                αν η ουρά δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα γεμάτης ουράς αν η ουρά είναι γεμάτη
*/
{
	if(!FullQ(*Queue))
	{
		Queue ->Element[Queue ->Rear] = Item;
		Queue ->Rear = (Queue ->Rear + 1) % QueueLimit;
	}
	else
		printf("Full Queue\n");
}


void TraverseQ(QueueType Queue) {
	int current;
	if (!EmptyQ(Queue)) {
        current = Queue.Front;
	    while (current != Queue.Rear) {
            printf("%.2f ", Queue.Element[current]);
            current = (current + 1)%QueueLimit;
	   }
	   printf("\n");
    }
    else printf("Empty Queue\n");
}

void CreateStack(StackType *Stack)
/* LEITOYRGIA: DHMIOYRGEI MIA KENH STOIBA.
   EPISTREFEI: MIA KENH STOIBA *)
*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/* DEXETAI:    MIA STOIBA Stack.
   LEITOYRGIA: ELEGXEI AN H STOIBA Stack EINAI KENH.
   EPISTREFEI: TRUE AN H Stack EINAI KENH, FALSE DIAFORETIKA. */
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* DEXETAI:    MIA STOIBA Stack.
   LEITOYRGIA: ELEGXEI AN H STOIBA Stack EINAI GEMATH.
   EPISTREFEI: TRUE AN H STOIBA Stack EINAI GEMATH, FALSE DIAFORETIKA. */
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/* DEXETAI:    MIA STOIBA Stack KAI TO STOIXEIO Item.
   LEITOYRGIA: EISAGEI STH KORYFH THS STOIBAS Stack, AN DEN EINAI GEMATH,
               TO STOIXEIO Item.
   EPISTREFEI: THN TROPOPOIHMENH STOIBA Stack.
   EJODOS:     MHNYMA GEMATHS STOIBAS, AN H STOIBA EINAI GEMATH. */
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* DEXETAI:    MIA STOIBA Stack.
   LEITOYRGIA: AFAIREI APO TH KORYFH THS STOIBAS Stack, AN DEN EINAI KENH,
               TO STOIXEIO Item.
   EPISTREFEI: TO STOIXEIO Item KAI THN TROPOPOIHMENH STOIBA Stack
   EJODOS:     MHNYMA KENHS STOIBAS, AN H STOIBA EINAI KENH. */
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

void ReverseQ(QueueType *Queue){

    StackType AStack;
    QueueElementType item;

    CreateStack(&AStack);
    while(!EmptyQ(*Queue)){
        RemoveQ(Queue, &item);
        Push(&AStack, item);
    }
    while(!EmptyStack(AStack)){
        Pop(&AStack, &item);
        AddQ(Queue, item);
    }


}






