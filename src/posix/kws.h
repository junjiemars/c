#ifndef _KWS_H_
#define _KWS_H_

#if !(NM_HAVE_RESTRICT_KW)
#  if (NM_HAVE___RESTRICT_KD)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif


#endif /* end of _KWS_H_ */
