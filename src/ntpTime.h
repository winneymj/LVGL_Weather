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






private:
  void printLocalTime();
};

#endif // NTPTIME_H_