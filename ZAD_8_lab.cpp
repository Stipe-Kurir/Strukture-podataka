#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 256




typedef struct Stablo* Direktorij;
typedef struct stog* Pozicija;



typedef struct Stablo {
	char name[MAX];
	Direktorij sibling;
	Direktorij child;
}Node;



typedef struct stog {
	Direktorij data;
	Pozicija next;
}Stog;




Direktorij Alokacija();
Pozicija AlokacijaStog();
void Meni();
void MDirektorij(Direktorij S,char ime[]);
void IspisDirektorija(Direktorij S);
void Push(Direktorij S, Pozicija P);
Direktorij Pop(Pozicija P);
Direktorij CDirektorij(Direktorij S, Pozicija P, char ime[]);




int main()
{
	 Direktorij ROOT;
	 Direktorij CURRENT;
	 ROOT = Alokacija();
	 CURRENT = ROOT;
	 int x = 0;
	 char temp[MAX];
	 Pozicija HEAD;
	 HEAD = AlokacijaStog();
	 strcpy(ROOT->name,"ROOT");  //naziv glavnog direkotrija koji nema braću!


	 printf("Nalazite se u ROOT direktoriju,on je prazan!\n");

	 while (x != 5)
	 {
		 Meni();
		 scanf("%d", &x);
		 switch (x)
		 {
		 case 1:
			 printf("Unesite naziv direktorija\n");
			 scanf("%s", temp);
			 MDirektorij(CURRENT, temp);
			 break;
		 case 2:
			 printf("Unesite ime direktorija:\n");
			 scanf("%s", temp);
			 CURRENT = CDirektorij(CURRENT, HEAD, temp); //Šaljemo trenutni direktorij u kojem se nalazimo,head element stoga,i naziv koji trazimo!
			 break;
		 case 3:
			 CURRENT = Pop(HEAD);
			 break;
		 case 4:
			 IspisDirektorija(CURRENT);
			 break;
		 default:
			 printf("Unijeli ste krivi broj!\n");
			 break;
		 }
	 }





	 return 0;
}



//Funkcija za alokaciju novog elementa u direktoriju!Vraća kreiran novi direkotrij!
Direktorij Alokacija()
{
	Direktorij novi;
	novi = (Direktorij)malloc(sizeof(Node));
	novi->child = NULL;
	novi->sibling = NULL;
	strcpy(novi->name, " ");
	return novi;

}


//Funkcija za alokaciju novog elementa na Stog!Ova nam funkcija služi za CDirekotrij gdje pushamo elemente(tipa direktorij) na stog!
Pozicija AlokacijaStog()
{
	Pozicija novi;
	novi = (Pozicija)malloc(sizeof(Stog));
	novi->next = NULL;
	novi->data = NULL;
	return novi;
}




void Meni()
{
	printf("######################################\n");
	printf("Odabir opcije:\n");
	printf("Pritisnitne broj 1 ako zelite md\n");
	printf("Pritisnite broj 2 ako zelite cd dir\n");
	printf("Pritisnite broj 3 ako zelite cd..\n");
	printf("Pritisnite broj 4 ako zelite dir\n");
	printf("Pritisnite broj 5 ako zelite izlaz\n");
	printf("######################################\n");

}




void MDirektorij(Direktorij S, char ime[]) //Funkcija za stvaranje direkorija!
{
	Direktorij novi = Alokacija();         //Poziv funkcije za alokaciju
	strcpy(novi->name, ime);
	if (S->child == NULL)                  //Provjeravamo dali direktorij ima dijete!
	{
		S->child = novi;                   //ako nema dijete onda novi direktorij postaje njegovo dijete!
		
	}
	else                                   //ako ima dijete onda postavljamo novi direktorij kao brata od tog djeteta!
	{
		
		S = S->child;
		if (S->sibling == NULL)            //Pošto novi direktorij stavaljamo kao brata njega stavljamo na kraj,odonoso kraj onog direktorija koji nema brata!  
		{
			S->sibling = novi;
		}
		else
		{
			while (S->sibling != NULL)
			{
				S = S->sibling;
			}

			S->sibling = novi;
		}
	}

}




void IspisDirektorija(Direktorij S)           //Funkcija za ispis direktorija!
{
	if (S->child == NULL)                     //Ako je direkotrij prazan ispiše se prazan direktorij!
	{
		printf("Prazan direktorij!\n");
    }
	else                                      //Ako nije prazan provjeravamo sa if-else petljom ima li jedno ili više djece te ispisujemo sve direkotrije! 
	{
		if (S->child->sibling == NULL)        //Provjera za jedno dijete i ispis tog jednog djeteta
		{
			printf("%s\n", S->child->name);
		}
		else
		{
			S = S->child;
			while (S->sibling != NULL)        
			{
				printf("%s\n", S->name);
				S = S->sibling;
			}
			printf("%s\n", S->name);        //triba pazit jer smo došli do zadnjeg ali ga nismo ispisali,pomoću ove linije ispišemo zadnjeg brata !
		}
	   
	}
}






void Push(Direktorij S, Pozicija P)    // funkcija kojom na stog pushamo direktorij u kojem se trenutno nalazimo!
{                                      //direktorij stavljamo na kraj stoga
	Pozicija novi;
	novi = AlokacijaStog();
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





Direktorij Pop(Pozicija P)       //Funkcija pop kojom vraćamo direktorij u kojem se nalazimo trenutno,a to je onaj koji je na zadnjoj poziciji u stogu!          
{
	Direktorij x;
	Pozicija temp;

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



Direktorij CDirektorij(Direktorij S, Pozicija P, char ime[])  //Funkcija za promjenu trenutnog direktorija u kojem se nalazimo
{
	Push(S, P);                 //Funkcija push,pushamo trenutni direktorij!
	Direktorij glavni = S;      //pamtimo glavni direktorij,ukoliko je ili direktorij prazan ili ne postoji neki direktorij u njemu da nam vrati glavni direktorij!

	if (S->child == NULL)         //Provjera jeli direktorij prazan
	{
		printf("Direktorij prazan\n");
	}
	else                         //ako nije onda pregledavamo njegovu djecu!
	{                           
		S = S->child;
		while (S->sibling != NULL)
		{
			if (!(strcmp(S->name, ime)))  //vrtimo dok nije isto ime!funckija strcmo vraća 0 ako su stringovi isti!
			{
				return S;
			}
			S = S->sibling;  
		}

		if (!(strcmp(S->name, ime)))  //nova if-else petlja za provjeru zadnjeg elementa jeli onaj trazeni!
		{
			return S;
		}
		else
		{
			printf("Ne postoji taj direktorij\n");
			return glavni;
		}
	}


}