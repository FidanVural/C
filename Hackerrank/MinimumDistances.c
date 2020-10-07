#include <stdio.h>

int main(){
	int n;
	scanf("%d",&n);
	
	int i,j,a[n];
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	int matris[n-1][3],k,l,min=1000;
	
	for(i=0;i<n-1;i++){
		min=1000;
		for(j=i+1;j<n;j++){
			if(abs(a[i]-a[j])<min){
				min=abs(a[i]-a[j]);
				k=i;
				l=j;
			}
		}
		matris[i][0]=min;
		matris[i][1]=k;
		matris[i][2]=l;	
	}
	min=0;
	int fark[100],t=0;
	
	for(i=0;i<n-1;i++){
		if(matris[i][0]<=min){
			min=matris[i][0];
			fark[t]=abs(matris[i][1]-matris[i][2]);
			t++;
		}
	}
	
	min=1000;
	int kontrol=0;
	for(i=0;i<t;i++){
		if(fark[i]<min){
			min=fark[i]; 
			kontrol+=1;
		}
	}
	if(kontrol>0){
		printf("%d",min);
	}
	else{
		printf("-1");
	}
}
