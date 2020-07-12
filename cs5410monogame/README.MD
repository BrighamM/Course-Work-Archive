# CS5410 MONOGAME

## Think of this as your Table of Contents.

1. If you want to set up your development environment keep reading.

1. If you need the OpenGLProjectTemplate then head into the OPENGL-PROJECT-TEMPLATE directory.

1. If you need the .gitignore file for monogame projects then head into the OPENGL-PROJECT-TEMPLATE directory.

1. If you want/need access to the monogame templates they are located in MonoGameTemplates.zip

1. If you need to know how to import assets into monogame look in the KNOWLEDGE-BASE directory for the HOWTOIMPORT file.

1. If you need to know how to create a monogame project that is cross platform compatible then head into the KNOWLEDGE-BASE directory for the HOW-TO-CREATE-CROSS-PLATFORM-DESKTOP-PROJECT file.

1. If you need Dean's sample projects that work in monogame, then head into the DEAN_MONOGAME_SAMPLES directory.

1. The CROSSERTESTER project is being used as a proof of concept for collaborative work between Windows, Linux and Mac. (Checkout the git log messages, for a better understanding.)

### What follows is the set up guide for development using MonoGame.

## DISCLAIMER!
Use of the dotnet cli will not work! You might get it to run on your machine but that does not guarantee that it 
will run on other machines.


If you can use Windows, then use Windows. Your life will be so much easier, and everything will "just work".


If you use a MAC(nobody is perfect) then you should strongly consider using Windows or virtualbox. 


If you use Linux, the advice is the same, use Windows if at all possible.


If you are unable to use Windows, don't worry. There are paths forward that will permit you to work and develop on your 
preferred OS.

## Windows Dev Environment Set up instructions

1. Download Visual Studio 2019 Community

   https://visualstudio.microsoft.com/vs/

1. Install Visual Studio 2019

1. Download Monogame 3.7.1 for Visual Studio

   https://community.monogame.net/t/monogame-3-7-1/11173
   
1. Install Monogame framework.

1. In Visual Studio go to Extensions > Manage Extensions...

1. Make sure you have Online selected on the left pane.

1. Search for MonoGame.

1. Select the MonoGame Project Templates extension and click Download.

1. Restart Visual Studio to install the extension.

1. When Visual Studio restarts, click Create a new project. The MonoGame templates should show up at the top, if not search for MonoGame in the search bar.

1. ### YOU ARE DONE!!!


## Linux Dev Environment Set up Instructions (UBUNTU 18.04)

### Preamble
As has already been mentioned use Windows if you can, and just follow the above instructions.


VirtualBox is a good options and requires relatively few compute resources.


Otherwise...

1. Follow the guide given here:

   https://community.monogame.net/t/install-monogame-3-7-1-on-linux-mint-19-2-tina-cinnamon/11793

1. Install Mono and Monodevelop

   ```shell
    sudo apt install apt-transport-https dirmngr
    sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
    echo "deb https://download.mono-project.com/repo/ubuntu vs-bionic main" | sudo tee /etc/apt/sources.list.d/mono-official-vs.list
    sudo apt update
    sudo apt-get install monodevelop
   ```

1. Install Monodevelop 7

   ```shell
    wget https://github.com/harry-cpp/monodevelop-run-installer/releases/download/7.3.3.5-2/monodevelop-7.3.3.5-2.run
    chmod +x monodevelop-7.3.3.5-2.run
    sudo ./monodevelop-7.3.3.5-2.run
   ```
1. ### STOP! Now you must open Monodevelop stable. Once it is done close it.

1. Install Monogame
   ```shell
    wget https://github.com/MonoGame/MonoGame/releases/download/v3.7.1/monogame-sdk.run
    chmod +x monogame-sdk.run
    sudo ./monogame-sdk.run
   ```

1. It was found that you may need to have the .NET Core. The following instructions will guide you for installing .NET Core on your machine.

1. The specific instructions depend on what version of UBUNTU you are running. 

1. You need to go to this site and follow the specific instructions for your version of UBUNTU. 

   https://docs.microsoft.com/en-us/dotnet/core/install/linux-ubuntu

1. Here we are including the instructions for UBUNTU 18.04
   ```shell
    wget https://packages.microsoft.com/config/ubuntu/18.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
    sudo dpkg -i packages-microsoft-prod.deb

    sudo apt-get update; \
    sudo apt-get install -y apt-transport-https && \
    sudo apt-get update && \
    sudo apt-get install -y aspnetcore-runtime-3.1

    sudo apt-get install -y dotnet-runtime-3.1
   ```
1. ### YOU ARE DONE!!!

## MAC Dev Environment Setup Instructions

### Preamble
You should really use Windows if you can be it through the tutor lab, virtualization or some other means.

### Otherwise
1. Install Visual studio 2019 community edition.
1. Run the package installer for monogame.
   
   https://github.com/MonoGame/MonoGame/releases/download/v3.7.1/MonoGame.pkg

1. You should go here now,

   https://addins.monodevelop.com/Project/Index/47

   and download two files

   3.6.0.586 (Stable) 

   and

   3.7.0.1 (Beta)

   then got to visualStudio->extensions->install from file, and select and install from both files.

1. ### YOU ARE DONE!!!
