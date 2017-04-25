#include "chi2.h"
#include <string.h>

double chi2(double m, double b, double *x, double *y, double *yerr, int N) {
    int n;
    double result = 0.0, diff;

    for (n = 0; n < N; n++) {
        diff = (y[n] - (m * x[n] + b)) / yerr[n];
        result += diff * diff;
    }

    return result;
}

int ca(char *s) {
    int n = 0;
    size_t i;

    for (i = 0; i < strlen(s); i++) {
        if (s[i] == 'a') n++;
    }

    return n;
}
