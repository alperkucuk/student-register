#include <stdio.h>
#include <stdlib.h>
struct kayit {// temelde kullan�lan struct bu
	int ogrno ;
	int derskodu;
	int puan ;
};
int datacount (){//Veri dosyas�ndaki kay�t say�s�n� bulup d�nderen fonksiyon toplam i�eride 50 kay�t varsa 50 say�s�n� d�nderiyor
	int a;
	struct kayit before ;
	struct kayit now ;
	FILE *file ;
	file=fopen("veridosyasi.bin","rb");// veri dosyas� okunuyor
	for(a=0;a<10000;a++){//Veri dosyas�ndaki eleman say�s�ndan daha fazla olacak �ekilde d�ng� d�n�yor veri dosyas�ndan i de�eri kadar eleman �ekiliyor e�er dosyada olan eleman say�s�ndan fazla eleman
		before.ogrno=now.ogrno ;// �ekilmek istenirse s�rekli dosyan�n sonundakini bast�r�yor bu y�zden hep bir �nceki struct� tutup ayn�s�m� diye kontrol ediyoruz ayn�s� oldu�u andada returnle 
		before.puan=now.puan ;// ka� defa �ekildi�ini al�yoruz buda veri dosyas�ndaki eleman say�m�z oluyor
		before.derskodu=now.derskodu ;
	fread(&now,sizeof(struct kayit),1,file);
	if(before.ogrno==now.ogrno && before.derskodu==now.derskodu && before.puan==now.puan){
		return a ;// return sayesinde d�nderme i�lemi bitiyor d�ng� k�r�l�yor
		}
						}
	fclose(file);	
}
void indexdosyasiolustur(){
	int a,b ;
	int count=datacount();// eleman say�s�n� ald�k
	struct kayit indexfile[count] ;// eleman say�s� kadar struct dizisi olu�turduk
	FILE *datafile ;
	datafile=fopen("veridosyasi.bin","rb");// veri dosyas� okunuyor
	for (a=0;a<count;a++){// veri dosyas� eleman say�s� elimizde oldu�undan o kadar veri �ekilip struct dizisine at�l�yor 
		fread(&indexfile[a],sizeof(struct kayit),1,datafile);// fread tek seferde 1 kay�t �ekiyor kay�t say�s� kadar �ekme i�emini indexfile struct dizisinin i�ine yap�yoruz.
	}
	fclose(datafile);
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlar� ogrno'ya g�re k���kten b�y��e s�ral�yoruz.
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
	file=fopen("indexdosyasi.txt","w");// veri dosyas� eleman say�s� kadar index dosyas�na s�ralanm�� verileri s�ras�yla bas�yoruz.
	for (a=0;a<count;a++){
		fprintf(file,"%d %d %d\n",indexfile[a].ogrno,indexfile[a].derskodu,indexfile[a].puan);
	}
	fclose(file);
	printf("�ndex dosyasi olusturuldu.\n");
}
void kayitEkle(struct kayit eklenecekstruct){// mainden struct geliyor 
	
	FILE *datafile ;
	datafile =fopen("veridosyasi.bin","ab");// dosyay� ekleme modunda a��yoruz.
	
	fwrite(&eklenecekstruct,sizeof(struct kayit),1,datafile);// veri dosyas�n�n sonuna gelen struct� ekliyoruz.
	
	fclose(datafile) ;
	int a,b ;
	int count=datacount();// eleman say�s�n� ald�k
	struct kayit indexfile[count] ;// eleman say�s� kadar struct olu�turduk
	FILE *data ;
	data=fopen("veridosyasi.bin","rb");// veri dosyas� okunuyor
	for (a=0;a<count;a++){// veri dosyas� eleman say�s� elimizde oldu�undan o kadar veri �ekilip struct dizisine at�l�yor 
		fread(&indexfile[a],sizeof(struct kayit),1,data);
	}
	fclose(data);
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlar� ogrno'ya g�re s�ral�yoruz.
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
	file=fopen("indexdosyasi.txt","w");// veri dosyas� eleman say�s� kadar index dosyas�na s�ralanm�� verileri s�ras�yla bas�yoruz.
	for (a=0;a<count;a++){
		fprintf(file,"%d %d %d\n",indexfile[a].ogrno,indexfile[a].derskodu,indexfile[a].puan);
	}
	fclose(file);
	printf("index dosyasi Guncellendi.\n");
}

void kayitBul(int ogrno,int derskodu,int puan){// mainden aranacak de�erleri al�yoruz.
	int count=datacount() ;// veri dosyas�ndaki eleman say�s�n� �ektik
	int *p,*t,a,b,c ;
	struct kayit indexfile[count];// eleman say�s� kadar struct olu�turduk
	FILE *dosya ;
	dosya=fopen("indexdosyasi.txt","r");// index dosyas�ndaki verileri al�yoruz ��nki s�ralanm�� binary search yaparken i�imize yarayacak
	int i,j ;
	for (i=0;i<count;i++){// index dosyas�ndaki verilerin al�nmas�
	fscanf(dosya,"%d %d %d\n",&a,&b,&c);// veriler x y z ye atan�yor ordanda yeni olu�turulmu� structa atan�yor
	indexfile[i].ogrno=a;
	indexfile[i].derskodu=b ;
	indexfile[i].puan=c ;
	}
	// burdan finaldizi[sayac]'a kadar olan yer binary search bunu bende internetten ald�m ekstra eklemelerimi yan�na yazaca��m
	int bb=count ;
	int sayac =0;
	int samearray[10];
	int k=-1 ;
	int flag=0 ;
	while(bb-k>1){
		int look=(bb+k)/2 ;
		p=indexfile[look].derskodu ;// derskodu ve puan adres olarak tutuldu�u i�in pointer olan p t ye atan�yor *p yap�ld���nda adresin g�sterdi�i yere gidiyor
		t=indexfile[look].puan ;
		if(indexfile[look].ogrno==ogrno && *p==derskodu && *t==puan){// kullan�c� ders kodunu ve puan� say� olarak veriyor pointerlar� kulland���m�zdan bizde say� olarak denk mi diye bak�yoruz
			flag=1 ;
			printf("istenilen kayit %d. indexte bulundu.",look);// hepsi denkse direk yazd�r�p break le d�ng�y� k�r�yor
			break ;
		}
		else if (sayac==10){
			break ;
		}
		else if (indexfile[look].ogrno==ogrno && indexfile[look].puan!=puan){// binary 'e ekledi�im yer buras� ogr no lar e�it ve puanlar e�it de�ilse buraya gidiyor 
			samearray[sayac]=look;// bu else if de bu �art� sa�layanlar�n index numaras� diziye atan�yor ama s�rekli diziye ayn� index numaralar�n� at�yor bu problemi ilerde ��z�yoruz.
			sayac++;// �imdilik en fazla ayn� ogr no sahip kay�tlar�n 10 defa bulunabilece�ini d���kd�k ve diziye o kadar eleman ald�k k�sacas� ayn� ogr noya sahip 2 index varsa 
			bb++ ;// s�rekli burada dizinin i�ine belli olmayan s�rada o 2 indexi veriyor
		}
		else if(indexfile[look].ogrno<ogrno){// oto binary search
			k=look ;
		}
		else {// oto binary search
			bb=look ;
		}
		
	}
	// dizide 0 1 0 1 0 1 gibi ayn� say�lar vard� ayn� say�lar� 0 ve 1 olacak �ekilde distinct edilmesini sa�layan i�lem a�a��daki for d�ng�s�
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
	// yukar�da kullan�c�n�n girdi�i de�erlere e�it bir kay�t bulunursa bulundu diyip breakla d�ng�y� k�r�yordu e�er oraya girerse flag'da 1 oluyor oraya girmeden d�ng� k�r�ld�ysa flag 0 kal�yor bu sayede aranan de�erdeki kayd�n bulunamad���n� anl�yor�z
	if (flag==0){
		printf("Kayit yok.\n");
	}
}
void kayitSil(){
	printf("ogr no girin:");// silinmesini istediginimiz kay�tlar� al�yoruz
	int q,w,e,i,c=0,b=0 ;
	scanf("%d",&q);
	printf("ders kodu girin:");
	scanf("%d",&w);
	printf("puan girin:");
	scanf("%d",&e);
	int count=datacount();// di�erleri ile ayn�
	struct kayit binaryfile[count] ;
	FILE *datafile ;
	datafile=fopen("veridosyasi.bin","rb");//okuma modunda a�t�k 
	for (i=0;i<count;i++){
		fread(&binaryfile[i],sizeof(struct kayit),1,datafile);// i�eridekileri struct dizisine ald�k
	}
	fclose(datafile);
	int *l,*k,final=-15 ;
	for(i=0;i<count;i++){// silinmesini istedi�imiz kayitlar�n index numaras�n� bulduruyoruz.sonuca at�yoruz
		l=binaryfile[i].derskodu ;
		k=binaryfile[i].puan ;
		if(q==binaryfile[i].ogrno && *l==w && *k==e){
			final=i ;
		}
	}
	if(final==-15){//sonuc hala -15 ise kay�t bulunamad� demek 
		printf("Bu girilen degerlerde kayit bulunamadi.\n");
	}
	else{// sonucun -15 olmad��� durumda 
		
	FILE *dosya ;
	dosya =fopen("veridosyasi.bin","wb");
	for(i=0;i<count;i++){// ba�tan dosyay� yazd�r�yoruz ama o indexe geldi�inde yazma i�lemi yapm�yor bu �ekilde yeni veri dosyas�nda o kay�t silinmi� oluyor
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
	data=fopen("veridosyasi.bin","rb");// veri dosyas� okunuyor
	for (i=0;i<count;i++){// veri dosyas� eleman say�s� elimizde oldu�undan o kadar veri �ekilip struct dizisine at�l�yor 
		fread(&indexfile[i],sizeof(struct kayit),1,data);
	}
	fclose(data);
	
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlar� ogrno'ya g�re s�ral�yoruz.
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
	file=fopen("indexdosyasi.txt","w");// veri dosyas� eleman say�s� kadar index dosyas�na s�ralanm�� verileri s�ras�yla bas�yoruz.
	for (i=0;i<count;i++){
		fprintf(file,"%d %d %d\n",indexfile[i].ogrno,indexfile[i].derskodu,indexfile[i].puan);
	}
	fclose(file);
	printf("�ndex dosyasi Guncellestirildi.\n");
	
	
	
}
static int zsayisi ;
void kayitGuncelle(){
		int q,w,e ;// g�ncellenmesini istedigmiz kayd�n ogr nosunu ve derskodunu al�yoruz ve yeni puan� 
		printf("ogrnosunu giriniz :");
		scanf("%d",&q);
		printf("ders kodunu giriniz :");
		scanf("%d",&w);
		printf("yeni puani :");
		scanf("%d",&e);

	int count=datacount();// yine ayn�
	struct kayit now[count] ;
	int i,tutucu=0;
	FILE *datafile ;
	datafile=fopen("veridosyasi.bin","rb");// okuma modunda a�t�k
	for (i=0;i<count;i++){
		fread(&now[i],sizeof(struct kayit),1,datafile);// eleman say�s� kadar eldeki isimli struct dizisine veri dosyas�ndakileri �ektik
	}
	fclose(datafile);
	int *pointer ;
	zsayisi=e ;
	for (i=0;i<count;i++){//t�m struct dizisi i�inde arama yap�l�yor kullan�c�dan al�nan ogr no ve ders kodunun e�it oldu�u kay�t varsa kullan�c�n�n verdi�i de�erin adresi 
		pointer=now[i].derskodu ;// o indexteki puana atan�yor
		if(now[i].ogrno==q && *pointer==w){
			now[i].puan=&zsayisi ;
			tutucu++;
			printf("kayit degistirildi.\n");
		}
	}
	if(tutucu==0){// ogr nosu ve ders kodu e�it kay�t bulunamad�ysa
		printf(" eslesme yok .\n");
	}
	FILE *file ;
	file =fopen("veridosyasi.bin","wb");// en son g�ncelennene struct dizisi tekrardan veri dosyas�na bas�l�yor
	for(i=0;i<count;i++){
			fwrite(&now[i],sizeof(struct kayit),1,file);
	}
	fclose(file) ;	
	
	int a,b ;
	struct kayit indexfile[count] ;// eleman say�s� kadar struct olu�turduk
	FILE *binaryfile ;
	binaryfile=fopen("veridosyasi.bin","rb");// veri dosyas� okunuyor
	for (a=0;a<count;a++){// veri dosyas� eleman say�s� elimizde oldu�undan o kadar veri �ekilip struct dizisine at�l�yor 
		fread(&indexfile[a],sizeof(struct kayit),1,binaryfile);
	}
	fclose(binaryfile);
	struct kayit kayt ;
	for(b=1;b<count;b++)// bu 2 for sayesinde struct dizisindeki elemanlar� ogrno'ya g�re s�ral�yoruz.
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
	filee=fopen("indexdosyasi.txt","w");// veri dosyas� eleman say�s� kadar index dosyas�na s�ralanm�� verileri s�ras�yla bas�yoruz.
	for (a=0;a<count;a++){
		fprintf(filee,"%d %d %d\n",indexfile[a].ogrno,indexfile[a].derskodu,indexfile[a].puan);
	}
	fclose(filee);
	printf("index dosyasi guncellendi.\n");
	
	
	
	
}
void veriDosyasiniGoster(){
	int count=datacount();// ayn� �eyler
	struct kayit datafile[count] ;
	int i;
	FILE *verifile ;
	verifile=fopen("veridosyasi.bin","rb");// okuma modunda veri dosyas� a��ld�
	for (i=0;i<count;i++){
		fread(&datafile[i],sizeof(struct kayit),1,verifile);// t�m kay�tlar veridosyas� struct dizisine at�ld�
	}
	fclose(verifile);
	printf("veri dosyasi orjinal\n");//veri dosyas�n�n orjinal hali bas�l�yor
	for(i=0;i<count;i++){
		printf("%d %d %d\n",datafile[i].ogrno,datafile[i].derskodu,datafile[i].puan);
	}
}
void indeksDosyasiniGoster(){//veri dosyas�ndaki muhabbetin tamamen ayn�s�
	int count=datacount() ;
	int x,y,z ;
	struct kayit indexfile[count];// kay�t say�s� al�nd�
	FILE *dosya ;
	dosya=fopen("indexdosyasi.txt","r");// okuma modunda dosya a��ld�
	int i ;
	for (i=0;i<count;i++){// 
	
	fscanf(dosya,"%d %d %d\n",&x,&y,&z);// kay�tlar �nce x y z ye sonra structa at�ld�

	indexfile[i].ogrno=x;
	indexfile[i].derskodu=y ;
	indexfile[i].puan=z ;
	}
	fclose(dosya);
	printf("index dosyasi \n");
	for(i=0;i<count;i++){// structtaki kay�tlar ekrana bas�ld�.
		printf("%d %d %d\n",indexfile[i].ogrno,indexfile[i].derskodu,indexfile[i].puan);
	}	
}
void indeksDosyasiniSil(){// remote ile index dosyas� siliniyor
	int donus = remove("indexdosyasi.txt");
	if(donus == 0){
    fprintf(stdout, "Dosya silindi\n");
  		}
}
void veridosyasisayisal(){
	int count=datacount();// ayn� �eyler
	struct kayit datafile[count] ;
	int i,*p,*t;
	FILE *verifile ;
	verifile=fopen("veridosyasi.bin","rb");// okuma modunda veri dosyas� a��ld�
	for (i=0;i<count;i++){
		fread(&datafile[i],sizeof(struct kayit),1,verifile);// t�m kay�tlar veridosyas� struct dizisine at�ld�
	}
	fclose(verifile);
	printf("veri dosyasi sayisal hali\n");//veri dosyas�n�n say�sal hali bas�l�yor
	for(i=0;i<count;i++){
		p=datafile[i].derskodu ;// ders kodu ve puan adresi tutuyordu pointer�n adresine onu atay�p *p yapt���m�zda adresin g�sterdi�i yerdeki de�eri g�steriyor.
		t=datafile[i].puan ;
		printf("%d %d %d\n",datafile[i].ogrno,*p,*t);// direk *p ile de�erler bas�ld�
	}
	
}
void indexdosyasisayisal(){// index dosyas�yla ayn� 
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
	for(i=0;i<count;i++){// ders kodu ve puan adres olarak tutuldu�undan pointera atand� ard�ndanda *p diyerek direk de�erler g�sterildi.
		p=indexfile[i].derskodu ;
		t=indexfile[i].puan ;
		printf("%d %d %d\n",indexfile[i].ogrno,*p,*t);
	}	
	
}



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Veri dosyas� olu�turma b�l�m�
	struct kayit datafile[50];
	struct kayit datafile2[50];
	int x ;
	
	
	for (x=0;x<50;x++){// �nce d�ng�deki de�i�kenlerin de�erine g�re binary isimli struct dizisine ogr derskodu ve puan atan�yor
	datafile2[x].ogrno=x%27+7;//datafile2 nin ogr nosuna direk say� atan�yor ��nki anahtar o direk say� olmas� gerekiyor
	datafile[x].derskodu=x%7+1;//ders kodu ve puana direk say�lar atan�yor a�a��da o say�lar�n adresleri datafile2 'ye atan�yor
	datafile[x].puan=x%100+30 ;
	datafile2[x].derskodu=&datafile[x].derskodu;// ard�ndan datafile i�erisindeki ders kodu ve puan�n adresi datafile2 nini i�erisine atan�yor
	datafile2[x].puan=&datafile[x].puan ;
	}
	
	FILE *data ;
	data =fopen("veridosyasi.bin","wb");// dosya binary file format�nda a��l�yor 
	for(x=0;x<50;x++){// struct dizisinin i�inde 50 farkl� girdi oldu�unda binary file 'a 50 kere bas�lmas� i�in d�ng� 50 defa d�n�yor
	fwrite(&datafile2[x],sizeof(struct kayit),1,data);// standart binary file yazma komutlar�
	}
	fclose(data) ;

	//Veri dosyas� olu�turma b�l�m�
	while(1){//d�ng�n�n s�rekli d�nmesi i�in while 1
	printf("1 index dosyas� yaratmak icin\n")	;
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
	if(secim==1){// gelen de�er 1 ise index bu fonksiyona gidiyor
		indexdosyasiolustur();
	}
	else if(secim==2){// eklenmek istenen kay�tlar �ekilip structa at�l�p struct fonksiyona g�nderiliyor
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
	else if(secim==3){// aran�lacak de�erler �ekilip fonksiyona g�nderiliyor
		int no,derskodu,puan ;
		printf("lutfen aranacak ogrenci numarasini giriniz.:\n");
		scanf("%d",&no);
		printf("lutfen aranacak ders kodunu giriniz.:\n");
		scanf("%d",&derskodu);
		printf("lutfen aranacak puani giriniz.:\n");
		scanf("%d",&puan);
		kayitBul(no,derskodu,puan);
	}
	else if(secim==4){// buras� ve a�a��s� her�ey fonksiyonlarda 
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
