/*

  Copyright (C) 2002 StrmnNrmn

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __ROMDB_H__
#define __ROMDB_H__

#include "Utility/Singleton.h"

#include "Core/ROM.h"


class	RomID;
enum	ECicType;

//*****************************************************************************
// Class definitions
//*****************************************************************************
class	CRomDB :  public CSingleton< CRomDB >
{
	public:
		virtual ~CRomDB();

		virtual bool			OpenDB( const char * filename ) = 0;												// Open the specified rom db, or creates a new one if it does not currently exist
		virtual void			Reset() = 0;																		// Resets the contents of the database
		virtual bool			Commit() = 0;																		// Commits any changes made to the database to disk

		virtual bool			QueryByFilename( const char * filename, RomID * id, u32 * rom_size, ECicType * cic_type ) = 0;		// Query a rom from the database
		virtual bool			QueryByID( const RomID & id, u32 * rom_size, ECicType * cic_type ) const = 0;						// Query a rom from the database
		virtual const char *	QueryFilenameFromID( const RomID & id ) const = 0;
};


#endif // __ROMDB_H__
