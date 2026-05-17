# NumTool - Sayı Teorisi Hesaplama Aracı

`NumTool`, bir giriş dosyasından aldığı matematiksel komutları satır satır okuyarak işleyen ve sonuçları dinamik olarak hesaplayıp bir çıktı dosyasına yazan komut tabanlı bir sayı teorisi aracıdır.

---

## 🧮 Programın Yapabildiği İşlemler

Program, girdi dosyasından aldığı komutlara göre aşağıda belirtilen temel matematiksel ve mantıksal hesaplamaları yürütür:

* **EBOB (En Büyük Ortak Bölen) Hesaplama (`GCD`):** Girilen iki pozitif tam sayının ortak bölenlerinin en büyüğünü bulur.
* **Hızlı ve Modüler Üs Alma (`POW`):** Çok büyük sayılarda bile bellek taşması yaşatmadan, bir sayının üssünü alır ve belirtilen mod değerine göre kalanını hesaplar ($Taban^{\ddot{U}s} \pmod{Mod}$).
* **Asallık Kontrolü (`PRIME`):** Girilen bir sayının asal (sadece kendisine ve 1'e bölünen) olup olmadığını test eder.
* **Modüler Ters Hesaplama (`INV`):** Modüler aritmetikte $(A \cdot x) \pmod{M} = 1$ eşitliğini sağlayan pozitif $x$ sayısını (A'nın M modundaki tersini) bulur.
* **Euler Totient Fonksiyonu (`PHI`):** Belirtilen sayıya kadar olan pozitif tam sayılar arasından, o sayı ile aralarında asal (ortak böleni olmayan) kaç tane sayı olduğunu adet olarak hesaplar.
* **Doğruluk Testi (`CHECK`):** Hesaplanan modüler tersin sağlamasını yapar. Ters eleman ile orijinal sayıyı çarpıp modunu alır ve sonucun $1$ gelip gelmediğini doğrular.

---

## 📄 Çıktı Formatları ve Hata Yönetimi

Program çalıştırıldığında, her komut için girdi dosyasındaki sıraya uygun olarak çıktı dosyasına (`output.txt`) şu formatlarda sonuçlar yazar:


### 1. Başarılı İşlem Çıktıları
Hesaplamalar matematiksel kurallara uygun ve sorunsuz tamamlandığında doğrudan işlem ve sonucu basılır:


### 2. Hata Çıktıları (İstisnalar)
Matematiksel kurallara aykırı veya geçersiz bir girdi verildiğinde, program hata mesajı üreterek durumu güvenli bir şekilde çıktıya yansıtır:

* **`ERROR_INVALID_INPUT` (Geçersiz Girdi Hatası):** * `GCD` işlemine negatif veya sıfır sayı girildiğinde (Örn: `GCD -5 10 -> ERROR_INVALID_INPUT`),
  * `PRIME` işlemine 2'den küçük bir sayı sorulduğunda (Örn: `PRIME 1 -> ERROR_INVALID_INPUT`),
  * `PHI` işlemine 1'den küçük bir değer verildiğinde bu hata çıktısı alınır.
* **`ERROR_NO_INVERSE` (Modüler Ters Yok Hatası):** * `INV` işleminde girilen iki sayı aralarında asal değilse (yani ortak bölenleri varsa) sayının modüler tersi olamaz. Program bu durumda doğrudan bu hatayı basar (Örn: `INV 4 8 -> ERROR_NO_INVERSE`).

---

## ⚙️ Programın Çalışma Yapısı

Program, komut satırı argümanları (CLI) üzerinden bir giriş dosyasını okuyarak çalışır. Giriş dosyasındaki tüm matematiksel komutları sırasıyla ayrıştırır, arka planda dinamik veri yapıları (bellek yönetimi) kullanarak işler ve elde ettiği tüm sonuçları doğrudan bir çıktı dosyasına satır satır yazdırır.

---

## 💻 Windows İçin Önemli Gereksinim (WSL / Sanal İşletim Sistemi)

* **Zorunluluk:** Projenin derleme süreçlerini otomatize eden `Makefile` mimarisi, platformlar arası karmaşayı önlemek adına tamamen Linux standartlarına uygun tasarlanmıştır.
* **Çözüm:** Windows kullanıcılarının bu projeyi sorunsuz bir şekilde derleyip çalıştırabilmesi için **WSL (Windows Subsystem for Linux)** aracılığıyla kurulacak bir sanal Linux işletim sistemine ihtiyacı vardır. Derleme ve çalıştırma komutları bu sanal terminal üzerinden yürütülmelidir.
