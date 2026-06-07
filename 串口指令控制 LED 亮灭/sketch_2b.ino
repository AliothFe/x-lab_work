// 密码箱实验：串口密码验证

String inputString = "";   // 存放当前接收的一行字符串
bool stringComplete = false;
int step = 0;              // 当前期望的密码索引：0=AA, 1=BB, 2=CC, 3=DD

// 定义正确密码序列
const String correctPassword[4] = {"AA", "BB", "CC", "DD"};

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("\n--- 密码箱已就绪 ---");
  Serial.println("请依次发送 AA, BB, CC, DD（每次以换行结束）");
  step = 0;  // 从第一个密码开始
}

void loop() {
  // 逐字节读取串口，直到收到换行符
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else if (inChar != '\r') {
      inputString += inChar;
    }
  }

  // 当收到完整一行时处理
  if (stringComplete) {
    inputString.trim();  // 去除首尾空白（包括 \r 等）

    // 检查是否与当前期待的密码匹配（区分大小写，严格匹配）
    if (inputString == correctPassword[step]) {
      step++;  // 匹配成功，进入下一步
      if (step == 4) {
        // 四个全部正确
        Serial.println("密码正确");
        step = 0;  // 重置，可以开始新一轮
      }
      // 注意：如果还未满4个，不返回任何提示，继续等待下一个
    } else {
      // 任何不匹配立即输出错误并重置
      Serial.println("密码错误");
      step = 0;  // 从头开始
    }

    // 清空接收缓冲区，准备下一行
    inputString = "";
    stringComplete = false;
  }
}
