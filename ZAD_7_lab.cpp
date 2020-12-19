#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


typedef struct lista* Pozicija;

struct lista {
	int EL;
	Pozicija next;
};



void Push(Pozicija P,int x);
int Pop(Pozicija P);
int Provjera(char x);
int Racunaj(int x, int y,char znak);



int main()
{
	char temp[100];
	int op1, op2;
	int rez;


	struct lista HEAD;
	HEAD.next = NULL;

	FILE* datoteka;
	datoteka = fopen("Postfix.txt", "r");
	if (datoteka == NULL)
	{
		printf("Problem sa datotekom!");
		return 0;
	}

	
	while (!feof(datoteka))
	{
		fscanf(datoteka,"%s",temp); //skenira string do razmaka

        if (Provjera(temp[0]))  //Provjeravam jeli u skeniranom stringu prvi procitan znak broj,ako jest pusham(cijeli string jer ako mu je prva znamenka broj onda je ostatak stringa procitanog broj) ga na stog,ako ne onda vršimo matrematičku operaciju! 
		{
			Push(&HEAD,atoi(temp)); //atoi pretvara procitani string u int!
		}
		else
		{
			op1 = Pop(&HEAD);
			op2 = Pop(&HEAD);
			rez = Racunaj(op2, op1, temp[0]);
			Push(&HEAD, rez);
		}
		
	}

	printf("Rezultat postfix izraza je:%d\n", Pop(&HEAD));


	fclose(datoteka);
	return 0;
}






void Push(Pozicija P,int x)    //Unosi novi element na kraj 
{
	Pozicija novi;
	
	while (P->next != NULL)
	{
		P = P->next;
	}

	novi = (Pozicija)malloc(sizeof(struct lista));
	novi->EL = x;
	novi->next = P->next;
	P->next = novi;

}







int Pop(Pozicija P)      //Funkcija Pop vraća zadnji uneseni element 
{
	int x;
	Pozicija temp;

	if (P->next == NULL)
	{
		return 0;
	}

	while (P->next->next != NULL)
	{
		P = P->next;
	}
	
	x = P->next->EL;
	temp = P->next;
	P->next = temp->next;
	free(temp);
	return x;

}






int Provjera(char x)   //Funkcija koja provjerava jeli pročitani znak broj!
{
	if (x >= '0' && x <= '9')
		return 1;
	else
		return 0;
}





int Racunaj(int x, int y,char znak)  //Funkcija koja obavlja određenu matematičku operaciju!
{

	switch (znak)
	{
	case '+':
	    return x + y;
	    break;
    case '-':
		return x - y;
		break;
	case'*':
		return x * y;
		break;
	case'/':
		return x / y;
		break;
	default:
		printf("Krivo unesen znak u Postfix izrazu!\n");
		return 0;
		break;
    }


}