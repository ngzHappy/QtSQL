
#include <QtWidgets/QtWidgets>
#include <QtSql/QtSql>

/*测试增加数据*/
void create_sqlite_table() {

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

    {
        /*删除已经存在的student表*/
        if(varDataBase.tables().contains(QStringLiteral("student"))) {
            QSqlQuery varSQLQuery{ varDataBase };
            if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(Drop Table student)^s.q.l^"))) {
                qWarning() << varDataBase.lastError();
            } else {
                qWarning() << QStringLiteral("OK drop table") << __func__;
            }
        }
    }

    {
        /*
        http://www.runoob.com/sqlite/sqlite-tutorial.html
        */
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(
                            Create Table student(
                                id int primary key,
                                name text,
                                age int))^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK create table")  << __func__;
        }
    }

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(INSERT INTO student VALUES(1,"Zhao",10))^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK insert") << __func__;
        }
    }

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(INSERT INTO student VALUES(2,"Qian",20))^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK insert") << __func__;
        }
    }

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(INSERT INTO student VALUES(3,"Sun",30))^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK insert") << __func__;
        }
    }

    qDebug() << QStringLiteral("transaction") << varDataBase.transaction();

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(update student set name = "Good" where id = 1)^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK update") << __func__;
        }
    }

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(delete from student where id = 2)^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK delete") << __func__;
        }
    }

    qDebug() << QStringLiteral("rollback") << varDataBase.rollback();

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(SELECT * from student)^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK select *") << __func__;

            auto varRecord = varSQLQuery.record();
            qWarning() << QStringLiteral("Number of columns") << varRecord.count();
            qWarning() << varRecord.fieldName(0);
            qWarning() << varRecord.indexOf(varRecord.fieldName(0));
            qWarning() << varRecord.field(varRecord.fieldName(0)).type();
            while(varSQLQuery.next()) {
                for(int i = 0; i < varRecord.count(); ++i) {
                    qWarning() << varSQLQuery.value(i);
                }
            }
        }
    }

    qDebug() << QStringLiteral("transaction") << varDataBase.transaction();

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(update student set name = "Good" where id = 1)^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK update") << __func__;
        }
    }

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(delete from student where id = 2)^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK delete") << __func__;
        }
    }

    qDebug() << QStringLiteral("commit") << varDataBase.commit();

    {
        QSqlQuery varSQLQuery{ varDataBase };
        if(!varSQLQuery.exec(QStringLiteral(R"^s.q.l^(SELECT * from student)^s.q.l^"))) {
            qWarning() << varDataBase.lastError();
        } else {
            qWarning() << QStringLiteral("OK select *") << __func__;

            auto varRecord = varSQLQuery.record();
            qWarning() << QStringLiteral("Number of columns") << varRecord.count() ;
            qWarning() << varRecord.fieldName(0);
            qWarning() << varRecord.indexOf(varRecord.fieldName(0));
            qWarning() << varRecord.field(varRecord.fieldName(0)).type();
            while(varSQLQuery.next()) {
                for(int i = 0; i < varRecord.count() ; ++i) {
                    qWarning() << varSQLQuery.value(i);
                }
            }
        }
    }


}



int main(int argc,char ** argv){
    QApplication varApp{argc,argv};

    QWidget varWidget ;

    create_sqlite_table();

    varWidget.show();

    return varApp.exec();
}













