#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

//variables para keyframes
float reinicio=1,reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo13, ciclo14, ciclo15, ciclo16, ciclo17, ciclo18, ciclo19, ciclo20, contador = 0;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void inputKeyframes();

// Window dimensions
const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

//variables
int displays = 0;
bool active;
float rotFlipperIzq = 0.0f;
float rotFlipperDer = 0.0f;
float rotFlipperArr = 0.0f;
float rotspot = 0.0f;
float rotationSpeed = 45.0f; // Grados por segundo
bool anim;
//animacion bumpers adelante
float logoBumpHeight = 0.35f; // Altura m�xima de movimiento
float logoBumpSpeed = 1.5f; // Velocidad de movimiento
const float maxYLimit = -0.005f;
const float maxYLimitd = -0.005f;
//animacion bumper atras
const float logoBumpSpeedatras = 2.0f; // Velocidad de la animaci�n
const float logoBumpHeightatras = 0.35f; // Altura m�xima de la animaci�n
const float initialPhase = 1.5f; // Fase inicial para empezar en un punto diferente
//animacion base miles
float timemiles = 0.0f;
float speedmiles = 0.5f; // Velocidad de oscilaci�n
float maxHeightmiles = 1.0f;
float heightmiles = 0.0f;
//animacion base gwen
float timegwen = 0.0f;
float speedgwen = 0.5f; // Velocidad de oscilaci�n
float maxHeightgwen = 1.0f;
float heightgwen = 0.0f;
//animacion palanca
float despPal = 0.0f;
float escPal = 1.0f;
float despPal2 = 0.0f;
//animacion oHara
float posX;		//Variable para PosicionX
float posY;		//Variable para PosicionY
float posZ;		//Variable para PosicionZ
float incX;		//Variable para IncrementoX
float incY;		//Variable para IncrementoY
float incZ;		//Variable para IncrementoZ
bool anim2 = false, anim3 = false;
float rot2 = 0.0f, rot3 = 0.0f;


// Positions of the point lights
glm::vec3 pointLightPositions[] = {//Cada vector se cambia para que haya un point en cada esfera
	glm::vec3(-5.0f, 0.0f, -5.0f),
	glm::vec3(-5.0f, 0.0f, 5.0f),
	glm::vec3(5.0f, 0.0f, 5.0f),
	glm::vec3(5.0f, 0.0f, -5.0f)
};

struct Spotlight {
	glm::vec3 Pos;
	glm::vec3 Dir;
};
Spotlight spotlight;


float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

//NEW// Keyframes
float posXcanica = -4.3, posYcanica = 0.3, posZcanica = -1.65;
float movCanica_z = 0.0f, movCanica_x = 0.0f;

#define MAX_FRAMES 100
int i_max_steps = 90;
int i_curr_steps = 10;//10
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movCanica_z;		//Canica PosX
	float movCanica_x;		//Canica PosZ
	float movCanica_zInc;	//Canica IncX
	float movCanica_xInc;	//Canica IncZ
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 10;//10		//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].movCanica_z = movCanica_z;
	KeyFrame[FrameIndex].movCanica_x = movCanica_x;
	//no volatil, agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;
}

void resetElements(void) //Tecla 0
{

	movCanica_x = KeyFrame[0].movCanica_z;
	movCanica_z = KeyFrame[0].movCanica_x;
}

void interpolation(void)
{
	KeyFrame[playIndex].movCanica_zInc = (KeyFrame[playIndex + 1].movCanica_z - KeyFrame[playIndex].movCanica_z) / i_max_steps;
	KeyFrame[playIndex].movCanica_xInc = (KeyFrame[playIndex + 1].movCanica_x - KeyFrame[playIndex].movCanica_x) / i_max_steps;
}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animaci�n entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animaci�n con �ltimo frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("Termin� la animaci�n\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolaci�n del pr�ximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animaci�n
			movCanica_z += KeyFrame[playIndex].movCanica_zInc;
			movCanica_x += KeyFrame[playIndex].movCanica_xInc;
			i_curr_steps++;
		}

	}
	else {
		movCanica_x = KeyFrame[0].movCanica_z;
		movCanica_z = KeyFrame[0].movCanica_x;
		play = true;
	}
}

///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	Model maquina((char*)"Models/maquina/maquina.obj");
	Model spot((char*)"Models/spot/spot.obj");
	Model flipizq((char*)"Models/flipizq/flipizq.obj");
	Model flipder((char*)"Models/flipder/flipder.obj");
	Model fliparr((char*)"Models/fliparr/fliparr.obj");
	Model botonizq((char*)"Models/boton/botonizq.obj");
	Model botonder((char*)"Models/boton/botonder.obj");
	Model logobumpizq((char*)"Models/logobumper/logobumper.obj");
	Model logobumpder((char*)"Models/logobumper/logobumper.obj");
	Model logobumpatras((char*)"Models/logobumper/logobumper.obj"); 
	Model basebumpadel((char*)"Models/bumpersadelante/basebump.obj");
	Model basebumpatras((char*)"Models/bumperatras/basebumper.obj");
	Model resorte((char*)"Models/resorte/resorte.obj");
	Model palanca((char*)"Models/palanca/palanca.obj");
	Model display0((char*)"Models/display0/display0.obj");
	Model display1((char*)"Models/display1/display1.obj");
	Model display2((char*)"Models/display2/display2.obj");
	Model display3((char*)"Models/display3/display3.obj");
	Model moneda((char*)"Models/moneda/moneda.obj");
	Model tope((char*)"Models/tope/tope.obj");
	Model canica((char*)"Models/canicas/canica.obj");
	Model canica2((char*)"Models/canicas/canica.obj");
	Model milesbase((char*)"Models/milesbase/milesbase.obj");
	Model gwenbase((char*)"Models/gwenbase/gwenbase.obj");

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	glm::vec3 canicaPos = glm::vec3(0.0f, 0.0f, 0.0f);

	//FRAME INICIAL
	KeyFrame[0].movCanica_z = 0.0f;
	KeyFrame[0].movCanica_x = 0.0f;
	
	//FRAMES RESTANTES CALCULADOS
	KeyFrame[1].movCanica_z = 0.0f;
	KeyFrame[1].movCanica_x = -0.5f;

	KeyFrame[2].movCanica_z = 3.5f;
	KeyFrame[2].movCanica_x = -0.5f;

	KeyFrame[3].movCanica_z = 2.0f;
	KeyFrame[3].movCanica_x = 2.0f;

	KeyFrame[4].movCanica_z = 0.5f;
	KeyFrame[4].movCanica_x = 6.5f;

	KeyFrame[5].movCanica_z = 0.5f;
	KeyFrame[5].movCanica_x = 8.0f;

	KeyFrame[6].movCanica_z = 3.0f;
	KeyFrame[6].movCanica_x = 6.0f;

	KeyFrame[7].movCanica_z = 3.0f;
	KeyFrame[7].movCanica_x = 7.5f;

	KeyFrame[8].movCanica_z = 1.5f;
	KeyFrame[8].movCanica_x = 3.5f;

	KeyFrame[9].movCanica_z = 0.000004f;
	KeyFrame[9].movCanica_x = 0.000053f;

	printf("\nTeclas para uso de Keyframes:\n1.-Presionar 9 para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");
	printf("3.-Presiona L para guardar frame\n4.-Presiona P para habilitar guardar nuevo frame\n5.-Presiona 1 para mover canica en X+\n6.-Presiona 2 para habilitar mover canica en X-\n");
	printf("7.-Presiona 3 para mover canica en X-\n8.-Presiona 4 para habilitar mover canica en X-\n9.-Presiona 5 para mover canica en Z+\n10.-Presiona 6 para habilitar mover canica en Z+\n");
	printf("11.-Presiona 7 para mover canica en Z-\n12.-Presiona 8 para habilitar mover canica en Z-\n");

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		//-------Para Keyframes
		inputKeyframes();
		animate();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = abs(sin(glfwGetTime() * Light1.z));
		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);//Estas 3 en todas
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.44f);


		// Point light 2
		glm::vec3 lightColor2;
		lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		lightColor2.z = abs(sin(glfwGetTime() * Light2.z));
		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.44f);


		// Point light 3
		glm::vec3 lightColor3;
		lightColor3.x = abs(sin(glfwGetTime() * Light3.x));
		lightColor3.y = abs(sin(glfwGetTime() * Light3.y));
		lightColor3.z = abs(sin(glfwGetTime() * Light3.z));
		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.44f);


		// Point light 4
		glm::vec3 lightColor4;
		lightColor4.x = abs(sin(glfwGetTime() * Light4.x));
		lightColor4.y = abs(sin(glfwGetTime() * Light4.y));
		lightColor4.z = abs(sin(glfwGetTime() * Light4.z));
		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.44f);



		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), spotlight.Pos.x, spotlight.Pos.y, spotlight.Pos.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), spotlight.Dir.x, spotlight.Dir.y, spotlight.Dir.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		if (playIndex <= 2) {
			displays = 0;
		}
		else {
			if (playIndex > 2 && playIndex <= 5) {
				displays = 1;
			}
			else {
				if (playIndex > 5 && playIndex <= 7) {
					displays = 2;
				}
				else {
					if (playIndex > 7 && playIndex <= 8) {
						displays = 3;
					}
					else {
						reinicio = 0;
					}
				}
			}
		}

		glm::mat4 model(1);

		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_BLEND); //Desactiva el canal alfa 
		//Maquina
		model = glm::mat4(1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		maquina.Draw(lightingShader);


		//Spot
		rotspot += rotationSpeed * deltaTime;
		if (rotspot > 360.0f) {
			rotspot -= 360.0f; // Para evitar un overflow de la variable
		}
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(6.8f, 0.8f, 3.3f));
		model = glm::rotate(model, glm::radians(rotspot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		spot.Draw(lightingShader);



		//Flipper Izquierdo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.5f, 0.25f, -1.6f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotFlipperIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		flipizq.Draw(lightingShader);


		//Flipper Derecho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.6f, 0.25f, 1.55f));
		model = glm::rotate(model, glm::radians(rotFlipperDer), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		flipder.Draw(lightingShader);

		//Flipper Arriba
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.1f, 0.25f, 1.85f));
		model = glm::rotate(model, glm::radians(rotFlipperArr), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		fliparr.Draw(lightingShader);

		//boton izquierdo
		model = glm::mat4(1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		botonizq.Draw(lightingShader);

		//boton derecho
		model = glm::mat4(1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		botonder.Draw(lightingShader);

		//logo bumper izquierda
		float logoBumpOffset = sin(glfwGetTime() * logoBumpSpeed) * logoBumpHeight;
		glm::mat4 logoBumpModel = glm::mat4(1.0);
		float translateY = -0.005f + logoBumpOffset;
		translateY = std::max(translateY, maxYLimit);
		logoBumpModel = glm::translate(logoBumpModel, glm::vec3(4.2f, translateY, -1.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(logoBumpModel));
		logobumpizq.Draw(lightingShader);

		//logo bumper derecha
		glm::mat4 modeld = glm::mat4(1.0);
		float translateYd = -0.005f;  // Asumiendo que este es el valor que quieres limitar
		translateYd = std::max(translateY, maxYLimitd);
		modeld = glm::translate(modeld, glm::vec3(4.1f, translateYd, 1.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modeld));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		logobumpder.Draw(lightingShader);

		//base bumper adelante
		model = glm::mat4(1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		basebumpadel.Draw(lightingShader);

		//logo bumper atras
		// Calcular el desplazamiento con una fase inicial
		float time = glfwGetTime();
		float logoBumpOffsetatras = sin(time * logoBumpSpeedatras + initialPhase) * logoBumpHeightatras;
		// Asegurar que el valor m�nimo de -y es -0.005
		float minY = -0.005f;
		float translateYatras = minY + logoBumpOffsetatras;
		translateYatras = std::max(translateYatras, minY);
		glm::mat4 modelatras = glm::mat4(1.0);
		modelatras = glm::translate(modelatras, glm::vec3(4.95f, translateYatras, -0.07f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelatras));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		logobumpatras.Draw(lightingShader);

		//resorte
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.03f, 0.35f, 4.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		resorte.Draw(lightingShader);

		//palanca
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.13f, 0.35f, 4.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		palanca.Draw(lightingShader);

		//display
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 4.75f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		if (displays == 0) {
			display0.Draw(lightingShader);
		}
		if (displays == 1) {
			display1.Draw(lightingShader);
		}
		if (displays == 2) {
			display2.Draw(lightingShader);
		}
		if (displays == 3) {
			display3.Draw(lightingShader);
		}

		//moneda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-8.75f, -1.0f, 2.9f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		moneda.Draw(lightingShader);

		//tope
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.3f, 0.25f, 3.75f));
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		tope.Draw(lightingShader);

		//canica 1
		model = glm::mat4(1.0);
		canicaPos = glm::vec3(posXcanica + movCanica_x, posYcanica, posZcanica + movCanica_z);
		model = glm::translate(model, canicaPos);
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		canica.Draw(lightingShader);

		//base bumper adelante
		model = glm::mat4(1.0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		basebumpatras.Draw(lightingShader);

		//miles con base
		time += deltaTime;
		heightmiles = (sin(time * speedmiles) + 1.0f) * (maxHeightmiles / 2.0f);
		if (heightmiles < 0.0f) heightmiles = 0.0f;
		model = glm::mat4(1.0);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, heightmiles, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		milesbase.Draw(lightingShader);

		//gwen con base
		time += deltaTime;
		heightgwen = (sin(time * speedgwen) + 1.0f) * (maxHeightgwen / 2.0f);
		if (heightgwen < 0.0f) heightgwen = 0.0f;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, heightgwen, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		gwenbase.Draw(lightingShader);


		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		model = glm::mat4(1);
		model = glm::translate(model, spotlight.Pos);
		model = glm::scale(model, glm::vec3(0.4f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
		anim2 = true;
		posZ -= .1;
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		anim2 = true;
		posZ += .1;

	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
		anim2 = true;
		posX -= .1;

	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
		anim2 = true;
		posX += .1;

	}
	if (keys[GLFW_KEY_Z]) // Si se presiona la tecla Z y la rotaci�n es menor a 75 grados.
	{
		rotFlipperIzq = 45.0f; // Incrementa la rotaci�n.
	}
	else if (!keys[GLFW_KEY_Z]) // Si se suelta la tecla Z y la rotaci�n es mayor a 0 grados.
	{
		rotFlipperIzq = 0.0f; // Decrementa la rotaci�n.
	}
	if (keys[GLFW_KEY_X]) // Si se presiona la tecla X y la rotaci�n es menor a 75 grados.
	{
		rotFlipperDer = -45.0f; // Incrementa la rotaci�n.
	}
	else if (!keys[GLFW_KEY_X]) // Si se suelta la tecla X y la rotaci�n es mayor a 0 grados.
	{
		rotFlipperDer = 0.0f; // Decrementa la rotaci�n.
	}
	if (keys[GLFW_KEY_C]) // Si se presiona la tecla X y la rotaci�n es menor a 75 grados.
	{
		rotFlipperArr = -45.0f; // Incrementa la rotaci�n.
	}
	else if (!keys[GLFW_KEY_C]) // Si se suelta la tecla X y la rotaci�n es mayor a 0 grados.
	{
		rotFlipperArr = 0.0f; // Decrementa la rotaci�n.
	}
	if (anim2) {
		if (rot2 < 30.0f) {
			rot2 += 0.1f;
		}
		if (rot2 >= 30.0f) {
			anim2 = false;
			anim3 = true;
		}
		if (rot3 > -30.0f) {
			rot3 -= 0.1f;
		}
		if (rot3 <= -30.0f) {
			anim2 = false;
			anim3 = true;
		}
	}
	if (anim2) {
		if (rot2 > -30.0f) {
			rot2 -= 0.1f;
		}
		if (rot2 <= 30.0f) {
			anim3 = false;
			anim2 = true;
		}
		if (rot3 < 30.0f) {
			rot3 += 0.1f;
		}
		if (rot3 >= 30.0f) {
			anim3 = false;
			anim2 = true;
		}
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 0.0f, 0.0f);
			Light2 = glm::vec3(0.0f, 1.0f, 0.0f);
			Light3 = glm::vec3(0.0f, 0.0f, 1.0f);
			Light4 = glm::vec3(0.8471f, 0.5059f, 0.8824f);
		}
		else
		{
			Light1 = glm::vec3(0);
			Light2 = glm::vec3(0);
			Light3 = glm::vec3(0);
			Light4 = glm::vec3(0);
		}
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		keys[GLFW_KEY_Z] = true;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
	{
		keys[GLFW_KEY_Z] = false;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		keys[GLFW_KEY_X] = true;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE)
	{
		keys[GLFW_KEY_X] = false;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		keys[GLFW_KEY_C] = true;
	}
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE)
	{
		keys[GLFW_KEY_C] = false;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void inputKeyframes()
{
	if (reinicio==1)
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n Presiona 0 para habilitar reproducir de nuevo la animaci�n'\n");
				habilitaranimacion = 0;
			
			}
			else
			{
				play = false;
			}
		}
	}
	if (reinicio==0)
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animaci�n con 9'\n");
			reproduciranimacion = 0;
			reinicio = 1;

		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movCanica_z es: %f\n", movCanica_z);
			printf("movCanica_x es: %f\n", movCanica_x);

			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1 && guardoFrame >= 1)
		{
			guardoFrame = 0;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}

	//MOV CANICA X+
	if (keys[GLFW_KEY_1])
	{
		if (ciclo13 < 1)
		{
			movCanica_x += 0.5f;
			printf("\n movCanica2_x es: %f\n", movCanica_x);
			ciclo13++;
			ciclo14 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo14 < 1 && ciclo13>0)
		{
			ciclo13 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}

	//MOV CANICA X-
	if (keys[GLFW_KEY_3])
	{
		if (ciclo15 < 1)
		{
			movCanica_x -= 0.5f;
			printf("\n movCanica2_x es: %f\n", movCanica_x);
			ciclo15++;
			ciclo16 = 0;
			printf("\n Presiona la tecla 4 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_4])
	{
		if (ciclo16 < 1 && ciclo15>0)
		{
			ciclo15 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 3\n");
		}
	}

	//MOV CANICA2 Z+
	if (keys[GLFW_KEY_5])
	{
		if (ciclo17 < 1)
		{
			movCanica_z += 0.5f;
			printf("\n movCanica2_z es: %f\n", movCanica_z);
			ciclo17++;
			ciclo18 = 0;
			printf("\n Presiona la tecla 6 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_6])
	{
		if (ciclo18 < 1 && ciclo17>0)
		{
			ciclo17 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 5\n");
		}
	}

	//MOV CANICA2 Z-
	if (keys[GLFW_KEY_7])
	{
		if (ciclo19 < 1)
		{
			movCanica_z -= 0.5f;
			printf("\n movCanica2_z es: %f\n", movCanica_z);
			ciclo19++;
			ciclo20 = 0;
			printf("\n Presiona la tecla 8 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_8])
	{
		if (ciclo20 < 1 && ciclo19>0)
		{
			ciclo19 = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 7\n");
		}
	}
}