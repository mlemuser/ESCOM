#include <stdio.h>
#include <stdlib.h>
#include <string.h>
   
int max(int a, int b){
    return (a > b)? a : b;
}
   
int lcs( char *x, char *y, int m, int n ){
	int i,j,L[m+1][n+1];
	
	for (i=0; i<=m; i++){
		for (j=0; j<=n; j++){
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if(x[i-1] == y[j-1])
				L[i][j] = L[i-1][j-1] + 1;
			else
				L[i][j] = max(L[i-1][j], L[i][j-1]);
		}
   }
   return L[m][n];
}
   
int main(){
	char *x,*y;

	x = malloc(1000 * sizeof(char));
	y = malloc(1000 * sizeof(char));

	scanf("%s" "%s", x,y);
  
	int m = strlen(x);
	int n = strlen(y);
	printf("%d",lcs(x, y, m, n));
	return 0;
}
