#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista* Pozicija;
struct lista
{
	int El;
	Pozicija next;
};



void SortUnos(int x, Pozicija P);
void Ispis(Pozicija P);
void Unija(Pozicija P1, Pozicija P2, Pozicija REZ);
void Presjek(Pozicija P1, Pozicija P2, Pozicija REZ);



int main()
{
	struct lista L1;
	L1.next = NULL;
	struct lista L2;
	L2.next = NULL;
	struct lista L3;
	L3.next = NULL;
	struct lista L4;
	L4.next = NULL;

	int br1, br2;
	int i;
	int elm = 0;




	printf("Unsesite broj koliko zelite elemenata u prvoj listi:\n");
	scanf("%d", &br1);
	for (i = 0; i < br1; i++)
	{
		printf("Unesite %d. broj:", i + 1);
		scanf("%d", &elm);
		SortUnos(elm, &L1);
	}




	printf("Unsesite broj koliko zelite elemenata u drugoj listi:\n");
	scanf("%d", &br2);
	for (i = 0; i < br2; i++)
	{
		printf("Unesite %d. broj:", i + 1);
		scanf("%d", &elm);
		SortUnos(elm, &L2);
	}



	printf("Prva lista:\n");
	Ispis(L1.next);

	printf("Druga lista:\n");
	Ispis(L2.next);


	Presjek(&L1, &L2, &L3);
	printf("Presjek dviju listi:\n");
	Ispis(L3.next);


	
	
	Unija(&L1,&L2,&L4);
    printf("UNIJA dviju listi:\n");
	Ispis(L4.next);






}



void SortUnos(int x, Pozicija P)
{
	Pozicija q;
	
	while (P->next != NULL && P->next->El < x)
	{
		P = P->next;
	}
	
		q = (Pozicija)malloc(sizeof(struct lista));
		q->El = x;
		q->next = P->next;
		P->next = q;
	

}





void Ispis(Pozicija P)
{
	while (P != NULL)
	{
		printf("%d %d %d\n", P->El, P, P->next);
		P = P->next;
	}
}







void Presjek(Pozicija P1, Pozicija P2, Pozicija REZ)
{
	Pozicija q;
	Pozicija Pocetak;
	Pozicija PocetakRez;
	PocetakRez = REZ;
	Pocetak = P2;
	P2 = P2->next;
	P1 = P1->next;


	while (P1 != NULL)           //OVAJ PRESJEK RADI SAMO SAN STAVIA DA UNOSI NA POCETAK ELEMENTE U NOVU LISTU!!!
	{
		while (P2->next != NULL && (P2->El != P1->El))
		{
			P2 = P2->next;
		}


		if (P2->El == P1->El)
		{
			
			
			REZ = (Pozicija)malloc(sizeof(struct lista));
			REZ->El = P2->El;
            REZ->next = PocetakRez->next;
			PocetakRez->next = REZ;

			P2 = Pocetak->next;
			P1 = P1->next;
        }
		else
		{
			
			P2 = Pocetak->next;
			P1 = P1->next;

		}

	}
	
}







void Unija(Pozicija P1, Pozicija P2, Pozicija REZ)  //UNIJA,ispiše elemente ali ne sortirano!(unosi elemente na pocetak)!
{

	Pozicija q;
	Pozicija Pocetak;
	Pozicija PocetakRez;
	PocetakRez = REZ;
	Pocetak = P2;
	P2 = P2->next;
	P1 = P1->next;

	while (P1 != NULL)
	{
		REZ = (Pozicija)malloc(sizeof(struct lista));
		REZ->El = P1->El;
		REZ->next = PocetakRez->next;
		PocetakRez->next = REZ;
		P1 = P1->next;
	}

	REZ = PocetakRez->next;

	while (P2 != NULL)
	{
		while (REZ->next != NULL && (P2->El != REZ->El))
		{
			REZ = REZ->next;
		}


		if (P2->El == REZ->El)
		{
			P2 = P2->next;
			REZ = PocetakRez->next;
		}
		if (REZ->next == NULL)
		{
			REZ = (Pozicija)malloc(sizeof(struct lista));
			REZ->El = P2->El;
			REZ->next = PocetakRez->next;
			PocetakRez->next = REZ;
			P2 = P2->next;
		}

	}


}
	











