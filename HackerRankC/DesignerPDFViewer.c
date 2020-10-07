// Hackerrank

#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
	
	int *arr=(int*)malloc(sizeof(int)*26);
	
	int i,j;
	
	for(i=0;i<26;i++){
		scanf("%d",&arr[i]);
	}
	
	char *kelime=(char*)malloc(sizeof(int)*10);
	
	scanf("%s",kelime);
	
	int a,max=0,temp;
	a=strlen(kelime);
	
	for(i=0;i<a;i++){
		for(j=0;j<26;j++){
			if(j+97==kelime[i]){
				temp=arr[j];
				if(max<arr[j]){
					max=arr[j];
				}
			}
		}
	}
	printf("%d",max*a);
}
