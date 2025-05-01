#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define MIDDLE_X 60
#define MIDDLE_Y 14

#define MAXPAR 10
#define MAXCAR 10
#define MAXFILA 8
#define MAXCOLUMNA 21

char paraules_clau [MAXPAR][MAXCAR] = {{"CALIU"}, {"SABOR"}, {"REPTE"}, {"AMOR"}, {"MUSICA"}, {"RITME"}, {"LLUNY"}, {"ASTRE"}, {"TRES"}, {"TETRIS"}};
char taula [MAXFILA][MAXCOLUMNA];
int i_paraules = 0, i_caracters = 0, fila = 0, columna = 0;
char lletra = '\0', tecles = '\0';
int punts = 0;
int x = 0, y = 0;

void mygotoxy(int x,int y);
void SetColor2();
void HideCursor();
void maximitzar_finestra();
void dibuixa_titol();
void tauler();
void inicialitzar_tauler();
void mostrar_paraules();
void randomitzador();
void puntuacio();
void mostrar_lletres();
void buscar_paraules();
int final();
void notificacions();
void borrar_notificacions();
void notificacio_fi();
void mostrar_array();

int main (void) {

    HideCursor();
    maximitzar_finestra();
    dibuixa_titol();
    tauler();
    inicialitzar_tauler();
    mostrar_paraules();
    do {
        randomitzador();
        puntuacio();
        mostrar_lletres();
        buscar_paraules();
    } while (!final());
    notificacio_fi();
    //mostrar_array();

    mygotoxy(0,35);
    return 0;
}

void mygotoxy(int x,int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void SetColor2(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

void maximitzar_finestra() {
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_SPACE,0x39,0,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
    keybd_event(VK_SPACE,0x39,KEYEVENTF_KEYUP,0);
    keybd_event(0x58,0x47,0,0);
    keybd_event(0x58,0x47,KEYEVENTF_KEYUP,0);
}

void dibuixa_titol() {
    FILE *f1 = fopen ("presenta.txt","rt");
    char c1;

    SetColor2(LIGHTGREEN,BLACK);
    x = MIDDLE_X; y = MIDDLE_Y;
    while (!feof(f1)) {
        mygotoxy (x,y);
        c1 = fgetc(f1);

        if (c1 == '\n') {
            Sleep (150);
            y++;
            x = MIDDLE_X;
        }
        else {
            x++;
        }
        putchar (c1);
    }

    mygotoxy (MIDDLE_X + 27, y + 4);
    SetColor2(LIGHTCYAN,BLACK);
    Sleep (200);
    printf ("Fet per: Andreu Niso Sevilla");
    mygotoxy (MIDDLE_X + 25, y + 12);
    SetColor2(WHITE,BLACK);
    Sleep (500);
    printf ("Prem UNA TECLA per a continuar...");
    getch();
    system("cls");

    fclose (f1);
}

/**SEGUIT D'ORDRES QUE MOSTREN TOT EL TAULER
ES PODRIA FER AMB UN FITXER .TXT COM LA FUNCI�
DE DIBUIXA_TITOL, PERO AL SER ASCII EXT�S
EL COMPILADOR NO POT MOSTRAR-HO**/
void tauler() {

    x = 10; y = 10;
    mygotoxy (x,y);

    SetColor2(WHITE,BLACK);
    printf ("%c", 218);
    for (columna = 0; columna < MAXCOLUMNA; columna++) {
        printf ("%c", 196);
        printf ("%c", 196);
        printf ("%c", 196);
        if (columna == MAXCOLUMNA - 1) {
            printf ("%c\n", 191);
        } else {
            printf ("%c", 194);
        }
    }

    for (fila = 1; fila < MAXFILA; fila++) {
        y++;
        mygotoxy (x,y);
        for (columna = 0; columna <= MAXCOLUMNA; columna++) {
            printf ("%c   ", 179);
        }
        y++;
        mygotoxy (x,y);
        printf ("%c", 195);
        for (columna = 0; columna < MAXCOLUMNA; columna++) {
            printf ("%c", 196);
            printf ("%c", 196);
            printf ("%c", 196);
            if (columna == MAXCOLUMNA - 1) {
                printf ("%c\n", 180);
            } else {
                printf ("%c", 197);
            }
        }
        if (fila == MAXFILA - 1) {
            y++;
            mygotoxy (x,y);
            for (columna = 0; columna <= MAXCOLUMNA; columna++) {
                printf ("%c   ", 179);
            }
            y++;
            mygotoxy (x,y);
            printf ("%c", 192);
            for (columna = 0; columna < MAXCOLUMNA; columna++) {
                printf ("%c", 196);
                printf ("%c", 196);
                printf ("%c", 196);
                if (columna == MAXCOLUMNA - 1) {
                    printf ("%c\n", 217);
                } else {
                    printf ("%c", 193);
                }
            }
        }
    }
}

/**INICIALITZA TOT EL TAULER AMB EL CARACTER '@'.
D'AQUESTA MANERA ACONSEGUIM QUE AL BAIXAR UNA LLETRA
COMPARI SI LA FILA DE SOTA EST� BUIDA (== '@') O SI
HI HA UNA LLETRA (!= '@')**/
void inicialitzar_tauler() {

    for (fila = 0; fila < MAXFILA; fila++) {
        for (columna = 0; columna < MAXCOLUMNA; columna++) {
            taula [fila][columna] = '@';
        }
    }
}

void mostrar_paraules() {
    x = 106; y = 10;
    mygotoxy(x, y);
    SetColor2(YELLOW,BLACK);
    printf ("PARAULES CLAU:");
    y++;
    SetColor2(WHITE,BLACK);
    for (i_paraules = 0; i_paraules < MAXPAR; i_paraules++) {
        y++;
        mygotoxy(x,y);
        printf ("%s", paraules_clau[i_paraules]);
    }
}

void randomitzador() {
    char lletra_anterior = '\0';
    int paraula = 0, posicio_lletra = 0;
    srand (time(NULL));

    do {
        lletra_anterior = lletra;
        paraula = rand () % MAXPAR;
        posicio_lletra = rand () % strlen(paraules_clau[paraula]);
        lletra = paraules_clau[paraula][posicio_lletra];
    } while (lletra_anterior == lletra); //NO PERMET MOSTRAR DUES VEGADES LA MATEIXA LLETRA
}

void puntuacio() {
    mygotoxy (11,7);
    SetColor2(BLACK,YELLOW);
    printf ("PUNTS: %u", punts);
}

void mostrar_lletres() {
    SetColor2(LIGHTGREEN,BLACK);
    x = 12; y = 9;
    columna = 0; fila = -1;
    do {
        mygotoxy (x,y);
        printf ("%c", lletra);
        tecles = getch();
        if ((tecles == 'd' || tecles == 'D') && x < 92) {
            mygotoxy (x,y);
            printf (" ");
            x+=4;
            columna++;
        } else if ((tecles == 'a' || tecles == 'A') && x > 12) {
            mygotoxy (x,y);
            printf (" ");
            x-=4;
            columna--;
        }
    } while (!((tecles == 's' || tecles == 'S') && taula[0][columna] == '@'));
    borrar_notificacions();

    while (taula[fila + 1][columna] == '@' && fila < MAXFILA) { //SI LA FILA DE SOTA ES '@' SIGNIFICA QUE ESTA BUIDA
        mygotoxy (x,y);
        printf (" ");
        y+=2;
        mygotoxy (x,y);
        printf ("%c", lletra);
        Sleep(150);
        fila++;
    }

    taula [fila][columna] = lletra; //GUARDA A UNA MATRIU LA POSICI� DE LA LLETRA AL TAULER
}

void buscar_paraules() {

    int fila_tmp = 0, columna_tmp = 0;

    for (fila = 0; fila < MAXFILA; fila++) {
        for (columna = 0; columna < MAXCOLUMNA; columna++) {
            i_paraules = 0;
            while (i_paraules < MAXPAR) {
                i_caracters = 0;
                if (taula[fila][columna] == paraules_clau[i_paraules][i_caracters]) { //COMPROVA SI LA LLETRA DE LA TAULA ES LA MATEIXA LLETRA QUE LA PRIMERA LLETRA DE LA PARAULA
                    fila_tmp = fila;
                    columna_tmp = columna;
                    if (taula[fila_tmp][columna_tmp + 1] == paraules_clau[i_paraules][i_caracters + 1]) { //COMPROVA SI LA LLETRA DE LA DRETA ES LA MATEIXA LLETRA QUE LA SEGONA LLETRA DE LA PARAULA
                        do {
                            i_caracters++;
                            columna_tmp++;
                        } while ((taula[fila_tmp][columna_tmp] == paraules_clau[i_paraules][i_caracters]) && (paraules_clau[i_paraules][i_caracters] != '\0')); //SEGUIRA COMPROVANT LES LLETRES FINS QUE LLEGEIXI TOTA LA PARAULA
                        if (paraules_clau [i_paraules][i_caracters] == '\0') { //SI HA ARRIBAT AL FINAL DE LA PARAULA...
                            notificacions();
                            punts += strlen(paraules_clau [i_paraules]); //SUMA ELS PUNTS SEGONS ELS CARACTERS DE LA PARAULA
                            x = 12 + columna * 4;
                            y = 11 + fila * 2;
                            fila_tmp = fila;
                            columna_tmp = columna;
                            i_caracters = 0;

                            /**EL PROGRAMA AL TROBAR UNA PARAULA LA SEGUIR� MOSTRANT PERO AMB UN COLOR DIFERENT.
                            D'AQUESTA MANERA EVITO TENIR QUE FER CAURE LES LLETRES DE SOBRE PER A QUE NO
                            QUEDIN ESPAIS BUITS

                            LES PARAULES TROBADES TAMPOC ES PODRAN SOBREESCRIURE**/

                            do {
                                SetColor2(LIGHTCYAN,BLACK);
                                mygotoxy(x,y);
                                printf ("%c", paraules_clau[i_paraules][i_caracters]); //MOSTRARA LA PARAULA TROBADA EN UN COLOR DIFERENT PER A DISTINGIR-LA
                                x+=4;
                                i_caracters++;

                                /**CANVIA TOTA LA PARAULA PEL CARACTER '#' UNA VEGADA TROBADA.
                                D'AQUESTA MANERA ACONSEGUIM QUE ES MOSTRI LA PARAULA AL TAULER
                                PERO L'ESBORRI DE LA MATRIU PER A NO SUMAR ELS PUNTS TOTA L'ESTONA**/

                                taula[fila_tmp][columna_tmp] = '#';
                                columna_tmp++;
                            } while (paraules_clau[i_paraules][i_caracters] != '\0');
                        }
                    } else if (taula[fila_tmp + 1][columna_tmp] == paraules_clau[i_paraules][i_caracters + 1]) {
                        do {
                            i_caracters++;
                            fila_tmp++;
                        } while ((taula[fila_tmp][columna_tmp] == paraules_clau[i_paraules][i_caracters]) && (paraules_clau[i_paraules][i_caracters] != '\0'));
                        if (paraules_clau [i_paraules][i_caracters] == '\0') {
                            notificacions();
                            punts += strlen(paraules_clau [i_paraules]);
                            x = 12 + columna * 4;
                            y = 11 + fila * 2;
                            fila_tmp = fila;
                            columna_tmp = columna;
                            i_caracters = 0;
                            do {
                                SetColor2(LIGHTCYAN,BLACK);
                                mygotoxy(x,y);
                                printf ("%c", paraules_clau[i_paraules][i_caracters]);
                                y+=2;
                                i_caracters++;
                                taula[fila_tmp][columna_tmp] = '#';
                                fila_tmp++;
                            } while (paraules_clau[i_paraules][i_caracters] != '\0');
                        }
                    } else if (taula[fila_tmp][columna_tmp - 1] == paraules_clau[i_paraules][i_caracters + 1]) {
                        do {
                            i_caracters++;
                            columna_tmp--;
                        } while ((taula[fila_tmp][columna_tmp] == paraules_clau[i_paraules][i_caracters]) && (paraules_clau[i_paraules][i_caracters] != '\0'));
                        if (paraules_clau [i_paraules][i_caracters] == '\0') {
                            notificacions();
                            punts += strlen(paraules_clau [i_paraules]);
                            x = 12 + columna * 4;
                            y = 11 + fila * 2;
                            fila_tmp = fila;
                            columna_tmp = columna;
                            i_caracters = 0;
                            do {
                                SetColor2(LIGHTCYAN,BLACK);
                                mygotoxy(x,y);
                                printf ("%c", paraules_clau[i_paraules][i_caracters]);
                                x-=4;
                                i_caracters++;
                                taula[fila_tmp][columna_tmp] = '#';
                                columna_tmp--;
                            } while (paraules_clau[i_paraules][i_caracters] != '\0');
                        }
                    } else if (taula[fila_tmp - 1][columna_tmp] == paraules_clau[i_paraules][i_caracters + 1]) {
                        do {
                            i_caracters++;
                            fila_tmp--;
                        } while ((taula[fila_tmp][columna_tmp] == paraules_clau[i_paraules][i_caracters]) && (paraules_clau[i_paraules][i_caracters] != '\0'));
                        if (paraules_clau [i_paraules][i_caracters] == '\0') {
                            notificacions();
                            punts += strlen(paraules_clau [i_paraules]);
                            x = 12 + columna * 4;
                            y = 11 + fila * 2;
                            fila_tmp = fila;
                            columna_tmp = columna;
                            i_caracters = 0;
                            do {
                                SetColor2(LIGHTCYAN,BLACK);
                                mygotoxy(x,y);
                                printf ("%c", paraules_clau[i_paraules][i_caracters]);
                                y-=2;
                                i_caracters++;
                                taula[fila_tmp][columna_tmp] = '#';
                                fila_tmp--;
                            } while (paraules_clau[i_paraules][i_caracters] != '\0');
                        }
                    }
                }
                i_paraules++; //PASSA A REVISAR SI LA SEG�ENT PARAULA COINCIDEIX
            }
        }
    }
}

//QUAN TOTA LA PRIMERA FILA ES PLENA, EL PROGRAMA ACABA
int final() {
    int ple = 1;

    for (columna = 0; columna < MAXCOLUMNA; columna++) {
        if (taula[0][columna] == '@') {
            ple = 0;
        }
    }

    return (ple == 1);
}

//MOSTRA NOTIFICACIONS QUAN ES FORMA UNA PARAULA
void notificacions() {
    SetColor2(LIGHTMAGENTA, BLACK);
    mygotoxy(47,7);
    printf ("Paraula %s trobada! +%d punts", paraules_clau [i_paraules], strlen(paraules_clau [i_paraules]));
}

//ESBORRA LES NOTIFICACIONES DESPR�S DE FORMAR LA PARAULA
void borrar_notificacions() {
    mygotoxy(47,7);
    printf ("                                            ");
}

//MOSTRA NOTIFICACI� QUAN ACABA EL PROGRAMA
void notificacio_fi() {
    SetColor2(BLACK, WHITE);
    mygotoxy(40,7);
    printf ("Has emplenat la primera fila i el joc acaba!");
    mygotoxy(47,8);
    printf ("Prem UNA TECLA per a tancar...");
    getch();
    SetColor2(WHITE, BLACK);
}

//ENS AJUDA A L'HORA DE TESTEJAR SI LES LLETRES S'EMMAGATZEMEN CORRECTAMENT A LA MATRIU
void mostrar_array() {
    system("cls");
    for (fila = 0; fila < MAXFILA; fila++) {
        for (columna = 0; columna < MAXCOLUMNA; columna++) {
            printf ("%c ", taula[fila][columna]);
        }
        printf ("\n");
    }
}
