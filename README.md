# SNAIL
## About
* This is mostly a personal learning project of mine. 
* SNAIL can load from a file and render a scene with OpenGL.
* You can also move the objects in real-time with the program (Saving the changes is to come).

## How to use it
* To create a scene, for now, you need to write the code that SANIL interprets. 
* To create a scene, for now, you need to write the code that SANIL interprets. 
The resource.snres file handles all the shaders, models, textures, and the project name. You use this file among the scene files.
* The .snsc file handles the scenes, in them, you add **GameObjects** (named GO inside the file) **Light**, **CubeMap** with the "**+**" operand.
* You have o close all **+** with a **|** operand followed by the object name *except* the **CubeMap** creation, that you close with the name of the texture to use on the cube map name, referenced in the resource file.
* Inside de creation of the game object, you can choose the position, shader, model, size, the camera to use. Some of those like model and shader are referenced from the resource file, to save memory.

### On Model Loading
* This program uses [Assimp](https://github.com/assimp/assimp) to load models, for now, the best file type is .obj.
* All used textures need to be in the same folder as the object. See the examples inside the "models" folder.

## 3rd Party Tools Used
* For the model loading, I am using [Assimp](https://github.com/assimp/assimp).
* For the GUI I am using [ImGUI](https://github.com/ocornut/imgui).
* For window rendering and inputs I use [GLFW](https://github.com/glfw/glfw).
* For openGL operatoin loader I am using [GLAD](https://github.com/Dav1dde/glad)
* [GLM](https://github.com/g-truc/glm) is used for mathematical calculations
* **_Thanks for all the forementioned Tools_**
