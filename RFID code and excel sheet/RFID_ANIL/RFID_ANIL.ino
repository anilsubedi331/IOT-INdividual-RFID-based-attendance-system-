#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

String card_ID=""; //card UID

//Add as many cards you want 
String Name1="15320982152";//first UID card
String Name2="185194126152";//second UID card

int NumbCard[2];//the number of cards.
int j=0;  //incresd by one for every user added
int statu[2];//the number of cards.
int s=0;  //incresd by one for every user you add 


String Name;//user name
long Number;//user number
String ExcelName="Logs";
int L=0;
int n ;//The number of card you want to detect (optional)  
int ID=1;
void setup() {
  //lcd.begin(16, 2);
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
               
  Serial.println("Swipe your card");

  delay(200);
   }

void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }

 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID += mfrc522.uid.uidByte[i];
 }

 Serial.println("The Card id is " + card_ID);

       if(card_ID==Name1){
       Name="Anil Subedi";//user name
       Number=180273;//user number
       j=0;//incresd by one for every user you add
       s=0;//++1
      }
      else if(card_ID==Name2){
       Name="Ram rai";//user name
       Number=180000;//user number
       j=1;//++1
       s=1;//++1
      }
      else{
         Serial.println("No data found for this card");
     }

      if(NumbCard[j] == 1 && statu[s] == 0){
      statu[s]=1;
      NumbCard[j] = 0;

      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print(card_ID); //send the card ID to excel
      Serial.print(",");
      Serial.print("");
      Serial.print(",");
      Serial.println("TIME");
      ID=ID+1;
      n++;//(optional)
;
      delay(30);

      }
      else if(NumbCard[j] == 0){
      NumbCard[j] = 1;
      statu[s]=0;
      n++;
      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print(card_ID); //send the card ID to excel
      Serial.print(",");
      Serial.print("TIME");
      Serial.print(",");
      Serial.println("");
   
      delay(30);
 
      ID=ID+1;
      }
      delay(1000);

cont:
delay(1000);
card_ID="";

}
