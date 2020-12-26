#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>




typedef struct CvorStabla* Stablo;
typedef struct CvorStabla {
	int EL;
	Stablo Lijevo;
	Stablo Desno;
}stablo;



Stablo Alokacija();
void Meni();
Stablo UnosElementa(Stablo S, int x);
void Ispis(Stablo S);
Stablo TraziElement(Stablo S, int x);
Stablo BrisiElement(Stablo S, int x);
Stablo TraziMin(Stablo S);



int main()
{
	Stablo ROOT;
	ROOT = Alokacija();

	int x = 0;
	int temp = 0;

	printf("Unesite element zelite da bude u ROOT cvoru:\n");
	scanf("%d", &ROOT->EL);




	while (x != 5)
	{
		Meni();
		scanf("%d", &x);

		switch (x)
		{
		case 1:
			printf("Unesite element koji zelite unijeti:\n");
			scanf("%d", &temp);
			UnosElementa(ROOT, temp);
			break;
		case 2:
			Ispis(ROOT);
			printf("\n");
			break;
		case 3:
			printf("Unesite koji element zelite izbrisati:\n");
			scanf("%d", &temp);
			BrisiElement(ROOT, temp);
				break;
		case 4:
			printf("Unesite element koji zelite pronaci:\n");
			scanf("%d", &temp);
			if (TraziElement(ROOT, temp) == NULL)
			{
				printf("Element ne postoji\n");
			}
			else
			{
				printf("Adresa pronadenog elementa:%d\n", TraziElement(ROOT, temp));
			}
			break;
		case 5:
			break;
		default:
			printf("Unijeli ste krivi broj!\n");
			break;
        }
	}

	return 0;
}




Stablo Alokacija()     //Funkcija za alokaciju memorije
{
	Stablo novi;
	novi = (Stablo)malloc(sizeof(stablo));
	novi->Desno = NULL;
	novi->Lijevo = NULL;
	return novi;
}




void Meni()
{
	printf("#################################################\n");
	printf("Unesite 1 ako zelite unijeti element.\n");
	printf("Uneiste 2 ako zelite ispis elemenata.\n");
	printf("Unesite 3 ako zelite izbrisati neki element.\n");
	printf("Unesite 4 ako zelite pronaci neki element.\n");
	printf("Unesite 5 ako zelite izlaz.\n");
	printf("#################################################\n");

}




Stablo UnosElementa(Stablo S, int x)   //Funkcija za unos elementa
{
	if (S==NULL)           
	{
		Stablo novi = Alokacija();
		    novi->EL = x;
			novi->Lijevo = NULL;
			novi->Desno = NULL;
			return novi;
	}

	else if (x < S->EL)
	{
		S->Lijevo = UnosElementa(S->Lijevo, x);
		return S;
	}
	else if (x > S->EL)
	{
		S->Desno = UnosElementa(S->Desno, x);
		return S;
	}
}




void Ispis(Stablo S)  //Inorder ispis,najprije ispis lijevog podstabla,pa trenutni čvor,pa desno podstablo!
{
	if (S != NULL)
	{
		Ispis(S->Lijevo);
		printf("%d  ", S->EL);
		Ispis(S->Desno);
	}
}





Stablo TraziElement(Stablo S, int x)  //Funkcija za trazenje elementa u stablu
{
	if (S == NULL)                    //ako je NULL znači da element nije pronađen,odnosno da ne postoji u stablu!
	{
		return NULL;
	}
	else if (x < S->EL)
	{
		 return TraziElement(S->Lijevo, x);
	}
	else if (x > S->EL)
	{ 
		return TraziElement(S->Desno, x);
	}
	else                              //ako nije element manji ni veći onda znači da je to taj element!
		return S;
}




Stablo TraziMin(Stablo S)     //vraca adresu najmanjeg elementa,a to je onaj koji se nalazi "najlivije"
{                             //ova funkcija nam je potrebna za brisanje elementa
	while (S->Lijevo!= NULL)
	{
		S = S->Lijevo;
	}
	return S;
}



Stablo BrisiElement(Stablo S, int x)
{
	
	if (S == NULL)    //Ako je jednako null znaci da ne postoji taj element
	{
		printf("Ne postoji taj element!\n");
		return S;
	}
	else if (x < S->EL)    //ako je manji od trenutnog cvora pomicemo se u lijevo
	{
		S->Lijevo = BrisiElement(S->Lijevo, x);
		return S;
	}
	else if (x > S->EL)      //ako je veci od trenutnog cvora onda se pomicemo u desno
	{
		S->Desno = BrisiElement(S->Desno, x);
		return S;
	}
	else if (S->Lijevo != NULL && S->Desno != NULL)  //kad smo dosli do ovdje to znaci da je pronaden te sad provjeravamo ima li dvoje djece
	{
		Stablo temp;                            //ako ima dvoje djece stvaramo  temp i u nju smjestimo najmanji element od desnog djeteta(jer najmanji element od desnog djeteta je sigurno veći od najvećeg elementa lijevog dijeteta!). 
		temp = TraziMin(S->Desno);
		S->EL = temp->EL;               
		S->Desno = BrisiElement(S->Desno, S->EL);
		return S;

	}
	else   // ovaj else znaci da ima jedno ili nula djece!
	{
		Stablo temp;
		temp = S;
		if (NULL == S->Lijevo)
		{
			S = S->Desno;
			free(temp);
		}
		else
		{
			S = S->Lijevo;
			free(temp);
		}
		return S;
	}
}