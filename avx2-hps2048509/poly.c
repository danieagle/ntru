#include "poly.h"
#include "poly_r2_inv.h"

/* Map {0, 1, 2} -> {0,1,q-1} in place */
void poly_Z3_to_Zq(poly *r)
{
  int i;
  for(i=0; i<NTRU_N; i++)
    r->coeffs[i] = r->coeffs[i] | ((-(r->coeffs[i]>>1)) & (NTRU_Q-1));
}

/* Map {0, 1, q-1} -> {0,1,2} in place */
void poly_trinary_Zq_to_Z3(poly *r)
{
  int i;
  for(i=0; i<NTRU_N; i++)
    r->coeffs[i] = 3 & (r->coeffs[i] ^ (r->coeffs[i]>>(NTRU_LOGQ-1)));
}

void poly_Sq_mul(poly *r, const poly *a, const poly *b)
{
  int i;
  poly_Rq_mul(r, a, b);
  for(i=0; i<NTRU_N; i++)
    r->coeffs[i] = MODQ(r->coeffs[i] - r->coeffs[NTRU_N-1]);
}

void poly_lift(poly *r, const poly *a)
{
  int i;
  for(i=0; i<NTRU_N; i++)
    r->coeffs[i] = a->coeffs[i];
  poly_Z3_to_Zq(r);
}

static void poly_R2_inv_to_Rq_inv(poly *r, const poly *ai, const poly *a)
{
#if NTRU_Q <= 256 || NTRU_Q >= 65536
#error "poly_R2_inv_to_Rq_inv in poly.c assumes 256 < q < 65536"
#endif

  int i;
  poly b, c;
  poly s;

  // for 0..4
  //    ai = ai * (2 - a*ai)  mod q
  for(i=0; i<NTRU_N; i++)
    b.coeffs[i] = MODQ(NTRU_Q - a->coeffs[i]); // b = -a

  for(i=0; i<NTRU_N; i++)
    r->coeffs[i] = ai->coeffs[i];

  poly_Rq_mul(&c, r, &b);
  c.coeffs[0] += 2; // c = 2 - a*ai
  poly_Rq_mul(&s, &c, r); // s = ai*c

  poly_Rq_mul(&c, &s, &b);
  c.coeffs[0] += 2; // c = 2 - a*s
  poly_Rq_mul(r, &c, &s); // r = s*c

  poly_Rq_mul(&c, r, &b);
  c.coeffs[0] += 2; // c = 2 - a*r
  poly_Rq_mul(&s, &c, r); // s = r*c

  poly_Rq_mul(&c, &s, &b);
  c.coeffs[0] += 2; // c = 2 - a*s
  poly_Rq_mul(r, &c, &s); // r = s*c
}

void poly_Rq_inv(poly *r, const poly *a)
{
  poly ai2;
  poly_R2_inv(&ai2, a);
  poly_R2_inv_to_Rq_inv(r, &ai2, a);
}
