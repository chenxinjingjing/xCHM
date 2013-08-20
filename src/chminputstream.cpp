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


#include <chminputstream.h>


/*----------------------------------------------------------------------
 * class CHMInputStream static members
 */


CHMFile *CHMInputStream::_archiveCache = NULL;
wxString CHMInputStream::_path;


void CHMInputStream::Cleanup()
{
	if(_archiveCache != NULL) {
		delete _archiveCache;
		_archiveCache = NULL;
	}
}


CHMFile* CHMInputStream::GetCache()
{
	return _archiveCache; 
}

/*----------------------------------------------------------------------
 * rest of class CHMInputStream implementation
 */


#include <iostream>


CHMInputStream::CHMInputStream(const wxString& archive, 
			       const wxString& file)
	: _currPos(0)
{
	wxString filename = file;

	std::cout << "archive: " << archive.mb_str() << ", file: "
		  << file.mb_str() << std::endl;

	if(!archive.IsEmpty())
		_path = archive.BeforeLast(wxT('/')) + wxT("/");

	memset(&_ui, 0, sizeof(_ui));

	// Maybe the cached chmFile* isn't valid anymore,
	// or maybe there is no chached chmFile* yet.
	if(!archive.IsEmpty() && !Init(archive)) {
		m_lasterror = wxSTREAM_READ_ERROR;
		return;
	}

	// Somebody's looking for the homepage.
	if(file.IsSameAs(wxT("/")))
		filename = _archiveCache->HomePage();

	if(!filename.Left(8).CmpNoCase(wxT("/MS-ITS:"))) {
		// If this ever happens chances are Microsoft
		// decided that even if we went through the
		// trouble to open this archive and check out
		// the index file, the index file is just a
		// link to a file in another archive.

		wxString arch_link = 
			filename.AfterFirst(wxT(':')).BeforeFirst(wxT(':'));

		filename = filename.AfterLast(wxT(':'));

		// Reset the cached chmFile* and all.
		if(!Init(arch_link))
			if(!Init(_path + arch_link)) {
				m_lasterror = wxSTREAM_READ_ERROR;
				return;
			}
	}

	assert(_archiveCache != NULL);

	// See if the file really is in the archive.
	if(!_archiveCache->ResolveObject(filename, &_ui)) {
		m_lasterror = wxSTREAM_READ_ERROR;
		return;
	}
}


size_t CHMInputStream::GetSize() const
{
	return _ui.length;
}


bool CHMInputStream::Eof() const
{
	return (uint64_t)_currPos >= _ui.length;
}


size_t CHMInputStream::OnSysRead(void *buffer, size_t bufsize)
{	
	if((uint64_t)_currPos >= _ui.length) {
		m_lasterror = wxSTREAM_EOF;
		return 0;
	}

	if(!_archiveCache)
		return 0;

	if((uint64_t)(_currPos + bufsize) > _ui.length)
        bufsize = _ui.length - _currPos;
        
	bufsize = 
		_archiveCache->RetrieveObject(&_ui,
					      (unsigned char *)buffer, 
					      _currPos, bufsize);
     
	_currPos += bufsize;
    
	return bufsize;
}


wxFileOffset CHMInputStream::OnSysSeek(wxFileOffset seek, wxSeekMode mode)
{
	switch(mode) {
	case wxFromCurrent:
		_currPos += seek;
		break;
	case wxFromStart:
		_currPos = seek;
		break;
	case wxFromEnd:
		_currPos = _ui.length - 1 + seek;
		break;
	default:
		_currPos = seek;
	}

	return _currPos;
}


bool CHMInputStream::Init(const wxString& archive)
{
	if(_archiveCache == NULL || 
	   !_archiveCache->ArchiveName().IsSameAs(archive)) {
	 
		Cleanup();

		_archiveCache = new CHMFile(archive);

		if(!_archiveCache->IsOk()) {
			Cleanup();
			return false;
		}
	}

	return true;
}


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

