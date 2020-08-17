#include <LiquidCrystal.h>
#include <Keypad.h>
const byte ROWS = 5;
const byte COLS = 4;
char keys [ROWS] [COLS] = {
  {'+', '=', '.', '0'},
  {'-', '3', '2', '1'},
  {'*', '6', '5', '4'},
  {'/', '9', '8', '7'},
  {'%', '^', '$', 'C'}
  
};
byte rowPins[ROWS] = {9,10,11,12,13};
byte colPins[COLS] = {5,6,7,8};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


boolean presentValue = false;
boolean percentage = false;
boolean next = false;
boolean final = false;
String num1, num2;

LiquidCrystal lcd(4, 3, 2, A5, A4, A3);

float answer;
char op;

void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Shreyas");
  lcd.setCursor(0,1);
  lcd.print("    Presents    ");
  delay(5000);
  lcd.setCursor(0,0);
  lcd.print("Hardware");
  lcd.setCursor(0,1);
  lcd.print("  Calculator"    );

  delay(5000);
  lcd.clear();
}

void loop(){
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'||key=='.'))
  {
    if (presentValue != true)
    {
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
      percentage = true;
      
    }
    else 
    {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }
 else if (percentage == true && key != NO_KEY && (key == '%'))
      {
        answer = (num1.toFloat())/100;
         op = key;
      lcd.setCursor(15,0);
      lcd.print(op);
          lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(answer);
      lcd.noAutoscroll();
        }

  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'||key== '^'||key== '$'))
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
      lcd.setCursor(15,0);
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      answer = num1.toFloat() + num2.toFloat();
    }
    else if (op == '-'){
      answer = num1.toFloat() - num2.toFloat();
    }
    else if (op == '*'){
      answer = num1.toFloat() * num2.toFloat();
    }
    else if (op == '/'){
      answer = num1.toFloat() / num2.toFloat();
    }    
     else if (op == '^'){
      answer = pow(num1.toFloat(),num2.toFloat());
    }    
     else if (op == '$'){
      answer = pow(num1.toFloat(),1/(num2.toFloat()));
    }    
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(answer);
      lcd.noAutoscroll();
  }
  else if (key != NO_KEY && key == 'C'){
    lcd.clear();
    presentValue = false;
    final = false;
    percentage = false;
    num1 = "";
    num2 = "";
    answer = 0;
    op = ' ';
  }
}
