<h1>RFID keys clonner</h1>

<p>Device, which has been created for clonning UID`s of RFID keys (<i>only 13.56MHz</i>). This keys can be use to open doors/intercoms/barriers/gate etc.</p>
<br>
<div style="max-width: 50%; max-height: 40%; display: flex; flex-direction: row;">
  <img src="https://github.com/SamanuelAdmin/RFID_UID_clonner/assets/68198268/a70ddc43-9f97-4dbc-892b-1901ad4d8f41" style="height: 200px;">
  <img src="https://github.com/SamanuelAdmin/RFID_UID_clonner/assets/68198268/c3b1df50-4efa-4114-86b8-5ecb04a8d025" style="height: 200px;">
  <img src="https://github.com/SamanuelAdmin/RFID_UID_clonner/assets/68198268/3146ebcf-9bfa-4438-bf03-e0adb4b4efbe" style="height: 200px;">
  <img src="https://github.com/SamanuelAdmin/RFID_UID_clonner/assets/68198268/7cc78307-5e91-4f2e-9768-89037b28b278" style="height: 200px;">
</div>

<br>
<p><strong>NOTE</strong>  <i>This project can be used only for keys, works on 13.56MHz.</i> Keys with frequency of 120KHz <i>wont be recognized.</i></p>
<img src="https://encrypted-tbn3.gstatic.com/shopping?q=tbn:ANd9GcS30ictxFUmfpxduYEQWQ9E88uDLUw7sAt3VLsWk_P7lRpZlMc4gp9RNmZY_3RIRN93SMkj19ISPd4DptM8oq12W7N-XzM7Kd6uCih38b6ILkZ1MebmKY8d-g&usqp=CAE" style="height: 250px">

<br><hr><br>

<h5>Menu:</h5>
<ul>
  <li><a href="#howtocreate"><i>How to create the clonner?</i></a></li>
  <li><a href="#software"><i>Setup software</i></a></li>
  <li><a href="#dependencies"><i>Dependencies</i></a></li>
</ul>

<br><br>

<h2 id="howtocreate">How to create the clonner?</h2>
1. At the first you need to buy some components. Project works on Arduino Mega 2560, for another boards you need to change pins in <strong>define</strong> lines. <br><i>But dont use Arduino nano/Arduino uno because they all have only one line of SPI, but this project required two</i> (for lcd1602 keyboard shield and RFID module).
A list of necessary components:
<ul>
  <a href="https://octopart.com/arduino+mega+2560+rev3-arduino-29408153?gad_source=1&gclid=CjwKCAjw17qvBhBrEiwA1rU9w5rPoaRsqKaB0a_GF7Vo3dou3f7pqEIl6K2O2xRefU7d27d8jEA7CxoCC24QAvD_BwE"><li>Arduino Mega</li></a>
  <a href="https://arduino.ua/prod649-rfid-modyl-rc522-s-kartochkoi-dostypa-dlya-arduino"><li>RC522 (RFID module)</li></a>
  <a href="https://arduino.ua/prod235-lcd-keypad-shield"><li>LCD1602 Keyboard shield</li></a>
  <a href="https://store.arduino.cc/collections/cables-wires/products/10-jumper-wires-150mm-male?selectedStore=eu"><li>Some wire (2 or more colors optionaly)</li></a>
  <a href="https://diyshop.com.ua/en/rfid-13-56-mgc-klyuch-dostupa-dlya-arduino"><li>Some RFID keys on 13.56MHz (optionaly)</li></a>
</ul>
<i>NOTE! Be shure that key has a rewrite option!</i>

<br><br>

2. Assembly devise using this video-instructions:
<div style="display: flex; flex-direction: row; justify-content: space-between;">
  <a href="http://www.youtube.com/watch?feature=player_embedded&v=hxQYIwdZRng" target="_blank" style="margin-right: 20px;">
    <img src="http://img.youtube.com/vi/hxQYIwdZRng/0.jpg" alt="How to connect rc522 to Arduino Mega 2560." width="240" height="180" border="10"/>
  </a>
  <a href="http://www.youtube.com/watch?feature=player_embedded&v=BVA2aX7NFLs" target="_blank">
    <img src="http://img.youtube.com/vi/BVA2aX7NFLs/0.jpg" alt="How to connect LCD shield to Arduino Mega 2560" width="240" height="180" border="10"/>
  </a>
</div>

<br>
<strong>Done!</strong> Now you are ready to flash Arduino Mega.

<hr>
<br>

<h2 id="software">Setup software</h2>
At the begin you need to download and setup <a href="#dependencies">Dependencies</a> to your Arduino IDE (<a href="https://www.arduino.cc/en/software">you can download it here</a>) via this guide:
  <a href="http://www.youtube.com/watch?feature=player_embedded&v=d5LU1ig4BQQ" target="_blank">
    <img src="http://img.youtube.com/vi/d5LU1ig4BQQ/0.jpg" alt="How to connect LCD shield to Arduino Mega 2560" width="280" border="10"/>
  </a>
<br>
Then download code from this <a href="https://github.com/SamanuelAdmin/RFID_UID_clonner/">repository</a> using

```ruby
git clone https://github.com/SamanuelAdmin/RFID_UID_clonner/
```
command or just press 
`
download
`
button and open <i>.ino</i> file. After that press 
`
"upload"
`
button and wait for a minute.
After all this steps you can see demo title on the screen and then your clonner ready to work.

<hr><br>


<h2 id="dependencies">Dependencies</h2>
<i>NOTE!</i> You can find this all in 

`
Sketch -> Include Library -> Manage Libraries... -> Search
`

<ul>
  <li>LiquidCrystal (for LCD1602 display)</li>
  <li>SPI</li>
  <li>MFRC522 (for RFID module)</li>
</ul>

<hr>
<h3>Support</h3>
<p>If <i></i>you enjoy my projects</i> or that <i>was helpful</i>, you can support me by donation.</p>

`
Visa: 4441 1144 6743 1589
`
