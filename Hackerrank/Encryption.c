#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void fonk(char a[],int lenght,int t){
	int i,j;
	for(i=0;i<t;i++){
		for(j=i;j<lenght;j++){
			if(j%t==i){
				printf("%c",a[j]);
			}
		}
		printf(" ");
	}
}

int main(){
	char a[82];
	gets(a);
	
	int lenght=strlen(a);

	int i,lenght2=0;
	for(i=0;i<lenght;i++){
		if(a[i] != ' '){
			lenght2+=1;
		}
	}
	int t=sqrt(lenght2);
	float t2=sqrt(lenght2);
	int j;
	if(t==t2){
		fonk(a,lenght,t);
	}
	else{
		fonk(a,lenght,t+1);
	}
}
