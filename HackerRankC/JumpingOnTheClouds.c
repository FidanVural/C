#include <stdio.h>

int main(){
	int n;
	scanf("%d",&n);
	
	int i,a[n];
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	i=0;
	int jump=0;
	while(i<n-3){
		if(a[i+2]==1){
			jump+=1;
			i+=1;
		}
		else{
			i+=2;
			jump+=1;
		}
	}
	
	if (i==n-2){
		jump+=1;
	}
	printf("%d",jump);
}
