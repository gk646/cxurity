#ifndef CXURITY_SRC_SHARED_CXUSHARED_H_
#define CXURITY_SRC_SHARED_CXUSHARED_H_

#include <cstdint>

enum class CXU_SecurityLevel : uint8_t { FULL, MAIN_ONLY };
enum class CXU_TabType : uint8_t { DASHBOARD, STATUS_BAR };
enum CXU_Side : uint8_t { CXU_WIDTH, CXU_HEIGHT };
enum CXU_Texture : uint8_t { APP, APP_ROUND };

struct Vec2 {
  float x;
  float y;
};
#endif  //CXURITY_SRC_SHARED_CXUSHARED_H_
