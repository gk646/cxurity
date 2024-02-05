#include "../../cxurity.h"
#include <raylib.h>
#include "style_jungle.h"    // raygui style: jungle
#include "style_candy.h"     // raygui style: candy
#include "style_lavanda.h"   // raygui style: lavanda
#include "style_cyber.h"     // raygui style: cyber
#include "style_terminal.h"  // raygui style: terminal
#include "style_ashes.h"     // raygui style: ashes
#include "style_bluish.h"    // raygui style: bluish
#include "style_dark.h"      // raygui style: dark
#include "style_cherry.h"    // raygui style: cherry
#include "style_sunny.h"     // raygui style: sunny
#include "style_enefete.h"   // raygui style: enefete

void EntityUIRoot::draw(Entity& e) {
  BeginDrawing();
  ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
  styleSelector();
  statusBar.draw(e, {0, 0});
  sPanel.draw(e, {(float)GetScreenWidth() * 0.7F, 0});
  EndDrawing();
}

void EntityUIRoot::styleSelector() {
  if (visualStyleActive != prevVisualStyleActive) {
    GuiLoadStyleDefault();

    switch (visualStyleActive) {
      case 1:
        GuiLoadStyleJungle();
        break;
      case 2:
        GuiLoadStyleCandy();
        break;
      case 3:
        GuiLoadStyleLavanda();
        break;
      case 4:
        GuiLoadStyleCyber();
        break;
      case 5:
        GuiLoadStyleTerminal();
        break;
      case 6:
        GuiLoadStyleAshes();
        break;
      case 7:
        GuiLoadStyleBluish();
        break;
      case 8:
        GuiLoadStyleDark();
        break;
      case 9:
        GuiLoadStyleCherry();
        break;
      case 10:
        GuiLoadStyleSunny();
        break;
      case 11:
        GuiLoadStyleEnefete();
        break;
      default:
        break;
    }

    prevVisualStyleActive = visualStyleActive;
  }

  GuiComboBox({GetScreenWidth()*0.08F, GetScreenHeight()*0.031F, 100, 20},
              "default;Jungle;Candy;Lavanda;Cyber;Terminal;Ashes;Bluish;Dark;Cherry;Sunny;Enefete",
              &visualStyleActive);
}