<p align="center">
    <img src="./resources/banner1.png" alt="project banner" width=100%>
</p>


# Overview

## Nvidia Omniverse<sup>TM</sup>

## Nvidia Omniverse<sup>TM</sup> Connect



## Pixar USD

![USD image](https://graphics.pixar.com/usd/release/api/USDLogoLrgWithAlpha.png)

Part of the magic of Nucleus is the implementation of Pixar's open source 3D scene description and file format called ==**Universal Scene Descriptor**== (or **USD** for short). A high performance, easily extensible format for content creation adopted in different disciplines because it provides a robust interchange between digital content creation tools. Working in the game industry, being able to collaborate in real time with other people of different teams, while being able to have a fluid working pipeline is a game changer that USD has brought upon the table of digital creation industries.



![USD Proccess](./resources/USD1.png)
_You can find more information on USD in the official page **[HERE](https://graphics.pixar.com/usd/release/index.html)**_


USD contains the information of what we could call a "Scene" (depending on the application, you may have heard some words like, scene or scenegraph or level, or map or world) that contains a list of objects that "populate" the world. We could call this a graph that can have several levels in which objects can nest or "parent" other objects (hence the name "SceneGraph"). This objects contain information that define how they look, act or react with other objects in the scene. This could be something like Geometry (to create models like houses, or characters, or a simple cube), Materials (that will show the geometry and how it looks), even Physics (will it bounce if it crashes? will it just fall into the void?). All this information is stored in the USD as a graph that lists all the objects and their properties[^1].



Nvidia Omniverse has pre-built libraries so one can access and work with USD files, either with Python or C++. For this tutorials, we will be focusing on the C++ aspect of USD.

[^1]: You could read more of this in books like 

[![Back to Index](https://img.shields.io/badge/Back%20to%20Index-<-red)](./MAIN.md) [![Installation](https://img.shields.io/badge/Installation->-green)](./INSTALLATION.md)
