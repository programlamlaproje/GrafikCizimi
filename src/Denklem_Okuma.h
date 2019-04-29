
#ifndef DENKLEM_OKUMA_H_
#define DENKLEM_OKUMA_H_

#include <iostream>
#include <SFML/Graphics.hpp>

int x;
bool sil_tusu_kontrol=true;
float denklem;

void silgi(sf::String &kullanici_denklemi){
	std::string str = kullanici_denklemi;
	int size = str.size();
	if(size>0)
		str.resize(size-1);
	kullanici_denklemi=str;
}

float isleme_cevir(sf::String kullanici_denklemi){
	std::string str = kullanici_denklemi;
	int onluk_sayi=1;
	for(int i=str.size()-1; i>=0; i--)
	{
		if(str[i]-'0'>=0 || str[i]-'0'<=9){
			denklem += onluk_sayi*str[i];
			onluk_sayi*=10;
		}
		if(str[i]-'0'==72){
			denklem += x;
		}
	}

	std::cout << "Denklem: " << denklem ;

	return denklem;
}


std::string denklem_oku(sf::Event& olayNesnesi, sf::String& kullanici_denklemi){

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
				|| olayNesnesi.text.unicode == 120
				|| olayNesnesi.text.unicode == 121)
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
	return kullanici_denklemi;
}




#endif /* DENKLEM_OKUMA_H_ */

//39 58 94=^

/*
 *
 */
