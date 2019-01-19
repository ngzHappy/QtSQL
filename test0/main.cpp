
#include <QtWidgets/QtWidgets>
#include <QtSql/QtSql>

/*测试创建数据库*/
void create_sqlite_db() {

    QSqlDatabase varDataBase;
    {
        /*获得SQLITE的Qt包装*/
        varDataBase =
            QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    }
    {
        /*设置QSLITE的本地名称*/
        const QDir varDir{ CURRENT_DEBUG_PATH };
        varDataBase.setDatabaseName(
            varDir.absoluteFilePath(QStringLiteral("../MyDataBase.db")));
    }
    {
        /*创建数据库*/
        if(false == varDataBase.open()) {
            qWarning() << varDataBase.lastError();
            return;
        } else {
            qWarning() << QStringLiteral("OK") << __func__  ;
        }
    }

}



int main(int argc,char ** argv){
    QApplication varApp{argc,argv};

    QWidget varWidget ;

    create_sqlite_db();

    varWidget.show();

    return varApp.exec();
}













