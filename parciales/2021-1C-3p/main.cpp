#include <iostream>
#include "vector.h"

typedef enum {
	UNKNOWN,
	VIDEO,
	MUSIC,
	SOCIAL
} appType;

class App {
private:
	std::string name;
	float size;
	appType type;
	bool appRequiresInternet;
	bool captionsActive;

public:
	/**
	 * post: inicializa `App`
	 */
	App() {
		this->size = 0;
		this->type = UNKNOWN;
		this->appRequiresInternet = false;
		this->captionsActive = false;
	}

	/**
	 * post: inicializa `App` con atributo `name` pasado como argumento
	 */
	App(std::string name) {
		this->name = name;
		this->size = 0;
		this->type = UNKNOWN;
		this->appRequiresInternet = false;
		this->captionsActive = false;
	}

	/**
	 * post: inicializa `App` con los atributos pasados como argumento
	 */
	App(std::string name, float size, appType type,
			bool appRequiresInternet, bool captionsActive) {
		this->name = name;
		this->size = size;
		this->type = type;
		this->appRequiresInternet = appRequiresInternet;
		this->captionsActive = captionsActive;
	}

	/**
	 * post: libera la memoria
	 */
	virtual ~App() {}

	/**
	 * post: devuelve el atributo `name`
	 */
	std::string getName() {
		return this->name;
	}

	/**
	 * post: devuelve el atributo `type`
	 */
	appType getAppType() {
		return this->type;
	}

	/**
	 * post: asigna al atributo `name` aquel pasado como argumento
	 */
	void setName(std::string name) {
		this->name = name;
	}

	/**
	 * post: asigna al atributo `captionsActive` el valor de `status`
	 */
	void setCaptions(bool status) {
		this->captionsActive = status;
	}

	/**
	 * post: devuelve el estado de `captionsActive`
	 */
	bool getCaptions(bool status) {
		return this->captionsActive;
	}

	/**
	 * post: cambia al valor opuesto `captionsActive`
	 */
	void toggleCaptions() {
		this->captionsActive = !this->captionsActive;
	}

	/**
	 * post: devuelve el valor del atributo `appRequiresInternet`
	 */
	bool requiresInternet() {
		return this->appRequiresInternet;
	}
};

class SmartTV {
private:
	Vector<App*> *appsList;
	App *currentApp;
	float diskSize;
	unsigned int appsInstalledCount;
	bool internetConnected;

public:
	/**
	 * post: inicializa la clase `SmartTV`
	 */
	SmartTV() {
		this->appsList = new Vector<App*>;
		this->currentApp = NULL;
		this->diskSize = 0;
		this->internetConnected = 0;
		this->appsInstalledCount = 0;
	}

	/**
	 * post: inicializa `SmartTV` con el valor de `diskSize` a aquel pasado como
	 *       argumento
	 */
	SmartTV(float diskSize) {
		this->appsList = new Vector<App*>;
		this->currentApp = NULL;
		this->diskSize = diskSize;
		this->internetConnected = 0;
		this->appsInstalledCount = 0;
	}

	/**
	 * post: libera la memoria de `SmartTV` y todas las instancias de `App` 
	 */
	virtual ~SmartTV() {
		for(size_t i = 0; i < this->appsList->getSize(); ++i) {
			delete this->appsList->getAtIndex(i);
		}
		delete this->appsList;
	}

	/**
	 * post: agrega una aplicacion a `appsList`
	 */
	void addApp(std::string name) {
		App *newApp = new App(name);
		this->appsList->append(newApp);
		this->appsInstalledCount++;
	}

	/**
	 * post: agrega una aplicacion a `appsList` con los atributos recibidos como
	 *       argumento
	 */
	void addApp(std::string name, float size, appType type, bool requiresInternet) {
		try {
			this->getAppByName(name);
		} catch (std::string return_value) {
			// la app no esta instalada
			App *newApp = new App(name, size, type, requiresInternet, false);
			this->appsList->append(newApp);
			this->appsInstalledCount++;
		}
	}

	/**
	 * post: devuelve el valor de `appsInstalledCount`
	 */
	unsigned int getAppsInstalledCount() {
		return this->appsInstalledCount;
	}

	/**
	 * post: devuelve un puntero a la aplicacion en la posicion `index` 
	 *       de `appsList`
	 */
	App *getAppByIndex(unsigned int index) {
		try {
			return this->appsList->getAtIndex(index);
		} catch (std::string error) {
			return NULL;
		}
	}

	/**
	 * pre: la aplicacion debe existir en `appsList` si no arroja una excepción
	 * post: devuelve un puntero a la aplicacion cuyo nombre es `name` 
	 */
	App *getAppByName(std::string name) {
		for(size_t i = 0; i < this->appsList->getSize(); ++i) {
			App *tmp = this->appsList->getAtIndex(i);
			if(tmp->getName() == name) {
				return tmp;
			}
		}
		throw "the app `" + name + "` is not installed";
	}

	/**
	 * pre: no hay una aplicacion corriendo, si no arroja una excepción
	 * post: apunta `currentApp` a la aplicacion con nombre `name`
	 */
	void startApp(std::string name) {
		if(currentApp != NULL) {
			throw "there is an app running already";
		}

		try {
			currentApp = this->getAppByName(name);
		} catch(std::string error) {
			currentApp = NULL;
			throw "the app is not installed";
		}

		if(currentApp->requiresInternet() && !this->internetConnected) {
			currentApp = NULL;
			throw "the app requires internet";
		}
	}

	/**
	 * pre: hay una aplicacion corriendo
	 * post: devuelve un puntero a la aplicacion que está corriendo actualmente
	 */
	App *getCurrentApp() {
		return this->currentApp;
	}

	/**
	 * pre: hay una aplicacion corriendo
	 * post: asigna el valor de `currentApp` a `NULL`
	 */
	void closeApp(std::string name) {
		if(currentApp == NULL) {
			throw "there is no app running";
		}

		currentApp = NULL;
	}

	/**
	 * post: asigna a `internetConnected` el valor `true`
	 */
	void internetConnect() {
		this->internetConnected = true;
	}

	/**
	 * post: asigna a `internetConnected` el valor `false`
	 */
	void internetDiconnect() {
		this->internetConnected = false;
	}

	/**
	 * pre: hay una aplicación ejecutandose y es de tipo `VIDEO`
	 * post: ejecuta el metodo `toggleCaptions` de la aplicacion en ejecución
	 */
	void toggleCaptions() {
		App *runningApp = this->currentApp;
		if((runningApp != NULL) && (runningApp->getAppType() == VIDEO)) {
			runningApp->toggleCaptions();
		} else {
			throw "there is no running app or the app does not allow captions";
		}
	}
};

void printTvStatus(SmartTV *tv) {
	for(size_t i = 0; i < tv->getAppsInstalledCount(); ++i) {
		std::cout << tv->getAppByIndex(i)->getName() << std::endl;
	}
	App *curApp = tv->getCurrentApp();
	std::string curAppName = (curApp == NULL ? "none" : curApp->getName());
	std::cout << "Current app running: " << curAppName << std::endl;
}

int main (void) {
	SmartTV *tv = new SmartTV(8000); // inicializa tv con disco de 8GB (8000MB)

	tv->internetConnect();
	tv->addApp("X", 150, SOCIAL, true);
	tv->addApp("youtube", 258, VIDEO, true);
	tv->addApp("spotify");

	tv->startApp("youtube");
	printTvStatus(tv);
	std::cout << std::endl;

	tv->closeApp("youtube");
	printTvStatus(tv);

	delete tv;
	return 0;
}
