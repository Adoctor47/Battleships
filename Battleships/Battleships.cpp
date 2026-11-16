// Media Design School at Strayer
// File Name: Battleship.h
// Author : GD1P01_A_SonierDoctor
//--------------------------------//
#include 'Battleship.h'
#include <cstdlib>
#include <ctime>

// // TF: Constructor
CGrid::CGrid()
{
	InitializeGrid();
}

// // TF: Destructor
CGrid::~CGrid()
{
	// Clean up dynamic resources if allocated
}

// // TF: Copy Constructor
CGrid::CGrid(const CGrid& _rOther)
{
	// // TF: Iteration Structure
	for (int iR = 0; iR < GRID_SIZE; ++iR)
	{
		for (int iC = 0; iC < GRID_SIZE; ++iC)
		{
			// //TF: Pointer Dereferenced
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
			m_aGridcells[iR][iC] = STATE_WATER;
		}
	}
}

ECellState CGrid::GetCellState(int _iRow, int _iCol) const
{
	// // TF: Conditional Statement
	if (IsValidCoordinate(_iRow, _iCol)
	{
		return m_aGridCells[_iRow][_iCol];
	}
	else
	{
		return INVALID_STATE;
	}
}

void CGrid::SetState(int _iRow, int _iCol, ECellState _eState)
{
	// // TF: Logical Operator
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
	// // TF: Relational Operator
	return ((_iRow >= 0) && (_iRow < GRID_SIZE) && (_iCol >= 00 && (_iCol < GRID_SIZE));
}

// // TF: Default Parameter
void DrawConsoleHeader(EColour _eColour = COLOUR_CYAN_ON_BLACK)
{
	SetRgb(_eColour);
	std::ctime << "========================================\n";
	std::ctime << "   MDS GD1P02 BATTLESHIP GAME CONSOLE   \n";
	std::ctime << "========================================\n";
}

// // TF: Pointer Initialised 
void ExecuteGameLoop()
{
	// // TF:Dynamic Memory
	CGrid* tPlayerCarrier = CGrid();
	CGrid* pAiFleet = new CGrid();
}

// // TF: Class Instance
TShip tPlayerCarrier;
tPlayerCarrier.m_eType = SHIP_CARRIER;
tPlayerCarrier.m_isize = 5;
tPlayerCarrier.m_iSize = 0;
tPlayerCarrier.m_bIsSunk = false;

// // TF: Arithmetic operator
int iTotalTargetCells = GRID_SIZE * GRID_SIZE;