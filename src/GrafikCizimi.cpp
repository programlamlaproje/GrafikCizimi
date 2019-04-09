
#include<SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Denklem_Okuma.h"
using namespace sf;

static const int PENCERE_ENI=1080,	//Acilan pencerenin enini belirler.
		PENCERE_YUKSEKLIGI=720,	//Acilan pencerenin boyunu belirler.
		SIMGE_BOYUTU=20,	//Secilen kalemin ya da silginin boyutunu belirler.
		MENU_SIMGE_BOYUTU=15	//Ust menude görünen simgelerin boyutunu belirler.
		;
int 	yakinlastirma_katsayisi=50,//Grafigin yakinlik ve uzaklik degerini belirler.
		x_eleman_sayisi=75,		//x-eksenindeki sayilarin dizisi icin eleman sayisi
		y_eleman_sayisi=81,		//y-eksenindeki sayilarin dizisi icin eleman sayisi
		menu_degisken=1, 		//kalem=1, silgi=2
		kalem_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*22,	//*****************
		kalem_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*20,		//
		silgi_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*19,	//SÝmgelerin menudeki baslangic ve bitis konumlari
		silgi_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*17,		//
		cop_baslangic=PENCERE_ENI-MENU_SIMGE_BOYUTU*16,		//
		cop_bitis=PENCERE_ENI-MENU_SIMGE_BOYUTU*14,			//*****************
		R=0,G=255,B=0
		;
float grafik_basitligi=0.007,	//Grafigin goruntusunu iyilestirir. Dusuk degerde program yavas calisir. ideal deger = 0.005
		eksen_kalinligi=2,//x ve y eksenlerinin kalinliklarini belirler.
		x_koordinati=0,	//Denklemde kullanilan noktanin x eksenindeki degerini belirler.
		y_koordinati=0, //Denklemde kullanilan noktanin y eksenindeki degerini belirler.
		x_koordinati_fark,	//x-ekseni ile fare isaretcisinin farkýný verir. Yakinsalip uzaklasmada kalemle cizilen seklin yerini korumasi icin
		y_koordinati_fark,	//y-ekseni ile fare isaretcisinin farkýný verir. Yakinsalip uzaklasmada kalemle cizilen seklin yerini korumasi icin
		mouse_eski_x, //Farenin hareket ettirilmeden ki x koordinatini verir.
		mouse_eski_y,//Farenin hareket ettirilmeden ki y koordinatini verir.
		mouse_x,//Farenin guncel x koordinatini verir.
		mouse_y, //Farenin guncel y koordinatini verir.
		kalem_kalinligi=1.5, //Kalemin kalinligini belirler.
		fark_x=0,	//Ekranin x-ekseninde kaydirilmasini saglar.
		fark_y=0,	//Ekranin y-ekseninde kaydirilmasini saglar.
		t,			//Denklem parametresi
		ekran_siniri_x, //Ekranin x-ekseninde ne kadar kaydirilacagini belirler.
		ekran_siniri_y	//Ekranin y-ekseninde ne kadar kaydirilacagini belirler.
		;
bool sol_kontrol=false, //Farenin sag tusuna basiliyorsa true degerini alir.
		sag_kontrol=false,	////Farenin sol tusuna basiliyorsa true degerini alir.
		abc=false /////////////////******************************************************/////////////////////////////////////////
		;

std::vector<CircleShape>kalem; //Kalem kullanimi icin dizi olusturur.

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
			kalem.clear();	//Kalem ile yazilan her seyi siler.

		if(PENCERE_ENI-2.2*MENU_SIMGE_BOYUTU<mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=0;G=0;B=255;}
		else if(PENCERE_ENI-2.2*MENU_SIMGE_BOYUTU>mouse_x
				&& PENCERE_ENI-4.4*MENU_SIMGE_BOYUTU<mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=0;G=255;B=0;}
		else if(PENCERE_ENI-4.4*MENU_SIMGE_BOYUTU>mouse_x
				&& PENCERE_ENI-6.6*MENU_SIMGE_BOYUTU<mouse_x
				&& olayNesnesi.mouseButton.button==sf::Mouse::Left
				&& mouse_y<50){R=255;G=0;B=2;}
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
		if(olayNesnesi.key.code==Keyboard::Up)fark_y-=50;
		if(olayNesnesi.key.code==Keyboard::Down)fark_y+=50;
		if(olayNesnesi.key.code==Keyboard::Left)fark_x-=50;
		if(olayNesnesi.key.code==Keyboard::Right)fark_x+=50;
		if(olayNesnesi.key.code==Keyboard::Delete)kalem.clear();
		if(olayNesnesi.key.code==Keyboard::Y && yakinlastirma_katsayisi <250 )yakinlastirma_katsayisi+=10;
		if(olayNesnesi.key.code==Keyboard::U && yakinlastirma_katsayisi>29)yakinlastirma_katsayisi-=10;
		if(olayNesnesi.key.code==Keyboard::Space){fark_x=0;fark_y=0;yakinlastirma_katsayisi=50;eksen_kalinligi=2;}
		if(olayNesnesi.key.code==Keyboard::Escape)pencere.close();
	}
}

int main() {
	ContextSettings settings;settings.antialiasingLevel=8; //Grafigin pruzlerini siler
	RenderWindow pencere(VideoMode(PENCERE_ENI, PENCERE_YUKSEKLIGI), "Grafik Cizimi",Style::Default,settings); //Pencereyi olusturur ve tanimlar.
	Event olayNesnesi; //Kullanicin komutlarini kontrol eden obje
	Font font;if(!font.loadFromFile("calibril.ttf")){/*Yazinin olusabilmesi icin bu kosul gerekli*/}
	Cursor imlec; //Imleci tanimlar.
	RectangleShape	//======================================================================================DORTGEN
	x_ekseni,	//x-eksenini olusturur.
	y_ekseni,	//y-eksenini olusturur.
	menu(Vector2f(PENCERE_ENI-6,50)), //Menu cercevesini olusturur.
	menu_renk_secimi(Vector2f(MENU_SIMGE_BOYUTU*1.5,MENU_SIMGE_BOYUTU*1.5))
	;
	CircleShape //==========================================================================================CEMBER
	sekil, //Kalem kullanimi icin nokta olusturur.
	imlecIcon(SIMGE_BOYUTU), //Imlec simgeleri(kalem ve silgi) icin cerceve olusturur.
	menu_kalem(MENU_SIMGE_BOYUTU),	//Menudeki kalem simgesi icin cerceve olusturur.
	menu_silgi(MENU_SIMGE_BOYUTU),	//Menudeki silgi simgesi icin cerceve olusturur.
	menu_tumunu_sil(MENU_SIMGE_BOYUTU)	//Menudeki cop kutusu simgesi icin cerceve olusturur.
	;
	Text //=================================================================================================METIN
	y_pozitif_sayilar[y_eleman_sayisi],//Eksenleri numaranlandiran sayilari olusturur.
	y_negatif_sayilar[y_eleman_sayisi],
	x_pozitif_sayilar[x_eleman_sayisi],
	x_negatif_sayilar[x_eleman_sayisi],
	fx,	//Menudeki "f(x)=" yazisini olusturur.
	denklem_metni //Kullanicinin girdigi denklemi ekrana yazar.
	;

	Texture	//==============================================================================================RESIM
	kalemSimgesi, //Kalem simgesinin resmi (cerceveye yerlestirilecek resim)
	silgiSimgesi, //Silgi simgesinin resmi
	tumunuSilSimgesi //Cop kutusu simgesinin resmi
	;
	String kullanici_denklemi = ""; //Kullanicin girdigi metni hafizaya alir.

	fx.setString("f(x)=");
	fx.setFont(font);
	fx.setPosition(10,10);
	fx.setCharacterSize(30);
	denklem_metni.setFont(font);
	denklem_metni.setPosition(80,10);
	denklem_metni.setCharacterSize(30);

	if(kalemSimgesi.loadFromFile("kalem.png"));	//Kalem resmi iceri aktarir.
	if(silgiSimgesi.loadFromFile("silgi.png"));
	if(tumunuSilSimgesi.loadFromFile("tumunuSil.png"));
	menu_kalem.setTexture(&kalemSimgesi); //Iceriye aktarilan resmi cerceveye yerlestirir.
	menu_silgi.setTexture(&silgiSimgesi);
	menu_tumunu_sil.setTexture(&tumunuSilSimgesi);
	menu_kalem.setPosition(kalem_baslangic,10);
	menu_silgi.setPosition(silgi_baslangic,10);
	menu_tumunu_sil.setPosition(cop_baslangic,10);
	menu.setOutlineThickness(2.5); //Menu cercevesinin dýs cizgi kalinligini belirler.
	menu.setFillColor(Color(30,30,30));
	menu.setOutlineColor(Color::White);//Menu cercevesinin dýs cizgi rengini belirler.
	menu.setPosition(3,3);


	menu_renk_secimi.setOutlineThickness(3);
	menu_renk_secimi.setOutlineColor(Color(240,240,240));

	for(int i=1;i<y_eleman_sayisi;i++){//y-ekseni sayilarini tanimlar.
		y_pozitif_sayilar[i].setFont(font);y_negatif_sayilar[i].setFont(font);
		y_pozitif_sayilar[i].setString(std::to_string(i));
		y_negatif_sayilar[i].setString(std::to_string(-i));
	}//y-eksen sayilari bitimi
	for(int i=1;i<x_eleman_sayisi;i++){// x-ekseni sayilarini tanimlar.
		x_pozitif_sayilar[i].setFont(font);x_negatif_sayilar[i].setFont(font);
		x_pozitif_sayilar[i].setString(std::to_string(i));
		x_negatif_sayilar[i].setString(std::to_string(-i));
	}//x-eksen sayilari bitimi

	while(pencere.isOpen()){	//Pencerenin acilmasini ve ekran grafiklerinin olusmasini saglayan dongu
		pencere.display();
		pencere.clear();
		while(pencere.pollEvent(olayNesnesi)){ //Kullanici komutlari dongusu

			fare_etkinlikleri(olayNesnesi);	//Farenin hareketlerini kontrol eder.
			klavye_etkinlikleri(olayNesnesi, pencere); //Klavyenin hareketlerini kontrol eder.
			denklem_metni.setString(denklem_oku(olayNesnesi, kullanici_denklemi)); //Kullanicidan denklem alan fonksiyon.

		}//Kullanici komutlari dongusu bitimi


		sekil.setFillColor(Color(R,G,B));//Kalem renginin ayarlar.

		ekran_siniri_x = 1100*yakinlastirma_katsayisi/24; //Ekranin x-ekseninde en fazla kaydirilabilecegi degeri hesaplar.
		ekran_siniri_y = 1500*yakinlastirma_katsayisi/24; //Ekranin y-ekseninde en fazla kaydirilabilecegi degeri hesaplar.

		if(menu_degisken==1)
		{
			imlecIcon.setTexture(&kalemSimgesi);
		}else{
			imlecIcon.setTexture(&silgiSimgesi);
		}

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

		if(fark_x<-ekran_siniri_x) //Ekran kaydirmada sinirlari asýlýrsa sinirlar bu else if dongusunde duzeltilir
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

		x_ekseni.setSize(Vector2f(PENCERE_ENI*2.1,eksen_kalinligi));		//Eksenlerin boyutlarini tanimlar.
		y_ekseni.setSize(Vector2f(eksen_kalinligi,PENCERE_YUKSEKLIGI*3.1));
		x_ekseni.setPosition(-1100,PENCERE_YUKSEKLIGI/2-fark_y);y_ekseni.setPosition(PENCERE_ENI/2-fark_x,-1500); //Eksenlerin konumlarini belirler
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
		t=30+fark_x/yakinlastirma_katsayisi;
		//Denkelem grafigin egrisi asagidaki for dongusunde cizilir.
		while(t>=-30+fark_x/yakinlastirma_katsayisi)//Grafigi olusturan noktalarin x degerinin verildigi dongu
		{
			x_koordinati=t;		//Noktanin x degeri belirlenir./////////////////////////////////////////////////////////////////////
			y_koordinati=t*t;		//Noktanin y degeri belirlenir./////////////////////////////////////////////////////////////////
			if(eski_x_koordinati!=0 &&	eski_y_koordinati!=0)
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

		if(sol_kontrol && menu_degisken==1 )//Kalem ile þekil cizme burada gerceklesir.
		{
			sekil.setPosition(mouse_x+fark_x,mouse_y+fark_y);//Cizilecek konumu belirler.
			kalem.push_back(sekil);//Cizimi hafizaya alir.
			pencere.draw(sekil);//Cizimi ekranada gosterir.
		}
		int silginin_altindaki_noktalar =0; //Silgi kullanilirken silginin hangi noktalari silecegi bu int ile belirlenir.
		for(CircleShape siradaki : kalem)//Cizilen sekli ekranda tutar.
		{
			if(sol_kontrol)
			{
				x_koordinati_fark=(PENCERE_ENI/2-siradaki.getPosition().x)*yakinlastirma_katsayisi/50;
				y_koordinati_fark=(PENCERE_YUKSEKLIGI/2-siradaki.getPosition().y)*yakinlastirma_katsayisi/50;
			}
			else
			{
				x_koordinati_fark=(PENCERE_ENI/2-siradaki.getPosition().x)*yakinlastirma_katsayisi/50;
				y_koordinati_fark=(PENCERE_YUKSEKLIGI/2-siradaki.getPosition().y)*yakinlastirma_katsayisi/50;
			}
			siradaki.setRadius(kalem_kalinligi+(float(yakinlastirma_katsayisi)/60));//Cizilen seklin kalinligini belirler.
			siradaki.setPosition(PENCERE_ENI/2-x_koordinati_fark-fark_x, PENCERE_YUKSEKLIGI/2-y_koordinati_fark-fark_y);
			pencere.draw(siradaki);
			if(mouse_x-7<=siradaki.getPosition().x 	//Silgi kosulu
					&& siradaki.getPosition().x<=mouse_x+10
					&& mouse_y-10<=siradaki.getPosition().y
					&& siradaki.getPosition().y<=mouse_y+7
					&& sol_kontrol
					&& menu_degisken==2){
				kalem[silginin_altindaki_noktalar].setFillColor(Color::Transparent);
			}

			silginin_altindaki_noktalar++;
		}
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
		pencere.draw(menu);pencere.draw(menu_kalem);pencere.draw(menu_silgi);pencere.draw(menu_tumunu_sil);
		pencere.draw(fx);pencere.draw(denklem_metni);

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

