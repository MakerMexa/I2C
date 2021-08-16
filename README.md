# I2C
programation and control using I2C protocol with modules wemos d1 mini and pcf8574, testing with multiple sensors and leds sharing information with internet client, how can improve brightness leds and options with this project


      // Importando librerías
      #include "Arduino.h"
      #include "PCF8574.h"
      #include "ESP8266WiFi.h"

      // Reemplazar con la información de la red
      const char* ssid = "yourssidname";
      const char* password = "yourpassword";

      //sensor y pines de salida
      const uint8_t sensorpin1=P2;
      const int r1=P0;
      const int v1=P1;
      int valorsensor1;

      const uint8_t sensorpin2=P3;
      const int r2=P2;
      const int v2=P3;
      int valorsensor2;

      const uint8_t sensorpin3=P4;
      const int r3=P4;
      const int v3=P5;
      int valorsensor3;

       WiFiServer server(80); //iniciando puerto de comunicacion wifi 

      PCF8574 pcf8574(0x20);// dirección del dispositivo
      PCF8574 pcf8574A (0x21);// dirección del dispositivo


      void setup(){
      //inicialiacion de modulos I2C 
      pcf8574.begin();// inicia la comunicación entre el uc y el CI PCF8574
      pcf8574A.begin();// inicia la comunicación entre el uc y el CI PCF8574
  
      pcf8574.pinMode(P0, OUTPUT); //se declará el pin PO del CI PCF8574 como SALIDA
      pcf8574.pinMode(P1, OUTPUT); //se declará el pin P1 del CI PCF8574 como SALIDA 
      pcf8574.pinMode(P2, OUTPUT); //se declará el pin P2 del CI PCF8574 como SALIDA 
      pcf8574.pinMode(P3, OUTPUT); //se declará el pin P3 del CI PCF8574 como SALIDA 
      pcf8574.pinMode(P4, OUTPUT); //se declará el pin P4 del CI PCF8574 como SALIDA 
      pcf8574.pinMode(P5, OUTPUT); //se declará el pin P5 del CI PCF8574 como SALIDA 
      pcf8574.pinMode(P6, OUTPUT); //se declará el pin P6 del CI PCF8574 como SALIDA 
      pcf8574.pinMode(P7, OUTPUT); //se declará el pin P7 del CI PCF8574 como SALIDA 
  
  
      pcf8574A.pinMode(P0, OUTPUT); //se declará el pin PO del CI PCF8574 como SALIDA 
      pcf8574A.pinMode(P1, OUTPUT); //se declará el pin P1 del CI PCF8574 como SALIDA 
      pcf8574A.pinMode(P2, INPUT); //se declará el pin P2 del CI PCF8574 como entrada 
      pcf8574A.pinMode(P3, INPUT); //se declará el pin P3 del CI PCF8574 como entrada 
      pcf8574A.pinMode(P4, INPUT); //se declará el pin P4 del CI PCF8574 como entrada 
      pcf8574A.pinMode(P5, INPUT); //se declará el pin P5 del CI PCF8574 como entrada 
      pcf8574A.pinMode(P6, INPUT); //se declará el pin P6 del CI PCF8574 como entrada 
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

      void loop(){
 
      uint8_t valorsensor1 = pcf8574A.digitalRead(sensorpin1);            // Lee el valor del pin P3 SENSOR 
      //condicion de control de leds
      if( valorsensor1 > 0)
      {
      pcf8574.digitalWrite(v1, LOW);
      pcf8574.digitalWrite(r1, HIGH);  
      }
      else 
       {
        pcf8574.digitalWrite(v1, HIGH);
        pcf8574.digitalWrite(r1, LOW); 
       }
        delay(1);
  
       uint8_t valorsensor2 = pcf8574A.digitalRead(sensorpin2);            // Lee el valor del pin P4 SENSOR 
       //condicion de control de leds 
       if(valorsensor2 > 0)
       { 
         pcf8574.digitalWrite(r2, HIGH);
         pcf8574.digitalWrite(v2, LOW);
       }
       else 
       { 
         pcf8574.digitalWrite(r2, LOW);
         pcf8574.digitalWrite(v2, HIGH);
        }
       delay(100);
 
       uint8_t valorsensor3 = pcf8574A.digitalRead(sensorpin3);             // Lee el valor del pin P5 SENSOR 
       //condicion de control de leds 
       if(valorsensor3 > 0)
       {
         pcf8574.digitalWrite(r3, HIGH);
         pcf8574.digitalWrite(v3, LOW);
       }
       else 
       {
         pcf8574.digitalWrite(v3, HIGH);
         pcf8574.digitalWrite(r3, LOW);
       }
         delay(100);
   
 
       uint8_t valorsensor4 = pcf8574A.digitalRead(sensorpin4);             // Lee el valor del pin P6 SENSOR 
       //condicion de control de leds 
       if(valorsensor4 > 0)
       {
         pcf8574.digitalWrite(r4, HIGH);
         pcf8574.digitalWrite(v4, LOW);  
       }
       else 
       {
         pcf8574.digitalWrite(v4, HIGH);
         pcf8574.digitalWrite(r4, LOW); 
        }
          delay(100);
  
     uint8_t valorsensor5 = pcf8574A.digitalRead(sensorpin5);           // Lee el valor del pin P2 SENSOr
     //condicion de control de leds 
    if(valorsensor5 > 0)
    {
      pcf8574A.digitalWrite(r5, HIGH);
      pcf8574A.digitalWrite(v5, LOW);
    }
    else 
    { 
      pcf8574A.digitalWrite(v5, HIGH);
      pcf8574A.digitalWrite(r5, LOW);
    }                
      delay(100);// Tiempo para que la comunicación se establezca con normalidad


    // Esperando nuevas conexiones 
     WiFiClient client = server.available();
    if (client) {
    Serial.println("Nuevo cliente");
    // Boleano para localizar el fin de una solicitud http
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); 
          }
          //página con HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // Código para mostrar estado de puertas en la página
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>Monitoreo Remoto de Estado</h1><h3>1:");
           
           if(valorsensor1 > 0)
             {
               client.println("o");
             }
               else{
                client.println("l");
                   }
                  delay(500);
        
          client.println("</h3><h3>2: ");
          if(valorsensor2 > 0)
            {
              client.println("o");
            }
             else{
              client.println("l");
                 }
                delay(500);
        
          client.println("</h3><h3>3: ");
         // client.println(valorsensor3)
         if(valorsensor3 > 0)
            {
              client.println("o");
            }
             else{
              client.println("l");
                 }
                delay(500);       
         
          client.println("</h3><h3>4: ");
         // client.println(valorsensor3)
         if(valorsensor4 > 0)
            {
              client.println("o");
            }
             else{
              client.println("l");
                 }
                delay(500);
         
          client.println("</h3><h3>5: ");
         // client.println(valorsensor3)
         if(valorsensor5 > 0)
            {
              client.println("o");
            }
             else{
              client.println("l");
                 }
                delay(500);
                   client.println("</h3><h3>");
                   client.println("</body>");
                   client.print("<meta http-equiv=\"refresh\" content=\"1\">");  //Actualización de la página cada segundo
                   client.println("</html>");
                   break;
             }       
      //Cerrando la conexión con el cliente
      delay(1);
      client.stop();
      Serial.println("Client disconnected.");
       }
      }
 
