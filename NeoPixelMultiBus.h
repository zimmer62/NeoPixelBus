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

#pragma once

class NeoPixelMultiBus
{
public:
    NeoPixelMultiBus(uint8_t size);
    ~NeoPixelMultiBus();

    void AddBus(NeoPixelBus* pBus);

    void ShowAll();

    inline bool CanShow(void) const
    {
        return (micros() - _endTime) >= 50L;
    }

    bool IsDirty() const
    {
        bool isDirty = false;
        for (uint8_t indexBus = 0; indexBus < _count; indexBus++)
        {
            if (_buses[indexBus].IsDirty())
            {
                isDirty = true;
                break;
            }
        }
        return isDirty;
    };

    void Dirty()
    {
        if (_count > 0)
        {
            // just set the first one, thats all thats needed
            _buses[0].Dirty();
        }
    };

    void ResetDirty()
    {
        for (uint8_t indexBus = 0; indexBus < _count; indexBus++)
        {
            _buses[indexBus].ResetDirty();
        }
    }

private:
    uint32_t _endTime;       // Latch timing reference

    NeoPixelBus* _buses;
    uint8_t _count;
    uint8_t _size;
};