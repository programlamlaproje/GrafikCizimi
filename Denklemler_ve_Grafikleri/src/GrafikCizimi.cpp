#include "araclar.hpp"

using namespace sf;

void denklemler_ve_grafikleri(){

	ContextSettings settings;settings.antialiasingLevel=8; //Grafigin pruzlerini siler
	RenderWindow pencere(VideoMode(PENCERE_ENI, PENCERE_YUKSEKLIGI,32), "Grafik Cizimi",Style::Close,settings); //Pencereyi olusturur ve tanimlar.
	Event olayNesnesi; //Kullanicin komutlarini kontrol eden obje
	denklemMenuOlustur();
	gorselleriOlustur(); //Kalem silgi ve cop kutusu gorsellerini ekler.
	menuOlustur(); //Ust menuyu olusturur ve duzenler.
	eksenSayilariniOlustur(); // x ve y eksenlerindeki sayilar icin sayi dizisi olusturur.

	if(ekran_degisti_mi){	//Ekranin degistini belirtmek icin ve kayitin ilk acilista cizilmesini saglar
		ekran_degisti_mi=false;	//Ekran boyutunun degismesinin sonsuz donguye girmesini engeller
	}else{
		kaydiAc();	//Kaydedilen cizimi acar
	}
	while(pencere.isOpen()){	//Pencerenin acilmasini ve ekran grafiklerinin olusmasini saglayan dongu

		pencere.clear(); //Dongu basa dondugunde ekrandaki grafikleri temizler.

		while(pencere.pollEvent(olayNesnesi)){ //Kullanici komutlari dongusu

			klavye_etkinlikleri(olayNesnesi, pencere); //Klavyenin hareketlerini kontrol eder.
			fare_etkinlikleri(olayNesnesi);	//Farenin hareketlerini kontrol eder.
			denklem_oku(olayNesnesi); //Kullanicidan denklem alamayan fonksiyon.

		}//Kullanici komutlari dongusu bitimi

		if(ekran_degisti_mi){	//Ekran degistirdiginde boyutlari ayarlar
			if(kucuk_ekran){
				kucuk_boyut_ayarla(PENCERE_ENI, PENCERE_YUKSEKLIGI);
				pencere.setSize(Vector2u(PENCERE_ENI, PENCERE_YUKSEKLIGI));
			}else{
				buyuk_boyut_ayarla(PENCERE_ENI, PENCERE_YUKSEKLIGI);
				pencere.setPosition(Vector2i(0,0));
				pencere.setSize(Vector2u(PENCERE_ENI, PENCERE_YUKSEKLIGI));
			}
			pencere.close();	//Pencereyi kapatir
			denklemler_ve_grafikleri();  //Pencereyi acar Fonkssiyon Yenileme
		}

		if(menu_degisken==1)	//Kalem secili ise kosul gerceklesir
		{
			imlecIcon.setTexture(&kalemSimgesi); //Imleci kalem formunda gosterir.
		}else{
			imlecIcon.setTexture(&silgiSimgesi); //Imleci silgi formunda gosterir.
		}
		ekraniKaydir(); //Fare sag tusu ile ekranin kaydirilmasini saglar.
		eksenleriYerlestir(pencere); // x ve y eksenlerinin konum ve kalinlik bilgilerini duzenler ve ekranda gosterir.
		eksenSayilariniYerlestir(pencere); //Eksenlerdeki sayilarin buyuklerini ve konumlarini duzenler. Ekranda gosterir.
		grafikCiz(pencere); //Grafik egrisini olusturur ve ekranda gosterir.
		grafikCiz2(pencere);
		kalemRengi(); //Menuden renk degistirilmesi ile kalem rengini degistirir.
		kalemSilgiKullan(pencere); // Kalem ve silgi araclarini olusturur.
		imleciDegistir(pencere, imlecIcon); //Imleci kalem veya silgi seklinde gosterir.
		menuyuYerlestir(pencere); //Olusturulan menuyu gosterir.
		denklemiMenuyeYerlestir(pencere);
		renkKutucuklari(pencere); //Kalem rengi seceneklerini olusturur ve menuye ekler.

		pencere.display(); //Menuye eklenen grafiklerin gosterilmesini saglar.
	}
}

int main() {
	kucuk_boyut_ayarla(PENCERE_ENI, PENCERE_YUKSEKLIGI);	//Pencereyi ilk acilis icin boyut degerlerini atar
	denklemler_ve_grafikleri();	//Programi baslatir
	return 0;
}

//En sevdigim grafik y=(1/x*x)+(x*x/sqrt(cos(x)+x))
/*
 * log(sqrt(x*x+1))-sin(pow(x*x+1,cos(x)))
 *
 * nokta.setX(3*cos(x)/(1/x*x)+(x*x/sqrt(cos(x)+x)));
				nokta.setY(3*sin(x));
				x_koordinati=sin(t)*cos(t)*log(abs(t));		//Noktanin x degeri belirlenir./////////////////////////////////////////////////////////////////////
			y_koordinati=sqrt(abs(t))*cos(t);		//Noktanin y degeri belirlenir.//////////////////////////////////////////////////////////////
 *////
