
#include "ModuleCollisions.h"
#include "BoundingBox.h"

// Define the bounding box around the visible area of the game screen
const int BOUNDING_BOX_WIDTH = 240;
const int BOUNDING_BOX_HEIGHT = 340;
const int BOUNDING_BOX_X = 0;
const int BOUNDING_BOX_Y = 0;

// Check if an enemy is off-screen
bool isOffScreen(int enemyX, int enemyY) {
    if (enemyX < BOUNDING_BOX_X || enemyX > BOUNDING_BOX_X + BOUNDING_BOX_WIDTH) {
        return true; // Enemy is off-screen horizontally
    }
    if (enemyY < BOUNDING_BOX_Y || enemyY > BOUNDING_BOX_Y + BOUNDING_BOX_HEIGHT) {
        return true; // Enemy is off-screen vertically
    }
    return false; // Enemy is on-screen
}
