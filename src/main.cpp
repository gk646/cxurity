#define RAYLIB_IMPLEMENTATION
#include <raylib.h>
#include "cxuconfig.h"
#include "cxurity.h"
#include <cxutil/cxtime.h>

using namespace std;
using namespace cxstructs;

int main() {
  auto cxu = new CXUEntityApplication();
  return cxu->run();
}