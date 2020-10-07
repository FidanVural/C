#include <stdio.h>

int main(){
	long long int p,d,m,s;
	scanf("%lld %lld %lld %lld",&p,&d,&m,&s);
	
	long long int k=p,game=0;
	
	while(s-k>=0){
		s-=k;
		if(k-d<=m){
			k=m;
		}
		else{
			k-=d;
		}
		game++;
	}
	printf("%lld",game);
}
