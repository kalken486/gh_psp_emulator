/*
Copyright (C) 2007 StrmnNrmn

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


#ifndef ADJUSTDEADZONESCREEN_H_
#define ADJUSTDEADZONESCREEN_H_

class CUIContext;

class CAdjustDeadzoneScreen
{
	public:
		virtual ~CAdjustDeadzoneScreen();

		static CAdjustDeadzoneScreen *	Create( CUIContext * p_context );

		virtual void				Run() = 0;
};

#endif	// ADJUSTDEADZONESCREEN_H_