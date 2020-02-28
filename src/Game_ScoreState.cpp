#include "Game.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::highScore_Activate() {
	
    // uint16_t score = EEPROM_Utils::readSaveScore(gameStats.mode);

    // playGameVars.frameRate = FRAME_RATE_MIN;
    // PC::setFrameRate(playGameVars.frameRate);
    // arduboy.clearButtonState();

    // highScoreVars.counter = 50;
    // highScoreVars.newHighScore = false;
    // highScoreVars.selectedMode = gameStats.mode;

    // if (gameStats.score >= score) {
    //     EEPROM_Utils::saveScore(gameStats.mode, gameStats.score);
    //     highScoreVars.newHighScore = true;
    // }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::highScore_Update() {


    // Handle other input ..

//     if (highScoreVars.counter > 0) {
//         highScoreVars.counter--;
//     }
//         else {

//         if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
//             gameState = GameStateType::TitleScreen_Activate; 
//         }

//         if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1))) {
//             highScoreVars.selectedMode = GameMode::Easy;
//         }

//         if ((PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1))) {
//             highScoreVars.selectedMode = GameMode::Hard;
//         }

//     }


// 	// Clear scores ..

// 	if (PC::buttons.repeat(BTN_LEFT, 1) && PC::buttons.repeat(BTN_RIGHT, 1)) {

// 		highScoreVars.clearScores++;

// 		switch (highScoreVars.clearScores) {

// 			case 21 ... 60:

// //				arduboy.setRGBled(128 - (highScoreVars.clearScores * 2), 0, 0);
// 				break;

// 			case 61:

// 				highScoreVars.clearScores = 0;
// //				arduboy.setRGBled(0, 0, 0);
// 				EEPROM_Utils::clearEEPROM();

// 				break;

// 		}

// 	}
// 	else {

// 		if (highScoreVars.clearScores > 0) {
		
// //			arduboy.setRGBled(0, 0, 0);
// 			highScoreVars.clearScores = 0;

// 		}
		
//	}

}


void Game::highScore_RenderHighScore(uint16_t score) {

    // for (uint8_t j = 4; j > 0; --j) {

    //     uint8_t digits[4] = {};
    //     extractDigits(digits, score);
    //     Sprites::drawErase(79 - (j*7), 41, Images_Normal::Numbers, digits[j - 1]);

    // }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void Game::highScore_Render() {

    // Sprites::drawOverwrite(0, 0, Images_Normal::HighScore_Left, 0);
    // Sprites::drawOverwrite(113, 0, Images_Normal::HighScore_Right, 0);
    // Sprites::drawOverwrite(15, 56, Images_Normal::HighScore_Bottom, 0);
    // Sprites::drawOverwrite(49, 38, Images_Normal::HighScore_Jnr, 0);
    // Sprites::drawOverwrite(19, 30, Images_Normal::HighScore_Chains, 0);
    // Sprites::drawOverwrite(103, 30, Images_Normal::HighScore_Chains, 0);
    // Sprites::drawOverwrite(10, 10, Images_Normal::HighScore_Panel_Left, 0);
    // Sprites::drawOverwrite(51, 0, Images_Normal::HighScore_Panel_Mid, 0);
    // Sprites::drawOverwrite(76, 10, Images_Normal::HighScore_Panel_Right, 0);
    // Sprites::drawOverwrite(9, 22, Images_Normal::HighScore_Chain_Left, 0);
    // Sprites::drawOverwrite(111, 22, Images_Normal::HighScore_Chain_Right, 0);

    // switch(highScoreVars.selectedMode) {

    //     case GameMode::Easy:
    //         Sprites::drawOverwrite(16, 50, Images_Normal::HighScore_Easy, 0);
    //         break;

    //     case GameMode::Hard:
    //         Sprites::drawOverwrite(95, 50, Images_Normal::HighScore_Hard, 0);
    //         break;

    // }

    // if (!highScoreVars.newHighScore || (highScoreVars.newHighScore & Utils::getFrameCountHalf(64))) { 

    //     uint16_t score = EEPROM_Utils::readSaveScore(highScoreVars.selectedMode);
    //     highScore_RenderHighScore(score);

    // }

}