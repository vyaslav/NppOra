/*
NppOra plugin by Viacheslav Avramenko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NPP_ORA_H
#define NPP_ORA_H

#define WIN32_LEAN_AND_MEAN

#include <math.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <stdio.h>
#include <assert.h>
#include "PluginInterface.h"
#include "Scintilla.h"
#include "Notepad_plus_rc.h"
#include "Notepad_plus_msgs.h"
#include <iostream>
#include <fstream>
#include "Resource.h"
#include "NppOraResource.h"
#include "OutputDialog.h"
#include <window.h>
#include <Commdlg.h>

#define CLEANUP 1

enum MENU_COMMANDS
{
    CMD_NPP_ORA = 0,
    NB_MENU_COMMANDS
};

#if 0
/* Extended Window Funcions */
void ClientToScreen(HWND hWnd, RECT* rect);
void ScreenToClient(HWND hWnd, RECT* rect);
#endif

#endif //NPP_ORA_H

