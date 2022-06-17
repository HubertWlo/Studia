#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct liczba
{
	int cyfra;
	struct liczba *nast;
	struct liczba *pop;
	struct liczba *nast_lista;
	struct liczba *pop_lista;
}liczba;

liczba *head;
liczba *poczatek = NULL;
liczba *koniec = NULL;
liczba *nast_lista = NULL;
liczba *pop_lista = NULL;

int lista(int k)
{
	liczba *nowyElement;
	int cyfra;

	printf("Wylosowana cyfra: ");
	cyfra = (rand() % 1000) + 1;
	printf("%d\n", cyfra);
	printf("\n");

	nowyElement = (liczba*)malloc(sizeof(liczba));
	nowyElement->nast = NULL;
	nowyElement->pop = NULL;
	nowyElement->nast_lista = NULL;
	nowyElement->pop_lista = NULL;
	nowyElement->cyfra = cyfra;

	if (poczatek == NULL)
	{
		nowyElement->nast = nowyElement;
		nowyElement->pop = nowyElement;
		nowyElement->nast_lista = NULL;
		nowyElement->pop_lista = NULL;
		poczatek = nowyElement;
		koniec = nowyElement;
		head = nowyElement;
	}
	else
	{
		if (koniec->cyfra % k == 0)
		{
			koniec->nast_lista = nowyElement;
			koniec->nast = poczatek;
			nowyElement->pop_lista = koniec;
			
			nowyElement->nast = NULL;
			nowyElement->pop = NULL;
			poczatek = nowyElement;

		}
		else
		{
			nowyElement->pop_lista = NULL;
			koniec->nast = nowyElement;
		}		
		nowyElement->nast = poczatek;
		nowyElement->nast_lista = NULL;
		nowyElement->pop = koniec;
		poczatek->pop = nowyElement;
		koniec = nowyElement;

	}
	return 0;
}

void wypisz(liczba *wezel)
{
	printf("Poprzednia %d\t  ", wezel->pop->cyfra);
	printf("obecna %d  ", wezel->cyfra);
	printf("nastepna %d\t", wezel->nast->cyfra);
	printf("Adres %d\n", wezel);
}

void wyswietlWszystkie(int n)
{
	liczba *temp, *temp_dwa;
	int i;

	temp = head;
	temp_dwa = head;
	
	for(i = 0; i < n-1; i++)
	{
		wypisz(temp);
		//printf("%d\n", temp->cyfra);
		if(temp->nast_lista != NULL)
		{
			temp = temp->nast_lista;
			printf("Nowa lista\n");
			temp_dwa = temp;
		}
		else
		{
			temp = temp->nast;	
		}
	}
	wypisz(temp);
	//printf("%d\n", temp->cyfra);
}

void wyswietlWszystkiePrzeciwnie(int n)
{
	liczba *temp;
	int i;

	temp = head;
	
	for(i = 0; i < n; i++)
	{
		wypisz(temp);
		//printf("%d\n", temp->cyfra);
		if(temp->nast_lista != NULL)
		{
			temp = temp->nast_lista;
			//printf("Nowa lista\n");
			poczatek = temp;
		}
		else if(temp->nast_lista == NULL)
		{
			temp = temp->pop;	
		}
		if(temp == koniec)
		{
			while(temp->pop_lista == NULL)
			{
				wypisz(temp);
				//printf("%d\n", temp->cyfra);
				temp = temp->pop;
				i++;
			}
			while(temp->pop_lista != NULL)
			{
				temp = temp->pop_lista;
				temp = temp->pop;
			}
		}
	}
	
}

void wypiszKilka(int ile_elementow, int kierunek)
{
	if(kierunek == 1)
	{
		wyswietlWszystkie(ile_elementow);
	}
	else
	{
		wyswietlWszystkiePrzeciwnie(ile_elementow);
	}
}

void wypisz_wezly(int n)
{
	liczba *temp;
	int i;

	temp = head;
	
	for(i = 0; i < n-1; i++)
	{
		if(temp->nast_lista != NULL)
		{
			printf("Wezel: %d ", temp->cyfra);
			temp = temp->nast_lista;
			printf("%d\n", temp->cyfra);
		}
		else
		{
			temp = temp->nast;	
		}
	}
}

void wypisz_n_krag(int n, int ktoryKrag)
{
	liczba *temp;
	int i, liczbaKregow = 0;

	temp = head;
	
	for(i = 0; i < n-1; i++)
	{
		if(ktoryKrag == liczbaKregow)
		{
			printf("%d\n", temp->cyfra);
		}
		if(temp->nast_lista != NULL)
		{
			liczbaKregow++;
			temp = temp->nast_lista;
		}
		else
		{
			temp = temp->nast;	
		}
	}
}

void usun_liste(int n)
{
	liczba *temp;
	int i;

	temp = head;
	
	for(i = 0; i < n-1; i++)
	{
		if(temp->nast_lista != NULL)
		{
			temp = temp->nast_lista;
			free(temp->pop_lista);
		}
		else
		{
			temp = temp->nast;
			free(temp->pop);	
		}
		
	}
}

int wypisz_menu(){
	int dzialanie;
	system("cls");
	printf("Wpisz numer operacji ktora wykonac \n");
	printf("-------------------------------------- \n");
	printf("[0] Wyjscie z programu \n");
	printf("[1] Wyswietl wszystkie \n");
	printf("[2] Wyswietl n elementow \n");
	printf("[3] Dodaj element na koncu \n");
	printf("[4] Usun liste \n");
	printf("[5] Wypisz wezly \n");
	printf("[6] Wypisz n krag \n");
	printf("-------------------------------------- \n");
	printf("\nWybrana komenda: \n");
	scanf("%d", &dzialanie);
	return dzialanie;
}

int main()
{
	int i, n, k, dzialanie = -1, ile_elementow, kierunek, krag;
	
	printf("Podaj ile liczb wygenerowac: ");
	scanf("%d", &n);
	
	printf("Podaj liczbe k: ");
	scanf("%d", &k);

	for (i = 0; i < n; i++)
	{
		lista(k);
	}
	system("pause");
	while(dzialanie != 0){
		switch(dzialanie){
			case 0:	
			break;
			case 1:
				wyswietlWszystkie(n);
				system("pause");
			break;
			case 2:
				printf("Podaj ile elementow wyswietlic ");
				scanf("%d", &ile_elementow);
				printf("Wipsz 1 jesli wypisac zgodnie z ruchem wskazowek, -1 w przeciwnym ");
				scanf("%d", &kierunek);
				wypiszKilka(ile_elementow, kierunek);
				system("pause");
			break;
			case 3:
				n++;
				lista(k);
			case 4:
				usun_liste(n);
				system("pause");
			break;
			case 5:
				wypisz_wezly(n);
				system("pause");
			break;
			case 6:
				printf("Podaj ktory krag wypisac ");
				scanf("%d", &krag);
				wypisz_n_krag(n, krag);
				system("pause");
			break;
		}
		dzialanie = wypisz_menu();
	}

	//wyswietlWszystkie(n);
	printf("\n");

	return 0;
}

