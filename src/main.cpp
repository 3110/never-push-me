#include <M5Unified.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

#if defined(LINE_NOTIFY)
#include "LINENotify.hpp"
#include "parser/LINENotifyConfigParser.hpp"

const char* CONFIG_FILE = "/line_notify.json";
const char* NOTIFY_MESSAGE = "押しちゃダメなのに押された";
#endif

const uint32_t BACKGROUND_COLOR = M5.Lcd.color888(255, 25, 25);

const struct
{
    const char* label;
    int color;
    int32_t x;
    int32_t y;
    const lgfx::IFont* font;
} LABELS[] = {
    {"絶対に！", TFT_WHITE, 64, 35, &fonts::lgfxJapanGothic_16},
    {"押すな", TFT_WHITE, 64, 55, &fonts::lgfxJapanGothic_28},
};
const size_t N_LABELS = sizeof(LABELS) / sizeof(LABELS[0]);

const uint8_t KEYS[] = {
    KEY_LEFT_CTRL,
    KEY_LEFT_ALT,
    KEY_DELETE,
};
const size_t N_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);

USBHIDKeyboard keyboard;

#if defined(LINE_NOTIFY)
LINENotify notify;
#endif

void setup(void) {
    M5.begin();
    M5.Lcd.setRotation(3);  // 左側にUSB-Cの口が来る向き
    M5.Lcd.startWrite();
    M5.Lcd.clear(BACKGROUND_COLOR);
    for (size_t i = 0; i < N_LABELS; ++i) {
        M5.Lcd.setTextColor(LABELS[i].color, BACKGROUND_COLOR);
        M5.Lcd.drawCenterString(LABELS[i].label, LABELS[i].x, LABELS[i].y,
                                LABELS[i].font);
    }
    M5.Lcd.endWrite();

#if defined(LINE_NOTIFY)
    LINENotifyConfigParser parser;
    if (!parser.parse(CONFIG_FILE)) {
        ESP_LOGE("main", "Failed to parse config file");
        while (true) {
            delay(100);
        }
    }
    ESP_LOGD("main", "SSID: %s", parser.getSSID());
    ESP_LOGD("main", "Password: %s", parser.getPassword());
    notify.begin(parser.getSSID(), parser.getPassword());
    notify.setToken(parser.getToken());
#endif

    keyboard.begin();
    USB.begin();
}

void loop(void) {
    vTaskDelay(1);
    M5.update();

#if defined(LINE_NOTIFY)
    notify.update();
#endif

    if (M5.BtnA.wasClicked()) {
        for (size_t i = 0; i < N_KEYS; ++i) {
            keyboard.press(KEYS[i]);
        }
#if defined(LINE_NOTIFY)
        if (!notify.send(NOTIFY_MESSAGE)) {
            ESP_LOGE("main", "Failed to send notify: %s", NOTIFY_MESSAGE);
        }
#endif
    } else {
        keyboard.releaseAll();
    }
}