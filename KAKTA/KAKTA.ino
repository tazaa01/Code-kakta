#include <ESP8266WiFi.h>       // ใช้ไลบรารีสำหรับการเชื่อมต่อ WiFi
#include <ESP8266SMTP.h>       // ใช้ไลบรารีสำหรับการส่งอีเมล (SMTP)

#define TRIG_PIN D2           // กำหนดพิน Trigger ของเซ็นเซอร์
#define ECHO_PIN D1           // กำหนดพิน Echo ของเซ็นเซอร์

// ตั้งค่าการเชื่อมต่อ Wi-Fi
const char* ssid = "Your_SSID";        // SSID ของ WiFi
const char* password = "Your_PASSWORD";  // รหัสผ่าน WiFi

// ตั้งค่าอีเมลสำหรับการแจ้งเตือน
const char* smtp_server = "smtp.gmail.com";  // เซิร์ฟเวอร์ SMTP
const int smtp_port = 465;                   // พอร์ต SMTP
const char* email_sender = "youremail@gmail.com";  // อีเมลผู้ส่ง
const char* email_recipient = "recipientemail@gmail.com"; // อีเมลผู้รับ
const char* email_subject = "Water Level Alert";  // หัวข้ออีเมล

long duration;
int distance;
int waterLevelThreshold = 20;  // ระดับน้ำที่ต่ำสุดที่ต้องการให้แจ้งเตือน (ในเปอร์เซ็นต์)

void setup() {
  Serial.begin(115200);         // เริ่มการสื่อสารผ่าน Serial Monitor
  pinMode(TRIG_PIN, OUTPUT);    // ตั้งค่าพิน TRIG เป็น OUTPUT
  pinMode(ECHO_PIN, INPUT);     // ตั้งค่าพิน ECHO เป็น INPUT

  // เชื่อมต่อ Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // การวัดระยะจากเซ็นเซอร์อัลตราโซนิก
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.0344 / 2;  // คำนวณระยะห่าง (cm)

  // คำนวณระดับน้ำ (สมมุติว่าเซ็นเซอร์วัดจากระดับน้ำเต็มถัง)
  int waterLevel = map(distance, 0, 100, 100, 0);  // เปลี่ยนระยะทางเป็นเปอร์เซ็นต์

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // ตรวจสอบระดับน้ำ หากต่ำกว่าค่าที่กำหนดให้ส่งอีเมลแจ้งเตือน
  if (waterLevel <= waterLevelThreshold) {
    sendEmailAlert(waterLevel);
  }

  delay(2000);  // หน่วงเวลา 2 วินาที
}

// ฟังก์ชั่นส่งการแจ้งเตือนทางอีเมล
void sendEmailAlert(int waterLevel) {
  WiFiClient client;
  if (client.connect(smtp_server, smtp_port)) {
    String emailBody = "Warning: Water level is too low! Current water level is: " + String(waterLevel) + "%";
    
    // ส่งคำสั่ง HELO
    client.println("HELO " + String(WiFi.localIP()));
    delay(500);
    
    // เข้าสู่การล็อกอิน SMTP
    client.println("AUTH LOGIN");
    delay(500);
    client.println(base64::encode("youremail@gmail.com")); // อีเมลผู้ส่ง
    delay(500);
    client.println(base64::encode("yourpassword")); // รหัสผ่านอีเมล
    delay(500);
    
    // ส่งคำสั่งส่งอีเมล
    client.println("MAIL FROM: <youremail@gmail.com>");
    delay(500);
    client.println("RCPT TO: <recipientemail@gmail.com>");
    delay(500);
    client.println("DATA");
    delay(500);
    
    // ข้อความในอีเมล
    client.println("Subject: " + String(email_subject));
    client.println("To: " + String(email_recipient));
    client.println("From: " + String(email_sender));
    client.println();
    client.println(emailBody);
    client.println(".");
    
    delay(500);
    client.println("QUIT");
  } else {
    Serial.println("SMTP connection failed.");
  }
}

void loop() {
  // การวัดระยะห่างจากเซ็นเซอร์
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2; // คำนวณระยะทาง
  
  // คำนวณระดับน้ำจากระยะห่าง
  waterLevel = 100 - distance; // สมมติว่าระยะห่างมีค่าน้อยจะมีระดับน้ำสูง
  
  // แสดงผลบน Serial Monitor
  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // ถ้าระดับน้ำต่ำกว่าค่าที่กำหนด ให้ส่งการแจ้งเตือน
  if (waterLevel <= alertLevel) {
    sendAlert();
  }
  
  delay(1000); // หน่วงเวลา 1 วินาที
}

// ฟังก์ชั่นสำหรับส่งการแจ้งเตือน
void sendAlert() {
  // ถ้าใช้การแจ้งเตือนผ่าน Wi-Fi หรืออีเมล์ ให้ใช้ API หรือโค้ดที่เหมาะสม
  Serial.println("Water level is too low! Sending alert...");
  // โค้ดการส่งอีเมล์ หรือแจ้งเตือนผ่านแอป
}
