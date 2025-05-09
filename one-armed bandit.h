﻿#pragma once

#include <iostream>
#include "button.h"
#include "roulette.h"
#include <random>
#include <SFML/Graphics.hpp>

const int widthWindow = 960;
const int heightWindow = 540;

bool isRouletteEnabled = false;
float timeOfScroll = 3.5, duration = 1;

int balance = 0;

sf::Texture interfaceTexture;
sf::Sprite interfaceSprite;
