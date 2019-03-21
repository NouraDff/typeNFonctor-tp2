#include <vector>
using namespace std;

class Type
{
public:
    string identificateur; 
    vector<string> idCollection; 
    friend ostream &operator<<(ostream &os, const Type &type);

    Type();
    Type(string id);
    ~Type();
     //Constructeur par copie
    Type(const Type &type)
    {
        identificateur = type.identificateur;
         for (int i=0; i<type.idCollection.size(); i++) {
            idCollection.push_back(type.idCollection[i]); 
         }
      
    }
};

Type::Type(string id)
{
    identificateur = id; 
}

Type::~Type()
{
    idCollection.clear(); 
}


   bool operator< (Type const& left, Type const& right) {
    if(left.identificateur < right.identificateur){
        return true;
    }   
    return false; 
}
 bool operator > (Type const& left, Type const& right) {
    if(left.identificateur > right.identificateur){
        return true;
    }   
    return false; 
}

ostream &operator<<(ostream &os, const Type &type)
{
    os << "{" <<  type.idCollection.at(0);
    for (int i = 1; i < type.idCollection.size(); i++) {
		os << ", " << type.idCollection.at(i);
	}
    os << "}" << endl; 
    
   
}



