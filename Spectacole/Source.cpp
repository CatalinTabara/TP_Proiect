#include<iostream>

typedef struct spect
{
	char *nume;
	int h1, m1;	//ora de incepere a spectacolului
	int h2, m2;	//ora de incheiere a spectacolului
	spect *urm;
	spect *prec;
};
spect *prim, *ultim;

void adaugare(int h_1,int m_1,int h_2,int m_2, char *x)
{
	spect *y = (spect*)calloc(1, sizeof(spect));
	y->h1 = h_1;
	y->h2 = h_2;
	y->m1 = m_1;
	y->m2 = m_2;
	y->nume = (char*)calloc(1, sizeof(strlen(x) + 1));
	strcpy(y->nume, x);
	if (prim == NULL)
	{
		prim = (spect*)calloc(1, sizeof(spect));
		prim = y;
		ultim = y;
		y->urm = 0;
		y->prec = 0;
	}
	else
	{
		ultim->urm = y;
		y->prec = ultim;
		y->urm = 0;
		ultim = y;
	}
}
void afisare()
{
	spect*y = (spect*)calloc(1, sizeof(spect));
	y = prim;
	int i = 1;
	while (y != NULL)
	{
		printf("Spectacolul nr %d \"%s\" incepe la ora %d:%d si se termina la ora %d:%d\n", i, y->nume, y->h1, y->m1, y->h2, y->m2);
		y = y->urm;
		i++;
	}
}

void orar(int h3, int m3, int h4, int m4)
{
	spect *y = (spect*)calloc(1, sizeof(spect));
	y = prim->urm;
	int ultim_h = 0, ultim_m = 0, i = 1;
	while (y != NULL)
	{
		if (((ultim_h * 60 + ultim_m) <= (y->h1 * 60 + y->m1)) && ((y->h1 * 60 + y->m1) >= (h3 * 60 + m3)) && ((y->h2 * 60 + y->m2)<=(h4*60+m4)))
		{
			printf("Spectacolul nr #%d cu titlul \"%s\" incepe la ora %d:%d si se incheie la ora %d:%d\n",i,y->nume,y->h1,y->m1,y->h2,y->m2);
			i++;
		}
		y = y->urm;
	}
}

void ordonare_sfarsit()
{
	spect *y = (spect*)calloc(1, sizeof(spect));
	spect* n = (spect*)calloc(1, sizeof(spect));
	int h1a = 0, h2a = 0, m1a = 0, m2a = 0;
	char *p;
	y = prim;
	while (y != NULL)
	{
		n = y;
		while (n != NULL)
		{
			if ((y->h2 * 60 + y->m2) > (n->h2 * 60 + n->m2))
			{
				p = (char*)calloc(1, sizeof(strlen(y->nume) + 1));
				strcpy(p, y->nume);
				h1a = y->h1;
				h2a = y->h2;
				m1a = y->m1;
				m2a = y->m2;

				y->h1 = n->h1;
				y->h2 = n->h2;
				y->m1 = n->m1;
				y->m2 = n->m2;
				y->nume = (char*)calloc(1, sizeof(strlen(n->nume) + 1));
				strcpy(y->nume, n->nume);

				n->h1 = h1a;
				n->h2 = h2a;
				n->m1 = m1a;
				n->m2 = m2a;
				n->nume = (char*)calloc(1, sizeof(strlen(p) + 1));
				strcpy(n->nume, p);
			}
			n = n->urm;
		}
		y = y->urm;
	}
}

void main()
{
	int n = 0;
	int h_1 = 0, m_1 = 0;
	int h_2 = 0, m_2 = 0;

	int h_3 = 0, m_3 = 0;
	int h_4 = 0, m_4 = 0;
	char x[1024];
	prim = NULL;
	ultim = NULL;
	printf("Dati nr de spectacole ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Dati ora de inceput, sfarsit si numele spectacolului");
		scanf("%d %d %d %d",&h_1,&m_1,&h_2,&m_2);
		gets(x);
		gets(x);
		printf("%s", x);
		adaugare(h_1,m_1,h_2,m_2,x);
	}
	/*afisare();
	printf("Dati orele vizionarii\n");
	printf("Ora inceput: ");
	scanf("%d", &h_3);
	printf("\nMinut inceput: ");
	scanf("%d", &m_3);
	printf("\nOra sfarsit: ");
	scanf("%d", &h_4);
	printf("Minut sfarsit: ");
	scanf("%d", &m_4);*/
	printf("\n\n\n\n\n\n\n\n");
	ordonare_sfarsit();
	afisare();
}