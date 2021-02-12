#include <iostream>
#include <string>
#include <vector>
#include "Intestazione.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

int main() {

    lettura_dati();  //lettura dati studenti nel file di testo

    //creazione oggetti studente
    for (size_t i{ 0 }; i < nomi.size(); i++){
        lista_studenti.push_back(Studente (nomi[i], punteggi[i]));
        for (size_t n{ 0 }; n < materie_s.size(); ++n) {
            lista_studenti.back().materie[materie_s[n]] = m_interrogato[i][n];
        }
    }

    //ritorna tutti i dati prima dell'estrazione
    for (auto x : lista_studenti) {
        std::cout <<std::setw(13) << x.name << " -- punteggio:" << x.score << " -- interrogato a:";
        x.materie_interrogato();
        if (interrogazioni.empty()) {
            std::cout << " niente";
        }
        else {
            for (auto x : interrogazioni) {
                std::cout << " " << x;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";

    while (true) {
        //input materia
        std::cout << "Scrivere la materia in minuscolo---> ";
        std::string materia;
        std::cin >> materia;
        std::cout << std::endl;

        //gestione eventuali volontari
        std::vector <std::string> volontari{};

        while (true) {
            std::cout << "Qualcuno vuole andare volontario? S/N-----> ";
            char scelta{};
            std::cin >> scelta;
            std::cout << std::endl;
            if (scelta == 's' || scelta == 'S') {
                //input numero volontario
                int n_seriale{ 0 };
                std::cout << "Metti il numero dello studente---> ";
                std::cin >> n_seriale;
                std::cout << std::endl;
                --n_seriale;
                volontari.push_back(lista_studenti[n_seriale].name);
                //modifica punteggio e segnato interrogato
                lista_studenti[n_seriale].modifica_punteggio(-4);
                lista_studenti[n_seriale].vengo_interrogato(materia);
            }
            else if (scelta == 'n' || scelta == 'N') {
                break;
            }
            //gestione immissione caratteri diversi da s o n
            else {
                std::cout << "\n\nDigita solamente S o N\n" << std::endl;
            }
        }
        //estrazione sventurati
        while (true) {
            //input scelta se estrarre
            std::cout << "Premi A per fare un estrazione e B per interrompere------> ";
            char scelta{};
            std::cin >> scelta;
            std::cout << std::endl;
            if (scelta == 'a' || scelta == 'A') {

                //input numero di estratti
                unsigned int estrazioni{};
                std::cout << "Scrivi il numero di estratti-------> ";
                std::cin >> estrazioni;
                std::cout << std::endl;
                if (estrazioni > 0) {
                    int count = 0;

                    //creazione lista di nomi da cui pescare escludendo i già interrogati alla materia
                    for (size_t i{ 0 }; i < lista_studenti.size(); i++) {
                        if (lista_studenti[i].stato_interrogato(materia) == false) {
                            for (int n{ 0 }; n < lista_studenti[i].score; n++) {
                                lista_stringhe.push_back(lista_studenti[i].name);
                            }
                        }
                    }
                    //shuffle lista
                    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // inizializzazione tempo
                    std::default_random_engine e(seed);                                          //costante random per lo shuffle
                    std::shuffle(lista_stringhe.begin(), lista_stringhe.end(), e);
                    std::cout << "\nEstratti :";

                    //estrazione con controllo se sono andati volontari
                    while (estratti.size() < estrazioni) {
                        if (std::find(estratti.begin(), estratti.end(), lista_stringhe[count]) == estratti.end()) { //ci siamo rotti il cazzo tanto non capite comunque
                            estratti.push_back(lista_stringhe[count]);
                            std::cout << " " << lista_stringhe[count];
                        }
                        ++count;
                    }
                    std::cout << '\n';

                    //modifica punteggio degli estratti e segnati interrogati
                    for (auto estratto : estratti) {
                        for (size_t n_seriale{ 0 }; n_seriale < nomi.size(); n_seriale++) {
                            if (estratto == nomi[n_seriale]) {
                                lista_studenti[n_seriale].modifica_punteggio(-2);
                                lista_studenti[n_seriale].vengo_interrogato(materia);
                            }
                        }
                    }
                    //aumento punteggio a tutti i non volontari e i non estratti
                    for (size_t n_seriale{ 0 }; n_seriale < nomi.size(); n_seriale++) {
                        bool uscito{ true };
                        //esclusione dei volontari
                        for (auto volontario : volontari) {
                            if (volontario == lista_studenti[n_seriale].name) {
                                uscito = false;
                                break;
                            }
                        }
                        //esclusione degli estratti
                        for (auto estratto : estratti) {
                            if (estratto == lista_studenti[n_seriale].name) {
                                uscito = false;
                                break;
                            }
                        }
                        //aumento punteggio
                        if (uscito) {
                            lista_studenti[n_seriale].modifica_punteggio(+1);
                        }
                    }
                }
                else {
                    std::cout << "\n\nnumero volontari deve essere maggiore di 0" << std::endl;
                }
            }
            else if (scelta == 'b' || scelta == 'B') {
                break;
            }
            //gestione immissione caratteri diversi da a o b
            else {
                std::cout << "\n\nDigita solamente A o B\n" << std::endl;
            }
        }
        std::cout << "Per estrarre di nuovo con una materia diversa clicca un tasto diverso da N---> ";
        char scelta;
        std::cin >> scelta;
        std::cout << std::endl;
        if (scelta == 'n' || scelta == 'N') {
            break;
        }
    }
    //riscrittura del file testo con i nuovi dati
    scrittura_dati();

    //resoconto dati aggiornati
    std::cout << "\n\n";

    for (auto x : lista_studenti) {
        std::cout << std::setw(13) << x.name << " -- punteggio:" << x.score << " -- interrogato a:";
        x.materie_interrogato();
        if (interrogazioni.empty()) {
            std::cout << " niente";
        }
        else {
            for (auto x : interrogazioni) {
                std::cout << " " << x;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}