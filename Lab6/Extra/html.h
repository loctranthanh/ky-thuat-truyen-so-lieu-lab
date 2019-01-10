const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<div id="demo">
<h1>CURRENT TIME IN:</h1>
	
</div>

<div>
	Viet Nam: <span id="timeInVN">0</span><br>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 10); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("timeInVN").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "timeVN", true);
  xhttp.send();
}

</script>

</body>
</html>
)=====";