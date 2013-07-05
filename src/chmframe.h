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


#ifndef __CHMFRAME_H_
#define __CHMFRAME_H_

#include <wx/wx.h>
#include <wx/webview.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/treectrl.h>
#include <wx/panel.h>
#include <wx/combobox.h>
#include <wx/font.h>
#include <wx/docview.h>
#include <wx/thread.h>


// Forward declarations.
class CHMHtmlWindow;
class CHMSearchPanel;
class CHMIndexPanel;
class wxFileType;
class CHMHtmlNotebook;


//! Default sash position.
#define CONTENTS_MARGIN 170


#ifdef HAVE_CONFIG_H
#	include <config.h>
#else
	// this should never happen
#	define VERSION "unknown"
#endif


//! IDs for various widget events.
enum
{
	ID_Quit = 1,
	ID_About,
	ID_Open,
	ID_Print,
	ID_Home,
	ID_Forward,
	ID_Back,
	ID_Contents,
	ID_Bookmarks,
	ID_Add,
	ID_Remove,
	ID_FindInPage,
	ID_CopySelection,
	ID_Recent,
	ID_Notebook,
	ID_RegisterExtension,
	ID_CloseTab,
	ID_NewTab,
	ID_FullScreen,
	ID_TreeCtrl = 1000,
};


/*!
  \class wxFrame
  \brief wxWidgets frame widget class.
*/


/*! 
  \brief The frame, owner of the wxHtmlWindow, contents tree control and
  all the other nifty stuff. 
*/
class CHMFrame : public wxFrame {

public:
	/*!
	  \brief Brings the frame into existence.
	  \param title The text that shows up on the titlebar.
	  \param booksDir Where to go when you click Open.. on the
	  toolbar. This is used to remember the last directory where
	  a book was sucessfully opened. For the current working
	  directory just pass the empty string.
	  \param pos The upper left corner of the frame.
	  \param size The size of the frame.
	  \param sashPosition Distance from the left of the frame to
	  \param fullAppPath The absolute path to the executable of the process
	  the end of the contents / search panel.
	  \param loadTopics If set to false, don't try to load the topics tree.
	  \param loadIndex If set to false, don't try to load the index list.
	*/
	CHMFrame(const wxString& title, const wxString& booksDir,
		 const wxPoint& pos, const wxSize& size,
		 const int sashPosition = CONTENTS_MARGIN,
		 const wxString& fullAppPath = wxEmptyString,
		 bool loadTopics = true, bool loadIndex = true);

	//! Cleans up.
	~CHMFrame();

	/*!
	  \brief Attempts to load a .chm file and display it's home page.
	  \param archive The .chm file name on disk.
	  \return TRUE if the operation was successful.
	 */
	bool LoadCHM(const wxString& archive);
	
	/*!
	  \brief Attempts to load a context-ID from within the current chm file
	  \param contextID the context-ID to load.
	  \return TRUE if the operation was successful.
	 */
	bool LoadContextID( const int contextID );

	//! Fills the index and the contents tree.
	void UpdateCHMInfo();

	//! Add html view
	void AddHtmlView(const wxString& path, const wxString& link);

	//! Toggles fullscreen mode
	void ToggleFullScreen(bool onlyIfFullScreenOn = false);

protected:
	//! Called when the user closes the window.
	void OnQuit(wxCommandEvent& event);

	//! Called when the user clicks on About.
	void OnAbout(wxCommandEvent& event);

	//! Called when the user wants to open a file.
	void OnOpen(wxCommandEvent& event);

	//! Called when the user wants to see the default page.
	void OnHome(wxCommandEvent& event);

	//! Called when the user wants to go forward in the history.
	void OnHistoryForward(wxCommandEvent& event);

	//! Called when the user wants to go back in the history.
	void OnHistoryBack(wxCommandEvent& event);	

	/*! 
	  \brief Called when the user wants to either disable or enable
	  the contents tree panel on the left.
	*/
	void OnShowContents(wxCommandEvent& event);	

	//! Called when the user wants to print the displayed page.
	void OnPrint(wxCommandEvent& event);

	//! Called when the user selects a file from the file history.
	void OnHistFile(wxCommandEvent& event);

	//! Called when the user types Ctrl-F.
	void OnFind(wxCommandEvent& event);

	//! Called when the user types Ctrl-F.
	void OnCopySelection(wxCommandEvent& event);

	//! Called when fullscreen mode is being toggled
	void OnFullScreen(wxCommandEvent& event);

	//! Called when the user clicks on the Add button.
	void OnAddBookmark(wxCommandEvent& event);

#if defined(__WXMSW__) || defined(__WXMAC__)
	//! Called when the user selects Register extension
	void OnRegisterExtension(wxCommandEvent& event);	
#endif// __WXMSW__

	//! Called when the user clicks on the Remove button.
	void OnRemoveBookmark(wxCommandEvent& event);

	//! Called when the user chooses a bookmark from the wxChoice control.
	void OnBookmarkSel(wxCommandEvent &event);

	//! Called when an item in the contents tree is clicked.
	void OnSelectionChanged(wxTreeEvent& event);

	//! Cleanup code. This saves the window position and last open dir.
	void OnCloseWindow(wxCloseEvent& event);

	//! Called when the user presses a key
	void OnChar(wxKeyEvent &event);

	//! Called when the user types Ctrl-F4.
	void OnCloseTab(wxCommandEvent& event);

	//! Called when the user types Ctrl-N.
	void OnNewTab(wxCommandEvent& event);

private:
	//! Helper. Creates the menu.
	wxMenuBar *CreateMenu();

	//! Helper. Initializes the frame toolbar.
	bool InitToolBar(wxToolBar *toolbar);

	//! Helper. Creates the contents panel.
	wxPanel* CreateContentsPanel();

	//! Helper. Loads the bookmarks for the currently opened CHM file.
	void LoadBookmarks();

	//! Helper. Saves the bookmarks for the currently opened CHM file.
	void SaveBookmarks();

	//! Helper. Saves exit information (size, history, etc.)
	void SaveExitInfo();

private:
	CHMHtmlNotebook * _nbhtml;
	wxTreeCtrl* _tcl;
	wxSplitterWindow* _sw;
	wxMenu* _menuFile;
	wxToolBar* _tb;
	wxNotebook* _nb;
	wxComboBox* _cb;
	CHMSearchPanel* _csp;
	CHMIndexPanel* _cip;

	wxString _openPath;
	bool _bookmarkSel;
	bool _bookmarksDeleted;
	int _sashPos;
	wxFileHistory _fh;
	wxString _fullAppPath;
	bool _loadTopics;
	bool _loadIndex;
	bool _fullScreen;

private:
	DECLARE_EVENT_TABLE()	
};


#endif // __CHMFRAME_H_


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
