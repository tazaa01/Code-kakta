#1 เตรียมอุปกรณ์
ESP8266 (เช่น NodeMCU หรือ Wemos D1 Mini)
เซ็นเซอร์ Ultrasonic (HC-SR04) สำหรับวัดระดับน้ำ
แหล่งจ่ายไฟ (เช่น Adapter 5V)
สาย Jumper สำหรับเชื่อมต่อ
คอมพิวเตอร์ สำหรับเขียนโปรแกรมและอัพโหลดไปที่ ESP8266
บัญชี Gmail (สำหรับการส่งอีเมลแจ้งเตือน)
#2เชื่อมต่อแหล่งจ่ายไฟ:
ใช้แหล่งจ่ายไฟ 5V ให้กับ ESP8266 เพื่อให้ทำงานได้
#3 การตั้งค่าไลบรารีใน Arduino IDE
1ติดตั้งไลบรารี ESP8266:
เปิด Arduino IDE แล้วไปที่ File > Preferences
ในช่อง "Additional Boards Manager URLs" ให้เพิ่ม URL สำหรับ ESP8266: http://arduino.esp8266.com/stable/package_esp8266com_index.json
ไปที่ Tools > Board > Board Manager แล้วค้นหา "esp8266" และติดตั้ง
2ติดตั้งไลบรารีสำหรับการเชื่อมต่อ Wi-Fi และ SMTP:
ไปที่ Sketch > Include Library > Manage Libraries และค้นหาไลบรารี:
ESP8266WiFi (สำหรับเชื่อมต่อ Wi-Fi)
ESP8266SMTP หรือไลบรารีที่สามารถส่งอีเมล (ถ้าไม่สามารถหานี้ใช้ไลบรารี SMTP ทั่วไปได้)
#4 เขียนโปรแกรม
ใช้โค้ดนี้ใน Arduino IDE เพื่อเชื่อมต่อ ESP8266 กับ Wi-Fi และส่งการแจ้งเตือนอีเมลเมื่อระดับน้ำต่ำ
#5การอัพโหลดโค้ดลงใน ESP8266
เชื่อมต่อ ESP8266 กับคอมพิวเตอร์ผ่าน USB
ใน Arduino IDE:
เลือก Board เป็น NodeMCU 1.0 (ESP-12E Module) หรืออุปกรณ์ ESP8266 ที่ใช้
เลือก Port ที่เชื่อมต่อกับ ESP8266
คลิก Upload เพื่ออัพโหลดโปรแกรมไปยัง ESP8266
#6. การทดสอบระบบ
หลังจากโปรแกรมถูกอัพโหลดลงใน ESP8266 แล้ว:
เชื่อมต่อ ESP8266 กับ Wi-Fi
วัดระดับน้ำในถัง โดยการวางเซ็นเซอร์ Ultrasonic ในถังน้ำ
ตรวจสอบว่าเมื่อระดับน้ำลดลงต่ำกว่าค่าที่กำหนด (เช่น 20%) ระบบจะส่งอีเมลแจ้งเตือนถึงคุณ
#7. การปรับแต่งและตรวจสอบ
คุณสามารถปรับค่า waterLevelThreshold เพื่อกำหนดระดับน้ำที่ต้องการให้แจ้งเตือน
หากระบบไม่ส่งการแจ้งเตือนหรือเชื่อมต่อ Wi-Fi ไม่ได้ ให้ตรวจสอบการตั้งค่า Wi-Fi และตรวจสอบโค้ดเพื่อหาข้อผิดพลาด
