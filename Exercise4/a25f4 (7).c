#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NumberOfNodes 10    /*όριο μεγέθους της συνδεδεμένης λίστας,
                            ενδεικτικά τέθηκε ίσο με 50*/
#define NilValue -1          // ειδική μεδενικη τιμη δείχνει το τέλος της Συνδ.λίστας

typedef struct{
    char name[20];
    int weight;
    int cost;
} ListElementType; /*τύπος δεδομένων για τα στοιχεία της συνδεδεμένης λίστας,
                                ενδεικτικά επιλέχθηκε ο τύπος int */
typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;

typedef enum {
    FALSE, TRUE
} boolean;

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);
void sort_list(ListPointer *List, NodeType Node[], boolean choice, int ByFeature);

void switch_positions(ListPointer prevptr, ListPointer CurrPtr, ListPointer NextPtr, NodeType Node[], ListPointer *List);

int main(){

    ListPointer AList;
    NodeType Node[NumberOfNodes];
    ListPointer FreePtr, PredPtr;
    char ch;

    int n;
    ListElementType AnItem;

    InitializeStoragePool(Node, &FreePtr);
    CreateList(&AList);
    printAll(AList, FreePtr, Node);

    TraverseLinked(AList, Node);


    printf("Give objects number: ");
    do{
        scanf("%d%c", &n, &ch);
    }while(n>10 || n<0);
    int i;
    for(i=0;i<n;i++){
        printf("Give name: ");
        scanf("%s%c", AnItem.name, &ch);
        printf("Give weight: ");
        scanf("%d%c", &AnItem.weight, &ch);
        printf("Give cost: ");
        scanf("%d%c", &AnItem.cost, &ch);

        PredPtr=NilValue;
        Insert(&AList, Node, &FreePtr, PredPtr, AnItem);
    }

    printAll(AList, FreePtr, Node);
    TraverseLinked(AList, Node);

    printf("Name Ascending\n");
    sort_list(&AList, Node, TRUE, 1);
    TraverseLinked(AList, Node);
    printf("Weight Ascending\n");
    sort_list(&AList, Node, TRUE, 2);
    TraverseLinked(AList, Node);
    printf("Cost Ascending\n");
    sort_list(&AList, Node, TRUE, 3);
    TraverseLinked(AList, Node);

    printf("Name Descending\n");
    sort_list(&AList, Node, FALSE, 1);
    TraverseLinked(AList, Node);
    printf("Weight Descending\n");
    sort_list(&AList, Node, FALSE, 2);
    TraverseLinked(AList, Node);
    printf("Cost Descending\n");
    sort_list(&AList, Node, FALSE, 3);
    TraverseLinked(AList, Node);

    return 0;




}

void sort_list(ListPointer *List, NodeType Node[], boolean choice, int ByFeature){
    ListPointer NextPointer, CurrPtr, PrevPtr, OutPtr;
    boolean swap;

    if(!EmptyList(*List)){
        OutPtr = *List;
        while(OutPtr!=NilValue){
            CurrPtr = *List;
            PrevPtr = NilValue;
            NextPointer = Node[CurrPtr].Next;
            while(!FullList(NextPointer)){
                swap = FALSE;
                if(choice){ //ascending
                    switch(ByFeature){
                        case 1:
                            if(strcmp(Node[CurrPtr].Data.name,Node[NextPointer].Data.name)>0)
                                swap = TRUE;
                            break;
                        case 2:
                            if(Node[CurrPtr].Data.weight>Node[NextPointer].Data.weight)
                                swap = TRUE;
                            break;

                        case 3:
                            if(Node[CurrPtr].Data.cost>Node[NextPointer].Data.cost)
                                swap = TRUE;
                            break;
                    }
                }
                else if(choice==FALSE){
                    switch(ByFeature){
                        case 1:
                            if(strcmp(Node[CurrPtr].Data.name, Node[NextPointer].Data.name)<0)
                                swap = TRUE;
                            break;
                        case 2:
                            if(Node[CurrPtr].Data.weight<Node[NextPointer].Data.weight)
                                swap = TRUE;
                            break;

                        case 3:
                            if(Node[CurrPtr].Data.cost<Node[NextPointer].Data.cost)
                                swap = TRUE;
                            break;

                        }
                    }
                if(swap){
                    switch_positions(PrevPtr, CurrPtr, NextPointer, Node, List);
                    if(OutPtr==CurrPtr){
                        OutPtr = NextPointer;
                    }
                }
                PrevPtr = CurrPtr;
                CurrPtr = NextPointer;
                NextPointer = Node[CurrPtr].Next;
                }
                OutPtr = Node[OutPtr].Next;
            }
        }
        else{
            printf("empty list");
        }
}

void switch_positions(ListPointer prevptr, ListPointer CurrPtr, ListPointer NextPtr, NodeType Node[], ListPointer *List){

    if(CurrPtr == *List){
        *List = NextPtr;
    }
    Node[CurrPtr].Next = Node[NextPtr].Next;
    Node[NextPtr].Next = CurrPtr;
    if(Node[prevptr].Data.weight!=0 && Node[prevptr].Data.cost!=0 && Node[prevptr].Data.name[0]!='\0'){
        Node[prevptr].Next = NextPtr;
    }

}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
/* Δέχεται:   Τον πίνακα Node και τον δείκτη FreePtr που δείχνει στον
                πρώτο διαθέσιμο κόμβο.
  Λειτουργία: Αρχικοποιεί τον πίνακα Node ως συνδεδεμένη λίστα συνδέοντας μεταξύ
                τους διαδοχικές εγγραφές του πίνακα,
                και αρχικοποιεί τον δείκτη FreePtr .
  Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον
                δείκτη FreePtr του πρώτου διαθέσιμου κόμβου
*/
{
    ListElementType t;
   int i;


    t.weight = 0;

    t.cost = 0;

    t.name[0]='\0';
    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data=t;    /* δεν είναι αναγκαίο η απόδοση αρχικής τιμής στο πεδίο των δεδομένων, βοηθάει στην εκτύπωση */
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data=t;
    *FreePtr=0;
}

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;
    //printf("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
    printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
    for (i=0;i<NumberOfNodes;i++)
        printf("(%d:<%s,%d,%d> ->%d) ",i,Node[i].Data.name, Node[i].Data.weight, Node[i].Data.cost, Node[i].Next );
    printf("\n");
}

void CreateList(ListPointer *List)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη λίστα.
   Επιστρέφει: Έναν (μηδενικό) δείκτη που δείχνει σε κενή λίστα
*/
{
  *List=NilValue;
}

boolean EmptyList(ListPointer List)
/* Δέχεται:    Έναν δείκτη List που δείχνει σε μια συνδεδεμένη λίστα.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι κενή.
   Επιστρέφει: True αν η συνδεδεμένη λίστα είναι κενή και false διαφορετικά
*/
{
  return (List==NilValue);
}

boolean FullList(ListPointer FreePtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι γεμάτη.
   Επιστρέφει: True αν η συνδεδεμένηλίστα είναι γεμάτη, false διαφορετικά
*/
{
  return (FreePtr == NilValue);
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
/* Δέχεται:   Τον πίνακα Node και τον δείκτη FreePtr.
  Λειτουργία: Αποκτά έναν "ελεύθερο" κόμβο που τον δείχνει ο δείκτης P.
  Επιστρέφει: Τον δείκτη P και τον τροποποιημένο  δείκτη FreePtr
                που δεικτοδοτεί στο πρώτο διαθέσιμο κόμβο
*/
{
  *P = *FreePtr;
  if (!FullList(*FreePtr))
    *FreePtr =Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
/* Δέχεται:    Τον πίνακα Node, που αναπαριστά τη δεξαμενή των διαθέσιμων κόμβων,
                έναν δείκτη TempPtr και τον δείκτη FreePtr.
   Λειτουργία: Επιστρέφει στη δεξαμενή τον κόμβο στον οποίο δείχνει ο TempPtr.
   Επιστρέφει: Τον τροποποιημένο πίνακα Node και τον δείκτη FreePtr
*/
{
    ListElementType t;
    t.name[0]='\0';
    t.weight = 0;

    t.cost = 0;
  Node[P].Next =*FreePtr;
  Node[P].Data = t; //Οχι αναγκαία εντολή, βοηθητική για να φαίνονται στην εκτύπωση οι διαγραμμένοι κόμβοι
  *FreePtr =P;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
/* Δέχεται:    Μια συνδεδεμένη λίστα, τον πίνακα Node, τον δείκτη PredPtr και
                ένα στοιχείο Item.
  Λειτουργία: Εισάγει στη συνδεδεμένη λίστα, αν δεν είναι γεμάτη, το στοιχείο
                Item μετά από τον κόμβο στον οποίο δείχνει ο δείκτης PredPtr.
  Επιστρέφει: Την τροποποιημένη συνδεδεμένη λίστα, τον τροποποιημένο πίνακα Node
                και τον δείκτη FreePtr.
  Εξοδος:     Μήνυμα γεμάτης λίστας, αν η συνδεδεμένη λίστα είναι γεμάτη
*/
{
  ListPointer TempPtr;
  GetNode(&TempPtr,FreePtr,Node);
  if (!FullList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =*List;
        *List =TempPtr;
    }
    else
      {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =Node[PredPtr].Next;
        Node[PredPtr].Next =TempPtr;
      }
}
  else
    printf("Full List ...\n");
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr)
/* Δέχεται:   Μια συνδεδεμένη λίστα και τον δείκτη PredPtr που δείχνει
                στον προηγούμενο κόμβο από αυτόν που θα διαγραφεί.
  Λειτουργία: Διαγράφει από τη συνδεδεμένη λίστα, αν δεν είναι κενή,
                τον προηγούμενο κόμβο από αυτόν στον οποίο δείχνει ο PredPtr.
  Επιστρέφει: Την τροποποιημένη λίστα και το δείκτη FreePtr.
  Έξοδος:     Μήνυμα κενής λίστας, αν η συνδεδεμένη λίστα είναι κενή
*/
{
  ListPointer TempPtr ;

  if (!EmptyList(*List))
    if (PredPtr == NilValue)
    {
        TempPtr =*List;
        *List =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])
/* Δέχεται:    Μια συνδεδεμένη λίστα.
   Λειτουργία: Κάνει διάσχιση της συνδεδεμένης λίστας, αν δεν είναι κενή.
   Έξοδος:     Εξαρτάται από την επεξεργασία
*/
{
  ListPointer CurrPtr;

  if (!EmptyList(List))
  {
      CurrPtr =List;
      while (CurrPtr != NilValue)
      {
          printf("(%s,%d,%d)\n",Node[CurrPtr].Data.name, Node[CurrPtr].Data.weight, Node[CurrPtr].Data.cost);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}
