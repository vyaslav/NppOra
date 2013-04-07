/*
NppOra plugin by Viacheslav Avramenko

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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef OUTPUT_DLG_H
#define OUTPUT_DLG_H

#include "NppOra.h"
#include "Windows.h"
#include "DockingDlgInterface.h"
#include "V_UIGrid.h"
#include "V_G_Events.h"

#define SPACE   2

class OutputDialog : public DockingDlgInterface
{
public:
	OutputDialog(void);
	~OutputDialog(void);

    void init(HINSTANCE hInst, NppData nppData);
	void destroy(void) {};
   	void doDialog(bool willBeShown = true);

	V_EVENT_PROVIDER(Resized);

protected:

	virtual BOOL CALLBACK run_dlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:

    HWND m_hWnd;

    LRESULT OnPaint(HWND hWnd);
    HDC     m_hdc;

	NppData	_nppData;
	tTbData	_data;
	//ref to grid obj
	V_UIGrid* grid;
};

#endif // NAV_DLG_H