
#ifndef SQL_OPS_H
#define SQL_OPS_H

#include <string>
#include <vector>
#include <sqlite3.h>

class sql_ops{
private:
    sqlite3* veritabani;
    char* hata;
    sqlite3_stmt* listele;
    std::string kaydet;
    bool numara_kontrol(int numara);

public:
    sql_ops(const char* dosya_adi);

    ~sql_ops();

    // Public metodlar
    void sql_kayit();
    void sql_select();
    void sql_close();
};






#endif // SQL_OPS_H
