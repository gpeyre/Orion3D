/* gettsctime.h */

#ifndef __GETTSCTIME_H__
#define __GETTSCTIME_H__

#ifdef _UNIX_

/* returns the cycle count of the cpu */
void gettsc(long long *cycle);

/* takes in a cycle count, and returns its equivalent in nanoseconds */
/* pbm :  CV++ renvoie : 'long' followed by 'long' is illegal */
long long gettsctime(long long tsc);

#endif /* #ifdef _UNIX_ */


#endif /* gettsctim_h */
