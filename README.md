# (k)povmodeler

## 27.10.2019
Today I decided that the newui is the way to go. So I merged it over into the master branch.
This may be not the way project trees are handled, but it makes me somewhat nervous always working on the branch. As long as I am alone here, its no problem anyway.
It is still in the beginning. But I learned much things about the old code.

For now I initialize the model tree, can load model files and have a recent files list.
I have a plan how to organize the needed property edit widgets. They are needed for all model classes, and thats a huge mass of code. This needs planing for not to fail here.

Anyway that I believe that the original model code can be reduced easily by more than 50% I let it stay as it is because it works.
Changing the model code as well will only be done if something will not work anymore, e.g. for new features. But for new features there will be a long way to go.

## 23.10.2019
Working on a branch I extracted the model tree classes in a way that makes them complete independent from the GUI.
This does not mean that there are no Qt-classes involved, but nothing that has to do with the user interaction.

I did load a test model, a very small one, and it seems everything available. 

The same I did with the base classes that I alrady moved into its own directory. They are independent from the gui or model now.

Doing so much changes to the core functions means that the branch has no working gui at the moment. But now it can be started with that.

## Start 

I am trying to make the KDE povmodeler work again even it has been develop over a decade ago.
My work has been forked from https://github.com/eticre/povmodeler as this code has already been stripped of the KDE specific parts and ported to Qt5.

I think it is a very good starting point to wakeup the many features and ideas already implemented/designed.

The actual code base uses cmake to build the program but I stripped the installation part as it did not realy work for the different plattforms.
But for the start I need something that creates a debug version and that I do understand. I prefer plain makefiles but its always good to learn something new.
So I focused on the splitting the code into several functional units to get a better view into the architecture.

Dont know how long it needs to come along with a good working system. But the first step is always the hardest.

## Installation

As I tried to compile the povmodeler on an OpenSUSE I found that it needs

freeglut
freetype2

besides some development headers for Qt5. But it compiled but had a problem within my VM installation with the OpenGL viewport creation.
