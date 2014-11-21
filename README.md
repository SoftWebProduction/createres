createres
=========

Game resource packer

To compile with CodeBlocks under Linux or Windows simply use 'main.cpp' and 'loadResource.cpp'.

To compile with Visual Studio, you need to include and compile also the VC folder contents.
___
usage:

```createres < option > < option >```

```-f   Output file name```

```-p   Folder containing the images or sounds to pack.```

Example:

```createres -f resources.dat -p DATA```
   
   where DATA is the folder with the resources
