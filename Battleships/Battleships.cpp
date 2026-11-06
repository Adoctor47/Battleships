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