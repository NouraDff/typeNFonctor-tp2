#include <vector>
using namespace std;

class Type
{
public:
    string identificateur; 
    vector<const char*> idCollection; 

	// Opérateurs:
	bool operator<(Type const& droit) const;
	bool operator>(Type const& droit) const;
	bool operator==(Type const& droit) const;
	bool operator!=(Type const& droit) const;
	Type &operator=(const Type& autre);
    	friend ostream &operator<<(ostream &os, const Type &type);

    Type();
    Type(string id);
    ~Type();

	private:
		void afficher(ostream &os) const;
};

Type::Type()
        : identificateur(NULL), idCollection(0)
{
}

Type::Type(string id)
{
    identificateur = id; 
}

Type::~Type()
{
    idCollection.clear(); 
}

bool Type::operator<(Type const& droit) const
{
    if(identificateur < droit.identificateur){
        return true;
    }   
    return false; 
}

bool Type::operator>(Type const& droit) const 
{
    if(identificateur > droit.identificateur){
        return true;
    }   
    return false; 
}

bool Type::operator==(Type const& droit) const
{
	if(identificateur == droit.identificateur)
		return true;
	return false;
}

bool Type::operator!=(Type const& droit) const
{
	if(identificateur != droit.identificateur)
		return true;
	return false;
}

Type &Type::operator=(const Type& autre)
{
        if (this == &autre)
        {
            return *this;
        }
        identificateur = autre.identificateur;
        idCollection = autre.idCollection;
        return *this;
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
