#include "../include/decide.hpp"
#include <iostream>

int main(int argc, char** argv) {

  Parameters_t params;
  params.NUMPOINTS = 7;
  params.X = new double[7]{0, 10, 2, 4, 12, 8, 6};
  params.Y = new double[7]{0, 0, -2, 0, 2, 0, -2};
  params.LENGTH1 = 1;
  params.RADIUS1 = 0.8;
  params.EPSILON = 0;
  params.AREA1 = 0.2;
  params.Q_PTS = 2;
  params.QUADS = 1;
  params.DIST = 0.1;
  params.N_PTS = 3;
  params.K_PTS = 1;
  params.A_PTS = 1;
  params.B_PTS = 1;
  params.C_PTS = 2;
  params.D_PTS = 2;
  params.E_PTS = 1;
  params.F_PTS = 1;
  params.G_PTS = 1;
  params.LENGTH2 = 25;
  params.RADIUS2 = 25;
  params.AREA2 = 0.1;

  std::array<std::array<Connectors, 15>, 15> LCM;
  for (int i = 0; i < 15; i++) {
      for (int j = 0; j < 15; j++) {
          LCM[i][j] = ORR;
      }
  }

  std::array<bool, 15> PUV = {true, true, true, true, true, true, true, true, false, true, true, true, true, false, true};

  if (decide(params, LCM, PUV)) std::cout << "YES";
  else std::cout << "NO";

  return 0;
}
