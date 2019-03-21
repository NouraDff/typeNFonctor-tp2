#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include "arbreavl.h"
#include "type.h"
#include "fonctor.h"

using namespace std;

int main(int argc, const char **argv)
{
	ifstream fichier(argv[1], ios::in);


	if (fichier)
	{

		vector<char *> t, c;
		string entree, nom, str;

		while (fichier >> entree >> nom)
		{ // être sûr que tt est en lettres min!! (caract par caract: isalpha(car) && islower(car)
			cout << entree << "->" << nom << endl;
			if (!entree.compare("type"))
			{
				//treeType.rechercher(<"nom">); veut voir s'il existe avant de l'ajouter...
				getline(fichier, str);
				char *typ = new char[str.length() + 1];
				strcpy(typ, str.c_str());

				t.push_back(strtok(typ, "= {,"));
				while (t.back() != NULL && find(t.begin(), t.end(), t.back()) == t.end() - 1) // lettres min
					t.push_back(strtok(NULL, " ,}"));
				if (t.back() != NULL && find(t.begin(), t.end(), t.back()) != t.end() - 1)
					cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
				else
					t.pop_back();

				for (unsigned it = 0; it < t.size(); ++it)
					cout << t.at(it) << endl;
				// créer objet
			}
			else if (!entree.compare("foncteur"))
			{
				//treeFonctor.rechercher(<"nom">); veut voir s'il existe avant de l'ajouter...
				getline(fichier, str);
				char *typ = new char[str.length() + 1];
				strcpy(typ, str.c_str());

				t.push_back(strtok(typ, ": ,"));
				while (t.back() != NULL && find(t.begin(), t.end(), t.back()) == t.end() - 1 /*&& t.back() est dans l'arbre de type*/) // lettres min
					t.push_back(strtok(NULL, " ,"));
				if (t.back() != NULL && find(t.begin(), t.end(), t.back()) != t.end() - 1)
					cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
				else
					t.pop_back();

				for (unsigned it = 0; it < t.size(); ++it)
					cout << t.at(it) << endl;

				vector<vector<char *>> f;
				char *fonc;
				while (fichier.peek() == '(')
				{
					getline(fichier, str);
					fonc = new char[str.length() + 1];
					strcpy(fonc, str.c_str());

					c.push_back(strtok(fonc, "( ,"));
					int i = 0;
					while (c.back() != NULL && find(c.begin(), c.end(), c.back()) == c.end() - 1 /*&& c.back() est un arg de t.at(i++)*/) // lettres min
						c.push_back(strtok(NULL, " ,)"));
					if (c.back() != NULL && find(c.begin(), c.end(), c.back()) != c.end() - 1)
						cerr << "Les arguments ne sont pas tous uniques." << endl; // arrêt??
					else
						c.pop_back();

					for (unsigned it = 0; it < c.size(); ++it)
						cout << c.at(it) << endl;

					f.push_back(c);
					c.clear();
					c.shrink_to_fit();
				}
				// créer obj
				f.clear();
				f.shrink_to_fit();
			}
			else
			{
				cerr << "Entrée invalide." << endl; // arrêt??
			}
			t.clear();
			t.shrink_to_fit();
		}

		fichier.close();
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}

	/*-------------------------------------------------------------
 *
 * Lecture au clavier
 *
 * ----------------------------------------------------------*/
	// string input;
	// while (getline(cin, input) && !cin.eof())
	// {
	// 	vector<string> vec;
	// 	//mettre chaque élément dans un vector)
	// 	vec.push_back(input);
	// 	size_t found = input.find_first_of("?(");
	// 	//Si la position du caractère doit ce trouver dans la chaine de catactère
	// 	if (found < input.length() && found > 0)
	// 	{
	// 		if(found.at(found) == '?'){

	// 		}
	// 		//Coupe la chaine au ?
	// 		string identificateur = input.substr(0, found);
	// 		cout << identificateur << endl; 
	// 	}
	// }
}
