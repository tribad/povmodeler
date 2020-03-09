# povmodeler

## 09.03.2020
As of the analysis of the original code I came to the conclusion that it has a way to large complexity. Many components have been developed at times where memory consumption and computational power has been not that huge as today. So the architecture and design decision have been good at its time.

With the newui try I tested myself whether I would be able to handle Qt and to check how hard it would be to stay on the old code. Unfortunatly I found that I was right with my first assumptions. To extend the code and may make the povmodeler fit for some more years to be in use would be very hard.

In times of blender/maya and others a new "modeler" for povray makes no sense as the old povmodeler still works, more or less. So what make povray exceptional to others? Why do I stick on povray despite the fact that it is somehow inconvenient to handle with its text files? 

Animations! 

But even that is somehow inconvenient as it is allways a mess to get the camera movement the right way, the objects at their positions or let them move the way I think. Here a modeler may have a chance to live some more years.

So what next?

I started to make it anew. First moved all old code out of the way and freshened the repository. Trying to make it some more organized. So that is the thing for now.



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
