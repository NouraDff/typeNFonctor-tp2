#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "arbreavl.h"

using namespace std;

int main(int argc, const char** argv){    
    ifstream fichier(argv[1], ios::in); 

    if(fichier){
        fichier.close(); 
    }
    else{
        cerr << "Impossible d'ouvrir le fichier." << endl; 
    }

}
   
