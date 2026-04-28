#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Alokuje pamięć i kończy program przy braku powodzenia.
void *safeMalloc(size_t size) {
    void *p = malloc(size);
    if (!p) {
        fprintf(stderr, "Błąd alokacji pamięci.");
        exit(1);
    }
    return p;
}

//  Kopiuje n znaków z src do dst.
void kopiuj(char *dst, const char *src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

// Tworzy tablicę 'wynik' o długości n i wypełnia ją znakami '_'.
char *zainicjalizujWynik(size_t n) {
    char *wynik = safeMalloc(n);

    for (size_t i = 0; i < n; i++) {
        wynik[i] = '_';
    }

    return wynik;
}

//Wczytuje filtr (ciąg znaków do końca linii).
//Zwraca jego długość oraz zapisuje wskaźnik do zaalokowanej pamięci.
size_t wczytajFiltr(char **filtr) {
    char buf[300];
    size_t len = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len < sizeof(buf)) {
            buf[len] = (char)c;
        }
        len++;
    }
    *filtr = safeMalloc(len);
    kopiuj(*filtr, buf, len);
    return len;
}

//Wczytuje do 200 wierszy danych, każdy o długości n.
//Zwraca liczbę wczytanych wierszy.
size_t wczytajDane(char ***tablica, size_t n) {
    *tablica = safeMalloc(200 * sizeof(char *));
    char *buf = safeMalloc(n);
    size_t liczbaWierszy = 0;
    bool czyKoniec = false;
    while (liczbaWierszy < 200 && !czyKoniec) {
        size_t dl = 0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (dl < n) {
                buf[dl] = (char)c;
            }
            dl++;
        }
        if (dl == 0)
            czyKoniec = true;
         else {
            char *linia = safeMalloc(n);
            kopiuj(linia, buf, n);

            (*tablica)[liczbaWierszy++] = linia;
        }
    }

    free(buf);
    return liczbaWierszy;
}

//Sprawdza, czy wynik jest kompletny (nie zawiera '_' w żadnej pozycji).
bool wynikPelny(const char *wynik, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (wynik[i] == '_') {
            return false;
        }
    }
    return true;
}


//Wypisuje wynik, biorąc pod uwagę filtr — tylko tam, gdzie filtr == '+'.

void wypiszWynik(const char *wynik, const char *filtr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (filtr[i] == '+') {
            putchar(wynik[i]);
        }
    }
    putchar('\n');
}


//Sprawdza, czy linia może zostać wstawiona do aktualnego wyniku.
//Linia pasuje, jeśli nie nadpisuje istniejących liter.
bool moznaWstawic(const char *linia, const char *wynik, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (wynik[i] != '_' && linia[i] != '_') {
            return false;
        }
    }
    return true;
}


//Wstawia litery z linii do wyniku tam, gdzie wynik ma '_'.
void wstaw(const char *linia, char *wynik, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (wynik[i] == '_' && linia[i] != '_') {
            wynik[i] = linia[i];
        }
    }
}

//Usuwa litery wpisane z danej linii (resetuje te pola do '_').
void usun(const char *linia, char *wynik, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (linia[i] != '_') {
            wynik[i] = '_';
        }
    }
}

/**
 * Rekurencyjna implementacja Algorytmu X:
 *  - wybiera zgodne wiersze,
 *  - uzupełnia wynik,
 *  - wypisuje gotowe rozwiązania zgodne z filtrem.
 */
void algorytmX(char **tab, char *wynik, const char *filtr,
               size_t start, size_t ilosc, size_t n) {
    if (wynikPelny(wynik, n)) {
        wypiszWynik(wynik, filtr, n);
        return;
    }

    for (size_t i = start; i < ilosc; i++) {
        if (moznaWstawic(tab[i], wynik, n)) {
            wstaw(tab[i], wynik, n);
            algorytmX(tab, wynik, filtr, i + 1, ilosc, n);
            usun(tab[i], wynik, n);
        }
    }
}

int main(void) {
    char *filtr;
    size_t n = wczytajFiltr(&filtr);
    char **tablica;
    size_t ilosc = wczytajDane(&tablica, n);
    char *wynik = zainicjalizujWynik(n);

    algorytmX(tablica, wynik, filtr, 0, ilosc, n); // główna funkcja
    //zwalnianie zasobów
    free(filtr);
    for (size_t i = 0; i < ilosc; i++) {
        free(tablica[i]);
    }
    free(tablica);
    free(wynik);
    return 0;
}
