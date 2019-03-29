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

static ArbreAVL<Type> arbreT = ArbreAVL<Type>();
static ArbreAVL<Fonctor> arbreF = ArbreAVL<Fonctor>();

void lecture(ifstream&);
void lectureArgumentsType(string, vector<string>&);
void lectureTypesFonc(string, vector<Type>&);
void lectureClausesFonc(string, vector<vector<string>>&, vector<Type>);
void lectureRequetes();
bool estEnLettres(const char*);
template <class T>
void vider(vector<T>*);
void erreur(const string);

void lecture(ifstream &fichier)
{
	Type type;
	Fonctor tempF;
	vector<string> clause,  arguments;
	vector<Type> vecT;
	vector<vector<string>> fonc;
	string entree, nom, ligne;

	while (fichier >> entree >> nom)
	{
		type = Type(nom);
		tempF = Fonctor(nom);
		if (estEnLettres(nom.c_str()) && nom.compare("type") && nom.compare("fonctor") && !arbreT.contient(type) && !arbreF.contient(tempF))
		{
			if (!entree.compare("type"))
			{
				getline(fichier, ligne);
				lectureArgumentsType(ligne, arguments);
				type.idCollection = arguments; // si on enleve vect arguments et que idCollection = lectureType, est-ce qu'on doit supprimer??
				arbreT.inserer(type);
				vider(&arguments);
			}
			else if (!entree.compare("foncteur"))
			{
				getline(fichier, ligne);
				lectureTypesFonc(ligne, vecT);
				while (fichier.peek() == '(')
				{
					getline(fichier, ligne);
					lectureClausesFonc(ligne, fonc, vecT);
				}
				vider(&vecT);
				tempF.matrice = fonc;
				arbreF.inserer(tempF);
				vider(&fonc);
			}
			else
			{
				erreur("Le contenu du fichier est invalide.");
		       	}
		}else
		       erreur("Les noms des types et/ou fonctors ne sont pas tous valides.");
	}
	fichier.close();
}

void lectureArgumentsType(string ligne, vector<string> &arguments)
{
        for (char *p = strtok((char *)ligne.c_str(), "= {,\r"); p != NULL; p = strtok(NULL, " ,}\r"))
	{
		arguments.push_back(p);
		if (!estEnLettres(p))
			erreur("Les arguments ne contiennent pas uniquement que des lettres.");
		if (find(arguments.begin(), arguments.end(), p) == arguments.end())
			erreur("Les arguments ne sont pas tous uniques.");
	}
}

void lectureTypesFonc(string ligne, vector<Type> &vecT)
{
	Type type;
	for (char *p = strtok((char *)ligne.c_str(), ": ,"); p != NULL; p = strtok(NULL, " ,"))
	{
		type = Type(p);
		if (!arbreT.contient(type))
			erreur("Les arguments ne sont pas tous existants."); 
		else{
			type = *(arbreT.rechercher(type));
			vecT.push_back(type);
		}
	}
}

void lectureClausesFonc(string ligne, vector<vector<string>> &fonc, vector<Type> type)
{
	vector<string> clause;
	for (char *p = strtok((char *)ligne.c_str(), "() ,\r"); p != NULL; p = strtok(NULL, " ,)(\r"))
	{
		clause.push_back(p);
		if (clause.size() > type.size())
			break;
		else if (!type.at(clause.size() - 1).possede(clause.back()))
			erreur("Les arguments des clauses ne correspondent pas tous aux types voulus."); 
	}
	if (clause.size() != type.size())
		erreur("Le format des clauses est invalide.");

	fonc.push_back(clause);
	vider(&clause);
}

void lectureRequetes()
{

}

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

void erreur(const string err)
{
	cerr << err << endl;
	exit(1); // s'assurer tt var delete (ex: les vecteurs) et que fichier est close??
}

int main(int argc, const char **argv) 	
{
	ifstream fichier(argv[1], ios::in);

	if (fichier)
	{
		lecture(fichier);
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
				delete [] temp;
				Fonctor fonctor = Fonctor(identificateur);
				Type type = Type(identificateur);
				if (input.at(found) == '?')
				{
					if (arbreF.contient(fonctor))
					{
						cout << *(arbreF.rechercher(fonctor));
					}
					else if (arbreT.contient(type))
					{
						cout << *(arbreT.rechercher(type));
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

					for (char *p = strtok((char *)elm.c_str(), "( ,)"); p != NULL; p = strtok(NULL, "( ,)"))
						elmFonctor.push_back(p);

					//Itérateur positionner au ?
					vector<string>::iterator it = find(elmFonctor.begin(), elmFonctor.end(), "?");
					int index;
					bool sousClause1, sousClause2;
					if (it != elmFonctor.end())
					{
						index = distance(elmFonctor.begin(), it);
						if (arbreF.contient(fonctor))
						{
							fonctor = *(arbreF.rechercher(fonctor));
							cout << "{";
							string sep = "";
							for (int i = 0; i < fonctor.matrice.size(); i++)
							{
								if (elmFonctor.size() == 1)
								{
									sousClause1 = true;
									sousClause2 = true;
								}
								if (it == elmFonctor.begin())
								{
									sousClause1 = equal(fonctor.matrice[i].begin() + 1, fonctor.matrice[i].end(), it + 1);
									sousClause2 = true;
								}
								else if (it == elmFonctor.end() - 1)
								{
									sousClause1 = equal(fonctor.matrice[i].begin(), fonctor.matrice[i].begin() + index, elmFonctor.begin());
									sousClause2 = true;
								}
								else
								{
									sousClause1 = equal(fonctor.matrice[i].begin(), fonctor.matrice[i].begin() + index, elmFonctor.begin());
									sousClause2 = equal(fonctor.matrice[i].begin() + index + 1, fonctor.matrice[i].end(), it + 1);
								}

								if (sousClause1 && sousClause2)
								{
									cout << sep << *(fonctor.matrice[i].begin() + index);
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
		cerr << "Impossible d'ouvrir le fichier.";
	}

	return 0;
}
