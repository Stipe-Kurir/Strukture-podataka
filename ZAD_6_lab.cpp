#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



typedef struct lista *Pozicija;
struct lista {
	int El;
	Pozicija next;
};


int PopStog( Pozicija P);
int PopRed(Pozicija P);
void Push(int x,Pozicija P);
void Ispis(Pozicija P);

int main()
{
	struct lista HeadStog;
	HeadStog.next = NULL;

	struct lista HeadRed;
	HeadRed.next = NULL;

	int a;
	int n;
	int i;
	int max=100;
	int min=10;
	char c;

	srand(time(NULL));
	printf("Unesite slovo 's' ako zelite stog ili unesite 'r' ako zelite red!");
	scanf("%c", &c);


	switch (c)
	{

	case 's':
		printf("KOliko brojeva želite unijeti u stog?");
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{

			a = min + (rand() % (max - min + 1));
			Push(a, &HeadStog);

		}


		Ispis(HeadStog.next);
		printf("\n");
		printf("izbrisan broj je:%d\n", PopStog(&HeadStog));
		printf("Ispis stoga nakon brisanja jednog elementa:\n");
		Ispis(HeadStog.next);
		break;

	case 'r':
		printf("KOliko brojeva želite unijeti u red?");
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{

			a = min + (rand() % (max - min + 1));
			Push(a, &HeadRed);

		}
		Ispis(HeadRed.next);
		printf("\n");
		printf("izbrisan broj je:%d\n", PopRed(&HeadRed));
		printf("Ispis stoga nakon brisanja jednog elementa:\n");
		Ispis(HeadRed.next);
		break;

	default:
		printf("Unijeli ste krivi znak!\n");
		break;

	}

	return 0;
}

void Push(int x, Pozicija P)  //Unos na pocetak.Onaj koji je unesen na pocetak je zadnji uneseni element!

{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct lista));
	q->El = x;
	q->next = P->next;
	P->next = q;

}


void Ispis(Pozicija P)

{
	while (P != NULL)
	{
		printf("%d\n", P->El);
		P = P->next;
	}
}



int PopStog(Pozicija P) //Briše zadnji uneseni element,a to je onaj koji se nalazi na pocetku!

{
	int x=0;
	Pozicija temp;

	if (P->next != NULL)
	{
		x = P->next->El;
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
	return x;

}


int PopRed(Pozicija P)  //Briše prvi uneseni element,a to je onaj koji se nalazi na kraju!

{
	Pozicija prev;
	prev = P;
	P = P->next;
	int x;

	while (P->next != NULL)
	{
		prev = P;
		P = P->next;
	}

	if (P->next == NULL)
	{
		x = P->El;
		prev->next = P->next;
		free(P);
	}
	return x;
}