#include <functions.h>

// HTML code for web app
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!doctype html>
<html>

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Eddie</title>
  <style>
    body {
      font-family: Arial, Helvetica, sans-serif;
      background: #181818;
      color: #EFEFEF;
      font-size: 16px;
      -webkit-user-select: none;
      user-select: none;
    }

    .button {
      background-color: #ff3034;
      border: none;
      border-radius: 4px;
      color: white;
      padding: 22px 10px;
      text-align: center;
      font-size: 16px;
      margin: 4px 60px;
      cursor: pointer;
    }

    .button2 {
      background-color: #ff3034;
      border: none;
      border-radius: 4px;
      color: white;
      padding: 22px 10px;
      text-align: center;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
      width: 100px;  
    }

    .slider1 {
      appearance: none;
      width: 70%;
      height: 15px;
      border-radius: 10px;
      background: #d3d3d3;
      outline: none;
    }

    .slider2 {
      appearance: none;
      width: 60%;
      height: 15px;
      border-radius: 10px;
      background: #d3d3d3;
      outline: none;
    }

    .slider1::-webkit-slider-thumb {
      appearance: none;
      width: 30px;
      height: 30px;
      border-radius: 50%;
      background: #ff3034;
    }

    .slider2::-webkit-slider-thumb {
      appearance: none;
      width: 30px;
      height: 30px;
      border-radius: 50%;
      background: #ff3034;
    }

    .label {
      color: #ff3034;
      font-size: 18px;
    }
  </style>
</head>

<body>
  <div align=center>
    <label class="label">Roll:</label>
    <br />
    <input type="range" class="slider1" id="roll" min="45" max="135" value="85"
      oninput="try{fetch(document.location.origin+'/control?var=roll&val='+this.value);}catch(e){}">
    <br />
    <br />
  </div>
  <div align=center class="label" id="pan_tilt"></div>
  <div align=center>
    <br />
    <label class="label">X axis:</label>
    <br />
    <input type="range" class="slider1" id="pan" min="0" max="309" value="139"
      oninput="try{fetch(document.location.origin+'/control?var=pan&val='+this.value);}catch(e){}">
    <br />
    <br />
    <canvas id="myCanvas" width="300" height="300" style="border:5px solid #ffffff;"
      onmouseup="fetch(document.location.origin+'/control?var=tilt&val='+y)+fetch(document.location.origin+'/control?var=pan&val='+x);"></canvas>
    <br />
    <br />
    <label class="label">Y axis:</label>
    <br />
    <input type="range" class="slider1" id="tilt" min="0" max="309" value="191"
      oninput="try{fetch(document.location.origin+'/control?var=tilt&val='+this.value);}catch(e){}">
    <br />
    <br />
    <button class="button" id="forward" ontouchstart="fetch(document.location.origin+'/control?var=car&val=1');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Forward</button>
    <br />
    <button class="button" id="turnleft" ontouchstart="fetch(document.location.origin+'/control?var=car&val=2');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Turn Left</button>
    <button class="button" id="turnright" ontouchstart="fetch(document.location.origin+'/control?var=car&val=4');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Turn Right</button>
    <br />
    <button class="button" id="backward" ontouchstart="fetch(document.location.origin+'/control?var=car&val=5');"
      ontouchend="fetch(document.location.origin+'/control?var=car&val=3');">Backward</button>
    <br />
    <br />
    <label class="label">Slower</label>
    <input type="range" class="slider2" id="speed" min="50" max="255" value="152"
      onchange="try{fetch(document.location.origin+'/control?var=speed&val='+this.value);}catch(e){}">
    <label class="label">Faster</label>
    <br />
    <br />
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=1');">Happy</button>
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=2');">Sleep</button>
    <br />
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=3');">Sad</button>
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=4');">Yes</button>
    <br />
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=5');">Mad</button>
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=6');">No</button>
    <br />
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=7');">Confused</button>
    <button class="button2" id="action" ontouchstart="fetch(document.location.origin+'/control?var=action&val=8');">Custom</button>
  </div>
  <script>
    const cnvs = document.getElementById('myCanvas');
    var ctx = cnvs.getContext("2d");
    var x = 139;
    var y = 191;
    ctx.translate(0,300);
    function draw() {
      ctx.clearRect(0, -300, cnvs.width, cnvs.height);
      ctx.clearRect
      ctx.strokeStyle = "white";
      ctx.lineWidth = 2;
      ctx.beginPath();
      ctx.moveTo(0, -150);
      ctx.lineTo(300, -150);
      ctx.stroke();
      ctx.moveTo(150, 0);
      ctx.lineTo(150, -300);
      ctx.stroke();
      ctx.closePath();
      ctx.moveTo(x + 5, -(y - 5));
      ctx.beginPath();
      ctx.arc(x - 5, -(y - 5), 10, 0, 2 * Math.PI);
      ctx.stroke();
      ctx.closePath();
    }
    draw();

    cnvs.addEventListener("mousedown", printMousePos);
    function printMousePos() {
      var rect = cnvs.getBoundingClientRect();
      x = Math.round(event.clientX - rect.left);
      y = Math.round(event.clientY - rect.bottom);
      document.getElementById("pan_tilt").innerHTML = "X: " + x + " || Y: " + Math.abs(y);
      y = -y;
      draw();
      y = Math.abs(y);
      document.getElementById('pan').value = x;
      document.getElementById('tilt').value = y;
    }

    const panSlider = document.getElementById('pan');
    panSlider.addEventListener("input", changeX);
    function changeX() {
      if (y == null) {
        y = -191;
      }
      x = document.getElementById('pan').value;
      document.getElementById("pan_tilt").innerHTML = "X: " + x + " || Y: " + Math.abs(y);
      draw();
      y = Math.abs(y);
    }

    const tiltSlider = document.getElementById('tilt');
    tiltSlider.addEventListener("input", changeY);
    function changeY() {
      if (x == null) {
        x = 139;
      }
      y = -(document.getElementById('tilt').value);
      document.getElementById("pan_tilt").innerHTML = "X: " + x + " || Y: " + Math.abs(y);
      y = -y;
      draw();
      y = Math.abs(y);
    }
  </script>
</body>

</html>
)rawliteral";

// Send HTML code
esp_err_t index_handler(httpd_req_t *req)
{
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}
