#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define STB_IMAGE_IMPLEMENTATION

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "Matrix.h"


#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	glClearColor(0.4f, 0.2f, 0.4f, 1.0f);
#ifdef _WINDOWS
	glewInit();
#endif

int LoadTexture(const char* filePath)
	{
		int w, h, comp;
		unsigned char* image1 = stbi_load("World_Globe_clip_art_medium.png", 1, 1, 1, STBI_rgb_alpha);
		GLUint textureID;

		if (image == NULL)
		{
			std::cout << "Unable to load image. Check file path\n";
			assert(false);
		}

		GLUint textureID;
		glGenTextures(3, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTextImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSINGED_BYTE, image1);
		glTextImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSINGED_BYTE, image2);
		glTextImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSINGED_BYTE, image3);
		glTextParam(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextParam(GL_TEXTURE_2D, GL_TEXTURE_MAX_FILTER, GL_LINEAR);

		float textCoords1[] = { 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
		glVertexAttribPtr(prog.textCoordAttribute, 2, GL_FLOAT, false, -, textCoords);
	}

	glViewport(0, 0, 640, 360);
	ShaderProgram prog;

	prog.Load(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	GLUint globeTexture = LoadTexture(RESOURCE_FOLDER"World_Globe_clip_art_medium.png");
	GLUint shyTexture = LoadTexture(RESOURCE_FOLDER"shy.gif");
	GLUint surprisedTexture = LoadTexture(RESOURCE_FOLDER"surprised.gif");
	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	float lastFrameTicks = 0.0f;

	projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
	glUseProgram(prog.programID);

	SDL_Event event;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(displayWindow);
		program.SetColor(0.4f, 0.1f, 0.4f, 1.0f);

		prog.SetModelMatrix(modelMatrix);
		prog.SetProjectionMatrix(projectionMatrix);
		prog.SetViewMatrix(viewMatrix);

		glBindTexture(GL_TEXTURE_2D, globeTexture);
		glBindTexture(GL_TEXTURE_2D, shyTexture);
		glBindTexture(GL_TEXTURE_2D, surprisedTexture);

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		float vertices[] = { -0.5, -0.5, -0.5, 0.5, 0.5, -0.5,-0.5, 0.5, 0.5, -0.5, 0.5 };
		glVertexAttribPtr(prog.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArr(prog.positionAttribute);

		angle += elapsed;

		float textCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
		glAtrribPtr(program.textCoordAttribute, 2, GL_FLOAT, false, 0, textCoords);
		glEnableVertexAttribArray(prog.textCoordAttribute);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.textCoordAttribute);

	}


	stbi_image_free(image1);
	stbi_image_free(image2);
	stbi_image_free(image3);


	SDL_Quit();
	return 0;
}