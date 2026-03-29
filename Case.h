#ifndef CASE_H
#define CASE_H

struct zcase {
    int pris;
    int tempo;
};

typedef struct zcase* caze;

void free_map(caze** map, int n);

#endif