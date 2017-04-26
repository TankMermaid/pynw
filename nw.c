#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #include "chi2.h"

#define DELETE_VALUE -1
#define INSERT_VALUE 1
#define MATCH_VALUE 0

#define MAX2(x,y) ((x) >= (y) ? (x) : (y))
#define MAX3(x,y,z) ((x) >= (y) && (x) >= (z) ? (x) : MAX2(y,z))

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

void string_reverse(char *s) {
    int length = strlen(s);
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void aligned_strings(int **outcomes, char *s1, char *s2, char *alignment1, char *alignment2) {
    const int l1 = strlen(s1);
    const int l2 = strlen(s2);
    int i;
    int j;
    int idx1;
    int idx2;

    memset(alignment1, '\0', l1 + l2 + 1);
    memset(alignment2, '\0', l1 + l2 + 1);

    i = l1;
    j = l2;
    idx1 = 0;
    idx2 = 0;

    while (i > 0 && j > 0) {
        switch(outcomes[i - 1][j - 1]) {
            case MATCH_VALUE :
                alignment1[idx1] = s1[i - 1];
                alignment2[idx2] = s2[j - 1];
                i -= 1;
                j -= 1;
                break;
            case DELETE_VALUE :
                alignment1[idx1] = s1[i - 1];
                alignment2[idx2] = '-';
                i -= 1;
                break;
            case INSERT_VALUE :
                alignment1[idx1] = '-';
                alignment2[idx2] = s2[j - 1];
                j -= 1;
                break;
            default :
                printf("Bad max value\n");
                exit(EXIT_FAILURE);
        }

        idx1 += 1;
        idx2 += 1;
    }

    while (i > 0) {
        alignment1[idx1] = s1[i - 1];
        alignment2[idx2] = '-';
        idx1 += 1;
        idx2 += 1;
        i -= 1;
    }

    while(j > 0) {
        alignment1[idx1] = '-';
        alignment2[idx2] = s2[j - 1];
        idx1 += 1;
        idx2 += 1;
        j -= 1;
    }

    // reverse the strings
    string_reverse(alignment1);
    string_reverse(alignment2);
}

double nw(char *s1, char *s2, int match_score, int mismatch_score, int gap_score, int print_alignments) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int i;
    int j;
    int match;
    int delete;
    int insert;
    int best;
    int n_matches, n_mismatches, n_deletions, n_insertions;

    char a1[l1 + l2 + 1];
    char a2[l2 + l2 + 1];

    int *score[l1 + 1];
    int *o[l1];

    for (i = 0; i <= l1; i++) {
        score[i] = (int *)malloc((l2 + 1) * sizeof(int));
        if (score[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < l1; i++) {
        o[i] = (int *)malloc(l2 * sizeof(int));
        if (o[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i <= l1; i++)
        score[i][0] = i * gap_score;

    for (i = 0; i <= l2; i++)
        score[0][i] = i * gap_score;

    for (i = 1; i <= l1; i++) {
        for (j = 1; j <= l2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                match = score[i - 1][j - 1] + match_score;
            } else {
                match = score[i - 1][j - 1] + mismatch_score;
            }

            delete = score[i - 1][j] + gap_score;
            insert = score[i][j - 1] + gap_score;

            best = MAX3(match, delete, insert);
            score[i][j] = best;

            if (best == delete) {
                o[i - 1][j - 1] = DELETE_VALUE;
            } else if (best == insert) {
                o[i - 1][j - 1] = INSERT_VALUE;
            } else if (best == match) {
                o[i - 1][j - 1] = MATCH_VALUE;
            } else {
                printf("max %i not one of match=%i del=%i ins=%i\n", best, match, delete, insert);
                printf("Bad max value\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    i = l1;
    j = l2;
    n_matches = 0;
    n_mismatches = 0;
    n_deletions = 0;
    n_insertions = 0;

    while (i > 0 && j > 0) {
        switch(o[i - 1][j - 1]) {
            case MATCH_VALUE :
                i -= 1;
                j -= 1;
                if (s1[i] == s2[j]) {
                    n_matches += 1;
                } else {
                    n_mismatches += 1;
                }
                break;
            case DELETE_VALUE :
                i -= 1;
                n_deletions += 1;
                break;
            case INSERT_VALUE :
                j -= 1;
                n_insertions += 1;
                break;
            default :
                printf("Bad max value\n");
                exit(EXIT_FAILURE);
        }
    }

    n_insertions += i;
    n_deletions += j;

    // make up the aligned strings and print them, separately
    if (print_alignments) {
        aligned_strings(o, s1, s2, a1, a2);
        printf("match=%i, mm=%i ins=%i del=%i l1+del=%i l2+ins=%i wrong=%i\n", n_matches, n_mismatches, n_insertions, n_deletions, l1 + n_deletions, l2 + n_insertions, l1 + n_insertions);
        printf("%s\n", a1);
        printf("%s\n", a2);
    }

    for (i = 0; i <= l1; i++)
        free(score[i]);

    for (i = 0; i < l1; i++)
        free(o[i]);

    return ((double) n_mismatches + (double) n_insertions + (double) n_deletions) / ((double) l1 + (double) n_deletions);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: ./nw <seq>\n");
        exit(EXIT_FAILURE);
    }

    printf("%f\n", nw(argv[1], argv[2], 1, -2, -2, 1));
    exit(EXIT_SUCCESS);
}
