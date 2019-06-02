#ifndef DENKLEM_OKUMA_H_
#define DENKLEM_OKUMA_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

bool sil_tusu_kontrol=true, //Silme islemi icin kontrol
		fx_kontrol=false, //f(x) denklemi girerse true olur
		fy_kontrol=false, //f(y) denklemi girerse true olur
		gx_kontrol=false, //g(x) denklemi girerse true olur
		gy_kontrol=false //g(y) denklemi girerse true olur
		;


sf::Text //=================================================================================================METIN
denklem_metni //Kullanicinin girdigi denklemi ekrana yazar.
;
sf::String kullanici_denklemi = "f(x)=";//Kullanicin girdigi metni hafizaya alir.
sf::Font font2;

std::vector<double>sonuclar_fx;	//f(x) icin denklem degerlerini depolar
std::vector<double>sonuclar_fy;	//f(y) grafik icin denklem degerlerini depolar
std::vector<double>sonuclar_gx;	//g(x) grafik icin denklem degerlerini depolar
std::vector<double>sonuclar_gy;	//g(y) grafik icin denklem degerlerini depolar

float grafik_basitligi=0.01,	//Grafigin goruntusunu iyilestirir. Dusuk degerde program yavas calisir. ideal deger = 0.005
		x_basl=-100,
		x_bit=100;

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
				&& olayNesnesi.text.unicode < 58
				&& olayNesnesi.text.unicode != 44)
				|| olayNesnesi.text.unicode == 32
				|| olayNesnesi.text.unicode == 61
				|| olayNesnesi.text.unicode == 94
				|| olayNesnesi.text.unicode == 97
				|| olayNesnesi.text.unicode == 99
				|| olayNesnesi.text.unicode == 102
				|| olayNesnesi.text.unicode == 103
				|| olayNesnesi.text.unicode == 105
				|| olayNesnesi.text.unicode == 110
				|| olayNesnesi.text.unicode == 111
				|| olayNesnesi.text.unicode == 115
				|| olayNesnesi.text.unicode == 116
				|| olayNesnesi.text.unicode == 117
				|| olayNesnesi.text.unicode == 120
				|| olayNesnesi.text.unicode == 121)
			kullanici_denklemi += olayNesnesi.text.unicode;
		if(olayNesnesi.text.unicode == 102 || olayNesnesi.text.unicode == 103){
			kullanici_denklemi += "(x)=";
		}
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
//====================================================================Ust taraf kullanicidan denklem okur ve ekrana eszamanli yazar

double isleme_cevir(string& denklem);



void islem_bitti_mi(string& denklem){
	int uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if((denklem[i]>= '0'&& denklem[i]<= '9') || denklem[i]=='.'/* || denklem[i]=='e+'|| denklem[i]=='e-'*/ || (denklem[i]=='-' && i==0)){
		}else{
			isleme_cevir(denklem);
		}
	}
}

void cikar(int i, string &denklem){
	bool eksi_taban=false, eksi_derece=false;
	int a=i-1, alt_sinir=0, ust_sinir=0;
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'){
		alt_sinir=a;
		a--;
	}
	if(denklem[a]=='-' && ((denklem[a-1]<='0' && denklem[a-1]>='9') || a==0 )){
		eksi_taban=true;
		alt_sinir=a;
	}
	double cikarilan, cikar;
	string boluneni ="", carpimi = "";
	while(++a!=i){
		boluneni.push_back(denklem[a]);
	}
	a=i+1;
	if(denklem[a]=='-' && a==i+1){
		eksi_derece=true;
	}
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'
					|| denklem[a]==','){
		carpimi.push_back(denklem[a]);

		a++;
		ust_sinir=a;
	}

	while(ust_sinir-alt_sinir>0){
		denklem.erase(denklem.begin()+alt_sinir);
		ust_sinir--;
	}
	cikarilan = stod(boluneni);
	cikar = stod(carpimi);
	if(eksi_taban){
		cikarilan*=-1;
	}
	if(eksi_derece){
		cikar*=-1;
	}
	denklem.insert(alt_sinir,to_string(cikarilan-cikar));
}

void topla(int i, string &denklem){
	bool eksi_taban=false, eksi_derece=false;
	int a=i-1, alt_sinir=0, ust_sinir=0;
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'){
		alt_sinir=a;
		a--;
	}
	if(denklem[a]=='-' && ((denklem[a-1]<='0' && denklem[a-1]>='9') || a==0 )){
		eksi_taban=true;
		alt_sinir=a;
	}
	double topla1, topla2;
	string boluneni ="", carpimi = "";
	while(a++!=i){
		boluneni.push_back(denklem[a]);
	}
	a=i+1;
	if(denklem[a]=='-' && a==i+1){
		eksi_derece=true;
	}
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.' ||(denklem[a]=='-' && a==i+1)){
		if(denklem[a]!='-')
			carpimi.push_back(denklem[a]);
		a++;
		ust_sinir=a;
	}
	while(ust_sinir-alt_sinir>0){
		denklem.erase(denklem.begin()+alt_sinir);
		ust_sinir--;
	}
	topla1 = stod(boluneni);
	topla2 = stod(carpimi);
	if(eksi_taban){
		topla1*=-1;
	}
	if(eksi_derece){
		topla2*=-1;
	}
	denklem.insert(alt_sinir,to_string(topla1+topla2));
}

void bol(int i, string &denklem){
	bool eksi_taban=false, eksi_derece=false;
	int a=i-1, alt_sinir=0, ust_sinir=0;
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'){
		alt_sinir=a;
		a--;
	}
	if(denklem[a]=='-' && ((denklem[a-1]<='0' && denklem[a-1]>='9') || a==0 )){
		eksi_taban=true;
		alt_sinir=a;
	}
	double bolunen, bolen;
	string boluneni ="", carpimi = "";
	while(++a!=i){
		boluneni.push_back(denklem[a]);
	}
	a=i+1;
	if(denklem[a]=='-' && a==i+1){
		eksi_derece=true;
	}
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.' ||(denklem[a]=='-' && a==i+1)){
		if(denklem[a]!='-'){
			carpimi.push_back(denklem[a]);
		}
		a++;
		ust_sinir=a;
	}

	while(ust_sinir-alt_sinir>0){
		denklem.erase(denklem.begin()+alt_sinir);
		ust_sinir--;
	}
	bolunen = stod(boluneni);
	bolen = stod(carpimi);
	if(eksi_taban){
		bolunen*=-1;
	}
	if(eksi_derece){
		bolen*=-1;
	}
	if(bolen!=0){
		denklem.insert(alt_sinir,to_string(double(bolunen)/bolen));
	}else{
		denklem.insert(alt_sinir,to_string(214748));
	}
}

void carp(int i, string &denklem){
	bool eksi_taban=false, eksi_derece=false;
	int a=i-1, alt_sinir=0, ust_sinir=0;
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'){
		alt_sinir=a;
		a--;
	}
	if(denklem[a]=='-' && ((denklem[a-1]<='0' && denklem[a-1]>='9') || a==0 )){
		eksi_taban=true;
		alt_sinir=a;
	}
	double carpan1, carpan2;
	string tabani ="", derecei = "";
	while(++a!=i){
		tabani.push_back(denklem[a]);
	}
	a=i+1;
	if(denklem[a]=='-' && a==i+1){
		eksi_derece=true;
	}
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.' ||(denklem[a]=='-' && a==i+1)){
		if(denklem[a]!='-'){
			derecei.push_back(denklem[a]);
		}
		a++;
		ust_sinir=a;
	}
	while(ust_sinir-alt_sinir>0){
		denklem.erase(denklem.begin()+alt_sinir);
		ust_sinir--;
	}
	carpan1 = stod(tabani);
	carpan2 = stod(derecei);
	if(eksi_taban){
		carpan1*=-1;
	}
	if(eksi_derece){
		carpan2*=-1;
	}
	denklem.insert(alt_sinir,to_string(double(carpan1)*carpan2));
}

void trigonometrik(int i, string& denklem){
	int a, alt_sinir=i;
	double deger;
	string trigoDenklem = "", degeri = "";
	while(denklem[i]=='a'
			|| denklem[i]=='c'
					|| denklem[i]=='i'
							|| denklem[i]=='n'
									|| denklem[i]=='o'
											|| denklem[i]=='s'
													|| denklem[i]=='t'){
		trigoDenklem.push_back(denklem[i]);
		i++;
	}
	a=i;
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'
					|| denklem[a] == '-'){
		degeri.push_back(denklem[a]);
		a++;
	}
	while(a-alt_sinir>0){
		denklem.erase(denklem.begin()+alt_sinir);
		a--;
	}

	deger = stod(degeri);
	if(trigoDenklem == "sin"){
		deger = sin(deger);
	}else if(trigoDenklem == "cos"){
		deger = cos(deger);
	}else if(trigoDenklem == "cot"){
		if(sin(deger)!=0){
			deger = 1/tan(deger);
		}else{
			if(cos(deger)>0){
				deger=214748;
			}else if(cos(deger)<0){
				deger=-214748;
			}
		}
	}else if(trigoDenklem == "tan"){
		if(cos(deger)!=0){
			deger = tan(deger);
		}else{
			if(sin(deger)>0){
				deger=214748;
			}else if(sin(deger)<0){
				deger=-214748;
			}

		}
	}else if(trigoDenklem == "asin"){
		deger = asin(deger);
	}else if(trigoDenklem == "acos"){
		deger = acos(deger);
	}else if(trigoDenklem == "acot"){
		deger = atan(1/deger);
	}else if(trigoDenklem == "atan"){
		deger = atan(deger);
	}else{
		cerr << "Bir seyler yanlis gidiyor.\nTrigonometrik denklemi kontrol et." << endl;
	}
	denklem.insert(alt_sinir,to_string(deger));
}

void us_al(int i, string& denklem){
	bool eksi_taban=false, eksi_derece=false;
	int a=i-1, alt_sinir=0, ust_sinir=0;
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.'){
		alt_sinir=a;
		a--;
	}
	if(denklem[a]=='-' && ((denklem[a-1]<='0' && denklem[a-1]>='9') || a==0 )){
		eksi_taban=true;
		alt_sinir=a;
	}
	double taban, derece;
	string tabani ="", derecei = "";
	while(++a!=i){
		tabani.push_back(denklem[a]);
	}
	a=i+1;
	if(denklem[a]=='-' && a==i+1){
		eksi_derece=true;
	}
	while((denklem[a]>= '0'
			&& denklem[a]<= '9')
			|| denklem[a]=='.' ||(denklem[a]=='-' && a==i+1)){
		if(denklem[a]!='-'){
			derecei.push_back(denklem[a]);
		}
		a++;
		ust_sinir=a;
	}
	while(ust_sinir-alt_sinir>0){
		ust_sinir--;
		denklem.erase(denklem.begin()+alt_sinir);
	}
	taban = stod(tabani);
	derece = stod(derecei);
	if(eksi_taban){
		taban*=-1;
	}
	if(eksi_derece){
		derece*=-1;
	}
	if(derece<0 && taban==0){
		denklem.insert(alt_sinir,to_string(214748));
	}else{
		denklem.insert(alt_sinir,to_string(pow(taban, derece)));
	}
}

double tur_kontrol(string &denklem){
	int uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='^'){
			us_al(i, denklem);
		}
	}
	uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]>='a' && denklem[i]<='z'){
			trigonometrik(i, denklem);
		}
	}
	uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='*'){
			carp(i, denklem);
		}
		if(denklem[i]=='/'){
			bol(i, denklem);
		}
	}
	uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='+'){
			topla(i, denklem);
		}
	}
	uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='-' && (denklem[i-1]>='0' && denklem[i-1]<='9')){
			cikar(i, denklem);
		}
	}
	islem_bitti_mi(denklem);
	return 0;
}

void parantezleri_sil(string& denklem){
	int acikPa=0, kapaliPa=0,aklinda_tut=0;
	int uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='('){
			acikPa++;
			aklinda_tut=i;
		}else if(denklem[i]==')'){
			kapaliPa++;
			if(acikPa==kapaliPa){
				string denklemParcasi = "";
				int parca_uzunlugu = i-aklinda_tut;
				for(int j=aklinda_tut+1; j<i; j++){
					denklemParcasi += denklem[j];
				}
				tur_kontrol(denklemParcasi);

				while(parca_uzunlugu>=0){
					denklem.erase(denklem.begin()+aklinda_tut);
					parca_uzunlugu--;
				}
				denklem.insert(aklinda_tut, denklemParcasi);
			}
		}
	}
	islem_bitti_mi(denklem);
}

int islem_kontrol(string denklem){
	int sayac1=0, sayac2=0;
	int uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='('){
			sayac1++;
		}else if(denklem[i]==')'){
			sayac2++;
		}
	}
	if(sayac1==0 && sayac2==0){
		return 1; // Parantez yok
	}else{
		if (sayac1-sayac2!=0){
			return 2;//Hatali parantez var
		}else{
			return 3;//Hata yok
		}
	}
}

double isleme_cevir(string& denklem){
	int secim = islem_kontrol(denklem);
	if(secim == 1){
		tur_kontrol(denklem);
	}else if(secim == 2){
		cout << "Parantez hatasi";
	}else{
		parantezleri_sil(denklem);
	}
	return 0;
}

void x_yok_et(double t, string &denklem){
	int uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='x' || denklem[i]=='u'){
			if(denklem[i-1]=='-'){
				denklem.erase(denklem.begin()+i-1);
				denklem.erase(denklem.begin()+i-1);
				denklem.insert(i-1, to_string(-1*t));
			}else{
				denklem.erase(denklem.begin()+i);
				denklem.insert(i, to_string(t));
			}

		}
	}
	uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){
		if(denklem[i]=='x' || denklem[i]=='u'){
			x_yok_et(t, denklem);
		}
	}
	isleme_cevir(denklem);
}

double sonucu_ver(double i, string denklem){

	x_yok_et(i,denklem);

	return stod(denklem);
}

void saymaya_basla(string denklem, vector<double>&sonuclar){
	double t=x_bit;
	while(t>=x_basl){
		sonuclar.push_back(sonucu_ver(t,denklem));
		t-=0.008;
	}
}

void islemeye_basla(){
	string denklem = kullanici_denklemi;
	int uzunluk = denklem.size();
	for(int i=0; i<uzunluk; i++){

		if(denklem[i]=='f'){
			if(denklem[i+2]=='x'){
				string fx_denklemi = "";
				int j=i+5;
				while(denklem[j]!=' ' && denklem[j]!='f' && denklem[j]!='g' && j<uzunluk){
					fx_denklemi+=denklem[j];
					j++;
				}
				fx_kontrol = true;
				saymaya_basla(fx_denklemi, sonuclar_fx);
			}
			if(denklem[i+2]=='y'){
				string fy_denklemi = "";
				int j=i+5;
				while(denklem[j]!=' ' && denklem[j]!='f' && denklem[j]!='g' && j<uzunluk){
					fy_denklemi+=denklem[j];
					j++;
				}
				fy_kontrol = true;
				saymaya_basla(fy_denklemi, sonuclar_fy);
			}
		}

		if(denklem[i]=='g'){
			if(denklem[i+2]=='x'){
				string gx_denklemi = "";
				int j=i+5;
				while(denklem[j]!=' ' && denklem[j]!='f' && denklem[j]!='g' && j<uzunluk){
					gx_denklemi+=denklem[j];
					j++;
				}
				gx_kontrol = true;
				saymaya_basla(gx_denklemi, sonuclar_gx);
			}
			if(denklem[i+2]=='y'){
				string gy_denklemi = "";
				int j=i+5;
				while(denklem[j]!=' ' && denklem[j]!='f' && denklem[j]!='g' && j<uzunluk){
					gy_denklemi+=denklem[j];
					j++;
				}
				gy_kontrol = true;
				saymaya_basla(gy_denklemi, sonuclar_gy);
			}
		}
	}
}

//=====================================================================Alt taraf girilen denklemi ekranda gosterir
void denklemMenuOlustur(){
	if(!font2.loadFromFile("calibril.ttf")){/*Yazinin olusabilmesi icin bu kosul gerekli*/};
	denklem_metni.setFont(font2);
	denklem_metni.setPosition(20,10);
	denklem_metni.setCharacterSize(30);
}

void denklemiMenuyeYerlestir(sf::RenderWindow &pencere){
	pencere.draw(denklem_metni);
}

#endif /* DENKLEM_OKUMA_H_ */




/*////////////////
f(x)= -5^x
f(x)= x^x


 *////////////

