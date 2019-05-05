
#include "araclar.hpp"

using namespace sf;

int main() {
	ContextSettings settings;settings.antialiasingLevel=8; //Grafigin pruzlerini siler
	RenderWindow pencere(VideoMode(PENCERE_ENI, PENCERE_YUKSEKLIGI), "Grafik Cizimi",Style::Close,settings); //Pencereyi olusturur ve tanimlar.
	Event olayNesnesi; //Kullanicin komutlarini kontrol eden obje

	denklemMenuOlustur();
	gorselleriOlustur(); //Kalem silgi ve cop kutusu gorsellerini ekler.
	menuOlustur(); //Ust menuyu olusturur ve duzenler.
	eksenSayilariniOlustur(); // x ve y eksenlerindeki sayilar icin sayi dizisi olusturur.

	while(pencere.isOpen()){	//Pencerenin acilmasini ve ekran grafiklerinin olusmasini saglayan dongu

		pencere.clear(); //Dongu basa dondugunde ekrandaki grafikleri temizler.

		while(pencere.pollEvent(olayNesnesi)){ //Kullanici komutlari dongusu

			klavye_etkinlikleri(olayNesnesi, pencere); //Klavyenin hareketlerini kontrol eder.
			fare_etkinlikleri(olayNesnesi);	//Farenin hareketlerini kontrol eder.
			denklem_oku(olayNesnesi); //Kullanicidan denklem alamayan fonksiyon.

		}//Kullanici komutlari dongusu bitimi

		if(menu_degisken==1)
		{
			imlecIcon.setTexture(&kalemSimgesi); //Imleci kalem formunda gosterir.
		}else{
			imlecIcon.setTexture(&silgiSimgesi); //Imleci silgi formunda gosterir.
		}
		ekraniKaydir(); //Fare sag tusu ile ekranin kaydirilmasini saglar.
		eksenleriYerlestir(pencere); // x ve y eksenlerinin konum ve kalinlik bilgilerini duzenler ve ekranda gosterir.
		eksenSayilariniYerlestir(pencere); //Eksenlerdeki sayilarin buyuklerini ve konumlarini duzenler. Ekranda gosterir.
		grafikCiz(pencere); //Grafik egrisini olusturur ve ekranda gosterir.
//		grafikCiz2(pencere);
		kalemRengi(); //Menuden renk degistirilmesi ile kalem rengini degistirir.
		kalemSilgiKullan(pencere); // Kalem ve silgi araclarini olusturur.
		imleciDegistir(pencere, imlecIcon); //Imleci kalem veya silgi seklinde gosterir.
		menuyuYerlestir(pencere); //Olusturulan menuyu gosterir.
		denklemiMenuyeYerlestir(pencere);
		renkKutucuklari(pencere); //Kalem rengi seceneklerini olusturur ve menuye ekler.

		pencere.display(); //Menuye eklenen grafiklerin gosterilmesini saglar.
	}
	return 0;
}

//En sevdigim grafik y=(1/t*t)+(t*t/sqrt(cos(t)+t))
/*
 * log(sqrt(x*x+1))-sin(pow(x*x+1,cos(x)))
 *
 * nokta.setX(3*cos(x)/(1/x*x)+(x*x/sqrt(cos(x)+x)));
				nokta.setY(3*sin(x));


				x_koordinati=sin(t)*cos(t)*log(abs(t));		//Noktanin x degeri belirlenir./////////////////////////////////////////////////////////////////////
			y_koordinati=sqrt(abs(t))*cos(t);		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
 */

/*
 *
 * Vertex lines[] =
		{
				Vertex(Vector2f(mouse_x+10,mouse_y-10)),
				Vertex(Vector2f(mouse_x,mouse_y),Color::Green)
		};
		pencere.draw(lines, 2, Lines);
 */

