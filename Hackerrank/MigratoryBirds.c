#include <stdio.h>

int main(){
	int n,i;
	scanf("%d",&n);
	
	int *arr = (int*)malloc(sizeof(int) * n);
	int dizi[10]={0};
	
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
		dizi[arr[i]]++;
	}

	int max=dizi[1],sonuc=0;
	
	for(i=1;i<10;i++){
		if(max<dizi[i]){
			max=dizi[i];
			sonuc=i;
		}
	}
	printf("%d",sonuc);
}
