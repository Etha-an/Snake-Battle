#include <stdio.h>
#include <stdbool.h>
#include "Case.h"

#define True 1
#define False 0

typedef struct zNoeud {
    int joueur;
    struct zNoeud *N1;
    struct zNoeud *N2;
    struct zNoeud *N3;
    struct zNoeud *N4;
    caze** map;
    int x, y, taille;
    int zx, zy, ztaille;

} Noeud;

typedef Noeud* Arbre;

Arbre creer_arbre_vide();

bool est_arbre_vide(Arbre a);

Arbre creer_noeud(caze** map, int x, int y, int taille, int zx, int zy, int ztaille, int joueur);

void supprimer_arbre(Arbre a, int n);
