---
title: HTTPSClient
summary: Contains a static method to get a WiFiClientSecure object. 

---

# HTTPSClient



Contains a static method to get a WiFiClientSecure object.  [More...](#detailed-description)


`#include <HTTPSClient.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| WiFiClientSecure | **[getClient](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_h_t_t_p_s_client/#function-getclient)**()<br>Get a secure client that can be used to make requests to the API over HTTPS by trusting the IRG Root X1 certificate.  |

## Detailed Description

```cpp
class HTTPSClient;
```

Contains a static method to get a WiFiClientSecure object. 

**Author**: F.S. Koulen

This client can then be used to make requests to the API over HTTPS.


License: GNU GPLv3 

## Public Functions Documentation

### function getClient

```cpp
static WiFiClientSecure getClient()
```

Get a secure client that can be used to make requests to the API over HTTPS by trusting the IRG Root X1 certificate. 

**Return**: A secure client that can be used to make requests to the API. 

**Author**: F.S. Koulen


License: GNU GPLv3 


-------------------------------

Updated on 2023-11-02 at 15:29:20 +0100