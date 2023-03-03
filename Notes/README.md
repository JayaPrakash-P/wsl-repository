YOCTO PROJECT:
--------------
Opensource hosted by Linux Foundation and supported by Silicon and OS vendors 
Helps build custom Linux OS for Embedded devices
Can create Linux images for all major HW architectures such as x86, PPC, ARM, MIPS
Provides high degree of Flexibility and customization
Reuse SW stack across wide range of HW platforms enabing boot and performance optimization

Build System Overview:
+++++++++++++++++++++
Poky = Bitbake(Executes and manages build steps) + Metadata(Waht gets built and how to build)
Poky : Build System used by Yocto
Bitbake : Task Executor and Scheduler
Meta data: Task definitions for Bitbake
	-Configuration(.conf) : Global definition of variables (PATH, Compiler flags, machine architecture etc.,)
	-Classes(.bbclass) Encapsulation and inheritance of build logic, packaging(How to build Linux kernel/RPM package/Root file system etc.,)
	-Recipes(.bb) - Logical units of SW/images to be built. What packages to be included inthe final image defined in Recipes. (Recipe for GNU Tar command, GTK library etc.,) : Where to obtain upstream source packages, what patch version to apply, build and runtime dependencies, Features to be enabled, choose where files are to be placed in a package(Say, libraries vs documentation)
	
Builds everything from source(HTTP server/Local path/Source control Management toos such as Git, Subversion). First build could take significant amount of time.
Generates Custom Linux image with configud packages included as well as an SDK to help cross-compile applications/libraries






