#ifndef NETWORK_H_
#define NETWORK_H_

#include <lvgl.h>
#include <vector>
#include <WiFi.h>

enum class NetworkStatus
{
  OK,
  NO_NETWORK_CONFIGURED
};

typedef enum {
  NONE,
  NETWORK_SEARCHING,
  NETWORK_SEARCHING_DONE,
  NETWORK_CONNECTED_POPUP,
  NETWORK_CONNECTED,
  NETWORK_CONNECT_FAILED
} Network_Status_t;

class Network {
public:
  Network(void);
  NetworkStatus initialize();
  static uint8_t startWiFi();
  static void stopWiFi();
  String getSSID();
  bool setSSID(const String& ssid);
  String getPassword();
  bool setPassword(const String& pwd);
  std::vector<String> retrieveSSIDList();
  static void startNetworkScanner();
  static void stopNetworkScanner();
  static void scanWIFITask(void *pvParameters);

  static String ssid;
  static String password;
  static int wifi_signal_strength;
  static std::vector<String> foundWifiList;
  static Network_Status_t networkStatus;
  static TaskHandle_t ntScanTaskHandler;
};

#endif /* ifndef NETWORK_H_ */