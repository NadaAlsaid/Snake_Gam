# Snake Game  
simulated version of the popular snake game on 8*8 led dot matrix.

using IOT to make website to choose level the player wants to play.

## Components :
- Arduino uno
- Nodemcu esp8266
- 8*8 led dot matrix
- Joystick 
  - Moves the snake
- LCD 
  - Shows  the player score and if the player wins or the game is over
- IR sensor 
  - Play the game if the player pays paper money
- Potentiometer 
  - For clarity of characters on the LCD
  
## Design :

![design](https://user-images.githubusercontent.com/92521186/176088268-1e41ce2e-8265-4ded-8b02-221ec93716af.png)

## The game consists of 3 levels :  
- ### Infinite : 
      - Player still plays untill snake eats himself .
- ### Levels : 
      - It's 2 levels . If player makes certain score , player moves to second level .
- ### Time : 
      - Player plays 15 seconds or untill eats himself .
