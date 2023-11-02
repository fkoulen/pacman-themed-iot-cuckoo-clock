#include "HTTPSClient.h"

/**
 * Get a secure client that can be used to make requests to the API over HTTPS by trusting the IRG Root X1 certificate.
 *
 * @return A secure client that can be used to make requests to the API.
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */
WiFiClientSecure HTTPSClient::getClient() {
    WiFiClientSecure client;
    client.setTrustAnchors(&cert);
    return client;
}