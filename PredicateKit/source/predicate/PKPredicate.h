// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

/**
 * A predicate.
 */
@interface PKPredicate : NSObject

-(BOOL)validate:(NSError **)error;
-(id)evaluateWithObject:(id)object;

@end

