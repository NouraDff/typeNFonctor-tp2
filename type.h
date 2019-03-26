#include <vector>
using namespace std;

class Type
{
public:
    const char* identificateur; 
    vector<const char*> idCollection; 

	// Opérateurs:
	bool operator<(Type const& droit) const;
	bool operator>(Type const& droit) const;
	Type &operator=(const Type& autre);
    	friend ostream &operator<<(ostream &os, const Type &type);

    Type();
    Type(const char* id);
    ~Type();

	bool existe() const;
	bool possede(const char* argument) const;

	private:
		void afficher(ostream &os) const;
};

Type::Type()
        : identificateur(NULL), idCollection(0)
{
}

Type::Type(const char* id)
{
    identificateur = id; 
}

Type::~Type()
{
    idCollection.clear(); //.shrink_to_fit ? et id = NULL?
}

bool Type::existe() const
{
	if(identificateur == NULL)
		return false;
	return true;
}

bool Type::possede(const char* argument) const
{
	if(find(idCollection.begin(), idCollection.end(), argument)!=idCollection.end())
		return true;
	return false;
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
