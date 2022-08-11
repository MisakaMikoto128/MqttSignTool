#include <QCoreApplication>
#include <QString>
#include <QStringBuilder>
#include <QDebug>
#include <QDateTime>
#include "hash-library/sha1.h"
#include "hash-library/hmac.h"
#include <iostream>

QString aliyun_matt_get_signature_content(const QString &productKey,const QString &deviceName,const QString &clientId,const QString &timestamp)
{
    QString content = \
            QString("clientId")%clientId% \
            QString("deviceName")%deviceName% \
            QString("productKey")%productKey% \
            QString("timestamp")%timestamp;
    return content;
}

QString aliyun_matt_get_clientId(const QString &clientId,const QString &timestamp,const QString &signMethod,int secureMode=2)
{

    QString result =
            clientId% \
            QString("|securemode=")%QString::number(secureMode)% \
            QString(",signmethod=")%signMethod% \
            QString(",timestamp=")%timestamp%QString("|");

    return result;
}

QString aliyun_matt_get_hostNmae(const QString &productKey,const QString &host)
{
    return productKey%QString(".")%host;
}

QString aliyun_matt_get_userNmae(const QString &productKey,const QString &deviceName)
{
    return deviceName%QChar('&')%productKey;
}

QString aliyun_matt_get_password(const QString &productKey,const QString &deviceName,const QString &clientId,const QString &timestamp,const QString& deviceSecret)
{
    QString content = aliyun_matt_get_signature_content(productKey,deviceName,clientId,timestamp);
    std::string msg = content.toStdString();
    std::string key = deviceSecret.toStdString();
    std::string sha1hmac = hmac< SHA1 >(msg, key);
    return QString::fromStdString(sha1hmac);
}

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);


//    std::string host = "iot-as-mqtt.cn-shanghai.aliyuncs.com";
//    std::string productKey = "a1w78T9VVmM";
//    std::string deviceName = "dev1";
//    std::string deviceSecret = "1041d8898a6cdc5a851074c1543c98db";
//    std::string SN = "SN";


//    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch()/1000);
//    QString content = aliyun_matt_get_signature_content(productKey,deviceName,SN,timestamp);
//    qDebug()<<"content"<<content;
//    QString clientId = aliyun_matt_get_clientId(SN,timestamp,"hmacsha1",2);
//    qDebug()<<"clientId"<<clientId;
//    QString hostName = aliyun_matt_get_hostNmae(productKey,host);
//    qDebug()<<"hostName"<<hostName;
//    QString userName = aliyun_matt_get_userNmae(productKey,deviceName);
//    qDebug()<<"userName"<<userName;
//    QString password = aliyun_matt_get_password(productKey,deviceName,SN,timestamp,deviceSecret);
//    qDebug()<<"password"<<password;


//    return a.exec();
//}


#include "aliyunmqttpasswordgenerator.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string host = "iot-as-mqtt.cn-shanghai.aliyuncs.com";
    std::string productKey = "a1w78T9VVmM";
    std::string deviceName = "dev1";
    std::string deviceSecret = "1041d8898a6cdc5a851074c1543c98db";
    std::string SN = "SN";

    const AliyunMqttPasswordGenerator gen(host,productKey,deviceName,deviceSecret,SN);
    std::cout << "hostName:" << gen.hostName() << std::endl;
    std::cout << "clientId:" << gen.clientId() << std::endl;
    std::cout << "userName:" << gen.userName() << std::endl;
    std::cout << "password:" << gen.password() << std::endl;
    std::cout << "SupportSignMethod:" << gen.getSupportSignMethod()[0] << std::endl;
    return a.exec();
}
