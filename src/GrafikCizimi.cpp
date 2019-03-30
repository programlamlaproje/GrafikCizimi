
#include<SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Nokta.h"

using namespace sf;
using std::cout;
using std::endl;

int main() {

	static const int PENCERE_ENI=1080,	//Acilan pencerenin enini belirler.
			PENCERE_YUKSEKLIGI=720;	//Acilan pencerenin boyunu belirler.

	int eleman_sayisi=80,	//Dizilerdeki eeleman sayisini belirler.
			x_koordinati=0,	//Denklemde kullanilan noktanin x eksenindeki degerini belirler.
			y_koordinati=0, //Denklemde kullanilan noktanin y eksenindeki degerini belirler.
			nokta_capi=2,	//Grafigik egrisinin kalinligini belirler.
			yakinlastirma_katsayisi=50; //Grafigin yakinlik ve uzaklik degerini belirler.
	double grafik_basitligi=0.01,	//Grafigin goruntusunu iyilestirir. Dusuk degerde program yavas calisir.
			eksen_kalinligi=2;	//x ve y eksenlerinin kalinliklarini belirler.

	RenderWindow pencere(VideoMode(PENCERE_ENI, PENCERE_YUKSEKLIGI), "Grafik Cizimi"); //Pencereyi olusturur ve tanimlar.
	Nokta nokta(x_koordinati,y_koordinati);	//Denklemin belirittigi her bir noktayi olusturur.
	CircleShape daire[eleman_sayisi]; //Grafik egrisini olusturan herbir nokta dizisini olusturur.
	RectangleShape x_ekseni;	//Eksenleri olusturur.
	RectangleShape y_ekseni;

	for(int i=0;i<80;i++){ //Egriyi olusturan herbir noktayi tanimlar.
		daire[i].setRadius(nokta_capi);
		daire[i].setFillColor(Color(255,255,255));
	}
	x_ekseni.setFillColor(Color::White);
	x_ekseni.setPosition(0,PENCERE_YUKSEKLIGI/2);
	y_ekseni.setFillColor(Color::White);
	y_ekseni.setPosition(PENCERE_ENI/2,0);

	while(pencere.isOpen()){	//Pencerenin acilmasini ve ekran grafiklerinin olusmasini saglayan dongu
		pencere.display();
		Event olayNesnesi; //Kullanicin kommutlarini kontrol eden obje
		pencere.clear();
		while(pencere.pollEvent(olayNesnesi)){
			if(olayNesnesi.type == Event::Closed)pencere.close(); //Pencerenin ust menuden kapanmasini saglar.
			if(olayNesnesi.type == Event::MouseWheelMoved){	//Yakinlasmayi ve uzaklasmayi kontrol eden if komutlari.
				if(olayNesnesi.mouseWheel.delta>0 && yakinlastirma_katsayisi <250){
					yakinlastirma_katsayisi+=20;
					eksen_kalinligi+=0.15;
					break;
				}else if(olayNesnesi.mouseWheel.delta<0 && yakinlastirma_katsayisi>25){
					yakinlastirma_katsayisi-=20;
					eksen_kalinligi-=0.15;
					break;
				}
			}
		}
		x_ekseni.setSize(Vector2f(PENCERE_ENI,eksen_kalinligi));		//Eksenleri tanimlar.
		y_ekseni.setSize(Vector2f(eksen_kalinligi,PENCERE_YUKSEKLIGI));
		for(double i=15; i>=-15; i-=grafik_basitligi){	//Denkelem grafigin egrisi burada cizilir.
			for(int arr=0;arr<80;arr++){
				pencere.draw(daire[arr]);
				nokta.setX(i);
				nokta.setY((1/i*i)+(i*i/sqrt(cos(i)+i)));
				daire[arr].setPosition(yakinlastirma_katsayisi*nokta.getX()+PENCERE_ENI/2,-yakinlastirma_katsayisi*nokta.getY()+PENCERE_YUKSEKLIGI/2);}

			pencere.draw(x_ekseni);pencere.draw(y_ekseni);
		}
	}
	return 0;
}

