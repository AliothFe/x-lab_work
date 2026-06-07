// 任务一：串口指令控制 LED 亮灭
// 引脚定义（根据实际硬件调整）
#define LED1_PIN  2   // 多数 ESP32 板载 LED 连接在 GPIO2（低电平点亮，这里按高电平有效处理）
#define LED2_PIN  4   // 第二个 LED，可接 GPIO4 或其他可用引脚

String inputString = "";      // 存储串口接收的字符串
bool stringComplete = false; // 标记是否收到完整一行

void setup() {
  // 初始化硬件串口
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("\n--- 串口 LED 控制 ---");
  Serial.println("指令说明：发送 '1' 切换 LED1，发送 '2' 切换 LED2");

  // 设置 LED 引脚为输出，初始熄灭
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
}

void loop() {
  // 逐字节读取串口数据，直到检测到换行符
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;   // 收到换行，一行结束
    } else if (inChar != '\r') {
      inputString += inChar;   // 忽略回车，拼接其他字符
    }
  }

  // 当收到完整一行时，进行处理
  if (stringComplete) {
    inputString.trim();        // 去除首尾空白（安全处理）

    if (inputString.length() > 0) {
      Serial.print("收到指令: ");
      Serial.println(inputString);

      // 根据指令执行动作（翻转 LED 并反馈状态）
      if (inputString == "1") {
        toggleLED(LED1_PIN, "LED1");
      } else if (inputString == "2") {
        toggleLED(LED2_PIN, "LED2");
      } else {
        Serial.println("无效指令，无动作");
      }
    }

    // 清空字符串，准备接收下一条指令
    inputString = "";
    stringComplete = false;
  }
}

// 翻转指定引脚电平，并发送反馈
void toggleLED(int pin, const String &name) {
  // 读取当前状态并翻转（假设高电平为亮）
  int currentState = digitalRead(pin);
  digitalWrite(pin, !currentState);

  // 根据翻转后状态发送反馈
  if (digitalRead(pin) == HIGH) {
    Serial.println(name + "亮");
  } else {
    Serial.println(name + "灭");
  }
}
