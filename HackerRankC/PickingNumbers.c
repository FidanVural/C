#include <stdio.h>
#include <math.h>

int main(){
	
	int n;
	scanf("%d",&n);
	
	int *a=(int*)malloc(sizeof(int)*n);
	
	int i,j;
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	int temp1;
	
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(a[i]>a[j]){
				temp1=a[i];
				a[i]=a[j];
				a[j]=temp1;
			}
		}
	}
	int temp=0,say=0;
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
			if(abs(a[i]-a[j])==0 || abs(a[i]-a[j])==1){
				temp++;
			}
		}
		if(temp>say){
			say=temp;		
		}
		temp=0;
	}
	printf("%d",say);
}

