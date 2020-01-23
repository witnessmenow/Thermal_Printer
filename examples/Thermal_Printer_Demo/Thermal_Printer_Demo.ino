//
// Thermal Printer Demo
// written by Larry Bank
// Copyright (c) 2020 BitBank Software, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Thermal_Printer.h>
static uint8_t ucBuf[48 * 384];
#define WIDTH 384
#define HEIGHT 240

// Arduino logo
const byte logo_bmp[] = {
  0x42,0x4d,0xe2,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x00,0x00,0x00,0x6c,0x00,
  0x00,0x00,0xdc,0x00,0x00,0x00,0xa8,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,
  0x00,0x00,0x60,0x12,0x00,0x00,0x23,0x2e,0x00,0x00,0x23,0x2e,0x00,0x00,0x02,0x00,
  0x00,0x00,0x02,0x00,0x00,0x00,0x42,0x47,0x52,0x73,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
  0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x07,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xfc,0x0f,0xfc,0x0f,0x81,0xfc,0x07,0xc0,0x00,0xff,0xfe,0x00,
  0x0f,0xf8,0x00,0x00,0x7c,0x0f,0xf0,0x1f,0xf0,0x00,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xfc,0x07,0xfc,0x0f,0x81,0xf8,0x07,0xc0,0x00,0x3f,0xfc,0x00,0x07,0xf8,0x00,0x00,
  0x7c,0x0f,0xf0,0x1f,0xe0,0x00,0x7f,0xff,0xff,0xf0,0xff,0xff,0xfe,0x07,0xf8,0x0f,
  0x81,0xf8,0x0f,0xc0,0x00,0x0f,0xf8,0x00,0x03,0xf8,0x00,0x00,0x7c,0x0f,0xe0,0x1f,
  0xc0,0x00,0x3f,0xff,0xff,0xf0,0xff,0xff,0xfe,0x07,0xf8,0x0f,0x81,0xf0,0x1f,0xc0,
  0x00,0x0f,0xf8,0x00,0x01,0xf8,0x00,0x00,0x7c,0x0f,0xe0,0x1f,0x80,0x00,0x1f,0xff,
  0xff,0xf0,0xff,0xff,0xfe,0x07,0xf8,0x1f,0x81,0xf0,0x1f,0xc0,0x00,0x07,0xf0,0x0e,
  0x01,0xf8,0x00,0x00,0x7c,0x0f,0xc0,0x1f,0x80,0x70,0x1f,0xff,0xff,0xf0,0xff,0xff,
  0xfe,0x00,0x00,0x1f,0x81,0xe0,0x3f,0xc0,0xfc,0x03,0xf0,0x1f,0x81,0xff,0xf0,0x3f,
  0xfc,0x0f,0xc0,0x1f,0x01,0xf8,0x0f,0xff,0xff,0xf0,0xff,0xff,0xff,0x00,0x00,0x1f,
  0x81,0xe0,0x3f,0xc0,0xfe,0x03,0xf0,0x3f,0x80,0xff,0xf0,0x3f,0xfc,0x0f,0x80,0x1f,
  0x01,0xfc,0x0f,0xff,0xff,0xf0,0xff,0xff,0xff,0x00,0x00,0x3f,0x81,0xc0,0x7f,0xc0,
  0xff,0x03,0xf0,0x3f,0x80,0xff,0xf0,0x3f,0xfc,0x0f,0x00,0x1f,0x03,0xfc,0x0f,0xff,
  0xff,0xf0,0xff,0xff,0xff,0x00,0x00,0x3f,0x80,0x00,0x7f,0xc0,0xff,0x01,0xf0,0x3f,
  0xc0,0xff,0xf0,0x3f,0xfc,0x0f,0x00,0x1f,0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,
  0xff,0x80,0x00,0x3f,0x80,0x00,0x3f,0xc0,0xff,0x01,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,
  0xfc,0x0e,0x00,0x1e,0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,0xff,0x81,0xe0,0x7f,
  0x80,0x00,0x1f,0xc0,0xff,0x01,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,0xfc,0x0e,0x00,0x1e,
  0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,0xff,0x81,0xe0,0x7f,0x80,0x00,0x1f,0xc0,
  0xff,0x01,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,0xfc,0x0c,0x08,0x1e,0x03,0xfc,0x07,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xc1,0xe0,0x7f,0x80,0x00,0x0f,0xc0,0xff,0x01,0xf0,0x3f,
  0xc0,0xff,0xf0,0x3f,0xfc,0x0c,0x08,0x1e,0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xc0,0xc0,0xff,0x81,0xf8,0x0f,0xc0,0xff,0x01,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,
  0xfc,0x08,0x18,0x1e,0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,0xff,0xc0,0xc0,0xff,
  0x81,0xfc,0x07,0xc0,0xff,0x01,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,0xfc,0x08,0x18,0x1e,
  0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,0xff,0xe0,0xc0,0xff,0x81,0xfc,0x07,0xc0,
  0xff,0x01,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,0xfc,0x00,0x38,0x1f,0x03,0xfc,0x07,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xe0,0xc1,0xff,0x81,0xfc,0x07,0xc0,0xff,0x01,0xf0,0x3f,
  0xc0,0xff,0xf0,0x3f,0xfc,0x00,0x38,0x1f,0x03,0xfc,0x07,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xe0,0x01,0xff,0x81,0xfc,0x07,0xc0,0xfe,0x03,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,
  0xfc,0x00,0x78,0x1f,0x03,0xfc,0x0f,0xff,0xff,0xf0,0xff,0xff,0xff,0xf0,0x01,0xff,
  0x81,0xfc,0x07,0xc0,0xfe,0x03,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,0xfc,0x00,0xf8,0x1f,
  0x01,0xf8,0x0f,0xff,0xff,0xf0,0xff,0xff,0xff,0xf0,0x03,0xff,0x81,0xf8,0x0f,0xc0,
  0xf8,0x03,0xf0,0x3f,0xc0,0xff,0xf0,0x3f,0xfc,0x00,0xf8,0x1f,0x80,0xf8,0x0f,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xf0,0x03,0xff,0x80,0x00,0x0f,0xc0,0x00,0x07,0xf0,0x3f,
  0xc0,0xf8,0x00,0x00,0x7c,0x01,0xf8,0x1f,0x80,0x00,0x1f,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xf0,0x03,0xff,0x80,0x00,0x1f,0xc0,0x00,0x0f,0xf0,0x3f,0xc0,0xf8,0x00,0x00,
  0x7c,0x01,0xf8,0x1f,0xc0,0x00,0x1f,0xff,0xff,0xf0,0xff,0xff,0xff,0xf8,0x07,0xff,
  0x80,0x00,0x1f,0xc0,0x00,0x1f,0xf0,0x3f,0xc0,0xf8,0x00,0x00,0x7c,0x03,0xf8,0x1f,
  0xe0,0x00,0x3f,0xff,0xff,0xf0,0xff,0xff,0xff,0xf8,0x07,0xff,0x80,0x00,0x7f,0xc0,
  0x00,0x3f,0xf0,0x3f,0xc0,0xf8,0x00,0x00,0x7c,0x03,0xf8,0x1f,0xf0,0x00,0x7f,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xf8,0x07,0xff,0x80,0x01,0xff,0xc0,0x01,0xff,0xf0,0x3f,
  0xc0,0xf8,0x00,0x00,0x7c,0x07,0xf8,0x1f,0xf8,0x01,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0x80,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x3f,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x3f,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00,0x01,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xf8,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,
  0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xe0,
  0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
  0x07,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,
  0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,
  0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0x00,
  0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x00,
  0x01,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,
  0x00,0x1f,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,
  0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xf8,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xfe,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x0f,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,
  0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xe0,0x00,0x00,
  0x01,0xff,0xf8,0x00,0x00,0x00,0x1f,0xff,0xfe,0x00,0x00,0x00,0x07,0xff,0xe0,0x00,
  0x00,0x00,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xc0,0x00,0x00,0x0f,0xff,0xff,0x80,
  0x00,0x00,0x0f,0xff,0xfc,0x00,0x00,0x00,0x3f,0xff,0xfe,0x00,0x00,0x00,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0x80,0x00,0x00,0x3f,0xff,0xff,0xe0,0x00,0x00,0x07,0xff,
  0xf8,0x00,0x00,0x01,0xff,0xff,0xff,0x80,0x00,0x00,0x7f,0xff,0xff,0xf0,0xff,0xff,
  0xff,0x00,0x00,0x01,0xff,0xff,0xff,0xfc,0x00,0x00,0x03,0xff,0xf0,0x00,0x00,0x07,
  0xff,0xff,0xff,0xe0,0x00,0x00,0x3f,0xff,0xff,0xf0,0xff,0xff,0xff,0x00,0x00,0x03,
  0xff,0xff,0xff,0xfe,0x00,0x00,0x01,0xff,0xe0,0x00,0x00,0x1f,0xff,0xff,0xff,0xf8,
  0x00,0x00,0x1f,0xff,0xff,0xf0,0xff,0xff,0xfe,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,
  0x80,0x00,0x00,0xff,0xc0,0x00,0x00,0x3f,0xff,0xff,0xff,0xfc,0x00,0x00,0x1f,0xff,
  0xff,0xf0,0xff,0xff,0xfe,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x7f,
  0xc0,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x0f,0xff,0xff,0xf0,0xff,0xff,
  0xfc,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x3f,0x80,0x00,0x01,0xff,
  0xff,0xff,0xff,0xff,0x80,0x00,0x0f,0xff,0xff,0xf0,0xff,0xff,0xf8,0x00,0x00,0x7f,
  0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x3f,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xff,
  0xc0,0x00,0x07,0xff,0xff,0xf0,0xff,0xff,0xf8,0x00,0x00,0xff,0xff,0xff,0xff,0xff,
  0xfc,0x00,0x00,0x1e,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x07,0xff,
  0xff,0xf0,0xff,0xff,0xf0,0x00,0x01,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x0e,
  0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xff,0xf0,0xff,0xff,
  0xf0,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x04,0x00,0x00,0x3f,0xff,
  0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,0xff,0xf0,0xff,0xff,0xf0,0x00,0x07,0xff,
  0xff,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,
  0xf8,0x00,0x01,0xff,0xff,0xf0,0xff,0xff,0xe0,0x00,0x07,0xff,0xff,0xff,0xff,0xff,
  0xff,0xc0,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x01,0xff,
  0xff,0xf0,0xff,0xff,0xe0,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,
  0x00,0x01,0xff,0xff,0xfe,0x01,0xff,0xff,0xfe,0x00,0x00,0xff,0xff,0xf0,0xff,0xff,
  0xe0,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x03,0xff,0xff,
  0xfc,0x01,0xff,0xff,0xfe,0x00,0x00,0xff,0xff,0xf0,0xff,0xff,0xc0,0x00,0x1f,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x00,0x03,0xff,0xff,0xfc,0x01,0xff,0xff,
  0xff,0x00,0x00,0xff,0xff,0xf0,0xff,0xff,0xc0,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,
  0xff,0xfc,0x00,0x00,0x00,0x07,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0x00,0x00,0xff,
  0xff,0xf0,0xff,0xff,0xc0,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,
  0x00,0x0f,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0x00,0x00,0x7f,0xff,0xf0,0xff,0xff,
  0xc0,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x1f,0xff,0xff,
  0xfc,0x01,0xff,0xff,0xff,0x80,0x00,0x7f,0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x1f,0xff,0xff,0xfc,0x01,0xff,0xff,
  0xff,0x80,0x00,0x7f,0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0x80,0x00,0x00,0x3f,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0x80,0x00,0x7f,
  0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00,
  0x00,0x7f,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0xc0,0x00,0x7f,0xff,0xf0,0xff,0xff,
  0x80,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x7f,0xff,0xff,
  0xfc,0x00,0xff,0xff,0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,
  0xc0,0x00,0x00,0x07,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xf8,0x00,0x00,0x00,0x7f,
  0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,0x80,0x00,0xff,0xff,0xc0,0x00,0x00,0x07,
  0xff,0xff,0xe0,0x00,0x01,0xff,0xff,0xf8,0x00,0x00,0x00,0x7f,0xff,0xc0,0x00,0x3f,
  0xff,0xf0,0xff,0xff,0x80,0x00,0xff,0xff,0xc0,0x00,0x00,0x07,0xff,0xff,0xf0,0x00,
  0x01,0xff,0xff,0xf8,0x00,0x00,0x00,0x7f,0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,
  0x80,0x00,0xff,0xff,0xc0,0x00,0x00,0x07,0xff,0xff,0xf0,0x00,0x03,0xff,0xff,0xf8,
  0x00,0x00,0x00,0x7f,0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,0x80,0x00,0xff,0xff,
  0xc0,0x00,0x00,0x07,0xff,0xff,0xf0,0x00,0x03,0xff,0xff,0xf8,0x00,0x00,0x00,0x7f,
  0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,0x80,0x00,0xff,0xff,0xc0,0x00,0x00,0x07,
  0xff,0xff,0xf0,0x00,0x01,0xff,0xff,0xf8,0x00,0x00,0x00,0x7f,0xff,0xc0,0x00,0x3f,
  0xff,0xf0,0xff,0xff,0x80,0x00,0xff,0xff,0xc0,0x00,0x00,0x07,0xff,0xff,0xe0,0x00,
  0x01,0xff,0xff,0xf8,0x00,0x00,0x00,0x7f,0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,
  0x80,0x00,0xff,0xff,0xc0,0x00,0x00,0x07,0xff,0xff,0xe0,0x00,0x00,0xff,0xff,0xf8,
  0x00,0x00,0x00,0x7f,0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,
  0xff,0xc0,0x00,0x3f,0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0x80,0x00,0x00,0x7f,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0xc0,0x00,0x7f,
  0xff,0xf0,0xff,0xff,0x80,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x00,
  0x00,0x3f,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0x80,0x00,0x7f,0xff,0xf0,0xff,0xff,
  0x80,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x3f,0xff,0xff,
  0xfc,0x01,0xff,0xff,0xff,0x80,0x00,0x7f,0xff,0xf0,0xff,0xff,0x80,0x00,0x3f,0xff,
  0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x1f,0xff,0xff,0xfc,0x01,0xff,0xff,
  0xff,0x80,0x00,0x7f,0xff,0xf0,0xff,0xff,0xc0,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,
  0xff,0xfe,0x00,0x00,0x00,0x0f,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0x80,0x00,0x7f,
  0xff,0xf0,0xff,0xff,0xc0,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,
  0x00,0x07,0xff,0xff,0xfc,0x01,0xff,0xff,0xff,0x00,0x00,0x7f,0xff,0xf0,0xff,0xff,
  0xc0,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x00,0x07,0xff,0xff,
  0xfc,0x01,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xf0,0xff,0xff,0xc0,0x00,0x1f,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x03,0xff,0xff,0xfc,0x01,0xff,0xff,
  0xfe,0x00,0x00,0xff,0xff,0xf0,0xff,0xff,0xe0,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,
  0xff,0xe0,0x00,0x00,0x00,0x01,0xff,0xff,0xfe,0x01,0xff,0xff,0xfe,0x00,0x00,0xff,
  0xff,0xf0,0xff,0xff,0xe0,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,
  0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0x01,0xff,0xff,0xf0,0xff,0xff,
  0xf0,0x00,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x7f,0xff,
  0xff,0xff,0xff,0xff,0xf8,0x00,0x01,0xff,0xff,0xf0,0xff,0xff,0xf0,0x00,0x03,0xff,
  0xff,0xff,0xff,0xff,0xff,0x80,0x00,0x04,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,
  0xf8,0x00,0x01,0xff,0xff,0xf0,0xff,0xff,0xf0,0x00,0x01,0xff,0xff,0xff,0xff,0xff,
  0xff,0x00,0x00,0x0c,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x03,0xff,
  0xff,0xf0,0xff,0xff,0xf8,0x00,0x01,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x1e,
  0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x03,0xff,0xff,0xf0,0xff,0xff,
  0xf8,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x1f,0x00,0x00,0x07,0xff,
  0xff,0xff,0xff,0xff,0xc0,0x00,0x07,0xff,0xff,0xf0,0xff,0xff,0xfc,0x00,0x00,0x7f,
  0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x3f,0x80,0x00,0x03,0xff,0xff,0xff,0xff,0xff,
  0x80,0x00,0x07,0xff,0xff,0xf0,0xff,0xff,0xfc,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,
  0xe0,0x00,0x00,0x7f,0x80,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x0f,0xff,
  0xff,0xf0,0xff,0xff,0xfe,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0xff,
  0xc0,0x00,0x00,0x7f,0xff,0xff,0xff,0xfe,0x00,0x00,0x1f,0xff,0xff,0xf0,0xff,0xff,
  0xff,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xe0,0x00,0x00,0x1f,
  0xff,0xff,0xff,0xf8,0x00,0x00,0x1f,0xff,0xff,0xf0,0xff,0xff,0xff,0x00,0x00,0x01,
  0xff,0xff,0xff,0xfc,0x00,0x00,0x01,0xff,0xf0,0x00,0x00,0x0f,0xff,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,0xff,0xff,0xff,0x80,0x00,0x00,0x7f,0xff,0xff,0xf0,
  0x00,0x00,0x03,0xff,0xf8,0x00,0x00,0x03,0xff,0xff,0xff,0xc0,0x00,0x00,0x7f,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xc0,0x00,0x00,0x1f,0xff,0xff,0xc0,0x00,0x00,0x07,0xff,
  0xfc,0x00,0x00,0x00,0x7f,0xff,0xfe,0x00,0x00,0x00,0x7f,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xe0,0x00,0x00,0x03,0xff,0xfe,0x00,0x00,0x00,0x0f,0xff,0xfe,0x00,0x00,0x00,
  0x0f,0xff,0xf0,0x00,0x00,0x00,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xe0,0x00,0x00,
  0x00,0x0f,0x80,0x00,0x00,0x00,0x1f,0xff,0xff,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,
  0x00,0x01,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x3f,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,
  0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xe0,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xfe,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x1f,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x00,
  0x00,0x07,0xff,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xec,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,
  0xff,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xcd,0x7f,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xff,0x00,0x00,
  0x00,0x00,0x00,0x00,0x01,0xff,0xa1,0x7f,0xff,0xf0,0xff,0xff,0xff,0xff,0xf8,0x00,
  0x00,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x00,
  0x03,0xff,0xa1,0x7f,0xff,0xf0,0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x00,
  0x01,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xad,0x7f,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,
  0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xe1,0x7f,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,
  0x00,0x00,0x00,0x00,0x7f,0xff,0xce,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xf0,
  0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00,0x03,
  0xff,0xff,0xf1,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xfe,0x00,0x00,0x00,0x03,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x1f,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xfc,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xf0,0x00,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xf0};
  
void setup() {
  int i;
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  Serial.println((char *)"Preparing image buffer...");
  tpSetBackBuffer(ucBuf, WIDTH, HEIGHT);
  tpFill(0);
//  for (i=0; i<WIDTH; i += 32)
//  {
//    tpDrawLine(i, 0, WIDTH-1-i, HEIGHT-1, 1);
//  }
//  for (i=0; i<HEIGHT; i+= 8)
//  {
//    tpDrawLine(WIDTH-1, i, 0, HEIGHT-1-i, 1);
//  }
  tpDrawText(0,0,(char *)"BitBank Thermal Printer", FONT_LARGE, 0);
  i = tpLoadBMP((uint8_t *)logo_bmp, 0, 82, 64);
  if (i != 0)
  {
    Serial.println((char *)"tpLoadBMP error!");
    while (1) {};
  }
  Serial.println((char *)"Scanning for BLE printer");
  if (tpScan("MTP-2",5))
  {
    Serial.println((char *)"Found a printer!, connecting...");
    if (tpConnect())
    {
      Serial.println((char *)"Connected!, printing graphics");
      tpPrintBuffer();
      Serial.println((char *)"Testing plain text printing");
      tpSetFont(0, 0, 0, 0, 0);
      tpPrint((char *)"12x24 plain text\r");
      tpSetFont(1, 0, 0, 0, 0);
      tpPrint((char *)"9x17 plain text\r");
      tpSetFont(1, 1, 0, 0, 0);
      tpPrint((char *)"Underlined\r");
      tpSetFont(1, 0, 1, 0, 0);
      tpPrint((char *)"Double Wide\r");
      tpSetFont(1, 0, 0, 1, 0);
      tpPrint((char *)"Double Tall\r");
      tpSetFont(1, 0, 1, 1, 0);
      tpPrint((char *)"Double Tall+Wide\r");
      tpSetFont(1, 0, 1, 1, 1);
      tpPrint((char *)"Double Tall+Wide + emphasized\r");
      Serial.println((char *)"Disconnecting");
      tpDisconnect();
      Serial.println((char *)"Done!");
      while (1) {};      
    }
  }
  else
  {
    Serial.println((char *)"Didn't find a printer :( ");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}