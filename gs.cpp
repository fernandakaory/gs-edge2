#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

//defines:
//defines para usar código de time utc
#define NTP_SERVER     "a.ntp.br"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0
 

//defines de id mqtt e tópicos para publicação e subscribe denominado TEF(Telemetria e Monitoramento de Equipamentos)
#define TOPICO_SUBSCRIBE    "/TEF/ponto0.4/cmd"        //tópico MQTT de escuta
#define TOPICO_PUBLISH      "/TEF/ponto0.4/attrs"      //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH_2    "/TEF/ponto0.4/attrs/t"    //tópico de envio da temperatura
#define TOPICO_PUBLISH_3    "/TEF/ponto0.4/attrs/m"    //tópico de envio do movimento
#define TOPICO_PUBLISH_4    "/TEF/ponto0.4/attrs/a"    //tópico de envio do horário da mudança de temperatura
#define TOPICO_PUBLISH_5    "/TEF/ponto0.4/attrs/b"    //tópico de envio do horário da captura de movimento
                         
#define ID_MQTT  "fiware_0.4"      //id mqtt (para identificação de sessão)
                        
                                
// WIFI
const char* SSID = "Wokwi-GUEST"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = ""; // Senha da rede WI-FI que deseja se conectar
  
// MQTT
const char* BROKER_MQTT = "46.17.108.113"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
 
int D4 = 2;

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';  //variável que armazena o estado atual da saída
  
//Prototypes
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
 
/* 
 *  Implementações das funções
 */
int valor = 0;
const int pir = 34;
int led=4;
float lastTemperature = 0.0;
bool lastMotionState = false;
#define DHTPIN 15           // Pino de dados do sensor DHT11
#define DHTTYPE DHT22       // Tipo do sensor DHT (DHT11)
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
    //inicializações:
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
    delay(5000);
    MQTT.publish(TOPICO_PUBLISH, "s|on");
    initLCD();
    pinMode(led, OUTPUT);

}
  
//Função: inicializa comunicação serial com baudrate 115200 (para fins de monitorar no terminal serial 
//        o que está acontecendo.
//Parâmetros: nenhum
//Retorno: nenhum
void initSerial() 
{
    Serial.begin(115200);
}
 

void initLCD()
{
  LCD.init();
    LCD.backlight();
    LCD.setCursor(0, 0);
    LCD.print("Connecting to ");
    LCD.setCursor(0, 1);
    LCD.print("WiFi ");

    WiFi.begin("Wokwi-GUEST", "", 6);
    while (WiFi.status() != WL_CONNECTED) {
      delay(250);
      spinner();
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println("Online");
    LCD.setCursor(0, 1);
    LCD.println("Updating time...");

    configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}
//Função: inicializa e conecta-se na rede WI-FI desejada
//Parâmetros: nenhum
//Retorno: nenhum
void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}
  
//Função: inicializa parâmetros de conexão MQTT(endereço do 
//        broker, porta e seta função de callback)
//Parâmetros: nenhum
//Retorno: nenhum
void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
  
// Função: função de callback 
//        esta função é chamada toda vez que uma informação de 
//        um dos tópicos subescritos chega)
// Parâmetros: nenhum
// Retorno: nenhum
bool sensorAtivo = false;
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
     
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);
    
    // Variável de controle para ativar/desativar o sensor

    //toma ação dependendo da string recebida:
   // Verifica a mensagem recebida e ativa ou desativa o sensor infravermelho
    if (msg.equals("ponto0.4@on|")) {
       // digitalWrite(sensor1, LOW); // Ativa o sensor (pino D4)
        EstadoSaida = '1';
        sensorAtivo = true;
    }

    if (msg.equals("ponto0.4@off|")) {
       // digitalWrite(sensor1, HIGH); // Desativa o sensor (pino D4)
        EstadoSaida = '0';
        sensorAtivo = false;
    }
     
}
  
//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
//        em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
//Parâmetros: nenhum
//Retorno: nenhum
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(5000);
        }
    }
}
  
//Função: reconecta-se ao WiFi
//Parâmetros: nenhum
//Retorno: nenhum
void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
       // Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}
 
//Função: verifica o estado das conexões WiFI e ao broker MQTT. 
//        Em caso de desconexão (qualquer uma das duas), a conexão
//        é refeita.
//Parâmetros: nenhum
//Retorno: nenhum
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
 
//Função: envia ao Broker o estado atual do output 
//Parâmetros: nenhum
//Retorno: nenhum
void EnviaEstadoOutputMQTT(void)
{
    if (EstadoSaida == '1')
    {
      MQTT.publish(TOPICO_PUBLISH, "s|on");
    }
    if (EstadoSaida == '0')
    {
      MQTT.publish(TOPICO_PUBLISH, "s|off");
    }
}
 
//Função: inicializa o output em nível lógico baixo
//Parâmetros: nenhum
//Retorno: nenhum
void InitOutput(void)
{
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
    
    boolean toggle = false;

    for(int i = 0; i <= 10; i++)
    {
        toggle = !toggle;
        digitalWrite(D4,toggle);
        delay(200);           
    }
}

//configura figura de spinner no lcd
void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

//função para exibição da data e horério utc
struct tm timeinfo;
void printLocalTime() {
  if (!getLocalTime(&timeinfo)) {
    LCD.setCursor(0, 1);
    LCD.println("Connection Err");
    return;
  }

  // Ajustar o deslocamento horário para UTC -3 (AST/BRT)
  timeinfo.tm_hour -= 3;
  if (timeinfo.tm_hour < 0) {
    timeinfo.tm_hour += 24;  // Garantir que o valor de hora seja positivo
  }

  LCD.setCursor(8, 0);
  LCD.println(&timeinfo, "%H:%M:%S");

  LCD.setCursor(0, 1);
  LCD.println(&timeinfo, "%d/%m/%Y   %Z");
}

//programa principal
void loop() 
{     
    printLocalTime();
    delay(250);
    char temperatureBuffer[6];
    char lastChangeTime1[20];
    char lastChangeTime2[20];

    char timeBuffer[20];
    char timeBuffer2[20];
    //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();
 
    //envia o status de todos os outputs para o Broker no protocolo esperado
    EnviaEstadoOutputMQTT();

    // Leitura da temperatura e umidade
    float temperature = dht.readTemperature();
    valor = digitalRead(pir);

    // Verifica se a temperatura mudou
    if (temperature != lastTemperature) {
        Serial.print("Temperatura: ");
        Serial.println(temperature);
        dtostrf(temperature, 4, 2, temperatureBuffer);
        strftime(timeBuffer2, sizeof(timeBuffer2), "%Y-%m-%d %H:%M:%S", &timeinfo);
        MQTT.publish(TOPICO_PUBLISH_2, temperatureBuffer);
        MQTT.publish(TOPICO_PUBLISH_4, timeBuffer2);
        lastTemperature = temperature;
    
    }

    // Verifica se a temperatura é maior ou igual a 37 graus Celsius
    if (temperature >= 37.0 && digitalRead(led) == LOW) {
        digitalWrite(led, HIGH);
    } else if (temperature < 37.0 && digitalRead(led) == HIGH) {
        digitalWrite(led, LOW);
    }

    // Verifica se o sensor PIR detectou movimento
    if (valor == HIGH && !lastMotionState) {
        lastMotionState = true;
        digitalWrite(led, HIGH);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        MQTT.publish(TOPICO_PUBLISH_3, "PACIENTE SE MOVIMENTOU");
        MQTT.publish(TOPICO_PUBLISH_5, timeBuffer);
        lastMotionState = false;
        digitalWrite(led, LOW);

     }

    //keep-alive da comunicação com broker MQTT
    MQTT.loop();
    delay(100);
}