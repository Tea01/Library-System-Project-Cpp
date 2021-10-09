#include <iostream>
#include <locale.h>                                                          //diller ve karakter setleri için kütüphanesi
#include <fstream>                                                           //dosyalama yapabilmek için kütüphanesi
#include <string>
#include <chrono>                                                            //zamaný bulmak için kütüphanesi
#include <ctime>                                                             //zamaný  bulmak için kütüphanesi
#include <Windows.h>                                                         //çizgilerin koordinatlarý için kütüphanesi
#include <cmath>                                                             //zamaný hesaplamak için kütüphanesi
#include <iomanip>                                                           //manipülatör kullanmak için kütüphanesi

using namespace std;
using namespace std::chrono;                                                 //chrono kütüphanesini kullanabilmek için


//fonskiyonlarýn tanýmlamasý 
void cizgi();
void kullanicilar();
void Menu_Secenekler();
bool okuyucu_kontrol(string);
bool kitap_kontrol(string);
void OkuyucuBilgileri(string);
void GuncellemeOkuyucu(string);
void silmeOkuyucu(string);
void kitap_listesi(string);
void OduncAlma(string, string);
void kitapDondurme(string);
void EklemeKitap(string);
void SilmeKitap(string);
void DuzeltmeKitap(string);

//kullanýcýný bilgileri
struct bilgi {
	string adi_user, aditxt;                                                  //adi_user = girilen adý;       aditxt = sistemde kaydedilen adý
	int sifre, sifretxt;                                                     //sifre = girilen sifre;       sifretxt = sistemde kaydedilen sifre
}Kullanici;

//okuyucunun bilgileri, okuyucu.txt dosyasýnda yer alanacak
struct bilgiler {
	string TC_NO;
	string adi;
	string soyadi;
	string uyeNo;
	string telefon;
	string dogumTarihi;
	string gorevi;
	string alabilecegi_kitapSayisi;
}Okuyucu;

//kitap bilgileri, Kitaplar.txt dosyasýnda yer alanacak
struct bilgileri {
	string ISBN;
	string ismi;
	string yazar_adi;
	string yazar_soyadi;
	string konu;
	string tur;
	string sayfa_sayisi;
}Kitap;

char cevap = 'e';
int secenek;
string tc_no;
string isbn;
const int genislik = 115;

//dosyada bilgileri yazmak için
string tc = "TC NO...................: ";
string name = "ADI.....................: ";
string surname = "SOYADI..................: ";
string member = "ÜYE NO..................: ";
string phone = "TELEFON.................: ";
string bday = "DOÐUM TARIHI(GG/AA/YYYY): ";
string job = "GÖREVÝ..................: ";
string opp = "ALABÝLECEÐÝ KÝTAP SAYISI: ";

//kitaplar dosyada bilgileri yazmak için
string book_isbn = "Kitabýn ISBN..: ";
string book_name = "Kitabýn Adý...: ";
string writers_name = "Yazarin Adý...: ";
string writers_surname = "Yazarýn Soyadý: ";
string topic = "Konu..........: ";
string genre = "Tür...........: ";
string pages = "Sayfa Sayýsý..: ";


int main()
{
	setlocale(LC_ALL, "Turkish");                                  //Türkçe kullanmak için

	system("cls");

	auto start = chrono::system_clock::now();
	auto now = chrono::system_clock::to_time_t(start);
	char baslama_zamani[30];
	ctime_s(baslama_zamani, sizeof(baslama_zamani), &now);                                         //zaman kaydetilmeye baþlar

	cizgi();

	cout << endl << endl << setw(70) << "HOÞGELDÝNÝZ!\n\n\n";

	kullanicilar();

	cout << setw(56) << "Giriþ zamaný: " << baslama_zamani;

	if ((Kullanici.adi_user != Kullanici.aditxt) || (Kullanici.sifre != Kullanici.sifretxt))
	{
		auto now = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::to_time_t(now);
		char cikis_zamani[30];
		ctime_s(cikis_zamani, sizeof(cikis_zamani), &end);                                          //zaman kaydetilmeye biter

		cout << endl << setw(91) << "Girdiðiniz bilgiler için sistemde bir hesap yoktur.\n\n\n";

		cizgi();
		cin.get();

		cout << setw(55) << "Çýkýþ zamaný: " << cikis_zamani << endl << endl;

		system("PAUSE");
		return 0;
	}
	else
	{
		cizgi();
		cout << endl;

		Menu_Secenekler();

		auto now = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::to_time_t(now);
		char cikis_zamani[30];
		ctime_s(cikis_zamani, sizeof(cikis_zamani), &end);                                       //zaman kaydetilmeye biter


		cout << setw(54) << "Çýkýþ zamaný: " << cikis_zamani << endl << endl;
		cout << setw(69) << "ÝYÝ ÇALIÞMALAR DÝLERÝM!" << endl;

		cizgi();
		cout << endl;
	}
	cin.get();
	system("pause");
	return 0;
}


//Çizgi çizer fonksiyon
void cizgi() {

	for (int i = 0; i < genislik; i++)
	{
		cout << (char)017;
	}
}

//kullanýcý fonksiyonu
void kullanicilar() {
	ifstream kullanicilar;                                                   //kullanýcýlar dosyayý açar
	kullanicilar.open("kullanicilar.txt");

	cout << setw(71) << "Bilgilerini giriniz:" << endl;

	cout << setw(10) << "Adý: ";
	cin >> Kullanici.adi_user;
	cout << setw(12) << "Þifre: ";
	cin >> Kullanici.sifre;
	cout << "\n\n\n";

	kullanicilar >> Kullanici.aditxt >> Kullanici.sifretxt;                //kullanýcýlar dosyada bulunan bilgiler okur 
}


//Menu'da seçenekten seçmek için Menu_Secenekler fonskiyonu kullanýlacak 
void Menu_Secenekler()
{
	cout << endl << setw(80) << "KÜTÜPHANENÝN PROGRAMINDA HOÞ GELDÝNÝZ!" << endl << endl;
	do
	{
		cout << setw(55) << "Aþaðýdaki seçeneklerden birinin numarasýný girin." << endl << endl;

		cout << setw(20) << "1. Okuyucu kaydý." << endl;
		cout << setw(31) << "2. Okuyucu kaydý güncelleme." << endl;
		cout << setw(20) << "3. Okuyucu silme." << endl;
		cout << setw(42) << "4. Okuyucu üzerindeki kitaplar listesi." << endl;
		cout << setw(32) << "5. Okuyucu kitap ödünç alma. " << endl;
		cout << setw(35) << "6. Okuyucu kitap geri döndürme. " << endl;
		cout << setw(20) << "7. Kitap ekleme. " << endl;
		cout << setw(19) << "8. Kitap silme. " << endl;
		cout << setw(22) << "9. Kitap düzeltme. " << endl << endl;

		cout << setw(45) << "Hangi seçenekle devam etmek istiyorsunuz? ";
		cin >> secenek;

		switch (secenek)                                                           //hangi secenekle devam etmek istiyorsa onu seçip ve iþlemleri ile devam eder
		{
		case 1:
		{
			cout << setw(63) << "OKUYUCU KAYDI." << endl << endl;
			OkuyucuBilgileri(tc_no);
			break;
		}

		case 2:
		{
			cout << endl << endl << setw(70) << "OKUYUCU KAYDI GÜNCELLEME." << endl;
			cout << setw(16) << "TC No girin: ";
			cin >> tc_no;
			GuncellemeOkuyucu(tc_no);
			break;
		}

		case 3:
		{
			cout << endl << endl << setw(63) << "OKUYUCU SÝLME." << endl;
			cout << setw(25) << "Silenecek kiþi TC_NO: ";
			cin >> tc_no;
			silmeOkuyucu(tc_no);
			break;
		}
		case 4:
		{
			cout << setw(76) << "OKUYUCU ÜZERÝNDEKÝ KÝTAPLAR LÝSTESÝ." << endl;
			cout << setw(16) << "TC No girin: ";
			cin >> tc_no;
			kitap_listesi(tc_no);
			break;
		}
		case 5:
		{
			cout << endl << setw(70) << "OKUYUCU KÝTAP ÖDÜNÇ ALMA." << endl;
			cout << setw(27) << "Okuyucunun TC NO girin: ";
			cin >> tc_no;
			OduncAlma(tc_no, isbn);
			break;
		}
		case 6:
		{
			cout << endl << setw(70) << "OKUYUCU KÝTAP GERÝ DÖNDÜRME." << endl;
			cout << endl << setw(27) << "Okuyucunun TC No girin: ";
			cin >> tc_no;
			kitapDondurme(tc_no);
			break;
		}
		case 7:
		{
			cout << setw(62) << "KÝTAP EKLEME." << endl;
			EklemeKitap(isbn);
			break;
		}
		case 8:
		{
			cout << endl << setw(66) << "KÝTAP SÝLME." << endl;
			cout << endl << setw(23) << "Kitabýn ISBN girin: ";
			cin >> isbn;
			SilmeKitap(isbn);
			break;
		}
		case 9:
		{
			cout << endl << setw(67) << "KÝTAP DÜZELTME." << endl;
			cout << endl << setw(23) << "Kitabýn ISBN girin: ";
			cin >> isbn;
			DuzeltmeKitap(isbn);
			break;
		}
		default:
		{
			cout << setw(60) << "Hatalý bir iþlem sectiniz." << endl;
			break;
		}
		}
		cout << setw(48) << "Baþka bir iþlem yapmak ister misiniz (e/h) : ";
		cin >> cevap;
		cout << endl << endl << endl;

	} while (!(cevap == 'h'));
}

//Okuyucu sistemde kayýtlý olup olmadýðýný bulunan fonksiyonu
bool okuyucu_kontrol(string tc_no)
{
	bool control = 0;                                 //TC No sistemde kayýtlý deðilse 0 deðeri alýr.

	ifstream dosyaoku("okuyucu.txt", ios::app);

	while (!dosyaoku.eof())
	{
		string line;
		getline(dosyaoku, line);                             //okuyucu dosyada bulunan bilgileri okunur

		if (Okuyucu.TC_NO == tc_no)
		{
			control = 1;
		}
	}
	return control;
}

//Kitap sistemede kayýtlý olup olmadýðýný bulunan fonksiyonu
bool kitap_kontrol(string isbn)
{
	bool control = 0;                                     //ISBN sistemde kayýtlý deðilse 0 deðeri alýr

	ifstream dosyaoku("Kitaplar.txt", ios::app);

	while (!dosyaoku.eof())
	{
		string line;
		getline(dosyaoku, line);                         //Kitaplar dosyada bulunan bilgileri okunur

		if (Kitap.ISBN == isbn)
		{
			control = 1;
		}
	}
	return control;
}


//okuyucu bilgileri fonksiyonu. Bu fonsiyon ile okuyucuyu dosya üzerinde kaydetmektedir.
void OkuyucuBilgileri(string tc_no)
{
	do {
		ofstream dosyayaz;                                                 //okuyucu dosyayý açar
		dosyayaz.open("okuyucu.txt", ios::app);

		cout << setw(59) << "KONTROL!" << endl << endl;
		cout << setw(92) << "Okuyucu daha önce kayýt olup olmadýðýný kontrol etmek için TC numarasýný giriniz lütfen: ";
		cin >> tc_no;

		if (okuyucu_kontrol(tc_no) == 1)                                 // Kayýt kontrol fonksiyonu çaðýrýlarak okuyucu kaydýnýn olup olmadýðý sorgulanýr.
		{
			cout << setw(52) << "Bu TC kimlik numarasina sistemde ait bir okuyucu var.\n\a";
		}

		else
		{
			Okuyucu.TC_NO = tc_no;

			cout << endl << setw(104) << "Girdiðiniz TC numaraný için sistemde bir kayýt bulunmadý. Kayýt iþlemler ile devam edebilirsiniz :)" << endl << endl;

			cout << setw(29) << name;       cin >> Okuyucu.adi;                                          //okuyucunun bilgileri dýþarýdan alýnýr
			cout << setw(29) << surname;    cin >> Okuyucu.soyadi;
			cout << setw(29) << member;     cin >> Okuyucu.uyeNo;
			cout << setw(29) << phone;      cin >> Okuyucu.telefon;
			cout << setw(29) << bday;       cin >> Okuyucu.dogumTarihi;
			cout << setw(29) << job;        cin >> Okuyucu.gorevi;
			cout << setw(29) << opp;        cin >> Okuyucu.alabilecegi_kitapSayisi;

			//alýnan bilgileri okuyucu dosyasýnda kaydetmelidir.
			dosyayaz << tc << Okuyucu.TC_NO << "\n" << name << Okuyucu.adi << "\n" << surname << Okuyucu.soyadi << "\n" << member << Okuyucu.uyeNo << "\n" << phone << Okuyucu.telefon << "\n" << bday << Okuyucu.dogumTarihi << "\n" << job << Okuyucu.gorevi << "\n" << opp << Okuyucu.alabilecegi_kitapSayisi << "\n\n";

			cout << endl << setw(70) << "Okuyucu sistemde baþarýyla eklendi!\n\n";

		}
		cout << setw(53) << "Baþka bir okuyucu kaydetmek ister misiniz (e/h) : ";
		cin >> cevap;
		cout << endl << endl;

		dosyayaz.close();

	} while (!(cevap == 'h'));

}

// kaydý güncelleme fonksiyonu 
void GuncellemeOkuyucu(string tc_no)
{
	ifstream dosyaoku("okuyucu.txt");                                                          //okuyucu.txt den bilgileri okunacak 
	ofstream dosyayaz("okuyucu guncelleme.tmp", ios::app);                              //okuyucu guncelleme için temporary bir dosya açýlýr

	bool control = 0;

	if (okuyucu_kontrol(tc_no) == 0)                                     // Kayýt kontrol fonksiyonu çaðýrýlarak okuyucu kaydýnýn olup olmadýðý sorgulanýr
	{
		cout << endl << setw(54) << "Sistemde böyle bir TC kimlik numarasý bulunamadý.\n\a";
	}
	else
	{
		control = 1;

		string line;
		getline(dosyaoku, line);

		if (Okuyucu.TC_NO == tc_no)
		{
			int sayi;
			while (!(cevap == 'h'))
			{
				cout << endl << setw(24) << "Kayýt olduðu kiþi. \n\n";                                        //kayýt olduðu kiþinin bilgileri çikartýyor
				cout << setw(5) << right << "1." << tc << Okuyucu.TC_NO << endl;
				cout << setw(5) << right << "2." << name << Okuyucu.adi << endl;
				cout << setw(5) << right << "3." << surname << Okuyucu.soyadi << endl;
				cout << setw(5) << right << "4." << member << Okuyucu.uyeNo << endl;
				cout << setw(5) << right << "5." << phone << Okuyucu.telefon << endl;
				cout << setw(5) << right << "6." << bday << Okuyucu.dogumTarihi << endl;
				cout << setw(5) << right << "7." << job << Okuyucu.gorevi << endl;
				cout << setw(5) << right << "8." << opp << Okuyucu.alabilecegi_kitapSayisi << endl;


				cout << endl << setw(78) << "Hangi bilgi deðiþtirmek istiyorsunuz? (1-8): ";
				cin >> sayi;

				switch (sayi)                                               //hangi bilgi deðiþtirmek istiyor seçip onu ekrana yazar ve sonra yeni bilgieri tekrar alýr
				{
				case 1:
				{
					int number;
					cout << setw(59) << "Yeni bilgileri:\n";                  //her case de yazdým çünkü eðer switchin üstüne yazsam ve kullanýcý yanlýþ bir numara girerse o zaman hem "Yeni bilgileri" hem de "Yanlýþ bir seçim yaptýný.." metni çýkacak
					cout << setw(31) << tc;
					cin >> Okuyucu.TC_NO;
					break;
				}
				case 2:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << name;
					cin >> Okuyucu.adi;
					break;
				}
				case 3:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << surname;
					cin >> Okuyucu.soyadi;
					break;
				}
				case 4:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << member;
					cin >> Okuyucu.uyeNo;
					break;
				}
				case 5:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << phone;
					cin >> Okuyucu.telefon;
					break;
				}
				case 6:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << bday;
					cin >> Okuyucu.dogumTarihi;
					break;
				}
				case 7:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << job;
					cin >> Okuyucu.gorevi;
					break;
				}
				case 8:
				{
					cout << endl << setw(59) << "Yeni bilgileri:\n";
					cout << setw(31) << opp;
					cin >> Okuyucu.alabilecegi_kitapSayisi;
					break;
				}
				default:
				{
					cout << endl << setw(69) << "Yanlýþ bir seçim yaptýnýz..." << endl;
					break;
				}
				}
				cout << endl << setw(53) << "Baþka bir deðiþim yapmak istiyor musunuz? (e/h): ";
				cin >> cevap;
				cout << endl;
			};

			while (dosyaoku.eof())	break;          // En son kaydýn 2 kere okuyup yazýlmamasý için eklendi.

			dosyayaz << tc << Okuyucu.TC_NO << endl << name << Okuyucu.adi << endl << surname << Okuyucu.soyadi << endl << member << Okuyucu.uyeNo << endl << phone << Okuyucu.telefon << endl << bday << Okuyucu.dogumTarihi << endl << job << Okuyucu.gorevi << endl << opp << Okuyucu.alabilecegi_kitapSayisi << endl << endl;
		}
		else
		{
			while (dosyaoku.eof())	break;          // En son kaydýn 2 kere okuyup yazýlmamasý için eklendi.

			dosyayaz << tc << Okuyucu.TC_NO << endl << name << Okuyucu.adi << endl << surname << Okuyucu.soyadi << endl << member << Okuyucu.uyeNo << endl << phone << Okuyucu.telefon << endl << bday << Okuyucu.dogumTarihi << endl << job << Okuyucu.gorevi << endl << opp << Okuyucu.alabilecegi_kitapSayisi << endl << endl;
		}

		dosyaoku.close();
		dosyayaz.close();

		if (control == 1)             // Programda kayýt varsa yapýlan deðiþikliklerin dosya üzerine yazýlmasý saðlandý.
		{
			remove("okuyucu.txt");                                    //okuyucu dosyayý siliyor
			rename("okuyucu guncelleme.tmp", "okuyucu.txt");         //okuyucu guncelleme -> okuyucu dosyayý yapar
			cout << setw(75) << "OKUYUCUNUN BÝLGÝLERÝ GÜNCELLENDÝ :)\n\n";
		}
		else
		{
			remove("okuyucu guncelleme.tmp");                       //okuyucu guncelleme dosyayý siler
		}
	}
}


//Okuyucu silme fonksiyonu
void silmeOkuyucu(string tc_no)
{
	ifstream dosyaoku("okuyucu.txt");                                 //okuyucu dosyadan bilgi okunacak
	ofstream dosyayaz("okuyucu sil.tmp", ios::app);                   //okuyucu silmek için temporary bir dosya açýldý
	ifstream oduncoku("Odunc.txt");                                   //odunc dosyadan bilgileri okunacak

	bool control = 0;

	if (okuyucu_kontrol(tc_no) == 0)                                  // okuyucu kayýt olup olmadýðýný kontrol eder
	{
		cout << setw(77) << "Sistemde bu TC Kimlik numarasý bulunmadý. :/" << endl << endl;
	}
	else
	{
		control = 1;

		while (true)
		{
			string line;
			getline(dosyaoku, line);                        //okuyucu dosyadan bilgileri okur

			if (Okuyucu.TC_NO != tc_no)                 //girilen tc no ve dosyadaki bulunan tc no ayný olup olmadýðýný kontrol eder
			{
				if (dosyaoku.eof())      break;

				dosyayaz << tc << Okuyucu.TC_NO << endl << name << Okuyucu.adi << endl << surname << Okuyucu.soyadi << endl << member << Okuyucu.uyeNo << endl << phone << Okuyucu.telefon << endl << bday << Okuyucu.dogumTarihi << endl << job << Okuyucu.gorevi << endl << opp << Okuyucu.alabilecegi_kitapSayisi << endl << endl;
			}
			else if (Okuyucu.TC_NO == tc_no)
			{
				cout << endl << setw(6) << Okuyucu.adi << " " << Okuyucu.soyadi << " sistemden silmek için emin misiniz? (e/h): ";
				cin >> cevap;
				if (true)
				{
					if (!(cevap == 'h'))
					{
						string line;
						getline(dosyaoku, line);

						if (oduncoku.is_open())                                          //odunc dosyayý açýk olup olmadýðýný kontrol eder
						{
							cout << endl << setw(75) << "Silinecek okuyucunun üzerindeki ödünçler: \n";
							for (int lineno = 1; getline(oduncoku, line) && lineno < 100; lineno + 8)         //bulunan oduncleri dýþarýda yazar
								cout << line << endl;

							dosyaoku.close();
							dosyayaz.close();
							oduncoku.close();
							remove("okuyucu.txt");                                        //okuyucu dosyayý siler
							rename("okuyucu sil.tmp", "okuyucu.txt");                     //okuyucu sil dosyayý ->okuyucu dosyaya çevirir
							cout << "\nKAYIT BAÞARIYLA SÝLÝNDÝ." << endl;
							break;
						}
						else
						{
							cout << endl << setw(75) << "Okuyucunun üzerindeki ödünçler yoktur.\n\n";
						}

					}
					else
					{
						dosyaoku.close();
						dosyayaz.close();
						remove("okuyucu sil.tmp");                                      //okuyucu sil dosyayý siler
					}
					break;
				}
			}
		}
	}
	dosyaoku.close();
	dosyayaz.close();
	oduncoku.close();
	remove("okuyucu.txt");
	rename("okuyucu sil.tmp", "okuyucu.txt");
}


//Okuyucu üzerindeki kitaplar listesi
void kitap_listesi(string tc_no)
{
	ifstream okuyucuoku("okuyucu.txt");                     //okuyucu dosyayý okur
	ifstream oduncoku("Odunc.txt");                         //odunc dosyayý okur
	ifstream kitapoku("Kitaplar odunc.tmp");                //kitaplar odunc dosyadan bilgileri okur

	bool control = 0;

	string line;
	getline(okuyucuoku, line);                         //okuyucu dosyanda bulunan bilgileri okunur

	if (okuyucu_kontrol(tc_no) == 0)                   // girilen tc no, okuyucu dosyada bulunan tc no ayný olup olmadýðýný kontrol eder
	{
		cout << endl << setw(82) << "Girdiðiniz deðerler için bir kayýt bulunmadý :/" << endl;
	}

	else
	{
		if (!oduncoku.is_open())                            //odunc dosya açýk olup olmadýðýný kontrol ederiz. açýk deðilse kitaplar yoktur.
		{
			cout << endl << setw(65) << "Okuyucun üzerindeki kitap bulunmadý.\n\n";
		}
		else
		{
			for (int lineno = 1; getline(kitapoku, line) && lineno < 100; lineno + 8)         //kitap odunc bulunan bilgileri okur
				cout << line << endl;

		}
	}
	okuyucuoku.close();
	oduncoku.close();
	kitapoku.close();
	remove("Odunc.txt");                                                 //odunc dosyayý siler
	rename("Kitaplar odunc.tmp", "Odunc.txt");                           //kitaplar odunc tmp dosyayý ->odunc dosyaya çevirir.
}

//Okuyucu kitap ödünç alma fonksiyonu
void OduncAlma(string tc_no, string isbn)
{
	do
	{
		ofstream dosyayaz("Odunc.txt", ios::app);            //odunc dosyayý açýp yazacak
		ifstream dosyaoku("okuyucu.txt");                    //okuyucu dosyadan bilgileri okur
		ifstream kitapoku("Kitaplar.txt");                  //Kitaplar dosyadan bilgileri okur
		ofstream kitapyaz("Kitaplar odunc.tmp", ios::app);   //kitaplar odun temporary dosyayý açýp yazar

		bool control = 0;

		if (okuyucu_kontrol(tc_no) == 0)                       //girilen tc no kotrol eder. sistemde kayýt var mý yok mu. yoksa yeni bir kayýt oluþtur
		{
			cout << endl << setw(66) << "Sistemde bu TC NO ile okuyucu bulunmadý. Yeni kayýt oluþturun:\n";
			ofstream dosyayaz("okuyucu.txt", ios::app);                                             //okuyucu dosyaya yeni kayýt olan okuyucuyu yazar

			Okuyucu.TC_NO = tc_no;
			cout << setw(29) << name;       cin >> Okuyucu.adi;
			cout << setw(29) << surname;    cin >> Okuyucu.soyadi;
			cout << setw(29) << member;     cin >> Okuyucu.uyeNo;
			cout << setw(29) << phone;      cin >> Okuyucu.telefon;
			cout << setw(29) << bday;       cin >> Okuyucu.dogumTarihi;
			cout << setw(29) << job;        cin >> Okuyucu.gorevi;
			cout << setw(29) << opp;        cin >> Okuyucu.alabilecegi_kitapSayisi;

			dosyayaz << tc << Okuyucu.TC_NO << "\n" << name << Okuyucu.adi << "\n" << surname << Okuyucu.soyadi << "\n" << member << Okuyucu.uyeNo << "\n" << phone << Okuyucu.telefon << "\n" << bday << Okuyucu.dogumTarihi << "\n" << job << Okuyucu.gorevi << "\n" << opp << Okuyucu.alabilecegi_kitapSayisi << "\n";

			cout << endl << setw(75) << "Okuyucu sistemde baþarýyla eklendi!\n";

			dosyayaz.close();
		}
		else
		{
			string line;                                      //Kitaplar dosyadan bilgileri okur
			getline(kitapoku, line);

			cout << setw(81) << "Kitap kütüphanede olup olmadýðý kontrol etmek için lütfen kitabýn ISBN girin: ";
			cin >> isbn;

			if (kitap_kontrol(isbn) == 0)                                                 //istenilen kitap kütüphanede olup olmadýðýný kontrol eder
			{
				cout << endl << setw(70) << "Bu kitap kütüphanede bulunmadý.\n\a";
			}
			else if (true)
			{

				Kitap.ISBN = isbn;

				string line;                              //okuyucu bilgilerini okur
				getline(dosyaoku, line);

				cout << endl << setw(16) << "Kitabýn ismi: " << Kitap.ismi << endl;

				auto start = chrono::system_clock::now();                                //odunc ne zaman aldýðýný yazar
				auto now = chrono::system_clock::to_time_t(start);
				char odunc_tarihi[30];
				ctime_s(odunc_tarihi, sizeof(odunc_tarihi), &now);
				cout << setw(26) << "Ödünc Tarihi..........: " << odunc_tarihi;

				if (dosyayaz.eof())	break;                                               // En son kaydýn 2 kere okuyup yazýlmamasý için eklendi.
				dosyayaz << "Kitabýn ISBN: " << Kitap.ISBN << endl << "Okuyucunun TC NO: " << Okuyucu.TC_NO << endl << "Ödünç alma tarihi: " << odunc_tarihi;

				if (true)
				{
					auto now = std::chrono::system_clock::now();
					auto t_c = std::chrono::system_clock::to_time_t(now + 336h);                           //oduncun dönüþ SON TARIHI ne zaman olacaðýný hesaplanýp yazar
					char bitis_tarihi[30];
					ctime_s(bitis_tarihi, sizeof(bitis_tarihi), &t_c);
					cout << setw(26) << "Dönüþ son tarihi......: " << bitis_tarihi;
					cout << endl << setw(90) << "BU TARÝHTEN SONRA OKUYUCU KÝTABI GERÝ DÖNDÜRMEZSE CEZA ALIR!!\n";
					dosyayaz << "Dönüþ SON tarihi: " << bitis_tarihi << endl;
				}

				cout << endl << setw(70) << "Kitap ödünc olarak alýndý.\n\n";

				//Kitap artýk ödünç olarak alýndýðýndan, kitap kütüphane kitaplarýndan silinmelidir
				kitapyaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;
				kitapoku.close();
				kitapyaz.close();
				remove("Kitaplar.txt");
			}
		}
		cout << endl << setw(39) << "Baþka bir ödünc alýnacak mý? (e/h): ";
		cin >> cevap;

		dosyaoku.close();
		kitapoku.close();
		dosyayaz.close();
		kitapyaz.close();
	} while (!(cevap == 'h'));
}

//okuyucu kitap döndürme fonksiyonu
void kitapDondurme(string tc_no)
{
	ifstream okuyucuoku("okuyucu.txt");                                             //okuyucu dosyadan bilgiler okur
	ifstream dosyaoku("Kitaplar odunc.tmp");                                        //kitaplar odunc dosyadan bilgileri okur
	ofstream dosyayaz("Kitaplar.txt", ios::app);                                    //kitaplar dosyaya bilgileri yazar
	ifstream oduncoku("Odunc.txt");                                                 //odunc dosyadan bilgileri okur
	ofstream oduncyaz("Odunc sil.tmp", ios::app);                                   //odunc sil dosyaya yazar

	bool control = 0;

	string line;                                                     //okuyucu dosyadan biligleri okur
	getline(okuyucuoku, line);

	if (okuyucu_kontrol(tc_no) == 0)                                  //girilen tc no sistemde bulunan tc no ayný olup olmadýðýný kontrol eder
	{
		cout << endl << setw(82) << "Girdiðiniz deðerler için bir kayýt bulunmadý :/" << endl;
	}
	else
	{
		if (true)
		{
			cout << endl;
			string line;

			auto start = chrono::system_clock::now();                           //oduncun donuþ tarihini yazar
			auto now = chrono::system_clock::to_time_t(start);
			char donus_tarihi[30];
			ctime_s(donus_tarihi, sizeof(donus_tarihi), &now);
			cout << setw(18) << "Dönüþ tarihi: " << donus_tarihi << endl;

			while (getline(oduncoku, line))
			{
				cout << line << endl;
				oduncyaz << line << endl;                             //odunc dosyadan bilgileri okur
			}


			while (getline(dosyaoku, line))
			{
				cout << line << endl;
				dosyayaz << line << endl;                           //odunc sil dosyadan bilgileri okur
			}

			cout << endl << setw(100) << "Alýnan kitap son teslim tarihinden önce iade edildi. Kitabýn bilgileri sisteme ekleniyor...\n\n";

		}
		okuyucuoku.close();
		dosyaoku.close();
		dosyayaz.close();
		remove("Kitaplar odunc.tmp");
		oduncoku.close();
		oduncyaz.close();
		remove("Odunc.txt");
		rename("Odunc sil.tmp", "Odunc.txt");
	}
	oduncoku.close();
	oduncyaz.close();
	remove("Odunc.txt");
	rename("Odunc sil.tmp", "Odunc.txt");
}

//Kitap ekleme fonksiyonu
void EklemeKitap(string isbn)
{
	do {
		ofstream dosyayaz;
		dosyayaz.open("Kitaplar.txt", ios::app);                                      //kitaplar dosyayý açýp yazar

		cout << endl << setw(59) << "KONTROL!" << endl;
		cout << setw(101) << "Kitap daha önce sistemde kayýt olup olmadýðýný kontrol etmek için ISBN numarasýný giriniz lütfen: ";
		cin >> isbn;

		if (kitap_kontrol(isbn) == 1)                                      //Kitap daha önce sisteme kayýt olup olmadýðýný kontrol edebilmek için
		{
			cout << "Sistemde bu ÝSBN numarasýna ait bir kitap var.\n\a";
		}
		else                                                           //kitap sisteme eklenir
		{
			Kitap.ISBN = isbn;

			cout << endl << setw(104) << "Girdiðiniz ISBN numaraný için sistemde bir kayýt bulunmadý. Kayýt iþlemler ile devam edebilirsiniz :)" << endl << endl;

			cin.ignore();
			cout << setw(19) << book_name;                    getline(cin, Kitap.ismi);
			cout << setw(19) << writers_name;                 getline(cin, Kitap.yazar_adi);
			cout << setw(19) << writers_surname;              getline(cin, Kitap.yazar_soyadi);
			cout << setw(19) << topic;                        getline(cin, Kitap.konu);
			cout << setw(19) << genre;                        getline(cin, Kitap.tur);
			cout << setw(19) << pages;                        cin >> Kitap.sayfa_sayisi;

			dosyayaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;

			cout << endl << setw(73) << "Kitap sistemde baþarýyla eklendi!\n";
		}
		dosyayaz.close();

		cout << endl << setw(49) << "Baþka bir kitap eklemek ister misiniz? (e/h): ";
		cin >> cevap;
		cout << endl << endl;

	} while (!(cevap == 'h'));

}

//Kitap Silme fonksiyonu
void SilmeKitap(string isbn)
{
	ifstream  dosyaoku("Kitaplar.txt");                             //kitaplar dosyadan bilgileri okur
	ofstream dosyayaz("Kitaplar sil.tmp");                          //kitaplar sil dosyaya bilgileri yazar

	bool control = 0;

	if (kitap_kontrol(isbn) == 0)                    //girilen isbn aynýsýný sistemde olup olmadýðýný kotrol eder
	{
		cout << endl << setw(77) << "Sistemde bu ÝSBN bulunmadý.\n\a ";
	}
	else
	{
		control = 1;

		while (true)
		{
			string line;                                              //kitaplar dosyadan bilgileri okur
			getline(dosyaoku, line);

			if (Kitap.ISBN != isbn)                                  //eðer girilen isbn sisteminin bulunan isbn ayný deðilse kitaplar dosyadan okuduðu bilgileri kitaplar sil dosyaya yazar        
			{
				if (dosyaoku.eof())      break;
				dosyayaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;

			}
			else if (Kitap.ISBN == isbn)                                                 //eþitse silme iþlemleri ile devam eder
			{
				cout << setw(8) << Kitap.ismi << " sistemden silmek için emin misiniz? (e/h): ";                          //silme iþlemi yapmapaya emin olup olmadýðýný sorar
				cin >> cevap;
				if (true)
				{
					if (!(cevap == 'h'))
					{
						dosyaoku.close();
						dosyayaz.close();
						remove("Kitaplar.txt");                                         //kitaplar dosyayý siler
						rename("Kitaplar sil.tmp", "Kitaplar.txt");                     //kitaplar sil tmp dosyayý ->kitaplar dosyasýnda çevirir
						cout << endl << setw(73) << "KAYIT BAÞARIYLA SÝLÝNDÝ." << endl;
						break;
					}
					else
					{
						dosyaoku.close();
						dosyayaz.close();
						remove("Kitaplar sil.tmp");                                     //kitaplar sil dosyayý siler
					}
					break;
				}
			}
		}
	}
};

//Kitap Düzeltme fonksiyonu
void DuzeltmeKitap(string isbn)
{
	ifstream dosyaoku("Kitaplar.txt");                                       //kitaplar dosyadan bilgileri okur
	ofstream dosyayaz("Kitaplar duzeltme.tmp");                              //kitaplat duzeltme temporary dosyaya bligileri yazar

	bool control = 0;

	if (kitap_kontrol(isbn) == 0)                                           //girilen isbn sistemde olup olmadýðýný kontrol eder
	{
		cout << setw(58) << "Sistemde bu ÝSBN numarasýna ait bir kitap bulunamadý.\n\a";
	}
	else
	{
		control = 1;

		string line;                                                        //kitaplar dosyadan bilgileri yazar
		getline(dosyaoku, line);

		if (Kitap.ISBN == isbn)
		{
			int sayi;
			do
			{
				cout << endl << setw(24) << "Kayýt olduðu kitap: \n" << endl;
				//kayýt olduðu kitabýn bilgilerini yazar
				cout << setw(5) << right << "1." << book_isbn << Kitap.ISBN << endl;;
				cout << setw(5) << right << "2." << book_name << Kitap.ismi << endl;
				cout << setw(5) << right << "3." << writers_name << Kitap.yazar_adi << endl;
				cout << setw(5) << right << "4." << writers_surname << Kitap.yazar_soyadi << endl;
				cout << setw(5) << right << "5." << topic << Kitap.konu << endl;
				cout << setw(5) << right << "6." << genre << Kitap.tur << endl;
				cout << setw(5) << right << "7." << pages << Kitap.sayfa_sayisi << endl;

				cout << setw(48) << "Hangi bilgi deðiþtirmek istiyorsunuz? (1-7): ";
				cin >> sayi;

				switch (sayi)                                                        //hangi bilgi deðiþtirmek istiyor seçip onu ekrana yazar
				{
				case 1:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << book_isbn;
					cin >> Kitap.ISBN;
					break;
				}
				case 2:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << book_name;
					cin >> Kitap.ismi;
					break;
				}
				case 3:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << writers_name;
					cin >> Kitap.yazar_adi;
					break;
				}
				case 4:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << writers_surname;
					cin >> Kitap.yazar_soyadi;
					break;
				}
				case 5:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << topic;
					cin >> Kitap.konu;
					break;
				}
				case 6:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << genre;
					cin >> Kitap.tur;
					break;
				}
				case 7:
				{
					cout << endl << setw(67) << "Yeni bilgileri:\n";
					cout << setw(19) << pages;
					cin >> Kitap.sayfa_sayisi;
					break;
				}
				default:
				{
					cout << endl << setw(72) << "Yanlýþ bir seçim yaptýnýz..." << endl;
					break;
				}
				}
				cout << endl << setw(53) << "Baþka bir deðiþim yapmak istiyor musunuz? (e/h): ";
				cin >> cevap;
				cout << endl;
			} while (!(cevap == 'h'));

			while (dosyaoku.eof())    break;
			//Kitaplar duzeltme dosyaya bilgileri yazar
			dosyayaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;

		}
		else
		{
			while (dosyaoku.eof())   break;

			dosyayaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;
		}
		dosyaoku.close();
		dosyayaz.close();

		if (control == 1)
		{
			remove("Kitaplar.txt");                                                         //kitaplar dosyayý siler
			rename("Kitaplar duzeltme.tmp", "Kitaplar.txt");                                //kitaplar duzeltme tmp dosyayý ->kitaplar dosyaya çevirir
			cout << endl << setw(65) << "Kitabýn bilgileri güncellendi :)\n";
		}
		else
		{
			remove("Kitaplar duzelte.tmp");                                               //kitaplar suzeltme dosyayý siler
		}
	}
}
