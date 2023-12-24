#ifndef _THINKINK_290_GRAY4_T94_H
#define _THINKINK_290_GRAY4_T94_H

// This file is #included by Adafruit_ThinkInk.h and does not need to
// #include anything else to pick up the EPD header or ink mode enum.

const uint8_t ti_290t94_gray4_lut_code[153] = {
    0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0x48, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0x48, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x20, 0x48, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xA, 0x19, 0x0, 0x3, 0x8, 0x0, 0x0,
    0x14, 0x1, 0x0, 0x14, 0x1, 0x0, 0x3,
    0xA, 0x3, 0x0, 0x8, 0x19, 0x0, 0x0,
    0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,
};

static const uint8_t ti_290t94_monofull_init_code[] {
  SSD1680_SW_RESET, 0, // soft reset
    0xFF, 20,          // busy wait
    SSD1680_DATA_MODE, 1, 0x03, // Ram data entry mode
    SSD1680_WRITE_BORDER, 1, 0x05, //BorderWavefrom

    SSD1680_WRITE_VCOM, 1, 0x36,   // Vcom Voltage
    SSD1680_GATE_VOLTAGE, 1, 0x17, // Set gate voltage 
    SSD1680_SOURCE_VOLTAGE, 3, 0x41, 0x00, 0x32,   // Set source voltage

    SSD1680_DRIVER_CONTROL, 3, 0x27, 0x01, 0x00, //Driver output control
    SSD1680_DISP_CTRL1, 2, 0x00, 0x80, //Display update control
    SSD1680_TEMP_CONTROL, 1, 0x80, //Read built-in temperature sensor
    SSD1680_SET_RAMXCOUNT, 1, 0x00, //set RAM x address count to 0
    SSD1680_SET_RAMYCOUNT, 2, 0x27, 0x01, //set RAM y address count to 0X199
    0xFE // EOM
};


static const uint8_t ti_290t94_grayfull_init_code[] {
  SSD1680_SW_RESET, 0, // soft reset
    0xFF, 20,          // busy wait
    SSD1680_SET_ANALOGBLOCKCTRL, 1, 0x54, //set analog block control
    SSD1680_SET_DIGITBLOCKCTRL, 1, 0x3B, //set digital block control
    SSD1680_DRIVER_CONTROL, 3, 0x27, 0x01, 0x00, //Driver output control
    SSD1680_DATA_MODE, 1, 0x01, //data entry mode
    SSD1680_SET_RAMXPOS, 2, 0x00, 0x0F, //set Ram-X address start/end position
    SSD1680_SET_RAMYPOS, 4, 0x27, 0x01, 0x00, 0x00, //set Ram-Y address start/end position
    SSD1680_WRITE_BORDER, 1, 0x00, //BorderWavefrom

    SSD1680_WRITE_VCOM, 1, 0x1C,
    0x3F, 1, 0x22, //EOPQ
    SSD1680_GATE_VOLTAGE, 1, 0x17, //VGH
    SSD1680_SOURCE_VOLTAGE, 3, 0x41, 0x0, 0x32, // VSH1, VSH2, VSL

    // gray LUT
    0x32, 153, 0x40, 0x48, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0x48, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0x48, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x20, 0x48, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xA, 0x19, 0x0, 0x3, 0x8, 0x0, 0x0,
    0x14, 0x1, 0x0, 0x14, 0x1, 0x0, 0x3,
    0xA, 0x3, 0x0, 0x8, 0x19, 0x0, 0x0,
    0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,

    SSD1680_DISP_CTRL1, 2, 0x00, 0x80, //Display update control
    SSD1680_SET_RAMXCOUNT, 1, 0x00, //set RAM x address count to 0
    SSD1680_SET_RAMYCOUNT, 2, 0x27, 0x01, //set RAM y address count to 0X199
    0xFE // EOM
};

class ThinkInk_290_Grayscale4_T94 : public Adafruit_SSD1680 {
public:
  ThinkInk_290_Grayscale4_T94(int16_t SID, int16_t SCLK, int16_t DC, int16_t RST,
                       int16_t CS, int16_t SRCS, int16_t MISO,
                       int16_t BUSY = -1)
      : Adafruit_SSD1680(296, 128, SID, SCLK, DC, RST, CS, SRCS, MISO, BUSY){};

  ThinkInk_290_Grayscale4_T94(int16_t DC, int16_t RST, int16_t CS, int16_t SRCS,
                       int16_t BUSY = -1, SPIClass *spi = &SPI)
      : Adafruit_SSD1680(296, 128, DC, RST, CS, SRCS, BUSY, spi){};

  void begin(thinkinkmode_t mode = THINKINK_MONO) {
    Adafruit_SSD1680::begin(true);
    setColorBuffer(0, true); // layer 0 uninverted
    setBlackBuffer(0, true); // only one buffer
    
    inkmode = mode; // Preserve ink mode for ImageReader or others

    if (mode == THINKINK_MONO) {
      _xram_offset = 0;
      _epd_init_code = ti_290t94_monofull_init_code;
      
      
      layer_colors[EPD_WHITE] = 0b00;
      layer_colors[EPD_BLACK] = 0b01;
      layer_colors[EPD_RED] = 0b01;
      layer_colors[EPD_GRAY] = 0b01;
      layer_colors[EPD_LIGHT] = 0b00;
      layer_colors[EPD_DARK] = 0b01;

      default_refresh_delay = 500;
    }


    setRotation(0);
    powerDown();
  }
};


#endif // _THINKINK_290_GRAY4_T94_H