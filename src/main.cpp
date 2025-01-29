#include "../include/decide.hpp"

int main(int argc, char** argv) {

    Parameters_t params;
    params.NUMPOINTS = 4;
    params.QUADS = 3;
    params.Q_PTS = 4;
    params.X = new double[4]{1, -2, -1, 4};
    params.Y = new double[4]{1, 2, -1, -4};

    lic4(params);
    params.NUMPOINTS = 4;
    params.QUADS = 3;
    params.Q_PTS = 4;
    params.X = new double[4]{0, -1, 0, 4};
    params.Y = new double[4]{1, 0, -1, -4};

    lic4(params);
  
  return 0;
}
