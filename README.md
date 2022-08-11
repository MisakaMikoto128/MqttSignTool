# MqttSignTool

# 使用注意
这段代码再Win10 Qt(V5.14.2)上编译有问题
```c
// big endian architectures need #define __BYTE_ORDER __BIG_ENDIAN
#ifndef _MSC_VER
#include <endian.h>
#endif
```
替换为下面这段：
```c
// big endian architectures need #define __BYTE_ORDER __BIG_ENDIAN
#ifdef _MSC_VER
// Windows
typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
// GCC
#include <stdint.h>
#endif
```
# 使用
```c
#include "aliyunmqttpasswordgenerator.h"
int main(int argc, char *argv[])
{
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
  return 0;
}
```
