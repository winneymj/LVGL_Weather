#ifndef CREDENTIALS_H_
#define CREDENTIALS_H_

// Use your own API key by signing up for a free developer account at https://openweathermap.org/
String apikey       = "*******************"; // See: https://openweathermap.org/
const char server[] = "api.weather.gov";

//Set your location according to OWM locations
String City             = "Milwaukee";                     // Your home city See: http://bulk.openweathermap.org/sample/
String Latitude         = "43.1082";                     // Latitude of your location in decimal degrees
String Longitude        = "-87.9009";                    // Longitude of your location in decimal degrees
String Language         = "EN";                            // NOTE: Only the weather description is translated by OWM
                                                           // Examples: Arabic (AR) Czech (CZ) English (EN) Greek (EL) Persian(Farsi) (FA) Galician (GL) Hungarian (HU) Japanese (JA)
                                                           // Korean (KR) Latvian (LA) Lithuanian (LT) Macedonian (MK) Slovak (SK) Slovenian (SL) Vietnamese (VI)
String Hemisphere       = "north";                         // or "south"  
String Units            = "M";                             // Use 'M' for Metric or I for Imperial 
const char* Timezone    = "	CST6CDT,M3.2.0,M11.1.0";       // Choose your time zone from: https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv 

#endif /* ifndef CREDENTIALS_H_ */
