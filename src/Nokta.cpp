/*
 * Nokta.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: Emre
 */

#include "Nokta.h"



Nokta::Nokta(double a, double b){x=a;y=b;}
double Nokta::getX(){return x;}
double Nokta::getY(){return y;}
void Nokta::setX(double a){x=a;}
void Nokta::setY(double b){y=b;}
void Nokta::ustune_topla(Nokta girdi){x = x+girdi.getX();y= y+girdi.getY();}
Nokta Nokta::topla(Nokta girdi){
	Nokta toplam(x+girdi.getX(),y+girdi.getY());
	return toplam;
}
void Nokta::ekrana_yazdir(){std::cout << "(" << x << "," << y << ")";}
