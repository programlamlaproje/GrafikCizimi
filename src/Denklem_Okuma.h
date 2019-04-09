
#ifndef DENKLEM_OKUMA_H_
#define DENKLEM_OKUMA_H_

#include <iostream>
#include <SFML/Graphics.hpp>

int x;
bool a=true;float denklem;
std::string denklem_oku(sf::Event& olayNesnesi, sf::String& kullanici_denklemi){

	if(olayNesnesi.type==sf::Event::TextEntered && a)
	{
		if(olayNesnesi.text.unicode)
			kullanici_denklemi += olayNesnesi.text.unicode;
	}
	a=true;
	if(olayNesnesi.type==sf::Event::KeyPressed)
	{
		if(olayNesnesi.key.code==sf::Keyboard::BackSpace){
			std::string str = kullanici_denklemi;
			int size = str.size();
			if(size>0)
				str.resize(size-1);
			kullanici_denklemi=str;
			a=false;
		}
	}


	return kullanici_denklemi;
}
float isleme_cevir(sf::String kullanici_denklemi, float t){
	std::string str = kullanici_denklemi;

	x=t;
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

	return denklem;
}

#endif /* DENKLEM_OKUMA_H_ */

//39 58 94=^

/*
 *
 */
