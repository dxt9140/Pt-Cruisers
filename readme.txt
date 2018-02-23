readme.txt
Author: Dominick Taylor (dxt9140@g.rit.edu)

This program is a multi-thread progrma in C using pthreads. It is quite old,
and my then unpracticed self forgot to include documentation! Thus, I am not
perfectly certain how it works. However, it is only two classes. pt-cruisers 
creates and runs each racer as a thread. racers serves as the thread class and
runs. Each time the racer gains distance, there is a random chance the engine
will fail and the racer won't continue. Who will win? Who will reach the end
first? Run the program and find out!

Execution:

	$> ./pt-cruisers <delay> [racer names]
	$> ./pt-cruisers [racer names]

	delay should be the number of milliseconds to wait after each run of
	    the cruisers. This is an optional parameter.
	racer names is any number of racers. Each racer can have any 8-character
	    string.

Note:
	Once again, this is just a fun project. I do not claim this to be my best
	code, nor at the level of my current code. 
