#include <stdio.h>
#include <stdlib.h>
struct kayit {// temelde kullanýlan struct bu
	int ogrno ;
	int derskodu;
	int puan ;
};
int datacount (){//Veri dosyasýndaki kayýt sayýsýný bulup dönderen fonksiyon toplam içeride 50 kayýt varsa 50 sayýsýný dönderiyor
	int a;
	struct kayit before ;
	struct kayit now ;
	FILE *file ;
	file=fopen("veridosyasi.bin","rb");// veri dosyasý okunuyor
	for(a=0;a<10000;a++){//Veri dosyasýndaki eleman sayýsýndan daha fazla olacak þekilde döngü dönüyor veri dosyasýndan i deðeri kadar eleman çekiliyor eðer dosyada olan eleman sayýsýndan fazla eleman
		before.ogrno=now.ogrno ;// çekilmek istenirse sürekli dosyanýn sonundakini bastýrýyor bu yüzden hep bir önceki structý tutup aynýsýmý diye kontrol ediyoruz aynýsý olduðu andada returnle 
		before.puan=now.puan ;// kaç defa çekildiðini alýyoruz buda veri dosyasýndaki eleman sayýmýz oluyor
		before.derskodu=now.derskodu ;
	fread(&now,sizeof(struct kayit),1,file);
	if(before.ogrno==now.ogrno && before.derskodu==now.derskodu && before.puan==now.puan){
		return a ;// return sayesinde dönderme iþlemi bitiyor döngü kýrýlýyor
		}
						}
	fclose(file);	
}
void indexdosyasiolustur(){
	int a,b ;
	int count=datacount();// eleman sayýsýný aldýk
	struct kayit indexfile[count] ;// eleman sayýsý kadar struct dizisi oluþturduk
	FILE *datafile ;
	datafile=fopen("veridosyasi.bin","rb");// veri dosyasý okunuyor
	for (a=0;a<count;a++){// veri dosyasý eleman sayýsý elimizde olduðundan o kadar veri çekilip struct dizisine atýlýyor 
		fread(&indexfile[a],sizeof(struct kayit),1,datafile);// fread tek seferde 1 kayýt çekiyor kayýt sayýsý kadar çekme iþemini indexfile struct dizisinin içine yapýyoruz.
	}
	fclose(datafile);
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlarý ogrno'ya göre küçükten büyüðe sýralýyoruz.
       {
           for (a=0;a<count - 1;a++)
          {
           if (indexfile[a].ogrno>indexfile[a+1].ogrno)
           {
               kayt.ogrno=indexfile[a].ogrno;
               kayt.derskodu=indexfile[a].derskodu;
               kayt.puan=indexfile[a].puan ;
               indexfile[a].ogrno=indexfile[a+1].ogrno;
               indexfile[a].derskodu=indexfile[a+1].derskodu;
               indexfile[a].puan=indexfile[a+1].puan;
               indexfile[a+1].ogrno=kayt.ogrno;
               indexfile[a+1].derskodu=kayt.derskodu;
               indexfile[a+1].puan=kayt.puan;
           }
          }
       }
	FILE *file ;
	file=fopen("indexdosyasi.txt","w");// veri dosyasý eleman sayýsý kadar index dosyasýna sýralanmýþ verileri sýrasýyla basýyoruz.
	for (a=0;a<count;a++){
		fprintf(file,"%d %d %d\n",indexfile[a].ogrno,indexfile[a].derskodu,indexfile[a].puan);
	}
	fclose(file);
	printf("Ýndex dosyasi olusturuldu.\n");
}
void kayitEkle(struct kayit eklenecekstruct){// mainden struct geliyor 
	
	FILE *datafile ;
	datafile =fopen("veridosyasi.bin","ab");// dosyayý ekleme modunda açýyoruz.
	
	fwrite(&eklenecekstruct,sizeof(struct kayit),1,datafile);// veri dosyasýnýn sonuna gelen structý ekliyoruz.
	
	fclose(datafile) ;
	int a,b ;
	int count=datacount();// eleman sayýsýný aldýk
	struct kayit indexfile[count] ;// eleman sayýsý kadar struct oluþturduk
	FILE *data ;
	data=fopen("veridosyasi.bin","rb");// veri dosyasý okunuyor
	for (a=0;a<count;a++){// veri dosyasý eleman sayýsý elimizde olduðundan o kadar veri çekilip struct dizisine atýlýyor 
		fread(&indexfile[a],sizeof(struct kayit),1,data);
	}
	fclose(data);
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlarý ogrno'ya göre sýralýyoruz.
       {
           for (a=0;a<count - 1;a++)
          {
           if (indexfile[a].ogrno>indexfile[a+1].ogrno)
           {
               kayt.ogrno=indexfile[a].ogrno;
               kayt.derskodu=indexfile[a].derskodu;
               kayt.puan=indexfile[a].puan ;
               indexfile[a].ogrno=indexfile[a+1].ogrno;
               indexfile[a].derskodu=indexfile[a+1].derskodu;
               indexfile[a].puan=indexfile[a+1].puan;
               indexfile[a+1].ogrno=kayt.ogrno;
               indexfile[a+1].derskodu=kayt.derskodu;
               indexfile[a+1].puan=kayt.puan;
           }
          }
       }
	FILE *file ;
	file=fopen("indexdosyasi.txt","w");// veri dosyasý eleman sayýsý kadar index dosyasýna sýralanmýþ verileri sýrasýyla basýyoruz.
	for (a=0;a<count;a++){
		fprintf(file,"%d %d %d\n",indexfile[a].ogrno,indexfile[a].derskodu,indexfile[a].puan);
	}
	fclose(file);
	printf("index dosyasi Guncellendi.\n");
}

void kayitBul(int ogrno,int derskodu,int puan){// mainden aranacak deðerleri alýyoruz.
	int count=datacount() ;// veri dosyasýndaki eleman sayýsýný çektik
	int *p,*t,a,b,c ;
	struct kayit indexfile[count];// eleman sayýsý kadar struct oluþturduk
	FILE *dosya ;
	dosya=fopen("indexdosyasi.txt","r");// index dosyasýndaki verileri alýyoruz çünki sýralanmýþ binary search yaparken iþimize yarayacak
	int i,j ;
	for (i=0;i<count;i++){// index dosyasýndaki verilerin alýnmasý
	fscanf(dosya,"%d %d %d\n",&a,&b,&c);// veriler x y z ye atanýyor ordanda yeni oluþturulmuþ structa atanýyor
	indexfile[i].ogrno=a;
	indexfile[i].derskodu=b ;
	indexfile[i].puan=c ;
	}
	// burdan finaldizi[sayac]'a kadar olan yer binary search bunu bende internetten aldým ekstra eklemelerimi yanýna yazacaðým
	int bb=count ;
	int sayac =0;
	int samearray[10];
	int k=-1 ;
	int flag=0 ;
	while(bb-k>1){
		int look=(bb+k)/2 ;
		p=indexfile[look].derskodu ;// derskodu ve puan adres olarak tutulduðu için pointer olan p t ye atanýyor *p yapýldýðýnda adresin gösterdiði yere gidiyor
		t=indexfile[look].puan ;
		if(indexfile[look].ogrno==ogrno && *p==derskodu && *t==puan){// kullanýcý ders kodunu ve puaný sayý olarak veriyor pointerlarý kullandýðýmýzdan bizde sayý olarak denk mi diye bakýyoruz
			flag=1 ;
			printf("istenilen kayit %d. indexte bulundu.",look);// hepsi denkse direk yazdýrýp break le döngüyü kýrýyor
			break ;
		}
		else if (sayac==10){
			break ;
		}
		else if (indexfile[look].ogrno==ogrno && indexfile[look].puan!=puan){// binary 'e eklediðim yer burasý ogr no lar eþit ve puanlar eþit deðilse buraya gidiyor 
			samearray[sayac]=look;// bu else if de bu þartý saðlayanlarýn index numarasý diziye atanýyor ama sürekli diziye ayný index numaralarýný atýyor bu problemi ilerde çözüyoruz.
			sayac++;// þimdilik en fazla ayný ogr no sahip kayýtlarýn 10 defa bulunabileceðini düþükdük ve diziye o kadar eleman aldýk kýsacasý ayný ogr noya sahip 2 index varsa 
			bb++ ;// sürekli burada dizinin içine belli olmayan sýrada o 2 indexi veriyor
		}
		else if(indexfile[look].ogrno<ogrno){// oto binary search
			k=look ;
		}
		else {// oto binary search
			bb=look ;
		}
		
	}
	// dizide 0 1 0 1 0 1 gibi ayný sayýlar vardý ayný sayýlarý 0 ve 1 olacak þekilde distinct edilmesini saðlayan iþlem aþaðýdaki for döngüsü
		for (i=0; i<sayac; i++)
	{
			for (j=0; j<i; j++)
			{
				if (samearray[i] == samearray[j]){
					break;
					}
			}

			if (i == j){
				printf("Ayni anahtara sahip bir kayit %d. indexte bulundu.\n", samearray[i]);
				}
	}
	// yukarýda kullanýcýnýn girdiði deðerlere eþit bir kayýt bulunursa bulundu diyip breakla döngüyü kýrýyordu eðer oraya girerse flag'da 1 oluyor oraya girmeden döngü kýrýldýysa flag 0 kalýyor bu sayede aranan deðerdeki kaydýn bulunamadýðýný anlýyorýz
	if (flag==0){
		printf("Kayit yok.\n");
	}
}
void kayitSil(){
	printf("ogr no girin:");// silinmesini istediginimiz kayýtlarý alýyoruz
	int q,w,e,i,c=0,b=0 ;
	scanf("%d",&q);
	printf("ders kodu girin:");
	scanf("%d",&w);
	printf("puan girin:");
	scanf("%d",&e);
	int count=datacount();// diðerleri ile ayný
	struct kayit binaryfile[count] ;
	FILE *datafile ;
	datafile=fopen("veridosyasi.bin","rb");//okuma modunda açtýk 
	for (i=0;i<count;i++){
		fread(&binaryfile[i],sizeof(struct kayit),1,datafile);// içeridekileri struct dizisine aldýk
	}
	fclose(datafile);
	int *l,*k,final=-15 ;
	for(i=0;i<count;i++){// silinmesini istediðimiz kayitlarýn index numarasýný bulduruyoruz.sonuca atýyoruz
		l=binaryfile[i].derskodu ;
		k=binaryfile[i].puan ;
		if(q==binaryfile[i].ogrno && *l==w && *k==e){
			final=i ;
		}
	}
	if(final==-15){//sonuc hala -15 ise kayýt bulunamadý demek 
		printf("Bu girilen degerlerde kayit bulunamadi.\n");
	}
	else{// sonucun -15 olmadýðý durumda 
		
	FILE *dosya ;
	dosya =fopen("veridosyasi.bin","wb");
	for(i=0;i<count;i++){// baþtan dosyayý yazdýrýyoruz ama o indexe geldiðinde yazma iþlemi yapmýyor bu þekilde yeni veri dosyasýnda o kayýt silinmiþ oluyor
		if(final==i){
			final++;
		}
		else{
			fwrite(&binaryfile[i],sizeof(struct kayit),1,dosya);
		}
	}
	fclose(dosya) ;	
	}
	count=datacount();
	struct kayit indexfile[count] ;
	FILE *data ;
	data=fopen("veridosyasi.bin","rb");// veri dosyasý okunuyor
	for (i=0;i<count;i++){// veri dosyasý eleman sayýsý elimizde olduðundan o kadar veri çekilip struct dizisine atýlýyor 
		fread(&indexfile[i],sizeof(struct kayit),1,data);
	}
	fclose(data);
	
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlarý ogrno'ya göre sýralýyoruz.
       {
           for (i=0;i<count - 1;i++)
          {
           if (indexfile[i].ogrno>indexfile[i+1].ogrno)
           {
               kayt.ogrno=indexfile[i].ogrno;
               kayt.derskodu=indexfile[i].derskodu;
               kayt.puan=indexfile[i].puan ;
               indexfile[i].ogrno=indexfile[i+1].ogrno;
               indexfile[i].derskodu=indexfile[i+1].derskodu;
               indexfile[i].puan=indexfile[i+1].puan;
               indexfile[i+1].ogrno=kayt.ogrno;
               indexfile[i+1].derskodu=kayt.derskodu;
               indexfile[i+1].puan=kayt.puan;
           }
          }
       }
	FILE *file ;
	file=fopen("indexdosyasi.txt","w");// veri dosyasý eleman sayýsý kadar index dosyasýna sýralanmýþ verileri sýrasýyla basýyoruz.
	for (i=0;i<count;i++){
		fprintf(file,"%d %d %d\n",indexfile[i].ogrno,indexfile[i].derskodu,indexfile[i].puan);
	}
	fclose(file);
	printf("Ýndex dosyasi Guncellestirildi.\n");
	
	
	
}
static int zsayisi ;
void kayitGuncelle(){
		int q,w,e ;// güncellenmesini istedigmiz kaydýn ogr nosunu ve derskodunu alýyoruz ve yeni puaný 
		printf("ogrnosunu giriniz :");
		scanf("%d",&q);
		printf("ders kodunu giriniz :");
		scanf("%d",&w);
		printf("yeni puani :");
		scanf("%d",&e);

	int count=datacount();// yine ayný
	struct kayit now[count] ;
	int i,tutucu=0;
	FILE *datafile ;
	datafile=fopen("veridosyasi.bin","rb");// okuma modunda açtýk
	for (i=0;i<count;i++){
		fread(&now[i],sizeof(struct kayit),1,datafile);// eleman sayýsý kadar eldeki isimli struct dizisine veri dosyasýndakileri çektik
	}
	fclose(datafile);
	int *pointer ;
	zsayisi=e ;
	for (i=0;i<count;i++){//tüm struct dizisi içinde arama yapýlýyor kullanýcýdan alýnan ogr no ve ders kodunun eþit olduðu kayýt varsa kullanýcýnýn verdiði deðerin adresi 
		pointer=now[i].derskodu ;// o indexteki puana atanýyor
		if(now[i].ogrno==q && *pointer==w){
			now[i].puan=&zsayisi ;
			tutucu++;
			printf("kayit degistirildi.\n");
		}
	}
	if(tutucu==0){// ogr nosu ve ders kodu eþit kayýt bulunamadýysa
		printf(" eslesme yok .\n");
	}
	FILE *file ;
	file =fopen("veridosyasi.bin","wb");// en son güncelennene struct dizisi tekrardan veri dosyasýna basýlýyor
	for(i=0;i<count;i++){
			fwrite(&now[i],sizeof(struct kayit),1,file);
	}
	fclose(file) ;	
	
	int a,b ;
	struct kayit indexfile[count] ;// eleman sayýsý kadar struct oluþturduk
	FILE *binaryfile ;
	binaryfile=fopen("veridosyasi.bin","rb");// veri dosyasý okunuyor
	for (a=0;a<count;a++){// veri dosyasý eleman sayýsý elimizde olduðundan o kadar veri çekilip struct dizisine atýlýyor 
		fread(&indexfile[a],sizeof(struct kayit),1,binaryfile);
	}
	fclose(binaryfile);
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlarý ogrno'ya göre sýralýyoruz.
       {
           for (a=0;a<count - 1;a++)
          {
           if (indexfile[a].ogrno>indexfile[a+1].ogrno)
           {
               kayt.ogrno=indexfile[a].ogrno;
               kayt.derskodu=indexfile[a].derskodu;
               kayt.puan=indexfile[a].puan ;
               indexfile[a].ogrno=indexfile[a+1].ogrno;
               indexfile[a].derskodu=indexfile[a+1].derskodu;
               indexfile[a].puan=indexfile[a+1].puan;
               indexfile[a+1].ogrno=kayt.ogrno;
               indexfile[a+1].derskodu=kayt.derskodu;
               indexfile[a+1].puan=kayt.puan;
           }
          }
       }
	FILE *filee ;
	filee=fopen("indexdosyasi.txt","w");// veri dosyasý eleman sayýsý kadar index dosyasýna sýralanmýþ verileri sýrasýyla basýyoruz.
	for (a=0;a<count;a++){
		fprintf(filee,"%d %d %d\n",indexfile[a].ogrno,indexfile[a].derskodu,indexfile[a].puan);
	}
	fclose(filee);
	printf("index dosyasi guncellendi.\n");
	
	
	
	
}
void veriDosyasiniGoster(){
	int count=datacount();// ayný þeyler
	struct kayit datafile[count] ;
	int i;
	FILE *verifile ;
	verifile=fopen("veridosyasi.bin","rb");// okuma modunda veri dosyasý açýldý
	for (i=0;i<count;i++){
		fread(&datafile[i],sizeof(struct kayit),1,verifile);// tüm kayýtlar veridosyasý struct dizisine atýldý
	}
	fclose(verifile);
	printf("veri dosyasi orjinal\n");//veri dosyasýnýn orjinal hali basýlýyor
	for(i=0;i<count;i++){
		printf("%d %d %d\n",datafile[i].ogrno,datafile[i].derskodu,datafile[i].puan);
	}
}
void indeksDosyasiniGoster(){//veri dosyasýndaki muhabbetin tamamen aynýsý
	int count=datacount() ;
	int x,y,z ;
	struct kayit indexfile[count];// kayýt sayýsý alýndý
	FILE *dosya ;
	dosya=fopen("indexdosyasi.txt","r");// okuma modunda dosya açýldý
	int i ;
	for (i=0;i<count;i++){// 
	
	fscanf(dosya,"%d %d %d\n",&x,&y,&z);// kayýtlar önce x y z ye sonra structa atýldý

	indexfile[i].ogrno=x;
	indexfile[i].derskodu=y ;
	indexfile[i].puan=z ;
	}
	fclose(dosya);
	printf("index dosyasi \n");
	for(i=0;i<count;i++){// structtaki kayýtlar ekrana basýldý.
		printf("%d %d %d\n",indexfile[i].ogrno,indexfile[i].derskodu,indexfile[i].puan);
	}	
}
void indeksDosyasiniSil(){// remote ile index dosyasý siliniyor
	int donus = remove("indexdosyasi.txt");
	if(donus == 0){
    fprintf(stdout, "Dosya silindi\n");
  		}
}
void veridosyasisayisal(){
	int count=datacount();// ayný þeyler
	struct kayit datafile[count] ;
	int i,*p,*t;
	FILE *verifile ;
	verifile=fopen("veridosyasi.bin","rb");// okuma modunda veri dosyasý açýldý
	for (i=0;i<count;i++){
		fread(&datafile[i],sizeof(struct kayit),1,verifile);// tüm kayýtlar veridosyasý struct dizisine atýldý
	}
	fclose(verifile);
	printf("veri dosyasi sayisal hali\n");//veri dosyasýnýn sayýsal hali basýlýyor
	for(i=0;i<count;i++){
		p=datafile[i].derskodu ;// ders kodu ve puan adresi tutuyordu pointerýn adresine onu atayýp *p yaptýðýmýzda adresin gösterdiði yerdeki deðeri gösteriyor.
		t=datafile[i].puan ;
		printf("%d %d %d\n",datafile[i].ogrno,*p,*t);// direk *p ile deðerler basýldý
	}
	
}
void indexdosyasisayisal(){// index dosyasýyla ayný 
	int count=datacount() ;
	int x,y,z ;
	struct kayit indexfile[count];
	FILE *dosya ;
	dosya=fopen("indexdosyasi.txt","r");
	int i ;
	for (i=0;i<count;i++){
	
	fscanf(dosya,"%d %d %d\n",&x,&y,&z);

	indexfile[i].ogrno=x;
	indexfile[i].derskodu=y ;
	indexfile[i].puan=z ;
	}
	fclose(dosya);
	int *p,*t ;
	printf("index dosyasi \n");
	for(i=0;i<count;i++){// ders kodu ve puan adres olarak tutulduðundan pointera atandý ardýndanda *p diyerek direk deðerler gösterildi.
		p=indexfile[i].derskodu ;
		t=indexfile[i].puan ;
		printf("%d %d %d\n",indexfile[i].ogrno,*p,*t);
	}	
	
}



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Veri dosyasý oluþturma bölümü
	struct kayit datafile[50];
	struct kayit datafile2[50];
	int x ;
	
	
	for (x=0;x<50;x++){// Önce döngüdeki deðiþkenlerin deðerine göre binary isimli struct dizisine ogr derskodu ve puan atanýyor
	datafile2[x].ogrno=x%27+7;//datafile2 nin ogr nosuna direk sayý atanýyor çünki anahtar o direk sayý olmasý gerekiyor
	datafile[x].derskodu=x%7+1;//ders kodu ve puana direk sayýlar atanýyor aþaðýda o sayýlarýn adresleri datafile2 'ye atanýyor
	datafile[x].puan=x%100+30 ;
	datafile2[x].derskodu=&datafile[x].derskodu;// ardýndan datafile içerisindeki ders kodu ve puanýn adresi datafile2 nini içerisine atanýyor
	datafile2[x].puan=&datafile[x].puan ;
	}
	
	FILE *data ;
	data =fopen("veridosyasi.bin","wb");// dosya binary file formatýnda açýlýyor 
	for(x=0;x<50;x++){// struct dizisinin içinde 50 farklý girdi olduðunda binary file 'a 50 kere basýlmasý için döngü 50 defa dönüyor
	fwrite(&datafile2[x],sizeof(struct kayit),1,data);// standart binary file yazma komutlarý
	}
	fclose(data) ;

	//Veri dosyasý oluþturma bölümü
	while(1){//döngünün sürekli dönmesi için while 1
	printf("1 index dosyasý yaratmak icin\n")	;
	printf("2 Kayit eklemek icin\n");
	printf("3 Kayit bulmak icin \n");	
	printf("4 Kayit silmek icin \n")	;
	printf("5 Kayit guncellemek icin \n");	
	printf("6 Veri dosyasi gormek icin \n");	
	printf("7 index dosyasini gormek icin \n");	
	printf("8 index dosyasi silmek icin \n")	;
	printf("9 Veri dosyasi sayisal olarak gormek icin \n");	
	printf("10 index dosyasini sayisal olarak gormek icin \n");	
	
	int secim ;
	scanf("%d",&secim);
	if(secim==1){// gelen deðer 1 ise index bu fonksiyona gidiyor
		indexdosyasiolustur();
	}
	else if(secim==2){// eklenmek istenen kayýtlar çekilip structa atýlýp struct fonksiyona gönderiliyor
		int no,derskodu,puan ;
		printf("lutfen ogrenci numarasini giriniz.:\n");
		scanf("%d",&no);
		printf("lutfen ders kodunu giriniz.:\n");
		scanf("%d",&derskodu);
		printf("lutfen puani giriniz.:\n");
		scanf("%d",&puan);
		struct kayit veri ;
		veri.ogrno=no ;
		veri.derskodu=&derskodu ;
		veri.puan=&puan ;
		
		
		kayitEkle(veri);
		
	}
	else if(secim==3){// aranýlacak deðerler çekilip fonksiyona gönderiliyor
		int no,derskodu,puan ;
		printf("lutfen aranacak ogrenci numarasini giriniz.:\n");
		scanf("%d",&no);
		printf("lutfen aranacak ders kodunu giriniz.:\n");
		scanf("%d",&derskodu);
		printf("lutfen aranacak puani giriniz.:\n");
		scanf("%d",&puan);
		kayitBul(no,derskodu,puan);
	}
	else if(secim==4){// burasý ve aþaðýsý herþey fonksiyonlarda 
		kayitSil();
	}
	else if(secim==5){
		
		kayitGuncelle();
	}
	else if(secim==6){
		veriDosyasiniGoster();
	}
	else if(secim==7){
		indeksDosyasiniGoster();
	}
	else if(secim==8){
		indeksDosyasiniSil();
	}
	else if(secim==9){
		veridosyasisayisal();
	}
	else if(secim==10){
		indexdosyasisayisal();
	}
}
	return 0;
}
