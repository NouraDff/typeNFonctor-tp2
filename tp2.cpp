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

/*
   
   
    @params 
    @return 
*/
void lectureBaseConnaissances(ifstream &);

/*
   Lit l'entrée vérifie que les types entrés sont uniques. 
   
    @params 
    @return 
*/
vector<string> lectureArgumentsType(string ligne);

/*
    Met dans un vecteur la liste des types que contiennent les clauses du fonctor
	et vérifie que le nombre de type correspond au nombre d'élément dans une clause. 
   
    @params 
    @return 
*/
vector<Type> lectureTypesFonc(string);

/*
   Permet de vérifier pour chaque élément si le type dans la clause
   existe puis l'insère dans dans le tableau de vector fonc. 
   
    @params ligne: ligne contenant l'entrée à lire
			type: vecteur contenant les types
    @return 
*/
vector<string> lectureClausesFonc(string,  vector<Type>);

/*
   
   
    @params 
    @return 
*/
void lectureRequetes();

/*
   Vérifie que la chaine de caractère ne contient que des lettres. 
   
    @params id: chaine de caratère
    @return vrai si la chaine ne contient que des lettres, sinon faux. 
*/
bool estEnLettres(const char *id);

/*
	Vide le vecteur 
   
    @params vect: vecteur qui sera vider. 
*/
template <class T>
void vider(vector<T> *vect);

/*
   Affiche un message d'erreur et quitte le programme avec exit(1) 
   
    @params string: Le message d'erreur à afficher
*/
void erreur(const string);



int main(int argc, const char **argv)
{
	ifstream fichier(argv[1], ios::in);

	if (fichier)
	{
		lectureBaseConnaissances(fichier);
		lectureRequetes();

		/*--------------------------------------------------------
	 	*
	 	* Lecture Clavier
	 	*
	 	* -------------------------------------------------------*/
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier.";
	}

	return 0;
}

void lectureBaseConnaissances(ifstream &fichier)
{
	string entree, nom, ligne;

	while (fichier >> entree >> nom)
	{
		Type type = Type(nom);
		Fonctor fonctor = Fonctor(nom);
		if (estEnLettres(nom.c_str()) && nom.compare("type") && nom.compare("fonctor") && !arbreT.contient(type) && !arbreF.contient(fonctor))
		{
			if (!entree.compare("type"))
			{
				getline(fichier, ligne);
				type.idCollection = lectureArgumentsType(ligne);
				arbreT.inserer(type);
			}
			else if (!entree.compare("foncteur"))
			{
				getline(fichier, ligne);
				vector<Type> vecT = lectureTypesFonc(ligne);
				vector<vector<string>> vecF;
				while (fichier.peek() == '(')
				{
					getline(fichier, ligne);
					vecF.push_back(lectureClausesFonc(ligne, vecT));
				}
				vider(&vecT);
				fonctor.matrice = vecF;
				arbreF.inserer(fonctor);
				vider(&vecF);
			}
			else
				erreur("Le contenu du fichier est invalide.");
		}
		else
			erreur("Les noms des types et/ou fonctors ne sont pas tous valides.");
	}

	fichier.close();
}

vector<string> lectureArgumentsType(string ligne)
{
	vector<string> arguments;
	for (char *p = strtok((char *)ligne.c_str(), "= {,\r"); p != NULL; p = strtok(NULL, " ,}\r"))
	{
		arguments.push_back(p);
		if (!estEnLettres(p))
			erreur("Les arguments ne contiennent pas uniquement que des lettres.");
		if (find(arguments.begin(), arguments.end(), p) == arguments.end())
			erreur("Les arguments ne sont pas tous uniques.");
	}
	return arguments;
}

vector<Type> lectureTypesFonc(string ligne)
{
	Type type;
	vector<Type> vecT;
	for (char *p = strtok((char *)ligne.c_str(), ": ,"); p != NULL; p = strtok(NULL, " ,"))
	{
		type = Type(p);
		if (!arbreT.contient(type))
			erreur("Les arguments ne sont pas tous existants.");
		else
		{
			type = *(arbreT.rechercher(type));
			vecT.push_back(type);
		}
	}
	return vecT;
}

vector<string> lectureClausesFonc(string ligne, vector<Type> type)
{
	vector<string> clause;
	for (char *p = strtok((char *)ligne.c_str(), "() ,\r"); p != NULL; p = strtok(NULL, "() ,\r"))
	{
		clause.push_back(p);
		if (clause.size() > type.size())
			break;
		else if (!type.at(clause.size() - 1).possede(clause.back()))
			erreur("Les arguments des clauses ne correspondent pas tous aux types voulus.");
	}
	if (clause.size() != type.size())
		erreur("Le format des clauses est invalide.");

	return clause;
}

void lectureRequetes()
{
		string input;
		while (getline(cin, input) && !cin.eof())
		{
				if (input.find_first_of("?") != string::npos)
				{
					char *identificateur = strtok((char*)input.c_str(), "?(");
		                        Fonctor fonctor = Fonctor(identificateur);
					Type type = Type(identificateur);	
					if (arbreF.contient(fonctor))
						cout << *(arbreF.rechercher(fonctor));
					else if (arbreT.contient(type))
						cout << *(arbreT.rechercher(type));
					else
						erreur("Le type ou le fonctor n'existe pas, dans la base de connaissances.");
				}
				else if (input.find_first_of("(") != string::npos)
				{
					char *identificateur = strtok((char*)input.c_str(), "?(");
					Fonctor fonctor = Fonctor(identificateur);
					//elm contient la string entre parenthèrse
					vector<string> elmFonctor;

					for (char *p = strtok((char *)input.c_str(), " ,)"); p != NULL; p = strtok(NULL, " ,)"))
						elmFonctor.push_back(p);

					//Itérateur positionner au ?
					vector<string>::iterator it = find(elmFonctor.begin(), elmFonctor.end(), "?");
					if (it != elmFonctor.end())
					{
						if (arbreF.contient(fonctor))
						{
							fonctor = *(arbreF.rechercher(fonctor));
							vector<vector<string>>::iterator index = fonctor.matrice[distance(elmFonctor.begin(), it)];
							cout << "{";
							string sep = "";
							for (unsigned i = 0; i < fonctor.matrice.size(); ++i)
							{
								bool sousClause1 = true, sousClause2 = true;
								if (it != elmFonctor.end()-1)
									sousClause2 = equal(index + 1, fonctor.matrice[i].end(), it + 1);
								if (it != elmFonctor.begin())
									sousClause1 = equal(fonctor.matrice[i].begin(), index, elmFonctor.begin());

								if (sousClause1 && sousClause2)
								{
									cout << sep << *(index);
									sep = ", ";
								}
							}
							cout << "}" << endl;
						}else
							erreur("Le fonctor n'existe pas.");
					}
					else
						erreur("Le format de la requête est invalide.");
				}
		}
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
