#ifndef INTESTAZIONE_H
#define INTESTAZIONE_H
#include<iostream>
#include<fstream>
#include <map>
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

    void vengo_interrogato(std::string materia) {
        this->materie[materia] = true;
    }

    bool stato_interrogato(std::string materia) {
        if (this->materie[materia]) {
            return true;
        }
        else { return false; }
    }

    void interrogazioni(std::string materia, bool interrogato) {
        this->materie[materia] = interrogato;
    }
    void modifica_punteggio(int a) {
        this->score += a;
    }
    Studente(std::string nome, int punteggio);
};
Studente::Studente(std::string nome, int punteggio)
    :name{ nome }, score{ punteggio } {}

//liste e vettori. 
std::vector <std::string> materie_s{ "italiano","latino","inglese","storia","filosofia","matematica","fisica","arte","scienze","motoria","civica" };
std::vector <std::string> nomi{ "Alunno1","Alunno2","Alunno3","Alunno4","Alunno5","Alunno6" };
bool m_interrogato[nomi.size][11]{};
std::vector <std::string> lista_stringhe;
std::vector < int> punteggi;
std::vector <Studente> lista_studenti;
std::vector<std::string> estratti;

//funzioni
void lettore_lista() {
    std::ifstream file;
    file.open("lista_sfigati.txt");
    std::string x{};
    int linea{ 0 };
    while (std::getline(file, x)) {

        if (x[3] == false) {
            punteggi.push_back(x[2] - 48);
            std::cout << punteggi.back();
        }
        else {
            int a = (x[2] - 48) * 10;
            int somma = a + (x[3] - 48);
            punteggi.push_back(somma);
        }

        for (size_t i{ 5 }; i < 16; ++i) {
            m_interrogato[linea][i - 5] = x[i] - 48;
        }
        ++linea;
    }
    file.close();
}

void scrittore_lista() {
    std::ofstream file;
    file.open("lista_sfigati.txt");
    for (size_t i{ 0 }; i < lista_studenti.size(); i++) {
        file << "//" << lista_studenti[i].score << " ";
        for (size_t n{ 0 }; n < materie_s.size(); n++) {
            file << lista_studenti[i].materie[materie_s[n]];
        }
        file << std::endl;
    }
    file.close();
}

#endif
