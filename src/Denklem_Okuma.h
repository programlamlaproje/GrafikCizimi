
#ifndef DENKLEM_OKUMA_H_
#define DENKLEM_OKUMA_H_

#include <iostream>
#include <SFML/Graphics.hpp>

int x;
bool sil_tusu_kontrol=true,
		islem_kontrol=false;

sf::Text //=================================================================================================METIN
fx,	//Menudeki "f(x)=" yazisini olusturur.
denklem_metni //Kullanicinin girdigi denklemi ekrana yazar.
;
sf::String kullanici_denklemi;//Kullanicin girdigi metni hafizaya alir.
sf::Font font2;

void denklem(std::string str){
	kullanici_denklemi = str;
}
void denklem(std::string str1, std::string str2){
	kullanici_denklemi = str1 + "  g(x)= " + str2;
}

double sayiya_cevir(std::string str){
	double denklem = stoi(str);
	return denklem;
}

double isleme_cevir(sf::String kullanici_denklemi){
	std::string str = kullanici_denklemi;
	double denklem=0;
	for(int i=str.size()-1; i>=0; i++){


	}

	std::cout << "Denklem: " << denklem << "\n" ;

	return denklem;
}

void silgi(sf::String &kullanici_denklemi){
	std::string str = kullanici_denklemi;
	int size = str.size();
	if(size>0)
		str.resize(size-1);
	kullanici_denklemi=str;
}

void denklem_oku(sf::Event& olayNesnesi){

	if(olayNesnesi.type==sf::Event::TextEntered && sil_tusu_kontrol)
	{
		if((olayNesnesi.text.unicode > 39
				&& olayNesnesi.text.unicode < 58)
				|| olayNesnesi.text.unicode == 94
				|| olayNesnesi.text.unicode == 97
				|| olayNesnesi.text.unicode == 99
				|| olayNesnesi.text.unicode == 105
				|| olayNesnesi.text.unicode == 110
				|| olayNesnesi.text.unicode == 111
				|| olayNesnesi.text.unicode == 115
				|| olayNesnesi.text.unicode == 116
				|| olayNesnesi.text.unicode == 120)
			kullanici_denklemi += olayNesnesi.text.unicode;
	}
	sil_tusu_kontrol=true;
	if(olayNesnesi.type==sf::Event::KeyPressed)
	{
		if(olayNesnesi.key.code==sf::Keyboard::BackSpace){
			silgi(kullanici_denklemi);
			sil_tusu_kontrol=false;
		}
	}

	denklem_metni.setString(kullanici_denklemi);
}

void denklemMenuOlustur(){
	if(!font2.loadFromFile("calibril.ttf")){/*Yazinin olusabilmesi icin bu kosul gerekli*/};
	fx.setString("f(x)=");
	fx.setFont(font2);
	fx.setPosition(10,10);
	fx.setCharacterSize(30);
	denklem_metni.setFont(font2);
	denklem_metni.setPosition(80,10);
	denklem_metni.setCharacterSize(30);
}

void denklemiMenuyeYerlestir(sf::RenderWindow &pencere){
	pencere.draw(fx);pencere.draw(denklem_metni);
}




#endif /* DENKLEM_OKUMA_H_ */

//39 58 94=^

/*
 *
 */
