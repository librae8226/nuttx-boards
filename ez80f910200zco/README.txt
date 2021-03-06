README.txt
^^^^^^^^^^

ZDS-II Compiler Versions
^^^^^^^^^^^^^^^^^^^^^^^^

Different configurations have been build for this board using ZDS-11
Versions 4.11.0, 4.11.1, and 5.1.1  You have to check the files */Make.defs
to see how the build is configured:  Check the definitions of
ZDSVERSION (if present) and ZDSINSTALLDIR.

NOTE:  Different versions of the ZDS-II compiler may also require
different versions of .linkcmd and .zdsproj files as well.

Version 4.11.0

  The 5.1.1 version of the ZDS-II tools are currently configured for
  all ez80 boards.  However, it is the older version 4.11.0 that this code
  has been verified against.

  Although it compiles without error, the 4.11.0 compiler generates
  bad code on one of the files, mm/mm_initialize.c.  Below is a simple work-
  around.

    --- mm/mm_initialize.c.SAVE	2008-02-13 08:06:46.833857700 -0600
    +++ mm/mm_initialize.c	2008-02-13 08:07:26.367608900 -0600
    @@ -94,8 +94,11 @@
    {
       int i;

    +#if 0 /* DO NOT CHECK IN */
       CHECK_ALLOCNODE_SIZE;
       CHECK_FREENODE_SIZE;
    +#endif

   /* Set up global variables */

   UPDATE:  I don't know if 4.11.1 has this same problem (I bet not since
   I submitted the bug to ZiLOG), but I have permanently worked around the
   above problem for all ZiLOG compilers.

Version 5.1.1

  On June 22, 2011 I verified that these configurations build successfully
  with the 5.1.1 ZDS-II version.  On November 12, 2012, all of the configurations
  were converted to use 5.1.1, but have not been verified on a running target.

  The above kludge for 4.11.0 is not required with 5.1.1.

  Paths were also updated that are specific to a 32-bit toolchain running on
  a 64 bit windows platform.  Change to a different toolchain, you will need
  to modify the versioning in Make.defs and setenv.sh; if you want to build
  on a different platform, you will need to change the path in the ZDS binaries
  in those same files.

Other Versions
  If you use any version of ZDS-II other than 5.1.1 or if you install ZDS-II
  at any location other than the default location, you will have to modify
  two files:  (1) configs/ez80f910200kitg/*/setenv.sh and (2)
  configs/ez80f910200kitg/*/Make.defs.

Configurations
^^^^^^^^^^^^^^

Common Configuration Notes
--------------------------

  1. src/ and include/

     These directories contain common logic for all ez80f910200zco
     configurations.

  2. Variations on the basic ez80f910200zco configuration are maintained
     in subdirectories.  To configure any specific configuration, do the
     following steps:

       cd <nuttx-top-directory>/tools
       ./configure.sh ez80f910200zco/<sub-directory>
       cd <nuttx-top-directgory>
       make

     Where <sub-directory> is the specific board configuration that you
     wish to build.  The available board-specific configurations are
     summarized in the following paragraph.

     Use configure.bat instead of configure.sh if you are building in a
     native Windows environment.

  3. This configuration uses the mconf-based configuration tool.  To
     change this configurations using that tool, you should:

     a. Build and install the kconfig-mconf tool.  See nuttx/README.txt
        see additional README.txt files in the NuttX tools repository.

     b. Execute 'make menuconfig' in nuttx/ in order to start the
        reconfiguration process.

Configuration Subdirectories
----------------------------

  dhcpd:
    This builds the DCHP server using the examples/dhcpd application
    (for execution from FLASH.) See apps/examples/README.txt for information
    about the dhcpd example.

  httpd:
    This builds the uIP web server example using the examples/webserver application
    (for execution from FLASH). See apps/examples/README.txt for information
    about httpd.

  nsh:
    This configuration builds the NuttShell (NSH).  That code can be
    found in examples/nsh.  For more information see:  examples/nsh/README.txt
    and Documentation/NuttShell.html.

  nettest:
    This configuration is used for testing the eZ80F91 EMAC driver.  It
    builds examples/nettest.  See examples/README.txt for more information
    about nettest.

  poll:
    This configuration is also used for testing the eZ80F91 EMAC driver.  It
    builds examples/poll.  See examples/README.txt for more information
    about the poll test.

Check out any README.txt files in these <sub-directory>s.
