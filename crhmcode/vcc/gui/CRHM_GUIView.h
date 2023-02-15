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
#pragma once

#include <string>
#include <list>
#include <ctime>
#include <atltime.h>

#include "CRHM_GUIDoc.h"
#include "COptions.h"
#include "CReport.h"
#include "ExportDlg.h"
#include "ConstructDlg.h"
#include "ParametersDlg.h"
#include "COptions.h"
#include "../../src/core/GlobalDll.h"


class CCRHMGUIView : public CView
{
protected: // create from serialization only
	CCRHMGUIView();
	DECLARE_DYNCREATE(CCRHMGUIView)

// Attributes
public:
	CCRHMGUIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCRHMGUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDialogShow();
	afx_msg void OnExport();
	afx_msg void OpenParametersDialog();
	afx_msg void OnBuildConstruct();
	afx_msg void OnFileSaveAs();

	
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // debug version in CRHM_GUIView.cpp
inline CCRHMGUIDoc* CCRHMGUIView::GetDocument() const
   { return reinterpret_cast<CCRHMGUIDoc*>(m_pDocument); }
#endif

