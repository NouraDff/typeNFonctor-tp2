#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include "arbreavl.h"
#include "type.h"
#include "fonctor.h"

using namespace std;

bool estEnLettres(const char* id){
	for(unsigned i = 0; i < strlen(id); ++i)
		if(!isalpha(id[i]))
			return false;
	return true;
}

template <class T>
void vider(vector<T> *vect){
	vect->clear();
	vect->shrink_to_fit();
}

int main(int argc, const char** argv){ // vérifier erreurs d'entrée (ne fonctionne plus correctement depuis nouvelles fct...) comme si les objets étaient ajoutés à l'arbre et non effacés après
    ifstream fichier(argv[1], ios::in); 

    if(fichier){ 

	ArbreAVL<Type> *arbreT = new ArbreAVL<Type>();
	ArbreAVL<Fonctor> *arbreF = new ArbreAVL<Fonctor>();
	Type *tempT;
	Fonctor *tempF;
	vector<const char*> arguments, clause;
	vector<const Type*> type;
	vector<vector<const char*>> fonc;
	string entree, nom, ligne;

	while(fichier >> entree >> nom){	

		tempT = new Type(nom.c_str());
                tempF = new Fonctor(nom.c_str());
                if(estEnLettres(nom.c_str()) && !arbreT->contient(*tempT) && !arbreF->contient(*tempF)){
			if(!entree.compare("type")){

                		getline(fichier, ligne);
                        	arguments.push_back(strtok((char*)ligne.c_str(), "= {,"));
                        	while(arguments.back() != NULL && find(arguments.begin(), arguments.end(), arguments.back())==arguments.end()-1)
                                	if(estEnLettres(arguments.back()))
						arguments.push_back(strtok(NULL, " ,}"));
					else
						cerr << "Les arguments ne contiennent pas uniquement que des lettres." << endl; // arrêt??
				if(arguments.back()!=NULL && find(arguments.begin(), arguments.end(), arguments.back())!=arguments.end()-1)
					cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
				else arguments.pop_back();

				tempT->idCollection = arguments;
				arbreT->inserer(*tempT);
				vider(&arguments);

			}else if(!entree.compare("foncteur")){

                        	getline(fichier, ligne);
				tempT = new Type(strtok((char*)ligne.c_str(), ": ,"));
				type.push_back(tempT); 
				while(tempT->existe()){ 
					if(arbreT->contient(*tempT)){
						tempT = new Type(strtok(NULL, " ,"));
						type.push_back(tempT);
					}
 					else
                                                cerr << "Les arguments ne sont pas tous existants." << endl; // arrêt
                                }
                                if(!tempT->existe()) 
                                        type.pop_back();

                                while(fichier.peek() == '('){
                                        getline(fichier, ligne);
                                        clause.push_back(strtok((char*)ligne.c_str(), "( ,")); 
                                        while(clause.back() != NULL && clause.size() <= type.size() && type.at(clause.size())->possede(clause.back()))
                                                clause.push_back(strtok(NULL, " ,)"));
					if(clause.back() == NULL && clause.size() > type.size())
						clause.pop_back();
                                        else if(!type.at(clause.size())->possede(clause.back()))
                                                cerr << "Les arguments des clauses ne correspondent pas tous aux types voulus." << endl; // arrêt??
                                        else 
						cerr << "Le format des clauses est invalide." << endl; // arrêt??

                                        fonc.push_back(clause);
                                        vider(&clause);
                                }

				vider(&type);
                                tempF->matrice = fonc;
                                arbreF->inserer(*tempF);
                                vider(&fonc);
			}
			else
			{
				cerr << "Entrée invalide." << endl; // arrêt??
			}
		} //else objet de même nom existe déjà ou nom n'est pas alphabéthque
	}

	fichier.close();

		/*--------------------------------------------------------
	 	*
	 	* Lecture Clavier
	 	* 
	 	* -------------------------------------------------------*/ 


		string input;
		while (getline(cin, input) && !cin.eof())
		{
			vector<string> vec;
			//mettre chaque élément dans un vector)
			vec.push_back(input);
			size_t found = input.find_first_of("?(");
			//Si la position du caractère doit ce trouver dans la chaine de catactère
			if (found < input.length() && found > 0)
			{
				//Coupe la chaine au ?
				string identificateur = input.substr(0, found);
				Fonctor *fonctor = new Fonctor(identificateur.c_str());
				Type *type = new Type(identificateur.c_str());
				if (input.at(found) == '?')
				{
					if (arbreF->contient(*fonctor))
					{
						cout << arbreF->rechercheElement(*fonctor) << endl;
					}
					else if (arbreT->contient(*type))
					{
						cout << arbreT->rechercheElement(*type) << endl;
					}
					else
					{
						cout << "PAS TROUVER" << endl;
					}
				}
				else if (input.at(found) == '(')
				{
					cout << "Requete ()" << endl;
				}
			}
		}
	}
	else
        {
                cerr << "Impossible d'ouvrir le fichier." << endl;
        }

	return 0;
}
