YOCTO PROJECT:
--------------
Opensource hosted by Linux Foundation and supported by Silicon and OS vendors 
Helps build custom Linux OS for Embedded devices
Can create Linux images for all major HW architectures such as x86, PPC, ARM, MIPS
Provides high degree of Flexibility and customization
Reuse SW stack across wide range of HW platforms enabing boot and performance optimization

Build System Overview:
+++++++++++++++++++++
Poky = Bitbake(Executes and manages build steps) + Metadata(What gets built and how to build)
Poky : Build System used by Yocto
Bitbake : Task Executor and Scheduler
Meta data: Task definitions for Bitbake
	-Configuration(.conf) : Global definition of variables (PATH, Compiler flags, machine architecture etc.,)
	-Classes(.bbclass) Encapsulation and inheritance of build logic, packaging(How to build Linux kernel/RPM package/Root file system etc.,)
	-Recipes(.bb) - Logical units of SW/images to be built. What packages to be included in the final image defined in Recipes. (Recipe for GNU Tar command, GTK library etc.,) : Where to obtain upstream source packages, what patch version to apply, build and runtime dependencies, Features to be enabled, choose where files are to be placed in a package(Say, libraries vs documentation)
	
Builds everything from source(HTTP server/Local path/Source control Management toos such as Git, Subversion). First build could take significant amount of time.
Generates Custom Linux image with configud packages included as well as an SDK to help cross-compile applications/libraries

Y3.1 - Dunfell(LTS)
git pull -b <code_name> /

Some STD image recipes:
core-image-minimal
core-image-base
core-full-cmdline
core-image-x11 : x11 based gui
core-image-sato
meta-toolchain : To build tool chain


SW Design:
----------
Functional Requirements : Requirements from user point of view
Non functional requirements : NOt directly related to feature like performance, battery, data usage, legal(sensitive data), documentation and support


Class Digram:STATIC DIAGRAM
--------------------------
- Class Name : stereotyped if interface <<interface>>
- Attributes : {Visibility : public(+), private(-), protected(#), package/namespaces(~)}
- Operations : {in/out/inout} Example : setValue(in inputVal : int) : void

[Cardinality/Multiplicity] : 1, 0..1, 0..*(Same as *), 1..*, m..n(custom)
 
Association/Aggregation/Composition :
[Association/Aggregation] : Aggregation is redundant with Association. Association denoted by a "Solid line" and aggregation denoted by "Solid line with a hollow diamond head". [has-a] relationship. Example : [Car & Wheel]
[Composition] : Type of Aggregation indicating strong ownership. One dies with another. Represented via a "Solid line with a filled diamond head". [part-of] relationship. Example : [Book & Chapter]
[Realization] : Represented via a "Dotted line with hollow triage head" and captures relationship between an interface class(<<interface>>) and implementing class
[Generalization] : Indicates relationship between parent and derived class. Represented via a "Solid line with hollow triage head". [is-a] relationship. Example : [Share & Circle]
[Dependency] : Class references another. Represented via "Dotted line with arrow head".

Sequence Digram:DYNAMIC DIAGRAM
----------------
Interaction between classes

Use case diagrams:
------------------

Activity Diagram:(Workflow/Business processes)
----------------------------------------------
- Nodes : Represents action
  Initial NOde       : Black filled circle
  Normal Action Node : Square
  Decision Node      : Diamond with single inbound flow and multiple outbound flow with guards{[if <condition>], [else]}
  Merge Activity Node: Diamond with multiple inbound flow with guards{[if <condition>], [else]} and single outbound flow.
Supports concurrent flows via [fork] and [join] which are represented as THICK horizontal lines
  FORK : Single incoming flow and several outgoing parallel flows(Actions) 
  JOIN : Multiple incoming parallel flows(Actions) and single outgoing flow(Action)
  Final Node : Filled Circle placed inside a bigger hollow circle
- Flow(Edges) : Flow of control between actions


State chart Diagram:(Workflow/Business processes)
-------------------------------------------------
SMC(State Machine Compiler)

[STATE] : Current condition of an object
[TRANSITION] : Object switches state
[EVENT] : Triggers state transition


