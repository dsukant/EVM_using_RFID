
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

String votersDatabase[4] = {

"54006B16624B", 

"54006B10557A", 

"54006B31B1BF", 

"54006B16674E", 
};

String votersName[10] = {
  "A","B","C","D"};


    int whetherCasted[10]= { 0, 0, 0, 0}; 

    int voteBank[4]={0, 0, 0, 0}; 

    String voterID="";

    boolean casted = false; 

    boolean exist = false; 

    char c ; 

    LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 



SoftwareSerial rfid(9, 10); 

void setup() 
{

    pinMode(A2, INPUT_PULLUP); 

    pinMode(A3, INPUT_PULLUP); 

    pinMode(A4, INPUT_PULLUP); 

    pinMode(A5, INPUT_PULLUP); 

    lcd.begin(16, 2); 

    lcd.display(); 


    lcd.clear(); 

    lcd.print("Welcome to EVM with Enhanced Security");
    
    delay(500);
     
    for(int sh=0; sh<21 ; sh++)
    { 
    delay(200); 
    lcd.scrollDisplayLeft(); 
    }

    delay(1000);
     
    lcd.clear();
     
    lcd.print("Start Voting"); 

    delay(2000);
     
    lcd.clear(); 

    Serial.begin(9600); 
    rfid.begin(9600);

    }

    void loop()
    {
    lcd.print("Touch RFID Card");
    delay(5000);

    if(rfid.available()>0) 
    {
    lcd.clear();
       
      voterID=voterID+String((char)rfid.read());

      if(voterID.length()==12)
      {
      gotID();
      voterID="";
      }

    } 
    
    }
    
  void gotID()
  {
  exist = false;
  casted = false;
  
  for (int i=0;i<4;i++)
    {
    if(votersDatabase[i]==voterID) // chech for valid voterID 
    {
        exist =true;
        lcd.print("Welcome,\n");
        lcd.print(votersName[i]);
        delay(5000);


         if(whetherCasted[i]==1)
     {
            lcd.clear();
      lcd.print("Voted already");
      lcd.setCursor(0,2);
      lcd.print("casted");
      delay(1000);
      lcd.clear();
     }
    
         else
     {
        while(casted == false)
      
      {
      lcd.clear();
      lcd.print("Please vote:");
      delay(1000);
      lcd.clear();
      
      
      if(digitalRead(A2)==LOW)
      {
      
      lcd.clear();
      lcd.print("Candidate A");
      casted=true;
      voteBank[0]=voteBank[0]+1;
      
      }
      
      else if(digitalRead(A3)==LOW)
      {
      lcd.clear();
      lcd.print("Candidate B");
      casted=true;
      voteBank[1]=voteBank[1]+1;      
            }
      
      else if(digitalRead(A4)== LOW)
      {
      lcd.clear();
      lcd.print ("Candidate C");
      casted = true;
      voteBank[2]=voteBank[2]+1;
      }
      
      else if(digitalRead(A5) == LOW)
      {
      lcd.clear();
      lcd.print ("Candidate D");
      casted=true;
      voteBank[3]=voteBank[3]+1;
      }
      
      delay(2000);
      
      lcd.clear();
      
      whetherCasted[i]=1;
      
      lcd.print("Vote Casted");
      
      delay(2000);
      
      lcd.clear();
      
      lcd.print ("Thanx for voting");
      
      delay(2000);
      
      lcd.clear();
      
      
      Serial.print("Tally:");            
      Serial.print("\nCandidate A=");
      Serial.print(voteBank[0]);
      Serial.print("\nCandidate B=");
      Serial.print(voteBank[1]); 
      Serial.print("\nCandidate C=");
      Serial.print(voteBank[2]);
      Serial.print("\nCandidate D=");
      Serial.print(voteBank[3]);  
      Serial.print("\n\n");
      }
       }
      }        


        if(exist == false)
        {
        lcd.print("Not Registered");
        delay(2000);
        lcd.clear();
        }   
     
  }    
      
}     







