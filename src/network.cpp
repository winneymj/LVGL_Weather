#include <iterator>
#include <Preferences.h>
#include <math.h>
#include "network.h"

const char* test_root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n" \
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n" \
"QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n" \
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n" \
"b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n" \
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n" \
"CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n" \
"nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n" \
"43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n" \
"T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n" \
"gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n" \
"BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n" \
"TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n" \
"DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n" \
"hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n" \
"06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n" \
"PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n" \
"YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n" \
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n" \
"-----END CERTIFICATE-----\n";

Preferences preferences;

String Network::ssid = "";
String Network::password = "";
int Network::wifi_signal_strength = 0;
Network_Status_t networkStatus = NONE;
TaskHandle_t Network::ntScanTaskHandler = {};
Network_Status_t Network::networkStatus = NONE;
std::vector<String> Network::foundWifiList = {};


Network::Network(void) {}

std::vector<String> Network::retrieveSSIDList()
{
  return foundWifiList;
}

NetworkStatus Network::initialize()
{
  if (ssid.isEmpty() || password.isEmpty())
  {
    // Get list of SSID's and return ssid/pwd needed
    return NetworkStatus::NO_NETWORK_CONFIGURED;
  }

  auto wifiStatus = Network::startWiFi();

  if (WiFi.status() == WL_CONNECTED)
  {
  }

  return NetworkStatus::OK;
}

uint8_t Network::startWiFi()
{
  Serial.println("\r\nConnecting to: " + String(ssid) +", pwd:" + password);

  IPAddress dns(8, 8, 8, 8); // Use Google DNS
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); // switch off AP
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("STA: Failed!\n");
    WiFi.disconnect(false);
    delay(500);
    WiFi.begin(ssid, password);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    wifi_signal_strength = WiFi.RSSI();
    Serial.println("WiFi connected at: " + WiFi.localIP().toString());
  }
  else
    Serial.println("WiFi connection *** FAILED ***");
  return WiFi.status();
}

void Network::stopWiFi()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  Serial.println("WiFi switched Off");
}

String Network::getSSID()
{
  preferences.begin("my_app");
  String ssid = preferences.getString("ssid", "");
  preferences.end();
  return ssid;
}

// Returns 0 if fails...else # bytes written
bool Network::setSSID(const String& ssid)
{
  // Save the SSID using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putString("ssid", ssid);
  preferences.end();
  return result;
}

String Network::getPassword()
{
  preferences.begin("my_app");
  String pwd = preferences.getString("password", "");
  preferences.end();
  return pwd;
}

// Returns 0 if fails...else # bytes written
bool Network::setPassword(const String& pwd)
{
  // Save the PWD using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putString("password", pwd);
  preferences.end();
  return result;
}

/*
 * NETWORK TASKS
 */

void Network::startNetworkScanner()
{
  if (ntScanTaskHandler == NULL)
  {
    networkStatus = NETWORK_SEARCHING;
    xTaskCreate(scanWIFITask,
                "ScanWIFITask",
                4096,
                NULL,
                1,
                &ntScanTaskHandler);
  }
}

void Network::stopNetworkScanner()
{
  if (ntScanTaskHandler != NULL)
  {
    networkStatus = NONE;
    vTaskDelete(ntScanTaskHandler);
    ntScanTaskHandler = NULL;
  }
}

void Network::scanWIFITask(void *pvParameters)
{
  while (1)
  {
    Serial.println("Network::scanWIFITask:ENTER");
    foundWifiList.clear();
    int n = WiFi.scanNetworks();
    vTaskDelay(10);
    for (int i = 0; i < min(n, 6); ++i) // Top 6
    {
      String item = WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") " + ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      foundWifiList.push_back(item);
      vTaskDelay(10);
    }
    networkStatus = NETWORK_SEARCHING_DONE;
    vTaskDelay(5000);
  }
}
