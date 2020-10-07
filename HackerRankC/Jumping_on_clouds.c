#include <stdio.h>

int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	
	int a[n],i,j;
	
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	int e=100;
	i=k;
	while(i%n!=0){
		i=i%n;
		e-=1;
		if(a[i]==1){
			e-=2;
		}
		// printf("%d\n",e);
		i+=k;
	}
	
	if(a[0]==1){
		e-=3;
	}
	else{
		e-=1;
	}
	
	printf("%d",e);
}
