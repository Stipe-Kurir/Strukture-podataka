#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 256

typedef struct CvorStabla* Stablo;
typedef struct Stog* Pozicija;


typedef struct CvorStabla
{
	char El[MAX];
	Stablo Lijevo;
	Stablo Desno;
}stablo;


typedef struct Stog
{  
	Stablo data;
	Pozicija next;
}stog;


Pozicija AlokacijaStog();
Stablo Alokacija();
int Provjera(char x);
void Push(Pozicija P,char x[]);
void PushCVOR(Pozicija P, Stablo S);

Stablo Pop(Pozicija P);
Stablo StvoriCvor(Stablo x, Stablo y,char X[]);
void Ispis(Stablo S,FILE*p);

int main()
{
	FILE* ptr;
	FILE* dat;
	ptr = fopen("postfix1.txt", "r");
	dat = fopen("postfix.txt", "w");
	char temp[MAX];

	Pozicija HEAD;
	HEAD = AlokacijaStog();
	Stablo ROOT;
	ROOT = Alokacija();

	Stablo CURRENT1 = Alokacija();
	Stablo CURRENT2 = Alokacija();
	Stablo CURRENT = Alokacija();

	if (ptr == NULL)
	{
		printf("Problem s datotekom postfix1.txt!\n");
			return 0;
	}
	if (dat == NULL)
	{
		printf("Problem s datotekom postfix.txt!\n");
		return 0;
	}


	while (!feof(ptr))
	{
		fscanf(ptr, "%s", temp);
		
		if (Provjera(temp[0]))
		{
			Push(HEAD, temp);
		}
		else
		{
			CURRENT1=Pop(HEAD);
			CURRENT2=Pop(HEAD);
		    ROOT=StvoriCvor(CURRENT2, CURRENT1, temp);
			PushCVOR(HEAD, ROOT);
		}

	}
	
	Ispis(ROOT,dat);

	fclose(ptr);
	fclose(dat);
	return 0;
}

int Provjera(char x) //provjeravamo jeli broj ili operator!
{
	if (x >= '0' && x <= '9')
		return 1;
	else
		return 0;
}




Stablo Alokacija()
{
	Stablo novi;
	novi = (Stablo)malloc(sizeof(stablo));
	novi->Lijevo = NULL;
	novi->Desno = NULL;
	strcpy(novi->El, " ");
	return novi;

}


Pozicija AlokacijaStog()
{
	Pozicija novi;
	novi = (Pozicija)malloc(sizeof(stog));
	novi->next = NULL;
	novi->data = NULL;
	return novi;
}


void Push(Pozicija P,char x[])    //OVDJE U PUSH SAMO STVORIMO NOVU STRUKUTRU I U NJU STVLJAMO ZNAKOVE(BROJEVE)!ONA SE POZIVA KAD JE PROCITAN BROJ!
{
	Pozicija novi;
	Stablo NOVI = Alokacija();
	

	if (P->next == NULL)
	{
		novi = AlokacijaStog();
		strcpy(NOVI->El, x);
		novi->data = NOVI;
		P->next = novi;
    }
	else
	{
		while (P->next != NULL)
		{
			P = P->next;
		}
		novi = AlokacijaStog();
		strcpy(NOVI->El, x);
        novi->data = NOVI;
		P->next = novi;
	}

}



Stablo Pop(Pozicija P)
{
	Pozicija temp;
	Stablo x;

	if (P->next == NULL)
	{
		printf("Prazan stog!\n");
		return NULL;
	}
	else
	{
		while (P->next->next != NULL)
		{
			P = P->next;
		}
		x = P->next->data;
		temp = P->next;
		P->next = temp->next;
		free(temp);
		return x;
    }

}




Stablo StvoriCvor(Stablo x, Stablo y,char X[])
{
	Stablo S;
	S = Alokacija();
	strcpy(S->El, X);

	S->Lijevo = x;
	S->Desno = y;

	return S;
}



void Ispis(Stablo S,FILE*p)  //INORDER ISPIS u datoteku!!
{
		if (S != NULL)
		{
			if (!Provjera(S->El[0]))
		         fprintf(p," ( ");

				Ispis(S->Lijevo,p);
				fprintf(p,"%s ", S->El);
				Ispis(S->Desno,p);

			if (!Provjera(S->El[0]))
				fprintf(p," ) ");

		}
}



void PushCVOR(Pozicija P, Stablo S)  //FUNKCIJA KOJA PUSHA CIJELI CVOR SA SVOJIM ELEMENTIMA!ONA SE POZIVA KAD JE PROCITAN OPERATOR!
{

	Pozicija novi;


	if (P->next == NULL)
	{
		novi = AlokacijaStog();
		novi->data = S;
		P->next = novi;
	}
	else
	{
		while (P->next != NULL)
		{
			P = P->next;
		}
		novi = AlokacijaStog();
		novi->data = S;
		P->next = novi;
	}
}