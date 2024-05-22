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
	App() {
		this->size = 0;
		this->type = UNKNOWN;
		this->appRequiresInternet = false;
		this->captionsActive = false;
	}

	App(std::string name) {
		this->name = name;
		this->size = 0;
		this->type = UNKNOWN;
		this->appRequiresInternet = false;
		this->captionsActive = false;
	}

	App(std::string name, float size, appType type,
			bool appRequiresInternet, bool captionsActive) {
		this->name = name;
		this->size = size;
		this->type = type;
		this->appRequiresInternet = appRequiresInternet;
		this->captionsActive = captionsActive;
	}

	virtual ~App() {}

	std::string getName() {
		return this->name;
	}

	appType getAppType() {
		return this->type;
	}

	void setName(std::string name) {
		this->name = name;
	}

	void setCaptions(bool status) {
		this->captionsActive = status;
	}

	bool getCaptions(bool status) {
		return this->captionsActive;
	}

	void toggleCaptions() {
		this->captionsActive = !this->captionsActive;
	}

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
	SmartTV() {
		this->appsList = new Vector<App*>;
		this->currentApp = NULL;
		this->diskSize = 0;
		this->internetConnected = 0;
		this->appsInstalledCount = 0;
	}

	SmartTV(float diskSize) {
		this->appsList = new Vector<App*>;
		this->currentApp = NULL;
		this->diskSize = diskSize;
		this->internetConnected = 0;
		this->appsInstalledCount = 0;
	}

	virtual ~SmartTV() {
		for(size_t i = 0; i < this->appsList->getSize(); ++i) {
			delete this->appsList->getAtIndex(i);
		}
		delete this->appsList;
	}

	void addApp(std::string name) {
		App *newApp = new App(name);
		this->appsList->append(newApp);
		this->appsInstalledCount++;
	}

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

	unsigned int getAppsInstalledCount() {
		return this->appsInstalledCount;
	}

	App *getAppByIndex(unsigned int index) {
		try {
			return this->appsList->getAtIndex(index);
		} catch (std::string error) {
			return NULL;
		}
	}

	App *getAppByName(std::string name) {
		for(size_t i = 0; i < this->appsList->getSize(); ++i) {
			App *tmp = this->appsList->getAtIndex(i);
			if(tmp->getName() == name) {
				return tmp;
			}
		}
		throw "the app `" + name + "` is not installed";
	}

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

	App *getCurrentApp() {
		return this->currentApp;
	}

	void closeApp(std::string name) {
		if(currentApp == NULL) {
			throw "there is no app running";
		}

		currentApp = NULL;
	}

	void internetConnect() {
		this->internetConnected = true;
	}

	void internetDiconnect() {
		this->internetConnected = false;
	}

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
	SmartTV *tv = new SmartTV(8000); // inicializa tv con disco de 8GB

	tv->internetConnect();
	tv->addApp("X", 150, SOCIAL, true);
	tv->addApp("youtube", 258, VIDEO, true);

	tv->startApp("youtube");
	printTvStatus(tv);

	tv->closeApp("youtube");
	printTvStatus(tv);

	delete tv;
	return 0;
}
