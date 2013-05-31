# Predicate Kit
**Predicate Kit** is an Objective-C implementation of a general-purpose, expression-oriented programming language – which is somewhat predictably named **Predicate Kit Language** (or PKL). PKL takes inspiration from `NSPredicate` and is used to evaluate expressions in the context of an object, for example:

	NSDictionary *context = /* assume this exists */;
	PKPredicate *predicate = [PKPredicate predicateWithSource:@"name =~ /^Joe/" error:&error];
	id result = [predicate evaluateWithObject:context];

## Predicate Kit / NSPredicate

Predicate Kit differs from NSPredicate is some important ways:

 * Despite what its name might imply, PKL can evaluate to any type, not just a boolean as `NSPredicate` requires. The expression `2`, for example, is perfectly valid and will yield the equivalent of `[NSNumber numberWithInt:2]`.
 
 * Predicate Kit works hard to provide useful errors when compliation or evalutation of an expression fails. Unlike `NSPredicate`, it provides an `NSError` object instead of throwing exceptions and [crashing your app] [1].
 
## For example...
Suppose you want to allow a sophisticated user to enter a query expression which you will use to filter a set of objects by:

	message.subject =~ /^Prefix/ && message.unread == true

You can compile this expression into a predicate and use it to filter a collection of messages in a very expressive way:

	NSArray *messages = /* assume this exists */;
	NSError *error = nil;
	
	PKPredicate *predicate = [PKPredicate predicateWithSource:userProvidedSource error:&error];
	if(predicate == nil) /* handle this error */
	
	for(Message *message in messages){
		id result = [predicate evaluateWithObject:message error:&error];
		if(result == nil){
			/* handle this error */
		}else if([result isKindOfClass:[NSNumber class]] && [result boolValue]){
			/* this message matches! */
		}
	}
	
Awesome! All is well.

## Error handling

Now let's assume that instead of the expression above, the user enters this:

	message.sujbect =~ /^Prefix/ && message.unread == true
	
Your `message` object doesn't have a property named `sujbect` – that's a typo. If you're using `NSPredicate` to evaluate that expression, you're going to get something like:

	[<SomeClass 0x100397ce0> valueForUndefinedKey:]: this class is not key value coding-compliant for the key sujbect.

… and then your app is going to crash. Lame.

Predicate Kit, on the other hand, allows you to handle this not-uncommon case elegantly. We can do the following during evaluation:

	id result = [predicate evaluateWithObject:message error:&error];
	if(result == nil){
		
		// display the error message
		NSLog(@"error: %@", [error localizedDescription]);
		
		// display the offending source excerpt with a '^^^' underline
		PKSpan *span;
		if((span = [[error userInfo] objectForKey:PKSourceSpanErrorKey]) != nil){
		    PKSpanFormatter *formatter = [[PKSpanFormatter alloc] init];
		    [formatter printCalloutForSpan:span stream:stderr];
		    [formatter release];
		}
		
		// bail out here
	}

Which will print the following useful message to standard error:

	error: No such property 'sujbect' of <SomeClass 0x1005a1cc8>
	message.sujbect == "Hello" && message.unread == true
            ^^^^^^^

`PKSpanFormatter` will let you easily extract  line, column, excerpt, and other information about the region of the source that produced an error. Using that, you can present useful errors to the user in whichever way makes sense.

[1]: http://developer.apple.com/library/mac/#documentation/Cocoa/Conceptual/Exceptions/Exceptions.html