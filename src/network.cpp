#include <iterator>
#include <Preferences.h>
#include <math.h>
#include "network.h"

Preferences preferences;

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
  Serial.println("Network::initialize():ENTER");
  if (getSSID().isEmpty() || getPassword().isEmpty())
  {
    Serial.println("Network::initialize():NO_NETWORK_CONFIGURED");
    return NetworkStatus::NO_NETWORK_CONFIGURED;
  }
  if (!getSSID().isEmpty() && !getPassword().isEmpty())
  {
    Serial.println("Network::initialize():got ssid & password");
    WiFi.disconnect();
    auto wifiStatus = wifiConnect();

    Serial.print("Network::initialize():wifiStatus=");
    Serial.println(static_cast<int>(wifiStatus));
    if (wifiStatus != NETWORK_CONNECTED)
      return NetworkStatus::CONNECTION_FAILED;
  }

  return NetworkStatus::OK;
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
bool Network::setSSID(const std::string& ssid)
{
  // Save the SSID using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putString("ssid", ssid.c_str());
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
bool Network::setPassword(const std::string& pwd)
{
  // Save the PWD using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putString("password", pwd.c_str());
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

void Network::startWifiConnection()
{
  Serial.println("Network::startWifiConnection(): ENTER");
  if (ntScanTaskHandler == NULL)
  {
    networkStatus = NETWORK_CONNECTING;
    xTaskCreate(startWIFITask,
                "StartWIFITask",
                4096,
                NULL,
                1,
                &ntScanTaskHandler);
  }
}

void Network::stopWifiConnection()
{
  stopNetworkScanner();
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

Network_Status_t Network::wifiConnect()
{
  IPAddress dns(8, 8, 8, 8); // Use Google DNS
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); // switch off AP
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.begin(Network::getSSID(), Network::getPassword());
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("STA: Failed!\n");
    WiFi.disconnect(false);
    vTaskDelay(500);
    WiFi.begin(Network::getSSID(), Network::getPassword());
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    wifi_signal_strength = WiFi.RSSI();
    Serial.println("WiFi connected at: " + WiFi.localIP().toString());
    return NETWORK_CONNECTED;
  }
  else
  {
    Serial.println("WiFi connection *** FAILED ***");
    return NETWORK_CONNECTION_FAILED;
  }
}

void Network::startWIFITask(void *pvParameters)
{
  while (1)
  {
    Serial.println("Network::startWIFITask:ENTER");
    Serial.println("\r\nConnecting to: " + Network::getSSID() +", pwd:" + Network::getPassword());
    wifiConnect();
  }
}
