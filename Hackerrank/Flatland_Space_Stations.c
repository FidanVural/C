#include <stdio.h>

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	
	int arr[m],i,j;
	for(i=0;i<m;i++){
		scanf("%d",&arr[i]);
		
	}
	int max=0;
	if(n==m){
		printf("0");
	}
	else{
		int temp;
		for(i=0;i<n;i++){
			temp=abs(i-arr[0]);
			for(j=0;j<m;j++){
				if(abs(i-arr[j])<temp){
					temp=abs(i-arr[j]);
				}
			}
			if(temp>max){
				max=temp;
			}
		}
		printf("%d",max);
	}
}
