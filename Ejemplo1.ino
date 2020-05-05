/*************************************************** 
Fuente original modulo TM1638: https://github.com/rjbatista/tm1638-library
Fuente original FreqCount: http://www.pjrc.com/teensy/td_libs_FreqCount.html
Código Arduino : 

FRECUENCIMETRO DE 4 CANALES

*********  VIDEO DEL EJEMPLO ACA ************ 

 ****************************************************/
 
#include <FreqCount.h>
#include <TM1638.h>

// definir un módulo en el pin de datos 8, pin de reloj 9 y pin de estroboscopio 7
TM1638 module(8, 9, 7);

// ******** Variables  ****************************************************************************
  const char string[] = "      ELEKTRONICA PROJECT -  FRECUENCIMETRO CON ARDUINO Y TM1638        ";
  int base = 0; // Variable con controla la longitud del mensaje
  int intro_aux=0; //Variable que define si el mensaje intro ya termino
  // Pines analógicos que utilizaremos como entrada de datos 
  int FREC1 = 14; // Frecuencia 1 - Entrada analogica A0 
  int FREC2 = 15; // Frecuencia 2 - Entrada analogica A1 
  int FREC3 = 16; // Frecuencia 3 - Entrada analogica A2 
  int FREC4 = 17; // Frecuencia 4 - Entrada analogica A3 
  
  
void setup() {
  Serial.begin(57600);
  Serial.println("Ejemplo 2 - Frecuencimetro con TM1638 ");
  FreqCount.begin(1000);

 // ******** Usamos los pines nalgicos de Arduino como pines digitales de salida *******
  pinMode(FREC1, OUTPUT);
  pinMode(FREC2, OUTPUT);
  pinMode(FREC3, OUTPUT);
  pinMode(FREC4, OUTPUT);
  
}

void loop() {

   if(intro_aux==0){
   intro();   //Subruina de encedido del display introduccion
  
   //****** Iniciamos con leyendo el canal 1 de frecuencias *******
   module.setLEDs(B00000001); // Encendemos el primer led 
   digitalWrite(FREC1, HIGH);
   digitalWrite(FREC2, LOW);
   digitalWrite(FREC3, LOW);
   digitalWrite(FREC4, LOW);
   }else{

   // ****** Leemos los botones de la placa TM1638 **********
   byte keys = module.getButtons();
   
   // ****** Si presionamos el boton S1 desginara el cana1 1 ****** 
   if (keys == B00000001 ){
    delay(200);
    Serial.print("Boton presionado: "); Serial.println(keys);
    module.setLEDs(B00000001); // Encendemos el primer led 
    digitalWrite(FREC1, HIGH);
    digitalWrite(FREC2, LOW);
    digitalWrite(FREC3, LOW);
    digitalWrite(FREC4, LOW);
    }
   
   // ****** Si presionamos el boton S2 desginara el cana1 2 ****** 
   if (keys == B00000010 ){
    delay(200);
    Serial.print("Boton presionado: "); Serial.println(keys);
    module.setLEDs(B00000010);  // Encendemos el segundo led 
    digitalWrite(FREC1, LOW);
    digitalWrite(FREC2, HIGH);
    digitalWrite(FREC3, LOW);
    digitalWrite(FREC4, LOW);
    }
   
   // ****** Si presionamos el boton S3 desginara el cana1 3 ****** 
   if (keys == B00000100 ){
    delay(200);
    Serial.print("Boton presionado: "); Serial.println(keys);
    module.setLEDs(B00000100);  // Encendemos el tercer led 
    digitalWrite(FREC1, LOW);
    digitalWrite(FREC2, LOW);
    digitalWrite(FREC3, HIGH);
    digitalWrite(FREC4, LOW);
    }

   // ****** Si presionamos el boton S4 desginara el cana1 4 ****** 
   if (keys == B00001000 ){
    delay(200);
    Serial.print("Boton presionado: "); Serial.println(keys);
    module.setLEDs(B00001000);  // Encendemos el cuarto led 
    digitalWrite(FREC1, LOW);
    digitalWrite(FREC2, LOW);
    digitalWrite(FREC3, LOW);
    digitalWrite(FREC4, HIGH);
    }
   
   if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    Serial.println(count);
    module.setDisplayToDecNumber(count, 0x00);
    delay(500);
    }
   }
  }

/********** SUB RUTINAS *******************************************************************************
 *  ***************************************************************************************************
 */
/* Se crea una subrutina void para hacer el encendido del display 
 */
void intro()  //Funcion que activa el display
{
 if(base < 68){
  const char* pos = string + base ;

    if (pos >= string && pos + 8 < string + sizeof(string)) {
      module.setDisplayToString(pos);    }
    else {
      module.clearDisplay();       }
    base++;
    delay(100);    }
    else{
      intro_aux=1;
     
      module.setLEDs(B00000001);
      delay(50);    
      module.setLEDs(B00000010);
      delay(50);    
      module.setLEDs(B00000100);
      delay(50);    
      module.setLEDs(B00001000);
      delay(50);   
      module.setLEDs(B00010000);
      delay(50);   
      module.setLEDs(B00100000);
      delay(50);    
      module.setLEDs(B01000000);
      delay(50);    
      module.setLEDs(B10000000);
      delay(50);  
      }
  }

 
