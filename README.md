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

![Bit ayarlari](https://github.com/kynemre/Cpp/blob/master/bit.png?raw=true)

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

![Acilis ekrani](https://github.com/kynemre/Cpp/blob/master/Acilis.png?raw=true)

Bilgisayardan ekran boyutlariniz alır ve küçülterek pencereyi açar.

Denklem girebilmek için ve fonksiyonları seçebilmek için üst menü vardır.

Hangi fonksiyonun denklemi girilecekse belirtilir(f(x), f(y), g(x), g(y)).

Denklem yazilir ve enter tuşuna basılır. Program denklemi işlemeye çalışır fakat bu konuda fazla başarılı değildir.


![Koda denklem girme](https://github.com/kynemre/Cpp/blob/master/koda_denklem_gir.png?raw=true)

Karmaşık bir denklem girmek için yorum olan kod parçasını yorumdan çıkartıp x ve y koordinatlarına denklemleri girin.
x_koordinati f(y), y_koordinati f(x)'e denk gelir. g fonksiyonu için de bunu yapabilirsiniz.

Kalem, fareye tıklanırken her koordinatı değiştiğinde bir daire bırakır. Kalem ile şekiller çizilip yazılar yazılabilinir.
Dört farklı renk eklendi.

Silgi, fareye tıklanırken her kalem dairesinin üzerine geldiğinde onu görünmez yapar. 
Ekranın yakınlığı değiştirilebildiği, ekran taşınabildiği ve kalem çizgisinin daireleri bir dizi içinde olduğu için kalem dairesini silmez. Silmek diziyi ve diğer dairelerin özelliklerini bozar.

Tümünü sil fonksiyonu tüm kalem dairelerini siler.

Kaydetme çizilen cizgideki dairelerin tüm özelliklerini bir txt dosyası içine kaydeder ve açılışta program çizgiyi tekrar çizer.

Ekran boyutunu değiştirirken program bilgisayarın ekran boyutunu alır ve pencereyi ona göre tekrar başlatır.
Büyük ekran için ekran boyutuna göre açar, küçük ekran için ekran boyutunu bir oranla çarparak açar.


![İki Grafik](https://github.com/kynemre/Cpp/blob/master/ikigrafik.png?raw=true)

Aynı anda f ve g olarak iki denklemin grafiğinini çizebilir.
Üstel ve trigonometrik(sin, cos, tan, cot ,asin, acos, atan, acot) ifdade içeren denklemlerin grafiğini çizebilir.

![Parametrik](https://github.com/kynemre/Cpp/blob/master/parametrik.png?raw=true)

Parametrik denklemlerin grafiğini görmek isterseniz burada çizdirebilirsiniz.

