//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (enter_param()) {
    Serial.println();
    Serial.println();
    Serial.print(" ");
    Serial.print('#');
    Serial.print(" ");
  }
}

short enter_param(void);
void process_command(char *cmd);
short cursor_position(void);
short write_mode(void);
void help(void);

void usart0_init(unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1 << TXEN0);
}

void usart0_write(char data) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = data;
}

char usart0_read() {
  while (!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

void disp_init() {
  lcd.init();
  lcd.backlight();
}

void disp_cmd(char cmd) {
  lcd.command(cmd);
}

void disp_write(char data) {
  lcd.print(data);
}

void disp_clear() {
  lcd.clear();
}

void _delay_ms(unsigned int delay) {
  delay = (delay / 10) * 8;
  while (delay--)
    ;
}
short enter_param() {
  static short counter = 0;       // auxiliary counter for string index
  register unsigned short i;      // iterations variable
  static char cmds[100] = { 0 };  // string of commands
  char key = 0;                   // stores the key pressed

  if (Serial.available() > 0) {  // are there data from UART?
    key = Serial.read();         // read data and stores in the key variable

    if (key == '\r') {        // enter pressed?
      process_command(cmds);  // verify and process command

      for (i = 0; i < 100; i++)
        cmds[i] = 0;  // clear all string of commands

      counter = 0;  // restart counter
      return 1;     // return done status
    }

    else if (key == '\b') {   // backspace pressed?
      Serial.print("\b \b");  // clear character

      if (counter >= 0)
        cmds[--counter] = 0;  // adjust string position
    }

    else {                          // read characters of command
      cmds[counter] = key;          // save keys on commands string
      Serial.print(cmds[counter]);  // echo

      counter++;  // increment for the next character

      if (counter > 99)  // max 100 bytes
        counter = 0;
    }
  }

  return 0;
}

void process_command(char *cmd) {
  if (!strcmp(cmd, "clear"))
    lcd.clear();
  else if (!strcmp(cmd, "home"))
    lcd.home();
  else if (!strcmp(cmd, "cursor")) {
    Serial.println();
    Serial.print("; Row: ");
    while (!cursor_position())
      ;
  } else if (!strcmp(cmd, "write")) {
    Serial.println();
    Serial.print("? ");
    while (!write_mode())
      ;
  } else if (!strcmp(cmd, "blink_on"))
    lcd.blink();
  else if (!strcmp(cmd, "blink_off"))
    lcd.noBlink();
  else if (!strcmp(cmd, "led_on"))
    digitalWrite(LED_BUILTIN, HIGH);
  else if (!strcmp(cmd, "led_off"))
    digitalWrite(LED_BUILTIN, LOW);
  else if (!strcmp(cmd, "help"))
    help();
  else
    Serial.println();
  Serial.print("* SYNTAX ERROR!");
}

short cursor_position() {
  static short index = 0, digs[3] = { 0 };
  static short done = 0, val = 0, row = 0, col = 0;
  char key = 0;

  if (Serial.available() > 0) {
    key = Serial.read();

    if (key == '\r') {
      switch (index) {
        case 1:
          index = 0;
          val = digs[0];
          break;
        case 0:
          index = 0;
          val = digs[0] * 10 + digs[1];
          break;
      }

      switch (done) {
        case 0:
          row = val;
          val = 0;
          done++;
          Serial.print("; Col: ");
          break;
        case 1:
          col = val;
          val = 0;
          done++;
          break;
      }

      if (!row)
        lcd.setCursor(col, 0);
      else
        lcd.setCursor(col, 1);

      if (done == 2) {
        col = row = done = 0;
        index = 0;
        return 1;
      }
    }

    else if (key == '\b') {
      Serial.print("\b \b");

      if (index >= 0)
        digs[--index] = 0;
    }

    else {
      switch (index) {
        case 0:
          index = 1;
          digs[0] = key - 0x30;
          Serial.print((char)digs[0] + 0x30);
          break;
        case 1:
          index = 0;
          digs[1] = key - 0x30;
          Serial.print((char)digs[1] + 0x30);
          break;
      }
    }
  }

  return 0;
}

short write_mode() {
  static short position = 0;
  register unsigned short i;
  static char chrs[100] = { 0 };
  char key = 0;

  if (Serial.available() > 0) {
    key = Serial.read();

    if (key == '\r') {
      for (i = 0; i < 100; i++)
        chrs[i] = 0;

      position = 0;
      return 1;
    }

    else if (key == '\b') {
      Serial.print("\b \b");

      lcd.setCursor(position, 1);
      lcd.print(" ");
      lcd.setCursor(position, 1);

      if (position >= 0)
        chrs[--position] = 0;
    }

    else {
      chrs[position] = key;
      Serial.print(chrs[position]);

      lcd.setCursor(position, 1);
      lcd.print(chrs[position]);

      position++;

      if (position > 99)
        position = 0;
    }
  }

  return 0;
}

void help() {
  Serial.println();
  Serial.println(" | Commands LCD Control v1.0");
  Serial.println(" | clear     : LCD clear");
  Serial.println(" | home      : position cursor row 0 column 0");
  Serial.println(" | cursor    : update row and column cursor");
  Serial.println(" | write     : LCD write mode");
  Serial.println(" | blink_on  : cursor blink on");
  Serial.println(" | blink_off : cursor blink off");
  Serial.println(" | led_on    : turns LED ON");
  Serial.println(" | led_off   : turns LED OFF");
}
