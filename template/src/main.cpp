#include "main.hpp"

// 1. This creates your Menu Toggle switch. 
// Set it to 'true' to start with the cheat turned ON when you boot up the game.
bool myMenuToggle = true; 

// 2. This links the exact address to the Quest game engine
MAKE_HOOK_MATCH(Baseball_GetVelocityWhenHitBat, 0x19ED48C, Vector3, int* self, Vector3 ballPosition, Vector3 cachedVelocity, int* collision, float* hitSpeed) {

    // Let the game calculate normal launch physics first
    Vector3 originalVelocity = Baseball_GetVelocityWhenHitBat(self, ballPosition, cachedVelocity, collision, hitSpeed);

    // 3. Check our menu switch status
    if (myMenuToggle == true) {
        // If the toggle is active, boost the speed by 50x!
        return originalVelocity * 50.0f; 
    }

    // If the toggle is turned off, return standard baseball rules
    return originalVelocity; 
}

void setup(ModInfo& info) {
    info.id = "gorillabaseball_cheat";
    info.version = "1.0.0";
}

void load() {
    // 4. This physically activates your address hook inside your Quest game code
    INSTALL_HOOK(Baseball_GetVelocityWhenHitBat);
}
