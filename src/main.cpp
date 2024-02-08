#include "cxurity.h"

#define RAYLIB_IMPLEMENTATION
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYLIB_IMPLEMENTATION
#undef RAYGUI_IMPLEMENTATION


#ifdef CXU_HOST_SYSTEM_WIN
#ifndef  CXU_COMPILE_DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
  auto cxu = new CXUEntityApplication();
  auto code = cxu->run();
  delete cxu;
  return code;
}
#else
int main() {
  auto cxu = new CXUEntityApplication();
  auto code = cxu->run();
  delete cxu;
  return code;
}
#endif
#elif CXU_HOST_SYSTEM_UNIX
int main() {
  auto cxu = new CXUEntityApplication();
  auto code = cxu->run();
  delete cxu;
  return code;
}
#endif
