#include "qpc.h"
#include "madgwick_filter.h"

void madgwick_filter_quat_update(madgwick_rec_t *pRec,
                                 fix16_t ax, fix16_t ay, fix16_t az,
                                 fix16_t gx, fix16_t gy, fix16_t gz,
                                 fix16_t mx, fix16_t my, fix16_t mz)
{
    // Auxiliary variables to avoid repeated arithmetic
    fix16_t _2q1mx;
    fix16_t _2q1my;
    fix16_t _2q1mz;
    fix16_t _2q2mx;
    fix16_t _4bx;
    fix16_t _4bz;
    fix16_t _2q1 = 2 * pRec->q[0];
    fix16_t _2q2 = 2 * pRec->q[1];
    fix16_t _2q3 = 2 * pRec->q[2];
    fix16_t _2q4 = 2 * pRec->q[3];
    fix16_t _2q1q3 = 2 * fix16_mul(pRec->q[0], pRec->q[2]);
    fix16_t _2q3q4 = 2 * fix16_mul(pRec->q[2], pRec->q[3]);
    fix16_t q1q1 = fix16_mul(pRec->q[0], pRec->q[0]);
    fix16_t q1q2 = fix16_mul(pRec->q[0], pRec->q[1]);
    fix16_t q1q3 = fix16_mul(pRec->q[0], pRec->q[2]);
    fix16_t q1q4 = fix16_mul(pRec->q[0], pRec->q[3]);
    fix16_t q2q2 = fix16_mul(pRec->q[1], pRec->q[1]);
    fix16_t q2q3 = fix16_mul(pRec->q[1], pRec->q[2]);
    fix16_t q2q4 = fix16_mul(pRec->q[1], pRec->q[3]);
    fix16_t q3q3 = fix16_mul(pRec->q[2], pRec->q[2]);
    fix16_t q3q4 = fix16_mul(pRec->q[2], pRec->q[3]);
    fix16_t q4q4 = fix16_mul(pRec->q[3], pRec->q[3]);
}
