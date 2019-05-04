# GrafikCizimi

Yazılan denklemin grafiğini çizer.

SFML kütüphanesi kullanarak yapılmıştır. Kütüphaneyi indirmek için ;

https://www.sfml-dev.org/download/sfml/2.5.1/

Kütüphane indirildikten sonra projeye eklenmesi gerekiyor;

Projeyi import ettikten sonra proje gezgini üzerinde projeye sağ tıklayın ve Properties seçin.

İnclude klasörünü ekleyin.
C/C++ Build > Settings > Tool Settings > GCC C++ Compiler > Includes Yeşil artı simgesine tıklayarak SFML kitaplığının include klasörünü bulun ve yolu ekleyin. 

Lib klasörünü ekleyin.
C/C++ Build > Settings > Tool Settings > MinGW C++ Linker > Libraries(-L) yolunu izleyin. Altında Library search path yeşil artı-ikonuna tıklayarak SFML kütüphanesinin lib klasörün yolunu ekleyin.

Altında Libraries(-l) şunları ekleyin: 
sfml-graphics 
sfml-window 
sfml-system 
Değişiklikleri kaydetmek için Uygula ve Tamam'ı tıklayın .

2019 Bahar Dönemi Programlama Projesi
