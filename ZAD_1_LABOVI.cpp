#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>



typedef struct {
	char ime[100];
	char prezime[100];
	double bodovi;
}student;

int main() 
{


	FILE* ptr;
	student* Osoba=NULL;  //Stavia si NULL jer realociraš memoriju!!PAZI!!
	char im[100];
	char prez[100];
	double bod;
	double rel_bod[100];
	double uk_bod;
	int i = 0;
	int j = 0;
	int brojac = 0;
	char ch;

	ptr = fopen("Student.txt", "r");

	printf("KOliko ima ukupno bodova u kolokviju: ");
	scanf_s("%f", &uk_bod);

	while (fgetc(ptr) != '\n') {}  //Preskočia si redak u kojem piše ime,prezime,bodovi!!

	while (1)
	{
		brojac++;
		Osoba = (student*)realloc(Osoba, brojac * sizeof(student));
       
		fscanf(ptr, "%s %s %f", im, prez, &bod);

		strcpy(Osoba[j].ime, im);
		strcpy(Osoba[j].prezime, prez);
		Osoba[j].bodovi = bod;

		j++;
		if (feof(ptr))
			break;
	}

	fclose(ptr);

	for (i = 0; i < brojac; i++)
	{
		printf("Ime %d. studenta je:%s\t", i + 1, Osoba[i].ime);
		printf("Prezime %d. studenta je:%s\t", i + 1, Osoba[i].prezime);
		printf("Bodovi: %f\t", Osoba[i].bodovi);
		rel_bod[i] = ((Osoba[i].bodovi / uk_bod) * 100);
		printf("Relativni bodovi: %f\n", rel_bod[i]);

	}

	return 0;
}