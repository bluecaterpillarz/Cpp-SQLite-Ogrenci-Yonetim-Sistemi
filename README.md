# 🎓 Cpp-SQLite-Ogrenci-Yonetim-Sistemi

C++ ve SQLite3 kullanılarak geliştirilmiş, duplicate kontrolü ve dosyadan toplu veri ekleme destekleyen konsol tabanlı bir öğrenci yönetim sistemi.  

A console-based student management system built with C++ and SQLite3 C API integration.

---

## 📖 Proje Hakkında

Bu proje, C++ dili ile SQLite3 veritabanı entegrasyonunu uygulamalı olarak göstermek amacıyla geliştirilmiştir.

Temel hedefler:

- SQLite3 C API ile bağlantı kurma
- SQL sorguları çalıştırma
- Duplicate (mükerrer kayıt) kontrolü
- Dosyadan toplu veri okuma (file parsing)
- Class-based modular yapı
- Dinamik SQL sorgu üretimi

This project demonstrates practical database integration, file parsing, and modular class design in C++.

---

## 🚀 Özellikler / Features

- 📋 Mevcut öğrencileri listeleme
- ⌨️ Klavyeden manuel öğrenci ekleme
- 📂 `ogrenciler.txt` dosyasından toplu kayıt ekleme
- 🔎 Öğrenci numarasına göre duplicate kontrolü
- 🗃 SQLite3 veritabanı kullanımı
- 🧱 Class metodları ile soyutlanmış SQL işlemleri
- 🔌 Constructor / Destructor ile güvenli DB bağlantı yönetimi

---

## 🛠 Kullanılan Teknolojiler

- C++
- SQLite3 (C API)
- STL (vector, string, stringstream, fstream)

---

## 📂 Proje Yapısı

```text
main.cpp
sql_ops.h
sql_ops.cpp
sqlite3.c
sqlite3.h
veritabani.db
ogrenciler.txt
```

> SQL işlemleri `sql_ops` sınıfı içinde kapsüllenmiştir ve main dosyasından çağrılır.

---

## 🧠 Mimari Yaklaşım (Architecture Overview)

Projede:

- SQLite bağlantısı constructor içinde açılır
- Destructor içinde güvenli şekilde kapatılır
- Duplicate kontrolü için SELECT COUNT mantığı kullanılır
- Hem manuel hem dosya tabanlı veri ekleme desteklenir
- SQL işlemleri class encapsulation ile yönetilir

This ensures modularity, separation of concerns, and cleaner code structure.

---

## 🔮 Geliştirilebilir Alanlar / Future Improvements

- Prepared Statements + Parameter Binding (SQL Injection prevention)
- Exception handling eklenmesi
- CMake desteği
- Unit testing
- Daha kapsamlı CRUD operasyonları (Update / Delete)
- Logging mekanizması eklenmesi

---

## 💼 CV / Portfolio Kullanımı

Bu proje aşağıdaki teknik becerileri göstermektedir:

- Database integration
- File parsing
- SQL query design
- Duplicate validation logic
- Class-based modular architecture
- Console backend prototyping

Example CV line:

> Developed a C++ console-based student management system integrated with SQLite3, implementing duplicate validation and file-based bulk insertion.

---

## 📝 Not

`veritabani.db` demo amaçlı eklenmiştir.  
Proje lokal ortamda doğrudan çalıştırılabilir.
