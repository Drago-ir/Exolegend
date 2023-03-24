

#ifndef KALMAN_H
#define KALMAN_H

#include "data_utils.h"
#include "user_utils.h"
#include "clock.h"
#include "fct_utils.h"
#include "debug.h"
#include "const.h"

#include <BasicLinearAlgebra.h>
using namespace hal;


#define M 2
#define N 3


using namespace BLA;
struct PosReg {
  double v, w, a;
  long long stamp;
};
class Kalman {

  public:
    Kalman(Clock* clock, Debug* debug);
    uint8_t process(Position measure, double v, double w, double dt);

    void predict(double v, double w, double dt);
    void update(Position measure);

    void initKalman(double rx, double ry, double ra, double qv, double qw, Position firstMeasure);
    Position getPosition(){return p;};
    void applyKalman(Position measure, long long stamp);
    void applyKalman(double vl, double vr);
    bool isInit() {return init;};
    void reset();
    void initRegisteries();
  private:
    PosReg buffer[REG_LENGTH];
    uint8_t buffLen = 0;
    void figureMatrices(Position measure, double v, double w, double dt);
    Matrix<N,N> P, H, S, K, R, A, I;
    Matrix<M,M> Q;
    Matrix<N,M> B;
    Matrix<N> x, y, z, h;
    Position p {0, 0, 0};
    Clock* clock;
    Debug* debug;
    bool init = false;
    double getDt(long long stamp);
    void addReg(PosReg reg);
    PosReg getLastReg();
    
};



#endif
