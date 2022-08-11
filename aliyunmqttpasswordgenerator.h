#ifndef ALIYUNMQTTPASSWORDGENERATOR_H
#define ALIYUNMQTTPASSWORDGENERATOR_H

#include <iostream>
#include "hash-library/sha1.h"
#include "hash-library/md5.h"
#include "hash-library/sha256.h"
#include "hash-library/hmac.h"
#include <vector>
class AliyunMqttPasswordGenerator
{
private:
    std::string host;
    std::string productKey;
    std::string deviceName;
    std::string deviceSecret;
    std::string deviceIdentifierString;

    std::string timestamp;
    std::string signContent;
    std::string signMethod = "hmacsha256";

    static const std::vector<std::string> supportSignMethod;
    int secureMode = 2;

    std::string getSignContent();
public:
    AliyunMqttPasswordGenerator(const std::string&host,const std::string&productKey,const std::string&deviceName,\
                                const std::string&deviceSecret,const std::string&deviceIdentifierString,\
                                const std::string& signMethod = "hmacsha256");

    void updateTimestamp();
    std::string clientId() const;
    std::string hostName() const;
    std::string userName() const;
    std::string password() const;
    static const std::vector<std::string> &getSupportSignMethod();
    bool signMethodIsSupported(const std::string& signMethod);
};

#endif // ALIYUNMQTTPASSWORDGENERATOR_H
