
#include <Preferences.h>
#include <WiFi.h>

#include "ntpTime.h"
#include "esp_sntp.h"

const char* ntpServer = "pool.ntp.org";
// const int   daylightOffset_sec = 3600;
const int   daylightOffset_sec = 0;

const long gmtOffset_sec[] = {
  0, // Greenwich Mean Time
  0, // Universal Coordinated Time
  3600, // European Central Time
  7200, // Eastern European Time
  7200, // (Arabic) Egypt Standard Time
  10800, // Eastern African Time
  12600, // Middle East Time
  14400, // Near East Time
  18000, // Pakistan Lahore Time
  19800, // India Standard Time
  21600, // Bangladesh Standard Time
  25200, // Vietnam Standard Time
  28800, // China Taiwan Time
  32400, // Japan Standard Time
  34200, // Australia Central Time
  36000, // Australia Eastern Time
  39600, // Solomon Standard Time
  43200, // New Zealand Standard Time
  -39600 // Midway Islands Time
  -36000, // Hawaii Standard Time
  -32400, // Alaska Standard Time
  -28800, // Pacific Standard Time
  -25200, // Phoenix Standard Time
  -25200, // Mountain Standard Time
  -21600, // Central Standard Time
  -18000, // Eastern Standard Time
  -18000, // Indiana Eastern Standard Time
  -14400, // Puerto Rico and US Virgin Islands Time
  -12600, // Canada Newfoundland Time
  -10800, // Argentina Standard Time
  -10800, // Brazil Eastern Time
  -3600// Central African Time
};

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

  Serial.print("gmtOffset_sec[getTimeZonePos()]=");
  Serial.println(gmtOffset_sec[getTimeZonePos()]);

  // Init and get the time
  configTime(gmtOffset_sec[getTimeZonePos()], daylightOffset_sec, ntpServer);

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
  int value = preferences.getInt("internetTime", 0);
  preferences.end();
  return value;
}

// Returns 0 if fails...else # bytes written
bool NtpTime::setInternetTimeEnabled(const bool enabled)
{
  Serial.print("setInternetTimeEnabled=");
  Serial.println(enabled);

  // Save using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putInt("internetTime", enabled ? 1 : 0);
  preferences.end();
  return result;
}

int NtpTime::getTimeZonePos()
{
  preferences.begin("my_app");
  int value = preferences.getInt("timezonepos", 0);
  preferences.end();

  Serial.print("getTimeZonePos()=");
  Serial.println(value);

  return value;
}

// Returns 0 if fails...else # bytes written
bool NtpTime::setTimeZonePos(const int pos)
{
  Serial.print("setTimeZonePos()=");
  Serial.println(pos);

  // Save using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putInt("timezonepos", pos);
  preferences.end();
  return result;
}

int NtpTime::convertTo12Hour(int hour)
{
  return hour > 12 ? hour % 12 : hour; 
}

int NtpTime::getHour(const bool hour24Mode)
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return 0;
  }

  return (hour24Mode ? timeinfo.tm_hour : convertTo12Hour(timeinfo.tm_hour));
}

int NtpTime::getMinutes()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return 0;
  }

  return timeinfo.tm_min;
}

bool NtpTime::set24HourMode(const bool hour24Mode)
{
  Serial.print("set24HourMode()=");
  Serial.println(hour24Mode);

  // Save using Preferences library so it is persistent across reboot
  preferences.begin("my_app");
  auto result = preferences.putBool("tfhourmode", hour24Mode);
  preferences.end();
  return result;
}

bool NtpTime::get24HourMode()
{
  preferences.begin("my_app");
  bool value = preferences.getBool("tfhourmode", false);
  preferences.end();

  Serial.print("get24HourMode()=");
  Serial.println(value);

  return value;
}

