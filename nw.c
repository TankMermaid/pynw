#include <stdlib.h>
#include <stdio.h>

// #include "chi2.h"
#include <string.h>

#define DELETE_VALUE -1
#define INSERT_VALUE 1
#define MATCH_VALUE 0

#define MAX2(x,y) ((x) >= (y) ? (x) : (y))
#define MIN2(x,y) ((x) <= (y) ? (x) : (y))
#define MAX3(x,y,z) ((x) >= (y) && (x) >= (z) ? (x) : MAX2(y,z))
#define MIN3(x,y,z) ((x) <= (y) && (x) <= (z) ? (x) : MIN2(y,z))
#define MAX4(w,x,y,z) MAX2(MAX3(w, x, y), z)

void print_matrix(int **x, int r, int c) {
    int i;
    int j;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%i ", x[i][j]);
        }
        printf("\n");
    }
}

/* char *empty_string(size_t n) { */
/*     char s[n + 1]; */
/*     int i; */
/*     for (i = 0; i < n; i++) { */
/*         s[i] = '.'; */
/*     } */
/*     s[n] = '\0'; */
/*     return s; */
/* } */

int nw(char *s1, char *s2) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int i;
    int j;
    int match;
    int delete;
    int insert;
    int best;

    int match_score = 1;
    int mismatch_score = -1;
    int gap_score = -1;

    int nmm = 0;

    int *m[l1 + 1];
    for (i = 0; i <= l1; i++)
        //swo > check that malloc actually allocates
        m[i] = (int *)malloc((l2 + 1)* sizeof(int));

    int *o[l1];
    for (i = 0; i < l1; i++)
        o[i] = (int *)malloc(l2 * sizeof(int));

    for (i = 0; i <= l1; i++)
        m[i][0] = i * gap_score;

    for (i = 0; i <= l2; i++)
        m[0][i] = i * gap_score;

    for (i = 1; i <= l1; i++) {
        for (j = 1; j <= l2; j++) {
            //printf("i=%i j=%i\n", i, j);
            if (s1[i - 1] == s2[j - 1]) {
                match = m[i - 1][j - 1] + match_score;
            } else {
                match = m[i - 1][j - 1] + mismatch_score;
            }

            delete = m[i - 1][j] + gap_score;
            insert = m[i][j - 1] + gap_score;

            best = MAX3(match, delete, insert);
            m[i][j] = best;

            if (best == match) {
                o[i - 1][j - 1] = MATCH_VALUE;
            } else if (best == delete) {
                o[i - 1][j - 1] = DELETE_VALUE;
            } else if (best == insert) {
                o[i - 1][j - 1] = INSERT_VALUE;
            } else {
                printf("max %i not one of match=%i del=%i ins=%i\n", best, match, delete, insert);
                printf("Bad max value\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    /* print_matrix(m, l1 + 1, l2 + 1); */

    char a1[l1 + l2 + 1];
    char a2[l2 + l2 + 1];
    memset(a1, '\0', l1 + l2 + 1);
    memset(a2, '\0', l1 + l2 + 1);
    int idx1 = 0;
    int idx2 = 0;

    i = l1;
    j = l2;
    nmm = 0;

    while (i > 0 && j > 0) {
        switch(o[i - 1][j - 1]) {
            case MATCH_VALUE :
                a1[idx1] = s1[i - 1];
                a2[idx2] = s2[j - 1];
                i -= 1;
                j -= 1;

                if (s1[i] != s2[j]) {
                    /* printf("mismatch %c %c\n", s1[i], s2[j]); */
                    nmm += 1;
                } else {
                    /* printf("match %c %c\n", s1[i], s2[j]); */
                }
                break;
            case DELETE_VALUE :
                a1[idx1] = s1[i - 1];
                a2[idx2] = '-';
                /* printf("delete %i\n", i); */
                i -= 1;
                nmm += 1;
                break;
            case INSERT_VALUE :
                a1[idx1] = '-';
                a2[idx2] = s2[j - 1];
                /* printf("insert %i\n", j); */
                j -= 1;
                nmm += 1;
                break;
            default :
                printf("o at i=%i j=%i is bad=%i\n", i, j, (o[i - 1][j - 1]));
                printf("Bad max value\n");
                exit(EXIT_FAILURE);
        }

        idx1 += 1;
        idx2 += 1;
    }

    while (i > 0) {
        a1[idx1] = s1[i - 1];
        a2[idx2] = '-';
        idx1 += 1;
        idx2 += 1;
        i -= 1;
        nmm += 1;
    }

    while(j > 0) {
        a1[idx1] = '-';
        a2[idx2] = s2[j - 1];
        idx1 += 1;
        idx2 += 1;
        j -= 1;
        nmm += 1;
    }

    for (i = 0; i <= l1; i++)
        free(m[i]);

    for (i = 0; i < l1; i++)
        free(o[i]);

    printf("%s\n", a1);
    printf("%s\n", a2);
    return nmm;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: ./nw <seq>\n");
        exit(EXIT_FAILURE);
    }

    printf("%i\n", nw(argv[1], argv[2]));
    exit(EXIT_SUCCESS);
}
