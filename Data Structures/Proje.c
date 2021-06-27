#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pgm{
	int row;
	int col;
	int arr[700][700];
}PGM;

void readPgm(PGM *pgmformat, char dosya[]){
	char tut[30], tut2[30], sakla[50];
	int a;
	
	FILE* fp = fopen(dosya, "r");
	
	if(fp == NULL){
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fp,"%s", &tut);
	
	fscanf(fp, "%s", sakla);
	if(sakla[0] == '#'){
		fgets(sakla, 50, fp);
		fscanf(fp, "%s", sakla);
	}
	
    sscanf(sakla, "%d", &pgmformat->col);
    
    fscanf(fp, "%d", &pgmformat->row);
    
    fscanf(fp,"%d", &a);
    
    int i,j;
    for(i=0;i<pgmformat->row;i++){
    	for(j=0;j<pgmformat->col;j++){
            if(fscanf(fp, "%d", &pgmformat->arr[i][j]) != 1){
            	exit(1);	
			}
		}
	}	
}

void writeConsol(){
	int a,b;
	FILE* fp = fopen("test_encoded.txt", "r");
	
	printf("\nDosya ici: \n");
	while(1){
		fscanf(fp, "%d %d", &a, &b);
		if(feof(fp)){
			break;
		}
		printf("%d %d ", a, b);
	}
	printf("\n");
	fclose(fp);
}


void writeRle(PGM *pgmformat){
	int i,j,k=0;
	int *dizi = (int*)malloc(sizeof(int)*pgmformat->col*pgmformat->row);
	for(i=0; i<pgmformat->row; i++){
        for(j=0; j<pgmformat->col; j++){
            dizi[k] = pgmformat->arr[i][j];
            k++;
    	}
    }
	
	FILE* fp1 = fopen("test_encoded.txt", "w");
	
	if(fp1 == NULL){
		perror("Error while opening the file.\n");
		exit(1);
	}
    
    fprintf(fp1, "%d %d ", pgmformat->row, pgmformat->col);
    
    int count,hide;
    i=0;
    while(i<pgmformat->col*pgmformat->row){
    	hide = dizi[i];
    	count = 1;
    	while(i < pgmformat->col*pgmformat->row-1 && dizi[i] == dizi[i+1]){
    		count++;
    		i++;
		}
		i++;
		fprintf(fp1 ,"%d %d ", count, hide);
	}
	fclose(fp1);
	
}

void turnPgm(){
	int row, column, i, j;
	int a,b;
	
	FILE* fp = fopen("test_encoded.txt", "r");
	FILE* fp2 = fopen("test_decoded.pgm", "w");
	
	fprintf(fp2, "%s", "P2");
	fprintf(fp2, "\n");
	
	fscanf(fp, "%d %d", &row, &column);
	fprintf(fp2, "%d %d", column, row);
	fprintf(fp2, "\n");
	
	fprintf(fp2, "%d", 255);
	fprintf(fp2, "\n");
	fscanf(fp, "%d %d", &a, &b);
	int tut=0;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(tut == a){
				if(!feof(fp)){
					fscanf(fp, "%d %d", &a, &b);
					tut=0;	
					fprintf(fp2, "%d ", b);
					tut++;	
				}
			}
			else{
				fprintf(fp2, "%d ", b);
				tut++;
			}
		}
		fprintf(fp2, "\n");
	}
	
	printf("\n>>> Goruntu acildi ve test_decoded.pgm dosyasina yazldi.\n");
	
	fclose(fp);
	fclose(fp2);
}

void control(){
	int toplam = 0, tut, row, column;
	int x = 0, a, b, c, d;
	
	FILE* fp = fopen("test_encoded.txt", "r");
	
	fscanf(fp, "%d %d", &row, &column);
	tut = row*column;
	
	while(1){
		fscanf(fp, "%d %d", &a, &b);
		if(feof(fp)){
			break;
		}
		toplam += a;
	}
	
	if(toplam != tut){
		printf("\n>>> Pixellerle ilgili hata. Goruntu acilamadi !\n");
		x = 1;
	}
	fclose(fp);

	
	if(x==0){
		FILE* fp = fopen("test_encoded.txt", "r");
		fscanf(fp, "%d %d", &row, &column);
		
		while(1){
			fscanf(fp, "%d %d", &a, &b);
			if(feof(fp)){
				break;
			}
			
			if(b > 255 || b < 0){
				printf("\n>>> 0-255 disinda bir sayi bulunmaktadir. Goruntu acilamadi !\n");
				x=1;
				break;
			}
		}
		fclose(fp);
	}
	
	if(x==0){
		FILE* fp = fopen("test_encoded.txt", "r");
		fscanf(fp, "%d %d", &row, &column);
		fscanf(fp, "%d %d", &a, &b);
		
		while(1){
			fscanf(fp, "%d %d", &c, &d);
			if(feof(fp)){
				break;
			}
			
			if(b == d){
				printf("\n>>> Arka arkaya ayni renk bulunmaktadir. Goruntu acilamadi !\n");
				x=1;
				break;
			}
			a = c;
			b = d;
		}
		fclose(fp);	
	}
	
	if(x==0){
		turnPgm();
	}
}


void manipulateTheImage_1(int color, int newcolor){
	
	int a, b, count, i=0, j=0, tut=0;
	PGM img;
	int sayac=0, row, column;
	
	if(newcolor <= 255 && newcolor >=0){
		FILE* fp = fopen("test_encoded.txt", "r");
	
		fscanf(fp, "%d %d", &row, &column);
		
		while(!feof(fp)){
			fscanf(fp, "%d", &a);
			sayac++;
		}
		sayac += 1;
	
		rewind(fp);
		
		int *dizi = (int*)malloc(sizeof(int)*sayac);
		
		fscanf(fp, "%d %d", &row, &column);
	
		fscanf(fp, "%d %d", &dizi[0], &dizi[1]);
		
		if(dizi[1] == color){
			dizi[1] = newcolor;
		}	
		
		j=0;
		int sonuc = 2;
		for(i=0;i<sayac-4;i+=2){
			fscanf(fp, "%d %d", &a, &b);
			if(b == color){
				if(newcolor == dizi[j+1]){
					dizi[j+1] = newcolor;
					dizi[j] += a; 
				}
				else{
					j+=2;
					sonuc+=2;
					dizi[j] = a;
					dizi[j+1] = newcolor;
				}	
			}
			else{
				if(b == dizi[j+1]){
					dizi[j] += a; 
				}
				else{
					j+=2;
					sonuc+=2;
					dizi[j] = a;
					dizi[j+1] = b;
				}
			}
		}
		
		fclose(fp);
		
		FILE* fp1 = fopen("test_encoded.txt", "w");
		
		fprintf(fp1, "%d %d ", row, column);
		
		for(i=0;i<sonuc;i++){
			fprintf(fp1, "%d ", dizi[i]);
		}
		
		fclose(fp1);
		
		printf("\n>>> Islem basarili bir sekilde gerceklestirildi.\n");
		writeConsol();
	}
	else{
		printf("\n>>> Degistirmek icin girdiginiz renk 0-255 araliginda olmadigindan degistirilemez.\n");
	}
	
}

void manipulateTheImage_2(int ilk, int son, int deger){
	int a,b,i=0, j=0;
	
	PGM img;
	
	FILE* fp = fopen("test_encoded.txt", "r");
	fscanf(fp, "%d %d", &img.row, &img.col);
	
	if(deger>=0 && deger<=255){
		if((ilk>=0 && ilk<img.row) && (son>=0 && son<img.col)){
			while(1){
				fscanf(fp, "%d %d", &a, &b);
				
				if(feof(fp)){
						break;
				}
				
				while(a>0){
					if(i==ilk && j==son){
						img.arr[i][j] = deger;
						a--;
					}
					else{
						img.arr[i][j] = b;
						a--;
					}
					j++;
					
					if(j>=img.col){
						i++;
						j=0;
					}
				}
			}
			fclose(fp);
			writeRle(&img);
			printf("\n>>> Islem basarili bir sekilde gerceklestirildi.\n");
			writeConsol();	
		}
		else{
			printf("\n>>> Lutfen satir ve sutun degerlerini dogru giriniz. \n");	
		}
	}
	else{
		printf("\n>>> Degistirmek icin girdiginiz renk 0-255 araliginda olmadigindan degistirilemez.\n");
	}
	
}

void histogram(){
	
	int row, col, a, b, i, j;
	FILE* fp = fopen("test_encoded.txt", "r");
	fscanf(fp, "%d %d", &row, &col);
	
	int dizi[256] = {0};
	
	while(1){
		fscanf(fp, "%d %d", &a, &b);
		if(feof(fp)){
			break;
		}
		for(i=0;i<a;i++){
			dizi[b]++;
		}
	}
	
	printf("\n");
	for(i=0;i<256;i++){
		if(dizi[i] != 0){
			printf("%d rengi %d adet\n", i, dizi[i]);
		}
	}
}


int main(){
	char dosya[30], kontrol[30], dosya2[30];
	int  numara, islem;
	int color, newcolor;
	int ilk, son, deger;
	FILE *fp;
	PGM *pgmformat = (PGM*)malloc(sizeof(PGM));
	
	int x=1;
	
	printf("PROGRAMA HOSGELDINIZ !\n\n");
	printf("Lutfen pgm dosya giriniz (file.pgm) : ");
	scanf("%s", dosya);
	
	if(fopen(dosya, "r") == NULL){
		printf("Error while opening the file.\n");
		exit(1);
	}
	else{
		fp = fopen(dosya, "r");
		fscanf(fp,"%s", &kontrol);
		if(strcmp(kontrol, "P2") != 0){
			printf("Girilen bir pgm format degildir.\n");
		}
		else{
			printf("\n>>> Pgm dosya okundu ve sikistirilmis goruntu test_encoded.txt dosyasina yazildi. \n");
			readPgm(pgmformat, dosya);
			writeRle(pgmformat);
			writeConsol("test_encoded.txt");
			
			while(x==1){
				printf("\n1- SIKISTIRILMIS GORUNTUYU ACMA\n");
				printf("2- SIKISTIRILMIS GORUNTU UZERINDE ISLEMLER\n");
				printf("3- CIKIS\n");
				printf("\nLutfen islem yapmak icin bir numara seciniz : ");
				scanf("%d", &numara);
				
				switch(numara){
					case 1:
						control();
						break;
					case 2:
						printf("\nISLEMLER\n");
						printf("1- Verilen bir rengin degerini degistirme\n");
						printf("2- Koordinatlari giris bilgisi olarak verilen bir pikselin degerini degistirme\n");
						printf("3- Resmin histograminin hesaplanmasi\n");
						printf("\nIslemler menusunden bir islem seciniz : ");
						scanf("%d", &islem);
						switch(islem){
							case 1:
								printf("Degistirmek istediginiz rengi giriniz : ");
								scanf("%d", &color);
								printf("Yeni rengi giriniz : ");
								scanf("%d", &newcolor);
								manipulateTheImage_1(color, newcolor);
								break;
							case 2:
								printf("Satiri giriniz : ");
								scanf("%d", &ilk);
								printf("Sutunu giriniz : ");
								scanf("%d", &son);
								printf("Koordinatlarini girdiginiz yerdeki pikselin degerini ne yapmak istersiniz: ");
								scanf("%d", &deger);
								manipulateTheImage_2(ilk, son, deger);
								break;
							case 3:
								histogram();
								break;
							default:
								printf("Yanlis bir islem numarasi girdiniz.\n");
								break;
						}
						break;
					case 3:
						x=0;
						printf("\nProgramdan cikis yaptiniz.\n");
						break;
					default:
						printf("Hatali bir numara girdiniz.\n");
						break;
				}	
			}
		}
		fclose(fp);
	}
	return 0;	
}
