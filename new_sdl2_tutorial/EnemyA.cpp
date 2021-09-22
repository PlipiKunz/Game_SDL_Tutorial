#include "EnemyA.h"
#include "globals.h"
#include <iostream>

#include <stdio.h>
#include <string>

EnemyA::EnemyA(int x, int y, int width, int height) :GameObject::GameObject(true, x, y, width, height) {
}

void EnemyA::step(const Uint8* currentKeyStates) {
}
