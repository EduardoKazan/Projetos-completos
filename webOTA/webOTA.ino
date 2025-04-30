
// Exemplo de WebOTA 
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>

//Parâmetros da rede WiFi
const char* ssid = "xxxxxxxxxx";
const char* password = "yyyyyyy";

//Parâmetros de rede
IPAddress local_ip(192, 168, 0, 121);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
const uint32_t PORTA = 80; //A porta que será utilizada (padrão 80)

//Algumas informações que podem ser interessantes
const uint32_t chipID = (uint32_t)(ESP.getEfuseMac() >> 32); //um ID exclusivo do Chip...
const String CHIP_ID = "<p> Chip ID: " + String(chipID) + "</p>"; // montado para ser usado no HTML
const String VERSION = "<p> Versão: 3.0 </p>"; //Exemplo de um controle de versão

//Informações interessantes agrupadas
const String INFOS = VERSION + CHIP_ID;

//Sinalizador de autorização do OTA
boolean OTA_AUTORIZADO = false;

//inicia o servidor na porta selecionada
//aqui testamos na porta 3000, ao invés da 80 padrão
WebServer server(PORTA);

//Páginas HTML utilizadas no procedimento OTA
String verifica = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Digite a chave de verificação.<p>Clique em ok para continuar. . .</p></h2>" + INFOS + "<form method='POST' action='/avalia 'enctype='multipart/form-data'> <p><label>Autorização: </label><input type='text' name='autorizacao'></p><input type='submit' value='Ok'></form></body></html>";
String serverIndex = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Selecione o arquivo para a atualização e clique em atualizar.</h2>" + INFOS + "<form method='POST' action='/update' enctype='multipart/form-data'><p><input type='file' name='update'></p><p><input type='submit' value='Atualizar'></p></form></body></html>";
String Resultado_Ok = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Atualização bem sucedida!</h2>" + INFOS + "</body></html>";
String Resultado_Falha = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Falha durante a atualização. A versão anterior será recarregado.</h2>" + INFOS + "</body></html>";

//Setup
void setup(void)
{
  Serial.begin(115200); //Serial para debug

  WiFi.mode(WIFI_AP_STA); //Comfigura o ESP32 como ponto de acesso e estação

  WiFi.begin(ssid, password);// inicia a conexão com o WiFi

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (WiFi.status() == WL_CONNECTED) //aguarda a conexão
  {
    //atende uma solicitação para a raiz
    // e devolve a página 'verifica'
    server.on("/", HTTP_GET, []() //atende uma solicitação para a raiz
    {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", verifica);
    });

    //atende uma solicitação para a página avalia
    server.on("/avalia", HTTP_POST, [] ()
    {
      Serial.println("Em server.on /avalia: args= " + String(server.arg("autorizacao"))); //somente para debug

      if (server.arg("autorizacao") != "123456") // confere se o dado de autorização atende a avaliação
      {
        //se não atende, serve a página indicando uma falha
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", Resultado_Falha);
        //ESP.restart();
      }
      else
      {
        //se atende, solicita a página de índice do servidor
        // e sinaliza que o OTA está autorizado
        OTA_AUTORIZADO = true;
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", serverIndex);
      }
    });

    //serve a página de indice do servidor
    //para seleção do arquivo
    server.on("/serverIndex", HTTP_GET, []()
    {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex);
    });

    //tenta iniciar a atualização . . .
    server.on("/update", HTTP_POST, []()
    {
      //verifica se a autorização é false.
      //Se for falsa, serve a página de erro e cancela o processo.
      if (OTA_AUTORIZADO == false)
      {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", Resultado_Falha);
        return;
      }
      //Serve uma página final que depende do resultado da atualização
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", (Update.hasError()) ? Resultado_Falha : Resultado_Ok);
      delay(1000);
      ESP.restart();
    }, []()
    {
      //Mas estiver autorizado, inicia a atualização
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START)
      {
        Serial.setDebugOutput(true);
        Serial.printf("Atualizando: %s\n", upload.filename.c_str());
        if (!Update.begin())
        {
          //se a atualização não iniciar, envia para serial mensagem de erro.
          Update.printError(Serial);
        }
      }
      else if (upload.status == UPLOAD_FILE_WRITE)
      {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
        {
          //se não conseguiu escrever o arquivo, envia erro para serial
          Update.printError(Serial);
        }
      }
      else if (upload.status == UPLOAD_FILE_END)
      {
        if (Update.end(true))
        {
          //se finalizou a atualização, envia mensagem para a serial informando
          Serial.printf("Atualização bem sucedida! %u\nReiniciando...\n", upload.totalSize);
        }
        else
        {
          //se não finalizou a atualização, envia o erro para a serial.
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
      else
      {
        //se não conseguiu identificar a falha no processo, envia uma mensagem para a serial
        Serial.printf("Atualização falhou inesperadamente! (possivelmente a conexão foi perdida.): status=%d\n", upload.status);
      }
    });

    server.begin(); //inicia o servidor

    Serial.println(INFOS); //envia as informações armazenadas em INFOS, para debug

    //Envia ara a serial o IP atual do ESP
    Serial.print("Servidor em: ");
    Serial.println( WiFi.localIP().toString() + ":" + PORTA);
  }
  else
  {
    //avisa se não onseguir conectar no WiFi
    Serial.println("Falha ao conectar ao WiFi.");
  }
}

void loop(void)
{
  //manipula clientes conectados
  server.handleClient();

  delay(1);//somente um instante
}
