//by : J.L.L.

// Importando librerías del ESP8266
#include <Arduino.h>
#include <PCF8574.h>
#include <Adafruit_ESP8266.h>

// Reemplazar con la información de la red
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";


//sensor y pines de salida
//traffic lights1
const uint8_t sensorpin1=P2;
const int rojo1=P0;
const int verde1=P1;
int valorsensor1;
//traffic lights2
const uint8_t sensorpin2=P3;
const int rojo2=P2;
const int verde2=P3;
int valorsensor2;
//traffic lights3
const uint8_t sensorpin3=P4;
const int rojo3=P4;
const int verde3=P5;
int valorsensor3;

//traffic lights4
const uint8_t sensorpin4=P5;
const int rojo4=P6;
const int verde4=P7;
int valorsensor4;

//traffic lights5
const uint8_t sensorpin5=P6;
const int rojo5=P0;
const int verde5=P1;
int valorsensor5;

PCF8574 pcf8574(0x20);// dirección del dispositivo
PCF8574 pcf8574A (0x21);// dirección del dispositivo

WiFiServer server(80); //iniciando puerto de comunicacion wifi

void setup() {
  pcf8574.begin();// inicia la comunicación entre el uc y el CI PCF8574 LEDS 
  pcf8574A.begin();// inicia la comunicación entre el uc y el CI PCF8574 LED Y SENSORES
  pcf8574.pinMode(P0, OUTPUT); //se declará el pin PO del CI PCF8574 como SALIDA LEDROJO traffic lights1
  pcf8574.pinMode(P1, OUTPUT); //se declará el pin P1 del CI PCF8574 como SALIDA LEDVERDE traffic lights1
  pcf8574.pinMode(P2, OUTPUT); //se declará el pin P2 del CI PCF8574 como SALIDA LEDROJO traffic lights2
  pcf8574.pinMode(P3, OUTPUT); //se declará el pin P3 del CI PCF8574 como SALIDA LEDVERDE traffic lights2
  pcf8574.pinMode(P4, OUTPUT); //se declará el pin P4 del CI PCF8574 como SALIDA LEDROJO traffic lights3
  pcf8574.pinMode(P5, OUTPUT); //se declará el pin P5 del CI PCF8574 como SALIDA LEDVERDE traffic lights3
  pcf8574.pinMode(P6, OUTPUT); //se declará el pin P6 del CI PCF8574 como SALIDA LEDROJO traffic lights4
  pcf8574.pinMode(P7, OUTPUT); //se declará el pin P7 del CI PCF8574 como SALIDA LEDVERDE traffic lights4

  pcf8574A.pinMode(P0, OUTPUT); //se declará el pin PO del CI PCF8574 como SALIDA LEDROJO traffic lights5
  pcf8574A.pinMode(P1, OUTPUT); //se declará el pin P1 del CI PCF8574 como SALIDA LEDVERDE traffic lights5
  pcf8574A.pinMode(P2, INPUT); //se declará el pin P2 del CI PCF8574 como entrada SENSOR traffic lights1
  pcf8574A.pinMode(P3, INPUT); //se declará el pin P3 del CI PCF8574 como entrada SENSOR traffic lights2
  pcf8574A.pinMode(P4, INPUT); //se declará el pin P4 del CI PCF8574 como entrada SENSOR traffic lights3
  pcf8574A.pinMode(P5, INPUT); //se declará el pin P5 del CI PCF8574 como entrada SENSOR traffic lights4
  pcf8574A.pinMode(P6, INPUT); //se declará el pin P6 del CI PCF8574 como entrada SENSOR traffic lights5
  pcf8574A.pinMode(P7, INPUT); //se declará el pin P7 del CI PCF8574 como entrada

  // Iniciando y configurando velocidad del Puerto Serial
  Serial.begin(115200);
  delay(10);

  // Conectando a la red WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  // Starting the web server
  server.begin();
  Serial.println("Web server ejecutándose. Esperando a la ESP IP...");
  delay(10000);

  // Mostrar la dirección ESP IP en el Monitor Serie
  Serial.println(WiFi.localIP());

  
}

void loop() {
 // Esperando nuevas conexiones (clientes)
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo cliente");
    // Boleano para localizar el fin de una solicitud http
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); 
          }
         //Maquetación de la página con HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // Código html para mostrar estado de puertas en la página
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>Monitoreo Remoto de Estado</h1><h3>traffic lights1:");
         //traffic lights1
           if(valorsensor1 > 0)
             {
               client.println("ocupado");
             }
               else{
                client.println("libre");
                   }
                
         //traffic lights2
          client.println("</h3><h3>traffic lights2: ");
          if(valorsensor2 > 0)
            {
              client.println("ocupado");
            }
             else{
              client.println("libre");
                 }
              
         //traffic lights3
          client.println("</h3><h3>traffic lights3: ");
         if(valorsensor3 > 0)
            {
              client.println("ocupado");
            }
             else{
              client.println("libre");
                 }
                   
         //traffic lights4
          client.println("</h3><h3>traffic lights4: ");
         if(valorsensor4 > 0)
            {
              client.println("ocupado");
            }
             else{
              client.println("libre");
                 }
                delay(500);
         //traffic lights5
          client.println("</h3><h3>traffic lights5: ");
         if(valorsensor5 > 0)
            {
              client.println("ocupado");
            }
             else{
              client.println("libre");
                 }
               
                   client.println("</h3><h3>");
                   client.println("</body>");
                   client.print("<meta http-equiv=\"refresh\" content=\"1\">");  //Actualización de la página cada segundo
                   client.println("</html>");
                   break;
    } 
   //Cerrando la conexión con el cliente
  client.stop();
  Serial.println("Client disconnected.");
  }
 trafficLights1();
 trafficLights2();
 trafficLights3();
 trafficLights4();
 trafficLights5();
}

void trafficLights1(){
 uint8_t valorsensor1 = pcf8574A.digitalRead(sensorpin1);            // Lee el valor del pin P3 SENSOR trafficLights1

 if( valorsensor1 > 0)
 {
   pcf8574.digitalWrite(verde1, LOW);
   pcf8574.digitalWrite(rojo1, HIGH);  
  }
 else 
 {
   pcf8574.digitalWrite(verde1, HIGH);
   pcf8574.digitalWrite(rojo1, LOW); 
  }
  delay(1);
  
}

void trafficLights2(){
 uint8_t valorsensor2 = pcf8574A.digitalRead(sensorpin2);            // Lee el valor del pin P4 SENSOR trafficLights2
  
 //enviar mensaje
 if(valorsensor2 > 0)
 { 
   pcf8574.digitalWrite(rojo2, HIGH);
   pcf8574.digitalWrite(verde2, LOW);
  }
 else 
 { 
   pcf8574.digitalWrite(rojo2, LOW);
   pcf8574.digitalWrite(verde2, HIGH);
  }
  delay(100);
 
}


void trafficLights3(){
  uint8_t valorsensor3 = pcf8574A.digitalRead(sensorpin3);             // Lee el valor del pin P5 SENSOR trafficLights3
  
 //enviar mensaje
 if(valorsensor3 > 0)
 {
   pcf8574.digitalWrite(rojo3, HIGH);
   pcf8574.digitalWrite(verde3, LOW);
  }
 else 
 {
   pcf8574.digitalWrite(verde3, HIGH);
   pcf8574.digitalWrite(rojo3, LOW);
  }
  delay(100);  
}

void trafficLights4(){
   uint8_t valorsensor4 = pcf8574A.digitalRead(sensorpin4);             // Lee el valor del pin P6 SENSOR trafficLights4
  
 //enviar mensaje
 if(valorsensor4 > 0)
 {
   pcf8574.digitalWrite(rojo4, HIGH);
   pcf8574.digitalWrite(verde4, LOW);  
  }
 else 
 {
   pcf8574.digitalWrite(verde4, HIGH);
   pcf8574.digitalWrite(rojo4, LOW); 
  }
  delay(100);
}

void trafficLights5(){
 uint8_t valorsensor5 = pcf8574A.digitalRead(sensorpin5);           // Lee el valor del pin P2 SENSOR trafficLights5
 
 //enviar mensaje
 if(valorsensor5 > 0)
 {
   pcf8574A.digitalWrite(rojo5, HIGH);
   pcf8574A.digitalWrite(verde5, LOW);
  }
 else 
 { 
   pcf8574A.digitalWrite(verde5, HIGH);
   pcf8574A.digitalWrite(rojo5, LOW);
  }                
  delay(100);// Tiempo para que la comunicación se establezca con normalidad
}

  
