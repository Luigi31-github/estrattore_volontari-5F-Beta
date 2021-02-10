#ifndef INTESTAZIONE_H
#define INTESTAZIONE_H
#include<iostream>
#include<fstream>
//dichiarazione classe
class Studente {
public:

    std::string name;
    int score;

    void modifica_punteggio(int a) {
        this->score += a;
    };

    Studente(std::string nome, int punteggio);
};
Studente::Studente(std::string nome, int punteggio)
    :name{ nome }, score{ punteggio } {}

//........................................................................................................................... 
std::vector <Studente> lista_studenti;
std::vector <std::string> nomi{ "Stronzo","Culomb","Ferramenta scopetta","Fausto","Inutile","Ggg" };
std::vector < int> punteggi;
std::vector <std::string> lista_stringhe;
std::vector<std::string> estratti;

void lettore_lista() {
    std::ifstream file;
    file.open("lista_sfigati.txt");
    std::string x{};
    while (std::getline(file, x)) {
        
        char valore_1 = x[2];
        char valore_2 = x[3];
        
        if (valore_2 == 0) {
            punteggi.push_back(valore_1 - 48);
            std::cout << punteggi.back();
        }
        else {
            int a = (valore_1-48)*10;
            int somma = a + (valore_2 - 48);
            punteggi.push_back(somma);
        }
    }
    file.close();
}

void scrittore_lista() {
    std::ofstream file;
    file.open("lista_sfigati.txt");
    for (size_t i{ 0 }; i < lista_studenti.size(); i++) {
        file << "//" << lista_studenti[i].score << "\n";
    }
    file.close();
}

#endif