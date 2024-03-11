#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>


#define RST_PIN 20 // DONT TOUCH IT
#define SS_PIN  53 // I SAID NO

#define buttonsCount 5
#define buttonFault 10

#define rightButton 0
#define topButton 143
#define downButton 341
#define leftButton 510
#define selectButton 730

int buttonValue;
int selected = 0; // 0 for the first element (id of element which is choosen now)
int maxInMenu;
int currentButton = -1; // button index (0 - 4)
int buttonsValuesList[buttonsCount] = { rightButton + buttonFault, 
                                        topButton + buttonFault, 
                                        downButton + buttonFault,
                                        leftButton + buttonFault, 
                                        selectButton + buttonFault 
                                       };



LiquidCrystal lcd(8, 9, 4, 5, 6, 7);    // correct pins for lcd1602 keyboard shield
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


void setup() {
  Serial.begin(9600); // The most popular bog rate for this board

  lcd.begin(16, 2); // display with 16 columns (with 1 symvol in one) and 2 rows
  // lcd.clear(); // clear display
  lcd.setCursor(0, 0); // start point for drawing (in null column and first row)
  // lcd.print("hello, world!");

  // RC522 init
  SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(40);				// Optional delay
	// mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details

  showDemo(); // loading screen

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.println("Ready for use");

  // just to remember
  // lcd.autoscroll();
  // lcd.noAutoscroll();
} 

void loop() {
  updateMainMenu();

  currentButton = detectButton();
  delay(200);

  Serial.print("Detected button ID: ");
  Serial.println(currentButton);

  // menu navigation
  if (currentButton == 2) {
    if (selected + 1 < maxInMenu) {
      selected++;
    } else {
      selected = 0;
    }
  } else if (currentButton == 1) {
    if (selected - 1 >= 0) {
      selected--;
    } else {
      selected = maxInMenu - 1;
    }
  } else if (currentButton == 4) {
    switch (selected) {
      case 0: 
              showUID();
              break;
      case 1:
              rewriteUID();
              break;

      default: return;
    }
  }
}


void updateMainMenu() {
  Serial.println("Main manu has been updated.");

  // configs for menu
  maxInMenu = 2; // menu has only maxInMenu elements

  // drawing menu (i didnt used printTop/bottom funcs cause had a problem with adding after ternary operator)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print((selected == 0) ? ">" : " ");
  lcd.print("Show  UID");
  lcd.setCursor(0, 1);
  lcd.print((selected == 1) ? ">" : " ");
  lcd.print("Rewrite UID");
}



void rewriteUID() {
  // base instructions
  String instruction1 = "Put a mark on the scanner to save it.";
  String instruction2 = "To write UID choose it and press Select.";
  String instruction3 = "Use Right/Left and Select buttons.";

  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.autoscroll();

  // for (int i = 0; i < 61; i++) {
  //   lcd.print(instruction1[i]);
  //   delay(150);
  // }

  // lcd.clear();
  // lcd.setCursor(0, 1);

  // for (int i = 0; i < 64; i++) {
  //   lcd.print(instruction2[i]);
  //   delay(150);
  // }

  // lcd.clear();
  // lcd.setCursor(0, 0);

  // for (int i = 0; i < 58; i++) {
  //   lcd.print(instruction3[i]);
  //   delay(150);
  // }

  // lcd.noAutoscroll();
  lcd.clear();

  // 10 availabel "fields" for UID
  int filedsCount = 10;
  int savedUIDs[filedsCount][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };

  int selectedField = 0;
  int menuOptionsCount = filedsCount + 2;

  while (true) {
    lcd.clear();
    if (selectedField < filedsCount){
      // print filed data
      String UID_INFO = "";
      for (byte i = 0; i < 4; i++) {
        UID_INFO += String(savedUIDs[selectedField][i], HEX) + " ";
      }

      lcd.clear();
      printTop("#" + (String) selectedField + ": " + UID_INFO);
    } else { // print another helpful options
      if (selectedField == (filedsCount + 1) - 1) printTop(" Delete all");
      if (selectedField == (filedsCount + 2) - 1) printTop(" Back");
    }


    currentButton = detectCurrentButton();
    if (currentButton != -1) {
      // if any button delected
      Serial.print("Detected button ID: ");
      delay(200);
      
      // keys functions
      switch (currentButton) {
        case 0: // right key
          if (selectedField + 1 < menuOptionsCount) {
            selectedField++;
          } else {
            selectedField = 0;
          }

          break;

        case 3: // left key
          if (selectedField - 1 >= 0) {
            selectedField--;
          } else {
            selectedField = menuOptionsCount - 1;
          }

          break;
        
        case 4:
          if (selectedField < filedsCount) { // write new UID
            delay(500);

            lcd.clear();
            printTop("Ready to write");

            byte newUID[] = {0x0, 0x0, 0x0, 0x0};

            String UID_INFO = "";
            for (byte i = 0; i < 4; i++) {
              UID_INFO += String(savedUIDs[selectedField][i], HEX) + " ";
              newUID[i] = (byte) savedUIDs[selectedField][i];
            }

            printBottom("  " +  UID_INFO);

            // waiting for the mark or untill button will be pressed
            do {} while ( (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) && !detectAnyButton());

            if ( mfrc522.MIFARE_SetUid(newUID, (byte) 4, true) ) {
              Serial.println(F("Wrote new UID to card."));
              
              mfrc522.PICC_HaltA();
              if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
                return;
              }

              lcd.clear();
              printTop("Success.");
              delay(1000);
              return;
            } else {
              lcd.clear();
              printTop("Error");
              printBottom("Can`t change UID");
              
              delay(1000);
            }
          } else {
            if (selectedField == (filedsCount + 1) - 1) { // delete all option
              int savedUIDs[filedsCount][4] = {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
              };

              int selectedField = 0;
            }
            if (selectedField == (filedsCount + 2) - 1) return; // back option
          }
      }
    } else if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())  // if card has been detected
    {
      if (selectedField < filedsCount) {
        Serial.println(selectedField);
        // read UID and write to the field
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          savedUIDs[selectedField][i] = mfrc522.uid.uidByte[i];
        }
      }
    }

    else { // if nothing happend just set delay
      delay(100);
    }
  }
}


void showUID() {
  lcd.clear();
  delay(400);

  lcd.clear();
  printTop("[SHOW UID]");
  printBottom("Hold but to exit");

  while (true) {
    if (detectAnyButton()){
      selected = 0;
      delay(300);
      return;
    }

    if ( ! mfrc522.PICC_IsNewCardPresent()) continue; // Reset the loop if no new card present on the sensor/reader. This saves the entire process.
    if ( ! mfrc522.PICC_ReadCardSerial()) continue; // Select one of the cards

    String UID_INFO = "";

    for (byte i = 0; i < mfrc522.uid.size; i++) {
      UID_INFO += String(mfrc522.uid.uidByte[i], HEX) + " ";
    }

    lcd.clear();
    printTop("[SHOW UID]");
    printBottom(UID_INFO);
    delay(100);
  }
}

// func for showing load demo screen

void showDemo() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Create by:");
  lcd.setCursor(5, 1);
  lcd.print("$Admin");

  Serial.println("Create by: $Admin");

  delay(1500);
  lcd.clear();
}


// simply base functions

void printTop(String text) {
  lcd.setCursor(0, 0);
  lcd.print(text);
}

void printBottom(String text) {
  lcd.setCursor(0, 1);
  lcd.print(text);
}

bool detectAnyButton() {
  if (analogRead(A0) < 1020) return true;
  return false;
}

int detectButton() {
  // waiting for pressing a button
  do {
    buttonValue = analogRead(A0);
  } while (buttonValue > 1020);

  for (int i = 0; i < buttonsCount; i++) {
    if (buttonValue < buttonsValuesList[i]) return i;
  }
}

int detectCurrentButton() {
  buttonValue = analogRead(A0);

  for (int i = 0; i < buttonsCount; i++) {
    if (buttonValue < buttonsValuesList[i]) return i;
  }

  return -1;
}