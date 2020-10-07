#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 100000

// Cocktail shaker sort algoritmasý kodu
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
	// Burada kodun sýralanmýþ halini yazdýrýyoruz. Ama süreyi etkilememesi için yazdýrmak yerine yorum satýrýna aldým.
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
    
    // n tane farklý boyutta dizi için sonuçlarý alýyorum.
    for(i=0;i<n;i++){
    	printf("Eleman sayisi: "); // Her dizi için farklý büyüklükte eleman sayýsý girelebilir.
    	scanf("%d",&a[i]);
    	
    	for(j=0;j<a[i];j++){
        	c[j]=rand()%1000; // Random deðerleri diziye atadým.
    	}
    	
    	start_t=clock(); 
    	shakersort(c,a[i]);//Diziyi fonksiyona gonderdim.
    	end_t=clock(); 
    	printf("\n");
    	
    	printf("Zaman (saniye): %f\n",(double)(end_t - start_t) / CLOCKS_PER_SEC); // Süreyi saniye cinsinden yazdýrdým.
		// Daha küçük sayýlarla çalýþýyorsak diyagramda görebilmek için 100 ya da 1000 gibi deðerlerle çarpmamýz gerekir.
        b[i]=((double)(end_t - start_t) / CLOCKS_PER_SEC);
    	printf("------------------------------------------------------\n");
    }
    
    
    // Buradan sonraki kodlarý diyagramý çizdirebilmek için yazdým.
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
