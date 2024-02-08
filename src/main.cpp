#include "cxurity.h"

#ifdef CXU_HOST_SYSTEM_WIN
#ifndef CXU_COMPILE_DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
  return EntityApplication().run();
}
#else
int main() {
  return EntityApplication().run();
}
#endif
#elif CXU_HOST_SYSTEM_UNIX
int main() {
  return EntityApplication().run();
}
#endif
