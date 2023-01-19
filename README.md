# Line-follower---IntroductionToRobotics 2023


#### Description
Assemble a line follower robot and write the code for it so that it can do any route in the shortest possible time and in the correct way (that is, to keep the line it is on, to be able to turn correctly without entering other lanes, etc. ).
To achieve this we used PID, is a control loop mechanism employing feedback that is widely used in industrial control systems and a variety of other applications requiring continuously modulated control.
 

### Used components
<ul>
  <li> Arduino Uno
  <li> Zip-ties
  <li> Power source (can be of different shape). In our case, a LiPo battery
  <li> Wheels (2)
  <li> Wires for the line sensor (female - male)
  <li> QTR-8A reflectance sensor, along with screws
  <li> Ball caster
  <li> Extra wires from the kit or lab
  <li> Chassis
  <li> Breadboard - medium (400pts)
  <li> L293D motor driver
  <li> DC motors (2)
</ul>  


### Parameters
- We map the error from sensors to [-30, 30] interval and apply PID with kp = 11, ki = 0, kd = 1, p = 1, i = 0, d = 0.

<br>
 
 ### Image
 ![Line-follower1](assets/line-follower-1.jpeg)
 
 ![Line-follower2](assets/line-follower-2.jpeg)
 
 <br>
 
 ### Video
 <a href =  "https://www.youtube.com/watch?v=Lc_LgxxVQkE&ab_channel=MihaiB%C3%AErsan"><img src = "assets/line-follower-2.jpeg"></a>
