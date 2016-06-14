#include <windows.h>
#include "resource.h"
#include<iostream>

#define button_1		101
#define button_2		102
#define button_3		103
#define button_4		104
#define IDC_MAIN_BUTTON	105		// Button identifier
#define IDC_MAIN_EDIT	106		// Edit box identifier

HWND hEdit;

HINSTANCE hInst;
bool window2closed = false;
const char g_szClassName[] = "myWindowClass";
int cmd;
WNDCLASSEX wc2;
HWND b1, b2, b3, b4, c1, adag, sterg, interv,afis;
char y[1024],z[1024],h1[7],h2[7];
int nr;
FILE *f = fopen("text.txt", "w");
typedef struct spect
{
	char *nume;
	int h1, m1;	//ora de incepere a spectacolului
	int h2, m2;	//ora de incheiere a spectacolului
	spect *urm;
	spect *prec;
};
spect *prim, *ultim;

void formare_lista(char* nume,char *inceput,char *sfarsit);

void stergere(char *nume);

void afisare();

void AppendText(HWND hEditWnd, LPCTSTR Text);

int verificare(char *nume,int &h_1, int &m_1);


LRESULT CALLBACK interval(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK adaugare(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK sterge(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



//LRESULT CALLBACK afisaz(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	cmd = nCmdShow;
	bool endprogram = false;
	hInst = hInstance;
	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	/*
	wc2.cbSize = sizeof(WNDCLASSEX);
	wc2.style = 0;
	wc2.lpfnWndProc = WndProc;
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = hInstance;
	wc2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc2.lpszMenuName = NULL;
	wc2.lpszClassName = g_szClassName;
	wc2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	*/

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Organizator spectacole",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 380,
		NULL, NULL, hInstance, NULL);
	
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;


	//fereastra 2	
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_CREATE:
	{
					  char buff[] = "Adaugare spectacol";
					  					 
					  b1 = CreateWindow("BUTTON", buff, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  50, 100, 140, 100, hwnd, (HMENU)button_1, NULL, NULL);

					  b2 = CreateWindow("BUTTON", "Interval orar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  200, 100, 140, 100, hwnd, (HMENU)button_2, NULL, NULL);

					  b3 = CreateWindow("BUTTON", "Stergere Spectacol", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  350, 100, 140, 100, hwnd, (HMENU)button_3, NULL, NULL);

					  b4 = CreateWindow("BUTTON", "Afisare Spectacole", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  500, 100, 140, 100, hwnd, (HMENU)button_4, NULL, NULL);
					
					  break;
	}

	case WM_CLOSE:
	{
					 DestroyWindow(hwnd);
					 break; 
	}

	case WM_DESTROY:
	{				PostQuitMessage(0);
					break; 
	}

	case WM_COMMAND:
	{
					   int wmId = LOWORD(wParam);
					   int wmEvent = HIWORD(wParam);

					   switch (wmId)
					   {
					   case button_1:
					   {
										adag = (HWND)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)adaugare);
										ShowWindow(adag,10);
										UpdateWindow(adag);
										break;
					   }

					   case button_2:{
										 interv = (HWND)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, (DLGPROC)interval);
										 break;
					   }

					   case button_3:
					   {
										 sterg = (HWND)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)sterge);
										 break;
					   }

					   case button_4:
					   {
										//afis = (HWND)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)afisaz);
										 break;
					   }

					   }
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK adaugare(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int ora_i = NULL, m_i = NULL, ora_s = NULL, m_s = NULL;
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK12)
		{
			GetDlgItemText(hwnd, IDC_EDIT1, y, 1024);
			GetDlgItemText(hwnd, IDC_EDIT2, h1, 7);
			verificare(h1, ora_i, m_i);
			GetDlgItemText(hwnd, IDC_EDIT4, h2, 7);
			verificare(y, ora_s, m_s);
			formare_lista(y, h1, h2);
			if (verificare(h2, ora_s, m_s) == 1 || verificare(h2, ora_i, m_i) == 1){
				EndDialog(hwnd, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else MessageBox(NULL, "Orele introduse nu sunt corecte!", "Eroare", MB_OK);
			
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK sterge(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			GetDlgItemText(hwnd, IDC_EDIT1, y, 1024);
			stergere(y);
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK interval(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int ora_i = NULL, m_i = NULL, ora_s = NULL, m_s = NULL;
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
	{

						  return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)	{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK3){
			GetDlgItemText(hwnd, IDC_EDIT3, y, 1024);
			if (verificare(y,ora_i,m_i) == 0) MessageBox(NULL, "A dat handicapatul ala cu viteza", "Eroare ba boule", MB_OK);			
		}
		if (LOWORD(wParam) == IDOK2){
			GetDlgItemText(hwnd, IDC_EDIT5, z, 1024);
			if (verificare(z,ora_s,m_s) == 0) MessageBox(NULL, "A dat handicapatul ala cu viteza", "Eroare ba boule", MB_OK);
			}
		if (LOWORD(wParam) == IDOK){
			if (ora_i == NULL || m_i == NULL || ora_s == NULL || m_s == NULL){
				MessageBox(NULL, "A dat handicapatul ala cu viteza", "Eroare ba boule", MB_OK);	
			}
			 else if ((ora_i == ora_s) && (m_i>m_s)){
				 MessageBox(NULL, "A dat handicapatul ala cu viteza!", "Eroare ba boule!", MB_OK);
			 }
			 else {

				 EndDialog(hwnd, LOWORD(wParam));
				 return (INT_PTR)TRUE;
				}
		}
		break;
	}
	return (INT_PTR)FALSE;
}

/*
LRESULT CALLBACK afisaz(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
	{
						  spect *y = (spect*)calloc(1, sizeof(spect));
						  y = prim->urm;
						  int ultim_h = 0, ultim_m = 0, i = 1;
						  while (y != NULL)
						  {
							  if (((ultim_h * 60 + ultim_m) <= (y->h1 * 60 + y->m1)) && ((y->h1 * 60 + y->m1) >= (h3 * 60 + m3)) && ((y->h2 * 60 + y->m2) <= (h4 * 60 + m4)))
							  {
								  printf("Spectacolul nr #%d cu titlul \"%s\" incepe la ora %d:%d si se incheie la ora %d:%d\n", i, y->nume, y->h1, y->m1, y->h2, y->m2);
								  i++;
							  }
							  y = y->urm;
						  }
						  return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
*/

void AppendText(HWND hEditWnd, LPCTSTR Text)
{
	int idx = GetWindowTextLength(hEditWnd);
	SendMessage(hEditWnd, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
	SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)Text);
}

/*
void print_traseu(HWND hEdit, spect *p)
{
	if (p != NULL)
	{
		AppendText(hEdit, TEXT(strcat(p->nume, "\n")));
		print_traseu(hEdit, p->left);
		print_traseu(hEdit, p->right);
	}
}*/

void formare_lista(char *nume,char *inceput,char *sfarsit)
{
	int i = 0, h_1 = 0, h_2 = 0, m_1 = 0, m_2 = 0;
	//SCHIMBARE CU VERIFICARE(STRING,ORA,MINUT)
	verificare(inceput, h_1, m_1);

	verificare(sfarsit, h_2, m_2);
	if (verificare(inceput, h_1, m_1) == 1 && verificare(sfarsit, h_2, m_2) == 1){
		spect *y = (spect*)calloc(1, sizeof(spect));
		y->h1 = h_1;
		y->h2 = h_2;
		y->m1 = m_1;
		y->m2 = m_2;
		y->nume = (char*)calloc(1, sizeof(strlen(nume) + 1));
		strcpy(y->nume, nume);
		if (prim == NULL){
			prim = (spect*)calloc(1, sizeof(spect));
			prim = y;
			ultim = y;
			y->urm = 0;
			y->prec = 0;
		}
		else{
			ultim->urm = y;
			y->prec = ultim;
			y->urm = 0;
			ultim = y;
		}
	}
}


void afisare()
{
	spect*y = (spect*)calloc(1, sizeof(spect));
	y = prim;
	int i = 1;
	while (y != NULL)
	{
		fprintf(f, "%d %d %d %d", y->h1, y->m1, y->h2, y->m2);
		//fprintf(f,"Spectacolul nr %d \"%s\" incepe la ora %d:%d si se termina la ora %d:%d\n", i, y->nume, y->h1, y->m1, y->h2, y->m2);
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

void stergere(char *nume)
{
	spect *y = (spect*)calloc(1, sizeof(spect));
	y = prim;
	while (y != NULL)
	{
		if (strcmp(y->nume, nume) == 0){
			y->prec->urm=y->urm;
			y->urm->prec=y->prec;
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

int verificare(char *y,int &h_1,int &m_1)
{
	char *p;
	int i = 0;
	p = strtok(y, ":");
	while (p != NULL)
	{
		if (i == 0){
			h_1 = atoi(p);
			i++;
		}
		else if (i == 1){
			m_1 = atoi(p);
		}
		p = strtok(NULL, "\n");
	}
	if (h_1 > 24 || h_1<0 || m_1>59 || m_1 < 0){
		return 0;
	}
	return 1;
}

/*
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
	scanf("%d", &m_4);
	printf("\n\n\n\n\n\n\n\n");
	ordonare_sfarsit();
	afisare();
}*/