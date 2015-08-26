#ifndef PAGE_CONFIG_REN_H
#define PAGE_CONFIG_REN_H

const char PAGE_CONFIG_RENARD[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<link rel="stylesheet" href="/style.css" type="text/css"/>
<script src="/microajax.js"></script>
<a href="/" class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Pixel Configuration</strong>
<hr>
<form action="" method="get">
<table border="0" cellspacing="0" cellpadding="3">
<tr><td align="right">Device ID:</td><td><input type="text" id="devname" name="devname" value=""></td></tr>
<tr><td align="right">Universe:</td><td><input type="text" id="universe" name="universe" value=""></td></tr>
<tr><td align="right">Start Channel:</td><td><input type="text" id="channel_start" name="channel_start" value=""></td></tr>
<tr><td align="right">Channel Count:</td><td><input type="text" id="channel_count" name="channel_count" value=""></td></tr>
<tr><td align="right">Baud:</td><td><select id="baud" name="baud"></select></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<script>
	setValues("/config/pixelvals");
</script>
)=====";

void send_config_renard_html() {
    if (web.args() > 0) {  // Save Settings
        for (uint8_t i = 0; i < web.args(); i++) {
            if (web.argName(i) == "devname") urldecode(web.arg(i)).toCharArray(config.name, sizeof(config.name));
            if (web.argName(i) == "universe") config.universe = web.arg(i).toInt(); 
            if (web.argName(i) == "channel_start") config.channel_start = web.arg(i).toInt();
            if (web.argName(i) == "channel_count") config.channel_count = web.arg(i).toInt();
            if (web.argName(i) == "baud") config.baud = web.arg(i).toInt();
        }
        saveConfig();
    }
    web.send(200, "text/html", PAGE_CONFIG_RENARD);
}

void send_config_renard_vals_html() {
    String values = "";
    values += "devname|input|" + (String)config.name + "\n";
    values += "universe|input|" + (String)config.universe + "\n";
    values += "channel_start|input|" + (String)config.channel_start + "\n";
    values += "channel_count|input|" + (String)config.channel_count + "\n";
    values += "baud|input|" + (String)config.baud + "\n";
    web.send(200, "text/plain", values);
}

#endif
