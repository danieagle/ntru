#ifndef PARAMS_H
#define PARAMS_H

/* New parameter sets need the following three values. */
/* The rest of the parameters are derived from these.  */

#define NTRU_N 701
#define NTRU_LOGQ 13
#define NTRU_N_INVERSE_MOD_Q 2197

/**/

#define NTRU_Q (1 << NTRU_LOGQ)

#define NTRU_SEEDBYTES       32
#define NTRU_PRFKEYBYTES     32
#define NTRU_SHAREDKEYBYTES  32
#define NTRU_DOMAINBYTES     8
#define NTRU_S3_IID_BYTES    (NTRU_N-1)

#define NTRU_DOMAIN_KEY ((unsigned char *) "samplefg")
#define NTRU_DOMAIN_MSG ((unsigned char *) "samplerm")

#define NTRU_PACK_DEG (NTRU_N-1)
#define NTRU_PACK_TRINARY_BYTES    ((NTRU_PACK_DEG+4)/5)

#define NTRU_OWCPA_MSGBYTES       (2*NTRU_PACK_TRINARY_BYTES)
#define NTRU_OWCPA_PUBLICKEYBYTES ((NTRU_LOGQ*NTRU_PACK_DEG+7)/8)
#define NTRU_OWCPA_SECRETKEYBYTES (2*NTRU_PACK_TRINARY_BYTES + NTRU_OWCPA_PUBLICKEYBYTES)
#define NTRU_OWCPA_BYTES          ((NTRU_LOGQ*NTRU_PACK_DEG+7)/8)

#define NTRU_PUBLICKEYBYTES  (NTRU_OWCPA_PUBLICKEYBYTES)
#define NTRU_SECRETKEYBYTES  (NTRU_OWCPA_SECRETKEYBYTES + NTRU_PRFKEYBYTES)
#define NTRU_CIPHERTEXTBYTES (NTRU_OWCPA_BYTES)

#endif
