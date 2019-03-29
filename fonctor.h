#include <vector>
using namespace std;

class Fonctor
{
  public:
    string identificateur;
    vector<vector<string>> matrice;

    // Opérateurs
    friend bool operator>(Fonctor const* gauche, Fonctor const droit);
    friend bool operator<(Fonctor const* gauche, Fonctor const droit);
    friend ostream &operator<<(ostream &os, const Fonctor &fonctor);

    Fonctor();
    Fonctor(string id);
    ~Fonctor();

  private:
    void afficher(ostream &os) const;
    bool plusGrand(Fonctor const& droit) const;
    bool plusPetit(Fonctor const& droit) const;
};

// Constructeur sans argument
Fonctor::Fonctor()
    : identificateur(""), matrice(0){}

// Constructeur
Fonctor::Fonctor(string id)
{
    identificateur = id;
}

// Destructeur
Fonctor::~Fonctor()
{
    matrice.clear();
}

bool operator<(Fonctor const* gauche, Fonctor const droit)
{
	return gauche->plusPetit(droit);
}

/*
   Vérifie que l'identificateur du fonctor est plus petit que le droit
   
    @params droit: fonctor à comparer
    @return vrai si l'identificatuer est plus petit que celui du fonctor droit, sinon faux. 
*/
bool Fonctor::plusPetit(Fonctor const& droit) const
{
    if (identificateur < droit.identificateur)
    {
        return true;
    }
    return false;
}

bool operator>(Fonctor const* gauche, Fonctor const droit)
{
	return gauche->plusGrand(droit);
}

/*
   Vérifiqe que l'identificateur du fonctor est plus grand que celui du fonctor droit
   
    @params droit: fonctor à comparer. 
    @return vrai si l'identificateur du fonctor est plus grand que celui du droit, sinon faux. 
*/
bool Fonctor::plusGrand(Fonctor const& droit) const
{
    if (identificateur > droit.identificateur)
    {
        return true;
    }
    return false;
}

/*
    Surcharge l'opérateur de sortie pour afficher le contenu du fonctor. 
   
    @params os: flux de sortie
			type: élement à afficher
    @return le flux de sortie ostream
*/
ostream &operator<<(ostream &os, const Fonctor &fonctor)
{
    fonctor.afficher(os);
    return os;
}

/*
   Affiche toutes les clauses du fonctor. 
   
    @params os: flux de sortie
*/
void Fonctor::afficher(ostream &os) const
{
    for (int i = 0; i < matrice.size(); i++)
    {
        os << "(" << string(matrice[i][0]);
        for (int j = 1; j < matrice[i].size(); j++)
        {
            os << ", " << string(matrice[i][j]);
        }
        os << ")" << endl;
    }
    os << "";
}
