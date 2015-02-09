/*
Copyright (C) 2015  Derek Chafin

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>

// #define ST7735_TFTWIDTH  128
// #define ST7735_TFTHEIGHT 160
// 128 samples; one per pixel
const unsigned int WHITE = 0xFFFFU;
const unsigned int BLACK = 0x0000U;

// Define various ADC prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

#define NUM_SAMPLES 64

unsigned int samples[NUM_SAMPLES];
unsigned char index = 0;

void setup()
{
  // set up the ADC
  // ADCSRA &= ~PS_128;  // remove bits set by Arduino library

  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  // ADCSRA |= PS_16;    // set our own prescaler to 64

  EsploraTFT.begin();
  EsploraTFT.background(BLACK);
  EsploraTFT.setRotation(3);
}

void loop()
{
  // Erase the old values
  EsploraTFT.drawPixel(index, lowByte(samples[index]), BLACK);
  EsploraTFT.drawPixel(index | NUM_SAMPLES, highByte(samples[index]) << 2, BLACK);
  // Note: readMicrophone is the rectified amplitude 0 - 1023 ie. the Arduino 10 bit ADC.
  samples[index] = Esplora.readMicrophone();
  // Draw the new values
  EsploraTFT.drawPixel(index, lowByte(samples[index]), WHITE);
  EsploraTFT.drawPixel(index | NUM_SAMPLES, highByte(samples[index]) << 2, WHITE);

  // Overflow at 256
  index++;
  // Overflow at 128
  index &= NUM_SAMPLES - 1;
}
