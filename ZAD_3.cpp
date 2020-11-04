#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct lista* Pozicija;

struct lista {
	char ime[30];
	char prezime[30];
	int godina_rodjena;
	Pozicija next;
};

void Sortiraj(char* prez, char* im, int god, Pozicija P);                            //SORTIRANI UNOS
void UnosPocetak(char* im, char* prezim, int god, Pozicija P);                       //UNOS NA POCETAK
void Ispis(Pozicija P);                                                              //ISPIS
void UnosKraj(char* im, char* prezim, int god, Pozicija P);                          //UNOS NA KRAJ
Pozicija Trazi(char* prezim, Pozicija P);                                            //FUNKCIJA TRAŽI ELM!
void Brisi(char* prezim, Pozicija P);                                                //IZBRIŠE TOČNO ONI ELEMNT KOJI SI TRAZIA!!
void UnosIspred(char* im, int god, char* prezim, char* prez, Pozicija P);            //UNOSIMO ISPRED
void UnosIza(char* im, int god, char* prezim, char* prez, Pozicija P);               //UNOSIMO IZA
void UpisDat(Pozicija P);                                                            //UPISUJEMO U DATOTEKU
void citajDat(Pozicija P);                                                           //ČITAMO IZ DATOTEKE



//GLAVNA FUNKCIJA

int main()
{
	struct lista Head;
	Head.next = NULL;
	struct lista Osoba[10];


	char i[30] = { 0 };
	char pr[30] = { 0 };
	int go = 0;
	char l[30] = { 0 };
	char r[30] = { 0 };
	int g = 0;
	int k;
	char prezimena[30] = { 0 };
	char a[30] = { 0 };
	char c[30] = { 0 };
	int b = 0;

	char im[30] = { 0 };
	char prez[30] = { 0 };
	int god = 0;





	for (k = 0; k < 2; k++)
	{
		printf("Unesite koliko godina ima osoba\n");
		scanf_s("%d", &Osoba[k].godina_rodjena);


		printf("Unesite ime:\n");
		scanf("%s", Osoba[k].ime);

		printf("UNEsoite prezime:\n");
		scanf("%s", Osoba[k].prezime);

		UnosPocetak(Osoba[k].ime, Osoba[k].prezime, Osoba[k].godina_rodjena, &Head);

	}


	printf("Unesite ime\n");
	scanf("%s", i);
	printf("Unesite prezie:\n");
	scanf("%s", pr);
	printf("Unesite godine\n");
	scanf("%d", &go);

	UnosKraj(i, pr, go, &Head);

	Ispis(Head.next);

	scanf("%s", prezimena);

	printf(" adresa od prezimena kojeg ste trazili je %d\n", Trazi(prezimena, &Head));



	Ispis(Head.next);
	printf("Unesite ime\n");
	scanf("%s", l);
	printf("Unesite prezie:\n");
	scanf("%s", r);
	printf("Unesite godine\n");
	scanf("%d", &g);

	UnosIspred(l, g, r, prezimena, &Head);




	printf("Unesite ime\n");
	scanf("%s", a);
	printf("Unesite prezie:\n");
	scanf("%s", c);
	printf("Unesite godine\n");
	scanf("%d", &b);
	UnosIza(a, b, c, prezimena, &Head);



	Ispis(Head.next);


	printf("Unesite ime:");
	scanf("%s", im);
	printf("Unesite prezime:");
	scanf("%s", prez);
	printf("Unseite god!");
	scanf("%d", &god);

	Sortiraj(prez, im, god, &Head);

	Ispis(Head.next);


	UpisDat(Head.next);
	citajDat(&Head);

	return 0;
}


void Sortiraj(char* prez, char* im, int god, Pozicija P)      //SORTIRANI UNOS
{
	Pozicija q;
	P = P->next;
	while (P->next != NULL && strcmp(P->prezime, prez) > 0)
	{

		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(struct lista));

	strcpy(q->ime, im);
	strcpy(q->prezime, prez);
	q->godina_rodjena = god;

	q->next = P->next;
	P->next = q;
}



void UnosPocetak(char* im, char* prezim, int god, Pozicija P)  //UNOS NA POCETAK
{
	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct lista));

	strcpy(q->ime, im);
	strcpy(q->prezime, prezim);
	q->godina_rodjena = god;


	q->next = P->next;
	P->next = q;

}

void Ispis(Pozicija P)                     //ISPIS
{
	while (P != NULL)
	{
		printf("%s %s %d %d %d\n", P->ime, P->prezime, P->godina_rodjena, P, P->next);
		P = P->next;
	}
}



void UnosKraj(char* im, char* prezim, int god, Pozicija P)           //UNOS NA KRAJ
{
	Pozicija q;

	while (P->next != NULL)
	{
		P = P->next;
	}

	q = (Pozicija)malloc(sizeof(struct lista));

	strcpy(q->ime, im);
	strcpy(q->prezime, prezim);
	q->godina_rodjena = god;

	q->next = P->next;
	P->next = q;
}


Pozicija Trazi(char* prezim, Pozicija P)     //FUNKCIJA TRAŽI ELM!
{

	P = P->next;


	while ((P->next) != NULL && strcmp(P->prezime, prezim) != 0)
	{

		P = P->next;
	}

	if (P == NULL)
	{
		return NULL;

	}
	return P;
}



void Brisi(char* prezim, Pozicija P) {   //IZBRIŠE TOČNO ONI ELEMNT KOJI SI TRAZIA!!
	Pozicija prev;
	prev = P;
	P = P->next;
	while (P != NULL && strcmp(P->prezime, prezim))
	{
		prev = P;
		P = P->next;

	}
	if (prev != NULL)
	{
		P = prev->next;//ovu liniju moš ali i nemoraš!!
		prev->next = P->next;
		free(P);
	}
}

void UnosIspred(char* im, int god, char* prezim, char* prez, Pozicija P)            //UNOSIMO ISPRED
{
	Pozicija prev;
	Pozicija q;
	prev = P;
	P = P->next;
	while (P != NULL && strcmp(P->prezime, prez))
	{
		prev = P;
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(struct lista));

	strcpy(q->prezime, prezim);
	strcpy(q->ime, im);
	q->godina_rodjena = god;

	q->next = prev->next;
	prev->next = q;
	q->next = P;

}
void UnosIza(char* im, int god, char* prezim, char* prez, Pozicija P)         //UNOSIMO IZA
{

	Pozicija q;

	P = P->next;
	while (P != NULL && strcmp(P->prezime, prez))
	{
		P = P->next;
	}
	q = (Pozicija)malloc(sizeof(struct lista));

	strcpy(q->prezime, prezim);
	strcpy(q->ime, im);
	q->godina_rodjena = god;

	q->next = P->next;
	P->next = q;

}

void UpisDat(Pozicija P)      //UPISUJEMO U DATOTEKU
{
	FILE* ptr;
	ptr = fopen("Studenti.txt", "w");

	if (ptr == NULL)
	{
		printf("Greška pri otvaranju datoteke!");
	}

	while (P != NULL)
	{
		fprintf(ptr, "%s %s %d\n", P->ime, P->prezime, P->godina_rodjena);
		P = P->next;
	}

	fclose(ptr);

}

void citajDat(Pozicija P)         //CITANJE IZ DATOTEKE
{
	FILE* p;
	p = fopen("Studenti.txt", "r");
	Pozicija priv;

	if (p == NULL)
	{
		printf("greška pri otvaranju datoteke!");
	}

	while (1)
	{
		Pozicija priv = NULL;
		priv = (Pozicija)malloc(sizeof(struct lista));
		fscanf(p, "%s %s %d", priv->ime, priv->prezime, &priv->godina_rodjena);

		priv->next = P->next;
		P->next = priv;
		P = priv;

		if (feof(p))
			break;
	}

	printf("Provjera");
	fclose(p);

}