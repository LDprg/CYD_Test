#pragma once

#include <SPI.h>

#include <XPT2046_Bitbang.h>
#include <TFT_eSPI.h>

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

class Button
{
public:
    void init(TFT_eSPI *tft, int16_t x, int16_t y, uint16_t w, uint16_t h, String l)
    {
        label = l;

        button.initButton(tft, x, y, w, h,
                          TFT_BLACK, // Outline
                          TFT_RED,   // Fill
                          TFT_BLACK, // Text
                          "", 1);

        button.drawButton(false, String(label));
    }

    void press(TouchPoint p)
    {
        if ((p.zRaw > 0) && button.contains(p.x, p.y))
        {
            button.press(true); 
        }
        else
        {
            button.press(false); 
        }
    }

    void draw()
    {
        if (button.justPressed())
        {
            Serial.printf("Button %d pressed\n", label);
            button.drawButton(true, label);
        }

        if (button.justReleased())
        {
            Serial.printf("Button %d released\n", label);
            button.drawButton(false, label);
        }
    }

    [[nodiscard]] bool justPressed() {
        return button.justPressed();
    }

    [[nodiscard]] bool justReleased() {
        return button.justReleased();
    }

    [[nodiscard]] bool isPressed() {
        return button.isPressed();
    }

private:
    TFT_eSPI_Button button;
    String label;
};

class Display
{
public:
    Display();
    ~Display();

    void init(int cntX, int cntY, int cnt);
    void draw();

private:
    XPT2046_Bitbang ts;

    TFT_eSPI tft;

    Button *key;
    int countX = 0;
    int countY = 0;
    int count = 0;

    int page = 0;

    void drawButtons();
};