// CExport.cpp : implementation file
//

#include "stdafx.h"
#include "CRHM_GUI.h"
#include "CExport.h"
#include "afxdialogex.h"


// CExport dialog

IMPLEMENT_DYNAMIC(CExport, CDialog)

CExport::CExport(CWnd* pParent /*=nullptr*/)
	: CDialog(EXPORT_DLG, pParent)
{

}

CExport::~CExport()
{
}

void CExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExport, CDialog)
END_MESSAGE_MAP()


// CExport message handlers
