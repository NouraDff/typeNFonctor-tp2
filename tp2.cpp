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

int main(int argc, const char **argv)
{
	ifstream fichier(argv[1], ios::in);

	ArbreAVL<Type> *arbreT = new ArbreAVL<Type>();
	ArbreAVL<Fonctor> *arbreF = new ArbreAVL<Fonctor>();

	if (fichier)
	{

		ArbreAVL<Type> *arbreT = new ArbreAVL<Type>();
		ArbreAVL<Fonctor> *arbreF = new ArbreAVL<Fonctor>();
		Type *tempT;
		Fonctor *tempF;
		vector<const char *> clause, typ;
		string entree, nom, str;

		while (fichier >> entree >> nom)
		{ // être sûr que tt est en lettres min!! (caract par caract: isalpha(car) && islower(car)
			cout << entree << "->" << nom << endl;
			tempT = new Type(nom);
			tempF = new Fonctor(nom);
			if (!arbreT->contient(*tempT) && !arbreF->contient(*tempF))
			{
				if (!entree.compare("type"))
				{

					getline(fichier, str);
					char *arguments = new char[str.length() + 1];
					strcpy(arguments, str.c_str());

					typ.push_back(strtok(arguments, "= {,"));
					while (typ.back() != NULL && find(typ.begin(), typ.end(), typ.back()) == typ.end() - 1) // lettres min
						typ.push_back(strtok(NULL, " ,}"));
					if (typ.back() != NULL && find(typ.begin(), typ.end(), typ.back()) != typ.end() - 1)
						cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
					else
						typ.pop_back();

					tempT->idCollection = typ;
					arbreT->inserer(*tempT);
				}
				else if (!entree.compare("foncteur"))
				{

					getline(fichier, str);
					char *types = new char[str.length() + 1];
					strcpy(types, str.c_str());

					typ.push_back(strtok(types, ": ,"));
					while (typ.back() != NULL && find(typ.begin(), typ.end(), typ.back()) == typ.end() - 1 /*&& t.back() est dans l'arbre de type*/) // lettres min
						typ.push_back(strtok(NULL, " ,"));
					if (typ.back() != NULL && find(typ.begin(), typ.end(), typ.back()) != typ.end() - 1)
						cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
					else
						typ.pop_back();

					vector<vector<const char *>> fonc;
					char *ligne;
					while (fichier.peek() == '(')
					{
						getline(fichier, str);
						ligne = new char[str.length() + 1];
						strcpy(ligne, str.c_str());

						clause.push_back(strtok(ligne, "( ,"));
						int i = 0;
						while (clause.back() != NULL && find(clause.begin(), clause.end(), clause.back()) == clause.end() - 1 /*&& c.back() est un arg de t.at(i++)*/) // lettres min
							clause.push_back(strtok(NULL, " ,)"));
						if (clause.back() != NULL && find(clause.begin(), clause.end(), clause.back()) != clause.end() - 1)
							cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
						else
							clause.pop_back();

						fonc.push_back(clause);
						clause.clear();
						clause.shrink_to_fit();
					}

					tempF->matrice = fonc;
					arbreF->inserer(*tempF);
					fonc.clear();
					fonc.shrink_to_fit();
				}
				else
				{
					cerr << "Entrée invalide." << endl; // arrêt??
				}
				typ.clear();
				typ.shrink_to_fit();
			} //else objet de même nom existe déjà
		}

		fichier.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}

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
				//Enlève la première parathèse
				string elm = input.substr(found, input.find(')'));

				//mettre chaque élément dans un vecteur
				//puis trouver à quel index est le ?
				//rechercher dans matrice ligne par ligne si ça correspond

				vector<string> elmFonctor;				
				size_t start = 0, end = 0;				
				while ((end = input.find(',', start)) != string::npos)
				{
					if (end != start)
					{
						elmFonctor.push_back(input.substr(start, end - start));
					}
					start = end + 1;
				}
				if (end != start)
				{
					elmFonctor.push_back(input.substr(start));
				}

				for (int i = 1; i < elmFonctor.size(); i++)
				{
					cout << elmFonctor.at(i) << endl;
				}
			}
		}
	}

	return 0;
}
