Perturb SDR
===========

About
-----
An ambitious project to develop a simple and straigtfoward, 100% free, software 
defined radio written in c++. Auxillarly goals include developing an fixed point
version of the library aid in porting to embeded platforms. 

Currently the library is under going haphazard development and the API is 
nowhere near stable. I expect the API and the features included to change as 
development continues. 

Compiling
---------
I have yet to write an cmake file to compile this whole project. I will write 
one eventually though it is not an top concern yet since there are not many 
inter-dependencies.

Unit Tests
----------
The plan is eventually to have an unit test for each part of the library. 
Hopefully, these unit test will help catch implementation errors and aid in 
porting to different numeric formats. 

FAQ
---
* Why not just use GNU radio  
Becuase I do not view the GNU license as free and I am using this project to 
teach myself DSP techniques, specifically Software Defined Radio. Also, I also 
have ambitious goals of porting parts of my code to ARM processors. Porting GNU 
radio to an fixed point implementation would require understanding their code 
and I am busy and already have too much to do.

* I want feature X  
Then email me and I will consider if adding it fits within the libraries 
philisophy and if I have time and know how to do it. Otherwise, go ahead and 
add feature X and submit it back to the library. 
