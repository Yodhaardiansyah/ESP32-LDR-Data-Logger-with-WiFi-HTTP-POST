
---

# **ESP32 LDR Data Logger with WiFi & HTTP POST**  

This project reads data from an LDR (Light Dependent Resistor) using an ESP32 and transmits it to a web server via HTTP POST over WiFi.  

📌 **Created by:** Yodha Ardiansyah  
📷 **Instagram:** [@yodhaar_](https://instagram.com/yodhaar_)  

---

## **🚀 Features**
✅ Reads light intensity using an LDR sensor  
✅ Sends data to a web server via HTTP POST  
✅ Connects to WiFi automatically  
✅ JSON-based data transmission  

---

## **📜 Requirements**
- **ESP32 Development Board**  
- **LDR Sensor (Light Dependent Resistor)**  
- **WiFi Network**  
- **Web Server with API Endpoint**  

---

## **🛠️ Wiring Diagram**
| ESP32 Pin | LDR Connection |
|-----------|---------------|
| **3.3V**  | VCC           |
| **GND**   | GND           |
| **GPIO39 (ADC1_CH3)** | LDR Output |

*Note:* You may need a **10kΩ pull-down resistor** for better readings.

---

## **📜 Code Overview**
### **1️⃣ WiFi Connection**
The ESP32 connects to the WiFi network using the provided SSID and password.  

```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
}
```

### **2️⃣ Reading LDR Sensor Value**
The LDR sensor data is read using `analogRead()` from GPIO39.  

```cpp
int ldrValue = analogRead(ldrPin);
Serial.println("LDR Value: " + String(ldrValue));
```

### **3️⃣ Sending Data via HTTP POST**
If the ESP32 is connected to WiFi, it sends the LDR value to a web server.  

```cpp
String postData = "{\"data\":\"" + String(ldrValue) + "\"}";
http.POST(postData);
```

---

## **📥 Installation**
1. **Clone this repository**  
   ```sh
   git clone https://github.com/Yodhaardiansyah/ESP32-LDR-Data-Logger-with-WiFi-HTTP-POST.git
   ```
2. **Open the project in Arduino IDE or PlatformIO**  
3. **Install the required libraries:**  
   - **WiFi** (built-in for ESP32)
   - **HTTPClient** (for HTTP requests)  
4. **Modify WiFi credentials in the code**  
   ```cpp
   const char* ssid = "your_wifi_ssid";
   const char* password = "your_wifi_password";
   ```
5. **Upload the code to ESP32**  
6. **Monitor the serial output for debug messages**  

---

## **🌍 Server API Setup**
Your server should have an API that can receive JSON data via HTTP POST.  
Example PHP script (`post_data.php`):  

```php
<?php
$data = json_decode(file_get_contents("php://input"), true);
if ($data) {
    $ldrValue = $data["data"];
    file_put_contents("ldr_log.txt", "LDR Value: " . $ldrValue . "\n", FILE_APPEND);
    echo json_encode(["status" => "success", "ldr" => $ldrValue]);
} else {
    echo json_encode(["status" => "error"]);
}
?>
```

---

## **🛠️ Troubleshooting**
🔹 **ESP32 not connecting to WiFi?**  
- Check if the SSID and password are correct.  
- Move closer to the router.  

🔹 **No data sent to the server?**  
- Ensure the server URL is correct.  
- Check the server log for errors.  

🔹 **Incorrect LDR values?**  
- Try using a **10kΩ resistor** as a voltage divider.  
- Test with different light intensities.  

---

## **📜 License**
This project is open-source under the **MIT License**.  

---

💡 **For more projects, follow:**  
📷 **Instagram:** [@yodhaar_](https://instagram.com/yodhaar_)  
🌐 **GitHub:** [Yodha Ardiansyah](https://github.com/Yodhaardiansyah)  

🚀 **Happy Coding!** 🚀
