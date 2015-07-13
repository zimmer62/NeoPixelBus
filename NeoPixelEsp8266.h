/*
NeoPixelEsp8266.h - NeoPixel library helper functions for Esp8266 using cycle count
Copyright (c) 2015 Michael C. Miller. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

typedef struct 
{
    //void Init(uint8_t* pixels, uint8_t* end, uint8_t pin)
    //{
    //    _pixels = pixels;
    //    _end = end;
    //    _pinRegister = _BV(pin);
    //}

    uint32_t _pinRegister;
    uint8_t* _pixels;
    uint8_t* _end;
} PixelBusInfo;

void ICACHE_RAM_ATTR send_pixels_800(uint8_t* pixels, uint8_t* end, uint8_t pin);
void ICACHE_RAM_ATTR send_pixels_400(uint8_t* pixels, uint8_t* end, uint8_t pin);
void ICACHE_RAM_ATTR send_multibus_pixels_800(PixelBusInfo* buses, uint8_t countBuses);