# Micro3Dengine

[![Watch the video](https://img.youtube.com/vi/ih32bu80fII/hqdefault.jpg)](https://www.youtube.com/watch?v=ih32bu80fII)

The **Micro3Dengine** is a simplified software 3D engine designed to run on microcontrollers. It is written from scratch with the necessary Vector3D and Matrix3x3 and a ProjectionMatrix classes so that it does not require any dependency other than the hardware TFT class to run on microcontrollers. The classes have been written as templates to be used with the appropriate type for the environment, the engine also includes a proprietary fixpoint number class, which allows the engine to run more optimally in environments where there is no hardware floating point support. (FixPoint class is not yet fully tested out, so there may be bugs.)
The development of the engine started first in STM32 environment, and was then partially ported to PC, speeding up development and testing. The aim is to make the 3D engine, now developed on PC, usable on any microcontroller. The engine itself is located in the Micro3D engine library, the rest of the project is creating a virtual embedded system environment to run on PC, such as VirtualTFT, which is based on SDL2library. In the microcontroller environment, only the content of Micro3Dengine folder is used.
Important note: The project including the demo project does not use dynamic memory management, because it can cause memory fragmentation in many embedded environments, so the code may not be nice, not the most optimal solution is used everywhere, but the demo can be compiled to embedded environment with minimal modifications.

[![Watch the video](https://img.youtube.com/vi/ilHwLmvpWWk/hqdefault.jpg)](https://www.youtube.com/watch?v=ilHwLmvpWWk)

**How it works (similar to a standard 3D engine):**
Objects are represented by Object3D classes, the mesh is stored as vertices and faces (triangles).
Objects can be set in offset, rotation and scaling properties, then by calling ObjectToWorld method, the object is placed in the set position and orientation in the world space. If desired, the backfaceculling option can also be set here.

The normal vector of the faces (triangles) transferred to the WorldSpace is also defined, which is both an input parameter to the backfaceculling function and is used in the illumination calculation.
The faces (triangles) placed in WorldSpace are then projected into 2D space using the projection matrix.
From this point on we have face objects with x,y coordinates in 2D space, no z coordinates converted (no NDC projection either) and a normal vector.
The resulting 2D triangles are sorted by their z coordinate, so the triangles further back in space are drawn first. (Later, with the implementation of the z buffer, this feature becomes unnecessary.)
The original engine for STM32 included the zbuffer implementation and scanline rendering, this has not been moved to this project yet, but will be coming soon.
It is important to note that the 3D engine is responsible for moving, rotating and scaling objects and then projecting them into 2D space, and the rendering engine is responsible for drawing and rendering the resulting 2D faces.

Rendering can be done in frame buffer and line buffer. The current project and demo uses the frame buffer solution, but the original STM32 engine uses the line buffer and scanline algorithm, soon the scanline renderer will be added to this project.

**So a summary of the operation:**
1. object3D (verticies and faces) in model Coordinates
2. rotation, scaling and translation
3. objectToWorld (with backfaceculling) to worldCoorinates 
4. project Faces to Screen. Projection Matrix is simplified for embedded using and projects coordinates 

**Which is not yet implemented:**
•	Camera: this is just a camera matrix, which matrix can be merged with the WorldMatrix, will be implemented soon
•	Currently rotation, translation and scaling operations are not merged in ObjectToWorld method, this will be merged soon. 
•	Z buffer
•	Clipping this may not be implemented, as it may not be necessary for a scanline renderer, or a simpler implementation may suffice.

