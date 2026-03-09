#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int n;  printf("Enter the size of the matrix:"); scanf("%d",&n); printf("\n");
    double **a = (double**)malloc(n*sizeof(double*));
    for (int i = 0; i < n; i++){
        a[i] = (double*)malloc(n*sizeof(double));
        for (int j = 0; j < n; j++) scanf("%lf", &a[i][j]);
    }
    double res = 1.0;
    for (int i = 0 ; i<n;i++){
        if (fabs(a[i][i]) < 1e-9) {
            int f = 0; for (int j = i+1; j < n; j++){
                while (f = 0){
                    if (fabs(a[j][i]) > 1e-9){
                        double *temp = a[i]; a[i] = a[j]; a[j] = temp; f = 1;}
                }
            }
        }
        res *= a[i][i];
        for (int j = i+1; j < n; j++){
            double c = a[j][i] / a[i][i]; a[j][i] = 0;
            for (int k = i + 1; k < n; k++) a[j][k] -= c * a[i][k];
        }
    }

    printf("Determinant: %f\n", res);
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
    return 0;
}
