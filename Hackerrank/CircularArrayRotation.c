#include <stdio.h>

int main(){
    int n,k,q;
    scanf("%d %d %d",&n,&k,&q);
    
    int i;
    int *a=(int*)malloc(sizeof(int)*n);
    
    for(i=0;i<n;i++){
        scanf("%d",&a[(i+k)%n]);
    }
    int m;
    for(i=0;i<q;i++){
        scanf("%d",&m);
        
        printf("%d\n",a[m]);
    }
}
