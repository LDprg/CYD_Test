#include "display.hpp"

void Display::drawButtons()
{
    if (key != nullptr)
        delete[] key;

    key = new Button[count];

    uint16_t bWidth = TFT_HEIGHT / countX;
    uint16_t bHeight = TFT_WIDTH / countY;

    for (int i = 0; i < countX * countY; i++)
    {
        key[i].init(&tft,
                    bWidth * (i % countX) + bWidth / 2,
                    bHeight * (i / countX) + bHeight / 2,
                    bWidth,
                    bHeight,
                    String(i + 1));
    }
}

Display::Display() : ts(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS), tft() {}
Display::~Display()
{
    delete[] key;
}

void Display::init(int cntX, int cntY, int cnt)
{
    countX = cntX;
    countY = cntY;
    count = cnt + (cntX * cntY % cnt);

    ts.begin();

    tft.init();
    tft.setRotation(1); 
    tft.invertDisplay(true);

    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(&FreeSansBold18pt7b);

    drawButtons();
}

void Display::draw()
{
    TouchPoint p = ts.getTouch();

    for (uint8_t b = 0; b < count; b++)
    {
        key[b].press(p);
        key[b].draw();
    }
}