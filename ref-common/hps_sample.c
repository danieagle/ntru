#include "sample.h"
#include "crypto_sort.h"
#include "fips202.h"

void sample_xof(unsigned char *output, const size_t sizeof_output, const unsigned char seed[NTRU_SEEDBYTES], const unsigned char domain[NTRU_DOMAINBYTES])
{
  unsigned char input[NTRU_SEEDBYTES+NTRU_DOMAINBYTES];
  int i;

  for(i=0;i<NTRU_SEEDBYTES;i++)
    input[i] = seed[i];
  for(i=0;i<8;i++)
    input[NTRU_SEEDBYTES+i] = domain[i];

  shake128(output, sizeof_output, input, sizeof(input));
}

void sample_iid(poly *r, const unsigned char uniformbytes[NTRU_S3_IID_BYTES])
{
  int i;
  /* {0,1,...,255} -> {0,1,2}; Pr[0] = 86/256, Pr[1] = Pr[-1] = 85/256 */
  for(i=0; i<NTRU_N-1; i++)
    r->coeffs[i] = mod3(uniformbytes[i]);

  r->coeffs[NTRU_N-1] = 0;
}

void sample_fixed_type(poly *r, const unsigned char u[NTRU_S3_FT_BYTES])
{
  // XXX: Assumes NTRU_S3_FT_BYTES = 4*N - 4.

  int32_t s[NTRU_N-1];
  int i;

  for (i = 0; i < NTRU_N-1; i++)
    s[i] = u[4*i+0] + (u[4*i+1] << 8) + (u[4*i+2] << 16) + (u[4*i+3] << 24);

  for (i = 0; i<NTRU_N-1; i++) s[i] &= -4;

  for (i = 0; i<NTRU_WEIGHT/2; i++) s[i] |=  1;

  for (i = NTRU_WEIGHT/2; i<NTRU_WEIGHT; i++) s[i] |=  2;

  crypto_sort(s,NTRU_N-1);

  for(i=0; i<NTRU_N-1; i++)
    r->coeffs[i] = ((uint16_t) (s[i] & 3));

  r->coeffs[NTRU_N-1] = 0;
}