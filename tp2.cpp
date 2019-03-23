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

int main(int argc, const char** argv){    
    ifstream fichier(argv[1], ios::in); 

    if(fichier){ 

	ArbreAVL<Type> *arbreT = new ArbreAVL<Type>();
	ArbreAVL<Fonctor> *arbreF = new ArbreAVL<Fonctor>();
	Type *tempT;
	Fonctor *tempF;
	vector<const char*> arguments, clause;
	vector<const Type*> type;
	vector<vector<const char*>> fonc;
	string entree, nom, str;
	char* ligne; // voir si on peut éviter la conversion char*/string

	while(fichier >> entree >> nom){	// nom doit être lettres (caract par caract: isalpha(car) 
		tempT = new Type(nom);
                tempF = new Fonctor(nom);
                if(!arbreT->contient(*tempT) && !arbreF->contient(*tempF)){
			if(!entree.compare("type")){

                		getline(fichier, str);
				ligne = new char[str.length()+1];
                        	strcpy(ligne, str.c_str());

                        	arguments.push_back(strtok(ligne, "= {,"));
                        	while(arguments.back() != NULL && find(arguments.begin(), arguments.end(), arguments.back())==arguments.end()-1) // lettres 
                                	arguments.push_back(strtok(NULL, " ,}"));
				if(arguments.back()!=NULL && find(arguments.begin(), arguments.end(), arguments.back())!=arguments.end()-1)
					cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
				else arguments.pop_back();

				tempT->idCollection = arguments;
				arbreT->inserer(*tempT);
				arguments.clear();
				arguments.shrink_to_fit();

			}else if(!entree.compare("foncteur")){

                        	getline(fichier, str);	
				ligne = new char[str.length()+1];
				strcpy(ligne, str.c_str()); 

				tempT = new Type(strtok(ligne, ": ,"));
				type.push_back(tempT); 
				while(tempT->identificateur != NULL){ 
					if(arbreT->contient(*tempT)){
						tempT = new Type(strtok(ligne, ": ,"));
						type.push_back(tempT);
					}
 					else
                                                cerr << "Les arguments ne sont pas tous existants." << endl; // arrêt
                                }
                                if(tempT->identificateur==NULL) // ajouter surcharge de == et != dans type
                                        type.pop_back();

                                while(fichier.peek() == '('){
                                        getline(fichier, str);
                                        ligne = new char[str.length()+1];
                                        strcpy(ligne, str.c_str());

                                        clause.push_back(strtok(ligne, "( ,")); // vérifier que logueur de clause est tjr = longueur type (si + grand => erreur, peut pas chercher)
                                        while(clause.back()!=NULL&&find(type.at[clause.end()]->idCollection.begin(), type.at[clause.end()]->idCollection.end(), clause.back())==clause.end()-1)
                                                clause.push_back(strtok(NULL, " ,)"));
                                        if(clause.back()!=NULL && find(type.at[clause.end()]->idCollection.begin(), type.at[clause.end()]->idCollection.end(), clause.back())!=clause.end()-1)
                                                cerr << "Les clauses ne sont pas toutes valides." << endl; // arrêt??
                                        else clause.pop_back();

                                        fonc.push_back(clause);
                                        clause.clear();
                                        clause.shrink_to_fit();
                                }

				type.clear();
				type.shrink_to_fit();
                                tempF->matrice = fonc;
                                arbreF->inserer(*tempF);
                                fonc.clear();
                                fonc.shrink_to_fit();
				}
				else
				{
					cerr << "Entrée invalide." << endl; // arrêt??
				}
			} //else objet de même nom existe déjà
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
				Fonctor *fonctor = new Fonctor(identificateur);
				Type *type = new Type(identificateur);
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
