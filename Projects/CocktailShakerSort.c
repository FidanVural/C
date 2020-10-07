#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 100000

// Cocktail shaker sort algoritmas� kodu
int shakersort(int arr[],int n){
    int ilk=0,son,degisim=1,gecici,gecici2;
    int i,a,temp,f;
    while(degisim==1){
        degisim=0;
        for(i=ilk;i<n-1;i++){
            if(arr[i]>arr[i+1]){
                temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
                gecici=i;
                degisim=1;
            }
        }
        son=gecici;
        for(i=son;i>ilk;i--){
            if(arr[i-1]>arr[i]){
                temp=arr[i];
                arr[i]=arr[i-1];
                arr[i-1]=temp;
                gecici2=i;
                degisim=1;
            }
        }
        ilk=gecici2;
    }
	// Burada kodun s�ralanm�� halini yazd�r�yoruz. Ama s�reyi etkilememesi i�in yazd�rmak yerine yorum sat�r�na ald�m.
    //for(f=0;f<n;f++){
    //	printf("%d ",arr[f]);
	//}
}


int main(){
    clock_t start_t,end_t;
    int n,k,i,j,x=0,a[SIZE],b[SIZE],max,max1,c[SIZE];
    srand(time(NULL));
    printf("Kac dizi girmek istersiniz:");
    scanf("%d",&n);
    printf("\n");
    
    // n tane farkl� boyutta dizi i�in sonu�lar� al�yorum.
    for(i=0;i<n;i++){
    	printf("Eleman sayisi: "); // Her dizi i�in farkl� b�y�kl�kte eleman say�s� girelebilir.
    	scanf("%d",&a[i]);
    	
    	for(j=0;j<a[i];j++){
        	c[j]=rand()%1000; // Random de�erleri diziye atad�m.
    	}
    	
    	start_t=clock(); 
    	shakersort(c,a[i]);//Diziyi fonksiyona gonderdim.
    	end_t=clock(); 
    	printf("\n");
    	
    	printf("Zaman (saniye): %f\n",(double)(end_t - start_t) / CLOCKS_PER_SEC); // S�reyi saniye cinsinden yazd�rd�m.
		// Daha k���k say�larla �al���yorsak diyagramda g�rebilmek i�in 100 ya da 1000 gibi de�erlerle �arpmam�z gerekir.
        b[i]=((double)(end_t - start_t) / CLOCKS_PER_SEC);
    	printf("------------------------------------------------------\n");
    }
    
    
    // Buradan sonraki kodlar� diyagram� �izdirebilmek i�in yazd�m.
    max=0;
    for(i=0;i<n;i++){
    	if(b[i]>max){
    		max=b[i];
		}
	}
	
	printf("\n\n");
	max1=max;
	for(i=0;i<max;i++){
		for(j=0;j<n;j++){
			if(b[j]>=max1){
				printf("*");
			}
			else{
				printf(" ");
			}
			printf("\t");
		}
		printf("\n");
		max1--;
	}
	for(i=0;i<n;i++){
		printf("%d 	",a[i]);
	}
}
