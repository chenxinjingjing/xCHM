/*

  Copyright (C) 2003  Razvan Cojocaru <razvanco@gmx.net>
 
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
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/


#ifndef __CHMINDEXPANEL_H_
#define __CHMINDEXPANEL_H_


#include <wx/panel.h>
#include <wx/textctrl.h>


class CHMHtmlWindow;
class CHMListCtrl;


/*!
  \class wxPanel
  \brief generic wxWindows panel widget class.
*/


//! IDs for various widget events.
enum {
	ID_SearchIndex = 1500,
	ID_IndexClicked,
};


//! Custom panel for displaying the .chm index (if available).
class CHMIndexPanel : public wxPanel {

public:	
	/*!
	  \brief Initializes the panel.
	  \param parent Parent widget.
	  \param html HTML-capable widget used for displaying pages
	  from the index.
	 */
	CHMIndexPanel(wxWindow *parent, CHMHtmlWindow* html);

public:
	//! Accesor for the CHMListCtrl used by this panel.
	CHMListCtrl* GetResultsList() { return _lc; }

	//! Clears the textbox and removes all items from the list control.
	void Reset();

	//! Sets the font.
	void SetNewFont(const wxFont& font);

protected:
	//! This gets called when the user clicks on a list item.
	void OnIndexSel(wxCommandEvent& event);

	//! Called whenever the user types a letter in the textbox.
	void OnText(wxCommandEvent& event);

private:
	CHMHtmlWindow* _html;
	wxTextCtrl* _text;
	CHMListCtrl* _lc;
	bool _navigate;

private:
	DECLARE_EVENT_TABLE()
};


#endif // __CHMINDEXPANEL_H_
