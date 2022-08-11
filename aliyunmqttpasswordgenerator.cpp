#include "aliyunmqttpasswordgenerator.h"
#include <ctime>
#include <random>
#if defined(_WIN32) || defined(_WIN64)
//define something for Windows (64-bit only)
static uint64_t getCurrentSecTimestamp(){
    time_t t;
    time(&t);
    return t;
}
#elif __APPLE__
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#endif
#elif __ANDROID__
// android
#elif __linux__
// linux
#include <sys/time.h>
#include <unistd.h>
static uint64_t g getCurrentSecTimestamp(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}
#elif __unix__ // all unices not caught above
// Unix
#elif defined(_POSIX_VERSION)
// POSIX
#else
#error "Unknown"
#endif



const std::vector<std::string> AliyunMqttPasswordGenerator::supportSignMethod = {"hmacsha1","hmacmd5","hmacsha256"};

const std::vector<std::string> &AliyunMqttPasswordGenerator::getSupportSignMethod()
{
    return supportSignMethod;
}

bool AliyunMqttPasswordGenerator::signMethodIsSupported(const std::string &signMethod)
{
    bool ret = false;
    for(std::vector<std::string>::const_iterator it = this->supportSignMethod.begin(); it != this->supportSignMethod.end(); it++){
        if(*it == signMethod){
            ret = true;
        }
    }
    return ret;
}

std::string AliyunMqttPasswordGenerator::generateRandomString(int len)
{
    std::string str;
    str.resize(len);
    int i = 0;
    std::default_random_engine r;
    r.seed(time(0));
    //分为三个情况，小写字母、大写字母、数字
    for(std::string::iterator it = str.begin();it!=str.end();it++){
        i = r()%3;
        switch(i){
            case 0:
            *it = r()%26+'a';
            break;
            case 1:
            *it = r()%26+'A';
            break;
            case 2:
            *it = r()%10+'0';
            break;
        }
    }
    return str;
}

std::string AliyunMqttPasswordGenerator::getSignContent()
{

    std::string signContent = \
            "clientId"+this->deviceIdentifierString+\
            "deviceName"+this->deviceName+ \
            "productKey"+this->productKey+ \
            "timestamp" +this->timestamp;
    return signContent;
}

AliyunMqttPasswordGenerator::AliyunMqttPasswordGenerator(const std::string&host,const std::string&productKey,const std::string&deviceName,\
                                                         const std::string&deviceSecret,const std::string&deviceIdentifierString,\
                                                         const std::string& signMethod)
{
    updateTimestamp();
    this->host = host;
    this->productKey = productKey;
    this->deviceName = deviceName;
    this->deviceSecret = deviceSecret;

    this->deviceIdentifierString = deviceIdentifierString;
    if(signMethodIsSupported(signMethod))
    {
        this->signMethod = signMethod;
    }
    //else{ //have a default value.}

    this->signContent = getSignContent();

}

void AliyunMqttPasswordGenerator::updateTimestamp()
{
    timestamp = std::to_string(getCurrentSecTimestamp());
}

std::string AliyunMqttPasswordGenerator::clientId() const
{
    std::string clientId =
            this->deviceIdentifierString+ \
            "|securemode="  + std::to_string(this->secureMode) +\
            ",signmethod="  + signMethod+\
            ",timestamp="   + timestamp+"|";
    return clientId;
}

std::string AliyunMqttPasswordGenerator::hostName() const
{
    return productKey+"."+host;
}

std::string AliyunMqttPasswordGenerator::userName() const
{
    return deviceName+"&"+productKey;
}

std::string AliyunMqttPasswordGenerator::password() const
{
    std::string sha1hmac;
    if(this->signMethod == this->supportSignMethod[0])
    {
        sha1hmac = hmac<SHA1>(this->signContent, this->deviceSecret);
    }else if(this->signMethod == this->supportSignMethod[1])
    {
        sha1hmac = hmac<MD5>(this->signContent, this->deviceSecret);
    }else if(this->signMethod == this->supportSignMethod[2])
    {
        sha1hmac = hmac<SHA256>(this->signContent, this->deviceSecret);
    }
    return sha1hmac;
}
