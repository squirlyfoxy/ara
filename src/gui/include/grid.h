#pragma once

#define GRID_SIZE 15
#define GRID_VERTICES_COUNT (GRID_SIZE * (GRID_SIZE + 1) * 3)
#define GRID_INDICES_COUNT (GRID_SIZE * GRID_SIZE * 6)

extern float gGridResolution;
extern float gGridScale;

void GenerateGridBuffers();
void DrawGrid();
