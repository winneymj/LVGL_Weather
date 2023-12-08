#ifndef NTPTIME_H_
#define NTPTIME_H_

class NtpTime
{
public:
  NtpTime(void);
  void getTime();
  bool getInternetTimeEnabled();
  bool setInternetTimeEnabled(const bool enabled);
  int getTimeZonePos();
  bool setTimeZonePos(const int pos);
  int getHour(const bool hour24Mode);
  int getMinutes();
  bool set24HourMode(const bool hour24Mode);
  bool get24HourMode();

private:
  void printLocalTime();
  int convertTo12Hour(int hour);
};

#endif // NTPTIME_H_