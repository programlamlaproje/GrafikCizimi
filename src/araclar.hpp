#ifndef ARACLAR_HPP_
#define ARACLAR_HPP_

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include "wtypes.h"
#include "Denklem_Okuma.h"

using namespace sf;

int 	PENCERE_ENI=1080,	//Acilan pencerenin enini belirler.
		PENCERE_YUKSEKLIGI=720,	//Acilan pencerenin boyunu belirler.
		SIMGE_BOYUTU=20,	//Secilen kalemin ya da silginin boyutunu belirler.
		MENU_SIMGE_BOYUTU=15,	//Ust menude görünen simgelerin boyutunu belirler.
		kalem_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*23,	//*****************
		kalem_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*21,		//
		silgi_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*22,	//Simgelerin menudeki baslangic ve bitis konumlari
		silgi_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*20,		//
		cop_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*19,		//
		cop_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*17,			//
		kaydet_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*16,	//
		kaydet_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*14,
		ekran_degistir_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*13,	//
		ekran_degistir_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*11,//*****************
		yakinlastirma_katsayisi=50,//Grafigin yakinlik ve uzaklik degerini belirler.
		menu_degisken=1, 		//kalem=1, silgi=2
		R=0,G=255,B=0	//Kalem cizgisi icin renkler
		;

static const int
x_eleman_sayisi=100,		//x-eksenindeki sayilarin dizisi icin eleman sayisi
y_eleman_sayisi=100		//y-eksenindeki sayilarin dizisi icin eleman sayisi
;

float 	eksen_kalinligi=2,//x ve y eksenlerinin kalinliklarini belirler.
		mouse_x,//Farenin guncel x koordinatini verir.
		mouse_y, //Farenin guncel y koordinatini verir.
		mouse_eski_x, //Farenin hareket ettirilmeden ki x koordinatini verir.
		mouse_eski_y, //Farenin hareket ettirilmeden ki y koordinatini verir.
		kalem_kalinligi=1.5, //Kalemin kalinligini belirler.
		fark_x=0,	//Ekranin x-ekseninde kaydirilmasini saglar.
		fark_y=0	//Ekranin y-ekseninde kaydirilmasini saglar.
		;

bool sol_kontrol=false, //Farenin sag tusuna basiliyorsa true degerini alir.
		sag_kontrol=false,	////Farenin sol tusuna basiliyorsa true degerini alir.
		denklem_kontrol=false,	//Programdan denklem girisi yapildiginda true degerini alir
		ekran_degisti_mi=false,	//Ekran boyutuunu degistire basilirsa true olur
		kucuk_ekran=true	//Tam ekran olup olmadigina karar ver
		;

std::vector<CircleShape>kalem; //Kalem kullanimi icin dizi olusturur.
std::vector<int>yakinlik; //Kalem kullanimi icin dizi olusturur.
std::vector<int>renk;//Kalem kullanimi icin dizi olusturur.


Text
y_pozitif_sayilar[y_eleman_sayisi],/////////////////////////////////////////////////////
y_negatif_sayilar[y_eleman_sayisi],/////////////////////////////////////////////////////
x_pozitif_sayilar[x_eleman_sayisi],////////Eksenleri numaranlandiran sayilari olusturur.
x_negatif_sayilar[x_eleman_sayisi];/////////////////////////////////////////////////////

CircleShape //====================================================================================DAIRE
sekil,	//Kalemin cizdigi sekiller icin daire olusturur.
imlecIcon(SIMGE_BOYUTU), //Imlec simgeleri(kalem ve silgi) icin cerceve olusturur.
menu_kalem(MENU_SIMGE_BOYUTU),	//Menudeki kalem simgesi icin cerceve olusturur.
menu_silgi(MENU_SIMGE_BOYUTU),	//Menudeki silgi simgesi icin cerceve olusturur.
menu_tumunu_sil(MENU_SIMGE_BOYUTU),	//Menudeki cop kutusu simgesi icin cerceve olusturur.
menu_kaydet(MENU_SIMGE_BOYUTU)	//Menudeki kaydet simgesi icin cerceve olusturur.
;

RectangleShape	//===================================================================================DORTGEN
x_ekseni,	//x-eksenini olusturur.
y_ekseni,	//y-eksenini olusturur.
menu, //Menu cercevesini olusturur.
menu_ekran(Vector2f(2*MENU_SIMGE_BOYUTU,2*MENU_SIMGE_BOYUTU)); //Ekran boyutunu degistir simgesi icin cerceve olusturur
;

Texture	//==============================================================================================RESIM
kalemSimgesi, //Kalem simgesinin resmi (cerceveye yerlestirilecek resim)
silgiSimgesi, //Silgi simgesinin resmi
tumunuSilSimgesi, //Cop kutusu simgesinin resmi
kaydetSimgesi,	// Kaydet simgesinin resmi
ekranSimgesi	//	Ekran degistirme simgesinin resmi
;

Cursor imlec; //Imleci tanimlar.
Font font;	//Yazilar icin yazi tipi tanimlar
void kaydet();
void degerleri_sekronize_et(){
	kalem_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*25;			//*****************
	kalem_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*23;				//
	silgi_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*22;			//
	silgi_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*20;				//
	cop_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*19;				//
	cop_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*17;					//Simgelerin menudeki baslangic ve bitis konumlari
	kaydet_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*16;			//
	kaydet_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*14;				//
	ekran_degistir_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*13;	//
	ekran_degistir_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*11;		//*****************

	int sayac=0;	//Cizilen seklin hangi yakinlik degerinde cizildigini bulmak icin sayar

	float
	x_koordinati_fark,	//x-ekseni ile fare isaretcisinin farkini verir. Yakinsalip uzaklasmada kalemle cizilen seklin yerini korumasi icin
	y_koordinati_fark,
	ekran_fark_x,	//Ekran boyutu degistirildiginde kalemle cizilen seklin yerini korumasi icin ilk boyutla son boyuttaki x farkini alir
	ekran_fark_y	//Ekran boyutu degistirildiginde kalemle cizilen seklin yerini korumasi icin ilk boyutla son boyuttaki y farkini alir
	;
	if(kucuk_ekran){	//Kucuk ekran secili ise kosul gerceklesir
		ekran_fark_x=(PENCERE_ENI-PENCERE_ENI*5/4)/2;
		ekran_fark_y=(PENCERE_YUKSEKLIGI-PENCERE_YUKSEKLIGI*5/4)/2;
	}else{
		ekran_fark_x=(PENCERE_ENI-PENCERE_ENI*4/5)/2;
		ekran_fark_y=(PENCERE_YUKSEKLIGI-PENCERE_YUKSEKLIGI*4/5)/2;
	}
	for(CircleShape& sirada:kalem){	//Kalem cizgisi icin her bir noktanin koordinatini gunceller

		x_koordinati_fark=(PENCERE_ENI/2-sirada.getPosition().x)*yakinlastirma_katsayisi;
		y_koordinati_fark=(PENCERE_YUKSEKLIGI/2-sirada.getPosition().y)*yakinlastirma_katsayisi;
		sirada.setPosition(PENCERE_ENI/2-x_koordinati_fark/yakinlik[sayac]-fark_x+ekran_fark_x, PENCERE_YUKSEKLIGI/2-y_koordinati_fark/yakinlik[sayac]-fark_y+ekran_fark_y);
		sayac++;
	}
}

void kucuk_boyut_ayarla(int& yatay, int& dikey){	//Bilgisayarin ekran boyutunu okur ve kucultmek icin 4/5 ile carpar
	RECT ekran;
	const HWND masaustu = GetDesktopWindow();
	GetWindowRect(masaustu, &ekran);
	yatay = ekran.right*4/5;
	dikey = ekran.bottom*4/5;
	degerleri_sekronize_et();	//Ekran boyutuna bagli tum degerleri gunceller
}
void buyuk_boyut_ayarla(int& yatay, int& dikey){//Bilgisayarin ekran boyutunu okur
	RECT ekran;
	const HWND masaustu = GetDesktopWindow();
	GetWindowRect(masaustu, &ekran);
	yatay = ekran.right;
	dikey = ekran.bottom;
	degerleri_sekronize_et();//Ekran boyutuna bagli tum degerleri gunceller
}

void fare_etkinlikleri(Event& olayNesnesi)//Fare hareketlerini denetleyen metot
{
	if(olayNesnesi.type==Event::MouseButtonPressed)//Farenin herhangi bir butonuna basilmasini kontrol eder.
	{
		if(olayNesnesi.mouseButton.button==sf::Mouse::Left)sol_kontrol=true;//Farenin sag butonuna basilmasini kontrol eder.
		if(olayNesnesi.mouseButton.button==sf::Mouse::Right)sag_kontrol=true;//Farenin sol butonuna basilmasini kontrol eder.
	}
	if(olayNesnesi.type==Event::MouseButtonReleased)//Farenin basilan butonunun birakilmasini kontrol eder.
	{
		if(olayNesnesi.mouseButton.button==sf::Mouse::Left)sol_kontrol=false;//Farenin sag butonunun birakilmasini kontrol eder.
		if(olayNesnesi.mouseButton.button==sf::Mouse::Right)sag_kontrol=false;//Farenin sol butonunun birakilmasini kontrol eder.
		if(kalem_baslangic<=mouse_x	//Menuden kalem simgesine tiklanirsa bu kosul gerceklesir.
				&& kalem_bitis>=mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50)
			menu_degisken=1; //Kalem secili demek
		if(silgi_baslangic<=mouse_x	//Menuden silgi simgesine tiklanirsa bu kosul gerceklesir.
				&& silgi_bitis>=mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50)
			menu_degisken=2; //Silgi secili demek
		if(cop_baslangic<=mouse_x	//Menuden cop kutusu simgesine tiklanirsa bu kosul gerceklesir.
				&& cop_bitis>=mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50)
		{
			kalem.clear();	//Kalem ile yazilan her seyi siler.
			yakinlik.clear();	//Kalem icin hafizaya alinan yakinlastirma katsayilarini siler
			renk.clear();	//Kalem icin hafizaya alinan renkleri siler
		}
		if(kaydet_baslangic<=mouse_x
				&& kaydet_bitis>=mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50)kaydet();	//Kaydet butonuna basilinca kaydet fonksiyonunu cagirir
		if(ekran_degistir_baslangic<=mouse_x
				&& ekran_degistir_bitis>=mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){//Ekran boyutunu degistire basilinca kosul gerceklesir
			ekran_degisti_mi=true;
			if(kucuk_ekran){
				kucuk_ekran=false;
			}else{
				kucuk_ekran=true;
			}
		}
		if(PENCERE_ENI-2.2*MENU_SIMGE_BOYUTU<mouse_x					/*Kalem icin renk kutucuklarina basilmayi kontrol eder*/
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=0;G=0;B=255;}
		else if(PENCERE_ENI-2.2*MENU_SIMGE_BOYUTU>mouse_x
				&& PENCERE_ENI-4.4*MENU_SIMGE_BOYUTU<mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=0;G=255;B=0;}
		else if(PENCERE_ENI-4.4*MENU_SIMGE_BOYUTU>mouse_x
				&& PENCERE_ENI-6.6*MENU_SIMGE_BOYUTU<mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=255;G=0;B=0;}
		else if(PENCERE_ENI-6.6*MENU_SIMGE_BOYUTU>mouse_x
				&& PENCERE_ENI-8.8*MENU_SIMGE_BOYUTU<mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=255;G=255;B=255;}
	}
	if(olayNesnesi.type == Event::MouseWheelMoved){	//Farenin tekerlek hareketlerini kontrol eden if komutlari.
		if(olayNesnesi.mouseWheel.delta>0 && yakinlastirma_katsayisi <250){
			yakinlastirma_katsayisi+=10;
			eksen_kalinligi+=0.2;
		}else if(olayNesnesi.mouseWheel.delta<0 && yakinlastirma_katsayisi>29){
			yakinlastirma_katsayisi-=10;
			if(eksen_kalinligi>0.3)eksen_kalinligi-=0.2;
		}//else if komutunun bitimi
	}//Fare tekerlek kontrol if komutunun bitimi

	if(olayNesnesi.type==sf::Event::MouseMoved)//Farenin hangi yone ne kadar hareket ettirildigini denetler.
	{
		mouse_x=olayNesnesi.mouseMove.x;//Farenin x-koordinatini verir.
		mouse_y=olayNesnesi.mouseMove.y;//Farenin y-koordinatini verir.
	}
}

void klavye_etkinlikleri(Event& olayNesnesi, RenderWindow& pencere)//Klavye etkinliklerini denetleyen metot
{
	if(olayNesnesi.type == Event::Closed)pencere.close(); //Pencerenin ust menuden kapanmasini saglar.
	if(olayNesnesi.type==Event::KeyPressed) //Klavye tusuna basilmasiyla bu kosul gerceklesir.
	{
		if(olayNesnesi.key.code==Keyboard::Up)fark_y-=50;				/*Ekran kaydirma islevlerini yapar*/
		if(olayNesnesi.key.code==Keyboard::Down)fark_y+=50;
		if(olayNesnesi.key.code==Keyboard::Left)fark_x-=50;
		if(olayNesnesi.key.code==Keyboard::Right)fark_x+=50;
		if(olayNesnesi.key.code==Keyboard::Delete)	//Tumunu sil butonu ile ayni islevi gorur
		{
			kalem.clear();	////////////////////
			yakinlik.clear();//Kalem egrisi bilgilerini siler
			renk.clear();	///////////////////
		}
		if(olayNesnesi.key.code==Keyboard::K && yakinlastirma_katsayisi <250 )yakinlastirma_katsayisi+=10;	//'y' karakterine basinca yakinlastirir
		if(olayNesnesi.key.code==Keyboard::L && yakinlastirma_katsayisi>29)yakinlastirma_katsayisi-=10;		//'u' karakterine basinca yakinlastirir
		if(olayNesnesi.key.code==Keyboard::J){fark_x=0;fark_y=0;yakinlastirma_katsayisi=50;eksen_kalinligi=2;}	// Bosluk tusuna basinca odaklar.
		if(olayNesnesi.key.code==Keyboard::Escape)pencere.close();	//Esc tusuna basinca programi kapatir
		if(olayNesnesi.key.code==Keyboard::Enter){	//Enter tusuna basinca kullanicinin girdigi denklemi okur
			sonuclar_fx.clear();	//Onceki denklemden kalma degerler var ise siler
			sonuclar_fy.clear();
			sonuclar_gx.clear();
			sonuclar_gy.clear();
			fx_kontrol=false;
			fy_kontrol=false;
			gx_kontrol=false;
			gy_kontrol=false;
			islemeye_basla(); //Alinan denklemin her noktada degerini hesaplar
			denklem_kontrol=true;	//Kullanicinin denklem girdigini belirtir
		}
	}
} //klavye_etkinlikleri fonksiyonu bitisi

//long long int fact(unsigned int); //Faktoriyel islemlerini yapar

void grafikCiz(RenderWindow &pencere){
	int eski_x_koordinati=0, eski_y_koordinati=0;
	float
	x_koordinati=0,	//Denklemde kullanilan noktanin x eksenindeki degerini belirler.
	y_koordinati=0; //Denklemde kullanilan noktanin y eksenindeki degerini belirler.
	if(denklem_kontrol){
		double sayac=x_bit;

		int boyut,
		i=0;

		if(fx_kontrol){
			boyut = sonuclar_fx.size();
		}else if(fy_kontrol){
			boyut = sonuclar_fy.size();
		}else if(gx_kontrol){
			boyut = sonuclar_gx.size();
		}else if(gy_kontrol){
			boyut = sonuclar_gy.size();
		}

		while(i<boyut){
			if(fx_kontrol){
				y_koordinati=sonuclar_fx[i];
			}else{
				y_koordinati=sayac;
			}
			if(fy_kontrol){
				x_koordinati=sonuclar_fy[i];
			}else{
				x_koordinati=sayac;		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
			}

			if((eski_x_koordinati!=0 &&	eski_y_koordinati!=0) && eski_y_koordinati!=214748 && eski_y_koordinati!=-214748)
			{
				Vertex cizikler[] = //Grafik burada olusturulan cizgiler ile olusturulur.
				{
						Vertex(Vector2f(eski_x_koordinati,eski_y_koordinati)),//Denenen iki parametre degerinden ilki
						Vertex(Vector2f(PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x,PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y))//Denenen iki parametre degerinden ikincileri
				};
				pencere.draw(cizikler, 2, Lines); //Grafik ekranda gosterilir.
			}
			eski_x_koordinati=PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x; //Denenen iki parametre degerinin ilk x sonucunu hafizada tutar
			eski_y_koordinati=PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y; //Denenen iki parametre degerinin ilk y sonucunu hafizada tutar
			sayac-=0.008;
			i++;
		}
	}/*else{                        //Program denklem okuyamadiginda denklemi buradan girebilirsiniz
	float 	t=50+fark_x/yakinlastirma_katsayisi;			//Denklem parametresi
		while(t>=-50+fark_x/yakinlastirma_katsayisi)//Grafigi olusturan noktalarin x degerinin verildigi dongu
		{
			x_koordinati=t;		//Noktanin x degeri belirlenir./////////////////////////////////////////////////////////////////////
			y_koordinati=t;		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
			if((eski_x_koordinati!=0 &&	eski_y_koordinati!=0))
			{
				Vertex cizikler[] = //Grafik burada olusturulan cizgiler ile olusturulur.
				{
						Vertex(Vector2f(eski_x_koordinati,eski_y_koordinati)),//Denenen iki parametre degerinden ilki
						Vertex(Vector2f(PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x,PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y))//Denenen iki parametre degerinden ikincileri
				};
				pencere.draw(cizikler, 2, Lines); //Grafik ekranda gosterilir.
			}
			eski_x_koordinati=PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x; //Denenen iki parametre degerinin ilk x sonucunu hafizada tutar
			eski_y_koordinati=PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y; //Denenen iki parametre degerinin ilk y sonucunu hafizada tutar
			t-=grafik_basitligi; //Parametrenin degeri azaltilir.
		} // Grafik ciziminin bitimi
	}*/

}

void grafikCiz2(RenderWindow &pencere){
	int eski_x_koordinati=0, eski_y_koordinati=0;
	float
	x_koordinati=0,	//Denklemde kullanilan noktanin x eksenindeki degerini belirler.
	y_koordinati=0; //Denklemde kullanilan noktanin y eksenindeki degerini belirler.
	//Denkelem grafigin egrisi asagidaki for dongusunde cizilir.
	if(denklem_kontrol){
		double sayac=x_bit;
		int boyut = sonuclar_gx.size(),
				i=0;
		while(i<boyut){
			if(gx_kontrol){
				y_koordinati=sonuclar_gx[i];
			}else{
				y_koordinati=sayac;
			}
			if(gy_kontrol){
				x_koordinati=sonuclar_gy[i];
			}else{
				x_koordinati=sayac;		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
			}

			if((eski_x_koordinati!=0 &&	eski_y_koordinati!=0) && eski_y_koordinati!=214748 && eski_y_koordinati!=-214748)
			{
				Vertex cizikler[] = //Grafik burada olusturulan cizgiler ile olusturulur.
				{
						Vertex(Vector2f(eski_x_koordinati,eski_y_koordinati)),//Denenen iki parametre degerinden ilki
						Vertex(Vector2f(PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x,PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y))//Denenen iki parametre degerinden ikincileri
				};
				pencere.draw(cizikler, 2, Lines); //Grafik ekranda gosterilir.
			}
			eski_x_koordinati=PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x; //Denenen iki parametre degerinin ilk x sonucunu hafizada tutar
			eski_y_koordinati=PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y; //Denenen iki parametre degerinin ilk y sonucunu hafizada tutar
			sayac-=0.008;
			i++;
		}
	}/*else{			//Program denklem okuyamadiginda denklemi buradan girebilirsiniz
	float 	t=50+fark_x/yakinlastirma_katsayisi;			//Denklem parametresi
		while(t>=-50+fark_x/yakinlastirma_katsayisi)//Grafigi olusturan noktalarin x degerinin verildigi dongu
		{
			x_koordinati=t*t;		//Noktanin x degeri belirlenir./////////////////////////////////////////////////////////////////////
			y_koordinati=t;		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
			if((eski_x_koordinati!=0 &&	eski_y_koordinati!=0))
			{
				Vertex cizikler[] = //Grafik burada olusturulan cizgiler ile olusturulur.
				{
						Vertex(Vector2f(eski_x_koordinati,eski_y_koordinati)),//Denenen iki parametre degerinden ilki
						Vertex(Vector2f(PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x,PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y))//Denenen iki parametre degerinden ikincileri
				};
				pencere.draw(cizikler, 2, Lines); //Grafik ekranda gosterilir.
			}
			eski_x_koordinati=PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x; //Denenen iki parametre degerinin ilk x sonucunu hafizada tutar
			eski_y_koordinati=PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y; //Denenen iki parametre degerinin ilk y sonucunu hafizada tutar
			t-=grafik_basitligi; //Parametrenin degeri azaltilir.
		} // Grafik ciziminin bitimi
	}*/
}

/*long long int fact(unsigned int tam_sayi){//Faktoriyel kullanabilme fonksiyonu
	long long int carpim=1;
	for(int i=tam_sayi; i>0; i--){
		carpim*=i;
	}
	return carpim;
}*/

void eksenleriYerlestir(RenderWindow &pencere){
	x_ekseni.setSize(Vector2f(PENCERE_ENI*2.1,eksen_kalinligi));		//Eksenlerin boyutlarini tanimlar.
	y_ekseni.setSize(Vector2f(eksen_kalinligi,PENCERE_YUKSEKLIGI*3.1));
	x_ekseni.setPosition(0,PENCERE_YUKSEKLIGI/2-fark_y);
	y_ekseni.setPosition(PENCERE_ENI/2-fark_x,0); //Eksenlerin konumlarini belirler
	pencere.draw(x_ekseni);pencere.draw(y_ekseni);//Eksenler ekranda gosterilir.
}

void eksenSayilariniOlustur(){
	if(!font.loadFromFile("calibril.ttf")){/*Yazinin olusabilmesi icin bu kosul gerekli*/};
	for(int i=1;i<y_eleman_sayisi;i++){//y-ekseni sayilarini tanimlar.
		y_pozitif_sayilar[i].setFont(font);y_negatif_sayilar[i].setFont(font);
		y_pozitif_sayilar[i].setString(std::to_string(i));
		y_negatif_sayilar[i].setString(std::to_string(-i));
	}//y-eksen sayilari bitimi
	for(int i=1;i<x_eleman_sayisi;i++){// x-ekseni sayilarini tanimlar.
		x_pozitif_sayilar[i].setFont(font);x_negatif_sayilar[i].setFont(font);
		x_pozitif_sayilar[i].setString(std::to_string(i));
		x_negatif_sayilar[i].setString(std::to_string(-i));
	}//x-eksen sayilari bit
}

void eksenSayilariniYerlestir(RenderWindow &pencere){
	for(int arr=1;arr<y_eleman_sayisi;arr++)//y_eksenine sayilari yerlestirir.
	{
		y_pozitif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
		if((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x < 15){
			y_pozitif_sayilar[arr].setPosition(15,PENCERE_YUKSEKLIGI/2-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
		}else if((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x > PENCERE_ENI-25){
			y_pozitif_sayilar[arr].setPosition(PENCERE_ENI-0.25*float(yakinlastirma_katsayisi)-10,PENCERE_YUKSEKLIGI/2-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
		}else{
			y_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x,PENCERE_YUKSEKLIGI/2-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
		}
		pencere.draw(y_pozitif_sayilar[arr]);
		y_negatif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
		if((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x < 15){
			y_negatif_sayilar[arr].setPosition(15 ,PENCERE_YUKSEKLIGI/2+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
		}else if((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x > PENCERE_ENI-25){
			y_negatif_sayilar[arr].setPosition(PENCERE_ENI-0.25*float(yakinlastirma_katsayisi)-10,PENCERE_YUKSEKLIGI/2+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
		}else{
			y_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x,PENCERE_YUKSEKLIGI/2+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
		}
		pencere.draw(y_negatif_sayilar[arr]);
	}//y-eksenine sayi yerlestirme bitimi

	for(int arr=1;arr<x_eleman_sayisi;arr++)//x_eksenine sayilari yerlestirir.
	{
		x_pozitif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
		if(PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y < 65){
			x_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/25-fark_x, 65);
		}else if(PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y > PENCERE_YUKSEKLIGI-20){
			if(kucuk_ekran){
				x_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/25-fark_x,PENCERE_YUKSEKLIGI-0.25*float(yakinlastirma_katsayisi)-10);
			}else{
				x_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/25-fark_x,PENCERE_YUKSEKLIGI-0.25*float(yakinlastirma_katsayisi)-40);
			}
		}else{
			x_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/25-fark_x,PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y);
		}
		pencere.draw(x_pozitif_sayilar[arr]);

		x_negatif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
		if(PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y < 65){
			x_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/10-fark_x,65);
		}else if(PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y > PENCERE_YUKSEKLIGI-20){
			if(kucuk_ekran){
				x_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/10-fark_x,PENCERE_YUKSEKLIGI-0.25*float(yakinlastirma_katsayisi)-10);
			}else{
				x_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/10-fark_x,PENCERE_YUKSEKLIGI-0.25*float(yakinlastirma_katsayisi)-40);
			}
		}else{
			x_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/10-fark_x,PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y);
		}
		pencere.draw(x_negatif_sayilar[arr]);
	}//x-eksenine sayi yerlestirme bitimi
}

void ekraniKaydir(){
	float
	ekran_siniri_x = PENCERE_ENI*4/5*yakinlastirma_katsayisi/24, //Ekranin x-ekseninde en fazla kaydirilabilecegi degeri hesaplar.
	ekran_siniri_y = PENCERE_YUKSEKLIGI*4/5*yakinlastirma_katsayisi/24; //Ekranin y-ekseninde en fazla kaydirilabilecegi degeri hesaplar.

	if(!sag_kontrol) //Tasima butonuna (fare sol) basilmadan onceki imlec konumunu hafizaya alir.
	{
		mouse_eski_x=mouse_x+fark_x;
		mouse_eski_y=mouse_y+fark_y;
	}
	if(sag_kontrol && fark_x>=-ekran_siniri_x //Ekran kaydirma ve kaydirmayi sinirlama
			&& fark_x<=ekran_siniri_x
			&& fark_y>=-ekran_siniri_y
			&& fark_y<=ekran_siniri_y)
	{
		fark_x=mouse_eski_x-mouse_x; //Ekranin x-ekseninde ne kadar kaydirilicagini hesaplar.
		fark_y=mouse_eski_y-mouse_y; //Ekranin y-ekseninde ne kadar kaydirilicagini hesaplar.
	}
	if(fark_x<-ekran_siniri_x) //Ekran kaydirmada sinirlari asilirsa sinirlar bu else if dongusunde duzeltilir
	{
		fark_x=-ekran_siniri_x+1;
	}else if( fark_x>ekran_siniri_x)
	{
		fark_x=ekran_siniri_x-1;
	}
	if(fark_y<-ekran_siniri_y)
	{
		fark_y=-ekran_siniri_y+1;
	}else if( fark_y>ekran_siniri_y)
	{
		fark_y=ekran_siniri_y-1;
	}
}

void menuOlustur(){
	menu_kalem.setPosition(kalem_baslangic,10);
	menu_silgi.setPosition(silgi_baslangic,10);
	menu_tumunu_sil.setPosition(cop_baslangic,10);
	menu_kaydet.setPosition(kaydet_baslangic,10);
	menu_ekran.setPosition(ekran_degistir_baslangic,10);
	menu.setSize(Vector2f(PENCERE_ENI-6,50));
	menu.setOutlineThickness(2.5); //Menu cercevesinin dis cizgi kalinligini belirler.
	menu.setFillColor(Color(30,30,30));
	menu.setOutlineColor(Color::White);//Menu cercevesinin dis cizgi rengini belirler.
	menu.setPosition(3,3);

}

void menuyuYerlestir(RenderWindow &pencere){
	pencere.draw(menu);
	pencere.draw(menu_kalem);
	pencere.draw(menu_silgi);
	pencere.draw(menu_tumunu_sil);
	pencere.draw(menu_kaydet);
	pencere.draw(menu_ekran);
}
void gorselleriOlustur(){
	if(kalemSimgesi.loadFromFile("kalem.png"));	//Kalem resmi iceri aktarir.
	if(silgiSimgesi.loadFromFile("silgi.png"));
	if(tumunuSilSimgesi.loadFromFile("tumunuSil.png"));
	if(kaydetSimgesi.loadFromFile("kaydet.png"));
	if(ekranSimgesi.loadFromFile("bigscreen.png"));

	menu_kalem.setTexture(&kalemSimgesi); //Iceriye aktarilan resmi cerceveye yerlestirir.
	menu_silgi.setTexture(&silgiSimgesi);
	menu_tumunu_sil.setTexture(&tumunuSilSimgesi);
	menu_kaydet.setTexture(&kaydetSimgesi);
	menu_ekran.setTexture(&ekranSimgesi);
}

void renkKutucuklari(RenderWindow &pencere){
	RectangleShape menu_renk_secimi(Vector2f(MENU_SIMGE_BOYUTU*1.5,MENU_SIMGE_BOYUTU*1.5));
	menu_renk_secimi.setOutlineThickness(3);
	menu_renk_secimi.setOutlineColor(Color(240,240,240));
	menu_renk_secimi.setFillColor(Color(0,0,255));
	menu_renk_secimi.setPosition(PENCERE_ENI-2.2*MENU_SIMGE_BOYUTU, 15);
	pencere.draw(menu_renk_secimi);
	menu_renk_secimi.setFillColor(Color(0,255,0));
	menu_renk_secimi.setPosition(PENCERE_ENI-4.4*MENU_SIMGE_BOYUTU, 15);
	pencere.draw(menu_renk_secimi);
	menu_renk_secimi.setFillColor(Color(255,0,0));
	menu_renk_secimi.setPosition(PENCERE_ENI-6.6*MENU_SIMGE_BOYUTU, 15);
	pencere.draw(menu_renk_secimi);
	menu_renk_secimi.setFillColor(Color(255,255,255));
	menu_renk_secimi.setPosition(PENCERE_ENI-8.8*MENU_SIMGE_BOYUTU, 15);
	pencere.draw(menu_renk_secimi);
}

void kaydiAc(){///////////////////////////////////////////////////////////////////////////////////
	std::string satir;
	std::ifstream dosyaOku;

	dosyaOku.open("kayit.txt");

	if(dosyaOku){
		std::vector<float>konumx;
		std::vector<float>konumy;
		bool konumKontrolx=false,
				konumKontroly=false,
				yakinlikKontrol=false,
				renkKontrol=false;
		while(getline(dosyaOku, satir)){
			if(satir=="noktax"){
				konumKontrolx=true;
				konumKontroly=false;
				yakinlikKontrol=false;
				renkKontrol=false;
				continue;
			}
			if(satir=="noktay"){
				konumKontrolx=false;
				konumKontroly=true;
				yakinlikKontrol=false;
				renkKontrol=false;
				continue;
			}
			if(satir=="yakinlik"){
				konumKontrolx=false;
				konumKontroly=false;
				yakinlikKontrol=true;
				renkKontrol=false;
				continue;
			}
			if(satir=="renk"){
				konumKontrolx=false;
				konumKontroly=false;
				yakinlikKontrol=false;
				renkKontrol=true;
				continue;
			}
			if(konumKontrolx){
				konumx.push_back(std::stoi(satir));
			}
			if(konumKontroly){
				konumy.push_back(std::stoi(satir));
			}
			if(yakinlikKontrol){
				yakinlik.push_back(std::stoi(satir));
			}
			if(renkKontrol){
				renk.push_back(std::stoi(satir));
			}
		}
		int uzunluk = konumx.size();
		for(int i=0; i<uzunluk; i++){
			sekil.setPosition(konumx[i], konumy[i]);//Cizilecek konumu belirler.
			if(renk[i]==0){
				sekil.setFillColor(Color::White);
			}
			if(renk[i]==1){
				sekil.setFillColor(Color::Red);
			}
			if(renk[i]==2){
				sekil.setFillColor(Color::Green);
			}
			if(renk[i]==3){
				sekil.setFillColor(Color::Blue);
			}
			if(renk[i]==4){
				sekil.setFillColor(Color::Transparent);
			}
			kalem.push_back(sekil);
		}
	}
	dosyaOku.close();
}

void kaydet(){///////////////////////////////////////////////////////////////////////////////////
	std::ofstream dosyaYazma;

	dosyaYazma.open("kayit.txt");

	dosyaYazma << "noktax\n";
	float ekran_fark_x=(PENCERE_ENI*4/5-PENCERE_ENI)/2;
	float ekran_fark_y=(PENCERE_YUKSEKLIGI*4/5-PENCERE_YUKSEKLIGI)/2;
	for(CircleShape siradaki:kalem){
		if(kucuk_ekran == false){
			dosyaYazma << siradaki.getPosition().x + ekran_fark_x << "\n";
		}else{
			dosyaYazma << siradaki.getPosition().x << "\n";
		}
	}
	dosyaYazma << "noktay\n";
	for(CircleShape siradaki:kalem){
		if(kucuk_ekran == false){
			dosyaYazma << siradaki.getPosition().y + ekran_fark_y << "\n";
		}else{
			dosyaYazma << siradaki.getPosition().y << "\n";
		}
	}
	dosyaYazma << "yakinlik\n";
	for(int siradaki:yakinlik){
		dosyaYazma << siradaki << "\n";
	}
	dosyaYazma << "renk\n";
	for(int siradaki:renk){
		dosyaYazma << siradaki << "\n";
	}
	dosyaYazma.close();
}

void kalemSilgiKullan(RenderWindow &pencere){
	float x_koordinati_fark,	//x-ekseni ile fare isaretcisinin farkini verir. Yakinsalip uzaklasmada kalemle cizilen seklin yerini korumasi icin
	y_koordinati_fark;	//y-ekseni ile fare isaretcisinin farkini verir. Yakinsalip uzaklasmada kalemle cizilen seklin yerini korumasi icin

	if(sol_kontrol && menu_degisken==1 )//Kalem ile sekil cizme burada gerceklesir.
	{
		if(mouse_y > 50){ //Kullanici menu secimi yaparken kalem sekil cizmez.
			sekil.setPosition(mouse_x+fark_x,mouse_y+fark_y);//Cizilecek konumu belirler.
			kalem.push_back(sekil);//Cizimi hafizaya alir.
			yakinlik.push_back(yakinlastirma_katsayisi);
			if(R==255 && G==0 && B==0){
				renk.push_back(1);
			}else if(R==0 && G==255 && B==0){
				renk.push_back(2);
			}else if(R==0 && G==0 && B==255){
				renk.push_back(3);
			}else{
				renk.push_back(0);
			}
		}
	}
	int silginin_altindaki_noktalar =0, //Silgi kullanilirken silginin hangi noktalari silecegi bu int ile belirlenir.
			sayac=0
			;
	for(CircleShape siradaki : kalem)//Cizilen sekli ekranda tutar.
	{
		x_koordinati_fark=(PENCERE_ENI/2-siradaki.getPosition().x)*yakinlastirma_katsayisi;
		y_koordinati_fark=(PENCERE_YUKSEKLIGI/2-siradaki.getPosition().y)*yakinlastirma_katsayisi;

		siradaki.setRadius(kalem_kalinligi+(float(yakinlastirma_katsayisi)/60));//Cizilen seklin kalinligini belirler.
		siradaki.setPosition(PENCERE_ENI/2-x_koordinati_fark/yakinlik[sayac]-fark_x, PENCERE_YUKSEKLIGI/2-y_koordinati_fark/yakinlik[sayac]-fark_y);
		sayac++;
		pencere.draw(siradaki);
		if(mouse_x-7<=siradaki.getPosition().x 	//Silgi kosulu
				&& siradaki.getPosition().x<=mouse_x+10
				&& mouse_y-10<=siradaki.getPosition().y
				&& siradaki.getPosition().y<=mouse_y+7
				&& sol_kontrol
				&& menu_degisken==2){
			kalem[silginin_altindaki_noktalar].setFillColor(Color::Transparent);
			renk[silginin_altindaki_noktalar]=4;
		}
		silginin_altindaki_noktalar++;
	}
}

void kalemRengi(){
	sekil.setFillColor(Color(R,G,B));//Kalem renginin ayarlar.
}

void imleciDegistir(RenderWindow &pencere, CircleShape &imlecIcon){
	if(sag_kontrol){  //Kullanici ekran kaydirirken + isaretini cikartan kosul
		pencere.setMouseCursorVisible(true);
		if(mouse_y>50)
			if (imlec.loadFromSystem(Cursor::SizeAll)); // Imleci + yapar.
	}else{
		if (imlec.loadFromSystem(Cursor::Arrow));
		pencere.setMouseCursorVisible(false);
		if(mouse_y<=50)pencere.setMouseCursorVisible(true);
		imlecIcon.setPosition(mouse_x,mouse_y-30);
		pencere.draw(imlecIcon);
	}
	pencere.setMouseCursor(imlec);
}


#endif /* ARACLAR_HPP_ */
