/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#include "ParamDlgCardShared.h"

ParamDlgCardShared::ParamDlgCardShared(ClassPar* param, FontsContainer * fonts, CWnd* pParent)
	: ParamDlgCard(param, fonts, pParent)
{
}


bool ParamDlgCardShared::call_create(CWnd* pParent)
{
	return Create(ParamDlgCardShared::IDD, pParent);
}


BEGIN_MESSAGE_MAP(ParamDlgCardShared, ParamDlgCard)
	ON_BN_CLICKED(ID_PARAM_MAKE_LOCAL, &ParamDlgCardShared::OnMakeLocal)
END_MESSAGE_MAP()


void ParamDlgCardShared::OnMakeLocal()
{
	GetParent()->PostMessage(UWM_MAKE_LOCAL, (WPARAM)this->parameter, (LPARAM)this->parameter);
}


bool ParamDlgCardShared::RenderGrid()
{

	CWaitCursor wait;

	// Place the first col guide CEdit in the vector
	this->colHeaders.push_back((CEdit*)GetDlgItem(ID_PARAM_COL));

	// Place the first row guide CEdit in the vector
	this->rowLabels.push_back((CEdit*)GetDlgItem(ID_PARAM_ROW));

	/*
	* Set the text for the grid guide items.
	*/
	std::string gridRowLabel = this->parameter->param + "[1]";
	CString gridRowLabelText = CString(gridRowLabel.c_str());
	SetDlgItemText(ID_PARAM_ROW, gridRowLabelText);

	std::string gridColLabel = "HRU[1]";
	CString gridColLabelText = CString(gridColLabel.c_str());
	SetDlgItemText(ID_PARAM_COL, gridColLabelText);

	// Create the column header cells
	int numCol = (int)this->parameter->dim;
	for (int i = 1; i < numCol; i++)
	{
		// Determine the location for the cell
		CRect columnRectangle;
		GetDlgItem(ID_PARAM_COL + i - 1)->GetWindowRect(&columnRectangle);
		ScreenToClient(&columnRectangle);
		int width = columnRectangle.Width();
		columnRectangle.TopLeft().x = columnRectangle.TopLeft().x + width;
		columnRectangle.BottomRight().x = columnRectangle.BottomRight().x + width;

		// Create a CEdit for the cell
		CEdit* colHeader = new CEdit();
		DWORD dwStyle = ES_CENTER | ES_READONLY | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP;
		bool creationSuccess = colHeader->Create(
			dwStyle,
			columnRectangle,
			this,
			ID_PARAM_COL + i
		);

		if (!creationSuccess)
		{
			delete colHeader;
			return false;
		}

		// Set the font and text for the cell
		GetDlgItem(ID_PARAM_COL + i)->SetFont(this->pointFont100);
		std::string colString = "HRU[" + std::to_string(i + 1) + "]";
		CString colText = CString(colString.c_str());
		SetDlgItemText(ID_PARAM_COL + i, colText);

		// Place the CEdit into the vector
		this->colHeaders.push_back(colHeader);
	}

	// Create the row label cells
	int numRow = (int)this->parameter->lay;
	for (int i = 1; i < numRow; i++)
	{
		// Determine the location for the cell
		CRect rowRectangle;
		GetDlgItem(ID_PARAM_ROW + i - 1)->GetWindowRect(&rowRectangle);
		ScreenToClient(&rowRectangle);
		int height = rowRectangle.Height();
		rowRectangle.TopLeft().y = rowRectangle.TopLeft().y + height;
		rowRectangle.BottomRight().y = rowRectangle.BottomRight().y + height;

		// Create a CEdit for the cell
		CEdit* rowHeader = new CEdit();
		DWORD dwStyle = ES_READONLY | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP;
		bool creationSuccess = rowHeader->Create(
			dwStyle,
			rowRectangle,
			this,
			ID_PARAM_ROW + i
		);

		if (!creationSuccess)
		{
			delete rowHeader;
			return false;
		}

		// Set the font and text for the cell
		GetDlgItem(ID_PARAM_ROW + i)->SetFont(this->pointFont80);
		std::string rowString = this->parameter->param + "[" + std::to_string(i + 1) + "]";
		CString rowText = CString(rowString.c_str());
		SetDlgItemText(ID_PARAM_ROW + i, rowText);

		// Place the CEdit into the vector
		this->rowLabels.push_back(rowHeader);
	}

	// Initalize space for the valueGrid of CEdit cells
	this->valueGrid.resize(numRow);

	// Create the value grid
	for (int i = 0; i < numRow; i++)
	{
		// Find the Y coordinates for the new cell
		CRect rowGuideRect;
		GetDlgItem(ID_PARAM_ROW + i)->GetWindowRect(&rowGuideRect);
		ScreenToClient(&rowGuideRect);
		int topY = rowGuideRect.TopLeft().y;
		int botY = rowGuideRect.BottomRight().y;

		for (int j = 0; j < numCol; j++)
		{
			// Find the X coordinates for the new cell
			CRect colGuideRect;
			GetDlgItem(ID_PARAM_COL + j)->GetWindowRect(&colGuideRect);
			ScreenToClient(&colGuideRect);
			int topX = colGuideRect.TopLeft().x;
			int botX = colGuideRect.BottomRight().x;

			// Set the positon of the rectangle for the new cell
			CRect newCellRect;
			newCellRect.TopLeft().x = topX;
			newCellRect.TopLeft().y = topY;
			newCellRect.BottomRight().x = botX;
			newCellRect.BottomRight().y = botY;

			// Set the styles for the new cell
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_RIGHT | ES_READONLY;
			if (this->parameter->varType == TVar::Int)
			{
				// If it is a numberic cell add the ES_NUMBER style to prevent non numeric characters
				dwStyle = dwStyle | ES_NUMBER;
			}

			// Create a CEdit for the cell
			CEdit* newCell = new CEdit();
			bool creationSuccess = newCell->Create(
				dwStyle,
				newCellRect,
				this,
				ID_PARAM_GRID + (i * 1000) + j
			);

			if (!creationSuccess)
			{
				delete newCell;
				return false;
			}

			// Set the font for the cell
			GetDlgItem(ID_PARAM_GRID + (i * 1000) + j)->SetFont(this->pointFont80);

			// Set the inital value in the cell
			std::stringstream valueStream;
			std::string valueString;
			if (this->parameter->varType == TVar::Float)
			{
				valueStream << this->parameter->layvalues[i][j];
				valueStream >> valueString;
			}
			else if (this->parameter->varType == TVar::Int)
			{
				valueStream << this->parameter->ilayvalues[i][j];
				valueStream >> valueString;
			}
			else if (this->parameter->varType == TVar::Txt)
			{
				if ((int)this->parameter->Strings->size() > j)
				{
					valueStream << this->parameter->Strings->at(j);
					valueStream >> valueString;
				}
				else
				{
					valueString = "";
				}
			}

			CString valueText = CString(valueString.c_str());
			SetDlgItemText(ID_PARAM_GRID + (i * 1000) + j, valueText);

			// Place the CEdit into the value grid to be tracked
			this->valueGrid[i].push_back(newCell);
		}

	}

	return true;

}