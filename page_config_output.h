#ifndef PAGE_CONFIG_OUTPUT_H
#define PAGE_CONFIG_OUTPUT_H

const char PAGE_CONFIG_OUTPUT[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<link rel="stylesheet" href="/style.css" type="text/css"/>
<script src="/microajax.js"></script>
<a href="/" class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Output Configuration</strong>
<hr>
<form action="" method="get">
<h2>Common Settings</h2>
<table border="0" cellspacing="0" cellpadding="3">
<tr><td align="right">Device ID:</td><td><input type="text" id="devname" name="devname" value=""></td></tr>
<tr><td align="right">Universe:</td><td><input type="text" id="universe" name="universe" value=""></td></tr>
<tr><td align="right">Start Channel:</td><td><input type="text" id="channel_start" name="channel_start" value=""></td></tr>
<tr><td align="right">Output Type:</td><td><select id="output" name="output"></select></td></tr>
</table>
<h2>Pixel Settings</h2>
<table border="0" cellspacing="0" cellpadding="3">
<tr><td align="right">Pixel Count:</td><td><input type="text" id="pixel_count" name="pixel_count" value=""></td></tr>
<tr><td align="right">Pixel Type:</td><td><select id="pixel_type" name="pixel_type"></select></td></tr>
<tr><td align="right">Color Order:</td><td><select id="pixel_color" name="pixel_color"></select></td></tr>
<tr><td align="right">Gamma:</td><td><input type="text" id="gamma" name="gamma" value=""></td></tr>
</table>
<h2> Renard Settings</h2>
<table border="0" cellspacing="0" cellpadding="3">
<tr><td align="right">Channel Count:</td><td><input type="text" id="channel_count" name="channel_count" value=""></td></tr>
<tr><td align="right">Baud:</td><td><select id="baud" name="baud"></select></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<script>
	setValues("/config/outputvals");
</script>
)=====";

const char PAGE_RELOAD_OUT[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="2; url=/config/output.html">
<strong>Please Wait....Configuring and Restarting.</strong>
)=====";


void send_config_output_html() {
    if (web.args() > 0) {  // Save Settings
        for (uint8_t i = 0; i < web.args(); i++) {
            if (web.argName(i) == "devname") urldecode(web.arg(i)).toCharArray(config.name, sizeof(config.name));
            if (web.argName(i) == "universe") config.universe = web.arg(i).toInt(); 
            if (web.argName(i) == "channel_start") config.channel_start = web.arg(i).toInt();
            if (web.argName(i) == "output") config.output = web.arg(i).toInt();
            if (web.argName(i) == "pixel_count") config.pixel_count = web.arg(i).toInt();
            if (web.argName(i) == "pixel_type") config.pixel_type = web.arg(i).toInt();
            if (web.argName(i) == "pixel_color") config.pixel_color = web.arg(i).toInt();
            if (web.argName(i) == "gamma") config.gamma = web.arg(i).toFloat();
            if (web.argName(i) == "channel_count") config.channel_count = web.arg(i).toInt();
            if (web.argName(i) == "baud") config.baud = web.arg(i).toInt();
        }
        web.send(200, "text/html", PAGE_RELOAD_OUT);
        saveConfig();
        ESP.restart();
    }
    web.send(200, "text/html", PAGE_CONFIG_OUTPUT);
}

void send_config_output_vals_html() {
    String values = "";
    values += "devname|input|" + (String)config.name + "\n";
    values += "universe|input|" + (String)config.universe + "\n";
    values += "channel_start|input|" + (String)config.channel_start + "\n";
    values += "output|opt|" + String("Pixel|") + (String)OUTPIXEL + "\n";
    values += "output|opt|" + String("Renard|") + (String)OUTRENARD + "\n";
    values += "output|input|" + (String)config.output + "\n";
    values += "pixel_count|input|" + (String)config.pixel_count + "\n";
    values += "pixel_type|opt|" + String("WS2811 800kHz|") + (String)NEO_KHZ800 + "\n";
    values += "pixel_type|input|" + (String)config.pixel_type + "\n";
    values += "pixel_color|opt|" + String("RGB|") + (String)NEO_RGB + "\n";
    values += "pixel_color|opt|" + String("GRB|") + (String)NEO_GRB + "\n";
    values += "pixel_color|opt|" + String("BRG|") + (String)NEO_BRG + "\n";
    values += "pixel_color|opt|" + String("RBG|") + (String)NEO_RBG + "\n";
    values += "pixel_color|input|" + (String)config.pixel_color + "\n";
    values += "gamma|input|" + String(config.gamma) + "\n";
    values += "channel_count|input|" + (String)config.channel_count + "\n";
    values += "baud|opt|" + String("38400|") + (String)38400 + "\n";
    values += "baud|opt|" + String("57600|") + (String)57600 + "\n";
    values += "baud|opt|" + String("115200|") + (String)115200 + "\n";
    values += "baud|input|" + (String)config.baud + "\n";
    web.send(200, "text/plain", values);
}

#endif
