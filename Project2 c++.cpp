#include <iostream>
#include <locale.h>                                                          //diller ve karakter setleri i�in k�t�phanesi
#include <fstream>                                                           //dosyalama yapabilmek i�in k�t�phanesi
#include <string>
#include <chrono>                                                            //zaman� bulmak i�in k�t�phanesi
#include <ctime>                                                             //zaman�  bulmak i�in k�t�phanesi
#include <Windows.h>                                                         //�izgilerin koordinatlar� i�in k�t�phanesi
#include <cmath>                                                             //zaman� hesaplamak i�in k�t�phanesi
#include <iomanip>                                                           //manip�lat�r kullanmak i�in k�t�phanesi

using namespace std;
using namespace std::chrono;                                                 //chrono k�t�phanesini kullanabilmek i�in


//fonskiyonlar�n tan�mlamas� 
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

//kullan�c�n� bilgileri
struct bilgi {
	string adi_user, aditxt;                                                  //adi_user = girilen ad�;       aditxt = sistemde kaydedilen ad�
	int sifre, sifretxt;                                                     //sifre = girilen sifre;       sifretxt = sistemde kaydedilen sifre
}Kullanici;

//okuyucunun bilgileri, okuyucu.txt dosyas�nda yer alanacak
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

//kitap bilgileri, Kitaplar.txt dosyas�nda yer alanacak
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

//dosyada bilgileri yazmak i�in
string tc = "TC NO...................: ";
string name = "ADI.....................: ";
string surname = "SOYADI..................: ";
string member = "�YE NO..................: ";
string phone = "TELEFON.................: ";
string bday = "DO�UM TARIHI(GG/AA/YYYY): ";
string job = "G�REV�..................: ";
string opp = "ALAB�LECE�� K�TAP SAYISI: ";

//kitaplar dosyada bilgileri yazmak i�in
string book_isbn = "Kitab�n ISBN..: ";
string book_name = "Kitab�n Ad�...: ";
string writers_name = "Yazarin Ad�...: ";
string writers_surname = "Yazar�n Soyad�: ";
string topic = "Konu..........: ";
string genre = "T�r...........: ";
string pages = "Sayfa Say�s�..: ";


int main()
{
	setlocale(LC_ALL, "Turkish");                                  //T�rk�e kullanmak i�in

	system("cls");

	auto start = chrono::system_clock::now();
	auto now = chrono::system_clock::to_time_t(start);
	char baslama_zamani[30];
	ctime_s(baslama_zamani, sizeof(baslama_zamani), &now);                                         //zaman kaydetilmeye ba�lar

	cizgi();

	cout << endl << endl << setw(70) << "HO�GELD�N�Z!\n\n\n";

	kullanicilar();

	cout << setw(56) << "Giri� zaman�: " << baslama_zamani;

	if ((Kullanici.adi_user != Kullanici.aditxt) || (Kullanici.sifre != Kullanici.sifretxt))
	{
		auto now = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::to_time_t(now);
		char cikis_zamani[30];
		ctime_s(cikis_zamani, sizeof(cikis_zamani), &end);                                          //zaman kaydetilmeye biter

		cout << endl << setw(91) << "Girdi�iniz bilgiler i�in sistemde bir hesap yoktur.\n\n\n";

		cizgi();
		cin.get();

		cout << setw(55) << "��k�� zaman�: " << cikis_zamani << endl << endl;

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


		cout << setw(54) << "��k�� zaman�: " << cikis_zamani << endl << endl;
		cout << setw(69) << "�Y� �ALI�MALAR D�LER�M!" << endl;

		cizgi();
		cout << endl;
	}
	cin.get();
	system("pause");
	return 0;
}


//�izgi �izer fonksiyon
void cizgi() {

	for (int i = 0; i < genislik; i++)
	{
		cout << (char)017;
	}
}

//kullan�c� fonksiyonu
void kullanicilar() {
	ifstream kullanicilar;                                                   //kullan�c�lar dosyay� a�ar
	kullanicilar.open("kullanicilar.txt");

	cout << setw(71) << "Bilgilerini giriniz:" << endl;

	cout << setw(10) << "Ad�: ";
	cin >> Kullanici.adi_user;
	cout << setw(12) << "�ifre: ";
	cin >> Kullanici.sifre;
	cout << "\n\n\n";

	kullanicilar >> Kullanici.aditxt >> Kullanici.sifretxt;                //kullan�c�lar dosyada bulunan bilgiler okur 
}


//Menu'da se�enekten se�mek i�in Menu_Secenekler fonskiyonu kullan�lacak 
void Menu_Secenekler()
{
	cout << endl << setw(80) << "K�T�PHANEN�N PROGRAMINDA HO� GELD�N�Z!" << endl << endl;
	do
	{
		cout << setw(55) << "A�a��daki se�eneklerden birinin numaras�n� girin." << endl << endl;

		cout << setw(20) << "1. Okuyucu kayd�." << endl;
		cout << setw(31) << "2. Okuyucu kayd� g�ncelleme." << endl;
		cout << setw(20) << "3. Okuyucu silme." << endl;
		cout << setw(42) << "4. Okuyucu �zerindeki kitaplar listesi." << endl;
		cout << setw(32) << "5. Okuyucu kitap �d�n� alma. " << endl;
		cout << setw(35) << "6. Okuyucu kitap geri d�nd�rme. " << endl;
		cout << setw(20) << "7. Kitap ekleme. " << endl;
		cout << setw(19) << "8. Kitap silme. " << endl;
		cout << setw(22) << "9. Kitap d�zeltme. " << endl << endl;

		cout << setw(45) << "Hangi se�enekle devam etmek istiyorsunuz? ";
		cin >> secenek;

		switch (secenek)                                                           //hangi secenekle devam etmek istiyorsa onu se�ip ve i�lemleri ile devam eder
		{
		case 1:
		{
			cout << setw(63) << "OKUYUCU KAYDI." << endl << endl;
			OkuyucuBilgileri(tc_no);
			break;
		}

		case 2:
		{
			cout << endl << endl << setw(70) << "OKUYUCU KAYDI G�NCELLEME." << endl;
			cout << setw(16) << "TC No girin: ";
			cin >> tc_no;
			GuncellemeOkuyucu(tc_no);
			break;
		}

		case 3:
		{
			cout << endl << endl << setw(63) << "OKUYUCU S�LME." << endl;
			cout << setw(25) << "Silenecek ki�i TC_NO: ";
			cin >> tc_no;
			silmeOkuyucu(tc_no);
			break;
		}
		case 4:
		{
			cout << setw(76) << "OKUYUCU �ZER�NDEK� K�TAPLAR L�STES�." << endl;
			cout << setw(16) << "TC No girin: ";
			cin >> tc_no;
			kitap_listesi(tc_no);
			break;
		}
		case 5:
		{
			cout << endl << setw(70) << "OKUYUCU K�TAP �D�N� ALMA." << endl;
			cout << setw(27) << "Okuyucunun TC NO girin: ";
			cin >> tc_no;
			OduncAlma(tc_no, isbn);
			break;
		}
		case 6:
		{
			cout << endl << setw(70) << "OKUYUCU K�TAP GER� D�ND�RME." << endl;
			cout << endl << setw(27) << "Okuyucunun TC No girin: ";
			cin >> tc_no;
			kitapDondurme(tc_no);
			break;
		}
		case 7:
		{
			cout << setw(62) << "K�TAP EKLEME." << endl;
			EklemeKitap(isbn);
			break;
		}
		case 8:
		{
			cout << endl << setw(66) << "K�TAP S�LME." << endl;
			cout << endl << setw(23) << "Kitab�n ISBN girin: ";
			cin >> isbn;
			SilmeKitap(isbn);
			break;
		}
		case 9:
		{
			cout << endl << setw(67) << "K�TAP D�ZELTME." << endl;
			cout << endl << setw(23) << "Kitab�n ISBN girin: ";
			cin >> isbn;
			DuzeltmeKitap(isbn);
			break;
		}
		default:
		{
			cout << setw(60) << "Hatal� bir i�lem sectiniz." << endl;
			break;
		}
		}
		cout << setw(48) << "Ba�ka bir i�lem yapmak ister misiniz (e/h) : ";
		cin >> cevap;
		cout << endl << endl << endl;

	} while (!(cevap == 'h'));
}

//Okuyucu sistemde kay�tl� olup olmad���n� bulunan fonksiyonu
bool okuyucu_kontrol(string tc_no)
{
	bool control = 0;                                 //TC No sistemde kay�tl� de�ilse 0 de�eri al�r.

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

//Kitap sistemede kay�tl� olup olmad���n� bulunan fonksiyonu
bool kitap_kontrol(string isbn)
{
	bool control = 0;                                     //ISBN sistemde kay�tl� de�ilse 0 de�eri al�r

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


//okuyucu bilgileri fonksiyonu. Bu fonsiyon ile okuyucuyu dosya �zerinde kaydetmektedir.
void OkuyucuBilgileri(string tc_no)
{
	do {
		ofstream dosyayaz;                                                 //okuyucu dosyay� a�ar
		dosyayaz.open("okuyucu.txt", ios::app);

		cout << setw(59) << "KONTROL!" << endl << endl;
		cout << setw(92) << "Okuyucu daha �nce kay�t olup olmad���n� kontrol etmek i�in TC numaras�n� giriniz l�tfen: ";
		cin >> tc_no;

		if (okuyucu_kontrol(tc_no) == 1)                                 // Kay�t kontrol fonksiyonu �a��r�larak okuyucu kayd�n�n olup olmad��� sorgulan�r.
		{
			cout << setw(52) << "Bu TC kimlik numarasina sistemde ait bir okuyucu var.\n\a";
		}

		else
		{
			Okuyucu.TC_NO = tc_no;

			cout << endl << setw(104) << "Girdi�iniz TC numaran� i�in sistemde bir kay�t bulunmad�. Kay�t i�lemler ile devam edebilirsiniz :)" << endl << endl;

			cout << setw(29) << name;       cin >> Okuyucu.adi;                                          //okuyucunun bilgileri d��ar�dan al�n�r
			cout << setw(29) << surname;    cin >> Okuyucu.soyadi;
			cout << setw(29) << member;     cin >> Okuyucu.uyeNo;
			cout << setw(29) << phone;      cin >> Okuyucu.telefon;
			cout << setw(29) << bday;       cin >> Okuyucu.dogumTarihi;
			cout << setw(29) << job;        cin >> Okuyucu.gorevi;
			cout << setw(29) << opp;        cin >> Okuyucu.alabilecegi_kitapSayisi;

			//al�nan bilgileri okuyucu dosyas�nda kaydetmelidir.
			dosyayaz << tc << Okuyucu.TC_NO << "\n" << name << Okuyucu.adi << "\n" << surname << Okuyucu.soyadi << "\n" << member << Okuyucu.uyeNo << "\n" << phone << Okuyucu.telefon << "\n" << bday << Okuyucu.dogumTarihi << "\n" << job << Okuyucu.gorevi << "\n" << opp << Okuyucu.alabilecegi_kitapSayisi << "\n\n";

			cout << endl << setw(70) << "Okuyucu sistemde ba�ar�yla eklendi!\n\n";

		}
		cout << setw(53) << "Ba�ka bir okuyucu kaydetmek ister misiniz (e/h) : ";
		cin >> cevap;
		cout << endl << endl;

		dosyayaz.close();

	} while (!(cevap == 'h'));

}

// kayd� g�ncelleme fonksiyonu 
void GuncellemeOkuyucu(string tc_no)
{
	ifstream dosyaoku("okuyucu.txt");                                                          //okuyucu.txt den bilgileri okunacak 
	ofstream dosyayaz("okuyucu guncelleme.tmp", ios::app);                              //okuyucu guncelleme i�in temporary bir dosya a��l�r

	bool control = 0;

	if (okuyucu_kontrol(tc_no) == 0)                                     // Kay�t kontrol fonksiyonu �a��r�larak okuyucu kayd�n�n olup olmad��� sorgulan�r
	{
		cout << endl << setw(54) << "Sistemde b�yle bir TC kimlik numaras� bulunamad�.\n\a";
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
				cout << endl << setw(24) << "Kay�t oldu�u ki�i. \n\n";                                        //kay�t oldu�u ki�inin bilgileri �ikart�yor
				cout << setw(5) << right << "1." << tc << Okuyucu.TC_NO << endl;
				cout << setw(5) << right << "2." << name << Okuyucu.adi << endl;
				cout << setw(5) << right << "3." << surname << Okuyucu.soyadi << endl;
				cout << setw(5) << right << "4." << member << Okuyucu.uyeNo << endl;
				cout << setw(5) << right << "5." << phone << Okuyucu.telefon << endl;
				cout << setw(5) << right << "6." << bday << Okuyucu.dogumTarihi << endl;
				cout << setw(5) << right << "7." << job << Okuyucu.gorevi << endl;
				cout << setw(5) << right << "8." << opp << Okuyucu.alabilecegi_kitapSayisi << endl;


				cout << endl << setw(78) << "Hangi bilgi de�i�tirmek istiyorsunuz? (1-8): ";
				cin >> sayi;

				switch (sayi)                                               //hangi bilgi de�i�tirmek istiyor se�ip onu ekrana yazar ve sonra yeni bilgieri tekrar al�r
				{
				case 1:
				{
					int number;
					cout << setw(59) << "Yeni bilgileri:\n";                  //her case de yazd�m ��nk� e�er switchin �st�ne yazsam ve kullan�c� yanl�� bir numara girerse o zaman hem "Yeni bilgileri" hem de "Yanl�� bir se�im yapt�n�.." metni ��kacak
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
					cout << endl << setw(69) << "Yanl�� bir se�im yapt�n�z..." << endl;
					break;
				}
				}
				cout << endl << setw(53) << "Ba�ka bir de�i�im yapmak istiyor musunuz? (e/h): ";
				cin >> cevap;
				cout << endl;
			};

			while (dosyaoku.eof())	break;          // En son kayd�n 2 kere okuyup yaz�lmamas� i�in eklendi.

			dosyayaz << tc << Okuyucu.TC_NO << endl << name << Okuyucu.adi << endl << surname << Okuyucu.soyadi << endl << member << Okuyucu.uyeNo << endl << phone << Okuyucu.telefon << endl << bday << Okuyucu.dogumTarihi << endl << job << Okuyucu.gorevi << endl << opp << Okuyucu.alabilecegi_kitapSayisi << endl << endl;
		}
		else
		{
			while (dosyaoku.eof())	break;          // En son kayd�n 2 kere okuyup yaz�lmamas� i�in eklendi.

			dosyayaz << tc << Okuyucu.TC_NO << endl << name << Okuyucu.adi << endl << surname << Okuyucu.soyadi << endl << member << Okuyucu.uyeNo << endl << phone << Okuyucu.telefon << endl << bday << Okuyucu.dogumTarihi << endl << job << Okuyucu.gorevi << endl << opp << Okuyucu.alabilecegi_kitapSayisi << endl << endl;
		}

		dosyaoku.close();
		dosyayaz.close();

		if (control == 1)             // Programda kay�t varsa yap�lan de�i�ikliklerin dosya �zerine yaz�lmas� sa�land�.
		{
			remove("okuyucu.txt");                                    //okuyucu dosyay� siliyor
			rename("okuyucu guncelleme.tmp", "okuyucu.txt");         //okuyucu guncelleme -> okuyucu dosyay� yapar
			cout << setw(75) << "OKUYUCUNUN B�LG�LER� G�NCELLEND� :)\n\n";
		}
		else
		{
			remove("okuyucu guncelleme.tmp");                       //okuyucu guncelleme dosyay� siler
		}
	}
}


//Okuyucu silme fonksiyonu
void silmeOkuyucu(string tc_no)
{
	ifstream dosyaoku("okuyucu.txt");                                 //okuyucu dosyadan bilgi okunacak
	ofstream dosyayaz("okuyucu sil.tmp", ios::app);                   //okuyucu silmek i�in temporary bir dosya a��ld�
	ifstream oduncoku("Odunc.txt");                                   //odunc dosyadan bilgileri okunacak

	bool control = 0;

	if (okuyucu_kontrol(tc_no) == 0)                                  // okuyucu kay�t olup olmad���n� kontrol eder
	{
		cout << setw(77) << "Sistemde bu TC Kimlik numaras� bulunmad�. :/" << endl << endl;
	}
	else
	{
		control = 1;

		while (true)
		{
			string line;
			getline(dosyaoku, line);                        //okuyucu dosyadan bilgileri okur

			if (Okuyucu.TC_NO != tc_no)                 //girilen tc no ve dosyadaki bulunan tc no ayn� olup olmad���n� kontrol eder
			{
				if (dosyaoku.eof())      break;

				dosyayaz << tc << Okuyucu.TC_NO << endl << name << Okuyucu.adi << endl << surname << Okuyucu.soyadi << endl << member << Okuyucu.uyeNo << endl << phone << Okuyucu.telefon << endl << bday << Okuyucu.dogumTarihi << endl << job << Okuyucu.gorevi << endl << opp << Okuyucu.alabilecegi_kitapSayisi << endl << endl;
			}
			else if (Okuyucu.TC_NO == tc_no)
			{
				cout << endl << setw(6) << Okuyucu.adi << " " << Okuyucu.soyadi << " sistemden silmek i�in emin misiniz? (e/h): ";
				cin >> cevap;
				if (true)
				{
					if (!(cevap == 'h'))
					{
						string line;
						getline(dosyaoku, line);

						if (oduncoku.is_open())                                          //odunc dosyay� a��k olup olmad���n� kontrol eder
						{
							cout << endl << setw(75) << "Silinecek okuyucunun �zerindeki �d�n�ler: \n";
							for (int lineno = 1; getline(oduncoku, line) && lineno < 100; lineno + 8)         //bulunan oduncleri d��ar�da yazar
								cout << line << endl;

							dosyaoku.close();
							dosyayaz.close();
							oduncoku.close();
							remove("okuyucu.txt");                                        //okuyucu dosyay� siler
							rename("okuyucu sil.tmp", "okuyucu.txt");                     //okuyucu sil dosyay� ->okuyucu dosyaya �evirir
							cout << "\nKAYIT BA�ARIYLA S�L�ND�." << endl;
							break;
						}
						else
						{
							cout << endl << setw(75) << "Okuyucunun �zerindeki �d�n�ler yoktur.\n\n";
						}

					}
					else
					{
						dosyaoku.close();
						dosyayaz.close();
						remove("okuyucu sil.tmp");                                      //okuyucu sil dosyay� siler
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


//Okuyucu �zerindeki kitaplar listesi
void kitap_listesi(string tc_no)
{
	ifstream okuyucuoku("okuyucu.txt");                     //okuyucu dosyay� okur
	ifstream oduncoku("Odunc.txt");                         //odunc dosyay� okur
	ifstream kitapoku("Kitaplar odunc.tmp");                //kitaplar odunc dosyadan bilgileri okur

	bool control = 0;

	string line;
	getline(okuyucuoku, line);                         //okuyucu dosyanda bulunan bilgileri okunur

	if (okuyucu_kontrol(tc_no) == 0)                   // girilen tc no, okuyucu dosyada bulunan tc no ayn� olup olmad���n� kontrol eder
	{
		cout << endl << setw(82) << "Girdi�iniz de�erler i�in bir kay�t bulunmad� :/" << endl;
	}

	else
	{
		if (!oduncoku.is_open())                            //odunc dosya a��k olup olmad���n� kontrol ederiz. a��k de�ilse kitaplar yoktur.
		{
			cout << endl << setw(65) << "Okuyucun �zerindeki kitap bulunmad�.\n\n";
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
	remove("Odunc.txt");                                                 //odunc dosyay� siler
	rename("Kitaplar odunc.tmp", "Odunc.txt");                           //kitaplar odunc tmp dosyay� ->odunc dosyaya �evirir.
}

//Okuyucu kitap �d�n� alma fonksiyonu
void OduncAlma(string tc_no, string isbn)
{
	do
	{
		ofstream dosyayaz("Odunc.txt", ios::app);            //odunc dosyay� a��p yazacak
		ifstream dosyaoku("okuyucu.txt");                    //okuyucu dosyadan bilgileri okur
		ifstream kitapoku("Kitaplar.txt");                  //Kitaplar dosyadan bilgileri okur
		ofstream kitapyaz("Kitaplar odunc.tmp", ios::app);   //kitaplar odun temporary dosyay� a��p yazar

		bool control = 0;

		if (okuyucu_kontrol(tc_no) == 0)                       //girilen tc no kotrol eder. sistemde kay�t var m� yok mu. yoksa yeni bir kay�t olu�tur
		{
			cout << endl << setw(66) << "Sistemde bu TC NO ile okuyucu bulunmad�. Yeni kay�t olu�turun:\n";
			ofstream dosyayaz("okuyucu.txt", ios::app);                                             //okuyucu dosyaya yeni kay�t olan okuyucuyu yazar

			Okuyucu.TC_NO = tc_no;
			cout << setw(29) << name;       cin >> Okuyucu.adi;
			cout << setw(29) << surname;    cin >> Okuyucu.soyadi;
			cout << setw(29) << member;     cin >> Okuyucu.uyeNo;
			cout << setw(29) << phone;      cin >> Okuyucu.telefon;
			cout << setw(29) << bday;       cin >> Okuyucu.dogumTarihi;
			cout << setw(29) << job;        cin >> Okuyucu.gorevi;
			cout << setw(29) << opp;        cin >> Okuyucu.alabilecegi_kitapSayisi;

			dosyayaz << tc << Okuyucu.TC_NO << "\n" << name << Okuyucu.adi << "\n" << surname << Okuyucu.soyadi << "\n" << member << Okuyucu.uyeNo << "\n" << phone << Okuyucu.telefon << "\n" << bday << Okuyucu.dogumTarihi << "\n" << job << Okuyucu.gorevi << "\n" << opp << Okuyucu.alabilecegi_kitapSayisi << "\n";

			cout << endl << setw(75) << "Okuyucu sistemde ba�ar�yla eklendi!\n";

			dosyayaz.close();
		}
		else
		{
			string line;                                      //Kitaplar dosyadan bilgileri okur
			getline(kitapoku, line);

			cout << setw(81) << "Kitap k�t�phanede olup olmad��� kontrol etmek i�in l�tfen kitab�n ISBN girin: ";
			cin >> isbn;

			if (kitap_kontrol(isbn) == 0)                                                 //istenilen kitap k�t�phanede olup olmad���n� kontrol eder
			{
				cout << endl << setw(70) << "Bu kitap k�t�phanede bulunmad�.\n\a";
			}
			else if (true)
			{

				Kitap.ISBN = isbn;

				string line;                              //okuyucu bilgilerini okur
				getline(dosyaoku, line);

				cout << endl << setw(16) << "Kitab�n ismi: " << Kitap.ismi << endl;

				auto start = chrono::system_clock::now();                                //odunc ne zaman ald���n� yazar
				auto now = chrono::system_clock::to_time_t(start);
				char odunc_tarihi[30];
				ctime_s(odunc_tarihi, sizeof(odunc_tarihi), &now);
				cout << setw(26) << "�d�nc Tarihi..........: " << odunc_tarihi;

				if (dosyayaz.eof())	break;                                               // En son kayd�n 2 kere okuyup yaz�lmamas� i�in eklendi.
				dosyayaz << "Kitab�n ISBN: " << Kitap.ISBN << endl << "Okuyucunun TC NO: " << Okuyucu.TC_NO << endl << "�d�n� alma tarihi: " << odunc_tarihi;

				if (true)
				{
					auto now = std::chrono::system_clock::now();
					auto t_c = std::chrono::system_clock::to_time_t(now + 336h);                           //oduncun d�n�� SON TARIHI ne zaman olaca��n� hesaplan�p yazar
					char bitis_tarihi[30];
					ctime_s(bitis_tarihi, sizeof(bitis_tarihi), &t_c);
					cout << setw(26) << "D�n�� son tarihi......: " << bitis_tarihi;
					cout << endl << setw(90) << "BU TAR�HTEN SONRA OKUYUCU K�TABI GER� D�ND�RMEZSE CEZA ALIR!!\n";
					dosyayaz << "D�n�� SON tarihi: " << bitis_tarihi << endl;
				}

				cout << endl << setw(70) << "Kitap �d�nc olarak al�nd�.\n\n";

				//Kitap art�k �d�n� olarak al�nd���ndan, kitap k�t�phane kitaplar�ndan silinmelidir
				kitapyaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;
				kitapoku.close();
				kitapyaz.close();
				remove("Kitaplar.txt");
			}
		}
		cout << endl << setw(39) << "Ba�ka bir �d�nc al�nacak m�? (e/h): ";
		cin >> cevap;

		dosyaoku.close();
		kitapoku.close();
		dosyayaz.close();
		kitapyaz.close();
	} while (!(cevap == 'h'));
}

//okuyucu kitap d�nd�rme fonksiyonu
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

	if (okuyucu_kontrol(tc_no) == 0)                                  //girilen tc no sistemde bulunan tc no ayn� olup olmad���n� kontrol eder
	{
		cout << endl << setw(82) << "Girdi�iniz de�erler i�in bir kay�t bulunmad� :/" << endl;
	}
	else
	{
		if (true)
		{
			cout << endl;
			string line;

			auto start = chrono::system_clock::now();                           //oduncun donu� tarihini yazar
			auto now = chrono::system_clock::to_time_t(start);
			char donus_tarihi[30];
			ctime_s(donus_tarihi, sizeof(donus_tarihi), &now);
			cout << setw(18) << "D�n�� tarihi: " << donus_tarihi << endl;

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

			cout << endl << setw(100) << "Al�nan kitap son teslim tarihinden �nce iade edildi. Kitab�n bilgileri sisteme ekleniyor...\n\n";

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
		dosyayaz.open("Kitaplar.txt", ios::app);                                      //kitaplar dosyay� a��p yazar

		cout << endl << setw(59) << "KONTROL!" << endl;
		cout << setw(101) << "Kitap daha �nce sistemde kay�t olup olmad���n� kontrol etmek i�in ISBN numaras�n� giriniz l�tfen: ";
		cin >> isbn;

		if (kitap_kontrol(isbn) == 1)                                      //Kitap daha �nce sisteme kay�t olup olmad���n� kontrol edebilmek i�in
		{
			cout << "Sistemde bu �SBN numaras�na ait bir kitap var.\n\a";
		}
		else                                                           //kitap sisteme eklenir
		{
			Kitap.ISBN = isbn;

			cout << endl << setw(104) << "Girdi�iniz ISBN numaran� i�in sistemde bir kay�t bulunmad�. Kay�t i�lemler ile devam edebilirsiniz :)" << endl << endl;

			cin.ignore();
			cout << setw(19) << book_name;                    getline(cin, Kitap.ismi);
			cout << setw(19) << writers_name;                 getline(cin, Kitap.yazar_adi);
			cout << setw(19) << writers_surname;              getline(cin, Kitap.yazar_soyadi);
			cout << setw(19) << topic;                        getline(cin, Kitap.konu);
			cout << setw(19) << genre;                        getline(cin, Kitap.tur);
			cout << setw(19) << pages;                        cin >> Kitap.sayfa_sayisi;

			dosyayaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;

			cout << endl << setw(73) << "Kitap sistemde ba�ar�yla eklendi!\n";
		}
		dosyayaz.close();

		cout << endl << setw(49) << "Ba�ka bir kitap eklemek ister misiniz? (e/h): ";
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

	if (kitap_kontrol(isbn) == 0)                    //girilen isbn ayn�s�n� sistemde olup olmad���n� kotrol eder
	{
		cout << endl << setw(77) << "Sistemde bu �SBN bulunmad�.\n\a ";
	}
	else
	{
		control = 1;

		while (true)
		{
			string line;                                              //kitaplar dosyadan bilgileri okur
			getline(dosyaoku, line);

			if (Kitap.ISBN != isbn)                                  //e�er girilen isbn sisteminin bulunan isbn ayn� de�ilse kitaplar dosyadan okudu�u bilgileri kitaplar sil dosyaya yazar        
			{
				if (dosyaoku.eof())      break;
				dosyayaz << book_isbn << Kitap.ISBN << endl << book_name << Kitap.ismi << endl << writers_name << Kitap.yazar_adi << endl << writers_surname << Kitap.yazar_soyadi << endl << topic << Kitap.konu << endl << genre << Kitap.tur << endl << pages << Kitap.sayfa_sayisi << endl << endl;

			}
			else if (Kitap.ISBN == isbn)                                                 //e�itse silme i�lemleri ile devam eder
			{
				cout << setw(8) << Kitap.ismi << " sistemden silmek i�in emin misiniz? (e/h): ";                          //silme i�lemi yapmapaya emin olup olmad���n� sorar
				cin >> cevap;
				if (true)
				{
					if (!(cevap == 'h'))
					{
						dosyaoku.close();
						dosyayaz.close();
						remove("Kitaplar.txt");                                         //kitaplar dosyay� siler
						rename("Kitaplar sil.tmp", "Kitaplar.txt");                     //kitaplar sil tmp dosyay� ->kitaplar dosyas�nda �evirir
						cout << endl << setw(73) << "KAYIT BA�ARIYLA S�L�ND�." << endl;
						break;
					}
					else
					{
						dosyaoku.close();
						dosyayaz.close();
						remove("Kitaplar sil.tmp");                                     //kitaplar sil dosyay� siler
					}
					break;
				}
			}
		}
	}
};

//Kitap D�zeltme fonksiyonu
void DuzeltmeKitap(string isbn)
{
	ifstream dosyaoku("Kitaplar.txt");                                       //kitaplar dosyadan bilgileri okur
	ofstream dosyayaz("Kitaplar duzeltme.tmp");                              //kitaplat duzeltme temporary dosyaya bligileri yazar

	bool control = 0;

	if (kitap_kontrol(isbn) == 0)                                           //girilen isbn sistemde olup olmad���n� kontrol eder
	{
		cout << setw(58) << "Sistemde bu �SBN numaras�na ait bir kitap bulunamad�.\n\a";
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
				cout << endl << setw(24) << "Kay�t oldu�u kitap: \n" << endl;
				//kay�t oldu�u kitab�n bilgilerini yazar
				cout << setw(5) << right << "1." << book_isbn << Kitap.ISBN << endl;;
				cout << setw(5) << right << "2." << book_name << Kitap.ismi << endl;
				cout << setw(5) << right << "3." << writers_name << Kitap.yazar_adi << endl;
				cout << setw(5) << right << "4." << writers_surname << Kitap.yazar_soyadi << endl;
				cout << setw(5) << right << "5." << topic << Kitap.konu << endl;
				cout << setw(5) << right << "6." << genre << Kitap.tur << endl;
				cout << setw(5) << right << "7." << pages << Kitap.sayfa_sayisi << endl;

				cout << setw(48) << "Hangi bilgi de�i�tirmek istiyorsunuz? (1-7): ";
				cin >> sayi;

				switch (sayi)                                                        //hangi bilgi de�i�tirmek istiyor se�ip onu ekrana yazar
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
					cout << endl << setw(72) << "Yanl�� bir se�im yapt�n�z..." << endl;
					break;
				}
				}
				cout << endl << setw(53) << "Ba�ka bir de�i�im yapmak istiyor musunuz? (e/h): ";
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
			remove("Kitaplar.txt");                                                         //kitaplar dosyay� siler
			rename("Kitaplar duzeltme.tmp", "Kitaplar.txt");                                //kitaplar duzeltme tmp dosyay� ->kitaplar dosyaya �evirir
			cout << endl << setw(65) << "Kitab�n bilgileri g�ncellendi :)\n";
		}
		else
		{
			remove("Kitaplar duzelte.tmp");                                               //kitaplar suzeltme dosyay� siler
		}
	}
}
