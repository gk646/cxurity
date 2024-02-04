#define RAYLIB_IMPLEMENTATION
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#undef RAYLIB_IMPLEMENTATION
#undef RAYGUI_IMPLEMENTATION

#include "cxuconfig.h"
#include "cxurity.h"
#include <cxutil/cxtime.h>

using namespace std;
using namespace cxstructs;

int main() {
  auto cxu = new CXUEntityApplication();
  auto code = cxu->run();
  delete cxu;
  return code;
}