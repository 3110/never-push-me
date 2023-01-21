#include <M5Unified.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

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

    keyboard.begin();
    USB.begin();
}

void loop(void) {
    vTaskDelay(1);
    M5.update();
    if (M5.BtnA.wasClicked()) {
        for (size_t i = 0; i < N_KEYS; ++i) {
            keyboard.press(KEYS[i]);
        }
    } else {
        keyboard.releaseAll();
    }
}