#include "Arbre.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

Arbre creer_arbre_vide() {
    return NULL;
}

bool est_arbre_vide(Arbre a) {
    return a == NULL;
}

Arbre creer_noeud(caze** map, int x, int y, int taille, int zx, int zy, int ztaille, int joueur) {
    Arbre tmp = malloc(sizeof(Noeud));
    tmp->map = map; //on fait pas de copie car on mettra directemnt une map copié dans en argument de la fonction
    tmp->x = x;
    tmp->y = y;
    tmp->taille = taille;
    tmp->zx = zx;
    tmp->zy = zy;
    tmp->ztaille = ztaille;
    tmp->joueur = joueur;
    tmp->N1 = NULL;
    tmp->N2 = NULL;
    tmp->N3 = NULL;
    tmp->N4 = NULL;
    return tmp;
}

void supprimer_arbre(Arbre a, int n) {
    if (a == NULL) return; // Sécurité si l'arbre est déjà vide

    // On libère récursivement les 4 fils
    supprimer_arbre(a->N1, n);
    supprimer_arbre(a->N2, n);
    supprimer_arbre(a->N3, n);
    supprimer_arbre(a->N4, n);

    // On libère les données internes
    if (a->map != NULL) {
        free_map(a->map, n); // Assure-toi que free_map est bien implémenté
    }

    // Enfin, on libère le noeud lui-même
    free(a);
}