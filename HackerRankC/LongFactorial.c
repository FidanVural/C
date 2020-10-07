#include <stdio.h> 
  
int main() 
{ 
    int data,fact[200],i,temp,m,k; 
  
        scanf("%d",&data);//data=100 for 100! 
        m=1; 
        fact[0]=1; 
        for(i=2;i<=data;++i) 
        { 
            temp=0; 
            for(k=0;k<m;++k) 
            { 
                temp+=fact[k]*i; 
                fact[k]=temp%10; 
                temp=temp/10; 
            } 
            while(temp>0) 
            { 
                fact[m]=temp%10;
                m=m+1; 
                temp=temp/10; 
  
            } 
  
        } 
  
        for(k=m-1;k>=0;--k) 
            printf("%d",fact[k]); 
        printf("\n"); 
    return 0; 
} 
