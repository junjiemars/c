#ifndef _RESTRICT_H_
#define _RESTRICT_H_

#if !(NM_HAVE_RESTRICT_KW)
#  if (NM_HAVE___RESTRICT_KD)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif


#endif /* end of _RESTRICT_H_ */
