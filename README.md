UniEngine

Project description: This is a framework that can be used to develop games or do scientific researches. 

Final deliverables:
1.	A fully functional Entity Component System (ECS) combined with multithreading to provide the best performance under the era of multi-core CPUs.
2.	A generic rendering framework that will allow: 
a.	Quick prototype / displaying geometries in scene. Develop APIs like Gizmos in Unity: https://docs.unity3d.com/ScriptReference/Gizmos.html.
b.	A full stack of deferred rendering that includes lighting, shadows, SSAO, post-possessing, etc.
c.	A full stack of forward rendering that includes user-controlled shading, lighting, shadows, etc. Develop APIs like Graphics in Unity: https://docs.unity3d.com/ScriptReference/Graphics.html
3.	Integrated industrial proven physics engine PhysX to provide stable and good physics simulations.
4.	Integrated ImGui with docking, multiple viewport features enabled to provide good editor experiences.

What additional components or libraries will you rely on?
Here is a list of libraries that I will use in the project:
1.	Assimp: Provides features related to asset/model loading.
2.	Glm: Provides math calculation.
3.	ImGui: Provides GUI.
4.	PhysX: Provides physics simulation.
5.	Stb: Provides image loading.
6.	Glfw: Provides windows management.
7.	Glad: Provides OpenGL linking, like GLEW but gives more control and better integration.
8.	gallickgunner/ImGui-Addons: Provides the file dialogs
https://github.com/gallickgunner/ImGui-Addons.
9.	vit-vit/CTPL: Provides thread pool that allow the engine to run in multi-threads safely.
https://github.com/vit-vit/ctpl

Related work.
1.	ECS design: 
The design of ECS is from the DOTS stack from Unity. Detailed information can be found from: https://unity.com/dots
The breakdown of the core concept, entity component system, or more deeply, the data-oriented programming, can be found from Mike Acton’s presentation on CppCon 2014 (Mike Acton actually got hired by Unity and designed the basic of their ECS): https://www.youtube.com/watch?v=rX0ItVEVjHc.
Note: The Unity is not open source, so I solely developed all the ECS without any help. However, I do not create the idea or the concept.
