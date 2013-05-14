// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

@class PKExpression;

/**
 * A predicate parser.
 */
@interface PKParser : NSObject

+(PKParser *)parser;

-(PKExpression *)parse:(NSString *)source error:(NSError **)error;

@end

