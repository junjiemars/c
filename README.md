# C Lessons
It is not **C Lessons** at all :). I'd programming in C long long time ago, sometimes I want to
pick something up, but I cannot find the peice of code somewhere or cannot run the code 
on a machine that been wrote in another machine. 

Sadly, old dog need learn something new
* Access the code from anywhere, oh, GitHub is good one
* Run or Write code on anywhere, so Linux, Darwin, or Windows, Docker Box
* Easy to try and learn something new


## Philosophy of Building System
The key question is how to build C code in variant OS environments by variant Compilers. 
Before I do the job, how [Nginx](https://www.nginx.com/resources/wiki/#)
build itself is the question that I always think about it: Nginx build itself 
from bottom to up and final is holy big one, but what about individual's freedom? 
so it is not the answer. 

The **C Lessons** build a set of basic rules first then let 
the individual units (call it **stick**) to build itself, it's up to bottom follow.

There should be some basic rules which face to variant building environments. 
And there must be individual units which decide how to build itself base on or not
the baisc rules.

What about **Shell** and **Make**: Make run in shell and Make controls building rules.
So the natrual way: shell controls the basic rules which use to build the basic Makefiles 
then let make play with **sticks**' Makefiles. Paul Smith in [Rules of Makefile](#http://make.mad-scientist.net/papers/rules-of-makefiles/)
said:
> Don’t hassle with writing portable makefiles, use a portable make instead!

## Hot to Play
```sh
$ git clone https://github.com/junjiemars/c_lessons.git

$ auto/configure --has-hi
$ make
$ make install
```


## C Lessons
This part is the **Lessons** indeed, ... Quiet!


