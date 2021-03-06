// VisitorMap

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
//
// This Function provides an optional Visitors Map Graphic
//
long
ICACHE_FLASH_ATTR
visitorMap() {

  long sz = 0;

        // Provide Optional Visitor Map
        sz += wprintln( );
        sz += wprintln( F("<!-- Visitor Map and Control -->") );
        sz += wprintln( F("<br>") );
        if (gVisitorMapState == true) {
          sz += wprintln( F("<!-- Visitor Map -->") );
          switch (gVisitorMapStyle) {
            case 1:
            default:
              sz += wprintln( F("<br>") );
              sz += wprint  ( F("<script type='text/javascript' src='//rc.revolvermaps.com/0/0/1.js?i=") );
              sz += wprint  ( gVisitorMapIdKey.length() > 0 ? gVisitorMapIdKey : gSharedVisitorMapIdKey );
              sz += wprintln( F("&amp;s=340&amp;m=0&amp;v=true&amp;r=false&amp;b=000000&amp;n=false&amp;c=00ff6c' async='async'></script>") );
            break;
            case 2:
              sz += wprintln( F("<br>") );
              sz += wprint  ( F("<script type='text/javascript' src='//rc.revolvermaps.com/0/0/6.js?i=") );
              sz += wprint  ( gVisitorMapIdKey.length() > 0 ? gVisitorMapIdKey : gSharedVisitorMapIdKey );
              sz += wprintln( F("&amp;m=0&amp;s=340&amp;c=54ff00&amp;cr1=ff0000&amp;f=arial&amp;l=0&amp;bv=100' async='async'></script>") );
            break;
          }
        }   
        sz += wprintln(  F("<br>") );
        sz += wprintln( sF("<form method='GET' action='/") + String((gVisitorMapState == true) ? "off" : "on") + F("/vismap'>") );
        sz += wprint  (  F("<b>Visitor Map</b> -&gt; ") );
        sz += wprintln( sF(" <input type='submit' name='' value='") + String((gVisitorMapState == true) ? "OFF" : "ON") + F("' />") );
        sz += wprintln(  F("</form>") );

        if (gVisitorMapState == true) {
          sz += wprintln( sF("<form method='GET' action='/") + String((gVisitorMapStyle == 1) ? "b" : "a") + F("/vismap'>") );
          sz += wprint  (  F("<b>Style</b> -&gt; ") );
          sz += wprintln( sF(" <input type='submit' name='' value='") + String((gVisitorMapStyle == 1) ? "B" : "A") + F("' />") );
          sz += wprintln(  F("</form>") );
        }

        return sz;
}

// End
