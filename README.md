
# Smart scale bluetooth hack   
 This arduino sketch is an attempt to reverse ingineered the <a target="_blank" href="https://www.amazon.com/Scale-DIKI-Bluetooth-Smart-Monitor/dp/B01LNSFJXK">diki smart scale.</a>    
    
I guess it should be working with all smart scale compatible with the Alfit app:    
    
  <div>  
<a target="_blank" href="https://itunes.apple.com/us/app/aifit/id975487343?mt=8"><img width="170" src="https://www.imro.ie/wp-content/uploads/2017/09/app-store-image.png"></a>  <br>  
<a target="_blank" href="https://play.google.com/store/apps/details?id=com.icare.iweight"><img width="170" src="https://www.designpieces.com/wp-content/uploads/2016/02/google-play-badge.png"></a>  
</div>  
  
<h2>Requirements :</h2>  

- <h3>Hardware : </h3>

	- <a href="https://www.amazon.com/DSD-TECH-Bluetooth-iBeacon-Arduino/dp/B06WGZB2N4/ref=sr_1_1_sspa?s=electronics&ie=UTF8&qid=1521901583&sr=1-1-spons&keywords=hm-10&psc=1">hm-10</a> (bluetooth LE module)  
	- any arduino (in my case, arduino Uno)

Now connect the hm-10 to the arduino.

 <h2>Wiring :</h2>
<table>
<tr>
<th>Arduino Pin</th>
<th>Hm-10 Pin</th>
</tr>
<tr>
<td>3.3V</td>
<td>VCC</td>
</tr>
<tr>
<td>Ground</td>
<td>Ground</td>
</tr>
<tr>
<td>10</td>
<td>TX</td>
</tr>
<tr>
<td>11</td>
<td>RX</td>
</tr>
</table>
<br>
<img width=600 src="https://user-images.githubusercontent.com/8396656/37866949-e86f9aa8-2f91-11e8-91ac-a5592e4eef77.png">
<h2>Configuration :</h2>  

First update the hm-10 firmware to a recent release. You can find different firmware release on the official website of the <a target="_blank" href="http://www.jnhuamao.cn/download_rom_en.asp?id=">constructor</a>.

<a target="_blank" href="http://www.martyncurrey.com/?wpdmdl=4939">Here</a>  is an instruction manual on how to update your firmware 

In order to make it work we need to configure the hm-10 module  
First upload the  <code>hm10_comm.ino</code> sketch to communicate with the module.

Once you've uploaded the sketch open the serial monitor, type <code>AT</code> in the input box and press Enter
If everything works fine, you should <code>OK</code> written in the serial monitor.

Now like with the <code>AT</code> command, follow the next steps :<br>
<code>AT+IMME1</code><br>
<code>AT+ROLE1</code><br>
<code>AT+NOTI1</code><br>

Try to disconnect all your device with bluetoothLE near you, so that the module will only detect the smart scale.<br>
<code>AT+DISC?</code>

Something like that should appear:<br>
<code>OK+DISCEOK+DISCSOK+DIS0:03B3EC12008DOK+DISCE</code>

If there is nothing, do it again until you see something, if still not verify that your scale is powered on and has no problem.

Will consider that there were only one device found otherwise do the following steps for each device until you find the smart scale.

Now enter<br>
<code>AT+CONN0</code>

you should have this as answer<br>
<code>OK+CONN0OK+CONN</code>

Now step on your scale and look for the serial monitor, if some gibberish appears, congrats you've connected your scale to your arduino.

Now enter<br>
<code>AT</code>

you should have this as answer<br>
<code>OK+LOST</code>

Then<br>
<code>AT+IMME0</code>

And at last <br>
<code>AT+RESET</code>

<a href="http://www.martyncurrey.com/?wpdmdl=5917">Here</a> is the hm-10 module DataSheet with all the AT-COMMAND

Now upload the sketch <code>bluetooth_reverse_ingineering.ino</code> open the serial monitor and step on your scale.

<h2>To do:</h2>  

- Update code for esp8266
- Use vector instead of static array to hold serial word
- Add option to persist data on database
- POO version
