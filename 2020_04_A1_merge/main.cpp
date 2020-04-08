/*
	Aufgabe 1. Merge

	Erstellt:				05/04/2020
	Zuletzt bearbeitet:		08/04/2020

	Autoren: 
			Mathias		FUHRER	fuma1017	73322	
			Johannes	WERNER	wejo1034	73431

			2. Semester

	Zweck der Datei: 
						Enth�lt Funktionen, die die Sortierung von 2 Vektoren �berpr�ft
						und dann in einen 3. Vektor sortiert einf�gt.
						Die Vektoren werden vom Nutzer eingegeben.

	Windows Version:						Windows 10 Home 1909 Build 18363
	Visual Studio Community 2019 Version:	Version 4.8.03752

*/
#include <iostream>
#include "vectorlib.h" 

using namespace std;

bool isSorted(int* v, int vlen)	// Funktion �berpr�ft Sortierung eines Vektors mit Parametern Vektor und Vektorl�nge
{
	int ret = 0;
	// Funktion �berpr�ft ob das das i+1 te Vektorelement gr��er ist als das i te. 
	// Dies wird so oft wiederholt wie es Vektorelemente gibt, damit alle �berpr�ft sind.
	// Ausgabe der Sortierung als true oder false.
	for (int* ptr = v; (ptr - v) < (vlen-1); ptr++) {
		if (*(ptr +1) < *ptr)
			ret++;					//Jeder Sortierungsfehler vergr��ert eine Variable. Ohne Fehler bleibt sie bei 0.
	}	
	if (ret > 0)
		return 0;
	else 
		return 1;
}


int merge(int* v1, int v1len, int* v2, int v2len, int* vDest)
{
	if (isSorted(v1, v1len) ==false || isSorted(v2, v2len) == false)		// Beide Vektoren werden auf Sortierung �berpr�ft. bei false wird -1 zur�ckgegeben (-> Fehlerausgabe in main), bei true geht es weiter
		return -1;
	else
	{
		int* ptr1 = v1;
		int* ptr2 = v2;
		int n1 = 0;
		int n2 = 0;

		for (int* ptrDest = vDest; (ptrDest - vDest) < ((v1len + v2len)+1); ptrDest++) {	// Steigt in jedes ite Vektorelement des 3. Vektors ein, mit L�nge v1+v2
			/*
			cout << "n1: " << n1 << ", n2: " << n2 << endl;
			
			if ((*ptr1 <= *ptr2) && (n1 < v1len))
			{
				cout << "1" << endl;
				*ptrDest = *ptr1;
				*ptr1++;
				n1++;
			}

			else if ((*ptr1 > *ptr2) && (n2 < v2len))
			{
				cout << "2" << endl;
				*ptrDest = *ptr2;
				*ptr2++;
				n2++;
			}

			else {
				cout << "HJUFDB" << endl;
				if (n1 == v1len) {
					cout << "3" << endl;
					*ptr2++;
					*ptrDest = *ptr2;
					n2++;
				}

				else if (n2 == v2len) {
					cout << "4" << endl;
					*ptr1++;
					*ptrDest = *ptr1;
					n1++;
					
				}

				else
					cout << "\aERROR" << endl;
			}*/
			// Zuerst wird immer das Vektorelement des ersten Vektors mit dem des anderen verglichen, das kleinere eingesetzt
			// Sobald das Vektorelement eines Vektors eingef�gt wird, gibt es ptr++ um an das n�chste noch nicht eingef�gte Element zu gelangen
			// z.B. wird bei v1 = { 1, 2) und v2 = { 3, 4} zuerst die 1 eingef�gt. Danach gibt es gleich ptr1++, damit danach die 2 und die 3 verglichen werden
			if ((*ptr1 <= *ptr2) && (n1 < v1len)) {
				*ptrDest = *ptr1;
				ptr1++, n1++;
			}
			else if ((*ptr2 <= *ptr1) && (n2 < v2len)) {
				*ptrDest = *ptr2;
				ptr2++, n2++;
			}
			else {
				// Wenn einer der beiden Vektoren komplett eingef�gt wurde, muss und DARF nichts mehr verglichen werden
				// Bei einem weitergehen w�rde ein Vektorelement mit einem nichtexistierendem Vektorelement verglichen werden
				// Es reicht also die verbleibenden Vektorelemente der Reihe nach einzuf�gen, da diese schon sortiert sind (isSorted)
				if (n1 < v1len) {
					*ptrDest = *ptr1;
					ptr1++, n1++;
				}
				else if (n2 < v2len) {
					*ptrDest = *ptr2;
					ptr2++, n2++;
				}
			}
		}
	}
	return 0;
}



int main()
{
	// Vektorl�nge wird abgefragt und die Elemente durch eine Schleife.
	// Auslagerung in eine separate Funktion sinnvoll v.a. f�r mehrere Vektoren.
	int v1len, v2len;

	printf("\nGeben Sie die Laenge des 1. Vektors ein (max. 10) -> ");
	cin >> v1len;
	if (v1len > 10) {
		cout << "\aBitte geben Sie maximal 10 ein!" << endl;	// Fehlermeldung mit Ton
		return NULL;
	}
	int* v1 = new int[v1len];
	int i = 0;
	for (int* ptr= v1; (ptr - v1) < v1len; ptr++) {
		i++;
		cout << i << ". Vektorelement -> ";
		cin >> *ptr;
	}

	
	printf("\nGeben Sie die Laenge des 2. Vektors ein (max. 10) -> ");
	cin >> v2len;
	if (v2len > 10) {
		cout << "\aBitte geben Sie maximal 10 ein!" << endl;
		return NULL;
	}
	int* v2 = new int[v2len];
	i = 0;
	for (int* ptr = v2; (ptr - v2) < v2len; ptr++) {
		i++;
		cout << i << ". Vektorelement -> ";
		cin >> *ptr;
	}



	int* vDest = new int[v2len+v1len];		// v3 enth�lt v1 und v2, also ist seine L�nge v1L�nge+v2L�nge


	// Vektoren werden an die merge(...) Funktion �bergeben
	if (merge(v1, v1len, v2, v2len, vDest) ==  (- 1))
		cout << "\n\n\n\t\aMindestens einer der Vektoren ist nicht sortiert! Das Programm wird beendet.\n" << endl;		// Nicht sortierter Vektor erzeugt Fehlermeldung (merge(..) gibt -1 zur�ck) und beep, das Programm wird beendet.
	else {
		cout << "\n\nErgebnis: {";
		for (int* ptr = vDest; (ptr - vDest) < (v1len+v2len); ptr++) 
		{	
			cout << " " << *ptr << ",";						// Finaler Vektor wird ausgegeben
		}
		cout << "\b}\n";	// Das backspace \b entfernt das �berfl�ssige Komma, einfacher als das letzte Element separat einzuf�gen
	}

	delete[] vDest, v1, v2; // Vom heap l�schen
	return NULL;
}