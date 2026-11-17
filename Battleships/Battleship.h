/***************************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer

File Name     : Battleship.h
Description   : Header file for Battleship game data structures, enums, and CGrid class.
Author        : Adam Sonier-Doctor (GD1P01_A_SonierDoctor)
Mail          : adam.sonier-doctor@mds.ac.nz
**************************************************************************/

#pragma once

#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <iostream>
#include <Windows.h>

// TF: Constant
const int SCREENWIDTH = 80;
const int SCREENHEIGHT = 24;
const int GRID_SIZE = 10;

// TF: Variable Type
// Enum for Win32 Console Colours
typedef enum tagColour
{
	INVALID_COLOUR = 0,
	COLOUR_WHITE_ON_BLACK = 1,
	COLOUR_RED_ON_BLACK = 2,
	COLOUR_GREEN_ON_BLACK = 3,
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
} ECellState;

// Ship Types
typedef enum tagShipType
{
	INVALID_SHIP = 0,
	SHIP_CARRIER = 1,
	SHIP_BATTLESHIP = 2,
	SHIP_DESTROYER = 3,
	SHIP_SUBMARINE = 4,
	SHIP_PATROL = 5,
	MAX_SHIP
} EShipType;

// Structure for Ship properties
typedef struct tagShip // TF: Structure
{
	EShipType m_eType;
	int m_iSize;
	int m_iHitsTaken;
	bool m_bIsSunk;
} TShip;

// TF: Class
class CGrid
{
	// TF: Access Specifier
private:
	// TF: Array
	ECellState m_aGridCells[GRID_SIZE][GRID_SIZE];

public:
	// TF: Constructor
	CGrid();

	// TF: Destructor
	~CGrid();

	// TF: Copy Constructor
	CGrid(const CGrid& _rOther);

	void InitializeGrid();
	ECellState GetCellState(int _iRow, int _iCol) const;
	void SetCellState(int _iRow, int _iCol, ECellState _eState);
	bool IsValidCoordinate(int _iRow, int _iCol) const;
};

// Console Utilities Prototypes
void SetRgb(EColour _eColour);
void GotoXY(int _iX, int _iY);
void ClearScreen();
void DrawConsoleHeader(EColour _eColour);
void ExecuteGameLoop();
void RunGameSession();
void InitializeFleet(TShip _aShips[], int _iNumShips);
bool PlacePlayerShips(CGrid& _rGrid, TShip _aShips[]);
void AiTurn(CGrid& _rPlayerGrid);
bool CheckAllShipsSunk(const TShip _aShips[]);
#endif // __BATTLESHIP_H__