/***************************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer

File Name     : Battleship.cpp
Description   : Implementation file for Battleship game logic and CGrid class.
Author        : Adam Sonier-Doctor (GD1P01_A_SonierDoctor)
Mail          : adam.sonier-doctor@mds.ac.nz
**************************************************************************/

#include "Battleship.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <limits>

// TF: Constructor
CGrid::CGrid()
{
	InitializeGrid();
}

// TF: Destructor
CGrid::~CGrid()
{
	// Clean up dynamic resources if allocated
}

// TF: Copy Constructor
CGrid::CGrid(const CGrid& _rOther)
{
	// TF: Iteration Structure
	for (int iR = 0; iR < GRID_SIZE; ++iR)
	{
		for (int iC = 0; iC < GRID_SIZE; ++iC)
		{
			// TF: Pointer Dereferenced
			this->m_aGridCells[iR][iC] = _rOther.m_aGridCells[iR][iC];
		}
	}
}

void CGrid::InitializeGrid()
{
	for (int iR = 0; iR < GRID_SIZE; ++iR)
	{
		for (int iC = 0; iC < GRID_SIZE; ++iC)
		{
			m_aGridCells[iR][iC] = STATE_WATER;
		}
	}
}

ECellState CGrid::GetCellState(int _iRow, int _iCol) const
{
	// TF: Conditional Statement
	if (IsValidCoordinate(_iRow, _iCol))
	{
		return m_aGridCells[_iRow][_iCol];
	}
	else
	{
		return INVALID_STATE;
	}
}

void CGrid::SetCellState(int _iRow, int _iCol, ECellState _eState)
{
	// TF: Logical Operator
	if ((_iRow >= 0) && (_iRow < GRID_SIZE) && (_iCol >= 0) && (_iCol < GRID_SIZE))
	{
		m_aGridCells[_iRow][_iCol] = _eState;
	}
	else
	{
		// Unhandled out-of-bounds error state
	}
}

bool CGrid::IsValidCoordinate(int _iRow, int _iCol) const
{
	// TF: Relational Operator
	return ((_iRow >= 0) && (_iRow < GRID_SIZE) && (_iCol >= 0) && (_iCol < GRID_SIZE));
}

// TF: Default Parameter
void DrawConsoleHeader(EColour _eColour = COLOUR_CYAN_ON_BLACK)
{
	SetRgb(_eColour);
	std::cout << "========================================\n";
	std::cout << "   MDS GD1P02 BATTLESHIP GAME CONSOLE   \n";
	std::cout << "========================================\n";
}

// Helper: Draw 10x10 Grid on Console (with optional ship concealment)
void DrawGrid(int _iStartX, int _iStartY, const CGrid& _rGrid, const std::string& _sTitle, bool _bShowShips = true)
{
	GotoXY(_iStartX, _iStartY - 1);
	SetRgb(COLOUR_CYAN_ON_BLACK);
	std::cout << _sTitle;

	// Draw Column headers (0-9)
	GotoXY(_iStartX, _iStartY);
	std::cout << "  0 1 2 3 4 5 6 7 8 9 ";

	for (int iR = 0; iR < GRID_SIZE; ++iR)
	{
		GotoXY(_iStartX, _iStartY + 1 + iR);
		SetRgb(COLOUR_CYAN_ON_BLACK);
		std::cout << iR << " "; // Row number

		for (int iC = 0; iC < GRID_SIZE; ++iC)
		{
			ECellState eState = _rGrid.GetCellState(iR, iC);

			if (eState == STATE_WATER)
			{
				SetRgb(COLOUR_BLUE_ON_BLACK);
				std::cout << "~ ";
			}
			else if (eState == STATE_SHIP)
			{
				if (_bShowShips)
				{
					SetRgb(COLOUR_GREEN_ON_BLACK);
					std::cout << "S "; // Shown only if bShowShips is true
				}
				else
				{
					SetRgb(COLOUR_BLUE_ON_BLACK);
					std::cout << "~ "; // Hidden as water on Target Grid!
				}
			}
			else if (eState == STATE_HIT)
			{
				SetRgb(COLOUR_RED_ON_BLACK);
				std::cout << "X ";
			}
			else if (eState == STATE_MISS)
			{
				SetRgb(COLOUR_YELLOW_ON_BLACK);
				std::cout << "O ";
			}
			else
			{
				SetRgb(COLOUR_WHITE_ON_BLACK);
				std::cout << ". ";
			}
		}
	}
}

// Helper: Initialize Fleet
void InitializeFleet(TShip _aShips[], int _iNumShips)
{
	int iaSizes[5] = { 5, 4, 3, 3, 2 };
	EShipType eaTypes[5] = { SHIP_CARRIER, SHIP_BATTLESHIP, SHIP_DESTROYER, SHIP_SUBMARINE, SHIP_PATROL };

	for (int i = 0; i < _iNumShips; ++i)
	{
		_aShips[i].m_eType = eaTypes[i];
		_aShips[i].m_iSize = iaSizes[i];
		_aShips[i].m_iHitsTaken = 0;
		_aShips[i].m_bIsSunk = false;
	}
}

// Helper: Simple AI Turn
void AiTurn(CGrid& _rPlayerGrid)
{
	int iAiRow = rand() % GRID_SIZE;
	int iAiCol = rand() % GRID_SIZE;

	ECellState eTargetState = _rPlayerGrid.GetCellState(iAiRow, iAiCol);
	if (eTargetState == STATE_SHIP)
	{
		_rPlayerGrid.SetCellState(iAiRow, iAiCol, STATE_HIT);
	}
	else if (eTargetState == STATE_WATER)
	{
		_rPlayerGrid.SetCellState(iAiRow, iAiCol, STATE_MISS);
	}
}

// Playable Game Session Implementation with Win/Loss Tracking
void RunGameSession(bool _bDebugMode)
{
	CGrid PlayerGrid;
	CGrid AiGrid;

	// Setup initial sample ships for demonstration
	PlayerGrid.SetCellState(2, 2, STATE_SHIP);
	PlayerGrid.SetCellState(2, 3, STATE_SHIP);
	PlayerGrid.SetCellState(2, 4, STATE_SHIP);
	PlayerGrid.SetCellState(5, 5, STATE_SHIP);
	PlayerGrid.SetCellState(6, 5, STATE_SHIP);

	AiGrid.SetCellState(1, 1, STATE_SHIP);
	AiGrid.SetCellState(1, 2, STATE_SHIP);
	AiGrid.SetCellState(8, 3, STATE_SHIP);
	AiGrid.SetCellState(8, 4, STATE_SHIP);
	AiGrid.SetCellState(8, 5, STATE_SHIP);

	// Track ship health (5 ship cells per side in this setup)
	int iPlayerHealth = 5;
	int iAiHealth = 5;

	bool bGamePlaying = true;
	std::string sMessage = "Game Started! Enter target coordinates.";
	std::string sGameResult = "";

	while (bGamePlaying)
	{
		ClearScreen();
		SetRgb(COLOUR_WHITE_ON_BLACK);

		DrawGrid(5, 3, PlayerGrid, "PLAYER FLEET", true);
		DrawGrid(45, 3, AiGrid, "TARGET GRID", _bDebugMode);

		GotoXY(5, 15);
		SetRgb(COLOUR_CYAN_ON_BLACK);
		std::cout << "Player Ships Left: " << iPlayerHealth << " | AI Ships Left: " << iAiHealth;

		GotoXY(5, 16);
		SetRgb(COLOUR_WHITE_ON_BLACK);
		std::cout << "Status: " << sMessage;

		GotoXY(5, 18);
		SetRgb(COLOUR_CYAN_ON_BLACK);
		std::cout << "Enter target Row (0-9) and Col (0-9) separated by space (or -1 to quit): ";

		int iTargetRow = 0;
		int iTargetCol = 0;
		std::cin >> iTargetRow;

		if (iTargetRow == -1)
		{
			break;
		}

		std::cin >> iTargetCol;

		if (AiGrid.IsValidCoordinate(iTargetRow, iTargetCol))
		{
			ECellState eCurrentState = AiGrid.GetCellState(iTargetRow, iTargetCol);

			if (eCurrentState == STATE_SHIP)
			{
				AiGrid.SetCellState(iTargetRow, iTargetCol, STATE_HIT);
				sMessage = "Direct Hit on Enemy Ship!";
				iAiHealth--; // Reduce AI health
			}
			else if (eCurrentState == STATE_WATER)
			{
				AiGrid.SetCellState(iTargetRow, iTargetCol, STATE_MISS);
				sMessage = "Shot missed into open water.";
			}
			else
			{
				sMessage = "You already fired at this coordinate!";
			}

			// Check if Player Won
			if (iAiHealth <= 0)
			{
				sGameResult = "VICTORY! You destroyed the enemy fleet!";
				bGamePlaying = false;
				break;
			}

			// AI Counter-Attack Turn
			int iAiRow = rand() % GRID_SIZE;
			int iAiCol = rand() % GRID_SIZE;
			ECellState eAiTargetState = PlayerGrid.GetCellState(iAiRow, iAiCol);

			if (eAiTargetState == STATE_SHIP)
			{
				PlayerGrid.SetCellState(iAiRow, iAiCol, STATE_HIT);
				iPlayerHealth--; // Reduce Player health
			}
			else if (eAiTargetState == STATE_WATER)
			{
				PlayerGrid.SetCellState(iAiRow, iAiCol, STATE_MISS);
			}

			// Check if AI Won (Player Lost)
			if (iPlayerHealth <= 0)
			{
				sGameResult = "DEFEAT! Your fleet has been sunk!";
				bGamePlaying = false;
				break;
			}
		}
		else
		{
			sMessage = "Invalid coordinates! Choose between 0 and 9.";
		}
	}

	// End Game Screen
	ClearScreen();
	SetRgb((iAiHealth <= 0) ? COLOUR_GREEN_ON_BLACK : COLOUR_RED_ON_BLACK);
	std::cout << "\n========================================\n";
	std::cout << "            GAME OVER                   \n";
	std::cout << "========================================\n";
	std::cout << " " << sGameResult << "\n";
	std::cout << "========================================\n\n";

	SetRgb(COLOUR_WHITE_ON_BLACK);
	std::cout << "Type any character and press Enter to return to Main Menu: ";
	char cPause = ' ';
	std::cin >> cPause;
}

// TF: Pointer Initialised 
void ExecuteGameLoop()
{
	bool bIsRunning = true;
	bool bDebugMode = false;

	while (bIsRunning)
	{
		int iMenuChoice = 0;

		ClearScreen();
		DrawConsoleHeader(COLOUR_CYAN_ON_BLACK);

		std::cout << "\n";
		std::cout << "========================================\n";
		std::cout << "               MAIN MENU                \n";
		std::cout << "========================================\n";
		std::cout << " [1] Start New Game (Single Player vs AI)\n";
		std::cout << " [2] Toggle Debug Mode (" << (bDebugMode ? "ON" : "OFF") << ")\n";
		std::cout << " [3] Exit Game\n";
		std::cout << "========================================\n";
		std::cout << "Enter your choice (1-3): ";

		std::cin >> iMenuChoice;

		// TF: Conditional Statement
		if (iMenuChoice == 1)
		{
			RunGameSession(bDebugMode);
		}
		else if (iMenuChoice == 2)
		{
			bDebugMode = !bDebugMode;
		}
		else if (iMenuChoice == 3)
		{
			bIsRunning = false; // Exits the game loop
		}
		else
		{
			ClearScreen();
			SetRgb(COLOUR_RED_ON_BLACK);
			std::cout << "\nInvalid choice! Please select 1, 2, or 3.\n";
			std::cout << "Type any character and press Enter to continue: ";

			char cPause = ' ';
			std::cin >> cPause;
		}
	}

	ClearScreen();
	SetRgb(COLOUR_WHITE_ON_BLACK);
	std::cout << "Thanks for playing Battleship!\n";
}

// Win32 Console utilities Implementation
void SetRgb(EColour _eColour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (_eColour)
	{
	case COLOUR_WHITE_ON_BLACK:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case COLOUR_RED_ON_BLACK:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case COLOUR_GREEN_ON_BLACK:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case COLOUR_YELLOW_ON_BLACK:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case COLOUR_BLUE_ON_BLACK:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		break;
	case COLOUR_CYAN_ON_BLACK:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
}

void GotoXY(int _iX, int _iY)
{
	COORD point;
	point.X = static_cast<SHORT>(_iX);
	point.Y = static_cast<SHORT>(_iY);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void ClearScreen()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}