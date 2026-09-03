#include "Adafruit_UC8279_Grayscale4.h"

#include "Adafruit_EPD.h"

// clang-format off

// 4-level grayscale waveforms for the UC8279: 5 tables of [register + 49
// data bytes], trailing bytes zero. Byte values are the stock Xteink X4 Pro
// firmware's, by way of the MIT-licensed Free-Ink SDK
// (libs/display/FreeInkDisplay/src/driver/Uc8279X4Driver.cpp). Two sets
// exist, keyed to the panel's LUT_VER (VER cmd 0x70, data byte 2): 0x02 and
// 0x68 differ only in the third/fourth frame-group bytes. Panels reporting
// anything else use the 0x68 set (the vendor reference defines no other).

static const uint8_t uc8279_gray_lut_02[5][50] = {
    {UC8279_LUT_VCOM, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_WW,   0x01, 0x02, 0x02, 0x41, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_BW,   0x01, 0x02, 0x82, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_WB,   0x01, 0x02, 0x82, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_BB,   0x01, 0x02, 0x02, 0x81, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
};

static const uint8_t uc8279_gray_lut_68[5][50] = {
    {UC8279_LUT_VCOM, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_WW,   0x01, 0x02, 0x03, 0x41, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_BW,   0x01, 0x02, 0x83, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_WB,   0x01, 0x02, 0x83, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
    {UC8279_LUT_BB,   0x01, 0x02, 0x03, 0x81, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01},
};

// clang-format on

/**************************************************************************/
/*!
    @brief constructor if using external SRAM chip and software SPI
    @param width the width of the display in pixels
    @param height the height of the display in pixels
    @param SID the SID pin to use
    @param SCLK the SCLK pin to use
    @param DC the data/command pin to use
    @param RST the reset pin to use
    @param CS the chip select pin to use
    @param SRCS the SRAM chip select pin to use
    @param MISO the MISO pin to use
    @param BUSY the busy pin to use
*/
/**************************************************************************/
Adafruit_UC8279_Grayscale4::Adafruit_UC8279_Grayscale4(
    int width, int height, int16_t SID, int16_t SCLK, int16_t DC, int16_t RST,
    int16_t CS, int16_t SRCS, int16_t MISO, int16_t BUSY)
    : Adafruit_UC8279(width, height, SID, SCLK, DC, RST, CS, SRCS, MISO, BUSY) {
  // The base constructor sized buffer1 only; grayscale needs both planes.
  buffer2_size = buffer1_size;
  if (use_sram) {
    buffer2_addr = buffer1_size;
  } else {
    buffer2 = (uint8_t*)malloc(buffer2_size);
  }

  _gray_lut = uc8279_gray_lut_68;
}

/**************************************************************************/
/*!
    @brief constructor if using on-chip RAM and hardware SPI
    @param width the width of the display in pixels
    @param height the height of the display in pixels
    @param DC the data/command pin to use
    @param RST the reset pin to use
    @param CS the chip select pin to use
    @param SRCS the SRAM chip select pin to use
    @param BUSY the busy pin to use
    @param spi the SPI bus to use
*/
/**************************************************************************/
Adafruit_UC8279_Grayscale4::Adafruit_UC8279_Grayscale4(int width, int height,
                                                       int16_t DC, int16_t RST,
                                                       int16_t CS, int16_t SRCS,
                                                       int16_t BUSY,
                                                       SPIClass* spi)
    : Adafruit_UC8279(width, height, DC, RST, CS, SRCS, BUSY, spi) {
  // The base constructor sized buffer1 only; grayscale needs both planes.
  buffer2_size = buffer1_size;
  if (use_sram) {
    buffer2_addr = buffer1_size;
  } else {
    buffer2 = (uint8_t*)malloc(buffer2_size);
  }

  _gray_lut = uc8279_gray_lut_68;
}

/**************************************************************************/
/*!
    @brief begin communication with and set up the display.
    @param reset if true the reset pin will be toggled.
*/
/**************************************************************************/
void Adafruit_UC8279_Grayscale4::begin(bool reset) {
  Adafruit_UC8279::begin(reset);

  // Absolute plane encoding (see class docs): layer bit 0 -> DTM1, bit 1 ->
  // DTM2, written straight through. Cleared buffers = (0,0) = white.
  setBlackBuffer(0, false);
  setColorBuffer(1, false);

  layer_colors[EPD_WHITE] = 0b00;
  layer_colors[EPD_BLACK] = 0b11;
  layer_colors[EPD_RED] = 0b01;
  layer_colors[EPD_GRAY] = 0b10;
  layer_colors[EPD_LIGHT] = 0b01;
  layer_colors[EPD_DARK] = 0b10;

  // Inherited from the mono path; not yet wall-clocked on hardware.
  default_refresh_delay = 5000;
}

/**************************************************************************/
/*!
    @brief select the grayscale waveform for the panel sub-revision
    @param lut_ver the panel's LUT_VER, data byte 2 of the VER (0x70)
           readback: 0x02 selects its own table, anything else the 0x68 set
*/
/**************************************************************************/
void Adafruit_UC8279_Grayscale4::setLUTVariant(uint8_t lut_ver) {
  _gray_lut = (lut_ver == 0x02) ? uc8279_gray_lut_02 : uc8279_gray_lut_68;
}

/**************************************************************************/
/*!
    @brief signal the display to update
*/
/**************************************************************************/
void Adafruit_UC8279_Grayscale4::update() {
  // Stock grayscale sequence (Free-Ink SDK displayGray): PSR with REG=1 ->
  // external LUTs -> CDI -> PON -> PSR rewrite -> DRF. No CCSET/TSSET here.
  uint8_t psr[2] = {_psr0, _psr1}; // REG stays 1: refresh from the loaded LUTs
  EPD_command(UC8279_PANELSETTING, psr, 2);

  for (uint8_t t = 0; t < 5; t++) {
    EPD_command(_gray_lut[t][0], &_gray_lut[t][1], 49);
  }

  // Constant on every grayscale refresh per stock firmware.
  uint8_t cdi = 0x97;
  EPD_command(UC8279_VCOM_DATA_INTERVAL, &cdi, 1);

  EPD_command(UC8279_POWERON);
  busy_wait();

  // PON refreshes the panel's defaults, so PSR only latches when written
  // after it (same quirk as the mono path, but REG is kept set).
  EPD_command(UC8279_PANELSETTING, psr, 2);

  EPD_command(UC8279_DISPLAYREFRESH);
  delay(100);
  busy_wait();

  if (_busy_pin <= -1) {
    delay(default_refresh_delay);
  }
}

/**************************************************************************/
/*!
    @brief Send the specific command to start writing to EPD display RAM
    @param index 0 writes the DTM1 plane (buffer1), 1 the DTM2 plane
   (buffer2); together they select the per-pixel gray level.
    @returns The byte that is read from SPI at the same time as sending the
   command
*/
/**************************************************************************/
uint8_t Adafruit_UC8279_Grayscale4::writeRAMCommand(uint8_t index) {
  const uint8_t rv =
      EPD_command(index == 0 ? UC8279_WRITE_RAM1 : UC8279_WRITE_RAM2, false);

  // Same gate-offset padding as the mono driver; skipped on the SRAM path,
  // where these transfers would advance the shared-bus SRAM read pointer.
  if (!use_sram) {
    dcHigh();
    writeBlankGates(_gate_offset);
  }

  return rv;
}
