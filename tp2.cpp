#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "arbreavl.h"
#include "type.h"

using namespace std;



int main(int argc, const char** argv){    
    vector<string> toto;
    toto.push_back("Hello"); 
    toto.push_back("Chat"); 
    toto.push_back("Chien"); 
    toto.push_back("poto");  
    Type *type= new Type("Toto", toto); 

    ArbreAVL<Type> *tree = new ArbreAVL<Type>(); 

    tree->inserer(*type); 
    Type *type2 = new Type("coco", toto);
    tree->inserer(*type2); 

    if(tree->contient (*type)){
        cout << *type2 << endl; 
    }
     

    


    // ifstream fichier(argv[1], ios::in); 

    // if(fichier)
    // {
    //     //process l'entrée
    //     fichier.close();
    // }
    // else{
    //     cerr << "Impossible d'ouvrir le fichier." << endl; 
    // }

}
   
