#include "../../cxurity.h"
#include <raylib.h>

void StatusBar::draw() {
  DrawRectangle(0, 0, GetScreenWidth(), 20, DARKGRAY);
  DrawText("Security Application", 10, 5, 10, WHITE);
}

void ProcessListView::draw() {
  // Draw a list view for processes
  DrawRectangle(20, 30, GetScreenWidth() / 4, GetScreenHeight() - 50, LIGHTGRAY);
  DrawText("Process List", 30, 40, 10, BLACK);
  // Dummy list items
  DrawText("process1.exe", 30, 60, 10, DARKGRAY);
  DrawText("process2.exe", 30, 80, 10, DARKGRAY);
}

void AnomalyPanel::draw() {
  int panelWidth = GetScreenWidth() / 3;
  int panelHeight = 150;
  int panelX = GetScreenWidth() - panelWidth - 20;
  int panelY = 30;
  DrawRectangle(panelX, panelY, panelWidth, panelHeight, RED);
  DrawText("Anomaly Detection", panelX + 10, panelY + 10, 10, WHITE);
  // Dummy anomaly data
  DrawText("No anomalies detected", panelX + 10, panelY + 30, 10, WHITE);
}