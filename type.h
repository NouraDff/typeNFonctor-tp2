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
	friend bool operator<(Type const* gauche, Type const droit);
	friend bool operator>(Type const* gauche, Type const droit);
	friend ostream &operator<<(ostream &os, const Type &type);

    Type();
    Type(string id);
    ~Type();

	bool possede(const string argument) const;

	private:
		void afficher(ostream &os) const;
		bool plusPetit(Type const& droit) const;
		bool plusGrand(Type const& droit) const;
};

Type::Type()
        : identificateur(""), idCollection(0)
{
}

Type::Type(string id)
{
    identificateur = id; 
}

Type::~Type()
{
	identificateur = "";
    idCollection.clear(); //.shrink_to_fit ? et id = NULL?
}

Type::operator bool() const
{
	return identificateur != "";
}

bool Type::operator!() const 
{
	return identificateur == "";
}

bool Type::possede(const string argument) const
{
	if(find(idCollection.begin(), idCollection.end(), argument)!=idCollection.end())
		return true;
	return false;
}

bool operator<(Type const* gauche, Type const droit) 
{
    return gauche->plusPetit(droit); 
}

bool Type::plusPetit(Type const& droit) const
{
	if(identificateur < droit.identificateur){
        	return true;
    	}
    	return false;
}

bool operator>(Type const* gauche, Type const droit)
{
    return gauche->plusGrand(droit); 
}

bool Type::plusGrand(Type const& droit) const
{
    if(identificateur > droit.identificateur){
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const Type& type)
{
        type.afficher(os);
    return os;
}

void Type::afficher(ostream &os) const
{
    os << "{" <<  idCollection.at(0);
    for (int i = 1; i < idCollection.size(); i++) {
		os << ", " << idCollection.at(i);
	}
    os << "}" << endl; 
}
