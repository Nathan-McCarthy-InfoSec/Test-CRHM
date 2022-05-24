#pragma once
#include <afxwin.h>
#include "../../src/core/ClassPar.h"

class GridCell :
    public CEdit
{
public:
    GridCell(ClassPar* par, int row, int col);

    DECLARE_MESSAGE_MAP()

private:

    COLORREF black;

    COLORREF white;

    COLORREF yellow;

    CBrush background_brush_white;

    CBrush background_brush_yellow;

    ClassPar * param;

    int row;

    int col;

    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

    bool valueChanged();
};

