//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPAPP.CPP
//
// Implementation for module, library and application objects.

#include <stdarg.h>
#include <sys\stat.h>
#include <sys\types.h>

#include "dbjwin_strsafe.h"
#include "wpp.h"

// DBJ: pre C++17 class statics have to be defined this way
WPApp *WPApp::pTheApp = NULL;

const char DFLTACCEL[] = "AppAccel";

//////////////////
// Load a user defined resource from the module file.
//
int WPModule::loadResource(LPCSTR resname, LPCSTR type, LPSTR buf, int len) {
  int size = 0;
  HRSRC hres = findResource(resname, type);
  if (hres) {
    HGLOBAL hmem = LoadResource(hinst, hres);
    if (hmem) {
      size = SizeofResource(hinst, hres);
      LPSTR resPtr = (LPSTR)LockResource(hmem);
      len = min(len, size);
      while (len-- > 0) *buf++ = *resPtr++;
      UnlockResource(hmem);
      FreeResource(hmem);
    }
  }
  return size;
}

//////////////////
// Create library object: load library module given name.
// Display error message if can't load it.
//
WPLibrary::WPLibrary(LPCSTR libname) {
  hinst = LoadLibrary(libname);
  if (hinst == NULL) {
    ErrBox("Error %d loading library %s", GetLastError(), libname);
    hinst = NULL;
  }
}

//////////////////
// Init application object.
//
//WPApp::WPApp() {
//  assert(pTheApp == NULL);
//  pTheApp = this;
//
//  cmdLine = NULL;
//  pinst = NULL;
//  cmdShow = 0;
//  exitCode = 0;
//  mainWin = NULL;
//  wndProc = WPWndProc;
//  dlgProc = WPDlgProc;
//  mdiClientHwnd = NULL;
//  dialogs = NULL;
//  accel = NULL;
//  // DBJ removed : useWININI = FALSE;
//}
//
////////////////////
//// Destroy application object
////
//WPApp::~WPApp() {
//  assert(pTheApp == this);
//  pTheApp = NULL;
//}

//////////////////
// Initialize application object.  Called from WinMain.
//
void WPApp::init(HINSTANCE h, HINSTANCE p, LPCSTR cmd, int show) {
  hinst = h;
  pinst = p;
  cmdLine = cmd;
  cmdShow = show;

  // Load default accelerator table if it exists
  if (findResource((char *)DFLTACCEL, RT_ACCELERATOR))
    loadAccel((char *)DFLTACCEL);
}

//////////////////
// Run the message loop. This super-duper message loop handles a number of
// different situations, including: modeless dialogs, accelerators, MDI
// windows, PeekMessage, etc. It's the only one applications ever need.
//
void WPApp::run() {
  assert(mainWin);
  mainWin->show(cmdShow);
  mainWin->update();
  HWND hwnd = (*mainWin)();
  assert(IsWindow(hwnd));

  MSG msg;
  BOOL peek = TRUE;

  while (peek || GetMessage(&msg, NULL, 0, 0)) {
    if (peek) {
      // We are doing peek message (app specified doIdle function)
      if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        peek = mainWin->doIdle();  // call app's doIdle function.
        continue;
      }
      if (msg.message == WM_QUIT) break;
    }
    // Check for MDI client message
    if (mdiClientHwnd && TranslateMDISysAccel(mdiClientHwnd, &msg)) continue;

    // Check for modeless dialog message.
    BOOL dlgmsg = FALSE;
    for (WPDialogModeless *dlg = dialogs; dlg; dlg = dlg->next) {
      if (dlg->getHwnd() && IsDialogMessage(dlg->getHwnd(), &msg)) {
        dlgmsg = TRUE;
        break;
      }
    }
    if (dlgmsg) continue;

    // Check for accelerator key.
    if (accel && TranslateAccelerator(hwnd, accel, &msg)) continue;

    // None of the above, so dispatch as normal.
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  exitCode = msg.wParam;
}

//////////////////
// Add modeless dialog to application
//
void WPApp::addDialog(WPDialogModeless *dlg) {
  dlg->next = dialogs;
  dialogs = dlg;
}

//////////////////
// Remove modeless dialog from application
//
void WPApp::removeDialog(WPDialogModeless *dlg) {
  if (dlg == dialogs)
    dialogs = dlg->next;
  else {
    for (WPDialogModeless *d = dialogs; d; d = d->next) {
      if (d->next == dlg) {
        d->next = dlg->next;
        return;
      }
    }
    assert(FALSE);
  }
}

//////////////////////////////////////////////////////////////////////////
//// The following functions access the Application's profile (.INI) file.
//////////////////////////////////////////////////////////////////////////
//
////////////////////
//// Get appliation profile string.  If no appname is specified,
//// gets it from either WIN.INI or appname.INI, depending on
//// value of flag useWININI.
//// DBJ 2022: WIN.INI use discarded
////
//int WPApp::getProfile(LPCSTR key, char *buf, int buflen, LPCSTR dflt,
//                      LPCSTR app) {
//  if (app == NULL)
//    app = this->modname();  // just a base name, no path and no extension
//  assert(app);
//  assert(ini_file_name());
//  return GetPrivateProfileString(app, key, dflt, buf, buflen, ini_file_name());
//}
//
//////////////////
//// Same thing, only get integer instead of string.
////
//int WPApp::getProfile(LPCSTR key, int dflt, LPCSTR app) {
//  if (app == NULL)
//    app = this->modname();  // just a base name, no path and no extension
//  assert(app);
//  assert(ini_file_name());
//  return GetPrivateProfileInt(app, key, dflt, ini_file_name());
//}
//
////////////////////
//// Same thing, only set instead of get.
////
//BOOL WPApp::setProfile(LPCSTR key, LPCSTR val, LPCSTR app) {
//  if (app == NULL)
//    app = this->modname();  // just a base name, no path and no extension
//  assert(app);
//  assert(ini_file_name());
//
//  return WritePrivateProfileString(app, key, val, ini_file_name());
//}
//
////////////////////
//// ...more of same
////
//BOOL WPApp::setProfile(LPCSTR key, int val, LPCSTR app) {
//  if (app == NULL)
//    app = this->modname();  // just a base name, no path and no extension
//  assert(app);
//  assert(ini_file_name());
//  char buf[16]{};
//  _itoa(val, buf, 10);
//  return WritePrivateProfileString(app, key, buf, ini_file_name());
//}

//////////////////////////////////////////////////////////////////
// Below are a few utility routines used throughout Windows++.
// This seems like as good a place as any to put them.
//////////////////////////////////////////////////////////////////

//////////////////
// This is a handy function for doing printf-style error boxes.
//
int DLLFUNC ErrBox(LPCSTR format, ...) {
  char buf[BUFSIZ]{};

  va_list argptr{};
  va_start(argptr, format);

  dbjwin_verify(S_OK == dbjwin_vsprintfa(buf, sizeof(buf), format, argptr));
  va_end(argptr);
  return MessageBox(NULL, buf, NULL, MB_OK | MB_ICONEXCLAMATION);
}

//////////////////
// Utility function copies source string into caller's
// buffer, given buffer length.
//
int DLLFUNC StringCopy(char *dest, int buflen, LPCSTR src) {
  size_t src_len{};
  if (S_OK == dbjwin_strlena(src, buflen, &src_len)) {
    if (S_OK != dbjwin_strncpya(dest, buflen, src, src_len))
      DoAssert("dbjwin_strncpya failed", __FILE__, __LINE__);
  } else {
    DoAssert("StringCopy failed; source size > destination size", __FILE__,
             __LINE__);
  }
  return src_len;
  // int rlen = lstrlen(src);
  // int len = min(buflen-1, rlen);
  // if (len>0) {
  //	if ( lstrcpynA(dest, src, len))
  //	dest[len]=0;
  //               else
  //                 DoAssert("lstrcpynA failed", __FILE__,__LINE__);
  //}
  // return rlen;
}

//////////////////
// Assertion failure
//
void DLLFUNC DoAssert(LPCSTR msg, LPCSTR file, unsigned line) {
  TRACE("Windows++: assertion failure in file %s, line %u: \"%s\"\n", file,
        line, msg);

  char buf[BUFSIZ]{};
  dbjwin_sprintfa(buf, BUFSIZ, "at line %u in file %s: \"%s\"", line, file,
                  msg);
  MsgBeep();
  if (MsgBox(buf, "ASSERTION FAILURE",
             MB_OKCANCEL | MB_ICONSTOP | MB_TASKMODAL) != IDOK)
    exit(-1);
}

//////////////////
// Display trace message in debug window
//
void WPTrace(LPCSTR format, ...) {
  va_list args;
  va_start(args, format);
  char buf[BUFSIZ]{};
  if (S_OK == dbjwin_vsprintfa(buf, BUFSIZ, format, args))
    OutputDebugStringA(buf);
  else
    OutputDebugStringA("dbjwin_vsprintfa() failed");
  va_end(args);
}

//////////////////
// FAR version of strchr
//
/*

LPSTR DLLFUNC lstrchr(LPSTR str, int c)
{
        if (str) {
                while (*str && *str!=c)
                        str++;
        }
        return (str && *str) ? str : NULL;
}
   that was 1992
*/
#define lstrchr strchr
