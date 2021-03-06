#include "Player.h"

#include "../utils/Enums.h"
#include "../map/Coordinates.h"

#define JUMP_POSITIONS 37

const uint8_t PROGMEM jumpPositions[JUMP_POSITIONS] = { 
0, 2, 4, 6,
8, 9, 10, 10,
11, 11, 12, 12, 
12, 13, 13, 13, 
13, 13, 13, 13, 
13, 13, 13, 13, 
13, 12, 12, 12, 
11, 11, 10, 9, 
8, 6, 4, 2, 
0
};

Player::Player() { 

//    this->setPosition(0);

}

uint16_t Player::getPosition() {

    return this->position;

}

uint8_t Player::getJumpPosition() {

    return this->jumpPosition;

}

uint8_t Player::getXPosition(ViewSize viewSize, bool updatePrevPosition) {

    if (viewSize == ViewSize::Normal) {

        if (updatePrevPosition) {
            this->prevXPosition = this->playerData.x;
        }

        switch (this->playerData.stance) {

            case Stance::OnRope_01:
                return this->playerData.x + 7 + VIEW_NORMAL_X_OFFSET;

            case Stance::OnRope_02:
                return this->playerData.x + 6 + VIEW_NORMAL_X_OFFSET;

            case Stance::OnRope_03:
                return this->playerData.x - 2 + VIEW_NORMAL_X_OFFSET;

            case Stance::OnRope_04:
                return this->playerData.x - 3 + VIEW_NORMAL_X_OFFSET;

            default:
                Coordinates::readPlayerData(viewSize, this->playerData, this->getPosition());
                return this->playerData.x + VIEW_NORMAL_X_OFFSET;

        }
    
    }
    else {

        if (updatePrevPosition) {
            this->prevXPosition = this->playerData.x;
        }

        switch (this->playerData.stance) {

            case Stance::OnRope_01:
                return (this->playerData.x + 1);

            case Stance::OnRope_02:
                return (this->playerData.x - 1);

            case Stance::OnRope_03:
                return (this->playerData.x - 17);

            case Stance::OnRope_04:
                return (this->playerData.x - 18);

            default:
                Coordinates::readPlayerData(viewSize, this->playerData, this->getPosition());
                return (this->playerData.x - 14);

        }

    }

}

uint8_t Player::getYPosition(ViewSize viewSize) {

    if (viewSize == ViewSize::Normal) {

        uint8_t y = this->playerData.y - jumpPositions[this->jumpPosition];

        if (y < 63) {
            y = y + VIEW_NORMAL_Y_UPPER_OFFSET;
        }
        else {

            y = y + VIEW_NORMAL_Y_LOWER_OFFSET;
        }
        
        return y;

    }
    else {

        int8_t y = this->playerData.y - this->playerData.yOffset - (jumpPositions[this->jumpPosition] * 2);
        return y;

    }

}

uint8_t Player::getMovements() {

    return this->playerData.movements;

}

uint8_t Player::getYOffset() {

    return this->playerData.yOffset;

}

bool Player::isDead() {

    return this->dead;

}

bool Player::isFalling() {

    return this->falling;

}

bool Player::getExit() {

    return this->exit;

}

void Player::setPosition(ViewSize viewSize, uint16_t position) {

    this->position = position;
    this->jumpPosition = 0;
    Coordinates::readPlayerData(viewSize, this->playerData, this->getPosition());

}

void Player::setJumpPosition(uint8_t jumpPosition) {

    this->jumpPosition = jumpPosition;

}

void Player::setDead(bool dead) {

    this->dead = dead;

}

void Player::setFalling(bool falling) {

    this->falling = falling;

}

void Player::setExit(bool exit) {

    this->exit = exit;

}

void Player::incPlayerPosition(ViewSize viewSize) {

    this->prevXPosition = this->playerData.x;
    this->position++;
    Coordinates::readPlayerData(viewSize, this->playerData, this->getPosition());

}

void Player::decPlayerPosition(ViewSize viewSize, bool exitSequence) {

    this->prevXPosition = this->playerData.x;
    this->position--;

    Coordinates::readPlayerData(viewSize, this->playerData, this->getPosition());

    if (this->playerData.stance == Stance::Falling_01 || this->playerData.stance == Stance::Falling_02) {

        this->falling = true;

        switch (this->position) {

            case PLAYER_VINE_0:
                this->falling = false;
                break;

            case PLAYER_VINE_1:
                this->falling = false;
                break;

            case PLAYER_CHAIN_0_BACKTOGROUND:
                if (!exitSequence) {
                    this->position = PLAYER_CHAIN_0_GROUND;
                }
                else {
                    this->position = PLAYER_CHAIN_MOVE_TO_EXIT_0;
                }
                this->falling = false;
                break;

            case PLAYER_CHAIN_1_BACKTOGROUND:
                if (!exitSequence) {
                    this->position = PLAYER_CHAIN_1_GROUND;
                }
                else {
                    this->position = PLAYER_CHAIN_MOVE_TO_EXIT_1;
                }
                this->falling = false;
                break;

            case PLAYER_CHAIN_2_BACKTOGROUND:
                if (!exitSequence) {
                    this->position = PLAYER_CHAIN_2_GROUND;
                }
                else {
                    this->position = PLAYER_CHAIN_MOVE_TO_EXIT_2;
                }
                this->falling = false;                
                break;

            case PLAYER_CHAIN_3_BACKTOGROUND:
                if (!exitSequence) {
                    this->position = PLAYER_CHAIN_3_GROUND;
                }
                else {
                    this->position = PLAYER_CHAIN_MOVE_TO_EXIT_3;
                }
                this->falling = false;
                break;

        }

        if (!this->falling) {

            Coordinates::readPlayerData(viewSize, this->playerData, this->getPosition());

        }

    }
    else {

        this->falling = false;

    }
  
}

bool Player::canMove(Movements movement) {

    return (this->playerData.movements & static_cast<uint8_t>(movement));

}

void Player::updateJump() {

    if (this->jumpPosition < JUMP_POSITIONS - 1) {
        this->jumpPosition++;
    }
    else {
        this->jumpPosition = 0;
    }

}

void Player::startJump() {

    this->jumpPosition = 1;

}

bool Player::isJumping() {

    return this->jumpPosition > 0;

}

bool Player::canGrabChain() {

    return this->jumpPosition == 7;

}

bool Player::atTopOfJump() {

    return this->jumpPosition == 18;

}

uint8_t Player::getImage() {

    return getImage(true);

}

uint8_t Player::getImage(bool update) {

    uint8_t imageIndex = static_cast<uint8_t>(Stance::Normal);

    if (!this->dead) {
            
        if (this->jumpPosition == 0) {

            switch (this->playerData.stance) {

                case Stance::Normal:

                    if (this->playerData.x == this->prevXPosition) {

                        if (this->runMovement == Movements::Left) {
                            imageIndex = static_cast<uint8_t>(Stance::Normal);
                        }
                        else {
                            imageIndex = static_cast<uint8_t>(Stance::Normal_RHS);
                        }

                        break;

                    }

                    if (this->playerData.x > this->prevXPosition) {

                        if (update) this->runCounter++;
                        this->runMovement = Movements::Right;
                        if (this->runCounter == 8) this->runCounter = 0;
                        imageIndex = static_cast<uint8_t>(Stance::Running_01_RHS) + (this->runCounter / 4);

                        break;

                    }

                    if (this->playerData.x < this->prevXPosition) {

                        if (update) this->runCounter++;
                        this->runMovement = Movements::Left;
                        if (this->runCounter == 8) this->runCounter = 0;
                        imageIndex = static_cast<uint8_t>(Stance::Running_01) + (this->runCounter / 4);

                        break;

                    }

                    break;

                case Stance::Falling_01:

                    imageIndex = static_cast<uint8_t>(Stance::Running_01);
                    break;

                case Stance::Falling_02:

                    imageIndex = static_cast<uint8_t>(Stance::Running_01_RHS);
                    break;

                default:
                    
                    imageIndex = static_cast<uint8_t>(this->playerData.stance);
                    break;

            }

        }
        else {

            if (this->playerData.x == this->prevXPosition) {

                if (this->runMovement == Movements::Left) {
                    imageIndex = static_cast<uint8_t>(Stance::Running_02);
                }
                else {
                    imageIndex = static_cast<uint8_t>(Stance::Running_02_RHS);
                }

            }

        }

        this->prevImage = imageIndex;
        return imageIndex;

    }
    else { //dead

        return this->prevImage;

    }

}


Rect Player::getRect(ViewSize viewSize) {

    uint8_t x = this->getXPosition(viewSize, false);
    uint8_t y = this->getYPosition(viewSize);

    if (viewSize == ViewSize::Normal) {

        switch (static_cast<Stance>(this->getImage(false))) {

            case Stance::Normal ... Stance::Normal_RHS:
                return Rect {x + 4, y + 1, 9, 10};

            case Stance::Running_01 ... Stance::Running_02_RHS:
                return Rect {x + 1, y + 1, 16, 10};

            case Stance::OnRope_01:
                return Rect {x + 1, y + 1, 12, 11};

            case Stance::OnRope_02:
                return Rect {x + 1, y + 1, 12, 11};

            case Stance::OnRope_03:
                return Rect {x + 1, y + 1, 12, 11};

            case Stance::OnRope_04:
                return Rect {x + 1, y + 1, 12, 11};

            case Stance::Falling_01 ... Stance::Falling_02:
                return Rect {x + 3, y + 1, 16, 10};

            case Stance::Climbing_Vine_01 ... Stance::Climbing_Vine_02:
                return Rect {x + 1, y + 1, 14, 12};

            default: // case Stance::Jump:
                return Rect {x + 1, y + 1, 16, 10};

        }

    }
    else {

        switch (static_cast<Stance>(this->getImage(false))) {

            case Stance::Normal ... Stance::Normal_RHS:
                return Rect {x + 8, y + 2, 19, 22};

            case Stance::Running_01 ... Stance::Running_02_RHS:
                return Rect {x + 2, y + 2, 32, 21};

            case Stance::OnRope_01:
                return Rect {x + 2, y + 2, 24, 22};

            case Stance::OnRope_02:
                return Rect {x + 2, y + 2, 24, 22};

            case Stance::OnRope_03:
                return Rect {x + 2, y + 2, 24, 22};

            case Stance::OnRope_04:
                return Rect {x + 1, y + 2, 24, 22};

            case Stance::Falling_01 ... Stance::Falling_02:
                return Rect {x + 2, y + 2, 32, 20};

            case Stance::Climbing_Vine_01 ... Stance::Climbing_Vine_02:
                return Rect {x + 2, y + 2, 28, 24};

            default: // case Stance::Jump:
                return Rect {x + 2, y + 2, 31, 21};

        }

    }

}

void Player::reset(ViewSize viewSize) {

    this->setPosition(viewSize, 0);
    this->setJumpPosition(0);
    this->dead = false;
    this->falling = false;
    this->prevXPosition = -1;
    this->runMovement = Movements::Right;

}