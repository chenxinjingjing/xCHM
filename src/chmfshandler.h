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


#ifndef __CHMFSHANDLER_H_
#define __CHMFSHANDLER_H_


#include <wx/filesys.h>


/*!
  \class wxFileSystemHandler
  \brief wxWidgets virtual filesystem handler class.
*/


//! CHM filesystem handler class.
class CHMFSHandler : public wxFileSystemHandler
{
public:
	/*!
	  \brief Doesn't do anything but needs to be here because of
	  the private copy constructor.
	 */
        CHMFSHandler();

	//! Cleanup code. This calls CHMInputStream's Cleanup().
	~CHMFSHandler();

	/*!
	  \brief Checks if it can open the file passed in location.
	  \param location File to open.
	  \returns true if location is in the form 
	  "file:filename.chm#xchm:/file_inside_archive.extension", false
	  otherwise. Does not attempt to actually open the file.
	 */
        virtual bool CanOpen(const wxString& location);

	/*!
	  \brief Tries to open the file specified.
	  \param fs Currently ignored.
	  \param location filename.
	  \return A valid pointer to a wxFSFile or NULL on failure.
	 */
        virtual wxFSFile* OpenFile(wxFileSystem& fs, const wxString& location);

private:
	//! No copy construction.
	CHMFSHandler(const CHMFSHandler&);

	//! No assignment.
	CHMFSHandler& operator=(const CHMFSHandler&);
};


#endif // __CHMFSHANDLER_H_


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

