#ifndef NTPTIME_H_
#define NTPTIME_H_

class NtpTime
{
public:
  NtpTime(void);
  void getTime();
  bool getInternetTimeEnabled();
  bool setInternetTimeEnabled(const bool enabled);




private:
  void printLocalTime();
};

#endif // NTPTIME_H_