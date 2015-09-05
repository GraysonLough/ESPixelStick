/*
* ESPixelStick.h
*
* Project: ESPixelStick - An ESP8266 and E1.31 based pixel driver
* Copyright (c) 2015 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

#ifndef ESPIXELSTICK_H
#define ESPIXELSTICK_H


#define DEBUG		//enable debug print statements on main serial port

//this software supports a few different hardware configurations. 
#define PIXELSTICK 0
#define RENWIFI 1
#define ESPIXEL 2
/********************************
PIXELSTICK by Shelby Merrick, not sure about his hardware layout
RENWIFI outpus Renard data on Serial 0 and a config reset jumper shorts IO2 to GND
ESPIXEL outputs pixel data on IO2 and a config reset button shorts IO0 to GND
********************************/
//set hardware configuration
#define HWCONFIG RENWIFI


/* Name and version */
const char VERSION[] PROGMEM = "ESPMultiStick v1.0";

#define HTTP_PORT   80  /* Default web server port */
#define DATA_PIN    0   /* Pixel output - GPIO0 */
#define EEPROM_BASE 0   /* EEPROM configuration base address */

#define OUTPIXEL 0
#define OUTRENARD 1

/* Configuration ID and Version */
#define CONFIG_VERSION 1;
const uint8_t CONFIG_ID[4] PROGMEM = { 'F', 'O', 'R', '6'};

/* Configuration structure */
typedef struct {
    /* header */
    uint8_t     id[4];          /* Configuration structure ID */
    uint8_t     version;        /* Configuration structure version */

    /* general config */
    char        name[32];       /* Device Name */

    /* network config */
    char        ssid[32];       /* 31 bytes max - null terminated */
    char        passphrase[64]; /* 63 bytes max - null terminated */
    uint8_t     ip[4];
    uint8_t     netmask[4];
    uint8_t     gateway[4];
    uint8_t     dhcp;           /* DHCP enabled boolean */
    uint8_t     multicast;      /* Multicast listener enabled boolean */
    uint8_t     mode;           /* Wifi Mode */
    
    /*output selection */
    uint8_t     output;         /* Output selection  */
    
    /* dmx and pixel config */
    uint16_t    universe;       /* Universe to listen for */
    uint16_t    channel_start;  /* Channel to start listening at - 1 based */
    uint16_t    pixel_count;    /* Number of pixels */
    uint8_t     pixel_type;     /* Pixel type */
    uint8_t     pixel_color;    /* Pixel color order */
    float       gamma;          /* Value used to build gamma correction table */
	
	/* Renard config  */
	uint16_t channel_count;		/* Number of channels */
	uint16_t baud;				/* Baudrate of Serial Port */
} __attribute__((packed)) config_t;

/* Globals */
E131                e131;
ESP8266WebServer    web(HTTP_PORT);
config_t            config;

void saveConfig();
void updatePixelConfig();

#endif
