/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique ArbreAVL<T> pour le Lab6 et le TP2.

   AUTEUR(S):
    1) Noura Djaffri DJAN28569508
    2) Laurianne Guindon GUIL22579900
*/

#if !defined(__ARBREAVL_H__)
#define __ARBREAVL_H__
#include <cassert>
#include "pile.h"

template <class T>
class ArbreAVL {
  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    // Annonce l'existance d'une classe Iterateur.
    class Iterateur;

    void inserer(const T&);
    bool contient(const T&) const;
    bool vide() const;
    void vider();
    void enlever(const T&); // non requis pour le TP2.
    int  hauteur() const;
    
    // Fonctions pour obtenir un itérateur (position dans l'arbre)    
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;

    // Accès aux éléments de l'arbre via un intérateur.
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);
    
    // Copie d'un arbre AVL.
    ArbreAVL& operator = (const ArbreAVL&);

  private:
    struct Noeud{
        Noeud(const T&);
        T contenu;
        int equilibre;
        Noeud *gauche,
              *droite;
    };
    Noeud* racine;

    // Fonctions internes
    bool inserer(Noeud*&, const T&);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    const T& max(Noeud*) const;
    bool enlever(Noeud*&, const T& e);

  public:
    // Sera présenté à la semaine #7
    class Iterateur{
      public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        
        const T& operator*() const;

        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);
      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;

      friend class ArbreAVL;
    };
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c)
 : contenu(c), equilibre(0), gauche(NULL), droite(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() 
 : racine(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre)
 : racine(NULL)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
<<<<<<< HEAD
    Iterateur iter(*this);
    iter = iter.arbre_associe.rechercher(element); 

    if(iter.courant == NULL){
        return false; 
    }

    if(iter.courant->contenu == element){
        return true; 
    }
=======
    if(rechercher(element)) return true;
>>>>>>> 254d6ecf73f34fa7f8365702202908f4a4f4f87b
    return false;
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    if(noeud==NULL)
    {
        noeud = new Noeud(element);
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if(noeud->equilibre == 0)
                return false;
            if(noeud->equilibre == 1)
                return true;
            assert(noeud->equilibre==2);
            if(noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    }
    else if(noeud->contenu < element){
        if(inserer(noeud->droite, element))
        {
            noeud->equilibre--;
            if(noeud->equilibre == 0){
                return false; 
            }
            if(noeud->equilibre == -1){
                return true; 
            }
            assert(noeud->equilibre == -2);
            if(noeud->droite->equilibre == 1){
                rotationGaucheDroite(noeud->droite); 
            } 
            rotationDroiteGauche(noeud); 
        }
        return false;
    }

    // element == noeud->contenu
    noeud->contenu = element;  // Mise à jour
    return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
     std::cout << "Contenu du noeud enfant : " << temp->contenu << " | equilibre avant : " << ea << " | equilibre après : " << nea << std::endl;
    std::cout << "Contenu du noeud parent : " << racinesousarbre->droite->contenu <<   " | equilibre avant : " << eb << " | equilibre après : " << neb << std::endl;
    std::cout << std::endl; 
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    
    Noeud *temp = racinesousarbre->droite; 
    int eb = temp->equilibre; 
    int ea = racinesousarbre->equilibre;   
    int nea =  ea - (eb < 0 ? eb : 0) + 1; 
    int neb = eb + (nea > 0 ? nea : 0) + 1 ; 

    temp->equilibre = neb; 
    racinesousarbre->equilibre = nea; 
    racinesousarbre->droite = temp->gauche; 
    temp->gauche = racinesousarbre; 
    racinesousarbre = temp; 

    std::cout << "Contenu du noeud parent : " << temp->contenu << " | equilibre avant : " << eb << " | equilibre après : " << neb << std::endl;
    std::cout << "Contenu du noeud enfant : " << racinesousarbre->gauche->contenu <<   " | equilibre avant : " << ea << " | equilibre après : " << nea << std::endl;
    std::cout << std::endl; 

}

template <class T>
bool ArbreAVL<T>::vide() const
{
    if(racine == NULL){
        return true; 
    }
    return false;
}

template <class T>
void ArbreAVL<T>::vider(){
  vider(racine);
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    if(vide()){
        return; 
    }
    vider(noeud->gauche);
    vider(noeud->droite);
    delete noeud; 
    noeud = NULL;
    
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
   noeud = new Noeud(source->contenu);
   noeud->equilibre = source->equilibre; 

   if(source->gauche != NULL){
       copier(source->gauche, noeud->gauche);
   }
   if(source->droite != NULL){
       copier(source->droite, noeud->droite); 
   }
   
}

template <class T>
<<<<<<< HEAD
int  ArbreAVL<T>::hauteur() const{
    int compteur = 0 ; 
    Iterateur iter(*this);
    iter.courant = this->racine; 

    while(iter){
        if(iter.courant->equilibre >= 0){
            iter.courant = iter.courant->gauche;
            compteur+= 1; 
            continue;
        }
=======
int  ArbreAVL<T>::hauteur() const{ // vrm pas sûr... boucle infini?? // manque des param??
	Iterateur iter(*this);
	if(iter.courant!=NULL) return max(iter.courant)+1;	// si la hauteur n'est pas déjà définie... prob!?
	return 0;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const // 2 var devraient êtres passées...
{
	int hg =n->gauche->hauteur(), hd = n->droite->hauteur();
	return (hg > hd ? hg : hd); 
}
>>>>>>> 254d6ecf73f34fa7f8365702202908f4a4f4f87b

        if(iter.courant->equilibre < 0){
            iter.courant = iter.courant->droite; 
            compteur += 1; 
            continue; 
        }
    }
    
    return compteur;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
    while(n->droite != NULL){
        n = n->droite; 
    }

    return n->contenu; 
}
// -------------------------------------------------------
// ITERATEURS
// -------------------------------------------------------

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
<<<<<<< HEAD
    Iterateur iter(*this);
    
    while(iter.courant->gauche != NULL){
        iter.chemin.empiler(iter.courant); 
        iter.courant = iter.courant->gauche; 
    }
    return iter;
=======
	Iterateur iter(*this);
	iter.courant = racine;
	if(iter.courant!=NULL)
		while(iter.courant->gauche!=NULL){
			iter.chemin.empiler(iter.courant);
			iter.courant = iter.courant->gauche;
		}
	return iter;
>>>>>>> 254d6ecf73f34fa7f8365702202908f4a4f4f87b
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
<<<<<<< HEAD
    Iterateur iter(*this);
    iter.courant = iter.arbre_associe.racine; 

    while(iter){
     
        if(iter.courant->contenu == e){
            return iter; 
        }

        if(iter.courant->contenu > e){
            if(iter.courant->gauche != NULL){
                iter.chemin.empiler(iter.courant);
                iter.courant = iter.courant->gauche; 
                continue;
            }
            return iter; 
        }

        if(iter.courant->contenu < e){
            if (iter.courant->droite != NULL){
                iter.chemin.empiler(iter.courant); 
                iter.courant = iter.courant->droite;     
                continue; 
            }
            return iter;
        }
    }
    return iter;
=======
	Iterateur iter(*this);
	Noeud* n = racine;

	while(n){
		if(e < n->contenu){
			iter.chemin.empiler(n);
			n = n->gauche;
		}else if(n->contenu < e) n = n->droite;
		else{
			iter.courant = n;
			return iter;
		}
	}

	iter.chemin.vider();
	return iter;
>>>>>>> 254d6ecf73f34fa7f8365702202908f4a4f4f87b
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
	Iterateur iter(*this);
	Noeud* n = racine, *dernier=NULL;
	
	while(n){
		if(e < n->contenu){
			dernier = n;  
			iter.chemin.empiler(n);
			n = n->gauche; 
		}else if(n->contenu < e) n = n->droite;  
		else{
			iter.courant = n;  
			return iter;
		}
	}

	if(dernier!=NULL) return rechercher(dernier->contenu);
	iter.chemin.vider();
	return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
	Noeud* n = racine, *dernier=NULL;

	while(n){
		if(e < n->contenu) n = n->gauche;
		else if(n->contenu < e){
			dernier = n;
			n = n->droite;
		}else return rechercher(e);
	}

	if(dernier!=NULL) return rechercher(dernier->contenu);
	return Iterateur(*this);
}

//-----------------------------------
template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}


//-----------------------
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
 : arbre_associe(a), courant(NULL)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

// Pré-incrément (++A)
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
	assert(courant);
	Noeud* suivant = courant->droite;
	while(suivant){
		chemin.empiler(suivant);
		suivant = suivant->gauche;
	}
	if(!chemin.vide())
		courant = chemin.depiler();
	else
		courant = NULL;
	return *this;
}

// Post-incrément (A++)
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int) 
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=NULL);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

#endif
