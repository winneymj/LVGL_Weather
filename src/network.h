#ifndef NETWORK_H_
#define NETWORK_H_

#include <lvgl.h>
#include <vector>
#include <WiFi.h>

enum class NetworkStatus
{
  OK,
  NO_NETWORK_CONFIGURED,
  CONNECTION_FAILED
};

typedef enum {
  NONE,
  NETWORK_SEARCHING,
  NETWORK_SEARCHING_DONE,
  NETWORK_CONNECTING,
  NETWORK_CONNECTED,
  NETWORK_CONNECTION_FAILED,

  NETWORK_CONNECTED_POPUP,
  NETWORK_CONNECT_FAILED
} Network_Status_t;

class Network
{
public:
  Network(void);
  NetworkStatus initialize();
  static uint8_t startWiFi();
  static void stopWiFi();
  static String getSSID();
  static bool setSSID(const std::string& ssid);
  static String getPassword();
  static bool setPassword(const std::string& pwd);
  std::vector<String> retrieveSSIDList();
  static void startNetworkScanner();
  static void stopNetworkScanner();
  static void scanWIFITask(void *pvParameters);
  static void startWIFITask(void *pvParameters);

  static void startWifiConnection();
  static void stopWifiConnection();
  static Network_Status_t wifiConnect();

  static int wifi_signal_strength;
  static std::vector<String> foundWifiList;
  static Network_Status_t networkStatus;
  static TaskHandle_t ntScanTaskHandler;
};

#endif /* ifndef NETWORK_H_ */