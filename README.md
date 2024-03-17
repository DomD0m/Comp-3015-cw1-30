# Comp-3015-cw1-30
 Comp 3015 30% OpenGL scene within Template.

 Youtube link:
 https://youtu.be/7DlY0UmQcQ0

 How to run:
 Build file open and be able to find project solution.exe and run it as all files are within that file, that should allow for the .exe to run.

 This project was made within Visual Studios 2022, and was running on a Windows 11 Machines.

 What Scene have I created:
The scene I have created is with a red barn on a grass plane with a small animal on it, the asesethic i was going for was to feel extreme retro like with old Playstations and even with the fog slightly covering some of models this adds to it and replicates the old Playstation and their poor render distance. The controls you can use within the scene are WASD which allows you to move forward, back, left and right respectively.

Blinn-Phong shader:
Within the frag shader files within the solution or within the file shader, you are able to see a method called blinn phong which is used to make a blinn phong shader and apply to the models, it also allows for a effective way to show off my models and their textures.

Texture loading:
I'm loading textures within the template by using texture.cpp load texture method within the scenebasic_uniform.cpp, I have loaded different textures by using the load texture and the link to the file that I want as a texture and then within the render() method, i have binded the textures before the mesh is render for the model to bind the certain textures to each of the models.

Lightning Subtechniques(Fog):
I've added fog to the scene within the frag shader and within the scenebasic_uniform.cpp, I'm calling the uniforms to set their variables to make the fog max distance and min distance and the colour of it this allows for it to be easily adjusted within the file and make different colour fogs. The Frag shader code is the uniform structure for the fog and wihtin the main that calls to run the fog and apply it to the scene.

Keyboard Controls:
The keyboard controls are found within the scenerunner.h and within the main loop function, where it collects data about the time of the scene and the button presses from the user and this is then applied to the viewmatrix to be able to move the screen around for the viewer by using the WASD controls and TV to go up and down and is done to the scene within the update function within the scenebasic_uniform.cpp.

Light Movement:
The light movement is done within the update function which changes the variable angle and then the angle is then applied to the render function where it moves the light position around the scene.

Things to add for the next part:
More animal model will make the scene feel more alive and more full also a fence like model to give it a more barn like asesthic will help to spruce up the scene.

The models: where created by me within Blender and the plane was rendered from the plane.cpp file within the template.