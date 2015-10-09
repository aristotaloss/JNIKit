# JNIKit
JNI C++ interaction kit to alleviate the pain a bit.

## Info
JNIKit is a small project to help you interact with running or new JVM instances by wrapping around the JNI C++ interface and providing a much cleaner and object-oriented approach on the API. See below for examples to get an impression.

## Example use

Let's imagine we'd hook into a running VM and would want to do stuff with a class we know:

```
JNIKit kit = JNIKit::attachAny(); // Pick the first running VM we can find
JavaClass *myClass = kit.getClass("my/package/MyClass"); // Load my.package.MyClass
// .. do something with myClass now.
```

Easy, eh? What about altering a static field:

```
JavaField *myField = kit.getStaticField("my/package/MyClass", "myField", "Ljava.lang.String;"); // Resolve..
myField->set(nullptr); // Set the field to null.. or whatever you wish to set it to.
```

A breeze. All the ugly `jclass` and `jobject` and the likes are done under the hood. You get to work with the pretty classes.
