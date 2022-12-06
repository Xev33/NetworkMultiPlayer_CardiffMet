# Cross Platform Replication Wrapper

This is a small cross platform (and hopefully fairly general) replication wrapper (plus ~~some~~ almost no testing), most of the core code is based on [Multiplayer Game Programming: Architecting Networked Games](https://www.oreilly.com/library/view/multiplayer-game-programming/9780134034355/) - by Josh Glazer.  This project is looking to extract out the core library allowing students in the third year Multi-Player Game Development module to use it in their own games having read the relevant book chapters.

**Windows Bug / Feature**
As of 9/22 building using the cmake-gui (and VS 2022 project files) is recommended, building via Visual Studio 2022 fails due to an unescaped % in the ninja build file produced by CMake.  

**Updated 4-1-2022:** 
- Moved to using the FetchContent plugin for gtest. 
- Moved top level CMake to the root of the project (this seems to be the convention). 

## For Students ##

Be sure to fork then clone with: ```git clone --recurse-submodules https://USERNAME@bitbucket.org/smu_sc_gj/crossplatformreplication.git``` or just add ```--recurse-submodules``` to the clone command provided by Bitbucket. 

<!--
## Plan ##

Need to write this somewhere so I don't forget short term.

Plan to add to this:
* Types of packet (means of identifying transmitted information)
* Replication Manager
  * Naieve World Replication
  * Delta based
* RPCs
* MVE for streams of objects

Remove:
* Unrelated test stuff concerning serialisation etc.
-->
## Targets ##

### Libraries ###

**networking** - TCP/UDP networking library and supporting data structures.  This is a wrapper around BSD Sockets and WindSock which should work across platforms.

**serialisation** - Serialisation for both basic and complex types. 

**maths** - A very basic 2D maths library

**engine** - Game Engine components, also game elements such as inputs, moves etc. sent across the network.  

**replication** - Game object registration, delta world and object replication. 

**strings** - Error logging etc.

### Executable Targets ###

**client** - Game Client, note this is composed of library classes including client versions of some of the networking components such as Network Manager. 

**server** - Game Server, note this is composed of library classes including server versions of some of the networking components such as Network Manager. 

**NetworkGame_test** - Google Tests for the various components. 

## Known Issues ##
1. Testing is incomplete
	- Linux Testing - **DONE**
	- Windows Testing - **DONE**
		- Works on lecturer machine with much faffing, need to work out procedure for the rest of the lab machines.
		- Hopefully just a question of opening ports and restarting firewall. 
		<!-- Need to link install guide for this -->
2. Some tests won't work on the university network
	- ~~Connect -- tries to contact an external 'echo' server.~~
	- Works provided windows/linux local network services are running on the machine. 
		- [Linux](http://www.yolinux.com/TUTORIALS/LinuxTutorialNetworking.html#INET)
			- Some linux distributions no longer provide these servers, so we have to make our own. See [here](https://nmap.org/ncat/guide/ncat-simple-services.html) <!-- Glenn ... make a script for this -->
		- [Windows](https://www.windows-security.org/windows-service/simple-tcpip-services)
3. Some tests require manual input
	- Listen -- waits for a connection on port 54321
	- Echo tests for TCP/UDP
	- **CTest** integration will mark these as failed unless the info can be sent (does all the tests at once!). 