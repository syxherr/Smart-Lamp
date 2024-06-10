

#include <ESP8266WiFi.h> //library ESP8266wifi yang telah diimportkan

#define ON LOW
#define OFF HIGH

const char* ssid = "lunaa";
const char* password = "terserah";
 
int relay1 = 5; //D1 on ESP Board
int relay2 = 4; //D2 on ESP Board
int relay3 = 00; //D3 on ESP Board
int relay4 = 2;  //D4 on ESP Board

int value1 = OFF, value2 = OFF, value3 = OFF, value4 = OFF, valueall=OFF;

//menggunakan port 80 untuk http
WiFiServer server(80);    

void setup(){
//menggunakan baud komunikasi serial pada 115200
  Serial.begin(115200); 
  delay(15);

  pinMode(relay1,OUTPUT);pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);pinMode(relay4,OUTPUT);
  
  digitalWrite(relay1, ON);digitalWrite(relay2, ON);
  digitalWrite(relay3, ON);digitalWrite(relay4, ON);
 
  Serial.println();Serial.println(); //pemberian spasi
  Serial.print("Terhubung dengan Wifi.... ");
 // Koneksi dengan Wifi
  Serial.println(ssid);
 
  //prosedur pengkoneksian wifi
  WiFi.begin(ssid, password);

 //pengecekan status wifi
  while (WiFi.status() != WL_CONNECTED) //pengecekan kondisi koneksi wifi
  {delay(600);Serial.print(".");}
  Serial.println("");
  Serial.println("Sudah terkoneksi dengan wifi");
 
  server.begin(); //prosedur memulai akses server
  Serial.println("Pemulaian Akses Server");
 
  //menuliskan alamat ip
  Serial.print("Alamat ip yang digunakan untuk pengaksesan: ");
  //contoh format ip address : http://192.168.120.3/ 
  Serial.print("http://");Serial.print (WiFi.localIP());Serial.println("/"); 

}
 
void loop() {
  WiFiClient client = server.available(); //cek kondisi jika terhubung dengan client
  if (!client) {
    return;
  }
 
  //menunggu client, data dikirim
  Serial.println("client baru");
  //jika client tidak available
  while(!client.available()) {delay(5);}
  String request = client.readStringUntil('\r');
  Serial.print(request);client.flush();
  
  //penulisan data pada browser dengan alamat diatas
  client.println("HTTP/1.1 200 OK");client.println("Content-Type: text/html");
  client.println("");

  client.println("<!DOCTYPE HTML>");client.println("<html>");
  client.println("<head>");
  client.println("<meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/css/bootstrap.min.css\">");
  client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
  client.println("<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/js/bootstrap.bundle.min.js\"></script>");
  client.println("<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js\"></script>");
  client.println("<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap-icons@1.10.3/font/bootstrap-icons.css\">");
  client.println("<title>Smart Lamp TIF RP 21B</title>");
  client.println("</head>");

  client.println("<body>");
  client.println("<Div class=\"container\"><div class=\"bg-primary text-white text-center\">");
  client.println("<h1>Smart Lamp <i class=\"bi bi-lightbulb-fill text-warning\"></i></h1>");
  client.println("<p>TIF RP 21B - KELOMPOK 8");
  client.println("</div>");
  client.println("<div class=\"row\">");
    client.println("<div class=\"col-lg-12\">");
      client.println("<h3>Kendali Lampu via Wifi <i class=\"bi bi-wifi\"></i></h3>");
    client.println("</div>");
  client.println("</div>");
  
 
  client.println("<div class=\"row\">");
  client.print("<div class=\"col-lg-3 bg-info text-white\">");
  client.print("Semua Lampu: ");
  
 // Control relay 1
  if(request.indexOf("/relayall=ON")!= -1)
  {
    digitalWrite(relay1, ON);value1 = ON;
    digitalWrite(relay2, ON);value2 = ON;
    digitalWrite(relay3, ON);value3 = ON;
    digitalWrite(relay4, ON);value4 = ON;
    valueall = ON;
    }

  if(request.indexOf("/relayall=OFF")!= -1)
  { 
    digitalWrite(relay1, OFF);value1 = OFF;
    digitalWrite(relay2, OFF);value2 = OFF;
    digitalWrite(relay3, OFF);value3 = OFF;
    digitalWrite(relay4, OFF);value4 = OFF;
    valueall = OFF;
    }
  if(valueall==ON){client.print("<i class=\"bi bi-lightbulb-fill\"></i>");}
  if(valueall==OFF){client.print("<i class=\"bi bi-lightbulb-off\"></i>");}
  client.println("</div>");  

  client.println("<div class=\"col-lg-3\"><div class=\"btn-group\">");
  client.println("<a href=\"/relayall=ON\" type=\"button\" class=\"btn btn-info\"><i class=\"bi bi-check-circle\"></i> ON</a>");
  client.println("<a href=\"/relayall=OFF\" type=\"button\" class=\"btn btn-secondary\"><i class=\"bi bi-x-circle\"></i> OFF</a>");  
  client.println("</div></div>");
  client.println("<div class=\"col-lg-6\">&nbsp;</div>");
  client.println("</div>");

  client.println("<div class=\"row\">");
  client.print("<div class=\"col-lg-3 bg-primary text-white\">");
  client.print("Lampu Biru: ");
  
 // Control relay 1
  if(request.indexOf("/relay1=ON")!= -1)
  {digitalWrite(relay1, ON);value1 = ON;}

  if(request.indexOf("/relay1=OFF")!= -1)
  {digitalWrite(relay1, OFF);value1 = OFF;}
  if(value1==ON){client.print("<i class=\"bi bi-lightbulb-fill\"></i>");}
  if(value1==OFF){client.print("<i class=\"bi bi-lightbulb-off\"></i>");}
  client.println("</div>");  

  client.println("<div class=\"col-lg-3\"><div class=\"btn-group\">");
  client.println("<a href=\"/relay1=ON\" type=\"button\" class=\"btn btn-primary\"><i class=\"bi bi-check-circle\"></i> ON</a>");
  client.println("<a href=\"/relay1=OFF\" type=\"button\" class=\"btn btn-secondary\"><i class=\"bi bi-x-circle\"></i> OFF</a>");  
  client.println("</div></div>");
  client.println("<div class=\"col-lg-6\">&nbsp;</div>");
  client.println("</div>");
  
 client.println("<div class=\"row\">");
 client.print("<div class=\"col-lg-3 bg-warning text-white\">");
 client.print("Lampu Kuning: ");
 
  // Control relay 2
  if (request.indexOf("/relay2=ON") != -1)  {
    digitalWrite(relay2, ON);
    value2 = ON;
    }
  if (request.indexOf("/relay2=OFF") != -1)  {
    digitalWrite(relay2, OFF);
    value2 = OFF;
    }
    if(value2==ON){client.print("<i class=\"bi bi-lightbulb-fill\"></i>");}
     if(value2==OFF){client.print("<i class=\"bi bi-lightbulb-off\"></i>");}
  client.println("</div>");  
    
  client.println("<div class=\"col-lg-3\"><div class=\"btn-group\">");
  client.println("<a href=\"/relay2=ON\" type=\"button\" class=\"btn btn-warning\"><i class=\"bi bi-check-circle\"></i> ON</a>");
  client.println("<a href=\"/relay2=OFF\" type=\"button\" class=\"btn btn-secondary\"><i class=\"bi bi-x-circle\"></i> OFF</a>");  
  client.println("</div></div>");
  client.println("<div class=\"col-lg-6\">&nbsp;</div></div>");
  
  
  client.print("<div class=\"row\"><div class=\"col-lg-3 bg-success text-white\">");
  client.print("Lampu Hijau: ");
  
 // Control relay 3
  if (request.indexOf("/relay3=ON") != -1)  {
    digitalWrite(relay3, ON);
    value3 = ON;
    }
  if (request.indexOf("/relay3=OFF") != -1)  {
    digitalWrite(relay3, OFF);
    value3 = OFF;
    }
    if(value3==ON){client.print("<i class=\"bi bi-lightbulb-fill\"></i>");}
     if(value3==OFF){client.print("<i class=\"bi bi-lightbulb-off\"></i>");}
  client.println("</div>");  
    
  client.println("<div class=\"col-lg-3\"><div class=\"btn-group\">");
  client.println("<a href=\"/relay3=ON\" type=\"button\" class=\"btn btn-success\"><i class=\"bi bi-check-circle\"></i> ON</a>");
  client.println("<a href=\"/relay3=OFF\" type=\"button\" class=\"btn btn-secondary\"><i class=\"bi bi-x-circle\"></i> OFF</a>");  
  client.println("</div></div>");
  client.println("<div class=\"col-lg-6\">&nbsp;</div></div>");
  
  client.print("<div class=\"row\"><div class=\"col-lg-3 bg-danger text-white\">");
  client.print("Lampu Merah: ");
  
  // Control relay 4
  if (request.indexOf("/relay4=ON") != -1)  {
    digitalWrite(relay4, ON);
    value4 = ON;
    } 
  if (request.indexOf("/relay4=OFF") != -1)  {
    digitalWrite(relay4, OFF);
    value4 = OFF;
    }
    if(value4==ON){client.print("<i class=\"bi bi-lightbulb-fill\"></i>");}
     if(value4==OFF){client.print("<i class=\"bi bi-lightbulb-off\"></i>");}
  client.println("</div>");  
     
  client.println("<div class=\"col-lg-3\"><div class=\"btn-group\">");
  client.println("<a href=\"/relay4=ON\" type=\"button\" class=\"btn btn-danger\"><i class=\"bi bi-check-circle\"></i> ON</a>");
  client.println("<a href=\"/relay4=OFF\" type=\"button\" class=\"btn btn-secondary\"><i class=\"bi bi-x-circle\"></i> OFF</a>");  
  client.println("</div></div>");
  client.println("<div class=\"col-lg-6\">&nbsp;</div></div>");
  
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
