#include <stdio.h>

int main(){
	int n,k,q;
	scanf("%d %d %d",&n,&k,&q);
	
	int i;
	int *a=(int*)malloc(sizeof(int)*n);
	
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	int *b=(int*)malloc(sizeof(int)*q);
	for(i=0;i<n;i++){
		scanf("%d",&b[i]);
	}
	int j,t;
	for(i=0;i<k;i++){
		t=a[n-1];
		for(j=n-1;j>=0;j--){
			a[j]=a[j-1];
		}
		a[0]=t;
	}
	printf("\n");
	for(i=0;i<q;i++){
		j=b[i];
		printf("%d\n",a[j]);
	}
}

