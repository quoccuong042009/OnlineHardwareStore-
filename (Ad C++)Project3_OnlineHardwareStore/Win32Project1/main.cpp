//-----------------------------------------------------------------------------------------
#include <afxwin.h>      //MFC core and standard components
#include "resource.h"    //main symbols
#include<iomanip>
#include "Function.h"

//-----------------------------------------------------------------------------------------
//Globals
//--- for list
CEdit * ECLlist;
CEdit * ECQuan;
CEdit * ECDes;
CEdit * ECPric;

//-- for Add to Cart
CListBox * LCACStockN;
CEdit * ECACPuchQu;
CEdit * ECACDescrip;
CEdit * ECACPriceEach;
CButton * BCACFini;
CButton * BCACAd;
CStatic *TCACAvaiQuan;


//-- for Remove to Cart
CListBox * LCRCStockN;
CEdit * ECRCPuchQu;
CEdit * ECRCDescrip;
CEdit * ECRCPriceEach;
CEdit * ECRCEx;
CButton * BCRCRem;
CButton * BCRCCan;


//-- for display Cart
CEdit* ECDCDispl;
CEdit* ECDCQuan;
CEdit* ECDCDes;
CEdit* ECDCPri;
CEdit* ECDCEx;
CEdit* ECDCtota;
CButton* BCDCDon;

//-- for Check Out Cart
CEdit* CODisplay;
CEdit* COQuan;
CEdit* COCDes;
CEdit* COCPri;
CEdit* COEx;

CEdit* COtotal;
CEdit* COTax;
CEdit* COShip;
CEdit* COOrTotal;

CEdit* COFirst;
CEdit* COLast;
CEdit* COAdres;
CEdit* COCity;
CEdit* COState;
CEdit* COZip;

CButton * COSubmit;
CButton * COcancel;

DoublyLinkedList inventorylist;
DoublyLinkedList purchasedList;

class STORE : public CDialog
{
public:
	STORE(CWnd* pParent = NULL) : CDialog(STORE::IDD, pParent)
	{    }
	// Dialog Data, name of dialog form
	enum{ IDD = STOREINTER};
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
		getList();
		ECLlist = (CEdit *)GetDlgItem(ECList);
		ECQuan = (CEdit *)GetDlgItem(ECQuantity);
		ECDes = (CEdit *)GetDlgItem(ECDescription);
		ECPric = (CEdit *)GetDlgItem(ECPrice);
		inventorylist.printInvenListOnCEdit(ECLlist, ECQuan, ECDes, ECPric);

		return true;
	}
public:
	void getList();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMnlist();
	afx_msg void OnMnadd();
	afx_msg void OnMncheckout();
	afx_msg void OnMndisplay();
	afx_msg void OnMnremove();
	afx_msg void OnMnquit();
};
void STORE::getList(){
	Info temp[] = { 
		  { "A100", 20, "Hammer", "9.95",9.95 }
		, { "A250", 25, "Saw", "13.95", 13.95}
		, { "B400", 50, "Flat-Head Nails", "11.99/Gross", 11.99 }
		, { "C888", 50, "Flat-Head Screwdriver", "6.59",6.59 }
		, { "A499", 75, "Pliers", "4.95",4.95 }
		, { "C667", 50, "Drill", "22.95",22.95 }
		, { "B875", 70, "Plumber's Wrench", "11.90" ,11.90}
		, { "D547", 60, "Ladder 10 foot", "70.44",70.44 }
		, { "A910", 85, "Flashflit 10 inch", "9.99" ,9.99}
		, { "B123", 90, "Assorted Buss Fuses", "4.99",4.99 }
	};

	for (int i = 0; i < 10; i++)
		inventorylist.insertFirst(temp[i]);
	
	inventorylist.quickSort();

}
//--------------------------------------------------------------------------------------
class ADD : public CDialog
{
public:
	ADD(CWnd* pParent = NULL) : CDialog(ADD::IDD2, pParent)
	{    }
	// Dialog Data, name of dialog form
	enum{ IDD2 = ADDTOCART };
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();

		LCACStockN = (CListBox *)GetDlgItem(LCACStockNum);
		ECACPuchQu = (CEdit *)GetDlgItem(EDACPuchQuan);
		ECACDescrip = (CEdit *)GetDlgItem(ECACDescription);
		ECACPriceEach = (CEdit *)GetDlgItem(ECACPPE);
		BCACFini = (CButton *)GetDlgItem(BCACFinish);
		BCACAd = (CButton *)GetDlgItem(BCACAdd);
		TCACAvaiQuan = (CStatic *)GetDlgItem(TCACAvailable);
		
		LCACStockN->AddString(L"A100");
		LCACStockN->AddString(L"A250");
		LCACStockN->AddString(L"A499");
		LCACStockN->AddString(L"A910");
		LCACStockN->AddString(L"B123");
		LCACStockN->AddString(L"B400");
		LCACStockN->AddString(L"B875");
		LCACStockN->AddString(L"C667");
		LCACStockN->AddString(L"C888");
		LCACStockN->AddString(L"D547");

		LCACStockN->SetCurSel(0);

		ECACDescrip->SetWindowTextW(L"Hammer");
		ECACPriceEach->SetWindowTextW(L"9.95");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(0));

		return true;
	}
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBcacadd();
	afx_msg void OnBcacfinish();
	afx_msg void OnLcacstocknum();
};
ADD addForm;
//-----------------------------------------------------------------------------------------
class REMOVEFROMCART : public CDialog
{
public:
	REMOVEFROMCART(CWnd* pParent = NULL) : CDialog(REMOVEFROMCART::IDD, pParent)
	{    }
	// Dialog Data, name of dialog form
	enum{ IDD = REMOVECART };
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
		
		LCRCStockN = (CListBox *)GetDlgItem(LCRCStockNum);
		ECRCPuchQu = (CEdit *)GetDlgItem(EDRCPuchQuan);
		ECRCDescrip = (CEdit *)GetDlgItem(ECRCDescription);
		ECRCPriceEach = (CEdit *)GetDlgItem(ECRCPPE);
		ECRCEx = (CEdit *)GetDlgItem(ECRCExtension);
		BCRCRem = (CButton *)GetDlgItem(BCRCREMOVE);
		BCRCCan = (CButton *)GetDlgItem(BCRCCANCEL);

		purchasedList.getListForRemoveForm(LCRCStockN);
		return true;
	}
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedBcrcremove();
	afx_msg void OnSelchangeLcrcstocknum();
	afx_msg void OnClickedBcrccancel();
};
//-----------------------------------------------------------------------------------------
class DISPLAY : public CDialog
{
public:
	DISPLAY(CWnd* pParent = NULL) : CDialog(DISPLAY::IDD, pParent)
	{    }
	// Dialog Data, name of dialog form
	enum{ IDD = DISPLAYCART };
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();

		ECDCDispl = (CEdit *)GetDlgItem(ECDCDisplay);
		ECDCQuan = (CEdit *)GetDlgItem(ECDCQuantity);
		ECDCDes = (CEdit *)GetDlgItem(ECDCDescription);
		ECDCPri = (CEdit *)GetDlgItem(ECDCPrice);
		ECDCEx = (CEdit *)GetDlgItem(ECDCExtension);

		ECDCtota = (CEdit *)GetDlgItem(ECDCTotal);
		BCDCDon = (CButton *)GetDlgItem(BCDCDone);

		displayContent();

		return true;
	}
public:
	void displayContent();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedBcdcdone();
};
DISPLAY displayForm;

void DISPLAY::displayContent(){
	purchasedList.printPurListOnCEdit(ECDCDispl, ECDCQuan, ECDCDes, ECDCPri, ECDCEx);
	purchasedList.printTotal(ECDCtota);

}

//-----------------------------------------------------------------------------------------
class CHECKOUTCART : public CDialog
{
public:
	CHECKOUTCART(CWnd* pParent = NULL) : CDialog(CHECKOUTCART::IDD, pParent)
	{    }
	// Dialog Data, name of dialog form
	enum{ IDD = CHECKOUT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();

		CODisplay = (CEdit *)GetDlgItem(ECCODisplay);
		COQuan = (CEdit *)GetDlgItem(ECCOQuantity);
		COCDes = (CEdit *)GetDlgItem(ECCODescription);
		COCPri = (CEdit *)GetDlgItem(ECCOPrice);
		COEx = (CEdit *)GetDlgItem(ECCOExtension);

		COtotal = (CEdit *)GetDlgItem(ECCOTotal);
		COTax = (CEdit *)GetDlgItem(ECCOTaxed);
		COShip = (CEdit *)GetDlgItem(ECCOShip);
		COOrTotal = (CEdit *)GetDlgItem(ECCOOrderTotal);

		COFirst = (CEdit *)GetDlgItem(ECDCFName);
		COLast = (CEdit *)GetDlgItem(ECDCLName);
		COAdres = (CEdit *)GetDlgItem(ECDCAddress);
		COCity = (CEdit *)GetDlgItem(ECCOCity);
		COState = (CEdit *)GetDlgItem(ECCOState);
		COZip = (CEdit *)GetDlgItem(ECCOZip);

		COSubmit = (CButton *)GetDlgItem(BCCKCheckOut);
		COcancel = (CButton *)GetDlgItem(BCCOCancel);

		displayContenForCheckOut();

		return true;
	}
public:
	void ExitMFCApp();
	void displayContenForCheckOut();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBcckcheckout();
	afx_msg void OnBccocancel();
};
CHECKOUTCART checkOutForm;

void CHECKOUTCART::displayContenForCheckOut(){
	purchasedList.printPurListOnCEdit(CODisplay, COQuan, COCDes, COCPri, COEx);
	purchasedList.printTotal(COtotal);
	
	CString TaxCstring, OrTotalCstring;
	double taxes, orTotal;

	taxes = purchasedList.getTotal() * TAXES;
	orTotal = taxes + purchasedList.getTotal() + 9.95;

	TaxCstring.Format(_T("$%.2f"), taxes);
	OrTotalCstring.Format(_T("$%.2f"), orTotal);

	COTax->SetWindowTextW(TaxCstring);
	COShip->SetWindowTextW(L"$9.95");
	COOrTotal->SetWindowTextW(OrTotalCstring);

}

void CHECKOUTCART::ExitMFCApp()
{
	// same as double-clicking on main window close box
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
//-----------------------------------------------------------------------------------------
class STOREAPP : public CWinApp
{
public:
	STOREAPP() {  }
public:
	virtual BOOL InitInstance()
	{
		CWinApp::InitInstance();
		STORE dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		return FALSE;
	} //close function
};
//-----------------------------------------------------------------------------------------
//Need a Message Map Macro for both CDialog and CWinApp
BEGIN_MESSAGE_MAP(STORE, CDialog)
	ON_COMMAND(MNLIST, &STORE::OnMnlist)
	ON_COMMAND(MNADD, &STORE::OnMnadd)
	ON_COMMAND(MNCHECKOUT, &STORE::OnMncheckout)
	ON_COMMAND(MNDISPLAY, &STORE::OnMndisplay)
	ON_COMMAND(MNREMOVE, &STORE::OnMnremove)
	ON_COMMAND(MNQUIT, &STORE::OnMnquit)
END_MESSAGE_MAP()
//-----------------------------------------------------------------------------------------
STOREAPP theApp;  //Starts the Application



void STORE::OnMnlist()
{
	inventorylist.printInvenListOnCEdit(ECLlist, ECQuan, ECDes, ECPric);
}


void STORE::OnMnadd()
{
	addForm.DoModal();
}


void STORE::OnMncheckout()
{
	checkOutForm.DoModal();
}


void STORE::OnMndisplay()
{
	displayForm.DoModal();
}

REMOVEFROMCART removeForm;
void STORE::OnMnremove()
{
	removeForm.DoModal();
}


void STORE::OnMnquit()
{
	int result = MessageBox(_T("Are You Sure?"), _T("Exiting"),MB_ICONERROR | MB_YESNO);

	if (result == IDYES){
		Beep(1000, 100);
		DestroyWindow();
	}
	else
		Beep(200, 100);
}
BEGIN_MESSAGE_MAP(ADD, CDialog)
	ON_COMMAND(BCACAdd, &ADD::OnBcacadd)
	ON_COMMAND(BCACFinish, &ADD::OnBcacfinish)
	ON_CBN_SELCHANGE(LCACStockNum, &ADD::OnLcacstocknum)
END_MESSAGE_MAP()


void ADD::OnBcacadd()
{
	int itemSeclected;
	CString purQuantity;
	int purQuantityInt;
	int availableQuan;

	ECACPuchQu->GetWindowTextW(purQuantity);
	if (purQuantity.SpanIncluding(L"0123456789") == purQuantity){
		itemSeclected = LCACStockN->GetCurSel();

		purQuantityInt = _ttoi(purQuantity);

		availableQuan = _ttoi(inventorylist.AvalableQuantity(itemSeclected));

		if (purQuantityInt == 0)
			MessageBox(_T("Purchased Quantity have to be bigger than zero"), _T("WARNING"), MB_ICONEXCLAMATION | MB_OK);
		else{
			if (availableQuan >= purQuantityInt){
				inventorylist.AddPurchaseList(purchasedList, purQuantityInt, itemSeclected);
				MessageBox(_T("Item has been added to Cart"), _T("Status"), MB_OK);
				TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(itemSeclected));
			}
			else if (availableQuan == 0)
				MessageBox(_T("OUT OF STOCK - ITEM IS BACKORDERED"), _T("WARNING"), MB_ICONEXCLAMATION | MB_OK);
			else if (availableQuan != 0)
				MessageBox(_T("EXCEED AVAILABLE QUANTITY"), _T("WARNING"), MB_ICONEXCLAMATION | MB_OK);
		}

		inventorylist.printInvenListOnCEdit(ECLlist, ECQuan, ECDes, ECPric);
	}
	else
		MessageBox(_T("Purchased Quantity must be an integer"), _T("Error"), MB_ICONERROR | MB_OK);
	
	

}


void ADD::OnBcacfinish()
{
	int result = MessageBox(_T("Are You Sure?"), _T("Exiting"), MB_ICONERROR | MB_YESNO);

	if (result == IDYES){
		Beep(1000, 100);
		addForm.OnOK();
	}
	else
		Beep(200, 100);
}


void ADD::OnLcacstocknum()
{
	switch (LCACStockN->GetCurSel())
	{
	case 0:
		ECACDescrip->SetWindowTextW(L"Hammer");
		ECACPriceEach->SetWindowTextW(L"9.95");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(0));
		break;
	case 1:
		ECACDescrip->SetWindowTextW(L"Saw");
		ECACPriceEach->SetWindowTextW(L"13.95");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(1));
		break;
	case 2:
		ECACDescrip->SetWindowTextW(L"Pliers");
		ECACPriceEach->SetWindowTextW(L"4.95");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(2));
		break;
	case 3:
		ECACDescrip->SetWindowTextW(L"Flashlight 10 inch");
		ECACPriceEach->SetWindowTextW(L"9.99");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(3));
		break;
	case 4:
		ECACDescrip->SetWindowTextW(L"Assorted Buss Fuses");
		ECACPriceEach->SetWindowTextW(L"4.99");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(4));
		break;
	case 5:
		ECACDescrip->SetWindowText(L"Flat - Head Nails"); 
		ECACPriceEach->SetWindowText(L"11.90/Gross");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(5));
		break;
	case 6:
		ECACDescrip->SetWindowTextW(L"Plumber's Wrench");
		ECACPriceEach->SetWindowTextW(L"11.99");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(6));
		break;
	case 7:
		ECACDescrip->SetWindowTextW(L"Drill");
		ECACPriceEach->SetWindowTextW(L"22.95");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(7));
		break;
	case 8:
		ECACDescrip->SetWindowTextW(L"Flat-Head Screwdriver");
		ECACPriceEach->SetWindowTextW(L"6.59");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(8));
		break;
	case 9:
		ECACDescrip->SetWindowTextW(L"Ladder 10 foot");
		ECACPriceEach->SetWindowTextW(L"70.44");
		TCACAvaiQuan->SetWindowTextW(inventorylist.AvalableQuantity(9));
		break;
	}
}
BEGIN_MESSAGE_MAP(REMOVEFROMCART, CDialog)
	ON_BN_CLICKED(BCRCREMOVE, &REMOVEFROMCART::OnClickedBcrcremove)
	ON_LBN_SELCHANGE(LCRCStockNum, &REMOVEFROMCART::OnSelchangeLcrcstocknum)
	ON_BN_CLICKED(BCRCCANCEL, &REMOVEFROMCART::OnClickedBcrccancel)
END_MESSAGE_MAP()

void REMOVEFROMCART::OnSelchangeLcrcstocknum()
{
	purchasedList.onChangeRemoveForm(LCRCStockN->GetCurSel(), ECRCPuchQu, ECRCDescrip, ECRCPriceEach, ECRCEx);
}


void REMOVEFROMCART::OnClickedBcrccancel()
{
	int result = MessageBox(_T("Are You Sure?"), _T("Exiting"), MB_ICONERROR | MB_YESNO);

	if (result == IDYES){
		Beep(1000, 100);
		removeForm.OnOK();
	}
	else
		Beep(200, 100);
}

void REMOVEFROMCART::OnClickedBcrcremove(){
	if (purchasedList.onRemoveButton(inventorylist, LCRCStockN->GetCurSel())){
		MessageBox(_T("Item have been removed from cart"), _T("Removal Status"), MB_OK);


		ECRCPuchQu->SetWindowTextW(L"");
		ECRCDescrip->SetWindowTextW(L"");
		ECRCPriceEach->SetWindowTextW(L"");
		ECRCEx->SetWindowTextW(L"");

		inventorylist.printInvenListOnCEdit(ECLlist, ECQuan, ECDes, ECPric);
		LCRCStockN->ResetContent();
		purchasedList.getListForRemoveForm(LCRCStockN);
		
	}
	else
		MessageBox(_T("ERROR: Item Can't Be Removed"), _T("Removal Status"), MB_OK);
}


BEGIN_MESSAGE_MAP(DISPLAY, CDialog)
	ON_BN_CLICKED(BCDCDone, &DISPLAY::OnClickedBcdcdone)
END_MESSAGE_MAP()


void DISPLAY::OnClickedBcdcdone()
{
	int result = MessageBox(_T("Are You Sure?"), _T("Exiting"), MB_ICONERROR | MB_YESNO);

	if (result == IDYES){
		Beep(1000, 100);
		displayForm.OnOK();
	}
	else
		Beep(200, 100);
}


BEGIN_MESSAGE_MAP(CHECKOUTCART, CDialog)
	ON_COMMAND(BCCKCheckOut, &CHECKOUTCART::OnBcckcheckout)
	ON_COMMAND(BCCOCancel, &CHECKOUTCART::OnBccocancel)
END_MESSAGE_MAP()


void CHECKOUTCART::OnBcckcheckout()
{
	if (!purchasedList.isEmpty()){
		CString test1, test2, test3, test4, test5, test6;

		COFirst->GetWindowTextW(test1);
		COLast->GetWindowTextW(test2);
		COAdres->GetWindowTextW(test3);
		COCity->GetWindowTextW(test4);
		COState->GetWindowTextW(test5);
		COZip->GetWindowTextW(test6);

		if (test1.IsEmpty() || test2.IsEmpty() || test3.IsEmpty() || test4.IsEmpty() || test5.IsEmpty() || test6.IsEmpty())
			int result = MessageBox(_T("Please fill out all the form"), _T("ERROR"), MB_OK);
		else{
			int result = MessageBox(_T("Thank you. Your order will be shipped soon"), _T("Order Submitted"), MB_OK);
			checkOutForm.OnOK();
			checkOutForm.SendMessage(WM_CLOSE);
			ExitMFCApp();
		}
	}
	else{
		int result = MessageBox(_T("There are no items in cart."), _T("Warning"), MB_OK);
		checkOutForm.OnOK();
	}
}


void CHECKOUTCART::OnBccocancel()
{
	int result = MessageBox(_T("Are You Sure?"), _T("Exiting"), MB_ICONERROR | MB_YESNO);

	if (result == IDYES){
		Beep(1000, 100);
		checkOutForm.OnOK();
	}
	else
		Beep(200, 100);
}
