/*
 * Nokta.h
 *
 *  Created on: Mar 29, 2019
 *      Author: Emre
 */

#ifndef NOKTA_H_
#define NOKTA_H_

#include <iostream>

class Nokta {
public:
	Nokta(double, double);//
	double getX();//Noktanin x degerini çagir
	double getY();
	void setX(double);
	void setY(double);
	void ustune_topla(Nokta);
	Nokta topla(Nokta);
	void ekrana_yazdir();

private:
	double x,y;
};

#endif /* NOKTA_H_ */
