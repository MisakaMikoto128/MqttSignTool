#include <QCoreApplication>
#include <QString>
#include <QStringBuilder>
#include <QDebug>
#include <QDateTime>
#include "hash-library/sha1.h"
#include "hash-library/hmac.h"
#include <iostream>

QString productKey = "a1w78T9VVmM";
QString deviceName = "dev1";
QString deviceSecret = "1041d8898a6cdc5a851074c1543c98db";
QString SN = "SN";

QString aliyun_matt_get_signature_content(const QString &productKey,const QString &deviceName,const QString &clientId)
{
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch()/1000);
    QString content = QString("clientId")%clientId% \
            QString("deviceName")%deviceName% \
            QString("productKey")%productKey% \
            QString("timestamp")%timestamp;
    return content;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString content = aliyun_matt_get_signature_content(productKey,deviceName,SN);
    qDebug()<<content<<endl;


    std::string msg = content.toStdString();
    std::string key = deviceSecret.toStdString();
    std::string sha1hmac = hmac< SHA1 >(msg, key);

    qDebug()<<QString::fromStdString(sha1hmac)<<endl;
    return a.exec();
}
