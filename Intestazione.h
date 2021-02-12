#ifndef INTESTAZIONE_H
#define INTESTAZIONE_H
#include<iostream>
#include<fstream>
#include <map>

//liste e vettori
std::vector <std::string> materie_s{ "italiano","latino","inglese","storia","filosofia","matematica","fisica","arte","scienze","motoria","civica" };
std::vector <std::string> nomi{ "prova" };
std::vector < int> punteggi;
bool m_interrogato[27][11]{};
std::vector <std::string> interrogazioni;

//dichiarazione classe
class Studente {
public:
    std::string name;
    int score;
    std::map<std::string, bool> materie = {
        {"italiano", false},
        {"latino", false },
        {"inglese", false },
        {"storia", false},
        {"filosofia", false},
        {"matematica", false},
        {"fisica", false},
        {"arte", false},
        {"scienze", false},
        {"motoria", false},
        {"civica", false}
    };
    void materie_interrogato() {
        for (size_t i{0}; i < materie_s.size(); ++i) {
            if (this->materie[materie_s[i]]) {
                interrogazioni.push_back(materie_s[i]);
            }
        }
    }

    void vengo_interrogato(std::string materia) {
        this->materie[materia] = true;
    }

    bool stato_interrogato(std::string materia) {
        if (this->materie[materia]) {
            return true;
        }
        else { return false; }
    }

    void modifica_punteggio(int a) {
        this->score += a;
        if (this->score < 0) {
            this->score = 0;
        }
    }

    Studente(std::string nome, int punteggio);
};
Studente::Studente(std::string nome, int punteggio)
    :name{ nome }, score{ punteggio } {}
//vettore studenti
std::vector <Studente> lista_studenti;


//funzioni
void lettura_dati() {
    std::ifstream file;
    file.open("dati.txt");
    std::string x{};
    int linea{ 0 };
    while (std::getline(file, x)) {

        if (x[2] == 48) {
            punteggi.push_back(0);
        }
        else if (x[3] == ' ') {
            punteggi.push_back(x[2] - 48);
        }
        else {
            punteggi.push_back((x[2] - 48) * 10 + x[3] - 48);
        }

        for (size_t i{ 5 }; i < 16; ++i) {
            m_interrogato[linea][i - 5] = x[i] - 48;
        }
        ++linea;
    }
    file.close();
}

void scrittura_dati() {
    std::ofstream file;
    file.open("dati.txt");
    for (size_t i{ 0 }; i < lista_studenti.size(); i++) {
        if (lista_studenti[i].score < 10) {
            file << "//" << lista_studenti[i].score << "  ";
            for (size_t n{ 0 }; n < materie_s.size(); n++) {
                file << lista_studenti[i].materie[materie_s[n]];
            }
            file << std::endl;
        }
        else {
            file << "//" << lista_studenti[i].score << " ";
            for (size_t n{ 0 }; n < materie_s.size(); n++) {
                file << lista_studenti[i].materie[materie_s[n]];
            }
            file << std::endl;
        }
    }
    file.close();
}

#endif