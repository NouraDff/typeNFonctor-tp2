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

Fonctor::Fonctor()
    : identificateur(""), matrice(0)
{
}

Fonctor::Fonctor(string id)
{
    identificateur = id;
}

Fonctor::~Fonctor()
{
    matrice.clear();
}

bool operator<(Fonctor const* gauche, Fonctor const droit)
{
	return gauche->plusPetit(droit);
}

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

bool Fonctor::plusGrand(Fonctor const& droit) const
{
    if (identificateur > droit.identificateur)
    {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const Fonctor &fonctor)
{
    fonctor.afficher(os);
    return os;
}

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
