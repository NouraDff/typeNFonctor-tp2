## Travail Pratique
### Description   
Ce programme est le résultat d'un travail pratique réalisé à l'UQAM à l'Hiver 2019 dans le cadre du cours Structures de données et algorithmes. 
Il a été réalisé par Laurianne Guindon et Noura Djaffri. 

Ce programme permet de réaliser des requêtes afin consulter une base de connaissances. 
Deux requêtes sont possible: 

`<nom>?`
* Le nom peut être foncteur ou un type 
* Affiche le contenue associé 

Exemple :
```
type aaaaaa = {baaaaa, caaaaa}
>> aaaaaa? (requête)
>> {baaaaa, caaaaa} (résultat)
```

```
foncteur edaaaa :: aaaaaa
(baaaaa)
>> edaaaa? 
>> (baaaaa) 
```

`<foncteur>(<type>, ?, ..., <type>)`
* Affiche toutes les possibiltés qui peuvent
* remplacer le ? dans les clauses d'un foncteur
```
>> edaaaa(?)
>> {baaaaa}
```

## Lancer le programme

Pour compiler le programme, il suffit de lancer sur une ligne de commande `make`
L'exécutif du programme se nomme tp2 et prend en argument le nom du fichier qui contient la base de connaissances. 
```
>> ./tp2 baseDeConnaissances.txt
```
Il est ensuite possible de réaliser les requêtes mentionnées plus haut. 

## Note

Le fichier de base de connaissances n'est pas fournit dans ce dépôt.
Les types sont de la forme suivante:
```
type aaaaaa = {baaaaa, caaaaa}
```
Les fonctors sont de la forme suivante:

```
foncteur fdaaaa :: daaaaa, haaaaa
(eaaaaa, iaaaaa)
(faaaaa, jaaaaa)
(gaaaaa, abaaaa)
```
