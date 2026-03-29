#include "Case.h"
#include <stdlib.h>

void free_map(caze** map, int n) {
    if (map == NULL) return;
    for (int i = 0; i < n; i++) {
        if (map[i] != NULL) {
            // Si chaque case est un pointeur (comme dans ton cree_map) :
            for (int j = 0; j < n; j++) {
                free(map[i][j]); 
            }
            free(map[i]);
        }
    }
    free(map);
}