#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <raylib.h>
#include "Case.h"
#include "Arbre.h"
#include <string.h>

    Texture2D tailTexture;
    Texture2D turnTexture;
    Texture2D headTexture;
    Texture2D bodyTexture;
    Texture2D tail_aiTexture;
    Texture2D turn_aiTexture;
    Texture2D head_aiTexture;
    Texture2D body_aiTexture;
    Texture2D appleTexture;
    Texture2D titleTexture;
    Music musicMenu;
    Music musicJeu;
    Sound fxPomme;
    Sound fxBack;
    Sound fxButton;
    Sound fxPause;

//la position du corp des serpents sont directement sauvegardait dans la map donc tout ce que l'on a à savoir a chaque tour c'est où est la tete
//donc dans chaque case du tableau on enregistre si il y a quelque chose et qui c'est     et on enregistre dans combien de temps il doit ce libérer




//pris indique si la case est prise -1=pomme 0=vide 1=joueur 2=ia
//tempo indique dans combien de temps la case sera libre (0 si pris=0 ou-1)

caze** cree_map(int n){
    caze** map=malloc(n*sizeof(caze*));
    int i,j;
    for(i=0;i<n;i=i+1){
        map[i]=malloc(n*sizeof(caze));
        
    }
    
    for(i=0;i<n;i=i+1){
        for(j=0;j<n;j=j+1){
            map[i][j]=malloc(sizeof(struct zcase));
            map[i][j]->pris=0;
            map[i][j]->tempo=0;
        }
    }

return map;
}


//dir c'est la direction prise 1=haut 2=droite 3=gauche 4=bas
int aller(caze** map,int n,int* x,int* y,int dir){
    if(dir==4){
        if(map[(*y+1)%n][*x]->pris<1||map[(*y+1)%n][*x]->tempo==1){
            *y=(*y+1)%n;
            return 0;
        }
        else{
            return -1;
        }
    }
    else{
        if(dir==3){
            if(map[*y][(*x+1)%n]->pris<1||map[*y][(*x+1)%n]->tempo==1){
                *x=(*x+1)%n;
                return 0;
            }
            else{
                return -1;
            }
        }
        else{
            if(dir==2){
                if(map[*y][(*x+n-1)%n]->pris<1||map[*y][(*x+n-1)%n]->tempo==1){
                    *x=(*x+n-1)%n;
                    return 0;
                }
                else{
                    return -1;
                }
            }
            else{
                if(dir==1){
                    if(map[(*y+n-1)%n][*x]->pris<1||map[(*y+n-1)%n][*x]->tempo==1){
                        *y=(*y+n-1)%n;
                        return 0;
                    }
                    else{
                        return -1;
                    }
                }
                else{
                    printf("mauvaise dir\n");
                    return -2;
                }
            }
        }
    }
}
//si la position choisit est libre il y va retun 0;
//si la position choisit est prise on doit perdre return -1
//mauvais direction (problème de code) return -2







void faire_apparaitre_pomme(caze** map,int n){
    //pour debug

    // int i,j;
    // for(i=0;i<n;i=i+1){
    //     for(j=0;j<n;j=j+1){
    //         if(map[i][j]->pris==-1){
    //             printf("tu as fait n'importe quoi avec les pommes\n");
    //         }
    //     }
    // }


    int x=rand() % n;
    int y = rand() % n;
    if(map[y][x]->pris>0){
        faire_apparaitre_pomme(map,n);
    }
    else{
        map[y][x]->pris=-1;
    }
    
}


//position du joueur x y       position de l'ia zx zy
void next_turn(caze** map,int n,int x,int y,int* taille,int zx,int zy,int*ztaille, int sound){
    
    int i,j;
    if(map[y][x]->pris==-1){
        for(i=0;i<n;i=i+1){
            for(j=0;j<n;j=j+1){
                if(map[i][j]->tempo==0){

                }
                else{
                    if(map[i][j]->pris==2){
                        if(map[i][j]->tempo >1){
                            map[i][j]->tempo = map[i][j]->tempo - 1;                            
                        }
                        else{
                            //tempo=1
                            map[i][j]->tempo = 0;
                            map[i][j]->pris = 0;
                        }
                    }
                }
            }
        }
    if(sound){
        PlaySound(fxPomme);
    }
    *taille=*taille + 1;
    map[y][x]->tempo=*taille;
    map[zy][zx]->tempo=*ztaille;
    map[y][x]->pris=1;
    map[zy][zx]->pris=2;
    faire_apparaitre_pomme(map,n);
    
    }
    else {
        if(map[zy][zx]->pris==-1){
            for(i=0;i<n;i=i+1){
                for(j=0;j<n;j=j+1){
                    if(map[i][j]->tempo==0){

                    }
                    else{
                        if(map[i][j]->pris==1){
                            if(map[i][j]->tempo >1){
                                map[i][j]->tempo = map[i][j]->tempo - 1;
                            }
                            else{
                            //tempo=1
                                map[i][j]->tempo = 0;
                                map[i][j]->pris = 0;
                            }
                        }

                    }
                }
            }
        if(sound){
            PlaySound(fxPomme);
        }
        *ztaille=*ztaille+1;
        map[y][x]->tempo=*taille;
        map[zy][zx]->tempo=*ztaille;
        map[y][x]->pris=1;
        map[zy][zx]->pris=2;
        faire_apparaitre_pomme(map,n);
        

        }
        else{
            for(i=0;i<n;i=i+1){
                for(j=0;j<n;j=j+1){
                    if(map[i][j]->tempo==0){

                    }
                    else{
                        if(map[i][j]->tempo>1){
                            map[i][j]->tempo = map[i][j]->tempo - 1;
                        }
                        else{
                            //tempo=1
                            map[i][j]->tempo = 0;
                            map[i][j]->pris = 0;
                        }

                    }
                }
            }
            map[y][x]->tempo=*taille;
            map[zy][zx]->tempo=*ztaille;
            map[y][x]->pris=1;
            map[zy][zx]->pris=2;
        }
    }
}

int qui_gagne(int resultat,int zresultat,int taille,int win){
    if(resultat==-1){
        return 2;
    }
    else{
        if(zresultat==-1){
            return 1;
        }
        else{
            if(taille==win){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
}


caze** copy_map(caze** map, int n) {
    caze** new_map = cree_map(n);
    int i,j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            new_map[i][j]->pris = map[i][j]->pris;
            new_map[i][j]->tempo = map[i][j]->tempo;
        }
    }
    return new_map;
}


void generer_enfants(Arbre a, int n) {
    int x, y, zx, zy, taille, ztaille, res, dir;
    Arbre fils;

    for (dir = 1; dir <= 4; dir++){
        x = a->x;
        y = a->y;
        taille = a->taille;
        zx = a->zx;
        zy = a->zy;
        ztaille = a->ztaille;

        caze** new_map = copy_map(a->map, n);

        if (a->joueur == 2){
            res = aller(new_map, n, &zx, &zy, dir);
        }
        else {
            res = aller(new_map, n, &x, &y, dir);
        }

        if (res == -1) {
            free_map(new_map, n);
            continue;
        }

        next_turn(new_map, n, x, y, &taille, zx, zy, &ztaille, 0);
        if (a->joueur == 2){
            fils = creer_noeud(new_map, x, y, taille, zx, zy, ztaille, 2);
        }
        else {
            fils = creer_noeud(new_map, x, y, taille, zx, zy, ztaille, 1);
        }

        if (dir == 1) a->N1 = fils;
        if (dir == 2) a->N2 = fils;
        if (dir == 3) a->N3 = fils;
        if (dir == 4) a->N4 = fils;
    }
}

int distancex(int x1, int x2, int n) {
    int dx = abs(x1 - x2);
    if (dx > n/2){
        dx = n - dx;
    }
    return dx;
}

int distancey(int y1, int y2, int n) {
    int dy = abs(y1 - y2);
    if (dy > n/2){
        dy = n - dy;
    }
    return dy;
}

int cases_libres(caze** map, int n, int x, int y) {
    int nx, ny, i, libre = 0;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (i=0; i<4; i++) {
        nx = (x+dx[i]+n) % n;
        ny = (y+dy[i]+n) % n;
        if (map[ny][nx]->pris == 0){
            libre++;
        }
    }
    return libre;
}

int flood_fill(caze** map, int n, int sx, int sy) {
    int visited[n][n];
    memset(visited, 0, sizeof(visited));
    int queueX[n*n], queueY[n*n];
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    int front = 0, back = 0, count = 1, x, y, nx ,ny, i;

    queueX[back] = sx;
    queueY[back] = sy;
    back++;
    visited[sy][sx] = 1;

    while (front < back){
        x = queueX[front];
        y = queueY[front];
        front++;
        for (i=0; i<4; i++){
            nx = (x+dx[i]+n) % n;
            ny = (y+dy[i]+n) % n;
            if (!visited[ny][nx] && map[ny][nx]->pris == 0) {
                visited[ny][nx] = 1;
                queueX[back] = nx;
                queueY[back] = ny;
                back++;
                count++;
            }
        }
    }

    return count;
}

int evaluate_hard(Arbre a, int n){
    int zx = a->zx;
    int zy = a->zy;
    int x = a->x;
    int y = a->y;
    int px = -1, py = -1;
    int distIA=0, distJ=0, spaceIA, spaceJ, libreIA, distPlayers, i, j;
    int score = 0;

    //MORT
    if (a->map[zy][zx]->pris > 0 && a->map[zy][zx]->tempo > 1) {
        if (a->map[zy][zx]->tempo < a->ztaille) return -50000; 
    }

    //RECHERCHE DE LA POMME
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            if (a->map[i][j]->pris == -1){
                py=i;
                px=j;
                break;
            }
        }
    }
    if (px != -1){
        distIA = distancex(zx, px, n) + distancey(zy, py, n);
        distJ  = distancex(x, px, n) + distancey(y, py, n);
    }

    //espace global
    spaceIA = flood_fill(a->map, n, zx, zy);
    spaceJ  = flood_fill(a->map, n, x, y);

    //liberté locale
    libreIA = cases_libres(a->map, n, zx, zy);
    distPlayers = distancex(zx, x, n) + distancey(zy, y, n);

    //survivre / espace
    score += (spaceIA - spaceJ) * 20;

    //éviter pièges immédiats
    score += libreIA * 75;

    //distance pomme
    score += (distJ - distIA) * 70;
    score += (n*2 - distIA) * 50;

    //taille
    score += (a->ztaille - a->taille) * 1000;

    //agressivité
    score -= distPlayers * 10;

    return score;
}

int evaluate_medium(Arbre a, int n){
    int zx = a->zx;
    int zy = a->zy;
    int x = a->x;
    int y = a->y;
    int px = -1, py = -1;
    int distIA=0, distJ=0, i, j;
    int score = 0;

    //MORT
    if (a->map[zy][zx]->pris > 0 && a->map[zy][zx]->tempo > 1) {
        if (a->map[zy][zx]->tempo < a->ztaille) return -50000; 
    }

    //RECHERCHE DE LA POMME
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            if (a->map[i][j]->pris == -1){
                py=i;
                px=j;
                break;
            }
        }
    }
    if (px != -1){
        distIA = distancex(zx, px, n) + distancey(zy, py, n);
        distJ  = distancex(x, px, n) + distancey(y, py, n);
    }

    //distance pomme
    score += (distJ - distIA) * 70;
    score += (n*2 - distIA) * 50;

    //taille
    score += (a->ztaille - a->taille) * 1000;

    return score;
}

int evaluate_easy(Arbre a, int n){
    int zx = a->zx;
    int zy = a->zy;
    int x = a->x;
    int y = a->y;
    int spaceIA, spaceJ, libreIA;
    int score = 0;

    //MORT
    if (a->map[zy][zx]->pris > 0 && a->map[zy][zx]->tempo > 1) {
        if (a->map[zy][zx]->tempo < a->ztaille) return -50000; 
    }

    //espace global
    spaceIA = flood_fill(a->map, n, zx, zy);
    spaceJ  = flood_fill(a->map, n, x, y);

    //liberté locale
    libreIA = cases_libres(a->map, n, zx, zy);

    //survivre / espace
    score += (spaceIA - spaceJ) * 200;

    //éviter pièges immédiats
    score += libreIA * 750;

    return score;
}


int minimax(Arbre a, int profondeur, int alpha, int beta, int n, int (*evaluate)(Arbre, int), int* nb_noeuds){
    (*nb_noeuds)++;
    Arbre fils[4] = {a->N1, a->N2, a->N3, a->N4};
    int i, Max, Min, eval, haschild = 0;

    if (est_arbre_vide(a)){
        return -100000;
    }
    if (profondeur == 0){
        return evaluate(a, n);
    }
    if (a->joueur == 2){
        Max = -100000;
        for (i = 0; i < 4; i++){
            if (fils[i] == NULL){
                continue;
            }
            haschild = 1;
            eval = minimax(fils[i], profondeur - 1, alpha, beta, n, evaluate, nb_noeuds);

            if (eval > Max) Max = eval;
            if (eval > alpha) alpha = eval;
            if (beta <= alpha) break;
        }
        if (!haschild) return evaluate(a, n);
        return Max;
    }
    else {
        Min = 100000;
        for (i = 0; i < 4; i++){
            if (fils[i] == NULL){
                continue;
            }
            haschild = 1;
            eval = minimax(fils[i], profondeur - 1, alpha, beta, n, evaluate, nb_noeuds);

            if (eval < Min) Min = eval;
            if (eval < beta) beta = eval;
            if (beta <= alpha) break;
        }
        if (!haschild) return evaluate(a, n);
        return Min;
    }
}

void construire_arbre(Arbre a, int n, int profondeur){ 
    int i;
    if (profondeur == 0){
        return;
    }
    generer_enfants(a, n); 
    Arbre fils[4] = {a->N1, a->N2, a->N3, a->N4}; 
    for (i=0; i<4; i++) {
        if (fils[i] != NULL) {
            construire_arbre(fils[i], n, profondeur - 1);
        }
    }
}

int choisir_direction(Arbre a, int n, int dif, int* nb_noeuds){
    *nb_noeuds = 0;
    clock_t start = clock();
    Arbre fils[4] = {a->N1, a->N2, a->N3, a->N4};
    int bestscore = -100000, bestdir = 1, score ,i;
    if (dif == 0){
        for (i=0; i<4; i++) {
            if (fils[i] == NULL){
                continue;
            }
            score = minimax(fils[i], 4, -100, 100, n, evaluate_easy, nb_noeuds);
            if (score > bestscore) {
                bestscore = score;
                bestdir = i + 1;
                // printf("dir %d -> score %d\n", i+1, score);
            }
        }
    }
    else if (dif == 1){
        for (i=0; i<4; i++) {
            if (fils[i] == NULL){
                continue;
            }
            score = minimax(fils[i], 4, -100, 100, n, evaluate_medium, nb_noeuds);
            if (score > bestscore) {
                bestscore = score;
                bestdir = i + 1;
                // printf("dir %d -> score %d\n", i+1, score);
            }
        }
    }
    else if (dif == 2){
        for (i=0; i<4; i++) {
            if (fils[i] == NULL){
                continue;
            }
            score = minimax(fils[i], 4, -100, 100, n, evaluate_hard, nb_noeuds);
            if (score > bestscore) {
                bestscore = score;
                bestdir = i + 1;
                // printf("dir %d -> score %d\n", i+1, score);
            }
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("temps de calcul : %f ms\n", time_spent * 1000);
    printf("nombre de noeuds évalués : %d\n", *nb_noeuds);
    return bestdir;
}

void dessine_plateau(caze** map, int n, int screenWidth, int taille, int ztaille, int dir, int zdir) {
    // Calcul de la taille d'une case (ex: 800px / 20 cases = 40px par case)
    int cellSize = screenWidth / n;
    Vector2 origin = { cellSize / 2, cellSize / 2 };
    Rectangle source = { 0.0f, 0.0f, (float)appleTexture.width, (float)appleTexture.height };
    int act;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Définition de la zone à dessiner (x, y, largeur, hauteur)
            // On retire 1 pixel à la largeur/hauteur pour créer un petit espacement (grille)
            Rectangle rect = { j * cellSize, i * cellSize, cellSize - 1, cellSize - 1 };
            Rectangle dest = { j * cellSize + cellSize / 2, i * cellSize + cellSize / 2, cellSize, cellSize };
            

            // On choisit la couleur selon le contenu de la case
            if((i+j)%2==0) {
                DrawRectangleRec(rect, (Color){ 30, 40, 60, 255 }); // Gris foncé
            }
            else {
                DrawRectangleRec(rect, (Color){ 10, 20, 40, 255 }); // Gris clair
            }
            if (map[i][j]->pris==-1) {
                DrawTexturePro(appleTexture, source, dest, origin, 0, WHITE);
            }
            act = map[i][j]->tempo;
            switch (map[i][j]->pris) {
                case 1:  // Joueur 1 (Toi)
                    if(map[i][j]->tempo==1) { //Queue
                            if(map[(i+1)%n][j]->pris==1 && map[(i+1)%n][j]->tempo==2) {
                                DrawTexturePro(tailTexture, source, dest, origin, 180, WHITE);
                            }
                            else if(map[((i - 1) + n) % n][j]->pris==1 && map[((i - 1) + n) % n][j]->tempo==2) {
                                DrawTexturePro(tailTexture, source, dest, origin, 0, WHITE);
                            }
                            else if(map[i][(j+1)%n]->pris==1 && map[i][(j+1)%n]->tempo==2) {
                                DrawTexturePro(tailTexture, source, dest, origin, 90, WHITE);
                            }
                            else if(map[i][((j - 1) + n) % n]->pris==1 && map[i][((j - 1) + n) % n]->tempo==2) {
                                DrawTexturePro(tailTexture, source, dest, origin, 270, WHITE);
                            }
                        }
                    else if(map[i][j]->tempo==taille) { //Tête
                            if(dir==1) {
                                DrawTexturePro(headTexture, source, dest, origin, 0, WHITE);
                            }
                            else if(dir==2) {
                                DrawTexturePro(headTexture, source, dest, origin, 270, WHITE);
                            }
                            else if(dir==3) {
                                DrawTexturePro(headTexture, source, dest, origin, 90, WHITE);
                            }
                            else if(dir==4) {
                                DrawTexturePro(headTexture, source, dest, origin, 180, WHITE);
                            }
                        }
                    else { //Corps
                            if((map[i][(j+1)%n]->pris==1) && (map[i][((j-1)+n)%n]->tempo == act-1) && (map[i][(j+1)%n]->tempo == act+1) && (map[i][((j - 1) + n) % n]->pris==1)) { //gauche
                                DrawTexturePro(bodyTexture, source, dest, origin, 90, WHITE);
                            }
                            else if((map[(i+1)%n][j]->pris==1) && (map[(i+1)%n][j]->tempo == act-1) && (map[((i-1)+n)%n][j]->tempo == act+1) && (map[((i-1)+n)%n][j]->pris==1)) { //haut
                                DrawTexturePro(bodyTexture, source, dest, origin, 0, WHITE);
                            }
                            else if((map[i][(j+1)%n]->pris==1) && (map[i][(j+1)%n]->tempo == act-1) && (map[i][((j-1)+n)%n]->tempo == act+1) && (map[i][((j - 1) + n) % n]->pris==1)) { //droite
                                DrawTexturePro(bodyTexture, source, dest, origin, 270, WHITE);
                            }
                            else if((map[(i+1)%n][j]->pris==1) && (map[(i+1)%n][j]->tempo == act+1) && (map[((i-1)+n)%n][j]->tempo == act-1) && (map[((i-1)+n)%n][j]->pris==1)) { //bas
                                DrawTexturePro(bodyTexture, source, dest, origin, 180, WHITE);
                            }
                            else if(map[(i+1)%n][j]->pris==1 && map[i][(j+1)%n]->pris==1  && (((map[i][(j+1)% n]->tempo==act-1 )&&( map[(i+1) % n][j]->tempo==act+1))||((map[i][(j+1)% n]->tempo==act+1 )&&( map[(i+1)% n][j]->tempo==act-1)))) { //vers droite
                                DrawTexturePro(turnTexture, source, dest, origin, 0, WHITE);
                            }
                            else if(map[(i+1)%n][j]->pris==1 && map[i][((j - 1) + n) % n]->pris==1 && (((map[i][((j-1)+n)% n]->tempo==act-1 )&&( map[(i+1) % n][j]->tempo==act+1))||((map[i][((j-1)+n)% n]->tempo==act+1 )&&( map[(i+1)% n][j]->tempo==act-1)))){ //vers haut
                                DrawTexturePro(turnTexture, source, dest, origin, 90, WHITE);
                            }
                            else if(map[((i - 1) + n) % n][j]->pris==1 && map[i][(j+1)%n]->pris==1 && (((map[i][(j+1)% n]->tempo==act-1 )&&( map[((i-1) + n) % n][j]->tempo==act+1))||((map[i][(j+1)% n]->tempo==act+1 )&&( map[((i-1) + n) % n][j]->tempo==act-1)))) { //vers bas
                                DrawTexturePro(turnTexture, source, dest, origin, 270, WHITE);
                            }
                            else if(map[((i - 1) + n) % n][j]->pris==1 && map[i][((j - 1) + n) % n]->pris==1 && (((map[i][((j-1)+n)% n]->tempo==act-1 )&&( map[((i-1) + n) % n][j]->tempo==act+1))||((map[i][((j-1)+n)% n]->tempo==act+1 )&&( map[((i-1) + n) % n][j]->tempo==act-1)))) { //vers gauche
                                DrawTexturePro(turnTexture, source, dest, origin, 180, WHITE);
                            }
                        }
                    break; 
                case 2:  // Joueur 2 (IA)
                    if(map[i][j]->tempo==1) { //Queue
                            if(map[(i+1)%n][j]->pris==2 && map[(i+1)%n][j]->tempo==2) {
                                DrawTexturePro(tail_aiTexture, source, dest, origin, 180, WHITE);
                            }
                            else if(map[((i - 1) + n) % n][j]->pris==2 && map[((i - 1) + n) % n][j]->tempo==2) {
                                DrawTexturePro(tail_aiTexture, source, dest, origin, 0, WHITE);
                            }
                            else if(map[i][(j+1)%n]->pris==2 && map[i][(j+1)%n]->tempo==2) {
                                DrawTexturePro(tail_aiTexture, source, dest, origin, 90, WHITE);
                            }
                            else if(map[i][((j - 1) + n) % n]->pris==2 && map[i][((j - 1) + n) % n]->tempo==2) {
                                DrawTexturePro(tail_aiTexture, source, dest, origin, 270, WHITE);
                            }
                        }
                    else if(map[i][j]->tempo==ztaille) { //Tête
                            if(zdir==1) {
                                DrawTexturePro(head_aiTexture, source, dest, origin, 0, WHITE);
                            }
                            else if(zdir==2) {
                                DrawTexturePro(head_aiTexture, source, dest, origin, 270, WHITE);
                            }
                            else if(zdir==3) {
                                DrawTexturePro(head_aiTexture, source, dest, origin, 90, WHITE);
                            }
                            else if(zdir==4) {
                                DrawTexturePro(head_aiTexture, source, dest, origin, 180, WHITE);
                            }
                        }
                    else { //Corps
                            if((map[i][(j+1)%n]->pris==2) && (map[i][((j-1)+n)%n]->tempo == act-1) && (map[i][(j+1)%n]->tempo == act+1) && (map[i][((j - 1) + n) % n]->pris==2)) { //gauche
                                DrawTexturePro(body_aiTexture, source, dest, origin, 90, WHITE);
                            }
                            else if((map[(i+1)%n][j]->pris==2) && (map[(i+1)%n][j]->tempo == act-1) && (map[((i-1)+n)%n][j]->tempo == act+1) && (map[((i-1)+n)%n][j]->pris==2)) { //haut
                                DrawTexturePro(body_aiTexture, source, dest, origin, 0, WHITE);
                            }
                            else if((map[i][(j+1)%n]->pris==2) && (map[i][(j+1)%n]->tempo == act-1) && (map[i][((j-1)+n)%n]->tempo == act+1) && (map[i][((j - 1) + n) % n]->pris==2)) { //droite
                                DrawTexturePro(body_aiTexture, source, dest, origin, 270, WHITE);
                            }
                            else if((map[(i+1)%n][j]->pris==2) && (map[(i+1)%n][j]->tempo == act+1) && (map[((i-1)+n)%n][j]->tempo == act-1) && (map[((i-1)+n)%n][j]->pris==2)) { //bas
                                DrawTexturePro(body_aiTexture, source, dest, origin, 180, WHITE);
                            }
                            else if(map[(i+1)%n][j]->pris==2 && map[i][(j+1)%n]->pris==2  && (((map[i][(j+1)% n]->tempo==act-1 )&&( map[(i+1) % n][j]->tempo==act+1))||((map[i][(j+1)% n]->tempo==act+1 )&&( map[(i+1)% n][j]->tempo==act-1)))) { //vers droite
                                DrawTexturePro(turn_aiTexture, source, dest, origin, 0, WHITE);
                            }
                            else if(map[(i+1)%n][j]->pris==2 && map[i][((j - 1) + n) % n]->pris==2 && (((map[i][((j-1)+n)% n]->tempo==act-1 )&&( map[(i+1) % n][j]->tempo==act+1))||((map[i][((j-1)+n)% n]->tempo==act+1 )&&( map[(i+1)% n][j]->tempo==act-1)))){ //vers haut
                                DrawTexturePro(turn_aiTexture, source, dest, origin, 90, WHITE);
                            }
                            else if(map[((i - 1) + n) % n][j]->pris==2 && map[i][(j+1)%n]->pris==2 && (((map[i][(j+1)% n]->tempo==act-1 )&&( map[((i-1) + n) % n][j]->tempo==act+1))||((map[i][(j+1)% n]->tempo==act+1 )&&( map[((i-1) + n) % n][j]->tempo==act-1)))) { //vers bas
                                DrawTexturePro(turn_aiTexture, source, dest, origin, 270, WHITE);
                            }
                            else if(map[((i - 1) + n) % n][j]->pris==2 && map[i][((j - 1) + n) % n]->pris==2 && (((map[i][((j-1)+n)% n]->tempo==act-1 )&&( map[((i-1) + n) % n][j]->tempo==act+1))||((map[i][((j-1)+n)% n]->tempo==act+1 )&&( map[((i-1) + n) % n][j]->tempo==act-1)))) { //vers gauche
                                DrawTexturePro(turn_aiTexture, source, dest, origin, 180, WHITE);
                            }
                        }
                    break;
                default: // Vide
                    break;
            }
        }
    }
}

void menu_pause(int screenWidth){
        BeginDrawing();
            ClearBackground((Color){ 0, 15, 30, 255 });
            DrawText("PAUSE", screenWidth/2 - MeasureText("PAUSE", 60)/2, 200, 60, RAYWHITE);
            DrawText("Appuyez sur ESPACE pour reprendre", screenWidth/2 - MeasureText("Appuyez sur ESPACE pour reprendre", 20)/2, 300, 20, RAYWHITE);
            DrawText("Appuyez sur ECHAP pour quitter", screenWidth/2 - MeasureText("Appuyez sur ECHAP pour quitter", 20)/2, 400, 20, RAYWHITE);
        EndDrawing();
}

void menu_fin(int gagnant, int screenWidth, int score){ 
    BeginDrawing();
        ClearBackground((Color){ 0, 15, 30, 255 });
        if(gagnant==1){
            DrawText("VOUS AVEZ GAGNE", screenWidth/2 - MeasureText("VOUS AVEZ GAGNE", 40)/2, 150, 40, RAYWHITE);
        }
        else{
            DrawText("VOUS AVEZ PERDU", screenWidth/2 - MeasureText("VOUS AVEZ PERDU", 40)/2, 150, 40, RAYWHITE);
        }
        DrawText(TextFormat("SCORE : %d", score), screenWidth/2 - MeasureText(TextFormat("SCORE : %d", score), 30)/2, 220, 30, RAYWHITE);
        DrawText("Appuyez sur ENTRER pour rejouer", screenWidth/2 - MeasureText("Appuyez sur ENTRER pour rejouer", 20)/2, 300, 20, RAYWHITE);
        DrawText("Appuyez sur ECHAP pour quitter", screenWidth/2 - MeasureText("Appuyez sur ECHAP pour quitter", 20)/2, 400, 20, RAYWHITE);
    EndDrawing();
}

int DrawButton(Rectangle rect, const char* text, Color baseColor, Color hoverColor, Color textcolor) { //fonction pour dessiner un bouton et detecter si on clique dessus
    Vector2 pointeur = GetMousePosition();
    int hover = CheckCollisionPointRec(pointeur, rect);
    Color couleur_aff = hover ? hoverColor : baseColor;
    DrawRectangleRec(rect, couleur_aff);
    DrawRectangleLinesEx(rect, 2, (Color){ 80, 95, 110, 255 });
    int fontSize = 40;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, rect.x + (rect.width/2 - textWidth/2), rect.y + (rect.height/2 - fontSize/2), fontSize, textcolor);
    return (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}


int menu_credits(int screenWidth){ 
    while(!WindowShouldClose()) {
        UpdateMusicStream(musicMenu);
        if(IsKeyPressed(KEY_BACKSPACE)) return -1;
        int fontSize = 40;
        BeginDrawing();
            ClearBackground((Color){ 0, 15, 30, 255 });
            DrawText("Développé par :", screenWidth/2 - MeasureText("Développé par :", 50)/2, 100, 50, RAYWHITE);
            DrawText("Antony Villalon", screenWidth/2 - MeasureText("Antony Villalon", fontSize)/2, 200, fontSize, RAYWHITE);
            DrawText("Gabriel Morillon", screenWidth/2 - MeasureText("Gabriel Morillon", fontSize)/2, 300, fontSize, RAYWHITE);
            DrawText("Ethan Renucci", screenWidth/2 - MeasureText("Ethan Renucci", fontSize)/2, 400, fontSize, RAYWHITE);
            DrawText("Appuyez sur BACKSPACE pour revenir au menu", screenWidth/2 - MeasureText("Appuyez sur BACKSPACE pour revenir au menu", 20)/2, 500, 20, RAYWHITE);
        EndDrawing();
    }
    return 0;   
}

int menu_jouer(int screenWidth) { 
    int diff=-1;//0 pour facile 1 pour moyen 2 pour difficile
    Rectangle btnFacile = { screenWidth/2 - 100, 220, 200, 60 };
    Rectangle btnMoyen = { screenWidth/2 - 100, 300, 200, 60 };
    Rectangle btnDifficile = { screenWidth/2 - 100, 380, 200, 60 };
    while (!WindowShouldClose()) {
        UpdateMusicStream(musicMenu);
        if(IsKeyPressed(KEY_BACKSPACE)) return -1;
        BeginDrawing();
            ClearBackground((Color){ 0, 15, 30, 255 });
            DrawText("Choisissez la difficulté", screenWidth/2 - MeasureText("Choisissez la difficulté", 40)/2, 100, 40, RAYWHITE);
            if (DrawButton(btnFacile, "EASY", (Color){ 30, 40, 60, 255 }, (Color){ 10, 20, 40, 255 }, RAYWHITE)) {
                PlaySound(fxButton);
                diff = 0;
                break;
            }
            if (DrawButton(btnMoyen, "MEDIUM", (Color){ 30, 40, 60, 255 }, (Color){ 10, 20, 40, 255 }, RAYWHITE)) {
                PlaySound(fxButton);
                diff = 1;
                break;
            }
            if (DrawButton(btnDifficile, "HARD", (Color){ 30, 40, 60, 255 }, (Color){ 10, 20, 40, 255 }, RAYWHITE)) {
                PlaySound(fxButton);
                diff = 2;
                break;
            }
            DrawText("Appuyez sur BACKSPACE pour revenir au menu", screenWidth/2 - MeasureText("Appuyez sur BACKSPACE pour revenir au menu", 20)/2, 500, 20, RAYWHITE);
        EndDrawing();
    }
    return diff;
}

void menu_principal(int screenWidth, int * diff) { 
    int menu=0; //0 pour le menu 1 pour JOUER 2 pour CREDITS
    //création de la fenêtre de jeu
    PlayMusicStream(musicMenu);
    titleTexture = LoadTexture("textures/title.png");
    Rectangle btnJouer = { screenWidth/2 - 100, 330, 200, 60 };
    Rectangle btnCredits = { screenWidth/2 - 100, 410, 200, 60 };
    while (!WindowShouldClose()) {
        UpdateMusicStream(musicMenu);
        switch(menu) {
            case 0:
                BeginDrawing();
                    ClearBackground((Color){ 0, 15, 30, 255 });
                    int posX = screenWidth / 2 - titleTexture.width / 2;
                    int posY = 40;
                    DrawTexture(titleTexture, posX, posY, RAYWHITE);
                    if (DrawButton(btnJouer, "JOUER", (Color){ 30, 40, 60, 255 }, (Color){ 10, 20, 40, 255 }, (Color){ 250, 190, 40, 255 })) {
                        PlaySound(fxButton);
                        menu = 1;
                    }
                    if (DrawButton(btnCredits, "CREDITS", (Color){ 30, 40, 60, 255 }, (Color){ 10, 20, 40, 255 }, (Color){ 40, 180, 240, 255 })) {
                        PlaySound(fxButton);
                        menu = 2;
                    }
                EndDrawing();
                break;
                
            case 1:
                int res = menu_jouer(screenWidth);
                if(res==-1) {
                    PlaySound(fxBack);
                    menu=0;
                }
                else {
                    *diff = res;
                    StopMusicStream(musicMenu);
                    return;
                }
                break;

            case 2:
                int res2 = menu_credits(screenWidth);
                if(res2==-1) {
                    PlaySound(fxBack);
                    menu=0;
                }
                break;
        }
    }
}

int jeu(int ecran){
    //initialisation
    srand(time(NULL));
    int diff;
    int n=16;
    int win;
    int start=0;
    int restart=0;

    menu_principal(ecran, &diff);
    PlayMusicStream(musicJeu);
    switch (diff)
    {
        case 0:
            win=7;
            start=1;
            break;
        
        case 1:
            win=10;
            start=1;
            break;

        case 2:
            win=15;
            start=1;
            break;

        default:
            break;
    }
    if(start==1) {    
        int nb_noeuds=0;
        //joueur
        int taille=4;
        int x = n/2 - 2;
        int* px=&x;
        int y = n/2 + 1;
        int* py=&y;
        int dir=1;
        //ia
        int ztaille=4;
        int zx = n/2 + 1;
        int* pzx=&zx;
        int zy = n/2 + 1;
        int* pzy=&zy;
        int zdir=1;
        //zone de jeu
        caze** map = cree_map(n);
        //position intiale des serpents
        //joueur
        map[y][x]->pris=1;
        map[y][x]->tempo=taille;
        map[y+1][x]->pris=1;
        map[y+1][x]->tempo=taille-1;
        map[y+2][x]->pris=1;
        map[y+2][x]->tempo=taille-2;
        map[y+3][x]->pris=1;
        map[y+3][x]->tempo=taille-3;
        //ia
        map[zy][zx]->pris=2;
        map[zy][zx]->tempo=ztaille;
        map[zy+1][zx]->pris=2;
        map[zy+1][zx]->tempo=ztaille-1;
        map[zy+2][zx]->pris=2;
        map[zy+2][zx]->tempo=ztaille-2;
        map[zy+3][zx]->pris=2;
        map[zy+3][zx]->tempo=ztaille-3;
        //apparition de la première pomme
        faire_apparaitre_pomme(map,n);
        //chargement des textures
        tailTexture = LoadTexture("textures/tail.png");
        turnTexture = LoadTexture("textures/turn.png");
        headTexture = LoadTexture("textures/head.png");
        bodyTexture = LoadTexture("textures/body.png");
        tail_aiTexture = LoadTexture("textures/tail_ai.png");
        turn_aiTexture = LoadTexture("textures/turn_ai.png");
        head_aiTexture = LoadTexture("textures/head_ai.png");
        body_aiTexture = LoadTexture("textures/body_ai.png");
        appleTexture = LoadTexture("textures/apple.png");
        //définition du nombre de frames par seconde et initialisation du compteur de frames
        int frame_counter=0;


        //boucle de jeu
        int resultat = 0;
        int zresultat = 0;
        int pause=0;
        int tmpdir=0;
        while(!WindowShouldClose() &&zresultat==0 &&resultat==0 && taille<win && ztaille<win){
            UpdateMusicStream(musicJeu);
            if (IsKeyPressed(KEY_Z)&&dir!=4) tmpdir = 1;
            if (IsKeyPressed(KEY_Q)&&dir!=3) tmpdir = 2;
            if (IsKeyPressed(KEY_W)&&dir!=4) tmpdir = 1;
            if (IsKeyPressed(KEY_A)&&dir!=3) tmpdir = 2;
            if (IsKeyPressed(KEY_D)&&dir!=2) tmpdir = 3;
            if (IsKeyPressed(KEY_S)&&dir!=1) tmpdir = 4;
            if (IsKeyPressed(KEY_SPACE)) {
                pause =! pause;
                PlaySound(fxPause);
            }

            //pause du jeu
            if(pause){
                menu_pause(ecran);
                continue;
            }


            frame_counter++;
            if(frame_counter>=40){ //tour de jeu toutes les 40 frames
                if(tmpdir!=0){
                    dir=tmpdir;
                }   
                resultat =aller(map,n,px,py,dir);
                Arbre a = creer_noeud(copy_map(map, n), x, y, taille, zx, zy, ztaille, 2);
                construire_arbre(a, n, 4);
                zdir = choisir_direction(a, n, diff, &nb_noeuds);
                supprimer_arbre(a, n);
                zresultat=aller(map,n,pzx,pzy,zdir);
                next_turn(map,n,x,y,&taille,zx,zy,&ztaille, 1);
                frame_counter=0;
                tmpdir=0;
            }
                BeginDrawing(); //UI à chaque tour
                    ClearBackground(BLACK); // nettoie l'écran à chaque tour            
                    dessine_plateau(map, n, ecran, taille, ztaille, dir, zdir);           
                    DrawText(TextFormat("Score: %d", taille), 10, 10, 20, RAYWHITE);
                    DrawText(TextFormat("AI Score: %d", ztaille), ecran - MeasureText(TextFormat("AI Score: %d", ztaille), 20) - 10, 10, 20, RAYWHITE);
                EndDrawing();
        }

        //fin du jeu
        UnloadTexture(tailTexture);
        UnloadTexture(turnTexture);
        UnloadTexture(headTexture);
        UnloadTexture(bodyTexture);
        UnloadTexture(tail_aiTexture);
        UnloadTexture(turn_aiTexture);
        UnloadTexture(head_aiTexture);
        UnloadTexture(body_aiTexture);
        UnloadTexture(appleTexture);

        int gagnant=qui_gagne(resultat,zresultat,taille,win);
        while(!WindowShouldClose() && !restart){
            menu_fin(gagnant, ecran, taille);
            if(IsKeyPressed(KEY_ENTER || KEY_KP_ENTER)) {
                restart=1;
            }
        }
    }
    StopMusicStream(musicJeu);
    return restart;
}





int main(){
    int ecran=600;
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(120);
    InitWindow(ecran, ecran, "Snake Battle");
    InitAudioDevice();
    SetMasterVolume(1.0f);
    musicMenu = LoadMusicStream("music/menu_music.mp3");
    musicMenu.looping = true;
    musicJeu = LoadMusicStream("music/game_music.mp3");
    musicJeu.looping = true;
    fxPause = LoadSound("music/sound_pause.wav"); 
    fxPomme = LoadSound("music/sound_apple.wav");
    fxBack = LoadSound("music/sound_back.wav");
    fxButton = LoadSound("music/sound_button.wav");
    SetMusicVolume(musicJeu, 0.7f);
    SetMusicVolume(musicMenu, 0.7f);
    while(jeu(ecran));
    UnloadMusicStream(musicJeu);
    UnloadMusicStream(musicMenu);
    UnloadSound(fxPause);
    UnloadSound(fxButton);
    UnloadSound(fxBack);
    UnloadSound(fxPomme);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}