#include "MemoryEater.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

TCHAR *get_error_message()
{
  DWORD dwLastError = ::GetLastError();
  TCHAR *buf = NULL;
  ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  dwLastError,
                  MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
                  (LPTSTR) &buf,
                  0,
                  NULL);

  return buf;
}

int _tmain(int argc, _TCHAR *argv[]) {
  if (argc < 2) {
    _tprintf(_T("No size given. Expected one argument specifying size in MiB. Aborting."));
    return 1;
  }

  SIZE_T memSize = _tcstol(argv[1], NULL, 10);
  _tprintf(_T("Allocating %Id MB...\n"), memSize);

  memSize = memSize * 1024 * 1024;

  LPVOID alloc = VirtualAlloc(NULL, memSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (alloc == NULL) {
    _tprintf(_T("VirtualAlloc error. %sAborting.\n"), get_error_message());
    return 2;
  }

  if (!SetProcessWorkingSetSize(GetCurrentProcess(), memSize + 1024 * 1024, memSize + 2048 * 1024)) {
    _tprintf(_T("SetProcessWorkingSetSize error. %sAborting.\n"), get_error_message());
    return 3;
  }

  if (!VirtualLock(alloc, memSize)) {
    _tprintf(_T("VirtualLock error. %sAborting.\n"), get_error_message());
    return 4; 
  }

  _tprintf(_T("Hogging memory. Press ENTER to exit..."));
  cin.ignore();

  return 0;
}
