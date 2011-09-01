/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

*******************************************************************************/

XCode4 Users:

  Make a new workspace and add the project in
    shared/DSPFiltersDemo/Builds/XCode4/

  Output files go into DerivedData like usual.

  Instructions to customize shared build settings is in
    user/settings/XCode4/

--------------------------------------------------------------------------------

Visual Studio 2008 Users:

  Open the workspace located in
    user/Workspaces/VisualStudio2008

Visual Studio 2010 Users:

  Open the workspace located in
    user/Workspaces/VisualStudio2008

All Visual Studio Users:

  Intermediate and Product files will be placed in a new
  directory in the same place as the solution. The name of
  the directory is "$(SolutionName)-Output"

  To create your own workspace for the demo (if you want it
  outside the repo, or you want to add it to your existing
  workspace), add all three of the project files appropraite
  for your IDE. Then choose Project->Project Dependencies and
  make DSPFiltersDemo dependent on DSPFilters and JuceAmalgam.

  It is also possible to add DSPFilters and/or JuceAmalgam to
  your workspace without the demo. Both produce static libraries
  and neither is dependent on the other.

  If you want to customize the own build settings (.vsprops and
  .props files), make a copy of the user/ directory that is not
  connected to the svn repo (for example, delete all the hidden
  .svn directories), and change your DSPFilters working copy root
  to "trunk/shared" instead. Put the "user" directory in the same
  directory that contains the "trunk/shared" working copy. Now you
  can check the "user" directory into your own private SVN repo
  and play with the build settings (and copy them to your own
  private projects). When you update and rebuild DSPFilters, it
  will use your settings instead.

  I use the svn:externals in my private repo so that DSPFilters
  looks like a seamless part of my repository even though it is
  hosted on Google Code. Using the technique of connecting your
  working copy to "trunk/shared" and adding it to svn:externals
  of your private repo, you can now add the copy of the "users"
  directory with your own property sheets to your private repo
  as I have done. When you do an "svn update" on the root of your
  repo, you will automatically pick up DSPFilters changes,
  including changes to the project files, and when you build it
  will continue to use your customized property sheets.

  This works for all builds, including the MacOS and iOS ones.
