/*

  Copyright (C) 2003 - 2013  Razvan Cojocaru <rzvncj@gmail.com>
  Tabbed browsing support developed by Cedric Boudinet <bouced@gmx.fr>
  (this file originally written by Cedric Boudinet)
 
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

#ifndef __CHMHTMLNOTEBOOK_H_
#define __CHMHTMLNOTEBOOK_H_

#include <wx/aui/auibook.h>
#include <wx/webview.h>
#include <wx/treectrl.h>


enum {
	ID_NextPage,
	ID_PriorPage,
	ID_OutOfFullScreen
};

// Forward declarations
class CHMFrame;


/*! 
  \class wxNotebook
  \brief wxWidgets application class.
*/

/*! 
  \brief Custom HTML notebook widget class. For tabbed viewing of a CHM file.
*/
class CHMHtmlNotebook : public wxAuiNotebook {

public:
	//! Constructor
	CHMHtmlNotebook(wxWindow *parent, wxTreeCtrl *tc, CHMFrame* frame);

	//! Add a notebook tab and display the specified URL
	void AddHtmlView(const wxString& path,
			 const wxString& link);

	//! Displays the URL in the current tab
	bool LoadPageInCurrentView(const wxString& location);

	//! Returns the current page as a CHMHtmlWindow
	wxWebView* GetCurrentPage();

	//! Close all pages except the first one
	void CloseAllPagesExceptFirst();

	//! Called when user asks for a tab to close
	void OnCloseTab(wxCommandEvent&);

	//! Called when user ask for a new tab
	void OnNewTab(wxCommandEvent& event);

	//! Creates a new tab view
	wxWebView* CreateView();

	//! Overload for tab height control
	virtual bool AddPage(wxWindow* page, const wxString& title);

protected:
	//! Called when user asks for next notebook page
	void OnGoToNextPage(wxCommandEvent&);

	//! Called when user asks for prior notebook page
	void OnGoToPriorPage(wxCommandEvent&);

	//! Called when user presses ESCAPE
	void OnOutOfFullScreen(wxCommandEvent&);

	//! Callback for the page changed wxWidgets event
	void OnPageChanged(wxAuiNotebookEvent&);

	//! Callback for when a child's title changes
	void OnTitleChanged(wxWebViewEvent& evt);

	//! Callback for when the web view encounters an error
	void OnLoadError(wxWebViewEvent& evt);

	void OnNavigating(wxWebViewEvent& evt);

	void OnNavigated(wxWebViewEvent& evt);

	void OnLoaded(wxWebViewEvent& evt);

	void OnIdle(wxIdleEvent& evt);

private:
	wxTreeCtrl* _tcl;
	CHMFrame *_frame;
	DECLARE_EVENT_TABLE()
};


#endif // __CHMHTMLNOTEBOOK_H_


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


