#ifndef PAGE_ROOT_H
#define PAGE_ROOT_H

const char PAGE_ROOT[] PROGMEM = R"=====(
<title id="title"></title>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<link rel="stylesheet" href="style.css" type="text/css"/>
<script src="/microajax.js"></script> 
<strong>ESPixelStick Admin</strong>
<hr>
<a href="config/net.html" style="width:250px" class="btn btn--m btn--blue">Network Configuration</a><br>
<a href="config/output.html" style="width:250px" class="btn btn--m btn--blue">output Configuration</a><br>
<a href="status/net.html" style="width:250px" class="btn btn--m btn--blue">Network Information</a><br>
<a href="status/e131.html" style="width:250px" class="btn btn--m btn--blue">E1.31 Status</a><hr>
<pre id="name"></pre>
<script>
    setValues("/rootvals");
</script>
)=====";

void send_root_vals_html() {
    String values = "";
    values += "name|div|" + (String)config.name + "\n";
    values += "title|div|" + String("ESPS - ") + (String)config.name + "\n";
    web.send(200, "text/plain", values);
}
#endif
