/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   
   Ce programme permet de réaliser des requêtes afin 
   consulter une base de connaissances. 

   Deux requêtes sont possible: 
   <nom>? Le nom peut être fonctor ou un type
		  Affiche le contenue associé 
	<fonctor>(<type>, ?, ..., <type>)
		  Affiche toutes les possibiltés qui peuvent
		  remplacer le ? dans les clauses d'un fonctor
	

   AUTEUR(S):
    1) Noura Djaffri DJAN28569508
    2) Laurianne Guindon GUIL22579900
*/

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
   Fait la lecture d'un fichier et le traitement des données pour les ajouter 
   à la base de connaissance. 
   
    @params fichier: le flux d'entrée d'un fichier
*/
void lectureBaseConnaissances(ifstream &fichier);

/*
   Lit l'entrée vérifie que les types entrés sont uniques. 
   
    @params ligne : entrée à lire
    @return vecteur contenant la liste des types d'un Type
*/
vector<string> lectureArgumentsType(string ligne);

/*
    Met dans un vecteur la liste des types que contiennent les clauses du fonctor
	et vérifie que le nombre de type correspond au nombre d'élément dans une clause. 
   
    @params ligne: ligne contenant l'entrée à lire
    @return un vecteur contenant les types
*/
vector<Type> lectureTypesFonc(string ligne);

/*
   Permet de vérifier pour chaque élément si le type dans la clause
   existe puis l'insère dans dans le tableau de vector fonc. 
   
    @params ligne: ligne contenant l'entrée à lire
			type: vecteur contenant les types
    @return un vecteur qui contient les clauses d'un foncteur
*/
vector<string> lectureClausesFonc(string ligne, vector<Type> type);

/*
    Fait la lecture au clavier des requêtes <nom>? et <fonctor>(<type>, ?, ..., <type>). 
*/
void lectureRequetes();

/*
	traite l'entrée au clavier et met les éléments de la clause dans un vecteur
   
    @params entree: l'entrée au clavier
*/
void traiterRequeteClauses(string entree);

/*
    Affiche le résultat de la requête <fonctor>(<type>, ?, ..., <type>)
   
    @params matrice: matrice du fonctor identifié
			elmFonctor: vector qui contient les éléments entrées au clavier
*/
void validerRequeteClauses(vector<vector<string>> matrice, vector<string> elmFonctor);

/*
    Affiche le résultat d'une requête <nom>? soit la collection de l'identificateur
   
    @params entree: l'entrée au clavier.  
*/
void afficherCollectionRequete(string entree);

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
	}
	else
		erreur("Impossible d'ouvrir le fichier.");

	return 0;
}

//
//		LECTURE FICHIER
//

void lectureBaseConnaissances(ifstream &fichier)
{
	string entree, nom, ligne;

	if (fichier.peek() == ifstream::traits_type::eof())
	{
		erreur("Le fichier est vide, aucun traitement ne sera fait.");
	}
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
			else if (!entree.compare("fonctor"))
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
		if (!estEnLettres(p) && strcmp(p, "type") && strcmp(p, "fonctor"))
			erreur("Les noms des arguments ne sont pas tous validés.");
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

//
//		REQUETES CLAVIER
//

void lectureRequetes()
{
	string entree;
	while (getline(cin, entree) && !cin.eof())
	{
		size_t found = entree.find_first_of("?(");
		//Si la position du caractère doit ce trouver dans la chaine de catactère
		if (found < entree.length() && found > 0)
			if (entree.find_first_of("(") != string::npos)
				traiterRequeteClauses(entree);
			else if (entree.find_first_of("?") != string::npos)
				afficherCollectionRequete(entree);
			else
				erreur("Le format de la requête est invalide. ");
	}
}

void traiterRequeteClauses(string entree)
{
	char *identificateur = strtok((char *)entree.c_str(), "(");
	Fonctor fonctor = Fonctor(identificateur);
	//Itérateur positionner au ?
	if (arbreF.contient(fonctor))
	{
		fonctor = *(arbreF.rechercher(fonctor));
		vector<string> elmFonctor;

		//elm contient la string entre parenthèrse
		for (char *p = strtok(NULL, " ,)"); p != NULL; p = strtok(NULL, " ,)"))
			elmFonctor.push_back(p);

		validerRequeteClauses(fonctor.matrice, elmFonctor);
	}
	else
		erreur("Le fonctor n'existe pas.");
}

void validerRequeteClauses(vector<vector<string>> matrice, vector<string> elmFonctor)
{
	vector<string>::iterator it = find(elmFonctor.begin(), elmFonctor.end(), "?");
	cout << "{";
	string sep = "";
	for (unsigned i = 0; i < matrice.size(); ++i)
	{
		vector<string>::iterator index = matrice[i].begin() + distance(elmFonctor.begin(), it);
		bool sousClause1 = true, sousClause2 = true;
		if (it != elmFonctor.end() - 1)
			sousClause2 = equal(index + 1, matrice[i].end(), it + 1);
		if (it != elmFonctor.begin())
			sousClause1 = equal(matrice[i].begin(), index, elmFonctor.begin());
		if (sousClause1 && sousClause2)
		{
			cout << sep << *(index);
			sep = ", ";
		}
	}
	cout << "}" << endl;
}

void afficherCollectionRequete(string entree)
{
	char *identificateur = strtok((char *)entree.c_str(), "?(");
	Fonctor fonctor = Fonctor(identificateur);
	Type type = Type(identificateur);
	if (arbreF.contient(fonctor))
		cout << *(arbreF.rechercher(fonctor));
	else if (arbreT.contient(type))
		cout << *(arbreT.rechercher(type));
	else
		erreur("Le type ou le fonctor n'existe pas, dans la base de connaissances.");
}

//
//		UTILITAIRES
//

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
	exit(1);
}
