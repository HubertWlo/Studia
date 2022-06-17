#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct kolejka
{
	int cyfra;
	int priorytet;
	struct kolejka *nast;
	struct kolejka *pop;
}kolejka;

kolejka *kol1, *kol2, *kol3;

kolejka *pocz1 = NULL;
kolejka *pocz2 = NULL;
kolejka *pocz3 = NULL;

int dlugosc = 0, dlugosc1 = 0, dlugosc2 = 0, dlugosc3 = 0;

void add(int numer_kolejki)
{
	kolejka *nowyElement;
	int cyfra, priorytet;
	printf("Dodawanie do kolejki nr. %d\n", numer_kolejki);
	printf("Wylosowana cyfra: ");
	cyfra = (rand() % 100) + 1;
	printf("%d\n", cyfra);
	printf("\n");
	printf("Wylosowana priorytet: ");
	priorytet = (rand() % dlugosc) + 1;
	printf("%d\n", priorytet);
	printf("\n");

	nowyElement = (kolejka*)malloc(sizeof(kolejka));
	nowyElement->nast = NULL;
	nowyElement->pop = NULL;
	nowyElement->cyfra = cyfra;
	nowyElement->priorytet = priorytet;
	
	if(numer_kolejki == 1)
	{
		if(pocz1 == NULL)
		{
			nowyElement->nast = nowyElement;
			nowyElement->pop = nowyElement;
			pocz1 = nowyElement;
		}
		else
		{
			nowyElement->nast = pocz1;
			nowyElement->pop = pocz1->pop;
			pocz1->nast = nowyElement;
		}
		dlugosc1++;
	}
	if(numer_kolejki == 2)
	{
		if(pocz2 == NULL)
		{
			nowyElement->nast = nowyElement;
			nowyElement->pop = nowyElement;
			pocz2 = nowyElement;
		}
		else
		{
			nowyElement->pop = pocz2;
			nowyElement->nast = pocz2->nast;
			pocz2->nast = nowyElement;
		}
		dlugosc2++;
	}
	if(numer_kolejki == 3)
	{
		if(pocz3 == NULL)
		{
			nowyElement->nast = nowyElement;
			nowyElement->pop = nowyElement;
			pocz3 = nowyElement;
		}
		else
		{
			nowyElement->pop = pocz3;
			nowyElement->nast = pocz3->nast;
			pocz3->nast = nowyElement;
		}
		dlugosc3++;
	}
	
}

void dodaj(int numer_kolejki, int priorytet)
{
	kolejka *nowyElement;
	int cyfra;
	printf("Dodawanie do kolejki nr. %d\n", numer_kolejki);
	printf("Wylosowana cyfra: ");
	cyfra = (rand() % 100) + 1;
	printf("%d\n", cyfra);
	printf("\n");

	nowyElement = (kolejka*)malloc(sizeof(kolejka));
	nowyElement->nast = NULL;
	nowyElement->pop = NULL;
	nowyElement->cyfra = cyfra;
	nowyElement->priorytet = priorytet;
	
	if(numer_kolejki == 1)
	{
		if(pocz1 == NULL)
		{
			nowyElement->nast = nowyElement;
			nowyElement->pop = nowyElement;
			pocz1 = nowyElement;
		}
		else
		{
			nowyElement->nast = pocz1;
			nowyElement->pop = pocz1->pop;
			pocz1->nast = nowyElement;
		}
		dlugosc1++;
	}
	if(numer_kolejki == 2)
	{
		if(pocz2 == NULL)
		{
			nowyElement->nast = nowyElement;
			nowyElement->pop = nowyElement;
			pocz2 = nowyElement;
		}
		else
		{
			nowyElement->pop = pocz2;
			nowyElement->nast = pocz2->nast;
			pocz2->nast = nowyElement;
		}
		dlugosc2++;
	}
	if(numer_kolejki == 3)
	{
		if(pocz3 == NULL)
		{
			nowyElement->nast = nowyElement;
			nowyElement->pop = nowyElement;
			pocz3 = nowyElement;
		}
		else
		{
			nowyElement->pop = pocz3;
			nowyElement->nast = pocz3->nast;
			pocz3->nast = nowyElement;
		}
		dlugosc3++;
	}
	
}

void obsluga()
{
	kolejka *temp;
	int i;
	if(pocz1 != NULL && pocz2 != NULL && pocz3 != NULL)
	{
		if(pocz1->priorytet > pocz2->priorytet && pocz1->priorytet > pocz3->priorytet)
		{
			temp = pocz1;
			pocz1 = pocz1->nast;
			dlugosc1--;
		}
		else if(pocz2->priorytet > pocz3->priorytet)
		{
			temp = pocz2;
			pocz2 = pocz2->nast;
			dlugosc2--;
		}
		else
		{
			temp = pocz3;
			pocz3 = pocz3->nast;
			dlugosc3--;
		}
	}
	else if(pocz1 == NULL && pocz2 == NULL)
	{
		temp = pocz3;
		pocz3 = pocz3->nast;
		dlugosc3--;
	}
	else if(pocz1 == NULL && pocz3 == NULL)
	{
		temp = pocz2;
		pocz2 = pocz2->nast;
		dlugosc3--;
	}
	else if(pocz2 == NULL && pocz3 == NULL)
	{
		temp = pocz1;
		pocz1 = pocz1->nast;
		dlugosc1--;
	}
	else if(pocz1 == NULL)
	{
		if(pocz2->priorytet > pocz3->priorytet)
		{
			temp = pocz2;
			pocz2 = pocz2->nast;
			dlugosc2--;
		}
		else
		{
			temp = pocz3;
			pocz3 = pocz3->nast;
			dlugosc3--;
		}
	}
	else if(pocz2 == NULL)
	{
		if(pocz1->priorytet > pocz3->priorytet)
		{
			temp = pocz1;
			pocz1 = pocz1->nast;
			dlugosc1--;
		}
		else
		{
			temp = pocz3;
			pocz3 = pocz3->nast;
			dlugosc3--;
		}
	}
	else if(pocz3 == NULL)
	{
		if(pocz2->priorytet > pocz1->priorytet)
		{
			temp = pocz2;
			pocz2 = pocz2->nast;
			dlugosc2--;
		}
		else
		{
			temp = pocz1;
			pocz1 = pocz1->nast;
			dlugosc1--;
		}
	}
	if(dlugosc1 == 0) printf("Kolejka 1 - EMPTY\n");
	if(dlugosc2 == 0) printf("Kolejka 2 - EMPTY\n");
	if(dlugosc3 == 0) printf("Kolejka 3 - EMPTY\n");
	free(temp);
	for (i = 0; i < 3; i++)
	{
		if(dlugosc3 < dlugosc2 && dlugosc3 < dlugosc1)
		{
			if(dlugosc3 < dlugosc)
			{
				add(3); 
			}
			else printf("Kolejka 3 - WAIT\n");
		}
		else if(dlugosc2 < dlugosc1)
		{
			if(dlugosc2 < dlugosc)
			{
				add(2); 
			}
			else printf("Kolejka 2 - WAIT\n");
		}
		else
		{
			if(dlugosc1 < dlugosc)
			{
				add(1); 
			} 
			else printf("Kolejka 1 - WAIT\n");
		}
	}
	system("pause");
}

void zawartosc(int numer_kolejki)
{
	int i;
	kolejka *temp;
	if(numer_kolejki == 1)
	{
		temp = pocz1;
		printf("Kolejka pierwsza: \n");
		for(i = 0; i<dlugosc1; i++)
		{
			printf("Cyfra %d, waga %d\n", temp->cyfra, temp->priorytet);
			temp = temp->nast;
		}
	}
		if(numer_kolejki == 2)
		{
		temp = pocz2;
		printf("Kolejka druga: \n");
		for(i = 0; i<dlugosc2; i++)
		{
			printf("Cyfra %d, waga %d\n", temp->cyfra, temp->priorytet);
			temp = temp->nast;
		}
	}
	if(numer_kolejki == 3)
		{
		temp = pocz3;
		printf("Kolejka trzecia: \n");
		for(i = 0; i<dlugosc3; i++)
		{
			printf("Cyfra %d, waga %d\n", temp->cyfra, temp->priorytet);
			temp = temp->nast;
		}
	}
}

void wypisz_wyszstko()
{
	zawartosc(1);
	zawartosc(2);
	zawartosc(3);
}

int ile_w_kolejce(int numer_kolejki)
{
	kolejka *temp;
	if(numer_kolejki == 1)
	{
		return dlugosc1;
	}
	if(numer_kolejki == 2)
	{
		return dlugosc2;
	}
	if(numer_kolejki == 3)
	{
		return dlugosc3;
	}
}

void dodaj_do_kolejki(int numer_kolejki, int waga)
{
	if(numer_kolejki == 1)
	{
		if(dlugosc1 < dlugosc)
		{
			dodaj(1, waga);
		}
		else
		{
			printf("Kolejka %d zapelniona!", numer_kolejki);
		}
	}
	if(numer_kolejki == 2)
	{
		if(dlugosc2 < dlugosc)
		{
			dodaj(2, waga);
		}
		else
		{
			printf("Kolejka %d zapelniona!", numer_kolejki);
		}
	}
	if(numer_kolejki == 3)
	{
		if(dlugosc3 < dlugosc)
		{
			dodaj(3, waga);
		}
		else
		{
			printf("Kolejka %d zapelniona!", numer_kolejki);
		}
	}
}

int wypisz_menu()
{
	int dzialanie;
	system("cls");
	printf("Wpisz numer operacji ktora wykonac \n");
	printf("-------------------------------------- \n");
	printf("[0] Wyjscie z programu \n");
	printf("[1] Dodaj do kolejki \n");
	printf("[2] Obsluga \n");
	printf("[3] Wypisz zawartosc kolejki \n");
	printf("[4] Wypisz ile elementow w kolejce \n");
	printf("[5] Wypisz wszystko \n");
	printf("-------------------------------------- \n");
	printf("\nWybrana komenda: \n");
	scanf("%d", &dzialanie);
	return dzialanie;
}

int main()
{
	int i, n, waga, dzialanie = -1;
	
	printf("Podaj dlugosc buforu: ");
	scanf("%d", &dlugosc);

	printf("Podaj ile liczb wygenerowac: ");
	scanf("%d", &n);
	
	for (i = 0; i < n; i++)
	{
		if(dlugosc3 < dlugosc2 && dlugosc3 < dlugosc1)
		{
			add(3);
		}
		else if(dlugosc2 < dlugosc1)
		{
			add(2);
		}
		else
		{
			add(1);
		}
	}
	system("pause");
	while(dzialanie != 0)
	{
		switch(dzialanie)
		{
			case 0:	
			break;
			case 1:
				printf("Podaj numer kolejki: ");
				scanf("%d", &n);
				printf("Podaj wage: ");
				scanf("%d", &waga);
				dodaj_do_kolejki(n, waga);
				system("pause");
			break;
			case 2:
				obsluga();
			break;
			case 3:
				printf("Podaj numer kolejki: ");
				scanf("%d", &n);
				zawartosc(n);
				system("pause");
			break;
			case 4:
				printf("Podaj numer kolejki: ");
				scanf("%d", &n);
				printf("W kolejce nr. %d jest %d liczb\n",n , ile_w_kolejce(n));
				system("pause");
			break;
			case 5:
				wypisz_wyszstko();
				system("pause");
			break;
		}
		dzialanie = wypisz_menu();
	}
	printf("\n");

	return 0;
}

