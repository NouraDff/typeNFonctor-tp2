#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "arbreavl.h"
#include "type.h"
#include "fonctor.h"

using namespace std;



int main(int argc, const char** argv){    
    
    ArbreAVL<Fonctor> *tree = new ArbreAVL<Fonctor>(); 
    
    vector<string> boole;
    boole.push_back("vrai"); 
    boole.push_back("faux"); 

    vector<vector<string> > fct { { "vrai", "vrai", "vrai" }, 
                               { "faux", "faux", "faux" }, 
                               { "vrai", "faux", "vrai" } }; 
    Fonctor *fonctor = new Fonctor("CBoolean", boole, fct); 
    tree->inserer(*fonctor); 

    vector<vector<string> > nb { { "1", "0", "0" }, 
                               { "1", "1", "1" }, 
                               { "0", "0", "0" } }; 
    vector<string> into;
    boole.push_back("1"); 
    boole.push_back("0"); 

    Fonctor *fonctor1 = new Fonctor("Binaire", into, nb); 
    tree->inserer(*fonctor1); 


    vector<vector<string> > ou { { "v", "f", "v" }, 
                               { "f", "v", "v" }, 
                               { "v", "v", "f" } }; 
    vector<string> pro;
    boole.push_back("v"); 
    boole.push_back("f");

     Fonctor *fonctor2 = new Fonctor("Atchoum", into, nb); 
    tree->inserer(*fonctor2); 

    
    



}
   
