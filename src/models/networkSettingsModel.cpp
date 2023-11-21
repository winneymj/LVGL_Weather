#include <WiFi.h>               // In-built

#include "networkSettingsModel.h"

NetworkSettingsModel::NetworkSettingsModel()
{
  // Need to get the SSID list
  if (!LoadSSIDList())
  {
    Serial.println("failed to load SSID List");
  }  
}

bool NetworkSettingsModel::LoadSSIDList()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    int n = WiFi.scanNetworks();
    Serial.println("scan done");

    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
      Serial.print(n);
      Serial.println(" networks found");

      for (int i = 0; i < n; ++i)
      {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
        delay(10);
      }
    }
    Serial.println("");

    return n > 0;
  }

  // ssidList.push_back("one");
  // ssidList.push_back("two");
  // ssidList.push_back("three");

  return false;
}
