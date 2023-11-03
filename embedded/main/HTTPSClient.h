/**
 * Contains a static method to get a WiFiClientSecure object.
 * This client can then be used to make requests to the API over HTTPS.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */
#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Constants.h"


class HTTPSClient {
public:
    HTTPSClient();
    /**
     * List of certificates to trust.
     */
    inline static X509List cert = X509List(IRG_Root_X1);
    HTTPClient httpClient;
    WiFiClientSecure getClient();

private:
    WiFiClientSecure client;
};


#endif //HTTPSCLIENT_H
