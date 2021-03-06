// A_WifiCTL

  /*
   * Copyright (c) 2015, Eldon R. Brown - ERB - WA0UWH - eldonb@ebcon.com
   *
   * See Blog at: http://WA0UWH.blogspot.com
   *
   * All rights reserved. See FULL Copyright in Main.h or Info Page for Exclusions
   *
   * Inspired by work by: Majenko Technologies - 2015 Esp8266 AdvancedWebServer
   *
   * See: https://github.com/esp8266/Arduino
   */ 
 

// ###########################################################
//////////////////////////////////////////////////////////////
// Initializes the WIFI AP
//
void
//ICACHE_FLASH_ATTR
initWifiAp()
{
    
    restartWifiAp();
    //WiFi.softAP( gDeviceName, "passwd1234", gApChannel );
    WiFi.softAP( gDeviceName, 0, gApChannel );  // For Open AP Network
    yield();
    Serial.println ( F("\nInitilize AP") );
    
    initHandlers();
    startWebServer(); 
    gStnLive = false;
    gReStartSTN = true;
    yield();
}


// ###########################################################
//////////////////////////////////////////////////////////////
// ReStarts the WIFI AP
//
void
//ICACHE_FLASH_ATTR
restartWifiAp()
{
    
    //gApKeepLive = true;
    gApTimeout = millis() + 15 * MINs;
    WiFi.mode( WIFI_AP_STA );
    Serial.println ( F("\n\nReStarting AP") );
    yield();
}


// ###########################################################
//////////////////////////////////////////////////////////////
// Initializes the WIFI STATION
//
void
//ICACHE_FLASH_ATTR
initWifiStn()
{
    
    restartWifiAp();
    
    Serial.print ( F("Trying to Connect to: ") );
    
    //WiFi.disconnect();
    delay(100);
    
    if (gPasswd.length() == 0) {   
         Serial.print ( gSsid + F("(open)*") );
         WiFi.begin ( gSsid.c_str() ); 
    }
    else {
         Serial.print ( gSsid );
         WiFi.begin ( gSsid.c_str(), gPasswd.c_str() );
    }
    yield();

    gWifiStnAttempts = 1;
}


// ###########################################################
//////////////////////////////////////////////////////////////
// Trys to Start the WIFI STATION
//
void
//ICACHE_FLASH_ATTR
try2StartWifiStn()
{
    
    if (!gWifiStnAttempts) initWifiStn(); 
    
    if ( WiFi.status() != WL_CONNECTED ) {
    	delay ( 500 );
    	Serial.print ( "." );
        gWifiStnAttempts = ++gWifiStnAttempts % 10;
        return;
    }
    yield();
    
    gStnLive = true;
    gReStartSTN = false;
    gWifiStnAttempts = 0;
    gWifiReStarts++;
    
    
    // Create Node Name from Least Digits of IPA
    sprintf(gDeviceName+3, FMT("%0d"), WiFi.localIP() >> 24);              // Append Least IP Digits at position 3
    
    
    Serial.println ( sF("\nConnected to: ")       + String(WiFi.SSID()) );
    Serial.println ( sF("IP address: ")           + ipa2str(WiFi.localIP()) );
    Serial.println ( sF("STN Mac Address: ")      + mac2str(WiFi.macAddress(gMacBuf)) );
    Serial.println ( sF("Soft IP address: ")      + gSoftAPAddress );
    Serial.println ( sF("Soft AP  Mac Address: ") + mac2str(WiFi.softAPmacAddress(gMacBuf)) );
    Serial.println ( sF("WiFi ReStarts: ")        + String(gWifiReStarts) );
    yield(); 
    
    Serial.println (); Serial.println ();
    WiFi.printDiag(Serial);
    Serial.println (); Serial.println ();
  
}


// ###########################################################
//////////////////////////////////////////////////////////////
// Starts the WIFI WEB SERVER
//
void
//ICACHE_FLASH_ATTR
startWebServer()
{
    
    gServer.begin();
    Serial.println ( F("HTTP Server Started") );
}

// ###########################################################
// End
