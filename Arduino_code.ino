#include <LedControl.h> // LedControl library is used for controlling a LED matrix. Find it using Library Manager or download zip here: https://github.com/wayoda/LedControl
#include <LiquidCrystal.h>

// there are defined all the pins
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

short joystickX = A2;   // joystick X axis pin
short joystickY = A3;   // joystick Y axis pin
int ir = 8 ;
short CLK = 10;   // clock for LED matrix
short CS  = 11;  // chip-select for LED matrix
short DIN = 12; // data-in for LED matrix

// LED matrix brightness: between 0(darkest) and 15(brightest)
const short intensity = 6;

// initial snake length (1...63, recommended 3)
const short initialSnakeLength = 3;

// --------------------------------------------------------------- //
// -------------------- supporting variables --------------------- //
// --------------------------------------------------------------- //

LedControl matrix(DIN, CLK, CS, 1);

struct Point {
  int row = 0, col = 0;
  Point(int row = 0, int col = 0): row(row), col(col) {}
};

struct Coordinate {
  int x = 0, y = 0;
  Coordinate(int x = 0, int y = 0): x(x), y(y) {}
};
char  x ;
bool win = false;
bool gameOver = false;
bool Level_2 = false ;
bool setLength = false ;
// primary snake head coordinates (snake head), it will be randomly generated
Point snake;

// food is not anywhere yet
Point food(-1, -1);

// construct with default values in case the user turns off the calibration
Coordinate joystickHome(500, 500);

// snake parameters
int snakeLength = initialSnakeLength; // choosed by the user in the config section
int snakeSpeed = 110; // will be set according to potentiometer value, cannot be 0
int snakeDirection = 0; // if it is 0, the snake does not move
int score = 0 ;
// direction constants
const short up     = 1;
const short right  = 2;
const short down   = 3; // 'down - 2' must be 'up'
const short left   = 4; // 'left - 2' must be 'right'
String value = "-1" ;
// threshold where movement of the joystick will be accepted
const int joystickThreshold = 160;

// artificial logarithmity (steepness) of the potentiometer (-1 = linear, 1 = natural, bigger = steeper (recommended 0...1))
const float logarithmity = 0.4;

// snake body segments storage
int gameboard[8][8] = {};
unsigned long time1 ;
void setup() {
  Serial.begin(115200);  // set the same baud rate on your Serial Monitor
  Serial.setTimeout(5);
  matrix.shutdown(0, true);
  matrix.setIntensity(0, intensity);
  matrix.clearDisplay(0);
  snake.row = random(8);
  snake.col = random(8);
  lcd.begin(16, 2);
  pinMode(ir , INPUT);
  calibrateJoystick(); // calibrate the joystick home (do not touch it)
}

void loop() {
  int s = digitalRead(ir) ;
  if ( s == 0 ) {
    Serial.println("0");
   if (Serial.available()) {
      value = Serial.read();
      Serial.print("value: ");
      Serial.println(value);
      lcd.setCursor(0, 0);
      lcd.write("Snake Game" );
    }



    time1 = millis() ;
    snakeLength = 3 ;

    if (value.toInt()== 0 ) {
      Serial.println("hjjhjh");
      matrix.shutdown(0, false);

      while (true ) {

        generateFood();    // if there is no food, generate one
        scanJoystick();    // watches joystick movements & blinks with food
        calculateSnake();  // calculates snake parameters
        //handleGameStates();
        if (gameOver) {

          gameOver =  false;
          matrix.shutdown(0, true);
          value = "-1";
          break ;
        }
      }
    }
   /* if (0 == strcmp(value, ",؟") ) {
      matrix.shutdown(0, false);
      Serial.println("i am in middile ");
      while (true) {
        generateFood();    // if there is no food, generate one
        scanJoystick();    // watches joystick movements & blinks with food
        calculateSnake();  // calculates snake parameters
        handleGameStates();
        if (snakeLength >= 6 && Level_2 == false ) {
          win = true;
          setLength = true ;
          lcd.print("Wins");
          delay(50);
        }
        if (snakeLength >= 6 && Level_2 == true ) {
          win = false;
          lcd.print("Wins");
          delay(50);
        }
        if (gameOver) {
          win = false ;
          Level_2 = false ;
          value = "-1";
          break ;
        }
        if (win) {
          matrix.setLed(0, 3, 3, 1);
          matrix.setLed(0, 3, 4, 1);
          matrix.setLed(0, 4, 4, 1);
          matrix.setLed(0, 4, 3, 1);
          Level_2 = true ;
        }
        if (setLength == true ) {
          snakeLength = 3 ;
          setLength = false  ;
        }
      }
    }*/

/*
    if (0 == strcmp(value, "2") ) {
      while (true) {
        generateFood();    // if there is no food, generate one
        scanJoystick();    // watches joystick movements & blinks with food
        calculateSnake();  // calculates snake parameters
        //handleGameStates();
        if (gameOver || millis() - time1 >= 5000) {
          value = "-1";
          break ;
        }
      }
    }*/
  }
  matrix.shutdown(0, true);
  // uncomment this if you want the current game board to be printed to the serial (slows down the game a bit)
  // dumpGameBoard();
}



// --------------------------------------------------------------- //
// -------------------------- functions -------------------------- //
// --------------------------------------------------------------- //


// if there is no food, generate one, also check for victory
void generateFood() {
  if (food.row == -1 || food.col == -1) {
    /*    // self-explanatory
        if (snakeLength >= 10) {
          win = true;
          return; // prevent the food generator from running, in this case it would run forever, because it will not be able to find a pixel without a snake
        }*/

    // generate food until it is in the right position
    do {
      food.col = random(8);
      food.row = random(8);
      if (Level_2 == true && (food.col == 3 || food.col == 4 ) && (food.row == 3 || food.row == 4 ))
        continue ;
    } while (gameboard[food.row][food.col] > 0);
  }
}


// watches joystick movements & blinks with food
void scanJoystick() {
  int previousDirection = snakeDirection; // save the last direction
  long timestamp = millis();

  while (millis() < timestamp + snakeSpeed) {

    // determine the direction of the snake
    analogRead(joystickY) < joystickHome.y - joystickThreshold ? snakeDirection = up    : 0;
    analogRead(joystickY) > joystickHome.y + joystickThreshold ? snakeDirection = down  : 0;
    analogRead(joystickX) < joystickHome.x - joystickThreshold ? snakeDirection = left  : 0;
    analogRead(joystickX) > joystickHome.x + joystickThreshold ? snakeDirection = right : 0;

    // ignore directional change by 180 degrees (no effect for non-moving snake)
    snakeDirection + 2 == previousDirection && previousDirection != 0 ? snakeDirection = previousDirection : 0;
    snakeDirection - 2 == previousDirection && previousDirection != 0 ? snakeDirection = previousDirection : 0;

    // intelligently blink with the food
    matrix.setLed(0, food.row, food.col, millis() % 100 < 50 ? 1 : 0);
  }
}


// calculate snake movement data
void calculateSnake() {
  switch (snakeDirection) {
    case up:
      snake.row--;
      fixEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    case right:
      snake.col++;
      fixEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    case down:
      snake.row++;
      fixEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    case left:
      snake.col--;
      fixEdge();
      matrix.setLed(0, snake.row, snake.col, 1);
      break;

    default: // if the snake is not moving, exit
      return;
  }

  // if there is a snake body segment, this will cause the end of the game (snake must be moving)
  if (gameboard[snake.row][snake.col] > 1 && snakeDirection != 0) {
    gameOver = true;
    return;
  }
  if (Level_2 ) {
    if (snake.row == 3 || snake.row == 4 ) {
      if (snake.col == 3 || snake.col == 4 ) {
        gameOver = true;
        Level_2 = false ;
        return;
      }
    }
  }

  // check if the food was eaten
  if (snake.row == food.row && snake.col == food.col) {
    food.row = -1; // reset food
    food.col = -1;

    // increment snake length
    snakeLength++;
    lcd.clear();
    score = (snakeLength - initialSnakeLength) ;
    lcd.print(score);
    // increment all the snake body segments
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] > 0 ) {
          gameboard[row][col]++;
        }
      }
    }
  }

  // add new segment at the snake head location
  gameboard[snake.row][snake.col] = snakeLength + 1; // will be decremented in a moment

  // decrement all the snake body segments, if segment is 0, turn the corresponding led off
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // if there is a body segment, decrement it's value
      if (gameboard[row][col] > 0 ) {
        gameboard[row][col]--;
      }

      // display the current pixel
      matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 0 : 1);
    }
  }
}


// causes the snake to appear on the other side of the screen if it gets out of the edge
void fixEdge() {
  snake.col < 0 ? snake.col += 8 : 0;
  snake.col > 7 ? snake.col -= 8 : 0;
  snake.row < 0 ? snake.row += 8 : 0;
  snake.row > 7 ? snake.row -= 8 : 0;
}


void handleGameStates() {
  if (gameOver ) {
    //unrollSnake();
    /* code of lcd
       // score = (snakeLength - initialSnakeLength);
        lcd.setCursor(0, 0);
        if (gameOver) lcd.write("Game Over" );
        delay(100);
        lcd.setCursor(1, 0);
        lcd.write(score );
        delay(100);
        lcd.clear();
    */
    // re-init the game
    gameOver = false;
    snake.row = random(8);
    snake.col = random(8);
    food.row = -1;
    food.col = -1;
    snakeLength = initialSnakeLength;
    snakeDirection = 0;
    memset(gameboard, 0, sizeof(gameboard[0][0]) * 8 * 8);
    matrix.clearDisplay(0);
    score = 0 ;
  }
}


void unrollSnake() {
  // switch off the food LED
  matrix.setLed(0, food.row, food.col, 0);

  delay(800);

  // flash the screen 5 times
  for (int i = 0; i < 5; i++) {
    // invert the screen
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 1 : 0);
      }
    }

    delay(20);
  }


  delay(600);

  for (int i = 1; i <= snakeLength; i++) {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] == i) {
          matrix.setLed(0, row, col, 0);
          delay(100);
        }
      }
    }
  }
}


// calibrate the joystick home for 10 times
void calibrateJoystick() {
  Coordinate values;

  for (int i = 0; i < 10; i++) {
    values.x += analogRead(joystickX);
    values.y += analogRead(joystickY);
  }

  joystickHome.x = values.x / 10;
  joystickHome.y = values.y / 10;
}

void dumpGameBoard() {
  String buff = "\n\n\n";
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (gameboard[row][col] < 10) buff += " ";
      if (gameboard[row][col] != 0) buff += gameboard[row][col];
      else if (col == food.col && row == food.row) buff += "@";
      else buff += "-";
      buff += " ";
    }
    buff += "\n";
  }
  Serial.println(buff);
}
