#include "../../cxurity.h"
#include <raylib.h>

void EntityUIRoot::draw() {
  BeginDrawing();
  ClearBackground(GRAY);
  dBoard.draw();

  mousePosition = GetMousePosition();
  windowSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  windowPosition = GetWindowPosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (mousePosition.y < MARGIN_SIZE) {
      // Top area for moving the window
      isMoving = true;
      clickOffset = mousePosition;
    } else if (mousePosition.x >= windowSize.x - MARGIN_SIZE) {
      // Right side for resizing width
      isResizingRight = true;
      clickOffset.x = mousePosition.x - windowSize.x;
    } else if (mousePosition.y >= windowSize.y - MARGIN_SIZE) {
      // Bottom side for resizing height
      isResizingBottom = true;
      clickOffset.y = mousePosition.y - windowSize.y;
    } else if (mousePosition.x < MARGIN_SIZE) {
      // Left side for resizing width
      isResizingLeft = true;
      clickOffset.x = mousePosition.x;
    }
  }

  if (isResizingRight || isResizingBottom || isResizingLeft) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      int newWidth = isResizingRight ? mousePosition.x - clickOffset.x : windowSize.x;
      int newHeight = isResizingBottom ? mousePosition.y - clickOffset.y : windowSize.y;

      // Adjust for left side resizing
      if (isResizingLeft) {
        newWidth = windowSize.x + (windowPosition.x - mousePosition.x);
        if (newWidth > minWidth) {  // Ensure the new width is not less than minWidth
          SetWindowPosition(mousePosition.x, windowPosition.y);
        }
      }

      newWidth = newWidth < minWidth ? minWidth : newWidth;
      newHeight = newHeight < minHeight ? minHeight : newHeight;

      SetWindowSize(newWidth, newHeight);
    } else {
      isResizingRight = false;
      isResizingBottom = false;
      isResizingLeft = false;
    }
  } else if (isMoving) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      SetWindowPosition(windowPosition.x + (mousePosition.x - clickOffset.x),
                        windowPosition.y + (mousePosition.y - clickOffset.y));
    } else {
      isMoving = false;
    }
  }

  EndDrawing();
}

void EntityUIRoot::update() {}