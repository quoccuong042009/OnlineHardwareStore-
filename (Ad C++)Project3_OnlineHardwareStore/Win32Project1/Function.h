#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

const double TAXES = 0.0625;
 
struct StockAndQuan{
	string stock;
	int quan;
};

struct boolForupdate{
	bool isAlreadyHad;
	int quantityInPurList;
};
struct Info{
	string stockNumber;
	int quantity;
	string description;
	string pricePerEach;
	double realPrice;
	double extension;
};

class Link{
public:
	Info data;
	Link* pNext;
	Link* pPrevious;
public:
	Link(){
		Link(NULL, 0, NULL, NULL, 0,0);
	}
	Link(Info i){
		data.stockNumber = i.stockNumber;
		data.quantity = i.quantity;
		data.description = i.description;
		data.pricePerEach = i.pricePerEach;
		data.realPrice = i.realPrice;
		data.extension = i.extension;
		pNext = NULL;
		pPrevious = NULL;
	}
	Link(string sNum, int q, string des, string pPE, double realP,double e){
		data.stockNumber = sNum;
		data.quantity = q;
		data.description = des;
		data.pricePerEach = pPE;
		data.realPrice = realP;
		data.extension = e;
		pNext = NULL;
		pPrevious = NULL;
	}


};

class DoublyLinkedList{
private:
	Link* pFirst;
	Link* pLast;
public:
	DoublyLinkedList() : pFirst(NULL), pLast(NULL){}
	//======================================================================
	~DoublyLinkedList(){
		Link* pCurrent = pFirst;
		while (pCurrent != NULL){
			Link* pOldCur = pCurrent;
			pCurrent = pCurrent->pNext;
			delete pOldCur;
		}
	}
	//======================================================================
	bool isEmpty(){
		return pFirst == NULL;
	}
	//======================================================================
	bool removeKeyByIndex(int index){
		int i = 0;
		Link* pCurrent;
		Link* pPrevious = NULL;

		if (index == 0){
			pCurrent = pFirst->pNext;
			delete pFirst;
			pFirst = pCurrent;
			return true;
		}
		else{
			pCurrent = pFirst;
			while (pCurrent != NULL && index != i){
				pPrevious = pCurrent;
				pCurrent = pCurrent->pNext;
				i++;
			}
			if (pCurrent){
				pPrevious->pNext = pCurrent->pNext;
				delete pCurrent;
				return true;
			}
			else
				return false;
		}
		return false;
	}
	//======================================================================
	int getIndexByStockNum(string n){
		Link* temp = pFirst;
		int i = 0; 

		while (temp != NULL){
			if (n == temp->data.stockNumber){
				return i;
			}
			i++;
			temp = temp->pNext;
		}
	}
	//======================================================================
	StockAndQuan getStockNumberAndQuantityByIndex(int index){
		Link* temp = pFirst;
		int i = 0;
		StockAndQuan k;

		while (temp != NULL){
			if (i++ == index){
				k.stock = temp->data.stockNumber;
				k.quan = temp->data.quantity;

				return k;
			}

			temp = temp->pNext;
		}
	}
	//======================================================================
	void insertFirst(Info in){
		Link* pNewLink = new Link(in);

		if (isEmpty())
			pLast = pNewLink;
		else
			pFirst->pPrevious = pNewLink;
		pNewLink->pNext = pFirst;
		pFirst = pNewLink;
	}
	//======================================================================
	void swap(Info* a, Info* b)
	{
		Info t = *a;      *a = *b;       *b = t;
	}

	//======================================================================
	Link *lastNode(Link *root)
	{
		while (root && root->pNext)
			root = root->pNext;
		return root;
	}
	//======================================================================
	Link* partition(Link *l, Link *h)
	{
		// set pivot as h element
		string x = h->data.stockNumber;

		// similar to i = l-1 for array implementation
		Link *i = l->pPrevious;

		// Similar to "for (int j = l; j <= h- 1; j++)"
		for (Link *j = l; j != h; j = j->pNext)
		{
			if (j->data.stockNumber <= x)
			{
				// Similar to i++ for array
				i = (i == NULL) ? l : i->pNext;

				swap(&(i->data), &(j->data));
			}
		}
		i = (i == NULL) ? l : i->pNext; // Similar to i++
		swap(&(i->data), &(h->data));

		return i;
	}
	//======================================================================
	void _quickSort(Link* l, Link *h)
	{
		if (h != NULL && l != h && l != h->pNext)
		{
			Link *p = partition(l, h);
			_quickSort(l, p->pPrevious);
			_quickSort(p->pNext, h);
		}
	}
	//======================================================================
	void quickSort()
	{
		// Find last node
		Link *h = lastNode(pFirst);

		// Call the recursive QuickSort
		_quickSort(pFirst, h);
	}
	//=====================================================================
	boolForupdate alreadyHave(DoublyLinkedList &purList, string stockNum){
		boolForupdate inPurList;

		Link* temp2 = purList.pFirst;

		while (temp2 != NULL){
			if (temp2->data.stockNumber == stockNum){
				inPurList.isAlreadyHad = true;
				inPurList.quantityInPurList = temp2->data.quantity;
				return inPurList;
			}

			temp2 = temp2->pNext;
		}

		inPurList.isAlreadyHad = false;
		inPurList.quantityInPurList = 0;

		return inPurList;
	}
	//=====================================================================
	void printInvenListOnCEdit(CEdit *L, CEdit *Q, CEdit *D, CEdit *P){
		Link * temp = pFirst;
		L->SetWindowTextW(L"");
		Q->SetWindowTextW(L"");
		D->SetWindowTextW(L"");
		P->SetWindowTextW(L"");

		while (temp != NULL){
			stringstream formatted1;
			stringstream formatted2;
			stringstream formatted3;
			stringstream formatted4;


			formatted1 << temp->data.stockNumber << endl;
			formatted2 << temp->data.quantity << endl;
			formatted3 << temp->data.description << endl;
			formatted4 << temp->data.pricePerEach << endl;
				

			CString str1 = formatted1.str().c_str();
			CString str2 = formatted2.str().c_str();
			CString str3 = formatted3.str().c_str();
			CString str4 = formatted4.str().c_str();

			LPCWSTR item1 = static_cast<LPCWSTR>(str1);
			LPCWSTR item2 = static_cast<LPCWSTR>(str2);
			LPCWSTR item3 = static_cast<LPCWSTR>(str3);
			LPCWSTR item4 = static_cast<LPCWSTR>(str4);

			temp = temp->pNext;

			int len1 = L->GetWindowTextLength();
			L->SetSel(len1, len1);
			L->ReplaceSel(item1);

			int len2 = Q->GetWindowTextLength();
			Q->SetSel(len2, len2);
			Q->ReplaceSel(item2);

			int len3 = D->GetWindowTextLength();
			D->SetSel(len3, len3);
			D->ReplaceSel(item3);

			int len4 = P->GetWindowTextLength();
			P->SetSel(len4, len4);
			P->ReplaceSel(item4);

		}
	}
	//=====================================================================
	void printPurListOnCEdit(CEdit *L, CEdit *Q, CEdit *D, CEdit *P, CEdit *E){
		Link * temp = pFirst;
		L->SetWindowTextW(L"");
		Q->SetWindowTextW(L"");
		D->SetWindowTextW(L"");
		P->SetWindowTextW(L"");
		E->SetWindowTextW(L"");

		while (temp != NULL){
			stringstream formatted1;
			stringstream formatted2;
			stringstream formatted3;
			stringstream formatted4;
			stringstream formatted5;


			formatted1 << temp->data.stockNumber << endl;
			formatted2 << temp->data.quantity << endl;
			formatted3 << temp->data.description << endl;
			formatted4 << temp->data.pricePerEach << endl;
			formatted5 << fixed << setprecision(2) << temp->data.extension << endl;


			CString str1 = formatted1.str().c_str();
			CString str2 = formatted2.str().c_str();
			CString str3 = formatted3.str().c_str();
			CString str4 = formatted4.str().c_str();
			CString str5 = formatted5.str().c_str();

			LPCWSTR item1 = static_cast<LPCWSTR>(str1);
			LPCWSTR item2 = static_cast<LPCWSTR>(str2);
			LPCWSTR item3 = static_cast<LPCWSTR>(str3);
			LPCWSTR item4 = static_cast<LPCWSTR>(str4);
			LPCWSTR item5 = static_cast<LPCWSTR>(str5);


			temp = temp->pNext;

			int len1 = L->GetWindowTextLength();
			L->SetSel(len1, len1);
			L->ReplaceSel(item1);

			int len2 = Q->GetWindowTextLength();
			Q->SetSel(len2, len2);
			Q->ReplaceSel(item2);

			int len3 = D->GetWindowTextLength();
			D->SetSel(len3, len3);
			D->ReplaceSel(item3);

			int len4 = P->GetWindowTextLength();
			P->SetSel(len4, len4);
			P->ReplaceSel(item4);

			int len5 = E->GetWindowTextLength();
			E->SetSel(len5, len5);
			E->ReplaceSel(item5);
		}
	}
	
	//=====================================================================
	CString AvalableQuantity(int num){
		Link * temp = pFirst;
		CString remainString;
		int i = 0;

		while (temp != NULL){
			if (i++ == num){
				remainString.Format(_T("%d"), (LPCTSTR)temp->data.quantity);
				return remainString;
			}
			temp = temp->pNext;
		}
	}
	//=====================================================================
	void AddPurchaseList(DoublyLinkedList &purList, int purQuantity, int index){
		Link* temp = pFirst;
		int i = 0;
		while (temp != NULL){
			if (i++ == index){
				boolForupdate b = alreadyHave(purList, temp->data.stockNumber);
				Info getInfoNewList;

				getInfoNewList.stockNumber = temp->data.stockNumber;

				if (b.isAlreadyHad){
					purList.removeKeyByIndex(purList.getIndexByStockNum(temp->data.stockNumber));
					getInfoNewList.quantity = b.quantityInPurList + purQuantity;
				}
				else
					getInfoNewList.quantity = purQuantity;
				
				getInfoNewList.description = temp->data.description;
				getInfoNewList.pricePerEach = temp->data.pricePerEach;
				getInfoNewList.extension = temp->data.realPrice * getInfoNewList.quantity;
				purList.insertFirst(getInfoNewList);
				purList.quickSort();

				// update data for the inventoryList
				temp->data.quantity -= purQuantity;
				return;
			}

		temp = temp->pNext;
		}	
	}
	//=====================================================================
	void printTotal(CEdit* P){
		Link* temp = pFirst;
		
		double total = 0;
		while (temp != NULL){
			total += temp->data.extension;
			temp = temp->pNext;
		}

		stringstream formatted;
		formatted << "$" << fixed << setprecision(2) << total;

		CString str = formatted.str().c_str();

		LPCWSTR item = static_cast<LPCWSTR>(str);

		int len = P->GetWindowTextLength();
		P->SetSel(len, len);
		P->ReplaceSel(item);
	}
	//=====================================================================
	void getListForRemoveForm(CListBox* list){
		Link* temp = pFirst;

		while (temp != NULL){
			list->AddString((LPCTSTR)(CString)(temp->data.stockNumber).c_str());
			temp = temp->pNext;
		}
	}
	//=======================================================================
	void onChangeRemoveForm(int index, CEdit* quantity, CEdit* des, CEdit* pPE, CEdit* exten){
		Link* temp = pFirst;
		int i = 0;
		CString cstringQuan, cstringDes, cstringPrice, cstringEx;

		while (temp != NULL){
			if (i++ == index){

				cstringQuan.Format(_T("%d"), temp->data.quantity);
				cstringDes = (LPCTSTR)(CString)(temp->data.description).c_str();
				cstringPrice = (LPCTSTR)(CString)(temp->data.pricePerEach).c_str();
				cstringEx.Format(_T("$%.2f"), temp->data.extension);

				quantity->SetWindowTextW(cstringQuan);
				des->SetWindowTextW(cstringDes);
				pPE->SetWindowTextW(cstringPrice);
				exten->SetWindowTextW(cstringEx);
			}

			temp = temp->pNext;
		}
	}
	//=======================================================================
	bool onRemoveButton(DoublyLinkedList &inventList,int index){
		StockAndQuan temp = getStockNumberAndQuantityByIndex(index);

		if (removeKeyByIndex(index)){
			inventList.updateQuantityForInvenList(temp.stock, temp.quan);
			return true;
		}
		else
			return false;
	}
	//=======================================================================
	void updateQuantityForInvenList(string stockNum, int purQuan){
		Link* temp = pFirst;

		while (temp != NULL){
			if (stockNum == temp->data.stockNumber)
				temp->data.quantity += purQuan;
			
			temp = temp->pNext;
		}
	}
	//=======================================================================
	double getTotal(){
		double total = 0;
		Link* temp = pFirst;

		while (temp != NULL){
			total += temp->data.extension;

			temp = temp->pNext;
		}

		return total;
	}
};