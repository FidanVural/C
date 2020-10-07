#include <stdio.h>

int main(){
	int n;
	scanf("%d",&n);
	
	char a[n][n];
	char x;
	int i,j;
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf(" %c",&a[i][j]);
		}
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i!=0 && j!=0 && i!=(n-1) && j!=(n-1)){
				if(a[i][j]>a[i-1][j] && a[i][j]>a[i+1][j] && a[i][j]>a[i][j-1] && a[i][j]>a[i][j+1]){
					printf("X");
				}
				else{
					printf("%c",a[i][j]);
				}
			}
			else{
				printf("%c",a[i][j]);
			}
		}
		printf("\n");
	}
}
