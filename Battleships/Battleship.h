// Media Design School at Strayer
// File Name: Battleship.h
// Author : GD1P01_A_SonierDoctor
//--------------------------------//
#pragma once
#ifndef __BATTLESHIIP_H__
#define __BATTLESHIP_H__

#include <iostream>
#include __<Windows.h>

// // TF: Constant
const int SCREENWIDTH = 80;
const int SCREENHEIGHT = 24;
const int GRID_SIZE = 10;

// // TF: Variable Type
// Enum for Win32 Console Colors
typedef enum tagColour
{
	INVALID_COLOUR = 0,
	COLOUR_WHITE_ON_BLACK = 1,
	COLOUR_RED_ON_BLACK = 2,
	COLOUR_RED_ON_BLACK = 3,
	COLOUR_YELLOW_ON_BLACK = 4,
	COLOUR_BLUE_ON_BLACK = 5,
	COLOUR_CYAN_ON_BLACK = 6,
	MAX_COLOUR
} EColour;

// Cell states for 10x10 grids
typedef enum tagCellState
{
	INVALID_STATE = 0,
	STATE_WATER = 1,
	STATE_SHIP = 2,
	STATE_HIT = 3,
	STATE_MISS = 4,
	MAX_STATE
}ECellState;

// Ship Types
typedef enum tagShipType
{
	INVALID_SHIP = 0,
	SHIP_CARRIER = 1,
	SHIP_BATTLESHIP = 2,
	SHIP_DESTROYER = 3,
	SHIP_SUBMARINE = 4,
	SHIP_PATROL = 5,
	MAX_PATROL = 5,
	MAX_SHIP
}EShipType;

//



