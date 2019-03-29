
#include<SFML\Graphics.hpp>
#include <iostream>
#include "Nokta.h"
#include <cmath>

using namespace sf;
using std::cout;
using std::endl;

int main() {
	int degisken=0, degisken2=0,teta=0;
	RenderWindow pencere(VideoMode(1080, 720), "Koordinat Duzleminde Vektor");
	Nokta nokta_2(0,0);
	CircleShape daire[80];
	//	pencere.setFramerateLimit(60);


	for(int i=0;i<80;i++){

		daire[i].setRadius(1);
		daire[i].setFillColor(Color(255,255,255));
	}



	while(pencere.isOpen()){
		Event olayNesnesi;
		while(pencere.pollEvent(olayNesnesi)){

		}

		for(double i=10; i>=-10; i-=0.005){
			for(int arr=0;arr<80;arr++){

				pencere.draw(daire[arr]);
				nokta_2.setX(i);
				nokta_2.setY(sqrt((i*i)+1)/cos((i*i)+1));
				nokta_2.ekrana_yazdir();
				cout<<endl;
				daire[degisken].setPosition(50*nokta_2.getX()+500,-50*nokta_2.getY()+500);}

			degisken++;degisken2++;
			if(degisken>79)degisken=0;

			pencere.display();}

	}
	return 0;
}












