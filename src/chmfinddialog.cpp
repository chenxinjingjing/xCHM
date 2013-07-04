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


#include <chmfinddialog.h>
#include <wx/webview.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/tokenzr.h>
#include <wx/wx.h>


CHMFindDialog::CHMFindDialog(wxWindow *parent, wxWebView *toSearch)
	: wxDialog(parent, -1, wxString(_("Find in page.."))),
	  _html(toSearch), _cell(NULL)
{
	wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	
	_text = new wxTextCtrl(this, ID_TextFind, wxEmptyString, 
			       wxDefaultPosition, wxSize(200, -1), 
			       wxTE_PROCESS_ENTER);

	_whole = new wxCheckBox(this, -1, _("Whole words only"));
	_case = new wxCheckBox(this, -1, _("Case sensitive"));

	sizer->Add(_text, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
	sizer->Add(_whole, 0, wxLEFT, 5);
	sizer->Add(_case, 0, wxLEFT | wxBOTTOM, 5);

	wxSizer *szButtons = new wxBoxSizer(wxVERTICAL);
	wxButton *find = new wxButton(this, ID_FindNext, _("Find next"));

	szButtons->Add(find, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 5);
	szButtons->Add(new wxButton(this, wxID_CANCEL, _("Cancel")), 
		       1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 5);

	wxSizer *topsizer = new wxBoxSizer(wxHORIZONTAL);
	topsizer->Add(sizer);
	topsizer->Add(szButtons);

	SetAutoLayout(TRUE);
	SetSizer(topsizer);
	topsizer->Fit(this);
	Centre(wxBOTH);

	SetFocusToTextBox();
}


void CHMFindDialog::OnFind(wxCommandEvent& WXUNUSED(event))
{
	_html->ClearSelection();

	wxString sr = _text->GetLineText(0);
	if (sr.IsEmpty())
		return;

	int flags = wxWEBVIEW_FIND_HIGHLIGHT_RESULT | wxWEBVIEW_FIND_WRAP;
	
	if(_case->IsChecked())
		flags |= wxWEBVIEW_FIND_MATCH_CASE;

	if(_whole->IsChecked())
		flags |= wxWEBVIEW_FIND_ENTIRE_WORD;
	
	_html->Find(sr, 0);
}



BEGIN_EVENT_TABLE(CHMFindDialog, wxDialog)
    EVT_TEXT_ENTER(ID_TextFind, CHMFindDialog::OnFind)
    EVT_BUTTON(ID_FindNext, CHMFindDialog::OnFind)
END_EVENT_TABLE()


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


