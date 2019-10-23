# (k)povmodeler

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
