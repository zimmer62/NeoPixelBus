/*-------------------------------------------------------------------------
Arduino library to control a wide variety of WS2811- and WS2812-based RGB
LED devices such as Adafruit FLORA RGB Smart Pixels and NeoPixel strips.

Copyright (c) 2015 Michael C. Miller. All right reserved.

-------------------------------------------------------------------------
NeoPixel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

NeoPixel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with NeoPixel.  If not, see
<http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------*/

#include "NeoPixelBus.h"


NeoPixelMultiBus::NeoPixelMultiBus(uint8_t size) :
    _size(size),
    _count(0)
{
    _buses = new NeoPixelBus*[size];
    if (_buses)
    {
        memset(_buses, 0, sizeof(_buses));
    }
}

NeoPixelMultiBus::~NeoPixelMultiBus()
{
    if (_buses)
        delete[] _buses;
}

void NeoPixelMultiBus::AddBus(NeoPixelBus* pBus)
{
    if (_count < _size)
    {
        _buses[_count] = pBus;
        _count++;
    }
}

void NeoPixelMultiBus::ShowAll()
{
    if (!IsDirty())
        return;

    // Data latch = 50+ microsecond pause in the output stream.  Rather than
    // put a delay at the end of the function, the ending time is noted and
    // the function will simply hold off (if needed) on issuing the
    // subsequent round of data until the latch time has elapsed.  This
    // allows the mainline code to start generating the next frame of data
    // rather than stalling for the latch.
    while (!CanShow())
    {
        delay(0); // allows for system yield if needed
    }

    PixelBusInfo busInfos[_count];
    for (uint8_t indexBus = 0; indexBus < _count; indexBus++)
    {
        NeoPixelBus* pBus = _buses[indexBus];
        busInfos[indexBus]._pixels = pBus->Pixels();
        busInfos[indexBus]._end = pBus->Pixels() + pBus->PixelSize();
        busInfos[indexBus]._pinRegister = _BV(pBus->Pin());
    }


    noInterrupts(); // Need 100% focus on instruction timing

#if defined(ESP8266)
    // 800 KHz bitstream, 400 KHz will not be supported
    send_multibus_pixels_800(busInfos, _count);
#endif

    interrupts();

    for (uint8_t indexBus = 0; indexBus < _count; indexBus++)
    {
        _buses[indexBus]->ResetDirty();
    }

    _endTime = micros(); // Save EOD time for latch on next call
}

bool NeoPixelMultiBus::IsDirty() const
{
    bool isDirty = false;
    for (uint8_t indexBus = 0; indexBus < _count; indexBus++)
    {
        if (_buses[indexBus]->IsDirty())
        {
            isDirty = true;
            break;
        }
    }
    return isDirty;
};

void NeoPixelMultiBus::Dirty()
{
    if (_count > 0)
    {
        // just set the first one, thats all thats needed
        _buses[0]->Dirty();
    }
};

void NeoPixelMultiBus::ResetDirty()
{
    for (uint8_t indexBus = 0; indexBus < _count; indexBus++)
    {
        _buses[indexBus]->ResetDirty();
    }
}