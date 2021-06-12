UniEngine

====================================================================

The development of UniEngine is moved to a new repo edisonlee0212/UniEngine-dev, with cross-platform support by CMake. I will not update on this repo anymore.

====================================================================
Project description: This is a framework that can be used to develop games or do scientific researches. 

1.	A fully functional Entity Component System (ECS) combined with multithreading to provide the best performance under the era of multi-core CPUs.
2.	A generic rendering framework that will allow: 
a.	Quick prototype / displaying geometries in scene. Develop APIs like Gizmos in Unity: https://docs.unity3d.com/ScriptReference/Gizmos.html.
b.	A full stack of deferred rendering that includes lighting, shadows, SSAO, post-possessing, etc.
c.	A full stack of forward rendering that includes user-controlled shading, lighting, shadows, etc. Develop APIs like Graphics in Unity: https://docs.unity3d.com/ScriptReference/Graphics.html
3.	Integrated industrial proven physics engine PhysX to provide stable and good physics simulations.
4.	Integrated ImGui with docking, multiple viewport features enabled to provide good editor experiences.
5.  An engine editor that allow user to create/edit/save/load the scene.

What additional components or libraries will you rely on?
Here is a list of libraries that I will use in the project:
1.	Assimp: Provides features related to asset/model loading.
2.	Glm: Provides math calculation.
3.	ImGui: Provides GUI.
4.	PhysX: Provides physics simulation.
5.	Stb: Provides image loading.
6.	Glfw: Provides windows management.
7.	Glad: Provides OpenGL linking, like GLEW but gives more control and better integration.
8.	vit-vit/CTPL: Provides thread pool that allow the engine to run in multi-threads safely.
https://github.com/vit-vit/ctpl

Primarily I use this project to experiment different technologies in computer graphics. I also use the framework for my own researches, and those research projects are private, but please feel free to use the UniEngine anyway you want to. 
