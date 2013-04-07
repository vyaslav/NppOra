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

#include "OutputDialog.h"
#include "Resource.h"

OutputDialog::OutputDialog(void) : DockingDlgInterface(IDD_NAV_DIALOG)
{
    grid = NULL;
}

OutputDialog::~OutputDialog(void)
{
}


void OutputDialog::init(HINSTANCE hInst, NppData nppData)
{
	_nppData = nppData;
	DockingDlgInterface::init(hInst, nppData._nppHandle);
}


void OutputDialog::doDialog(bool willBeShown)
{
    if (!isCreated())
	{
		create(&_data);

		// define the default docking behaviour
		_data.uMask			= DWS_DF_CONT_BOTTOM;
        _data.pszName       = TEXT("Output Window");
		_data.pszModuleName	= getPluginFileName();
        _data.dlgID			= CMD_NPP_ORA;

		::SendMessage(_hParent, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&_data);
		//create
		//create GRID
		grid = new V_UIGrid(_hInst, _hSelf);
		V_EVENT_BIND(this, V_GridRenderer, grid->gridRenderer, Resized)
	}
    // Display
	display(willBeShown);
	if(grid)
		grid->getGridWindow()->display(willBeShown);
}

BOOL CALLBACK OutputDialog::run_dlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	//::MessageBox(NULL, TEXT("WTF2"), TEXT("WTF2"), MB_OK);

	switch (Message) 
	{
		case WM_INITDIALOG:
		{
            // Here, I modify window styles (set H and V redraw)
            //SetClassLong(hWnd, GCL_STYLE, CS_HREDRAW | CS_VREDRAW );
			SetWindowLong(hWnd, GWL_STYLE, WS_CLIPCHILDREN );
            m_hWnd = hWnd;
            //ReadyToDraw = FALSE;
    		break;
		}

		case WM_SIZE:
		{
			if(OnResized){
				V_EventOnResized eventOnResized;
				eventOnResized.hwnd=grid->getGridWindow()->getHWND();
				eventOnResized.x=LOWORD(lParam);
				eventOnResized.y=HIWORD(lParam);
				OnResized(eventOnResized);
			}

		}

	    case WM_PAINT:
		{
            //ReadyToDraw = TRUE;
            //return OnPaint(hWnd);
			::RedrawWindow(grid->getGridWindow()->getHWND(), NULL, NULL, TRUE);
			break;
		}

		case WM_NOTIFY:
		{
			//return DockingDlgInterface::run_dlgProc(hWnd, Message, wParam, lParam);
			break;
		}

		case WM_DESTROY:
		{

            PostQuitMessage(0); 
			break;
		}

		default:
			return DockingDlgInterface::run_dlgProc(hWnd, Message, wParam, lParam);
	}

	return FALSE;
}


LRESULT OutputDialog::OnPaint(HWND hWnd)
{
	return 0;
}

