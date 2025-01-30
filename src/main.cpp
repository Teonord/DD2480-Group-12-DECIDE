#include "../include/decide.hpp"
#include <array>
#include <iostream>

int main(int argc, char** argv) {
  //std::cout << "Starting program...\n"; // Debugging Step
  // Step 1: Initialize Parameters
  Parameters_t params;
  params.LENGTH1 = 1.0;
  params.RADIUS1 = 3.0;
  params.RADIUS2 = 9.0;
  params.EPSILON = 0.2;
  params.DIST = 5.0;
  params.A_PTS = 1;
  params.B_PTS = 1;
  params.G_PTS = 1;
  params.QUADS = 1;
  params.Q_PTS = 4;
  params.K_PTS = 1;
  params.N_PTS = 3;
  params.E_PTS = 2;
  params.F_PTS = 2;
  params.NUMPOINTS = 8; 
  params.AREA1 = 20;
  params.AREA2 = 12;
  params.X = new double[8]{-100, 0, 2, 0, 1, 12, -50, 2};
  params.Y = new double[8]{0, -1, 3, 100, 0, 32, 50, -2};

  //std::cout << "Parameters initialized.\n"; // Debugging Step
  // Step 2: Compute CMV
  std::array<bool, 15> CMV = {false};
  CMV[0] = isConsecDistGTLen(params);
  CMV[1] = lic1(params);
  CMV[2] = lic2(params);
  CMV[3] = lic3(params);
  CMV[4] = lic4(params);
  CMV[5] = lic5(params);
  CMV[6] = isDistFromLine(params);
  CMV[7] = lic7(params);
  CMV[8] = sepPointsContainedInCircle(params);  
  CMV[9] = isAngleWithinThreshold(params);  
  CMV[10] = lic10(params);
  CMV[11] = lic11(params);
  CMV[12] = lic12(params);
  CMV[13] = lic13(params);
  CMV[14] = lic14(params);

  //std::cout << "CMV Computed\n"; // Debugging Step
  // Step 3: Initialize Logical Connector Matrix (LCM)
  std::array<std::array<Connectors, 15>, 15> LCM;
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      LCM[i][j] = ORR;  
    }
  }

  //std::cout << "LCM Initialized\n"; // Debugging Step
  // Step 4: Initialize Preliminary Unlocking Vector (PUV)
  std::array<bool, 15> PUV;
  PUV.fill(true);

  //std::cout << "PUV Initialized\n"; // Debugging Step
  // Step 5: Compute Preliminary Unlocking Matrix (PUM)
  std::array<std::array<bool, 15>, 15> PUM;
  PUM = generatePreliminaryUnlockingMatrix(CMV, LCM);
  //std::cout << "PUM Computed\n"; // Debugging Step
  //std::cout << "PUM Matrix:\n";

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
        std::cout << PUM[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // Step 6: Compute Final Unlocking Vector (FUV)
  std::array<bool, 15> FUV;
  FUV = generateFinalUnlockingVector(PUM, PUV);
  //std::cout << "FUV Computed\n"; // Debugging Step
  std::cout << "FUV Vector:\n";
  for (int i = 0; i < 15; i++) {
    std::cout << "FUV[" << i << "] = " << FUV[i] << std::endl;
  }

  // Step 7: Determine Launch Decision
  bool launch = launchDecision(FUV);
  //std::cout << "Launch Decision Computed\n"; // Debugging Step
  std::cout << "Launch decision evaluation:\n";
  for (int i = 0; i < 15; i++) {
    if (!FUV[i]) {
        std::cout << "Launch failed at FUV[" << i << "] = false\n";
        launch = false;
    }
  }

  // Step 8: Output Result
  std::cout << (launch ? "Yes" : "No") << std::endl;

  return 0;
}
