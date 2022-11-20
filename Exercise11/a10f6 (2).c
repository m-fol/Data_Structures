#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define HMax 31              /*     το μέγεθος του πίνακα HashTable
                                ενδεικτικά ίσο με 5 */
#define VMax 30             /*το μέγεθος της λίστας,
                                ενδεικτικά ίσο με 30 */
#define EndOfList -1        /* σημαία που σηματοδοτεί το τέλος της λίστας
                                και της κάθε υπολίστας συνωνύμων */

typedef struct{
    char string[6];
    int num;
}ListElementType;  /*τύπος δεδομένων για τα στοιχεία της λίστας
                               * ενδεικτικά τύπου int */
typedef int KeyType;

typedef struct {
	KeyType key;
	ListElementType Data;
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];   // πίνακας δεικτών προς τις υπολίστες συνωνύμων
    int Size;                // πλήθος εγγραφών της λίστας List
	int SubListPtr;          // Dδείκτης σε μια υπολίστα συνωνύμων
    int StackPtr;           // δείκτης προς την πρώτη ελεύθερη θέση της λίστας List
	ListElm List[VMax];
} HashListType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateHashList(HashListType *HList);
int HashKey(KeyType key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void AddRec(HashListType *HList,ListElm InRec);
void DeleteRec(HashListType *HList,KeyType DelKey);

void Print_HashList(HashListType HList);

int FoldKey(char *s);


int main(){
    HashListType HList;
    ListElm AnItem, AnItem2;
    int Loc1=-1, Loc2=-1, Pred2, Pred1, i, key;

    CreateHashList(&HList);
    printf("Declare variables\n");
    for(i=0;i<4;i++){
        printf("Enter the variable name: ");
        scanf("%s", AnItem.Data.string);
        printf("Enter variable value: ");
        scanf("%d", &AnItem.Data.num);
        AnItem.key = FoldKey(AnItem.Data.string);
        AddRec(&HList, AnItem);
    }
    Print_HashList(HList);

    //A. Multiply Variables
    printf("Multiply Variables\n");
    printf("Enter the first variable: ");
    scanf("%s", AnItem.Data.string);
    AnItem.key = FoldKey(AnItem.Data.string);
    SearchHashList(HList, AnItem.key, &Loc1, &Pred1);

    printf("Enter the second variable: ");
    scanf("%s", AnItem2.Data.string);
    AnItem2.key = FoldKey(AnItem2.Data.string);
    SearchHashList(HList, AnItem2.key, &Loc2, &Pred2);

    if((Loc1!=EndOfList) && (Loc2!=EndOfList)){
        if(strcmp(HList.List[Loc1].Data.string, AnItem.Data.string)==0 && strcmp(HList.List[Loc2].Data.string, AnItem2.Data.string)==0){
            printf("%sx%s=%d\n", HList.List[Loc1].Data.string, HList.List[Loc2].Data.string, HList.List[Loc1].Data.num*HList.List[Loc2].Data.num);
        }
        else{
            if(strcmp(HList.List[Loc1].Data.string, AnItem.Data.string)!=0){
                printf("Undeclared variable %s\n", HList.List[Loc1].Data.string);
            }
            if(strcmp(HList.List[Loc2].Data.string, AnItem2.Data.string)!=0){
                printf("Undeclared variable %s\n", HList.List[Loc2].Data.string);
            }
        }
    }
    else{
        if(Loc1==-1){
            printf("Undeclared variable %s\n", AnItem.Data.string);
        }
        if(Loc2==-1){
            printf("Undeclared variable %s\n", AnItem2.Data.string);
        }
    }

    //B. Add Variables
    printf("Add Variables\n");
    printf("Enter the first variable: ");
    scanf("%s", AnItem.Data.string);
    AnItem.key = FoldKey(AnItem.Data.string);
    SearchHashList(HList, AnItem.key, &Loc1, &Pred1);

    printf("Enter the second variable: ");
    scanf("%s", AnItem2.Data.string);
    AnItem2.key = FoldKey(AnItem2.Data.string);
    SearchHashList(HList, AnItem2.key, &Loc2, &Pred2);

    if((Loc1!=EndOfList) && (Loc2!=EndOfList)){
        if(strcmp(HList.List[Loc1].Data.string, AnItem.Data.string)==0 && strcmp(HList.List[Loc2].Data.string, AnItem2.Data.string)==0){
            printf("%s+%s=%d", HList.List[Loc1].Data.string, HList.List[Loc2].Data.string, HList.List[Loc1].Data.num+HList.List[Loc2].Data.num);
        }
        else{
            if(strcmp(HList.List[Loc1].Data.string, AnItem.Data.string)!=0){
                printf("Undeclared variable %s\n", HList.List[Loc1].Data.string);
            }
            if(strcmp(HList.List[Loc2].Data.string, AnItem2.Data.string)!=0){
                printf("Undeclared variable %s\n", HList.List[Loc2].Data.string);
            }
        }
    }
    else{
        if(Loc1==-1){
            printf("Undeclared variable %s\n", AnItem.Data.string);
        }
        if(Loc2==-1){
            printf("Undeclared variable %s\n", AnItem2.Data.string);
        }
    }


    return 0;


}

int FoldKey(char *s){

    KeyType Key;
    Key = 0;
    int i;
    for(i=0;i<strlen(s);i++){
        Key = Key + (s[i]-65+1)*(i+1);
    }
    return Key;
}

int HashKey(KeyType key)
/* Δέχεται:    Την τιμή key ενός κλειδιού.
   Λειτουργία: Βρίσκει την τιμή κατακερματισμού HValue για το κλειδί Key.
   Επιστρέφει: Την τιμή κατακερματισμού HValue
*/
{
	/*σε περίπτωση που το KeyType δεν είναι ακέραιος
	θα πρέπει να μετατρέπεται κατάλληλα το κλειδί σε αριθμό*/
	return key%HMax;
}

void CreateHashList(HashListType *HList)
/* Λειτουργία: Δημιουργεί μια δομή HList.
   Επιστρέφει: Την δομή HList
*/
{
	int index;

	HList->Size=0;           //ΔΗΜΙΟΥΡΓΕΙ ΜΙΑ ΚΕΝΗ ΛΙΣΤΑ
	HList->StackPtr=0;       //ΔΕΙΚΤΗς ΣΤΗ ΚΟΡΥΦΗ ΤΗΣ ΣΤΟΙΒΑΣ ΤΩΝ ΕΛΕΥΘΕΡΩΝ ΘΕΣΕΩΝ

    /*ΑΡΧΙΚΟΠΟΙΕΙ ΤΟΝ ΠΙΝΑΚΑ HashTable ΤΗΣ ΔΟΜΗΣ HList ΩΣΤΕ ΚΑΘΕ ΣΤΟΙΧΕΙΟΥ ΤΟΥ
        ΝΑ ΕΧΕΙ ΤΗ ΤΙΜΗ EndOfList (-1)*/
    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }

     //Δημιουργία της στοίβας των ελεύθερων θέσεων στη λίστα HList
    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}

boolean FullHashList(HashListType HList)
/* Δέχεται:    Μια δομή HList.
   Λειτουργία: Ελέγχει αν η λίστα List της δομής HList είναι γεμάτη.
   Επιστρέφει: TRUE αν η λίστα List είναι γεμάτη, FALSE διαφορετικά.
*/
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στην υπολίστα συνωνύμων.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της προηγούμενης
                εγγραφής στην υπολίστα
*/
{
	int Next;
	Next=HList.SubListPtr;
	*Loc=-1;
	*Pred=-1;
	while(Next!=EndOfList)
	{
		if (HList.List[Next].key==KeyArg)
		{
			*Loc=Next;
			Next=EndOfList;
		}
		else
		{
			*Pred=Next;
			Next=HList.List[Next].Link;
		}
	}
}
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στη δομή HList.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της
                προηγούμενης εγγραφής της υπολίστας στην οποία ανήκει.
                Αν δεν υπάρχει εγγραφή με κλειδί KeyArg τότε Loc=Pred=-1
*/
{
	int HVal;
	HVal=HashKey(KeyArg);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=-1;
		*Loc=-1;
	}
	else
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}

void AddRec(HashListType *HList,ListElm InRec)
/* Δέχεται:    Μια δομή HList και μια εγγραφή InRec.
   Λειτουργία: Εισάγει την εγγραφή InRec στη λίστα List, αν δεν είναι γεμάτη,
                και ενημερώνει τη δομή HList.
   Επιστρέφει: Την τροποποιημένη δομή HList.
   Έξοδος:     Μήνυμα γεμάτης λίστας, αν η List είναι γεμάτη, διαφορετικά,
                αν υπάρχει ήδη εγγραφή με το ίδιο κλειδί,
                εμφάνιση αντίστοιχου μηνύματος
*/
{
	int Loc, Pred, New, HVal;

   // New=0;
	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;
		SearchHashList(*HList,InRec.key,&Loc,&Pred);
		if(Loc==-1)
		{
			HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New]=InRec;
			if (Pred==-1)
			{
			    HVal=HashKey(InRec.key);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else
	{
		printf("Full list...");
	}
}
void DeleteRec(HashListType *HList,KeyType DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=-1)
	{
		if(Pred!=-1)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HVal=HashKey(DelKey);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d \n",DelKey);
	}
}

void Print_HashList(HashListType HList)
{
   int i, SubIndex;

    // printf("HASHLIST STRUCTURE with SYNONYM CHAINING\n");
    // printf("========================================\n");

         // printf("PINAKAS DEIKTWN STIS YPO-LISTES SYNWNYMWN EGGRAFWN:\n");
          //  for (i=0; i<HMax;i++)
          //    printf("%d| %d\n",i,HList.HashTable[i]);

         // printf("OI YPO-LISTES TWN SYNWNYMWN EGGRAFWN:\n");
          for (i=0; i<HMax;i++)
          {
              SubIndex = HList.HashTable[i];
              while ( SubIndex != EndOfList )
              {
                   printf("[%d, %s %d, %d]",HList.List[SubIndex].key,HList.List[SubIndex].Data.string,HList.List[SubIndex].Data.num, HList.List[SubIndex].Link);
                   printf(" -> ");
                   printf("TELOS % dHS YPO-LISTAS\n", i);
                   SubIndex = HList.List[SubIndex].Link;
               } //* while *)

          }

          /*printf("H STOIBA TWN ELEY8ERWN 8ESEWN THS LISTAS:\n");
          SubIndex = HList.StackPtr;
          while ( SubIndex != EndOfList )
          {
                printf("%d <= ",SubIndex);
                SubIndex = HList.List[SubIndex].Link;
          }
          printf("TELOS\n");

          printf("MEGE8OS THS LISTAS = %d\n", HList.Size);
          printf("========================================\n");
          */
}


