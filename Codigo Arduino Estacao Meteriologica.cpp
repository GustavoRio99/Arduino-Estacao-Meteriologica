#include <LiquidCrystal.h>
#include <DHT.h>

// Pino de dados do sensor DHT
#define DHT_PIN 2
#define DHTTYPE DHT22

// Pinos do display LCD
#define RS 12
#define EN 11
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// Intervalo entre as leituras (em milissegundos)
#define INTERVALO 5000

// Instancia os objetos do LCD e do sensor DHT
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
DHT dht(DHT_PIN, DHTTYPE);

// Variável para controle do tempo
unsigned long ultimoTempo = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("INICIANDO SISTEMA");

  // Inicializa o sensor e o LCD
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();
  
  lcd.setCursor(2, 0); 
  lcd.print("INIT SYSTEM"); 
  delay(3000);
  lcd.clear();
}

void loop() {
  // Verifica se passou o tempo definido para uma nova leitura
  if (millis() - ultimoTempo >= INTERVALO) {
    ultimoTempo = millis();

    // Lê os dados do sensor
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    // Verifica se a leitura foi bem-sucedida
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Falha na leitura do sensor DHT!"));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Erro leitura DHT");
      return;
    }

    // Envia os dados via serial
    Serial.print("Temperatura (C): ");
    Serial.print(t);
    Serial.print(" | Umidade: ");
    Serial.print(h);
    Serial.print("% | Temp (F): ");
    Serial.println(f);

    // Atualiza o LCD com os valores lidos
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(h);
    lcd.print(" %");
  }
}
