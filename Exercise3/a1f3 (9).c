
#include <stdio.h>
#include <stdlib.h>


#define QueueLimit 21  //το όριο μεγέθους της ουράς

typedef int QueueElementType;   /* ο τύπος δεδομένων των στοιχείων της ουράς
                         τύπος struct (δομή) */

typedef struct {
	int Front, Rear;
	QueueElementType Element[QueueLimit];
} QueueType;

typedef enum {FALSE, TRUE} boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);


void TraverseQ(QueueType Queue);

int QSizeA(QueueType Queue);
int QSizeB(QueueType *Q);

int main(){

    QueueType Q;
    QueueElementType QEle;
    CreateQ(&Q);
    int size, i;

    printf("Question a\n");


    for(i=0;i<20;i++){
        AddQ(&Q, i);
    }

    printf("Printing Queue\n");
    TraverseQ(Q);
    size = QSizeA(Q);
    printf("(QSizeA) size=%d\n", size);
    printf("Printing Queue\n");
    TraverseQ(Q);
    size = QSizeB(&Q);
    printf("(QSizeB) size=%d\n", size);
    printf("Printing Queue\n");
    TraverseQ(Q);

    printf("\nQuestion b\n");

    for(i=0;i<20;i++){
        AddQ(&Q, i);
    }

    for(i=0;i<10;i++){
        RemoveQ(&Q, &QEle);
    }
    printf("Printing Queue\n");
    TraverseQ(Q);
    size = QSizeA(Q);
    printf("(QSizeA) size=%d\n", size);

    printf("Printing Queue\n");
    TraverseQ(Q);
    size = QSizeB(&Q);
    printf("(QSizeB) size=%d\n", size);
    printf("Printing Queue\n");
    TraverseQ(Q);

    printf("\nQuestion c\n");
    size = QSizeA(Q);
    printf("(QSizeA) size=%d\n", size);
    printf("Printing Queue\n");
    TraverseQ(Q);
    size = QSizeB(&Q);
    printf("(QSizeB) size=%d\n", size);
    printf("Printing Queue\n");
    TraverseQ(Q);




    return 0;



}

int QSizeA(QueueType Queue){
    return ((QueueLimit - Queue.Front + Queue.Rear )%QueueLimit);
    //εδώ κάνουμε - front + rear και μετα ολο αυτο mod διότι έχουμε την περίπτωση όπου στον πίνακα το rear είναι πριν από το front
}

int QSizeB(QueueType *Q){

    QueueElementType item;
    int count=0;

    while(!EmptyQ(*Q)){
        RemoveQ(Q, &item); //edw exoume &(*Q)
        count++;
    }


    return count;


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
            printf("%d ", Queue.Element[current]);
		  current = (current + 1) % QueueLimit;
	   }
	   printf("\n");
    }
    else printf("Empty Queue\n");
}




