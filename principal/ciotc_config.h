// This file contains your configuration used to connect to Cloud IoT Core


// Wifi newtork details.
const char *ssid = "Ni lo intentes";
const char *password = "Holahola98";

// Cloud iot details.
const char *project_id = "proyecto-esp32-307412";
const char *location = "europe-west1";
const char *registry_id = "esp32-registry";
const char *device_id = "esp32-device";


// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
// The key length should be exactly the same as the key length bellow (32 pairs
// of hex digits). If it's bigger and it starts with "00:" delete the "00:". If
// it's smaller add "00:" to the start. If it's too big or too small something
// is probably wrong with your key.
const char *private_key_str =
    "a8:ae:06:03:05:22:e4:80:ab:77:f4:49:63:d3:3a:78:ee:40:b1:39:f2:4e:bb:a2:00:09:f0:d0:58:72:b7:b7";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 60*20; // Maximum 24H (3600*24)

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to root.cert and put here on the root_cert variable.

//const char *root_cert =
//    "-----BEGIN CERTIFICATE-----\n"
//    "MIIErjCCA5agAwIBAgIQW+5sTJWKajts11BgHkBRwjANBgkqhkiG9w0BAQsFADBU\n"
//    "MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMSUw\n"
//    "IwYDVQQDExxHb29nbGUgSW50ZXJuZXQgQXV0aG9yaXR5IEczMB4XDTE5MDYxMTEy\n"
//    "MzE1OVoXDTE5MDkwMzEyMjAwMFowbTELMAkGA1UEBhMCVVMxEzARBgNVBAgMCkNh\n"
//    "bGlmb3JuaWExFjAUBgNVBAcMDU1vdW50YWluIFZpZXcxEzARBgNVBAoMCkdvb2ds\n"
//    "ZSBMTEMxHDAaBgNVBAMME21xdHQuZ29vZ2xlYXBpcy5jb20wggEiMA0GCSqGSIb3\n"
//    "DQEBAQUAA4IBDwAwggEKAoIBAQDHuQUoDZWl2155WvaQ9AmhTRNC+mHassokdQK7\n"
//    "NxkZVZfrS8EhRkZop6SJGHdvozBP3Ko3g1MgGIZFzqb5fRohkRKB6mteHHi/W7Uo\n"
//    "7d8+wuTTz3llUZ2gHF/hrXFJfztwnaZub/KB+fXwSqWgMyo1EBme4ULV0rQZGFu6\n"
//    "7U38HK+mFRbeJkh1SDOureI2dxkC4ACGiqWfX/vSyzpZkWGRuxK2F5cnBHqRbcKs\n"
//    "OfmYyUuxZjGah+fC5ePgDbAntLUuYNppkdgT8yt/13ae/V7+rRhKOZC4q76HBEaQ\n"
//    "4Wn5UC+ShVaAGuo7BtfoIFSyZi8/DU2eTQcHWewIXU6V5InhAgMBAAGjggFhMIIB\n"
//    "XTATBgNVHSUEDDAKBggrBgEFBQcDATA4BgNVHREEMTAvghNtcXR0Lmdvb2dsZWFw\n"
//    "aXMuY29tghhtcXR0LW10bHMuZ29vZ2xlYXBpcy5jb20waAYIKwYBBQUHAQEEXDBa\n"
//    "MC0GCCsGAQUFBzAChiFodHRwOi8vcGtpLmdvb2cvZ3NyMi9HVFNHSUFHMy5jcnQw\n"
//    "KQYIKwYBBQUHMAGGHWh0dHA6Ly9vY3NwLnBraS5nb29nL0dUU0dJQUczMB0GA1Ud\n"
//    "DgQWBBSKWpFfG/yH1dkkJT05y/ZnRm/M4DAMBgNVHRMBAf8EAjAAMB8GA1UdIwQY\n"
//    "MBaAFHfCuFCaZ3Z2sS3ChtCDoH6mfrpLMCEGA1UdIAQaMBgwDAYKKwYBBAHWeQIF\n"
//    "AzAIBgZngQwBAgIwMQYDVR0fBCowKDAmoCSgIoYgaHR0cDovL2NybC5wa2kuZ29v\n"
//    "Zy9HVFNHSUFHMy5jcmwwDQYJKoZIhvcNAQELBQADggEBAKMoXHxmLI1oKnraV0tL\n"
//    "NzznlVnle4ljS/pqNI8LUM4/5QqD3qGqnI4fBxX1l+WByCitbTiNvL2KRNi9xau5\n"
//    "oqvsuSVkjRQxky2eesjkdrp+rrxTwFhQ6NAbUeZgUV0zfm5XZE76kInbcukwXxAx\n"
//    "lneyQy2git0voUWTK4mipfCU946rcK3+ArcanV7EDSXbRxfjBSRBD6K+XGUhIPHW\n"
//    "brk0v1wzED1RFEHTdzLAecU50Xwic6IniM3B9URfSOmjlBRebg2sEVQavMHbzURg\n"
//    "94aDC+EkNlHh3pOmQ/V89MBiF1xDHbZZ1gB0GszYKPHec9omSwQ5HbIDV3uf3/DQ\n"
//    "his=\n"
//    "-----END CERTIFICATE-----\n";

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
//const char *root_cert =
/*      "-----BEGIN CERTIFICATE-----\n"
      "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\n"
      "FMQ8QN+7Kj51qXc3M1xASoksFrurbhP1DXzU\n"
      "-----END CERTIFICATE-----\n";*/
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
//const char *root_cert =
/*      "-----BEGIN CERTIFICATE-----\n"
      "MIIESjCCAzKgAwIBAgINAeO0mqGNiqmBJWlQuDANBgkqhkiG9w0BAQsFADBMMSAw\n"
      "HgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEGA1UEChMKR2xvYmFs\n"
      "U2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjAeFw0xNzA2MTUwMDAwNDJaFw0yMTEy\n"
      "MTUwMDAwNDJaMEIxCzAJBgNVBAYTAlVTMR4wHAYDVQQKExVHb29nbGUgVHJ1c3Qg\n"
      "U2VydmljZXMxEzARBgNVBAMTCkdUUyBDQSAxTzEwggEiMA0GCSqGSIb3DQEBAQUA\n"
      "A4IBDwAwggEKAoIBAQDQGM9F1IvN05zkQO9+tN1pIRvJzzyOTHW5DzEZhD2ePCnv\n"
      "UA0Qk28FgICfKqC9EksC4T2fWBYk/jCfC3R3VZMdS/dN4ZKCEPZRrAzDsiKUDzRr\n"
      "mBBJ5wudgzndIMYcLe/RGGFl5yODIKgjEv/SJH/UL+dEaltN11BmsK+eQmMF++Ac\n"
      "xGNhr59qM/9il71I2dN8FGfcddwuaej4bXhp0LcQBbjxMcI7JP0aM3T4I+DsaxmK\n"
      "FsbjzaTNC9uzpFlgOIg7rR25xoynUxv8vNmkq7zdPGHXkxWY7oG9j+JkRyBABk7X\n"
      "rJfoucBZEqFJJSPk7XA0LKW0Y3z5oz2D0c1tJKwHAgMBAAGjggEzMIIBLzAOBgNV\n"
      "HQ8BAf8EBAMCAYYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1Ud\n"
      "EwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFJjR+G4Q68+b7GCfGJAboOt9Cf0rMB8G\n"
      "A1UdIwQYMBaAFJviB1dnHB7AagbeWbSaLd/cGYYuMDUGCCsGAQUFBwEBBCkwJzAl\n"
      "BggrBgEFBQcwAYYZaHR0cDovL29jc3AucGtpLmdvb2cvZ3NyMjAyBgNVHR8EKzAp\n"
      "MCegJaAjhiFodHRwOi8vY3JsLnBraS5nb29nL2dzcjIvZ3NyMi5jcmwwPwYDVR0g\n"
      "BDgwNjA0BgZngQwBAgIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly9wa2kuZ29vZy9y\n"
      "ZXBvc2l0b3J5LzANBgkqhkiG9w0BAQsFAAOCAQEAGoA+Nnn78y6pRjd9XlQWNa7H\n"
      "TgiZ/r3RNGkmUmYHPQq6Scti9PEajvwRT2iWTHQr02fesqOqBY2ETUwgZQ+lltoN\n"
      "FvhsO9tvBCOIazpswWC9aJ9xju4tWDQH8NVU6YZZ/XteDSGU9YzJqPjY8q3MDxrz\n"
      "mqepBCf5o8mw/wJ4a2G6xzUr6Fb6T8McDO22PLRL6u3M4Tzs3A2M1j6bykJYi8wW\n"
      "IRdAvKLWZu/axBVbzYmqmwkm5zLSDW5nIAJbELCQCZwMH56t2Dvqofxs6BBcCFIZ\n"
      "USpxu6x6td0V7SvJCCosirSmIatj/9dSSVDQibet8q/7UK4v4ZUN80atnZz1yg==\n"
      "-----END CERTIFICATE-----\n";*/

// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};
