#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Telechargeable{
    public:
        virtual void afficherMessage(){
            cout << "telechargement possiible pour cette ressource." << endl;
        }
        virtual void telecharger() const = 0;
};
class Ressource{
    protected:
        int id;
        string titre;
        string auteur;
        int annee;
    public:
        Ressource(int i, string t, string a, int an)
        : id(i), titre(t), auteur(a), annee(an) {}
        virtual void afficherInfos() const{
            cout << id << " : "<< titre << " , " << auteur << " , " << annee << endl;
        }
        virtual void telecharger() const{
            cout << "encours de telechargements ....." << endl;
        }
        bool operator==(const Ressource &a) const{
            return this->id == a.id;
        }
        int getId(){return id;}
        string getTitre(){return titre;}
        string getAuteur(){return auteur;}
        int getAnnee(){return annee;}
        virtual ~Ressource() {}
};

class Livre:public Ressource, public Telechargeable{
    public:
        int nbrDesPages;
        Livre(int id, string titre, string auteur, int annee, int nbrDesPages)
        : Ressource(id, titre, auteur, annee), nbrDesPages(nbrDesPages){}
        void afficheInfos(){
            cout << id << " : " << titre << ", " << auteur << ", " << annee << ", " << nbrDesPages << endl;
        }
        void telecharger() const{
            cout << "Livre encours de telechargement...." << endl;
        }
};
class Magazine:public Ressource, public Telechargeable {
    public:
        int version;
        Magazine(int id, string titre, string auteur, int annee, int version)
        : Ressource(id, titre, auteur, annee), version(version){}
        void afficheInfo(){
            cout << id << " : " << titre << ", " << auteur << ", " << annee << ", " << version << endl;
        }
        void telecharger() const{
            cout << "Magazine encours de telechargement...." << endl;
        }
        
};
class Video:public Ressource, public Telechargeable {
    public:
        float duree;
        Video(int id, string titre, string auteur, int annee, float duree)
        : Ressource(id, titre, auteur, annee), duree(duree){}
        void afficheInfo(){
            cout << id << " : " << titre << ", " << auteur << ", " << annee << ", " << duree << endl;
        }
        void telecharger() const{
            cout << "Video encours de telechargement...." << endl;
        }
};

class Mediatheque{
    Ressource* ressources[100];
    int count;                 
    public:
        Mediatheque() : count(0) {}

        void ajouter(Ressource* r) {
            if (count < 100) {
                ressources[count++] = r;
            } else {
                cout << "La médiathèque est pleine !" << endl;
            }
        }

        void afficherTout() const {
            cout << "=== Contenu de la médiathèque ===" << endl;
            for (int i = 0; i < count; ++i)
                ressources[i]->afficherInfos();
        }

        // Rechercher par titre
        void rechercher(string titre) const {
            cout << "Recherche par titre: " << titre << endl;
            for (int i = 0; i < count; ++i)
                if (ressources[i]->getTitre() == titre)
                    ressources[i]->afficherInfos();
        }

        // Rechercher par année
        void rechercher(int annee) const {
            cout << "Recherche par année: " << annee << endl;
            for (int i = 0; i < count; ++i)
                if (ressources[i]->getAnnee() == annee)
                    ressources[i]->afficherInfos();
        }

        // Rechercher par auteur + année
        void rechercher(string auteur, int annee) const {
            cout << "Recherche par auteur et année: " << auteur << ", " << annee << endl;
            for (int i = 0; i < count; ++i)
                if (ressources[i]->getAuteur() == auteur && ressources[i]->getAnnee() == annee)
                    ressources[i]->afficherInfos();
        }

        ~Mediatheque() {}
};

int main(){
    Mediatheque m;

    Livre* l1 = new Livre(1, "1984", "George Orwell", 1949, 328);
    Magazine* m1 = new Magazine(2, "Science et Vie", "Divers", 2023, 214);
    Video* v1 = new Video(3, "Inception", "Christopher Nolan", 2010, 148.5);
    m.ajouter(l1);
    m.ajouter(m1);
    m.ajouter(v1);
    m.afficherTout();
    cout << endl;
    l1->Telechargeable::afficherMessage();
    l1->telecharger();
    v1->telecharger();
    cout << endl;
    m.rechercher("1984");
    m.rechercher(2023);
    m.rechercher("George Orwell", 1949);
    cout << endl;
    if (*l1 == *m1)
        cout << "Les ressources ont le même ID.\n";
    else
        cout << "Les ressources sont différentes.\n";
    return 0;
}