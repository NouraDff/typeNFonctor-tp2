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

bool estEnLettres(const char *id)
{
	for (unsigned i = 0; i < strlen(id); ++i)
		if (!isalpha(id[i]))
			return false;
	return true;
}

template <class T>
void vider(vector<T> *vect)
{
	vect->clear();
	vect->shrink_to_fit();
}

int main(int argc, const char **argv)
{
	ifstream fichier(argv[1], ios::in);

	if (fichier)
	{

		ArbreAVL<Type> *arbreT = new ArbreAVL<Type>();
		ArbreAVL<Fonctor> *arbreF = new ArbreAVL<Fonctor>();
		Type *tempT;
		Fonctor *tempF;
		vector<string> arguments, clause;
		vector<Type *> type;
		vector<vector<string>> fonc;
		string entree, nom, ligne;

		while (fichier >> entree >> nom)
		{
			tempT = new Type(nom);
			tempF = new Fonctor(nom);
			if (estEnLettres(nom.c_str()) && nom.compare("type") && nom.compare("fonctor") && !arbreT->contient(*tempT) && !arbreF->contient(*tempF))
			{
				if (!entree.compare("type"))
				{

					getline(fichier, ligne);
					for (char *p = strtok((char *)ligne.c_str(), "= {,\r"); p != NULL; p = strtok(NULL, " ,}\r"))
					{
						arguments.push_back(p);
						if (!estEnLettres(p))
							cerr << "Les arguments ne contiennent pas uniquement que des lettres." << endl; // arrêt??
						if (find(arguments.begin(), arguments.end(), p) == arguments.end())
							cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
					}

					tempT->idCollection = arguments;
					arbreT->inserer(*tempT);
					vider(&arguments);
				}
				else if (!entree.compare("foncteur"))
				{

					getline(fichier, ligne);
					for (char *p = strtok((char *)ligne.c_str(), ": ,"); p != NULL; p = strtok(NULL, " ,"))
					{
						tempT = new Type(p);
						if (!arbreT->contient(*tempT))
							cerr << "Les arguments ne sont pas tous existants." << endl; // arrêt
						else
						{
							*tempT = arbreT->rechercheElement(*tempT);
							type.push_back(tempT);
						}
					}

					while (fichier.peek() == '(')
					{
						getline(fichier, ligne);
						for (char *p = strtok((char *)ligne.c_str(), "() ,\r"); p != NULL; p = strtok(NULL, " ,)(\r"))
						{
							clause.push_back(p);
							if (clause.size() > type.size())
							{
								// arrêt??
							}
							else if (!type.at(clause.size() - 1)->possede(clause.back()))
								cerr << "Les arguments des clauses ne correspondent pas tous aux types voulus." << endl; // arrêt??
						}
						if (clause.size() != type.size())
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
					break;
				}
			} //else objet de même nom existe déjà ou nom n'est pas alphabéthque ou correspond à mots réservés
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
			size_t found = input.find_first_of("?(");
			//Si la position du caractère doit ce trouver dans la chaine de catactère
			if (found < input.length() && found > 0)
			{
				//Copie l'entree afin qu'il ne soit pas modifé par le strtok
				char *temp = new char[input.length()];
				strcpy(temp, (char *)input.c_str());
				//Coupe la chaine au ?
				char *identificateur = strtok(temp, "?(");
				Fonctor *fonctor = new Fonctor(identificateur);
				Type *type = new Type(identificateur);
				delete [] temp; 
				if (input.at(found) == '?')
				{
					if (arbreF->contient(*fonctor))
					{
						cout << arbreF->rechercheElement(*fonctor);
					}
					else if (arbreT->contient(*type))
					{
						cout << arbreT->rechercheElement(*type);
					}
					else
					{
						cout << "PAS TROUVER" << endl;
					}
				}
				else if (input.at(found) == '(')
				{
					//elm contient la string entre parenthèrse
					string elm = input.substr(found, input.find(')'));
					vector<string> elmFonctor;
					size_t start = 0, end = 0;

					char *clause = new char[elm.length()];
					clause = (char *)elm.c_str();
					clause = strtok(clause, "( ,)");
					elmFonctor.push_back(clause);
					//Met les éléments dans vecteur
					while (clause != NULL)
					{
						clause = strtok(NULL, "(), )");
						if (clause != NULL)
							elmFonctor.push_back(clause);
					}

					//Itérateur positionner au ?
					vector<string>::iterator it = find(elmFonctor.begin(), elmFonctor.end(), "?");
					int index;
					bool sousClause1, sousClause2;
					if (it != elmFonctor.end())
					{
						index = distance(elmFonctor.begin(), it);
						if (arbreF->contient(*fonctor))
						{
							*fonctor = arbreF->rechercheElement(*fonctor);
							cout << "{";
							string sep = "";
							for (int i = 0; i < fonctor->matrice.size(); i++)
							{
								if (elmFonctor.size() == 1)
								{
									sousClause1 = true;
									sousClause2 = true;
								}
								if (it == elmFonctor.begin())
								{
									sousClause1 = equal(fonctor->matrice[i].begin() + 1, fonctor->matrice[i].end(), it + 1);
									sousClause2 = true;
								}
								else if (it == elmFonctor.end() - 1)
								{
									sousClause1 = equal(fonctor->matrice[i].begin(), fonctor->matrice[i].begin() + index, elmFonctor.begin());
									sousClause2 = true;
								}
								else
								{
									sousClause1 = equal(fonctor->matrice[i].begin(), fonctor->matrice[i].begin() + index, elmFonctor.begin());
									sousClause2 = equal(fonctor->matrice[i].begin() + index + 1, fonctor->matrice[i].end(), it + 1);
								}

								if (sousClause1 && sousClause2)
								{
									cout << sep << *(fonctor->matrice[i].begin() + index);
									sep = ", ";
								}
							}
							
								cout << "}" << endl;
						}
					}
					else
					{
						cout << "Element Not Found" << endl;
					}
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
