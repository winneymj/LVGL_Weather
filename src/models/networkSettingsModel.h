#ifndef NETWORK_SETTINGS_MODEL_H_
#define NETWORK_SETTINGS_MODEL_H_

#include <Array.h>

const int ELEMENT_COUNT_MAX = 20;
typedef Array<String, ELEMENT_COUNT_MAX> StringArrayElements;

class NetworkSettingsModel {
public:
  NetworkSettingsModel(void);

private:
  bool LoadSSIDList();

  StringArrayElements ssidList;
};

#endif /* ifndef NETWORK_SETTINGS_MODEL_H_ */