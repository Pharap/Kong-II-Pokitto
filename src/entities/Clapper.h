#pragma once

#include "Pokitto.h"
#include "../Utils/Enums.h"
#include "../Utils/Utils.h"

class Clapper {

    public:

        Clapper();

        // Properties ..

        int16_t getXPosition(ViewSize viewSize);
        uint8_t getYPosition(ViewSize viewSize, uint8_t yOffset);
        uint8_t getImage(ViewSize viewSize);
        bool isEnabled();

        void setEnabled(bool enabled);
        void setY(uint8_t y);


        // Methods

        void updatePosition();
        Rect getRect(uint8_t yOffset, GameMode mode);

    protected:

        bool enabled = false;
        int16_t x;
        uint8_t y;

};
