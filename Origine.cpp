#include <iostream>
#include <string>
#include <vector>
#include "Intestazione.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>

//lisciami le mele fetiB

int main() {
    
    lettore_lista();  // controllo il file.txt con i dati per la probabilita'

    for (size_t i{ 0 }; i < nomi.size(); i++)  // creazione oggetti
    {
        lista_studenti.push_back(Studente(nomi[i], punteggi[i]));
    }
    
    std::cout << lista_studenti[0].name << std::endl;    //stronzo
    
    int numero_volontari{ 0 };
    char scelta{};
    std::vector <std::string> estratti{};

    while (true) { // input per eventuali volontari e non estratti
        std::cout << "Qualcuno vuole andare volontario? S/N----->";
        std::cin >> scelta;
        if (scelta == 's' || scelta == 'S') {
            int n_seriale{ 0 };
            std::cout << "metti il numero dello studente---> " << std::endl;
            std::cin >> n_seriale;
            lista_studenti[n_seriale].modifica_punteggio(-2);
            std::cout << lista_studenti[n_seriale].score << std::endl;
            estratti.push_back(lista_studenti[n_seriale].name);
            numero_volontari += 1;
        }

        else if (scelta == 'n' || scelta == 'N') {
            break;
        }
        else {
            std::cout << "\n\nDigita solamente S o N\n" << std::endl;
        }
    }
    //...........................................................................................
    for (size_t i{ 0 }; i < lista_studenti.size(); i++) {
        for (int n{ 0 }; n <= lista_studenti[i].score; n++) {
            lista_stringhe.push_back(lista_studenti[i].name);
        }
    }

    //...........................................................................................
    while (true) // inizio random shuffle
    {
        //INPUT SCELTA
        std::cout << "premi A per fare un estrazione e B per interrompere------> " << std::endl;
        std::cin >> scelta;
        //...........................................................................................
        if (scelta == 'a' || scelta == 'A') {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // inizializzazione tempo
            std::default_random_engine e(seed);                                          //costante random per lo shuffle
            std::shuffle(lista_stringhe.begin(), lista_stringhe.end(), e);
            std::cout << "shuffled elements:";
            //............................................................................................


            unsigned int estrazioni{};                         //numero estrazioni e input per il numero (numero di interrogati - volontari)
            std::cout << "scrivi il numero di volontari-------> " << std::endl;
            std::cin >> estrazioni;
            estrazioni += numero_volontari;
            int count = 0;
            while (estratti.size() < estrazioni) {   //uso vettore estratti dichiarato nell header, estraggo, controllo se il nuovo estratto è già presente, se si estraggo un' altra volta sennò ez

                if (std::find(estratti.begin(), estratti.end(), lista_stringhe[count]) == estratti.end()) { //ci siamo rotti il cazzo tanto non capite comunque
                    estratti.push_back(lista_stringhe[count]);
                    std::cout << ' ' << lista_stringhe[count];
                }
                ++count;
            }
            std::cout << '\n';
            for (auto estratto : estratti) {
                for (size_t n_seriale{ 0 }; n_seriale< nomi.size(); n_seriale++) {
                    if (estratto ==nomi[n_seriale]) {
                        lista_studenti[n_seriale].modifica_punteggio(-2);
                    }
                }
            }
        }
        else if (scelta == 'b' || scelta == 'B') {
            break;
        }
        else {
            std::cout << "\n\nDigita solamente A o B\n" << std::endl;
        }
    }
    for (int n_seriale{ 0 }; n_seriale < nomi.size(); n_seriale++){
        for (auto estratto : estratti) {
            if (lista_studenti[n_seriale].name == estratto) {
                break;
            }
            lista_studenti[n_seriale].modifica_punteggio(1);
        }
    }
    
    lista_studenti[0].score = 0;// stronzo
    scrittore_lista();
    //...........................................................................................................................
    return 0;
}