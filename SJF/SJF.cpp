#include <iostream>
#include <fstream>
using namespace std;

const int wiersze = 4;
const int kolumny = 15;
int proces[wiersze][kolumny]; // Tablica danych testowych procesow
int czasOczekiwania[kolumny];
int czasZakonczenia[kolumny];

int main() {
    
    ifstream plik("dane.txt"); // Otwiera plik do odczytu
    for (int i = 0; i < wiersze-1; i++) {
        for (int j = 0; j < kolumny; j++) plik >> proces[i][j];   // Wczytuje kolejną liczbę z pliku do tablicy
    }
    plik.close();   // Zamyka plik
    for (int i = 0; i < kolumny; i++) proces[3][i] = false; // Dodanie 4 wiersza do tablicy, aby okreslic, czy proces przybyl
    int taktCzasu = 0;
    int liczbaWczytanychProcesow = 0,sumaCzasowPrzybycia=0,procesyPrzybyle=0;
    bool czyKoniec; // Zmienna potrzebna do utworzenia warunku petli
    while(!czyKoniec){ // Główna petla algorytmu
        for (int l = 0; l < 15; l++) { // Sprawdzenie warunku wykonania petli
        if(czasZakonczenia[l] == 0) break;
        else czyKoniec = true;
    }
    for (int j = procesyPrzybyle; j < kolumny; j++) { // Okreslenie ile procesow przybylo w danym takcie czasu
        if(sumaCzasowPrzybycia <= taktCzasu && proces [0][j] <= taktCzasu && sumaCzasowPrzybycia + proces [0][j] <= taktCzasu){
            if(sumaCzasowPrzybycia != taktCzasu)sumaCzasowPrzybycia += proces [0][j];
            procesyPrzybyle = j;
        }
    }
    for (int j = 0; j < kolumny; j++) { // Zmiana stanu procesu na przybyly
    if(proces[0][j] <= taktCzasu && proces [3][j] == false && j >= liczbaWczytanychProcesow-1 && j <= procesyPrzybyle){
        proces [3][j] = true;
        liczbaWczytanychProcesow++;
    }}
    int usuniecie = INT_MAX;
    int idMin = 0;
    for (int i = 0; i < kolumny; i++) { // Proces decyzyjny, ktory proces jest najkrotszy
        if (proces[3][i]) {
            if (proces[1][i] < proces[1][idMin])idMin = i;
        }
    }
        taktCzasu += proces[1][idMin]; // Modyfikacja taktuCzasu o czas wykonania procesu
        czasZakonczenia[idMin] = taktCzasu; // Zapisanie czasu zakonczenia procesu
        czasOczekiwania[idMin] = czasZakonczenia[idMin] - proces[0][idMin] - proces[1][idMin]; // Zapisanie czasu oczekiwania procesu
        proces[1][idMin] = usuniecie; // Usuniecie procesu z kolejki do wykonania
    }
    for (int i = 0; i < 15; i++) { // Wyswietlenie czasow oczekiwania oraz zakonczenia procesow
        cout << "Proces " << i+1 << ": czas oczekiwania = " << czasOczekiwania[i] << ", czas zakończenia = " << czasZakonczenia[i] << endl;
    }
    double sredniCzasOczekiwania = 0;
    for (int i = 0; i < 15; i++) sredniCzasOczekiwania += czasOczekiwania[i];
    sredniCzasOczekiwania /= 15;
    cout << "Sredni czas oczekiwania: " << sredniCzasOczekiwania << endl; // Wyswietlenie sredniego czasu oczekiwania procesu
    ofstream plikk; // Przesyla raport programu do pliku
    plikk.open("wynikSJF.txt");
    plikk << "Sredni czas oczekiwania dla algorytmu SJF: " << sredniCzasOczekiwania << endl;
    plikk.close();
    return 0;
    }