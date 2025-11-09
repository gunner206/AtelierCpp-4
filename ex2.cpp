#include <iostream>
#include <string>
using namespace std;
class AgentBancaire;
class Banque;

class Client{
    private:
        string nome;
        string CIN;
        int idClient;
    public:
        Client(int id, string nome, string cin): idClient(id), nome(nome), CIN(cin){}
        string getNome() const {return nome;}
        string getCIN() const {return CIN;}
        int getID() const {return idClient;}
};
class CompteBancaire{
    private:
        int numero;
        double solde;
        int code;
        Client& client;
    public:
        CompteBancaire(int numero, double solde , int codeSecret, Client &client):
        numero(numero), solde(solde), code(codeSecret), client(client){
        }
        void deposer(double montant){
            solde += montant;
        }

        bool retirer(double montant){
            if (montant > solde){
                cout << "solde Insuffisant!!" << endl;
                return false;
            }
            solde -= montant;
            return true;
        }
    friend AgentBancaire;
    friend Banque;
};
class AgentBancaire{
    
    int consulteCode(CompteBancaire& compte){
        std::cout << "code secret de Compte : " << compte.client.getNome() << " : " << compte.code << "\n";
        return compte.code;
    }
    void transfertEntreCompte(CompteBancaire& source, CompteBancaire& destination, double montant){
        if (source.retirer(montant)){
            destination.deposer(montant);
            cout << "operation de transfert effectuee\n";
            return;
        }
        cout << "Operation de transfert echouee!!" << endl;
    }
};
const int MAX_COMPTES = 10;
class Banque{
    private:
        CompteBancaire *comptes[MAX_COMPTES];
        int nombreComptes = 0;

    public:
        void ajouterCompte(Client &client, int numero, double solde, int codeSecret){
            if (nombreComptes < MAX_COMPTES){
                CompteBancaire *compte = new CompteBancaire(numero, solde, codeSecret ,client);
                comptes[nombreComptes] = compte;
                nombreComptes++;
            }
            else {
                cout << "Ereure d'ajoute de compte" << endl;
                return;
            }
        }

        void afficherRapportAudit(){
            for (int i = 0; i < nombreComptes ; i++){
                cout << comptes[i]->client.getNome() << " Numero : " << comptes[i]->numero << " Solde: " << comptes[i]->solde << endl;
            }
        }
};

int main(){
    Banque banque;
    Client c1(1, "yassine", "BW50345");
    Client c2(2, "khalid", "J342455");
    Client c3(3, "Brahim", "KR4356");
    banque.ajouterCompte(c1, 43254634, 100.0 , 1234);
    banque.ajouterCompte(c2, 36346345, 200, 5678);
    banque.ajouterCompte(c3, 32453653, 150.23, 1358);
    
    banque.afficherRapportAudit();

    return 0;
}