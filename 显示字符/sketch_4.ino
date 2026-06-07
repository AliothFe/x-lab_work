#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED 显示屏宽度和高度（常用 128x64 或 128x32，请根据你的模块修改）
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64   // 如果是 128x32 的屏，这里改为 32

// I2C 地址，通常为 0x3C，如果不是请修改
#define OLED_ADDR 0x3C

// 创建显示对象，-1 表示使用硬件复位引脚（通常不需要复位引脚，可设为 -1）
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // 初始化 OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);  // 死循环
  }

  // 显示初始画面
  display.clearDisplay();
  display.setTextSize(2);              // 设置字号
  display.setTextColor(SSD1306_WHITE); // 白色文字
  display.setCursor(0, 0);            // 起点坐标 (x,y)
  display.println(F("ESP32 OLED"));
  display.setTextSize(1);
  display.println(F("Hello, World!"));
  display.display();                   // 将缓冲区内容显示到屏幕
  delay(2000);
}

void loop() {
  // 不断刷新屏幕右下角的时间（示例动态显示）
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(F("ESP32 OLED"));
  display.setTextSize(1);
  display.print(F("Millis: "));
  display.print(millis() / 1000);
  display.println(F(" s"));
  display.display();
  delay(1000);
}