# How to import assets (images, music, etc...) into monogame.

## Windows
1. With the project open in Visual Studio...

1. Under the Content folder in the solution explorer, right click on Content.mgcb and select "open with..." select "Monogame Pipeline Tool (Default)" and set as default and then click OK.

1. Double click on content.mgcb icon.

1. Select Content under Project and make sure that in the properties table it's platform value is "DesktopGL".

1. Right Click on the monogameContent Symbol under Properties and select "add" -> "existing item".

1. Navigate to the asset file or files you want to import, select them and choose "open".

1. Now click save and then click build.

1. Close the pipeline tool.
  
1. Now right click on the Content folder and select add existing item. (LINUX = Add Files)

1. Navigate to Content -> bin -> DesktopGL -> Make sure that you  "Show all file types" -> select desired file types

1. You are done.

## Linux
1. With the project open in MonoDevelop...

1. Under the Content folder in the solution explorer, right click on Content.mgcb and select "open with..." select "Monogame Pipeline Tool (Default)" and set as default and then click OK.

1. Double click on content.mgcb icon.

1. Select Content under Project and make sure that in the properties table it's platform value is "DesktopGL".

1. Right Click on the monogameContent Symbol under Properties and select "add" -> "existing item".

1. Navigate to the asset file or files you want to import, select them and choose "open".

1. Now click save and then click build.

1. Close the pipeline tool.
  
1. Now right click on the Content folder and select add files.

1. Navigate to Content -> bin -> DesktopGL -> Make sure that you  "Show all file types" -> select desired file types

1. You are done.
  

## Mac

1. Run Monogame pipeline tool.

1. Using the pipeline tool open content.mgcb in the Content folder of your project.

1. Click on the icon to verify the appropriate OS

1. Select "Add Existing Item"

1. Navigate to the item desired

1. Copy the file to the directory

1. Build

1. Save 

1. Close the pipeline tool

1. Now Under the Content folder in your project select "Add Existing Files"

1. Content -> bin -> OS -> Show all file types.

1. Select the file. It should be called something like \<filename\>.xnb

1. Copy the file.
  
  
 