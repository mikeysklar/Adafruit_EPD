#ifndef LIB_ADAFRUIT_UC8279_GRAYSCALE4
#define LIB_ADAFRUIT_UC8279_GRAYSCALE4

#include <Arduino.h>

#include "Adafruit_UC8279.h"

/**************************************************************************/
/*!
    @brief  Class for interfacing with UC8279 EPD drivers in 4-level
            grayscale mode using the external LUT bank (PSR REG=1).

    Plane encoding is absolute, matching the stock Xteink X4 Pro firmware
    (byte tables and sequence via the MIT-licensed Free-Ink SDK,
    Uc8279X4Driver): per pixel, (DTM1, DTM2) bits are
    black = (1,1), dark gray = (0,1), light gray = (1,0), white = (0,0).
    buffer1 streams to DTM1 and buffer2 to DTM2 with no inversion, and
    layer_colors produces this encoding directly; a cleared buffer is white.

    Note: in the stock tables the two mid-gray waveforms (0x22/0x23) are
    byte-identical, so EPD_DARK and EPD_LIGHT render the same mid-gray (3
    effective levels) until those tables are differentiated. The sibling
    UC8179's GxEPD2_4G tables show the recipe: same voltage pattern, different
    frame counts in the final group. Which mid-code is dark vs light must be
    settled by a bench edit, not by source comments (every reference's labels
    have been caught wrong at least once).

    Other bench items: the refresh delay for the no-BUSY path (inherited
    5000 ms, not yet wall-clocked) and the LUT variant for a given panel
    (see setLUTVariant()).
*/
/**************************************************************************/
class Adafruit_UC8279_Grayscale4 : public Adafruit_UC8279 {
 public:
  Adafruit_UC8279_Grayscale4(int width, int height, int16_t SID, int16_t SCLK,
                             int16_t DC, int16_t RST, int16_t CS, int16_t SRCS,
                             int16_t MISO, int16_t BUSY = -1);
  Adafruit_UC8279_Grayscale4(int width, int height, int16_t DC, int16_t RST,
                             int16_t CS, int16_t SRCS, int16_t BUSY = -1,
                             SPIClass* spi = &SPI);

  void begin(bool reset = true);
  void update(void);

  void setLUTVariant(uint8_t lut_ver);

 protected:
  uint8_t writeRAMCommand(uint8_t index);

  const uint8_t (*_gray_lut)[50]; ///< Active 5x[reg + 49B] grayscale LUT set
};

#endif
