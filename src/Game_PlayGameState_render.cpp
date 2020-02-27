#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Render the state .. 
//
void Game::playGame_Render() {

    const uint8_t yOffset = playGameVars.player.getYOffset();


    // Draw Scenery ..

    playGame_DrawScenery(yOffset);


    // Draw player

    if (!gameStats.gameOver) {

        if (playGameVars.introDelay == 0) {

            uint8_t stance = playGameVars.player.getImage();
            uint8_t x = playGameVars.player.getXPosition(this->gameStats.viewSize, false);
            uint8_t y = playGameVars.player.getYPosition(this->gameStats.viewSize);

            PD::drawBitmap(x, y, Images::Junior[stance]);

        }
        else {

            if ((playGameVars.introDelay / 20) % 2 == 0) {

                uint8_t x = playGameVars.player.getXPosition(this->gameStats.viewSize, false);
                uint8_t y = playGameVars.player.getYPosition(this->gameStats.viewSize);

                if (playGameVars.player.isDead()) {

                    uint8_t stance = playGameVars.player.getImage();
                    PD::drawBitmap(x, y, Images::Junior[stance]);

                }
                else {

                    PD::drawBitmap(x, y, Images::Jnr_Idle_R_F0);

                }

            }

        }

    }


    // Draw Kong
/*
    if (playGameVars.kong.getEnabled()) {

        playGame_RenderKong(yOffset);

    }
*/

    // Draw sparks / birds / clappers ..

    for (uint8_t i = 0; i < NUMBER_OF_ENTITIES; i++) {

        auto &lowerClapper = playGameVars.lowerClappers.getClapper(i);

        if (lowerClapper.isEnabled()) {

            int16_t x = lowerClapper.getXPosition(this->gameStats.viewSize);
            uint8_t y = lowerClapper.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = lowerClapper.getImage(this->gameStats.viewSize);

            PD::drawBitmap(x, y, Images::Clappers[index]);

        }

        auto &upperClapper = playGameVars.upperClappers.getClapper(i);

        if (upperClapper.isEnabled()) {

            int16_t x = upperClapper.getXPosition(this->gameStats.viewSize);
            uint8_t y = upperClapper.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = upperClapper.getImage(this->gameStats.viewSize);

            PD::drawBitmap(x, y, Images::Clappers[index]);

        }

        auto &lowerSpark = playGameVars.lowerSparks.getSpark(i);

        if (lowerSpark.isEnabled()) {

            uint8_t x = lowerSpark.getXPosition(this->gameStats.viewSize);
            uint8_t y = lowerSpark.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = lowerSpark.getImage();

            if (static_cast<SparkImage>(index) != SparkImage::None) {
                PD::drawBitmap(x, y, Images::Spark[index]);
            }

        }

        auto &upperSpark = playGameVars.upperSparks.getSpark(i);

        if (upperSpark.isEnabled()) {

            uint8_t x = upperSpark.getXPosition(this->gameStats.viewSize);
            uint8_t y = upperSpark.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = upperSpark.getImage();

            if (static_cast<SparkImage>(index) != SparkImage::None) {
                PD::drawBitmap(x, y, Images::Spark[index]);
            }

        }

        auto &bird = playGameVars.birds.getBird(i);

        if (bird.isEnabled()) {

            uint8_t x = bird.getXPosition(this->gameStats.viewSize);
            uint8_t y = bird.getYPosition(this->gameStats.viewSize, yOffset);
            uint8_t index = bird.getImage();

            if (static_cast<BirdImage>(index) != BirdImage::None) {

                PD::drawBitmap(x, y, Images::Birds[index]);

            }

        }

    }

    if (this->gameStats.viewSize == ViewSize::Normal) {

        PD::drawBitmap(VIEW_NORMAL_X_OFFSET - 8, 107 + VIEW_NORMAL_Y_LOWER_OFFSET, Images::Scenery_Edge_L);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 107 + VIEW_NORMAL_Y_LOWER_OFFSET, Images::Scenery_Edge_R);

        PD::drawBitmap(VIEW_NORMAL_X_OFFSET - 8, 54 + VIEW_NORMAL_Y_UPPER_OFFSET, Images::Scenery_Edge_L);
        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 54 + VIEW_NORMAL_Y_UPPER_OFFSET, Images::Scenery_Edge_R);

        PD::drawBitmap(VIEW_NORMAL_X_OFFSET + 128, 42 + VIEW_NORMAL_Y_UPPER_OFFSET, Images::Scenery_Edge_R_Large);

    // playGameVars.lowerClappers.reset(107);

    // playGameVars.upperClappers.setDelayMax(playGameVars.clappersUpperDelay, true);
    // playGameVars.upperClappers.reset(54);


    }

/*
    playGame_RenderKey(yOffset);
    playGame_RenderGameOverOrPause();


    // Render score ..

    playGame_RenderScore(yOffset);
*/
}


// ----------------------------------------------------------------------------
//  Render Kong .. 
//
void Game::playGame_RenderKong(uint8_t yOffset) {

    // int8_t x = playGameVars.kong.getXPosition(this->gameStats.viewSize);
    // int8_t y = playGameVars.kong.getYPosition(this->gameStats.viewSize, yOffset);
    // KongImage image = playGameVars.kong.getImage();

    // Sprites::drawErase(x, y, pgm_read_word_near(&Images::Kong_Mask[static_cast<uint8_t>(image)]), 0);
    // Sprites::drawSelfMasked(x, y, pgm_read_word_near(&Images::Kong[static_cast<uint8_t>(image)]), 0);
    
    // const uint8_t xPos[] = { 30, 47, 76, 83 };
    // const uint8_t yPos[] = { 6, 11, 11, 6 };
    
    // for (uint8_t i = 0; i < 4 ; i++) {

    //     if (playGameVars.kong.getDisplayChain(i)) {

    //         Sprites::drawErase(xPos[i], yPos[i] - yOffset, pgm_read_word_near(&Images::Lock_Chains_Mask[i]), 0);
    //         Sprites::drawSelfMasked(xPos[i], yPos[i] - yOffset, pgm_read_word_near(&Images::Lock_Chains[i]), 0);

    //     }

    // }

}


// ----------------------------------------------------------------------------
//  Render key .. 
//
void Game::playGame_RenderKey(uint8_t yOffset) {

    // Render key ..

    // if (playGameVars.key.getKeyLocation() != KeyLocation::None) {

    //     int8_t x = playGameVars.key.getXPosition();
    //     int8_t y = playGameVars.key.getYPosition(yOffset);
    //     uint8_t index = playGameVars.key.getImage();

    //     if (index == NO_IMAGE) {

    //         index = arduboy.getFrameCount() % 59 / 15;
    //         Sprites::drawErase(x, y, Images::Key_Spin_Mask, index);
    //         Sprites::drawSelfMasked(x, y, Images::Key_Spin, index);

    //     }
    //     else {

    //         if (playGameVars.key.getDisplay()) {
    //             Sprites::drawErase(x, y, Images::Key_Rotate_Mask, index);
    //             Sprites::drawSelfMasked(x, y, Images::Key_Rotate, index);
    //         }

    //     }

    // }

}