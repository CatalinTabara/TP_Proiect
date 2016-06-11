#include<iostream>

typedef struct spect
{
	char *nume;
	int h1, m1;	//ora de incepere a spectacolului
	int h2, m2;	//ora de incheiere a spectacolului
	spect *urm;
};
spect *prim, *ultim;

void adaugare(int h_1,int m_1,int h_2,int m_2, char *x)
{
	spect *y = (spect*)calloc(1, sizeof(spect));
	if (prim == NULL)
	{
		prim = (spect*)calloc(1, sizeof(spect));

	}
}

void main()
{
	int n = 0;
	int h_1 = 0, m_1 = 0;
	int h_2 = 0, m_2 = 0;
	char x[1024];
	prim = NULL;
	ultim = NULL;
	printf("Dati nr de spectacole ");
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Dati ora de inceput, sfarsit si numele spectacolului");
		adaugare(h_1,m_1,h_2,m_2,x);
	}
}