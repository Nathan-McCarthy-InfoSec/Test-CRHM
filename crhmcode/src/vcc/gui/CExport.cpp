#include "CExport.h"

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
	DDX_Control(pDX, ID_EXPORT_CHOICES_LIST_BOX, choicesListBox);
	DDX_Control(pDX, ID_EXPORT_SELECTED_LIST_BOX, selectedListBox);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_MORE, previewMoreButton);
	DDX_Control(pDX, ID_EXPORT_FORMAT_BTN, formatToggle);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_EDIT_BOX, previewEditBox);
}


BEGIN_MESSAGE_MAP(CExport, CDialog)
	ON_LBN_SELCHANGE(ID_EXPORT_CHOICES_LIST_BOX, &CExport::OnChoicesSelectionChange)
	ON_LBN_SELCHANGE(ID_EXPORT_SELECTED_LIST_BOX, &CExport::OnSelectedSelectionChange)
	ON_BN_CLICKED(ID_EXPORT_PREVIEW_MORE, &CExport::OnPreviewMorePressed)
END_MESSAGE_MAP()


BOOL CExport::OnInitDialog()
{
	CDialog::OnInitDialog();

	choicesListBox.ResetContent();
	selectedListBox.ResetContent();

	CRHMmain* model = CRHMmain::getInstance();
	
	for (int i = 0; i < model->SeriesCnt; i++)
	{
		std::string varName = model->cdSeries[i]->Title;
		choicesListBox.AddString(CString(varName.c_str()));
	}

	return true;
}

void CExport::OnChoicesSelectionChange()
{
	int selectedCount = choicesListBox.GetSelCount();
	int * selectedIndicies = new int[selectedCount];
	choicesListBox.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		choicesListBox.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		int found = selectedListBox.FindString(-1, selectedText);
		if (found == LB_ERR)
		{
			selectedListBox.AddString(selectedText);
		}

	}

	delete[] selectedIndicies;
}

void CExport::OnSelectedSelectionChange()
{
	int selectedCount = selectedListBox.GetSelCount();
	int* selectedIndicies = new int[selectedCount];
	selectedListBox.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		selectedListBox.DeleteString(selectedIndicies[i]);
	}

	delete[] selectedIndicies;
}

void CExport::OnPreviewMorePressed()
{

	previewEditBox.ResetContent();

	CRHMmain* model = CRHMmain::getInstance();

	previewEditBox.AddString(L"Future File Description");

	std::string Sx;
	std::string Sy;

	std::vector<int> * exportIndex = getExportIndex();

	for (size_t i = 0; i < exportIndex->size(); i++)
	{
		ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
		Sx = model->cdSeries[exportIndex->at(i)]->Title;
		Sx += std::string(" 1 ");
		Sx += thisVar->units;
		previewEditBox.AddString(CString(Sx.c_str()));
	}

	Sx = "###### time";
	for (size_t i = 0; i < exportIndex->size(); i++)
	{
		std::string S = model->cdSeries[exportIndex->at(i)]->Title;
		Sx.append("\t");
		Sx.append(S);
	}

	previewEditBox.AddString(CString(Sx.c_str()));

	//Output the rest of the info
	for (long index = Global::DTmin + this->nextLine; (index < Global::DTmin + this->nextLine + 1000) && (index < Global::DTmax); index++)
	{
		std::string Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
		Sx = StandardConverterUtility::GetDateTimeInStringForOutput(model->cdSeries[0]->XValue(index));

		Sx = FloatToStrF(model->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);

		for (size_t i = 0; i < exportIndex->size(); i++)
		{
			// has to equal first series length
			if (model->cdSeries[0]->Count() == model->cdSeries[exportIndex->at(i)]->Count())
			{
				ClassVar* thisVar = model->cdSeries[exportIndex->at(i)]->Tag;
				int prec = 7;
				//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.

				if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
				{
					prec = 7;
				}

				std::string Sy = FloatToStrF(model->cdSeries[exportIndex->at(i)]->YValue(index), TFloatFormat::ffGeneral, prec, 10);
				Sx = Sx + "\t" + Sy;
			}
		}

		previewEditBox.AddString(CString(Sx.c_str()));
	}

	this->nextLine += 1000;
	if (this->nextLine > Global::DTmax)
	{
		this->nextLine = 0;
	}
}

std::vector<int> * CExport::getExportIndex()
{
	std::vector<int> * index = new std::vector<int>();
	CRHMmain* model = CRHMmain::getInstance();
	CString text;
	std::string name;

	int selectedCount = this->selectedListBox.GetCount();

	for (int i = 0; i < selectedCount; i++)
	{
		this->selectedListBox.GetText(i, text);
		CT2CA pszConvertedAnsiString(text); 
		name.assign(pszConvertedAnsiString);

		for (int j = 0; j < model->SeriesCnt; j++)
		{
			if (model->cdSeries[j]->Title == name)
			{
				index->push_back(j);
				break;
			}
		}
	}

	return index;

}