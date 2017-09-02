# C Lessons

It is not **C Lessons** at all :). I'd programming in C long long time ago, 
sometimes I want to pick something up, but I cannot find the peice of code 
somewhere or cannot run the code on a machine that been wrote in another machine. 

Sadly, old dog need learn something new
* Access the code from anywhere, oh, GitHub is good one
* Run or write code on anywhere, so Linux, Darwin, or Windows, Docker Box
* Easy to try and learn something new

Now, we had [Nore](https://github.com/junjiemars/nore), something changed and 
something not.


## Hot to Play
```sh
# <where> to put nore down
$ PREFIX=<where> bash <(curl https://raw.githubusercontent.com/junjiemars/nore/master/bootstrap.sh)

# configure -> make -> install
$ ./configure --has-hi
$ make
$ make install

# update nore, <what> you want to make
$ ./configure --update --has-<what>
```


## Vim Basic Skills 

* show variable state: ```:verbose set <var>?```
* open ```:clist``` after ```grep```: ```:copen```
* switch to previous/next buffer: ```:bp``` and ```:bn```
