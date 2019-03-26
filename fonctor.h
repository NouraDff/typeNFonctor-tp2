#include <vector>
using namespace std;

class Fonctor
{
  public:
    string identificateur;
    vector<vector<const char *>> matrice;

    // Opérateurs
    bool operator>(Fonctor const &droit) const;
    bool operator<(Fonctor const &droit) const;
    Fonctor &operator=(const Fonctor &autre);
    friend ostream &operator<<(ostream &os, const Fonctor &fonctor);

    Fonctor();
    Fonctor(string id);
    ~Fonctor();

  private:
    void afficher(ostream &os) const;
};

Fonctor::Fonctor()
    : identificateur(NULL), matrice(0)
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

bool Fonctor::operator<(Fonctor const &droit) const
{
    if (identificateur < droit.identificateur)
    {
        return true;
    }
    return false;
}

bool Fonctor::operator>(Fonctor const &droit) const
{
    if (identificateur > droit.identificateur)
    {
        return true;
    }
    return false;
}

Fonctor &Fonctor::operator=(const Fonctor &autre)
{
    if (this == &autre)
    {
        return *this;
    }
    identificateur = autre.identificateur;
    matrice = autre.matrice;
    return *this;
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
