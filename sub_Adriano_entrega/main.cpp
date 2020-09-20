// Implementado por Adriano Domingos Goulart

#include <iostream>
#include <cmath>

#include <vart/scene.h>
#include <vart/light.h>
#include <vart/box.h>
#include <vart/point4d.h>
#include <vart/meshobject.h>
#include <vart/transform.h>
#include <vart/contrib/viewerglutogl.h>

#include <time.h>
#include <random>

using namespace std;
using namespace VART;

const unsigned int MAX_KEYS = 10;
enum Key{ UP, DOWN, RIGHT, LEFT};

bool keyPressed[MAX_KEYS];

class KeyboardHandler : public VART::ViewerGlutOGL::KbHandler{
	private:
		
	public:
		KeyboardHandler(){
            for(unsigned int i = 0; i < MAX_KEYS; ++i){
            	keyPressed[i] = false;
            }
        }
		
		virtual void OnKeyDown(int key){
			switch(key){

				case 'l':
					keyPressed[RIGHT] = true;
					break;
				   
				case 'j':
					keyPressed[LEFT] = true;
					break;

				case 'i':
					keyPressed[UP] = true;
					break;
				
				case 'k':
					keyPressed[DOWN] = true;
					break;
			}
		}

		virtual void OnKeyUp(int key){
			switch (key){

				case 'l':
					keyPressed[RIGHT] = false;
					break;

				case 'j':
					keyPressed[LEFT] = false;
					break;

				case 'i':
					keyPressed[UP] = false;
					break;

				case 'k':
					keyPressed[DOWN] = false;
					break;			
			}
		}
};

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler{
	private:
		double speed = 0.8;
        double xTranslation = 10.0;
        double yTranslation = 8;
        double zTranslation = 0.0;
        double yRotation = 0.0;
        time_t ini = time(&ini);
        time_t fim;
        int vitorias = 0;

	public:
		Transform* skeletonTranslation;
        Transform* skeletonRotation;
        Transform* castleTranslation;

        virtual void OnIdle(){
        	// Gerador numeros aleatorios
        	random_device rd;
			mt19937 gen(rd());
			uniform_real_distribution<> disX(-20, 20);
			uniform_real_distribution<> disZ(-40, 70);
			uniform_real_distribution<> disR(0, 6);

            if(keyPressed[UP]){
                xTranslation += sin(yRotation) * speed;
                zTranslation += cos(yRotation) * speed;
                skeletonTranslation->MakeTranslation(xTranslation, yTranslation, zTranslation);
            }

            if(keyPressed[DOWN]){
                xTranslation += -sin(yRotation) * speed;
                zTranslation += -cos(yRotation) * speed;
                skeletonTranslation->MakeTranslation(xTranslation, yTranslation, zTranslation);
            }

            if(keyPressed[RIGHT]){
                yRotation -= M_PI/20;
                skeletonRotation->MakeYRotation(yRotation);
            }

            if(keyPressed[LEFT]){
                yRotation += M_PI/20;
                skeletonRotation->MakeYRotation(yRotation);
            }

            // Saiu da area delimitada pelo chao
            if(zTranslation > 80 or zTranslation < -40 or xTranslation < -21 or xTranslation > 21){
            	xTranslation = disX(gen);
        		zTranslation = disZ(gen);
        		yRotation = disR(gen);

        		skeletonTranslation->MakeTranslation(xTranslation, yTranslation, zTranslation);
        		skeletonRotation->MakeYRotation(yRotation);
        		cout << endl <<"Voce perdeu." << endl;
            }

            // Chegou ao castelo
            if(zTranslation > 69 and xTranslation < -11 and xTranslation > -19){
				xTranslation = disX(gen);
        		zTranslation = disZ(gen);
        		yRotation = disR(gen);

        		skeletonTranslation->MakeTranslation(xTranslation, yTranslation, zTranslation);
        		skeletonRotation->MakeYRotation(yRotation);
        		vitorias++;
        		cout << endl <<"Voce chegou ao castelo " << vitorias << " vezes!"<< endl;

            }

            // Ganhou
            if(vitorias == 5){
            	time(&fim);
            	cout << endl << "|*|*|===|*|*|=== VOCE GANHOU EM: " << double(fim - ini);
        		cout << " SEGUNDOS!!! ===|*|*|===|*|*|" << endl;
        		vitorias = 0;
        		time(&ini);
            }
            
            viewerPtr->PostRedisplay();
        }
};

int main(int argv, char* argc[]){
	ViewerGlutOGL::Init(&argv, argc); // Initialize GLUT
	static Scene scene; // create a scene
	static ViewerGlutOGL viewer; // create a viewer (application window)

	// Create a camera (scene observer)
	Camera camera(Point4D(60,60,10), Point4D(10,10,10), Point4D::Y());

	// ----------Create some objects-------------- //

	// Esqueleto
	list<MeshObject*> skeleton;
    MeshObject::ReadFromOBJ("skeleton5b/skeleton5b.obj", &skeleton);
    list<MeshObject*>::iterator it = skeleton.begin();

    Transform rotateSkeleton;
    Transform movingSkeletonRotation;
    Transform movingSkeletonTransform;

    // Chao
    MeshObject box;
    Transform boxTranslation;

    // Castelo
    list<MeshObject*> castle;
    MeshObject::ReadFromOBJ("Castle_Tower/20956_Castle_Tower_V1.obj", &castle);
    list<MeshObject*>::iterator itc = castle.begin();

    Transform rotateCastle;
    Transform translationCastle;

    // ----------Initialize scene objects--------- //

    // Esqueleto
    for(; it != skeleton.end(); ++it){
        rotateSkeleton.AddChild((**it));
    }
    rotateSkeleton.MakeXRotation(-M_PI/2);
    movingSkeletonRotation.MakeXRotation(0);
    movingSkeletonTransform.MakeTranslation(10,8,0);

    // Chao
    box.MakeBox(-20, 20, 0, 1, -60, 60);
    box.SetMaterial(Material::DARK_PLASTIC_GRAY());
    boxTranslation.MakeTranslation(0,-2,20);

    // Castelo
    for(; itc != castle.end(); ++itc){
        rotateCastle.AddChild((**itc));
    }
    rotateCastle.MakeXRotation(-M_PI/2);
    translationCastle.MakeTranslation(-15,-1,75);
	
	// ----------Build up the scene--------------- //

	// Esqueleto
	movingSkeletonTransform.AddChild(movingSkeletonRotation);
	movingSkeletonRotation.AddChild(rotateSkeleton);

	// Chao
	boxTranslation.AddChild(box);

	// Castelo
	translationCastle.AddChild(rotateCastle);

	// Cena
	scene.AddObject(&movingSkeletonTransform);
    scene.AddObject(&boxTranslation);
    scene.AddObject(&translationCastle);

	scene.AddLight(Light::BRIGHT_AMBIENT());
	scene.AddCamera(&camera);
	scene.DrawLightsOGL(); // Set OpenGL's lights' state

	// ----------Set up the Idle Handler---------- //

    MyIHClass idh;

    // Esqueleto
    idh.skeletonTranslation = &movingSkeletonTransform;
    idh.skeletonRotation = &movingSkeletonRotation;

    // Castelo
    idh.castleTranslation = &translationCastle;

	// ----------Set up the viewer---------------- //

    viewer.SetTitle("Run Skeleton Run");
    viewer.SetScene(scene); // attach the scene
    viewer.SetIdleHandler(&idh); // attach the idle handler to the viewer

    KeyboardHandler kbh;
	viewer.SetKbHandler(&kbh);

	// ----------Infos---------------------------- //

	cout << endl << "-------------------------Run Skeleton Run--------------------------" << endl
		 << "Chegue com o esqueleto no castelo 5 vezes, no menor tempo possivel." << endl
		 << "(AVISO: JOGUE EM TELA CHEIA)" << endl;

    cout << endl << "COMANDOS:" << endl
		 << "-Movimentacao = (i, j, k, l)" << endl
		 << "-Fechar o programa = (q)" << endl;

	cout << "-------------------------------------------------------------------" << endl;

    ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}