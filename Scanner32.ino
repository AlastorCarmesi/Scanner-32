//Librerias necesarias para el funcionamiento del dispositivo
#include <SPI.h>
#include "WiFi.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Constantes 
#define SCREEN_WIDTH 128 //Ajustes del tamaño del dispositivo
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C //Direccion de la pantalla esto puede variar en pantalla 
#define OLED_RESET -1 //en caso de tener un reset la pantalla en caso de que no dejarlo en -1
#define SDA_PIN 21 // Pin SDA
#define SCL_PIN 22 // Pin SCL

//Se inicializa la pantalla Oled
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  //iniciamos la comunicacion con el puerto serie 
  Serial.begin(115200);

  //inicializamos la comunicacion con la pantalla Oled con los Pins correspondientes 
  Wire.begin(SDA_PIN, SCL_PIN);

  //se inicia la pantalla en caso de tener problemas se mandara un mensaje de error 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
	Serial.println(F("failed"));
	for(;;); 
  }
  display.clearDisplay();
  display.display();

  
  WiFi.mode(WIFI_STA); //ajustamos el dispositivo en modo STATION para entrar en modo cliente y escanear las redes
  WiFi.disconnect(); //En caso de que el dispositivo ESP-32 este conectado a una red este lo desconecte
  delay(100);

  //personalizacion de la pantalla OLED
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Scanner-32 ON...");
  display.display();
  delay(2000);
  display.clearDisplay();


}

void loop() {
  
  int N = WiFi.scanNetworks(); //Declaramos una variable para que esta lea las redes existentes

  //Ajustamos la pantalla
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Escaneo hecho...");

  //Creamos un ciclo If en caso de no encontrar una coincidencia este devolvera un mensaje
  if(N==0) {
    display.println("No se encontraron redes...");
  } else {
    display.print(N);
    display.println("Redes encontradas :)"); //en caso contrario este mandara un mensaje e iniciara un ciclo for 

    //en este ciclo mandaremos a llamar la variable N donde mandara las redes encontradas 
    for (int i = 0; i < N; ++i){
      //Imprime el SSID y RSSI de las redes encontradas
      display.print(i + 1); //cantidad de redes encontradas
      display.print(": ");
      display.println(WiFi.SSID(i)); //nombre de la red
      display.println(WiFi.RSSI(i)); //intensidad de la red
      display.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"------"); //en caso de que la red esta protegida
    }
  }

  display.display();
  Serial.println("...");

  delay(5000);

}
