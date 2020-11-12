#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct lista* Pozicija;

struct lista
{
	int br;
	int exp;
	Pozicija next;

};



void UnosSortirani(int k, int exp, Pozicija P);
void Ispis(Pozicija P);
void sumaPolinoma(Pozicija P, Pozicija Q,Pozicija S);
void umnPolinoma(Pozicija P, Pozicija Q, Pozicija S);



int main()
{
	struct lista P1;
	struct lista P2;
	struct lista REZ1;
	struct lista REZ2;
	
	int broj1=1;
	int broj2 = 1;
    int  exponent=1;

	P1.next = NULL;
	P2.next = NULL;
	REZ1.next = NULL;
	REZ2.next = NULL;

	printf("Unos prvog polinoma!\n");

	while (broj1!=0)
	{
		
		printf("Unesite broj:");
		scanf("%d", &broj1);
		if (broj1 == 0)
			break;
		printf("Unesite exp:");
		scanf("%d", &exponent);
		
		UnosSortirani(broj1, exponent, &P1);

		printf("ako zelite prikiniti unos pritisnite 0!\n");
	}
	
	Ispis(P1.next);

	printf("Unos drugog polinoma!\n");

	while (broj2 != 0)
	{
		printf("Unesite broj:");
		scanf("%d", &broj2);
		if (broj2 == 0)
			break;
		printf("Unesite exp:");
		scanf("%d", &exponent);

		UnosSortirani(broj2, exponent, &P2);
		printf("ako zelite prikiniti unos pritisnite 0!\n");

	}


	Ispis(P2.next);



  sumaPolinoma(P1.next, P2.next,&REZ1);

  printf("Ispis zbroja dvaju polinoma!\n");

  Ispis(REZ1.next);

  umnPolinoma(P1.next, P2.next, &REZ2);
  
  printf("Ispis umnoska polinoma!\n");
  Ispis(REZ2.next);



}

void UnosSortirani(int k, int ex, Pozicija P)  //Sortiran unos od najmanjeg prema najvecem exp!!
{
	Pozicija q;

	while (P->next != NULL && P->next->exp < ex)
	{
		P = P->next;
	}

	q = (Pozicija)malloc(sizeof(struct lista));
	q->br = k;
	q->exp = ex;
	q->next = P->next;
	P->next = q;

}




void Ispis(Pozicija P)
{
	while (P != NULL)
	{
		printf("%d  %d   %d  %d\n", P->br, P->exp, P->next);
		P = P->next;
	}

}




void sumaPolinoma(Pozicija P, Pozicija Q, Pozicija S)   //Funkcija za zbrajanje dvaju polinoma!!
{
	Pozicija temp=NULL;
	int zbroj=0;
	
	while (P != NULL && Q != NULL)
	{
		if (P->exp < Q->exp)
		{
			UnosSortirani(Q->br, Q->exp, S);
			Q = Q->next;

		}
		else if (P->exp > Q->exp)
		{
			UnosSortirani(P->br, P->exp, S);
			P = P->next;
		}
		else
		{
			zbroj = P->br + Q->br;
			UnosSortirani(zbroj, P->exp, S);
			P = P->next;
			Q = Q->next;
		}
}

	if (P != NULL)
		temp = P;
	else
		temp = Q;


	while (temp != NULL)
	{
		UnosSortirani(temp->br, temp->exp, S);
		temp = temp->next;
	}


}

void umnPolinoma(Pozicija P, Pozicija Q, Pozicija S)   //Funkcija za mnozenje dvaju polinoma!!
{
	Pozicija temp=NULL;
	int umn = 1;

	while (P != NULL && Q != NULL)
	{
		if (P->exp == Q->exp)
		{
			umn = P->br * Q->br;
			UnosSortirani(umn, P->exp, S);
			P = P->next;
			Q = Q->next;
		}
		else if (P->exp > Q->exp)
		{
			UnosSortirani(P->br, P->exp, S);
			P = P->next;
		}
		else
		{
			UnosSortirani(Q->br, Q->exp, S);
			Q = Q->next;
		}
	}

	if (P != NULL)
		temp = P;
	else
		temp = Q;


	while (temp != NULL)
	{
		UnosSortirani(temp->br, temp->exp, S);
		temp = temp->next;
	}


}


