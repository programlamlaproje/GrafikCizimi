# Grafik Cizimi

Denklem grafiğini çizer. 
Denklemleri görsele dökebilir ve grafik üzerinde kalem ile işlemler yabalirsiniz.


# Kullanabilmek İçin

SFML kütüphanesi kullanmanız lazım. Kütüphaneyi indirirken derleyiciniz ile uyumlu olduğunu kontrol ediniz.
Kütüphaneyi indirmek için ;

https://www.sfml-dev.org/download/sfml/2.5.1/

Kütüphane indirildikten sonra projeye eklenmesi gerekiyor;

Eclipse icin kütüphaneyi projeye ekleme,

Projeyi import ettikten sonra proje gezgini üzerinde projeye sağ tıklayın ve Properties seçin.

Açılan pencerede C/C++ Build > Settings > Tool Settings > GCC C++ Compiler > Includes adımlarını izleyin ve Include Paths kısmındaki yeşil artı simgesine tıklayarak indirdiğiniz SFML kitaplığının include klasörünü yolunu ekleyin. 

Ardından C/C++ Build > Settings > Tool Settings > MinGW C++ Linker > Libraries(-L) yolunu izleyin. Açılan bölümde Library search path yeşil artı ikonuna tıklayarak SFML kütüphanesinin lib klasörün yolunu ekleyin.

Aynı ekranda Libraries(-l) şunları ekleyin: 
sfml-graphics 
sfml-window 
sfml-system 

Değişiklikleri kaydetmek için Uygula ve Tamam'ı tıklayın .

Projeyi derleyin ve SFML kütüphanesinin klasöründe bin klasöründeki tüm dosyaları kopyalayın. Kopyaladığınız dosyaları debug klasörünün içindeki exe dosyasının yanına yapıştırınız.

Programı çalıştırabilirsiniz.

Kütüphaneyi projeye eklemeyi daha ayrıntılı görmek için:
https://github.com/Peplow/SFML-and-Eclipse




Visual Studio icin kütüphaneyi projeye ekleme,

Grafik Çizimi projesinin kodlarını Visual Studio'ya entegre edin.
Proje gezgini üzerinde projeye sağ tıklayın ve Properties seçin. Eğer projeniz bit'i ile  Properties'deki platforms bit'i farklı ise aynı değerde olacak şekilde düzenleyin. 

![BitAyari](https://user-images.githubusercontent.com/46110671/81459953-fd65da80-91aa-11ea-8e40-cb75b22a07ea.png)

Açılan pencerede VC++ Directories bölümüne gidin. Bu bölümde Include Directories satırına edit diyerek düzenlemeyi açın. Sağ üstten yeni yol ekleye tıklayarak indirdiğiniz SFML kitaplığının include klasörünü yolunu ekleyin. Tamam'a tıklayın.

VC++ Directories bölümünde Library Directories satırına edit diyerek düzenlemeyi açın. Sağ üstten yeni yol ekleye tıklayarak indirdiğiniz SFML kitaplığının lib klasörünü yolunu ekleyin. Tamam'a tıklayın.

Properties kısmında Linker bölümünü açın. Bu bölümde Input kısmına gelin ve Additional Dependencies satırını düzenleye tıklayın.
Eğer relase modda çalışıyorsanız buraya
sfml-graphics.lib
sfml-window.lib
sfml-system.lib 
satırlarını ekleyin.

Debug modunda çlışıyorsanız
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib 
olarak ekleyin ve Tamam deyin.
Tamam'a tıklayarak kaydedin ve properties'i kapatın.

Projeyi derleyin. SFML kütüphanesinin klasöründe bin klasöründeki tüm dosyaları kopyalayın.  Ardından projenin kurulu olduğu klasöre giderek (x64 ya da x86)>  debug  klasörü içine yapıştırın. Eğer aynı dosyadan var ise değiştire tıklayın.

Programı çalıştırabilirsiniz.

# Grafik Cizimi Hakkında

Windows versiyonudur.

![AcilisEkrani](https://user-images.githubusercontent.com/46110671/81459982-271f0180-91ab-11ea-8393-5b224e817d6d.png)

Bilgisayardan ekran boyutlariniz alır ve küçülterek pencereyi açar.

Denklem girebilmek için ve fonksiyonları seçebilmek için üst menü vardır.

Hangi fonksiyonun denklemi girilecekse belirtilir(f(x), f(y), g(x), g(y), r1, r2).

Denklem yazilir ve enter tuşuna basılır.
*Denklem okuma kısmı henüz tamamlanmış değil.

Aynı anda f, g, r1 ve r2 olarak dört denklemin grafiğinini aynı anda çizebilir.
Üstel ve trigonometrik(sin, cos, tan, cot ,asin, acos, atan, acot) ifdade içeren denklemlerin grafiğini çizebilir.
