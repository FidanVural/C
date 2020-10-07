#include <stdio.h>

int main(){
	int son,sayfa;
	scanf("%d %d",&son,&sayfa);
	
	int bas=1;
	
	int son_fark=son-sayfa;
	int bas_fark=sayfa-bas;
	
	if(son_fark>=bas_fark){
		sayfa=sayfa/2;
		printf("%d",sayfa);
	}
	else{
		if(son%2==0){
			if(son_fark%2==0){
				printf("%d",son_fark/2);
			}
			else{
				printf("%d",(son_fark/2)+1);
			}
		}
		else{
			printf("%d",son_fark/2);
		}
	}
}
