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
Suppose you want to allow a sophisticated user to enter a query expression which you will use to filter a set of objects by. And suppose you build this feature and a user enters the following:

	message.sujbect == "Hello" && message.unread == true

Your `message` object probably doesn't have a property named `sujbect` – that's a typo. If you're using NSPredicate to evaluate that expression, you're going to get something like:

	[<SomeClass 0x100397ce0> valueForUndefinedKey:]: this class is not key value coding-compliant for the key sujbect.

… and then your app is going to crash. Lame.

Predicate Kit, on the other hand, works hard to give you useful error information. The same example, evaluated with Predicate Kit, would give you an `NSError` object – instead of throwing an exception – which you could use to display something like:

	error: No such property 'sujbect' of <SomeClass 0x1005a1cc8>
	message.sujbect == "Hello" && message.unread == true
            ^^^^^^^

## For example…

	name =~ /^Joe/ && (age >= 21 || booze == false)

The above expression evaluated in the context of an NSDictionary object containing the following:

	{
		name: "Joe Blow",
		age: 30,
		booze: true
	}

Would result in the value `[NSNumber numberWithBool:FALSE]` when compiled and evaluated by Predicate Kit.

[1]: http://developer.apple.com/library/mac/#documentation/Cocoa/Conceptual/Exceptions/Exceptions.html