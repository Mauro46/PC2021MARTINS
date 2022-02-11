/* ==================================================================================================
                                     UNIVERSIDADE EDUARDO MONDLANE
                                        FACULDADE DE ENGENHARIA
                                DEPARTAMENTO DE ENGENHARIA ELECTROTÉCNICA
                                    CURSO DE ENGENHARIA ELECTRÓNICA
                                     Relatório do Projeto do Curso
                                Casa Inteligente controlada remotamente
                                   Autor: Mauro Miguel Dos Martins
                                 Supervisor: Luis Massango, Eng⁰.
                                       Maputo, Fevereiro de 2022
   ==================================================================================================*/#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>

#define FIREBASE_HOST "pc2021uem-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Ydebf6woUcnDC7ep4VVSccmJvEnWTe24eEtDGhH0"
//#define WIFI_SSID "Redmi Note 10S"
//#define WIFI_PASSWORD "111333@5@5"
#define WIFI_SSID "CONTACTA DTICS"
#define WIFI_PASSWORD "80624172"

const int Sala = 0;
const int Quarto1 = 2;
const int Quarto2 = 15;
const int Varanda = 12;
void setup()
{
  Serial.begin(115200);
  pinMode(Sala, OUTPUT);
  pinMode(Quarto1, OUTPUT);
  pinMode(Quarto2, OUTPUT);
  pinMode(Varanda, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed())
  {
    Serial.print(Firebase.error());
  }
  else {
    Serial.print("Firebase Connected");
  }

  Firebase.setInt("S1", 0);
}
void loop()
{
 // String path = "/SALA/";
  FirebaseObject sala = Firebase.get(/SALA/);
  String LuzSala = sala.getString("estado");
  if (LuzSala == "LIGADA") {
    digitalWrite(Sala, LOW);
  }
  else if (LuzSala == "DESLIGADA") {
    digitalWrite(Sala, HIGH);
  }

 // String path = "/Quarto1/";
  FirebaseObject quarto1 = Firebase.get(/Quarto1/);
  String LuzQuarto1 = quarto1.getString("estado");
  if (LuzQuarto1 == "LIGADA") {
    digitalWrite(Quarto1, LOW);
  }
  else if (LuzQuarto1 == "DESLIGADA") {
    digitalWrite(Quarto1, HIGH);
  }

  //String path = "/Quarto2/";
  FirebaseObject quarto2 = Firebase.get(/Quarto2/);
  String LuzQuarto2 = quarto2.getString("estado");
  if (LuzQuarto2 == "LIGADA") {
    digitalWrite(Quarto2, LOW);
  }
  else if (LuzQuarto2 == "DESLIGADA") {
    digitalWrite(Quarto2, HIGH);
  }

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue > 800) {
    digitalWrite(Varanda, LOW);
  }
  else {
    digitalWrite(Varanda, HIGH);
  }
}
