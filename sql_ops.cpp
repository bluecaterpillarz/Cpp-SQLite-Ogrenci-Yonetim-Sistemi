#include "sql_ops.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

sql_ops::sql_ops(const char* dosya_adi)
{
    if (sqlite3_open(dosya_adi, &veritabani) != SQLITE_OK)
    {
        std::cerr << "Dosya acilamadi!" << std::endl;
        veritabani = nullptr;
    }
}

sql_ops::~sql_ops()
{
    sql_close();
}

bool sql_ops::numara_kontrol(int numara){
        //SELECT COUNT ile verilen numaraya sahip kac kisi odugunu buluyoruz.
        std::string kontrolSQL = "SELECT COUNT(*) FROM ogrenciler WHERE numara = " + std::to_string(numara) + ";";
        sqlite3_stmt* stmt;
        bool var_mi = false;

        if (sqlite3_prepare_v2(veritabani, kontrolSQL.c_str(), -1, &stmt, NULL) == SQLITE_OK)
        {
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                int sayi = sqlite3_column_int(stmt, 0);
                int* sayi_p = &sayi;
                if (*sayi_p > 0)
                {
                    var_mi = true;
                }
            }
            sqlite3_finalize(stmt);
        }

        return var_mi;
    }
void sql_ops::sql_kayit(){
    if (!veritabani)
        {
            std::cerr << "Veritabani baglantisi yok!" << std::endl;
            return;
        }

        std::string veri_isim;
        std::string* veri_isim_p = &veri_isim;
        int veri_numara;
        int* veri_numara_p = &veri_numara;
        short kontrol_degeri;
        short* kontrol_p = &kontrol_degeri;

        std::cout << "Bilgileri klavyeden mi girmek istersiniz, dosyadan mi okumak istersiniz:\n1-klavyeden girmek icin basiniz\n2-dosyadan girmek icin basiniz: ";
        std::cin >> *kontrol_p;

        if (*kontrol_p == 1)
        {
            std::cout << "Ad soyad giriniz: ";
            std::cin.ignore();
            std::getline(std::cin, *veri_isim_p);
            std::cout << "Numara giriniz: ";
            std::cin >> *veri_numara_p;

            // NUMARA KONTROLÜ
            if (numara_kontrol(*veri_numara_p))
            {
                std::cout << "Bu numara zaten kayitli! Ekleme iptal edildi." << std::endl;
                return;
            }

            kaydet = "INSERT INTO ogrenciler (adsoyad,numara) VALUES ('" + (*veri_isim_p) + "','" + std::to_string((*veri_numara_p)) + "');";
        }
        else
        {
            std::string okunacak_dosya;
            std::string* okunacak_dosya_p = &okunacak_dosya;
            std::string gelen;
            std::string* gelen_p = &gelen;
            std::string gelen2;
            std::string* gelen2_p = &gelen2;
            std::vector<std::vector<std::string>> veriler;
            std::vector<std::vector<std::string>>* veriler_p = &veriler;

            std::cout << "Dosya adi giriniz; orneginde veri.txt : ";
            std::cin >> *okunacak_dosya_p;

            std::ifstream dosya_oku(*okunacak_dosya_p);

            if (dosya_oku.is_open())
            {
                while(std::getline(dosya_oku, *gelen_p))
                {
                    std::stringstream ss(*gelen_p);
                    std::vector<std::string> satir;
                    std::vector<std::string>* satir_p = &satir;

                    while(std::getline(ss, *gelen2_p, ','))
                    {
                        if(!(*gelen2_p).empty())
                        {
                            satir_p->push_back(*gelen2_p);
                        }
                    }

                    if(satir_p->size() == 2)
                    {
                        veriler_p->push_back(*satir_p);
                    }
                }
                dosya_oku.close();
            }
            else
            {
                std::cerr << "Dosya acilamadi!" << std::endl;
                return;
            }

            // SQL statement baslama
            kaydet = "INSERT INTO ogrenciler (adsoyad, numara) VALUES ";

            int eklenen_sayi = 0;
            int* eklenen_sayi_p = &eklenen_sayi;

            // Dongu ile VALUES ekleme
            for(int i = 0; i < veriler_p->size(); i++)
            {
                std::string veri_isim_temp = (*veriler_p)[i][0];
                std::string* veri_isim_temp_p = &veri_isim_temp;
                std::string veri_numara_temp = (*veriler_p)[i][1];
                std::string* veri_numara_temp_p = &veri_numara_temp;

                // NUMARA KONTROLÜ
                int numara_int = std::stoi(*veri_numara_temp_p);
                int* numara_int_p = &numara_int;
                if (numara_kontrol(*numara_int_p))
                {
                    std::cout << "Numara " << *numara_int_p << " zaten kayitli, atlanýyor..." << std::endl;
                    continue;
                }

                // VALUES kkismini ekleme
                if (*eklenen_sayi_p > 0)
                {
                    kaydet += ", ";
                }
                kaydet += "('" + (*veri_isim_temp_p) + "', '" + (*veri_numara_temp_p) + "')";
                (*eklenen_sayi_p)++;
            }


            if (*eklenen_sayi_p == 0)
            {
                std::cout << "Tum kayitlar zaten mevcut, ekleme yapilmadi." << std::endl;
                return;
            }

            // SQL statement'ý bitirme
            kaydet += ";";
        }


        char* hata_msg = nullptr;
        int ekleme_ok = sqlite3_exec(veritabani, kaydet.c_str(), NULL, 0, &hata_msg);

        if (ekleme_ok != SQLITE_OK)
        {
            std::cerr << "Ekleme Hatasi: " << hata_msg << std::endl;
            sqlite3_free(hata_msg);
        }
        else
        {
            std::cout << "Veri basariyla eklendi!" << std::endl;
        }

}
void sql_ops::sql_select() {
        if (!veritabani)
        {
            std::cerr << "Veritabani baglantisi yok!" << std::endl;
            return;
        }

        std::string selectSQL = "SELECT * FROM ogrenciler;";

        if (sqlite3_prepare_v2(veritabani, selectSQL.c_str(), -1, &listele, NULL) != SQLITE_OK)
        {
            std::cerr << "Sorgu hazirlanamadi: " << sqlite3_errmsg(veritabani) << std::endl;
        }
        else
        {
            std::cout << "Guncel Liste:" << std::endl;
            while (sqlite3_step(listele) == SQLITE_ROW)
            {
                int kimlik = sqlite3_column_int(listele, 0);
                const unsigned char* isim = sqlite3_column_text(listele, 1);
                int numara = sqlite3_column_int(listele, 2);

                std::string isimler = reinterpret_cast<const char*>(isim);

                std::cout << kimlik << " " << isimler << " " << numara << std::endl;
            }
            sqlite3_finalize(listele);
        }
    }

void sql_ops::sql_close()
{
    if (veritabani)
    {
        sqlite3_close(veritabani);
        veritabani = nullptr;
    }
}
