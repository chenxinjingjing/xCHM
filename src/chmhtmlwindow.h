/*

  Copyright (C) 2003 - 2013  Razvan Cojocaru <rzvncj@gmail.com>
 
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
  MA 02110-1301, USA.

*/


#ifndef __CHMHTMLWINDOW_H_
#define __CHMHTMLWINDOW_H_


#include <wx/html/htmlwin.h>
#include <wx/treectrl.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <chmfinddialog.h>



//! Event IDs.
enum {
	ID_CopySel = 1216,
	ID_CopyLink,
	ID_SaveLinkAs,
	ID_PopupForward,
	ID_PopupBack,
	ID_PopupFind,
	ID_PopupFullScreen,
	ID_OpenInNewTab,
};


//! Minimize dependencies. Forward declaration.
class CHMFrame;


/*!
  \class wxHtmlWindow
  \brief wxWidgets HTML widget class.
*/


/*! 
  \brief Custom HTML widget class. Needed for sychnronization between
  the topics tree control and the currently displayed page.
*/
class CHMHtmlWindow : public wxHtmlWindow {

public:
	/*!
	  \brief Initializes the widget.
	  \param parent The parent widget.
	  \param tc Pointer to the tree control we want to synchronize
	  with.
	  \param frame Outer frame.
	 */
	CHMHtmlWindow(wxWindow *parent, wxTreeCtrl *tc, CHMFrame* frame);

	//! Destructor. Deletes heap objects allocated in the constructor.
	~CHMHtmlWindow();

	virtual void OnSetTitle(const wxString& title);

	//! Override. Looks up the wanted page in the tree and selects it.
	bool LoadPage(const wxString& location);

	/*!
	  \brief Dictates the behaviour of LoadPage(). If SetSync()
	  has been called with a true parameter, the tree control will
	  be updated by LoadPage(). Otherwise, it will not be updated.
	  \param value Synchronize the tree widget on load?
	 */
	void SetSync(bool value) { _syncTree = value; }
	
	/*!
	  Returns true if the tree control's EVT_TREE_SEL_CHANGED
	  event happened as a result of the CHMHtmlWindow calling
	  SelectItem() on it.
	*/
	bool IsCaller() const { return _found; }

public:
	/*!
	  \brief Finds the first occurence of word in the displayed page.
	  \param parent Root of the wxHtmlCell tree where the search should
	  begin.
	  \param word The word we're looking for. If more words separated
	  by spaces are typed in, only the first one is taken into
	  account.
	  \param wholeWords If true, will search for words that match
	  word exactly.
	  \param caseSensitive If true, the search will be performed
	  case sensitive.
	  \return A valid cell if the result was found, NULL otherwise.
	 */
	wxHtmlCell* FindFirst(wxHtmlCell* parent, const wxString& word, 
			      bool wholeWords, bool caseSensitive);
	
	/*! 
	  \brief Same as FindFirst(), but continues the search from start
	  (start is considered in the search process).
	*/
	wxHtmlCell* FindNext(wxHtmlCell *start, 
			     const wxString& word, bool wholeWords,
			     bool caseSensitive);

	//! Clears the current selection.
	void ClearSelection();
	
	// Needs to be public, cause I call it from CHMHtmlFrame.
	//! Called when the user selects 'Find' from the popup menu.
	void OnFind(wxCommandEvent& event);

	//! Called when the user selects 'Copy' from the popup menu.
	void OnCopy(wxCommandEvent& event);

protected:	
	//! Called when the user selects 'Forward' from the popup menu.
	void OnForward(wxCommandEvent& event);

	//! Called when the user selects 'Back' from the popup menu.
	void OnBack(wxCommandEvent& event);
	
	//! Called when the user selects 'Copy link' from the popup menu.
	void OnCopyLink(wxCommandEvent& event);

	//! Called when the user selects 'Save link as' from the popup menu.
	void OnSaveLinkAs(wxCommandEvent& event);

	//! Called when the user presses a key
	void OnChar(wxKeyEvent &event);

	//! Called on widget resize.
	void OnSize(wxSizeEvent& event);

	//! Called when the user selects 'Save link as' from the popup menu.
	void OnOpenInNewTab(wxCommandEvent& event);

	//! Called when the 'Toggle fullscreen' is selected from the popup menu.
	void OnToggleFullScreen(wxCommandEvent& event);

protected:	
	//! Called when the user right clicks the HTML window.
	void OnRightClick(wxMouseEvent& event);

	//! Overridden. Called when the user clicks on a link.
	void OnLinkClicked(const wxHtmlLinkInfo& link);

private:
	//! Helper. Recursively looks for the opened page in the tree.
	void Sync(wxTreeItemId root, const wxString& page);

	//! Helper. Returns the prefix of the currently loaded page.
	wxString GetPrefix(const wxString& location) const;
	
private:
	wxTreeCtrl *_tcl;
	bool _syncTree;
	bool _found;
	wxMenu *_menu;
	CHMFrame *_frame;
	wxString _link;
	CHMFindDialog* _fdlg;

private:
	DECLARE_EVENT_TABLE()
};



#endif // __CHMHTMLWINDOW_H_


/*
  Local Variables:
  mode: c++
  c-basic-offset: 8
  tab-width: 8
  c-indent-comments-syntactically-p: t
  c-tab-always-indent: t
  indent-tabs-mode: t
  End:
*/

// vim:shiftwidth=8:autoindent:tabstop=8:noexpandtab:softtabstop=8

