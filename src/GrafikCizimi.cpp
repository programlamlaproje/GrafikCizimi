
#include<SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;


static const int PENCERE_ENI=1080,	//Acilan pencerenin enini belirler.
		PENCERE_YUKSEKLIGI=720;	//Acilan pencerenin boyunu belirler.

int 	yakinlastirma_katsayisi=50,//Grafigin yakinlik ve uzaklik degerini belirler.
		x_eleman_sayisi=75,
		y_eleman_sayisi=81
		;
float grafik_basitligi=0.007,	//Grafigin goruntusunu iyilestirir. Dusuk degerde program yavas calisir. ideal deger = 0.005
		eksen_kalinligi=2,//x ve y eksenlerinin kalinliklarini belirler.
		x_koordinati=0,	//Denklemde kullanilan noktanin x eksenindeki degerini belirler.
		y_koordinati=0, //Denklemde kullanilan noktanin y eksenindeki degerini belirler.
		x_koordinati_fark,
		y_koordinati_fark,
		mouse_eski_x, //Farenin hareket ettirilmeden ki x koordinatini verir.
		mouse_eski_y,//Farenin hareket ettirilmeden ki y koordinatini verir.
		mouse_x,//Farenin guncel x koordinatini verir.
		mouse_y, //Farenin guncel y koordinatini verir.
		kalem_kalinligi=1, //Kalemin kalinligini belirler.
		fark_x=0,	//Ekranin x-ekseninde kaydirilmasini saglar.
		fark_y=0	//Ekranin y-ekseninde kaydirilmasini saglar.
		;
bool sag_kontrol=false, //Farenin sag tusuna basiliyorsa true degerini alir.
		sol_kontrol=false	////Farenin sol tusuna basiliyorsa true degerini alir.
		;
std::vector<CircleShape>kalem; //Kalem kullanimi icin dizi olusturur.


void buyutec(Event& olayNesnesi){ // Yakinlastirma metotu
	if(olayNesnesi.type == Event::MouseWheelMoved){	//Farenin hareketlerini kontrol eden if komutlari.
		if(olayNesnesi.mouseWheel.delta>0 && yakinlastirma_katsayisi <250){
			yakinlastirma_katsayisi+=10;
			eksen_kalinligi+=0.2;
		}else if(olayNesnesi.mouseWheel.delta<0 && yakinlastirma_katsayisi>29){
			yakinlastirma_katsayisi-=10;
			if(eksen_kalinligi>0.3)eksen_kalinligi-=0.2;
		}//else if komutunun bitimi
	}//Fare tekerlek kontrol if komutunun bitimi
}//Buyutec metotunun bitimi

void fare_etkinlikleri(Event& olayNesnesi)//Fare hareketlerini denetleyen metot
{
	if(olayNesnesi.type==Event::MouseButtonPressed)//Farenin herhangi bir butonuna basilmasini kontrol eder.
	{
		if(olayNesnesi.mouseButton.button==sf::Mouse::Right)//Farenin sag butonuna basilmasini kontrol eder.
		{
			sag_kontrol=true;
		}
		if(olayNesnesi.mouseButton.button==sf::Mouse::Left)//Farenin sol butonuna basilmasini kontrol eder.
			sol_kontrol=true;

	}
	if(olayNesnesi.type==Event::MouseButtonReleased)//Farenin basilan butonunun birakilmasini kontrol eder.
	{
		if(olayNesnesi.mouseButton.button==sf::Mouse::Right)
			sag_kontrol=false;

		if(olayNesnesi.mouseButton.button==sf::Mouse::Left)
			sol_kontrol=false;

	}
	if(olayNesnesi.type==sf::Event::MouseMoved)//Farenin hareket ettirilmesini denetler.
	{
		mouse_x=olayNesnesi.mouseMove.x;//Farenin x-koordinatini verir.
		mouse_y=olayNesnesi.mouseMove.y;//Farenin y-koordinatini verir.
	}
}

void klavye_etkinlikleri(Event& olayNesnesi, RenderWindow& pencere)
{
	if(olayNesnesi.type==Event::KeyPressed)
	{
		if(olayNesnesi.key.code==Keyboard::Up)fark_y-=50;
		if(olayNesnesi.key.code==Keyboard::Down)fark_y+=50;
		if(olayNesnesi.key.code==Keyboard::Left)fark_x-=50;
		if(olayNesnesi.key.code==Keyboard::Right)fark_x+=50;
		if(olayNesnesi.key.code==Keyboard::BackSpace)kalem.clear();
		if(olayNesnesi.key.code==Keyboard::Add && yakinlastirma_katsayisi <250)yakinlastirma_katsayisi+=10;
		if(olayNesnesi.key.code==Keyboard::Subtract && yakinlastirma_katsayisi>29)yakinlastirma_katsayisi-=10;
		if(olayNesnesi.key.code==Keyboard::LShift || olayNesnesi.key.code==Keyboard::RShift)yakinlastirma_katsayisi=50;
		if(olayNesnesi.key.code==Keyboard::Space)
		{
			fark_x=0;fark_y=0;
		}
		if(olayNesnesi.key.code==Keyboard::Enter)
		{
			yakinlastirma_katsayisi=50;
			fark_x=0;fark_y=0;
		}
		if(olayNesnesi.key.code==Keyboard::Escape)pencere.close();

	}
}


int main() {
	ContextSettings settings;settings.antialiasingLevel=8; //Grafigin pruzlerini siler
	RenderWindow pencere(VideoMode(PENCERE_ENI, PENCERE_YUKSEKLIGI), "Grafik Cizimi",Style::Default,settings); //Pencereyi olusturur ve tanimlar.
	RectangleShape x_ekseni;RectangleShape y_ekseni;	//Eksenleri olusturur.
	Font font;if(!font.loadFromFile("calibril.ttf")){/*Yazinin olusabilmesi icin bu kosul gerekli*/}
	Text y_pozitif_sayilar[y_eleman_sayisi],y_negatif_sayilar[100],x_pozitif_sayilar[x_eleman_sayisi], x_negatif_sayilar[x_eleman_sayisi]; //Eksenleri numaranlandiran sayilari olusturur.
	CircleShape sekil; //Kalem kullanimi icin nokta olusturur.

	sekil.setFillColor(Color(0,255,0));//Kalem renginin ayarlar.

	for(int i=1;i<y_eleman_sayisi;i++){//y-ekseni sayilarini tanimlar.
		y_pozitif_sayilar[i].setFont(font);
		y_pozitif_sayilar[i].setString(std::to_string(i));
		y_pozitif_sayilar[i].setColor(Color::White);

		y_negatif_sayilar[i].setFont(font);
		y_negatif_sayilar[i].setString(std::to_string(-i));
		y_negatif_sayilar[i].setColor(Color::White);
	}//y-eksen sayilari bitimi
	for(int i=1;i<x_eleman_sayisi;i++){// x-ekseni sayilarini tanimlar.
		x_pozitif_sayilar[i].setFont(font);
		x_pozitif_sayilar[i].setString(std::to_string(i));
		x_pozitif_sayilar[i].setColor(Color::White);

		x_negatif_sayilar[i].setFont(font);
		x_negatif_sayilar[i].setString(std::to_string(-i));
		x_negatif_sayilar[i].setColor(Color::White);

	}//x-eksen sayilari bitimi

	//Eksen cizgilerini tanimlanir.
	x_ekseni.setFillColor(Color::White);

	y_ekseni.setFillColor(Color::White);


	while(pencere.isOpen()){	//Pencerenin acilmasini ve ekran grafiklerinin olusmasini saglayan dongu
		pencere.display();
		Event olayNesnesi; //Kullanicin komutlarini kontrol eden obje
		pencere.clear();
		while(pencere.pollEvent(olayNesnesi)){
			if(olayNesnesi.type == Event::Closed)pencere.close(); //Pencerenin ust menuden kapanmasini saglar.
			buyutec(olayNesnesi);//Ekrani yakinlastirma metotuna goturur.
			fare_etkinlikleri(olayNesnesi);	//Farenin hareketlerini kontrol eder.
			klavye_etkinlikleri(olayNesnesi, pencere);
		}

		if(!sol_kontrol)
		{
			mouse_eski_x=mouse_x+fark_x;
			mouse_eski_y=mouse_y+fark_y;

		}

		if(!sol_kontrol)
		{
			mouse_eski_x=mouse_x+fark_x;
			mouse_eski_y=mouse_y+fark_y;

		}

		if(sol_kontrol && fark_x>=-1100*yakinlastirma_katsayisi/24
				&& fark_x<=1100*yakinlastirma_katsayisi/24
				&& fark_y>=-1500*yakinlastirma_katsayisi/24
				&& fark_y<=1500*yakinlastirma_katsayisi/24)
		{
			fark_x=mouse_eski_x-mouse_x;
			fark_y=mouse_eski_y-mouse_y;
		}

		if(fark_x<-1100*yakinlastirma_katsayisi/24)
		{
			fark_x=-1100*yakinlastirma_katsayisi/24+1;
		}else if( fark_x>1100*yakinlastirma_katsayisi/24)
		{
			fark_x=1100*yakinlastirma_katsayisi/24-1;
		}
		if(fark_y<-1500*yakinlastirma_katsayisi/24)
		{
			fark_y=-1500*yakinlastirma_katsayisi/24+1;
		}else if( fark_y>1500*yakinlastirma_katsayisi/24)
		{
			fark_y=1500*yakinlastirma_katsayisi/24-1;
		}

		x_ekseni.setSize(Vector2f(PENCERE_ENI*2.1,eksen_kalinligi));		//Eksenlerin boyutlarini tanimlar.
		y_ekseni.setSize(Vector2f(eksen_kalinligi,PENCERE_YUKSEKLIGI*3.1));
		x_ekseni.setPosition(-1100,PENCERE_YUKSEKLIGI/2-fark_y);y_ekseni.setPosition(PENCERE_ENI/2-fark_x,-1500);
		pencere.draw(x_ekseni);pencere.draw(y_ekseni);//Eksenler ekranda gosterilir.
		for(int arr=1;arr<y_eleman_sayisi;arr++)//y_eksenine sayilari yerlestirir.
		{
			y_pozitif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			y_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x,PENCERE_YUKSEKLIGI/2-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
			pencere.draw(y_pozitif_sayilar[arr]);

			y_negatif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			y_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-yakinlastirma_katsayisi/2-5-fark_x,PENCERE_YUKSEKLIGI/2+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/5-fark_y);
			pencere.draw(y_negatif_sayilar[arr]);
		}//y-eksenine sayi yerlestirme bitimi

		for(int arr=1;arr<x_eleman_sayisi;arr++)//x_eksenine sayilari yerlestirir.
		{
			x_pozitif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			x_pozitif_sayilar[arr].setPosition((PENCERE_ENI/2)+float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/25-fark_x,PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y);
			pencere.draw(x_pozitif_sayilar[arr]);

			x_negatif_sayilar[arr].setCharacterSize(float(yakinlastirma_katsayisi)/5+5);
			x_negatif_sayilar[arr].setPosition((PENCERE_ENI/2)-float(yakinlastirma_katsayisi)*arr-float(yakinlastirma_katsayisi)/10-fark_x,PENCERE_YUKSEKLIGI/2+yakinlastirma_katsayisi/5-fark_y);
			pencere.draw(x_negatif_sayilar[arr]);
		}//x-eksenine sayi yerlestirme bitimi
		int eski_x_koordinati=0, eski_y_koordinati=0;
		//Denkelem grafigin egrisi asagidaki for dongusunde cizilir.
		for(float t=30+fark_x/yakinlastirma_katsayisi; t>=-30+fark_x/yakinlastirma_katsayisi;t-=grafik_basitligi)//Grafigi olusturan noktalarin x degerinin verildigi dongu
		{
			x_koordinati=t;		//Noktanin x degeri belirlenir./////////////////////////////////////////////////////////////////////
			y_koordinati=t*t/(sqrt(4*t-t*t));		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
			if(eski_x_koordinati!=0 &&	eski_y_koordinati!=0)
			{
				Vertex cizikler[] = //Grafik burada olusturulan cizgiler ile olusturulur.
				{
						Vertex(Vector2f(eski_x_koordinati,eski_y_koordinati)),
						Vertex(Vector2f(PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x,PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y),Color::White)
				};
				pencere.draw(cizikler, 2, Lines);
			}
			eski_x_koordinati=PENCERE_ENI/2+yakinlastirma_katsayisi*x_koordinati-fark_x;eski_y_koordinati=PENCERE_YUKSEKLIGI/2-yakinlastirma_katsayisi*y_koordinati-fark_y;
		}

		if(sag_kontrol )//Kalem ile þekil cizme burada gerceklesir.
		{
			sekil.setPosition(mouse_x+fark_x,mouse_y+fark_y);//Cizilecek konumu belirler.
			kalem.push_back(sekil);//Cizimi hafizaya alir.
			pencere.draw(sekil);//Cizimi ekranada gosterir.
		}

		for(CircleShape siradaki : kalem)//Cizilen sekli ekranda tutar.
		{
			if(sag_kontrol)
			{
				x_koordinati_fark=(PENCERE_ENI/2-siradaki.getPosition().x)*50/yakinlastirma_katsayisi;
				y_koordinati_fark=(PENCERE_YUKSEKLIGI/2-siradaki.getPosition().y)*50/yakinlastirma_katsayisi;
			}
			else
			{
				x_koordinati_fark=(PENCERE_ENI/2-siradaki.getPosition().x);
				y_koordinati_fark=(PENCERE_YUKSEKLIGI/2-siradaki.getPosition().y);
			}


			siradaki.setRadius(kalem_kalinligi+(float(yakinlastirma_katsayisi)/60));//Cizilen seklin kalinligini belirler.
			siradaki.setPosition(PENCERE_ENI/2-x_koordinati_fark*yakinlastirma_katsayisi/50-fark_x, PENCERE_YUKSEKLIGI/2-y_koordinati_fark*yakinlastirma_katsayisi/50-fark_y);
			pencere.draw(siradaki);
		}
		Vertex lines[] =
		{
				Vertex(Vector2f(mouse_x+10,mouse_y-10)),
				Vertex(Vector2f(mouse_x,mouse_y),Color::Green)
		};
		pencere.draw(lines, 2, Lines);
	}
	return 0;
}

//En sevdigim grafik y=(1/t*t)+(t*t/sqrt(cos(t)+t))
/*
 * log(sqrt(x*x+1))-sin(pow(x*x+1,cos(x)))
 *
 * nokta.setX(3*cos(x)/(1/x*x)+(x*x/sqrt(cos(x)+x)));
				nokta.setY(3*sin(x));
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
/*

	if(!sol_kontrol)
		{
			mouse_eski_x=mouse_x+fark_x;
			mouse_eski_y=mouse_y+fark_y;

		}

		if(sol_kontrol && fark_x>=-1100*yakinlastirma_katsayisi/24
				&& fark_x<=1100*yakinlastirma_katsayisi/24
				&& fark_y>=-1500*yakinlastirma_katsayisi/24
				&& fark_y<=1500*yakinlastirma_katsayisi/24)
		{
			fark_x=mouse_eski_x-mouse_x;
			fark_y=mouse_eski_y-mouse_y;
		}

		if(fark_x<-1100*yakinlastirma_katsayisi/24)
		{
			fark_x=-1100*yakinlastirma_katsayisi/24+1;
		}else if( fark_x>1100*yakinlastirma_katsayisi/24)
		{
			fark_x=1100*yakinlastirma_katsayisi/24-1;
		}
		if(fark_y<-1500*yakinlastirma_katsayisi/24)
		{
			fark_y=-1500*yakinlastirma_katsayisi/24+1;
		}else if( fark_y>1500*yakinlastirma_katsayisi/24)
		{
			fark_y=1500*yakinlastirma_katsayisi/24-1;
		}

 */
