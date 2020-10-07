#include <stdio.h>

int main(){
	
	int p,q;
	scanf("%d",&p);
	scanf("%d",&q);
	
	long long int i,j,l,a,b,k,t,bas=0,toplam1=0,toplam2=0,say=0;
	for(i=p;i<=q;i++){
		k=i*i;
		bas=0;
		while(k!=0){
			k=k/10;
			bas++;
		}
		k=i*i;
		t=1;
		if(bas%2==0){
			for(j=0;j<bas/2;j++){
				a=k%10;
				k=k/10;
				a=a*t;
				toplam1+=a;
				t*=10;
			}
			t=1;
			for(l=0;l<bas/2;l++){
				b=k%10;
				k=k/10;
				b=b*t;
				toplam2+=b;
				t*=10;	
			}
		}
		else{
			for(j=0;j<bas/2+1;j++){
				a=k%10;
				k=k/10;
				a=a*t;
				toplam1+=a;
				t*=10;
			}
			t=1;
			for(l=0;l<bas/2;l++){
				b=k%10;
				k=k/10;
				b=b*t;
				toplam2+=b;
				t*=10;	
			}
		}
		if((toplam1+toplam2)==i){
			printf("%lld ",i);
			say++;
		}
		toplam1=0;
		toplam2=0;
	}
	if(say==0){
		printf("INVALID RANGE");
	}
}
