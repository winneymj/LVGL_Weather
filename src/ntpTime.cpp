
#include <Preferences.h>
#include <WiFi.h>

#include "ntpTime.h"
#include "esp_sntp.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

extern Preferences preferences;

NtpTime::NtpTime(void) {}

void NtpTime::printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}

void NtpTime::getTime()
{
  if (WiFi.status() != WL_CONNECTED)
    return;
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  auto syncStatus = sntp_get_sync_status();
  while (syncStatus != SNTP_SYNC_STATUS_COMPLETED)
  {
    // Serial.println("NtpTime::getTime(): waiting for ntp time");
    syncStatus = sntp_get_sync_status();
    delay(100); // Adjust the delay time as per your requirements
  }
  sntp_stop();  //resets syncStatus to SNTP_SYNC_STATUS_RESET for the next time I initiate 
   
  printLocalTime();
}

bool NtpTime::getInternetTimeEnabled()
{
  preferences.begin("my_app");
  String value = preferences.getString("internetTime", "");
  preferences.end();
  return value.equals("true");
}

// Returns 0 if fails...else # bytes written
bool NtpTime::setInternetTimeEnabled(const bool enabled)
{
  // Save using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putString("internetTime", enabled ? "true" : "false");
  preferences.end();
  return result;
}


