/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   
   Classe représentant un Type. 

   AUTEUR(S):
    1) Noura Djaffri DJAN28569508
    2) Laurianne Guindon GUIL22579900
*/

#if !defined(__TYPE__H__)
#define __TYPE__H__

#include <vector>
using namespace std;

class Type
{
  public:
	string identificateur;
	vector<string> idCollection;

	// Opérateurs:
	operator bool() const;
	bool operator!() const;
	friend bool operator<(Type const *gauche, Type const droit);
	friend bool operator>(Type const *gauche, Type const droit);
	friend ostream &operator<<(ostream &os, const Type &type);

	Type();
	Type(string id);
	~Type();

	bool possede(const string argument) const;

  private:
	void afficher(ostream &os) const;
	bool plusPetit(Type const &droit) const;
	bool plusGrand(Type const &droit) const;
};

//Constructeur sans argument
Type::Type()
	: identificateur(""), idCollection(0) {}

// Constructeur
Type::Type(string id)
	: identificateur(id), idCollection(0) {}

// Destructeur
Type::~Type()
{
	identificateur = "";
	idCollection.clear();
	idCollection.shrink_to_fit();
}

Type::operator bool() const
{
	return identificateur != "";
}

bool Type::operator!() const
{
	return identificateur == "";
}

/*
   Recherche si la clause dans un foncteur possède le type. 
   
    @params argument: argument correspond à un élément dans un clause dans un foncteur
    @return vrai si l'argument correspond à un type, sinon vrai. 
*/
bool Type::possede(const string argument) const
{
	return find(idCollection.begin(), idCollection.end(), argument) != idCollection.end();
}

bool operator<(Type const *gauche, Type const droit)
{
	return gauche->plusPetit(droit);
}

/*
   Vérifie si l'identificateur du type est plus petit que celui du droit
   
    @params droit: type dont on compare l'identificateur
	@return vrai si l'identificateur est plus petit que le type droit, sinon faux. 
*/
bool Type::plusPetit(Type const &droit) const
{
	return identificateur < droit.identificateur;
}

bool operator>(Type const *gauche, Type const droit) 
{
	return gauche->plusGrand(droit);
}

/*
   Vérifie si l'identificateur du type  est plus grand que celui droit
   
    @params : type dont on compare l'identificateur
    @return vrai si l'identificateur est plus grand que le type droit. 
*/
bool Type::plusGrand(Type const &droit) const
{
	return identificateur > droit.identificateur;
}

/*
    Surcharge l'opérateur de sortie pour afficher le contenu du type. 
   
    @params os: flux de sortie
			type: élement à afficher
    @return le flux de sortie ostream
*/
ostream &operator<<(ostream &os, const Type &type)
{
	type.afficher(os);
	return os;
}

/*
    Affiche le vecteur qui contient collection d'id du type 
   
    @params os: flux de sortie
*/
void Type::afficher(ostream &os) const
{
	os << "{" << idCollection.at(0);
	for (int i = 1; i < idCollection.size(); i++)
		os << ", " << idCollection.at(i);
	os << "}" << endl;
}

#endif