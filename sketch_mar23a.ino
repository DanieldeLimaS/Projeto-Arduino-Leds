#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <Ethernet.h> //INCLUSÃO DE BIBLIOTECA

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 }; //ATRIBUIÇÃO DE ENDEREÇO MAC AO ETHERNET SHIELD W5100
byte ip[] = { 192, 168, 0, 19 }; //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110  **** ISSO VARIA, NO MEU CASO É: 192.168.0.175
byte gateway[] = {192, 168, 0, 1}; //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
byte subnet[] = {255, 255, 255, 0}; //MASCARA DE REDE (ALTERE PARA A SUA MÁSCARA DE REDE)
EthernetServer server(80); //PORTA EM QUE A CONEXÃO SERÁ FEITA

const int ledPin1 = 4; //PINO DIGITAL UTILIZADO PELO LED
const int ledPin2 = 2; //PINO DIGITAL UTILIZADO PELO LED
const int ledPin3 = 3; //PINO DIGITAL UTILIZADO PELO LED
String readString = String(30); //VARIÁVEL PARA BUSCAR DADOS NO ENDEREÇO (URL)
int status1 = 0; 
int status2 = 0; 
int status3 = 0; 

void setup(){
  Ethernet.begin(mac, ip, gateway, subnet); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE
  server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA 80
    pinMode(ledPin1, OUTPUT); //DEFINE O PINO COMO SAÍDA
    pinMode(ledPin2, OUTPUT); //DEFINE O PINO COMO SAÍDA
    pinMode(ledPin3, OUTPUT); //DEFINE O PINO COMO SAÍDA
      digitalWrite(ledPin1, LOW); //LED INICIA DESLIGADO
      digitalWrite(ledPin2, LOW); //LED INICIA DESLIGADO
      digitalWrite(ledPin3, LOW); //LED INICIA DESLIGADO
  }
void loop(){
EthernetClient client = server.available(); //CRIA UMA CONEXÃO COM O CLIENTE
  if (client) { // SE EXISTE CLIENTE, FAZ
    while (client.connected()) {//ENQUANTO EXISTIR CLIENTE CONECTADO, FAZ
   if (client.available()) { //SE O CLIENTE ESTÁ HABILITADO, FAZ
    char c = client.read(); //LÊ CARACTERE A CARACTERE DA REQUISIÇÃO HTTP
    if (readString.length() < 100) //SE O ARRAY FOR MENOR QUE 100, FAZ
      {
        readString += c; 
      }  
        if (c == '\n') { 
          if (readString.indexOf("?") <0){ 
          }
          else
        {
          
               //BOTAO 3
                 if(readString.indexOf("ledParam3=1") >0)
               {
                 digitalWrite(ledPin3, HIGH); 
                 status3 = 1; 
               }
               else if(readString.indexOf("ledParam3=0") >0){
                 digitalWrite(ledPin3, LOW);
                 status3 = 0;             
               }
            else if(readString.indexOf("ledParam1=1") >0)
               {
                 digitalWrite(ledPin1, HIGH); //LIGA O LED
                 status1 = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
               }
               else if(readString.indexOf("ledParam1=0") >0){
                 digitalWrite(ledPin1, LOW);
                 status1 = 0;             
               }
               //BOTAO 2
                else if(readString.indexOf("ledParam2=1") >0)
               {
                 digitalWrite(ledPin2, HIGH); 
                 status2 = 1; 
               }
               else if(readString.indexOf("ledParam2=0") >0){
                 digitalWrite(ledPin2, LOW);
                 status2 = 0;             
               }


              
        }
          client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
          client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
          client.println("");
          client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
          client.println("<html>"); //ABRE A TAG "html"
          client.println("<head>"); //ABRE A TAG "head"
          client.println("<link rel='icon' type='image/png' href='https://blogmasterwalkershop.com.br/arquivos/artigos/sub_wifi/logo_mws.png'/>"); //DEFINIÇÃO DO ICONE DA PÁGINA
          client.println("<title>MasterWalker Shop - Controle de Led via Web server</title>"); //ESCREVE O TEXTO NA PÁGINA
          client.println("</head>"); //FECHA A TAG "head"
          client.println("<body style=background-color:#ADD8E6>"); //DEFINE A COR DE FUNDO DA PÁGINA
          client.println("<center><font color='blue'><h1>Atividade com Arduino</font></center></h1>"); //ESCREVE "MASTERWALKER SHOP" EM COR AZUL NA PÁGINA
          client.println("<h1><center>CONTROLE DE LED</center></h1>"); //ESCREVE "CONTROLE DE LED" NA PÁGINA
          
        
   //BOTAO 1
          if (status1 == 1){ 
              client.println("<center><form method=get name=LED><input type=hidden name=ledParam1 value=0 /><input type=submit value='APAGAR LED 1' style='background: blue; padding:20px; border-radius:10px; color:white'></form></center>");
          }
          else{ 
              client.println("<center><form method=get name=LED><input type=hidden name=ledParam1 value=1 /><input type=submit value='ACENDER LED 1' style='background: blue; padding:20px; border-radius:10px;color:white'></form></center>");
          }
          
          client.println("<center><font size='5'>Status atual do LED 1: </font></center>");
          if (status1 == 1){
              client.println("<center><font color='green' size='5'>LIGADO</font></center>"); 
          }
          else{ 
              client.println("<center><font color='red' size='5'>DESLIGADO</font></center>"); 
          }

   //BOTAO 2
          if (status2 == 1){ 
              client.println("<center><form method=get name=LED><input type=hidden name=ledParam2 value=0 /><input type=submit value='APAGAR LED 2' style='background: blue; padding:20px; border-radius:10px;color:white'></form></center>");
          }
          else{ 
              client.println("<center><form method=get name=LED><input type=hidden name=ledParam2 value=1 /><input type=submit value='ACENDER LED 2' style='background: blue; padding:20px; border-radius:10px;color:white'></form></center>");
          }
          
          client.println("<center><font size='5'>Status atual do LED 2: </font></center>");
          if (status2 == 1){
              client.println("<center><font color='green' size='5'>LIGADO</font></center>"); 
          }
          else{ 
              client.println("<center><font color='red' size='5'>DESLIGADO</font></center>"); 
          }    


 //BOTAO 3
          if (status3 == 1){ 
              client.println("<center><form method=get name=LED><input type=hidden name=ledParam3 value=0 /><input type=submit value='APAGAR LED 3' style='background: blue; padding:20px; border-radius:10px;color:white; cursor:hand'></form></center>");
          }
          else{ 
              client.println("<center><form method=get name=LED><input type=hidden name=ledParam3 value=1 /><input type=submit value='ACENDER LED 3' style='background: blue; padding:20px; border-radius:10px;color:white'></form></center>");
          }
          
          client.println("<center><font size='5'>Status atual do LED 3: </font></center>");
          if (status3 == 1){
              client.println("<center><font color='green' size='5'>LIGADO</font></center>"); 
          }
          else{ 
              client.println("<center><font color='red' size='5'>DESLIGADO</font></center>"); 
          }  
           
          client.println("<hr/>"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("<hr/>"); //TAG HTML QUE CRIA UMA LINHA HORIZONTAL NA PÁGINA
          client.println("</body>"); //FECHA A TAG "body"
          client.println("</html>"); //FECHA A TAG "html"
          readString=""; //A VARIÁVEL É REINICIALIZADA
          client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
            }
          }
        }
      }
 }
