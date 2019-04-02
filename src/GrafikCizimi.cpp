
#include<SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using std::cout;
using std::endl;

static const int PENCERE_ENI=1080,	//Acilan pencerenin enini belirler.
		PENCERE_YUKSEKLIGI=720;	//Acilan pencerenin boyunu belirler.

int 	yakinlastirma_katsayisi=50//Grafigin yakinlik ve uzaklik degerini belirler.
		;
float grafik_basitligi=0.005,	//Grafigin goruntusunu iyilestirir. Dusuk degerde program yavas calisir.
		grafik_egri_kalinligi=1,	//Grafigik egrisinin kalinligini belirler.
		eksen_kalinligi=2,//x ve y eksenlerinin kalinliklarini belirler.
		x_koordinati=0,	//Denklemde kullanilan noktanin x eksenindeki degerini belirler.
		y_koordinati=0, //Denklemde kullanilan noktanin y eksenindeki degerini belirler.
		eski_x, //Farenin hareket ettirilmeden ki x koordinatini verir.
		eski_y,//Farenin hareket ettirilmeden ki y koordinatini verir.
		mouse_x,//Farenin guncel x koordinatini verir.
		mouse_y, //Farenin guncel y koordinatini verir.
		kalem_kalinligi=2 //Kalemin kalinligini belirler.
		;
bool kontrol=false; //Farenin sol tusuna basiliyorsa true degerini alir.

void buyutec(Event& olayNesnesi){ // Yakinlastirma metotu
	if(olayNesnesi.type == Event::MouseWheelMoved){	//Farenin hareketlerini kontrol eden if komutlari.
		if(olayNesnesi.mouseWheel.delta>0 && yakinlastirma_katsayisi <250){
			yakinlastirma_katsayisi+=10;
			eksen_kalinligi+=0.2;
		}else if(olayNesnesi.mouseWheel.delta<0 && yakinlastirma_katsayisi>19){
			yakinlastirma_katsayisi-=10;
			if(eksen_kalinligi>0.3)eksen_kalinligi-=0.2;
		}//else if komutunun bitimi
	}//Fare tekerlek kontrol if komutunun bitimi
}//Buyutec metotunun bitimi

void fare_etkinlikleri(Event& olayNesnesi){
	if(olayNesnesi.type==Event::MouseButtonPressed)
	{
		if(olayNesnesi.mouseButton.button==sf::Mouse::Left)
		{
			kontrol=true;
		}
	}
	if(olayNesnesi.type==Event::MouseButtonReleased)
	{
		if(olayNesnesi.mouseButton.button==sf::Mouse::Left){
			kontrol=false;
		}
	}
	if(olayNesnesi.type==sf::Event::MouseMoved){
		mouse_x=olayNesnesi.mouseMove.x;
		mouse_y=olayNesnesi.mouseMove.y;
	}
}


int main() {
	ContextSettings settings;settings.antialiasingLevel=500; //Grafigin pruzlerini siler
	RenderWindow pencere(VideoMode(PENCERE_ENI, PENCERE_YUKSEKLIGI), "Grafik Cizimi",Style::Default,settings); //Pencereyi olusturur ve tanimlar.
	CircleShape nokta; //Grafik egrisini olusturan noktayý olusturur.
	RectangleShape x_ekseni;RectangleShape y_ekseni;	//Eksenleri olusturur.
	Font font;if(!font.loadFromFile("calibril.ttf")){/*Yazinin olusabilmesi icin bu kosul gerekli*/}
	Text y_pozitif_sayilar[40],y_negatif_sayilar[40],x_pozitif_sayilar[60], x_negatif_sayilar[60]; //Eksenleri numaranlandiran sayilari olusturur.
	CircleShape sekil; //Kalem kullanimi icin nokta olusturur.
	std::vector<CircleShape>kalem; //Kalem kullanimi icin dizi olusturur.

	nokta.setFillColor(Color(255,255,255));//Grafik egrisini renklendirir.
	sekil.setFillColor(Color(0,255,0));//Kalem renginin ayarlar.

	for(int i=1;i<40;i++){//y-ekseni sayilarini tanimlar.
		y_pozitif_sayilar[i].setFont(font);
		y_pozitif_sayilar[i].setString(std::to_string(i));
		y_pozitif_sayilar[i].setColor(Color::White);

		y_negatif_sayilar[i].setFont(font);
		y_negatif_sayilar[i].setString(std::to_string(-i));
		y_negatif_sayilar[i].setColor(Color::White);
	}//y-eksen sayilari bitimi
	for(int i=1;i<60;i++){// x-ekseni sayilarini tanimlar.
		x_pozitif_sayilar[i].setFont(font);
		x_pozitif_sayilar[i].setString(std::to_string(i));
		x_pozitif_sayilar[i].setColor(Color::White);

		x_negatif_sayilar[i].setFont(font);
		x_negatif_sayilar[i].setString(std::to_string(-i));
		x_negatif_sayilar[i].setColor(Color::White);

	}//x-eksen sayilari bitimi

	//Eksen cizgilerini tanimlanir.
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
			buyutec(olayNesnesi);//Ekrani yakinlastirma metotuna goturur.
			fare_etkinlikleri(olayNesnesi);	//Farenin hareketlerini kontrol eder.
		}
		x_ekseni.setSize(Vector2f(PENCERE_ENI,eksen_kalinligi));		//Eksenlerin boyutlarini tanimlar.
		y_ekseni.setSize(Vector2f(eksen_kalinligi,PENCERE_YUKSEKLIGI));
		pencere.draw(x_ekseni);pencere.draw(y_ekseni);//Eksenler ekranda gosterilir.
		for(int arr=1;arr<40;arr++)//y_eksenine sayilari yerlestirir.
		{
			y_pozitif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			y_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5,PENCERE_YUKSEKLIGI/2-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5);
			pencere.draw(y_pozitif_sayilar[arr]);

			y_negatif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			y_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5,PENCERE_YUKSEKLIGI/2+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5);
			pencere.draw(y_negatif_sayilar[arr]);
		}//y-eksenine sayi yerlestirme bitimi

		for(int arr=1;arr<60;arr++)//x_eksenine sayilari yerlestirir.
		{
			x_pozitif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			x_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/25,PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5);
			pencere.draw(x_pozitif_sayilar[arr]);

			x_negatif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			x_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/10,PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5);
			pencere.draw(x_negatif_sayilar[arr]);
		}//x-eksenine sayi yerlestirme bitimi

		//Denkelem grafigin egrisi asagidaki for dongusunde cizilir.
		for(double t=20; t>=-20; t-=grafik_basitligi)//Grafigi olusturan noktalarin x degerinin verildigi dongu
		{
			x_koordinati=3*sin(t);		//Noktanin x degeri belirlenir.
			y_koordinati=5*cos(t);		//Noktanin y degeri belirlenir.
			nokta.setPosition(yakinlastirma_katsayisi*x_koordinati+PENCERE_ENI/2,-yakinlastirma_katsayisi*y_koordinati+PENCERE_YUKSEKLIGI/2);//Noktalari koordinat duzlemindeki yerlerine yerlestirir.
			nokta.setRadius(grafik_egri_kalinligi+(float(yakinlastirma_katsayisi)/75));//Grafik kalinligi ayarlanir
			pencere.draw(nokta);//Grafik noktalari ekranda gosterilir.
		}

		if(kontrol && (eski_x!=mouse_x || eski_y!=mouse_y))//Kalem ile þekil cizme burada gerceklesir.
		{
			sekil.setPosition(mouse_x,mouse_y);//Cizilecek konumu belirler.
			kalem.push_back(sekil);//Cizimi hafizaya alir.
			pencere.draw(sekil);//Cizimi ekranada gosterir.
		}
		for(CircleShape siradaki : kalem)//Cizilen sekli ekranda tutar.
		{
			siradaki.setRadius(kalem_kalinligi+(float(yakinlastirma_katsayisi)/60));//Cizilen seklin kalinligini belirler.
			siradaki.setPosition(siradaki.getPosition().x,siradaki.getPosition().y);
			pencere.draw(siradaki);
		}

	}
	return 0;
}

//En sevdigim grafik y=(1/x*x)+(x*x/sqrt(cos(x)+x))
/*
 * log(sqrt(x*x+1))-sin(pow(x*x+1,cos(x)))
 *
 * nokta.setX(3*cos(x)/(1/x*x)+(x*x/sqrt(cos(x)+x)));
				nokta.setY(3*sin(x));
 */
