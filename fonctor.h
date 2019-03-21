#include <vector>
using namespace std;

class Fonctor
{
  public:
    string identificateur;
    vector<string> typeCollection;
    vector<vector<string>> matrice;
    friend ostream &operator<<(ostream &os, const Fonctor &fct);

    Fonctor();
    Fonctor(string id);
    ~Fonctor();

    //Constructeur par copie
    Fonctor(const Fonctor &fonctor)
    {
        identificateur = fonctor.identificateur;
        for (int i = 0; i < fonctor.typeCollection.size(); i++)
        {
            typeCollection.push_back(fonctor.typeCollection[i]);
        }
    }
};

Fonctor::Fonctor(string id)
{
    identificateur = id;
}

Fonctor::~Fonctor()
{
    typeCollection.clear();
    matrice.clear();
}

bool operator<(Fonctor const &left, Fonctor const &right)
{
    if (left.identificateur < right.identificateur)
    {
        return true;
    }
    return false;
}
bool operator>(Fonctor const &left, Fonctor const &right)
{
    if (left.identificateur > right.identificateur)
    {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const Fonctor &fonctor)
{
    for (int i = 0; i < fonctor.matrice.size(); i++)
    {
        os << "(" << fonctor.matrice[i][0];
        for (int j = 1; j < fonctor.matrice[i].size(); j++)
        {
            os << ", " <<fonctor.matrice[i][j] ;
        }
        os << ")" << endl;
    }
    os << "";
}
