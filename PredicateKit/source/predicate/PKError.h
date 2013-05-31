// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

typedef enum {
  PKStatusOk            =  0,
  PKStatusError         = -1,
  PKStatusCount
} PKStatus;

#define PKPredicateException    @"PKPredicateException"
#define PKPredicateErrorDomain  @"PKPredicateErrorDomain"
#define PKSourceSpanErrorKey    @"PKSourceSpanErrorKey"

/** Create an NSError the easy way */
#if !defined(NSERROR)
#define NSERROR(d, c, m...) \
  [NSError errorWithDomain:(d) code:(c) userInfo:[NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:m], NSLocalizedDescriptionKey, nil]]
#endif

/** Create an NSError the easy way */
#if !defined(NSERROR_WITH_SPAN)
#define NSERROR_WITH_SPAN(d, c, s, m...) \
  [NSError errorWithDomain:(d) code:(c) userInfo:[NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:m], NSLocalizedDescriptionKey, (s), PKSourceSpanErrorKey, nil]]
#endif

/** Create an NSError the easy way */
#if !defined(NSERROR_WITH_FILE)
#define NSERROR_WITH_FILE(d, c, p, m...) \
  [NSError errorWithDomain:(d) code:(c) userInfo:[NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:m], NSLocalizedDescriptionKey, (p), NSFilePathErrorKey, nil]]
#endif

/** Create an NSError the easy way */
#if !defined(NSERROR_WITH_URL)
#define NSERROR_WITH_URL(d, c, u, m...) \
  [NSError errorWithDomain:(d) code:(c) userInfo:[NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:m], NSLocalizedDescriptionKey, (u), NSURLErrorKey, nil]]
#endif

/** Create an NSError the easy way */
#if !defined(NSERROR_WITH_CAUSE)
#define NSERROR_WITH_CAUSE(d, c, r, m...) \
  [NSError errorWithDomain:(d) code:(c) userInfo:[NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:m], NSLocalizedDescriptionKey, (r), NSUnderlyingErrorKey, nil]]
#endif


