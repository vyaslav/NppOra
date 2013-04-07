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

#include "NppOra.h"

const TCHAR PLUGIN_NAME[] = TEXT("NppOra");
NppData nppData;

FuncItem funcItem[NB_MENU_COMMANDS];

HANDLE g_hModule;

OutputDialog    OutputDlg;

void openOutputDlg();

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  reasonForCall, LPVOID /*lpReserved*/)
{
    g_hModule = hModule;

    switch (reasonForCall)
    {
        case DLL_PROCESS_ATTACH:
        {
            funcItem[CMD_NPP_ORA]._pFunc = openOutputDlg;
            lstrcpy(funcItem[CMD_NPP_ORA]._itemName, TEXT("Open Output dialog"));
            funcItem[CMD_NPP_ORA]._pShKey = new ShortcutKey;
            funcItem[CMD_NPP_ORA]._pShKey->_isAlt = true;
            funcItem[CMD_NPP_ORA]._pShKey->_isCtrl = false;
            funcItem[CMD_NPP_ORA]._pShKey->_isShift = false;
            funcItem[CMD_NPP_ORA]._pShKey->_key = 'O';
            funcItem[CMD_NPP_ORA]._init2Check = false;
            break;
        }

        case DLL_PROCESS_DETACH:
        {
            OutputDlg.destroy();

            // Don't forget to deallocate your shortcut here
            for (int i = 0; i < NB_MENU_COMMANDS; i++)
                if (funcItem[i]._pShKey != NULL)
                    delete funcItem[i]._pShKey;

            break;
        }

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
    nppData = notpadPlusData;

    OutputDlg.init((HINSTANCE)g_hModule, nppData);
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
    return PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
    *nbF = NB_MENU_COMMANDS;
    return funcItem;
}

/*void ViewNavigationBar(void)
{
    HMENU hMenu = GetMenu(nppData._nppHandle);
    Settings.UseNavBar = !Settings.UseNavBar;

    if (hMenu)
        CheckMenuItem(hMenu,
                      funcItem[CMD_USE_NAV_BAR]._cmdID,
                      MF_BYCOMMAND | (Settings.UseNavBar ? MF_CHECKED : MF_UNCHECKED));

    if (active)
    {
        if (Settings.UseNavBar)
        {
            // Save current N++ focus
            HWND hwnd = GetFocus();

            // Configure NavBar
            NavDlg.SetColor(
                Settings.ColorSettings.added,
                Settings.ColorSettings.deleted,
                Settings.ColorSettings.changed,
                Settings.ColorSettings.moved,
                Settings.ColorSettings.blank);

            // Display Navbar
            NavDlg.doDialog(true);
            start_old = -1;

            // Restore N++ focus
            SetFocus(hwnd);
        }
        else
        {
            NavDlg.doDialog(false);
        }
    }
}*/

HWND getCurrentHScintilla(int which)
{
    return (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
};

// NP++ messages processing
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    /*if (Message == WM_CREATE)
    {
        HMENU hMenu = ::GetMenu(nppData._nppHandle);
        ::ModifyMenu(hMenu, funcItem[CMD_SEPARATOR_1]._cmdID, MF_BYCOMMAND | MF_SEPARATOR, 0, 0);
        ::ModifyMenu(hMenu, funcItem[CMD_SEPARATOR_2]._cmdID, MF_BYCOMMAND | MF_SEPARATOR, 0, 0);
        ::ModifyMenu(hMenu, funcItem[CMD_SEPARATOR_3]._cmdID, MF_BYCOMMAND | MF_SEPARATOR, 0, 0);
        ::ModifyMenu(hMenu, funcItem[CMD_SEPARATOR_4]._cmdID, MF_BYCOMMAND | MF_SEPARATOR, 0, 0);
    }*/

    return TRUE;
}


void openOutputDlg()
{
	OutputDlg.doDialog(!OutputDlg.isVisible());
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
    switch (notifyCode->nmhdr.code)
    {
        case NPPN_SHUTDOWN:
        {
            // Always close it, else N++'s plugin manager would call 'ViewNavigationBar'
            // on startup, when N++ has been shut down before with opened navigation bar
            if (OutputDlg.isVisible())
                OutputDlg.doDialog(false);
            break;
        }
    }
}
