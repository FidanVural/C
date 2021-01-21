#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

struct ogrenciler{
	int ID;
	char ad[20];
	char soyad[20];
	int toplam_ders;
	int toplam_kredi;
};

struct ogretim_uyesi{
	int ID;
	char ad[20];
	char soyad[20];
	char unvan[20];
};

struct dersler{
	int ID;
	char ders_adi[20];
	int toplam_kredi;
	int kontenjan;
	int hoca_id;
};

struct ogrenci_ders_kayit{
	int ID;
	int ogr_no;
	int ders_kod;
	char tarih[10];
	int kayit_durum;
};

void txtOlusturucu();
void ogrenci_ekle();
void ogrenci_sil();
void ogrenci_ders_kayit_guncelle(int);
void ogretim_uyesi_ekle();
void ogretim_uyesi_sil();
void ogretim_uyesi_guncelle(int);
void ogrenci_ders_kredi_guncelleme(int,int,int);
void dersler_ekle();
void dersler_sil();
void dersler_guncelle(int,int);
void ders_listeleme();
void ogrenci_ders_ekleme(int,int);
void kayitli_ogrenciler();
void dersleri_listele();
void ogrenci_ders_kayit_durumu();
void derskodu_siniflistesi();


int main(){
	int n,fb=0;
	int max_d, max_k;
	setlocale(LC_ALL, "Turkish");
	
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN);
	
	printf("\t\t\t\tHOSGELDINIZ. KAYIT SISTEMINE GIRIS YAPTINIZ!\t\t\t\t\t\n");
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("-> MENU\n\n");
	printf("1) ��renciler dosyas�na ��renci eklemek i�in 1'e bas�n�z.\n");
	printf("2) ��renciler dosyas�ndan ��renci silmek i�in 2'ye bas�n�z.\n");
	printf("3) ��retim �yesi dosyas�na ��retim �yesi eklemek i�in 3'e bas�n�z.\n");
	printf("4) ��retim �yesi dosyas�ndan ��retim �yesi silmek i�in 4'e bas�n�z.\n");
	printf("5) Dersler dosyas�na ders eklemek i�in 5'e bas�n�z.\n");
	printf("6) Dersler dosyas�ndan ders silmek i�in 6'ya bas�n�z.\n");
	printf("7) ID'si girilen ��retim g�revlisinin derslerini listelemek i�in 7'ye bas�n�z.\n");
	printf("8) ��renciye ders eklemek i�in 8'e bas�n�z.\n");
	printf("9) ��renciden ders silinmesi i�in 9'a bas�n�z.\n");
	printf("10) Ders kodu verilen bir derse kay�tl� ��rencileri listelemek i�in 10'a bas�n�z.\n");
	printf("11) ��renci numaras� verilen bir ��rencinin ald��� t�m dersleri listelemek i�in 11'e bas�n�z.\n");
	printf("12) Bir ��retim �yesinin verdi�i bir derse ait s�n�f listesini g�r�nt�lemek i�in 12'ye bas�n�z.\n");
	printf("13) ��k�� yapmak i�in 13'e bas�n�z.\n\n");
	
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	txtOlusturucu();
	
	printf("Ilerideki i�lemlerde kullan�lmas� a��s�ndan l�tfen max ders ve max kredi de�eri giriniz.\n");
	printf("L�tfen al�nabilecek max ders say�s�n� giriniz: ");
	scanf("%d",&max_d);
	
	printf("L�tfen al�nabilecek max kredi say�s�n� giriniz: ");
	scanf("%d",&max_k);
	
	while(fb==0){
		
		printf("\nL�tfen i�lem yapmak i�in bir de�er giriniz: ");
		scanf("%d",&n);
		
		switch(n){
			case 1:
				ogrenci_ekle();
				break;
			case 2:
				ogrenci_sil();
				break;
			case 3:
				ogretim_uyesi_ekle();
				break;
			case 4:
				ogretim_uyesi_sil();
				break;
			case 5:
				dersler_ekle();
				break;
			case 6:
				dersler_sil();
				break;
			case 7:
				ders_listeleme();
				break;
			case 8:
				ogrenci_ders_ekleme(max_d,max_k);
				break;
			case 9:
				ogrenci_ders_kayit_durumu();
				break;
			case 10:
				kayitli_ogrenciler();
				break;
			case 11:
				dersleri_listele();
				break;
			case 12:
				derskodu_siniflistesi();
				break;
			case 13:
				fb=1;
				printf("Sistemden ��k�� yapt�n�z.\n");
				break;
			default:
				printf("Yanl�� bir i�lem ger�ekle�tirdiniz !\n");
		}
	}
	
	return 0;
}

void txtOlusturucu(){
    FILE *fp;
    
    if((fp = fopen("ogretim_uyesi.txt","a+")) == NULL)
        printf("ogretim_uyesi.txt olusturulamadi!");
    fclose(fp);
    
    if((fp = fopen("ogrenciler.txt","a+")) == NULL)
        printf("ogrenciler.txt olusturulamadi!");
    fclose(fp);
    
    if((fp = fopen("dersler.txt","a+")) == NULL)
        printf("dersler.txt olusturulamadi!");
    fclose(fp);
    
    if((fp = fopen("OgrenciDersKayit.txt","a+")) == NULL)
        printf("HATA OgrenciDersKayit.txt olusturulamadi!");
    fclose(fp);
}

void ogrenci_ekle(){
	struct ogrenciler ekle,kontrol;
	int tut=0;
	
	FILE *dosya_ogrenci;
	dosya_ogrenci = fopen("ogrenciler.txt","a+");
	
	if (dosya_ogrenci == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n\n");
	}
	
	printf("\t\t OGRENCI EKLEME \t\t\n");
	
	printf("O�renci ID : ");
	scanf("%d",&ekle.ID);
	printf("O�renci ismi : ");
	scanf("%s",&ekle.ad);
	printf("O�renci soyismi : ");
	scanf("%s",&ekle.soyad);
	printf("O�renci toplam ders say�s� : ");
	scanf("%d",&ekle.toplam_ders);
	printf("O�renci toplam kredi say�s� : ");
	scanf("%d",&ekle.toplam_kredi);
	
	while(!feof(dosya_ogrenci)){
		fscanf(dosya_ogrenci, "%d %s %s %d %d", &kontrol.ID, kontrol.ad, kontrol.soyad, &kontrol.toplam_ders, &kontrol.toplam_kredi);
		if(ekle.ID == kontrol.ID){
			printf("\nBu ID'de bir ��renci bulunmaktad�r. ID'ler �zel olmald�r!\nL�tfen farkl� bir ID giriniz !\n");
			tut=1;
		}
	} 
	
	if(tut == 0){
		fseek(dosya_ogrenci,0,SEEK_END);
		fprintf(dosya_ogrenci, "%d %s %s %d %d\n", ekle.ID, ekle.ad, ekle.soyad, ekle.toplam_ders, ekle.toplam_kredi);
		printf("��renci kayit edildi !\n");	
	}
	
	fclose(dosya_ogrenci);
}

void ogrenci_sil(){
	int id, tut=0;
	int temp1=0;
	struct ogrenciler sil;
	
	FILE *dosya_ogrenci =  fopen("ogrenciler.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	if (dosya_ogrenci == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	} 
	
	printf("\t\t OGRENCI SILME \t\t\n");
	
	printf("\nLutfen silmek istediginiz ogrencinin ID'sini giriniz: ");
	scanf("%d",&id);
	
	fseek(dosya_ogrenci,0,SEEK_SET);
	
	while(!feof(dosya_ogrenci)){
		
		fscanf(dosya_ogrenci, "%d %s %s %d %d",&sil.ID, sil.ad, sil.soyad, &sil.toplam_ders, &sil.toplam_kredi);
		
		if(temp1 != sil.ID){
		
			if(id != sil.ID){
				fprintf(kopyala, "%d %s %s %d %d\n", sil.ID, sil.ad, sil.soyad, sil.toplam_ders, sil.toplam_kredi);
			}
			else{
				tut=1;
			}
		temp1 = sil.ID;
		}
	}
	
	fclose(dosya_ogrenci);
	fclose(kopyala);
		
	if(tut==0){
		printf("%d ID'ye sahip bir ��renci bulunmamaktad�r.\n",id);
		remove("kopya.txt");
	}
	else{
		remove("ogrenciler.txt");
		rename("kopya.txt","ogrenciler.txt");
		printf("��renci silindi !\n");
		ogrenci_ders_kayit_guncelle(id);
	}
}

void ogrenci_ders_kayit_guncelle(int id){
	int tut=0;
	int temp1;
	struct ogrenci_ders_kayit kontrol;
	
	FILE *dosya_ders_ogrenci =  fopen("OgrenciDersKayit.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	if (dosya_ders_ogrenci == NULL){
		printf("ogrenciler.txt dosyas� bulunamad�. Orada de�i�iklikler d�zenlenemedi !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	}
	
	fseek(dosya_ders_ogrenci,0,SEEK_SET);
	
	while(!feof(dosya_ders_ogrenci)){
		
		fscanf(dosya_ders_ogrenci, "%d %d %d %s %d", &kontrol.ID, &kontrol.ogr_no, &kontrol.ders_kod, kontrol.tarih, &kontrol.kayit_durum);
		
		if(temp1 != kontrol.ogr_no){
			if(id != kontrol.ogr_no){
				fprintf(kopyala, "\n%d %d %d %s %d", kontrol.ID, kontrol.ogr_no, kontrol.ders_kod, kontrol.tarih, kontrol.kayit_durum);
			}
			else{
				tut=1;
			}
		temp1 = kontrol.ogr_no;
		}
	}
	
	fclose(dosya_ders_ogrenci);
	fclose(kopyala);
		
	if(tut==0){
		printf("%d ID'ye sahip ��rencinin hen�z ald��� bir ders bulunmamaktad�r.\n",id);
		remove("kopya.txt");
	}
	else{
		remove("OgrenciDersKayit.txt");
		rename("kopya.txt","OgrenciDersKayit.txt");
		printf("��rencinin ald��� dersler silindi !\n");
	}
}


void ogretim_uyesi_ekle(){
	struct ogretim_uyesi ekle,kontrol;
	int tut=0;
	
	FILE *dosya_ogretim_uyesi;
	dosya_ogretim_uyesi = fopen("ogretim_uyesi.txt","a+");
	
	if (dosya_ogretim_uyesi == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	}
	
	printf("\n\t\t OGRETIM UYESI EKLEME \t\t\n");
	
	printf("O�retim �yesi ID : ");
	scanf("%d",&ekle.ID);
	printf("O�retim �yesi ismi : ");
	scanf("%s",&ekle.ad);
	printf("O�retim �yesi soyismi : ");
	scanf("%s",&ekle.soyad);
	printf("Ogretim �yesinin unvan�n� giriniz: ");
	scanf("%s",&ekle.unvan);
	
	while(!feof(dosya_ogretim_uyesi)){
		fscanf(dosya_ogretim_uyesi, "%d %s %s %s", &kontrol.ID, kontrol.ad, kontrol.soyad, kontrol.unvan);
		if(ekle.ID == kontrol.ID){
			printf("\nBu ID'de bir ��retim �yesi bulunmaktad�r. ID'ler �zel olmald�r!\nL�tfen farkl� bir ID giriniz !\n");
			tut=1;
		}
	}
	
	if(tut == 0){
		fseek(dosya_ogretim_uyesi,0,SEEK_END);
		fprintf(dosya_ogretim_uyesi, "%d %s %s %s\n", ekle.ID, ekle.ad, ekle.soyad, ekle.unvan);
		printf("��retim �yesi kay�t edildi !\n");	
	}
	
	fclose(dosya_ogretim_uyesi);
	
}

void ogretim_uyesi_sil(){
	int id, tut=0;
	int temp1;
	struct ogretim_uyesi sil;
	
	FILE *dosya_ogretim_uyesi =  fopen("ogretim_uyesi.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	if (dosya_ogretim_uyesi == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	} 
	
	printf("\n\t\t OGRETIM UYESI SIL \t\t\n");
	
	printf("\nL�tfen silmek istedi�iniz ��retim �yesinin ID'sini giriniz: ");
	scanf("%d",&id); 
	
	fseek(dosya_ogretim_uyesi,0,SEEK_SET);
	
	while(!feof(dosya_ogretim_uyesi)){
		
		fscanf(dosya_ogretim_uyesi, "%d %s %s %s",&sil.ID, sil.ad, sil.soyad, sil.unvan);
		
		if(temp1 != sil.ID){
			if(id != sil.ID){
				fprintf(kopyala, "%d %s %s %s\n", sil.ID, sil.ad, sil.soyad, sil.unvan);
			}
			else{
				tut=1;
			}
		temp1 = sil.ID;
		}
	}
	
	fclose(dosya_ogretim_uyesi);
	fclose(kopyala);
		
	if(tut==0){
		printf("%d ID'ye sahip bir ��retim �yesi bulunmamaktad�r.\n",id);
		remove("kopya.txt");
	}
	else{
		remove("ogretim_uyesi.txt");
		rename("kopya.txt","ogretim_uyesi.txt");
		printf("��retim �yesi silindi !\n");
		ogretim_uyesi_guncelle(id);
	}
}

void ogretim_uyesi_guncelle(int id){
	int tut=0, *sakla = (int*)malloc(sizeof(int)*50);
	int i=0,temp1,n=0;
	int a,ders,kontrol_kd,sakla2;
	int *kredi = (int*)malloc(sizeof(int)*50);
	struct dersler kontrol;
	struct ogrenci_ders_kayit kontrol2;
	struct ogrenciler yaz;
	
	FILE *dosya_dersler = fopen("dersler.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	if (dosya_dersler == NULL){
		printf("Dersler dosyas� mevcut de�ildir. O nedenle de�i�iklikler yap�lamam��t�r. !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	}
	
	fseek(dosya_dersler,0,SEEK_SET);
	while(!feof(dosya_dersler)){
		
		fscanf(dosya_dersler, "%d %s %d %d %d", &kontrol.ID, kontrol.ders_adi, &kontrol.toplam_kredi, &kontrol.kontenjan, &kontrol.hoca_id);
	
		if(id == kontrol.hoca_id){
			sakla[i] = kontrol.ID;
			kredi[i] = kontrol.toplam_kredi;
			ders=-1;
			i++;
			n++;
			tut=1;
		}
	}
	
	fseek(dosya_dersler,0,SEEK_SET);
	while(!feof(dosya_dersler)){
		
		fscanf(dosya_dersler, "%d %s %d %d %d", &kontrol.ID, kontrol.ders_adi, &kontrol.toplam_kredi, &kontrol.kontenjan, &kontrol.hoca_id);
		
		if(temp1 != kontrol.hoca_id){
			if(id != kontrol.hoca_id){
				fprintf(kopyala, "%d %s %d %d %d\n", kontrol.ID, kontrol.ders_adi, kontrol.toplam_kredi, kontrol.kontenjan, kontrol.hoca_id);
			}
			else{
				tut=1;
			}
		temp1 = kontrol.ID;
		}
	}

	fclose(dosya_dersler);
	fclose(kopyala);
		
	if(tut==0){
		printf("%d ID'ye sahip bir ��retim �yesinin verdi�i bir ders bulunmamaktad�r.\n",id);
		remove("kopya.txt");
	}
	else{
		remove("dersler.txt");
		rename("kopya.txt","dersler.txt");
		printf("��retim �yesinin verdi�i dersler, dersler dosyas�ndan silindi !\n");
	}
	
	i=0;
	while(i<n){
		
		FILE *dosya_ders_ogrenci =  fopen("OgrenciDersKayit.txt","r");
		FILE *kopya = fopen("kopyala.txt","w");
		
		fseek(dosya_ders_ogrenci,0,SEEK_SET);
		
		while(!feof(dosya_ders_ogrenci)){
		
			fscanf(dosya_ders_ogrenci, "%d %d %d %s %d", &kontrol2.ID, &kontrol2.ogr_no, &kontrol2.ders_kod, kontrol2.tarih, &kontrol2.kayit_durum);
			if(temp1 != kontrol2.ders_kod){
			if(sakla[i] != kontrol2.ders_kod){
				fprintf(kopya, "%d %d %d %s %d\n", kontrol2.ID, kontrol2.ogr_no, kontrol2.ders_kod, kontrol2.tarih, kontrol2.kayit_durum);
			} 
			else{
				kontrol_kd = kontrol2.kayit_durum;
				tut=1;
				kredi[i] = kredi[i]*(-1);
				sakla2=kontrol2.ogr_no;
				if( kontrol_kd == 1){
					ogrenci_ders_kredi_guncelleme(ders, kredi[i], sakla2);
				}
			}
			temp1 = kontrol2.ders_kod;
		}
	}
		
		fclose(dosya_ders_ogrenci);
		fclose(kopya);
		
		if(tut==0){
			printf("%d ID'ye sahip bir ��retim �yesi bulunmamaktad�r.\n",id);
			remove("kopyala.txt");
		}
		else{
			remove("OgrenciDersKayit.txt");
			rename("kopyala.txt","OgrenciDersKayit.txt");
			printf("Ger�ekle�ti !\n");
		}
		i++;
	}
}

void ogrenci_ders_kredi_guncelleme(int ders, int kredi, int ogr_no){
	int temp1;
	struct ogrenciler ders_kredi;
	
	FILE *dosya_ogrenciler = fopen("ogrenciler.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	fseek(dosya_ogrenciler,0,SEEK_SET);
		
	while(!feof(dosya_ogrenciler)){
		
		fscanf(dosya_ogrenciler, "%d %s %s %d %d",&ders_kredi.ID, ders_kredi.ad, ders_kredi.soyad, &ders_kredi.toplam_ders, &ders_kredi.toplam_kredi);
		
		if(temp1 != ders_kredi.ID){
		
			if(ogr_no != ders_kredi.ID){
				fprintf(kopyala, "%d %s %s %d %d\n", ders_kredi.ID, ders_kredi.ad, ders_kredi.soyad, ders_kredi.toplam_ders, ders_kredi.toplam_kredi);
			}
			else{
				ders_kredi.toplam_ders += ders;
				ders_kredi.toplam_kredi += kredi;
				fprintf(kopyala, "%d %s %s %d %d\n", ders_kredi.ID, ders_kredi.ad, ders_kredi.soyad, ders_kredi.toplam_ders, ders_kredi.toplam_kredi);
			}
		temp1 = ders_kredi.ID;
		}
	}
	
	fclose(dosya_ogrenciler);
	fclose(kopyala);
	
	remove("ogrenciler.txt");
	rename("kopya.txt","ogrenciler.txt");
	printf("��renciler dosyas�ndan ders kredi bilgileri de g�ncellendi !\n");

}

void dersler_ekle(){
	struct dersler ekle,kontrol;
	struct ogretim_uyesi hoca;
	int tut=0,tut0=0;
	
	FILE *dosya_dersler;
	dosya_dersler = fopen("dersler.txt","a+");
	FILE *ogretim_uye = fopen("ogretim_uyesi.txt","r");
	
	if (dosya_dersler == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	}
	
	printf("\n\t\t DERS EKLEME \t\t\n");
	
	printf("Ders ID : ");
	scanf("%d",&ekle.ID);
	printf("Ders ismi : ");
	scanf("%s",&ekle.ders_adi);
	printf("Ders kredisi : ");
	scanf("%d",&ekle.toplam_kredi);
	printf("Ders kontenjan say�s�: ");
	scanf("%d",&ekle.kontenjan);
	printf("Hoca ID: ");
	scanf("%d",&ekle.hoca_id);
		
	while(!feof(ogretim_uye)){
		
		fscanf(ogretim_uye, "\n%d %s %s %s", &hoca.ID, hoca.ad, hoca.soyad, hoca.unvan);
	
		if(ekle.hoca_id == hoca.ID){
			tut0=1;
		}
	}
	
	if(tut0==0){
		printf("\nBu ID'de bir ��retim �yesi bulunmamaktad�r. Dolay�s�yla bu ders eklenemedi.\n");
	}
 	
 	
 	fseek(dosya_dersler,0,SEEK_SET);
	while(!feof(dosya_dersler) && tut0==1){
		
		fscanf(dosya_dersler, "\n%d %s %d %d %d", &kontrol.ID, kontrol.ders_adi, &kontrol.toplam_kredi, &kontrol.kontenjan, &kontrol.hoca_id);
	
		if(ekle.ID == kontrol.ID){
			printf("\nBu ID'de bir ders bulunmaktad�r. ID'ler �zel olmal�d�r!\nL�tfen farkl� bir ID giriniz !\n");
			tut=1;
		}
	}
	
	if(tut == 0 && tut0 == 1){
		fseek(dosya_dersler,0,SEEK_END);
		fprintf(dosya_dersler, "\n%d %s %d %d %d", ekle.ID, ekle.ders_adi, ekle.toplam_kredi, ekle.kontenjan, ekle.hoca_id);
		printf("Ders eklendi !\n");	
	}
	
	fclose(dosya_dersler);
}

void dersler_sil(){
	int id, tut=0, sakla;
	int temp1;
	struct dersler sil;
	
	FILE *dosya_dersler =  fopen("dersler.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	if (dosya_dersler == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	}
	
	printf("\n\t\t DERS SIL \t\t\n");
		
	printf("\nL�tfen silmek istedi�iniz dersin ID'sini giriniz: ");
	scanf("%d",&id); 
	
	fseek(dosya_dersler,0,SEEK_SET);
	
	while(!feof(dosya_dersler)){
		
		fscanf(dosya_dersler, "\n%d %s %d %d %d", &sil.ID, sil.ders_adi, &sil.toplam_kredi, &sil.kontenjan, &sil.hoca_id);
		
		if(temp1 != sil.ID){
			if(id != sil.ID){
				fprintf(kopyala, "%d %s %d %d %d\n", sil.ID, sil.ders_adi, sil.toplam_kredi, sil.kontenjan, sil.hoca_id);
			}
			else{
				tut=1;
				sakla = sil.toplam_kredi;
			}
		temp1 = sil.ID;
		}
	}
	
	fclose(dosya_dersler);
	fclose(kopyala);
		
	if(tut==0){
		printf("%d ID'ye sahip bir ders bulunmamaktad�r.",id);
		remove("kopya.txt");
	}
	else{
		remove("dersler.txt");
		rename("kopya.txt","dersler.txt");
		printf("Ders silindi !\n");
		dersler_guncelle(id,sakla);
	}
}

void dersler_guncelle(int id, int sakla){
	int tut=0,i=0,temp1,tut2=0;
	struct ogrenci_ders_kayit sil;
	int ders;
	FILE *dosya_ders_ogrenci =  fopen("OgrenciDersKayit.txt","r");
	
	fseek(dosya_ders_ogrenci,0,SEEK_SET);
		
	while(!feof(dosya_ders_ogrenci)){
		
		fscanf(dosya_ders_ogrenci, "%d %d %d %s %d", &sil.ID, &sil.ogr_no, &sil.ders_kod, sil.tarih, &sil.kayit_durum);
		
		if(id == sil.ders_kod){
			tut=1;
		}
	}
	
	fclose(dosya_ders_ogrenci);
	
	
	if(tut==0){
		printf("��renci ders kay�t dosyas�nda herhangi bir ��renci bu dersi almamaktad�r.\nDolay�s�yla bu dosyada silinecek bir �ey yoktur.\n");
	}
	else{
		
		FILE *dosya_ders_ogrenci =  fopen("OgrenciDersKayit.txt","r");
		FILE *kopya = fopen("kopyala.txt","w");

		while(!feof(dosya_ders_ogrenci)){
			
			fscanf(dosya_ders_ogrenci, "%d %d %d %s %d", &sil.ID, &sil.ogr_no, &sil.ders_kod, sil.tarih, &sil.kayit_durum);
			
			if(temp1 != sil.ders_kod){
				if(id != sil.ders_kod){
					fprintf(kopya, "\n%d %d %d %s %d", sil.ID, sil.ogr_no, sil.ders_kod, sil.tarih, sil.kayit_durum);
				}
				else{
					tut2=1;
					ders=-1;
					sakla=sakla*(-1);
					if(sil.kayit_durum ==1){
						ogrenci_ders_kredi_guncelleme(ders,sakla,sil.ogr_no);
					}
				}
				temp1 = sil.ders_kod;
			}
	    }
	
		fclose(dosya_ders_ogrenci);
		fclose(kopya);
		
		if(tut2==0){
			printf("I'm here :(\n");
			remove("kopyala.txt");
		}
		else{
			remove("OgrenciDersKayit.txt");
			rename("kopyala.txt","OgrenciDersKayit.txt");
			printf("��renci kay�t dosyas�nda bulunan bu derse ait �eyler de ba�ar�yla silindi !\n");
		}	
	}
}

void ders_listeleme(){
	int id,i=1;
	struct dersler sil;
	
	printf("\n��retim �yesinin verdi�i dersleri g�rmek i�in ID'sini giriniz: ");
	scanf("%d",&id);
	
	FILE *dosya_dersler;
	dosya_dersler = fopen("dersler.txt","a+");

	printf("\n%d ID'li ��retim �yesinin verdi�i dersler\n",id);
	
	fseek(dosya_dersler,0,SEEK_SET);
	while(!feof(dosya_dersler)){
		fscanf(dosya_dersler, "%d %s %d %d %d", &sil.ID, sil.ders_adi, &sil.toplam_kredi, &sil.kontenjan, &sil.hoca_id);
		
		if(id == sil.hoca_id){
			printf("%d) %s\n",i,sil.ders_adi);
			i++;
		}
	}
	
	fclose(dosya_dersler);
} 

void ogrenci_ders_ekleme(int max_d, int max_k){
	int og_ID,cik=0,tut=0,cik2=0,bos=0;
	int i=0,ders_no,ogrenci_no,tut2=0;
	int size, artir=0; // ders say�s�n� tutar. 
	int ders_ID, ders1, kredi,kod,degisken=0;
	struct ogrenciler bul;
	struct dersler bul2;
	struct ogrenci_ders_kayit kayit;
	
	time_t timer; 
    struct tm* tm_info; 
    char day[3],month[3],year[5],str[10];
 
    time(&timer); 
    tm_info = localtime(&timer); 
	
	FILE *ogrenci = fopen("ogrenciler.txt","r");
	FILE *dersler = fopen("dersler.txt","r");
	
	FILE *ders = fopen("OgrenciDersKayit.txt","a+");	
	
	if (NULL != ders) {
    	fseek (ders, 0, SEEK_END);
    	size = ftell(ders);

    	if (0 == size) {
        	bos=1;
        	printf("Bu dosya bo�tur. \n");
		}
	}
	
	fseek(ders, 0,SEEK_SET);
	while(!feof(ders) && bos==0){
		fscanf(ders, "%d %d %d %s %d", &kayit.ID, &kayit.ogr_no, &kayit.ders_kod, kayit.tarih, &kayit.kayit_durum);
		i = kayit.ID;
	}


	printf("\n��renci ders ekleme i�in ��renci ID giriniz: ");
	scanf("%d",&og_ID);
	
	while(!feof(ogrenci)){
		
		fscanf(ogrenci, "%d %s %s %d %d", &bul.ID, bul.ad, bul.soyad, &bul.toplam_ders, &bul.toplam_kredi);
		
		if(og_ID == bul.ID){
			cik=1;
			
			if(bul.toplam_ders >= max_d || bul.toplam_kredi >= max_k){
				tut2=1;
				printf("Max kredi ve max ders de�erlerine ula��lm��t�r.\n Bu nedenle ders alamazs�n�z.\n");
			}
			
			break;
		}	
	}	
	
	if(cik==0){
			printf("B�yle ID'ye sahip bir ��renci bulunmamaktad�r !\n");
			tut=1;
	}
	
	fseek(ders,0,SEEK_SET); 
	
	while(!feof(ders) && tut==0 && tut2==0){
		
		fscanf(ders, "%d %d %d %s %d",&kayit.ID, &kayit.ogr_no, &kayit.ders_kod, kayit.tarih, &kayit.kayit_durum);
		
		if(og_ID == kayit.ogr_no && kayit.kayit_durum == 1){
			max_d--;
			
			while(!feof(dersler)){
				fscanf(dersler, "%d %s %d %d %d",&bul2.ID, bul2.ders_adi, &bul2.toplam_kredi, &bul2.kontenjan, &bul2.hoca_id);
				
				if(kayit.ders_kod == bul2.ID){
					max_k -= bul2.toplam_kredi; 
				}
			}
		}
	}
	
	
	while(tut==0 && tut2==0){
		
		printf("L�tfen eklemek istedi�iniz dersin ID'sini giriniz ya da ��kmak i�in -1 giriniz: ");
		scanf("%d",&ders_ID);
			
			fseek(dersler,0,SEEK_SET);
			while(!feof(dersler)){
		
				fscanf(dersler, "%d %s %d %d %d",&bul2.ID, bul2.ders_adi, &bul2.toplam_kredi, &bul2.kontenjan, &bul2.hoca_id);
				
				if(ders_ID == bul2.ID){
					cik2=1;
				}	
			}
		
			if(cik2==0){
				printf("B�yle bir ders kodu bulunmamaktad�r !\n");
				break;
			}
			else{
				tut=1;
				fseek(dersler,0,SEEK_SET);
				while(!feof(dersler)){ 
					fscanf(dersler, "%d %s %d %d %d",&bul2.ID, bul2.ders_adi, &bul2.toplam_kredi, &bul2.kontenjan, &bul2.hoca_id);
					if(kod != bul2.ID){
					if(ders_ID == bul2.ID){
						
						if(max_d > 0  && max_k >= bul2.toplam_kredi){
							
							max_k -= bul2.toplam_kredi;
							max_d -= 1;
							
							strftime(day, 3, "%d", tm_info); 
        					strftime(month, 3, "%m", tm_info); 
        					strftime(year, 5, "%Y", tm_info); 
 		
 							strcpy(str, day);
 							strcat(str,"/");
 							strcat(str, month);
 							strcat(str,"/");
 							strcat(str, year);
 		
							i++;
							kayit.ID = i;
							kayit.ogr_no = og_ID;
							kayit.ders_kod = ders_ID;
							strcpy(kayit.tarih, str);
							kayit.kayit_durum = 1;
							printf("\n\n");
							
							
							fseek(ders,0,SEEK_END);
							fprintf(ders, "%d %d %d %s %d\n", kayit.ID, kayit.ogr_no, kayit.ders_kod, kayit.tarih, kayit.kayit_durum);
						
							ders_no = kayit.ders_kod;
							ogrenci_no = kayit.ogr_no;
						}
						else{
							printf("Ders alma ya da krediniz dolmu�tur.\n");
							degisken=1;
							break;
						}
						
					}
					}
					kod = bul2.ID;
				}
			}
	}
	
	fclose(ders);
	fclose(ogrenci);
	fclose(dersler);
	
	FILE *derss = fopen("dersler.txt","r");
	
	if(tut == 1 && degisken==0){
		fseek(derss, 0,SEEK_SET);
		
		while(!feof(derss)){
			fscanf(derss, "%d %s %d %d %d", &bul2.ID, bul2.ders_adi, &bul2.toplam_kredi, &bul2.kontenjan, &bul2.hoca_id);
			
			if(ders_no == bul2.ID){
				kredi = bul2.toplam_kredi;
			}
		}
		ders1 = 1;
		ogrenci_ders_kredi_guncelleme(ders1,kredi,ogrenci_no);
	}
	fclose(derss);
}

void ogrenci_ders_kayit_durumu(){ 
	
	struct ogrenci_ders_kayit sil;
	struct dersler ders;
	struct ogrenciler ogr;
	int temp1,id,tut=0,sakla,ders1,kredi;
	int kod, dikkat=0, dikkat2=0;
	
	FILE *ogrenci_kayit_sil =  fopen("OgrenciDersKayit.txt","r");
	FILE *kopyala = fopen("kopya.txt","w");
	
	if (ogrenci_kayit_sil == NULL){
		printf("�yle bir dosya yok !");
		return;
	}
	else{
		printf("Dosya bulundu.\n");
	}

	printf("\nL�tfen dersini silmek istedi�iniz ��rencinin ID'sini giriniz: ");
	scanf("%d",&id); 
	
	printf("L�tfen ��renciye ait silmek istedi�iniz dersin kodunu giriniz: ");
	scanf("%d",&kod);
	
	FILE *dosya_ders = fopen("dersler.txt","r");
	FILE *ogrencileer = fopen("ogrenciler.txt","r");
	
	while(!feof(dosya_ders)){
		fscanf(dosya_ders, "%d %s %d %d %d", &ders.ID, ders.ders_adi, &ders.toplam_kredi, &ders.kontenjan, &ders.hoca_id);
			
		if(kod == ders.ID){
			dikkat = 1;
		}
	}
	
	while(!feof(ogrencileer)){
		fscanf(ogrencileer, "%d %s %s %d %d", &ogr.ID, ogr.ad, ogr.soyad, &ogr.toplam_ders, &ogr.toplam_kredi);
			
		if(id == ogr.ID){
			dikkat2 = 1;
		}
	}
	
	fclose(dosya_ders);
	fclose(ogrencileer);
	
	if(dikkat == 0 || dikkat2 == 0){
		printf("�zg�n�z. Ders kodu ya da b�yle bir ��renci id'si bulunmamaktad�r.");
	}
	
	fseek(ogrenci_kayit_sil,0,SEEK_SET);
	
	while(!feof(ogrenci_kayit_sil) && dikkat == 1 && dikkat2 == 1){
		
		fscanf(ogrenci_kayit_sil, "%d %d %d %s %d",&sil.ID, &sil.ogr_no, &sil.ders_kod, sil.tarih, &sil.kayit_durum);
		
		if(temp1 != sil.ogr_no){
			if(id != sil.ogr_no ){
				fprintf(kopyala, "%d %d %d %s %d\n",sil.ID, sil.ogr_no, sil.ders_kod, sil.tarih, sil.kayit_durum);
			}
			else{
				if(sil.ders_kod == kod){
					if(sil.kayit_durum == 1){
						sil.kayit_durum=0;
						fprintf(kopyala,"%d %d %d %s %d\n",sil.ID, sil.ogr_no, sil.ders_kod, sil.tarih, sil.kayit_durum);
						tut=1;
						sakla=sil.ders_kod;
					}
				}
				else{
					fprintf(kopyala, "%d %d %d %s %d\n",sil.ID, sil.ogr_no, sil.ders_kod, sil.tarih, sil.kayit_durum);
				}
			}
		temp1 = sil.ogr_no;
		}
	}
	
	fclose(ogrenci_kayit_sil);
	fclose(kopyala);
		
	if(tut==0){
		printf("%d ID'ye sahip bir ��renci bulunmamaktad�r.\n",id);
		remove("kopya.txt");
	}
	else{
		remove("OgrenciDersKayit.txt");
		rename("kopya.txt","OgrenciDersKayit.txt");
		printf("��renci ders kay�t dosyas�ndan dersi silindi !\n");
		
		FILE *dosya_ders;
		dosya_ders = fopen("dersler.txt","r");
		
		while(!feof(dosya_ders)){
			fscanf(dosya_ders, "%d %s %d %d %d", &ders.ID, ders.ders_adi, &ders.toplam_kredi, &ders.kontenjan, &ders.hoca_id);
			if(sakla == ders.ID){
				kredi = ders.toplam_kredi;
				kredi = kredi*(-1);
			}
		}
		ders1=-1;
		fclose(dosya_ders);
		ogrenci_ders_kredi_guncelleme(ders1,kredi,id);
	}
}

void kayitli_ogrenciler(){
	
	int kod, cik=0,i=1,kod2;
	struct ogrenci_ders_kayit kontrol;
	
	FILE *ders = fopen("OgrenciDersKayit.txt","r");
	
	printf("\nL�tfen ders kodunu giriniz: ");
	scanf("%d",&kod);
	
	while(!feof(ders)){
		fscanf(ders, "%d %d %d %s %d", &kontrol.ID, &kontrol.ogr_no, &kontrol.ders_kod, kontrol.tarih, &kontrol.kayit_durum);
		
		if(kontrol.ID != kod2){
			if(kod == kontrol.ders_kod && kontrol.kayit_durum==1){
				cik=1;
				printf("%d) %d\n",i,kontrol.ogr_no);
				i++;
			}
		}
		kod2 = kontrol.ID;
	}
	
	if(cik==0){
		printf("Kodu verilen derse ait ��renci bulunamam��t�r. \n");
	}
	fclose(ders);
}

void dersleri_listele(){
	int og_ID,i=1;
	int cik=0,kod2;
	
	struct ogrenci_ders_kayit listele;
	
	FILE *ders = fopen("OgrenciDersKayit.txt","r");
	
	printf("\nL�tfen ��renci ID'yi giriniz: ");
	scanf("%d",&og_ID);	
	
	while(!feof(ders)){
		fscanf(ders, "%d %d %d %s %d", &listele.ID, &listele.ogr_no, &listele.ders_kod, listele.tarih, &listele.kayit_durum);
		
		if(listele.ID != kod2){
			if(og_ID == listele.ogr_no && listele.kayit_durum==1){
				cik=1;
				printf("%d) %d\n",i,listele.ders_kod);
				i++;
			}
		}
		kod2 = listele.ID;
	}
	
	if(cik==0){
		printf("Girilen ��renci ID'sine ait ders bulunamam��t�r. \n");
	}
	fclose(ders);
}

void derskodu_siniflistesi(){
	int id,kod,dene,dene2;
	int tut=0,tut2=0;
	int *sakla = (int*)malloc(sizeof(int)*50);
	int i=0,n=0;
	struct ogretim_uyesi kontrol;
	struct dersler ders;
	struct ogrenci_ders_kayit listele;
	struct ogrenciler ogrenci;
	
	printf("\nL�tfen ��retim �yesinin ID'sini giriniz: ");
	scanf("%d",&id);
	
	FILE *dosya_ogretim_uyesi =  fopen("ogretim_uyesi.txt","r");
	
	fseek(dosya_ogretim_uyesi,0,SEEK_SET);
	
	while(!feof(dosya_ogretim_uyesi)){
		
		fscanf(dosya_ogretim_uyesi, "%d %s %s %s",&kontrol.ID, kontrol.ad, kontrol.soyad, kontrol.unvan);
		
		if(id == kontrol.ID){
			tut=1;
		}	
	}
		
	fclose(dosya_ogretim_uyesi);
	
	if(tut==0){
		printf("%d ID'ye sahip bir ��retim �yesi bulunmamaktad�r.\n",id);
	}
	else{
		printf("L�tfen ilgili ��retim �yesinin verdi�i dersin kodunu giriniz: ");
		scanf("%d",&kod);
		
		FILE *dosya_dersler =  fopen("dersler.txt","r");
		
		while(!feof(dosya_dersler)){
			fscanf(dosya_dersler, "%d %s %d %d %d", &ders.ID, ders.ders_adi, &ders.toplam_kredi, &ders.kontenjan, &ders.hoca_id);
		
			if(kod == ders.ID && id == ders.hoca_id){
				tut2=1;
			}
		}
		
		fclose(dosya_dersler);
	}
	
	if(tut==1 && tut2==0){
		printf("%d ID'ye sahip bir ��retim �yesinin verdi�i ders bulunmamaktad�r.\n",id);
	}
	
	if(tut!=0 && tut2!=0){
		
		FILE *dosya_ders_kayit =  fopen("OgrenciDersKayit.txt","r");
		fseek(dosya_ders_kayit,0,SEEK_SET);
		
		while(!feof(dosya_ders_kayit)){
			fscanf(dosya_ders_kayit, "%d %d %d %s %d", &listele.ID, &listele.ogr_no, &listele.ders_kod, listele.tarih, &listele.kayit_durum);
			if(dene != listele.ID){
			if(kod == listele.ders_kod && listele.kayit_durum == 1){
				sakla[i] = listele.ogr_no;
				i++;
				n++;
			}
			}
			dene = listele.ID;
		}
		
		fclose(dosya_ders_kayit);
			
		FILE *siniflistesi = fopen("DERSKODU_SINIFL�STES�.txt ","w");
		FILE *ogrenciler = fopen("ogrenciler.txt","r");
		 
		i=0;
		while(i<n){
			fseek(ogrenciler,0,SEEK_SET);
			while(!feof(ogrenciler)){
				fscanf(ogrenciler, "%d %s %s %d %d", &ogrenci.ID, ogrenci.ad, ogrenci.soyad, &ogrenci.toplam_ders, &ogrenci.toplam_kredi);
				if(dene2 != ogrenci.ID){
				if(sakla[i] == ogrenci.ID){
					fprintf(siniflistesi,"%d %s %s\n",ogrenci.ID,ogrenci.ad,ogrenci.soyad);
					i++;
					break;
				}
				}
				dene2 = ogrenci.ID;
			}
		}
		fclose(siniflistesi);
		fclose(ogrenciler);
		printf("\nS�n�f listesi DERSKODU_SINIFL�STES� dosyas�na yaz�lm��t�r.\n");
	}
	free(sakla);
}


