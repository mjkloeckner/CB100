#include <iostream>
#include <sstream>
#include <cctype>

#define	CHANNELS_MAX	140

class Channel {
private:
	Channel* next;
	Channel* prev;
	unsigned int index;
	unsigned int volume;
	unsigned int lastVolume;
	unsigned int maxVolume;
	bool mute;

public:
	Channel() {
		next = prev = NULL;
		index = 0;
		lastVolume = maxVolume = volume = 50; // initialize channel volume at 50%
		mute = false;
	}

	virtual ~Channel() {
		delete this->next;
	}

	void setChannelIndex(unsigned int index) {
		this->index = index;
	}

	void toggleMute() {
		this->mute = !this->mute;
	}

	void setMute() {
		this->mute = true;
	}

	void unsetMute() {
		this->mute = false;
	}

	bool getMute() {
		return this->mute;
	}

	unsigned int getIndex() {
		return this->index;
	}

	unsigned int getVolume() {
		return this->volume;
	}

	void setVolume(int volume) {
		lastVolume = this->volume;
		if(volume > 100) {
			this->volume = 100;
		}
		else if(volume < 0) {
			this->volume = 0;
		} else {
			this->volume = volume;
		}
	}

	unsigned int getMaxVolume() {
		return this->maxVolume;
	}

	unsigned int getLastVolume() {
		return this->lastVolume;
	}

	void setNextChannel(Channel *next) {
		this->next = next;
	}

	void setPrevChannel(Channel *prev) {
		this->prev = prev;
	}

	Channel *getPrev() {
		return this->prev;
	}

	Channel *getNext() {
		return this->next;
	}
};

class Television {
private:
	Channel *channelList;
	Channel *currentChannel;

public:
	Television() {
		channelList = new Channel;
		currentChannel = channelList;
		channelList->setChannelIndex(0);

		Channel *prev = NULL;
		Channel *next = new Channel;
		next->setPrevChannel(channelList);
		next->setNextChannel(NULL);
		next->setChannelIndex(1);

		channelList->setPrevChannel(prev);
		channelList->setNextChannel(next);

		for(unsigned int i = 2; i < CHANNELS_MAX; ++i) {
			prev = next;
			next = new Channel;
			prev->setNextChannel(next);
			next->setPrevChannel(prev);
			next->setNextChannel(NULL);
			next->setChannelIndex(i);
		}
	}

	virtual ~Television() {
		delete this->channelList;
	}

	Channel *getCurrentChannel() {
		return this->currentChannel;
	}

	void nextChannel() {
		if(currentChannel->getNext() != NULL) {
			currentChannel = currentChannel->getNext();
		}
	}

	void prevChannel() {
		if(currentChannel->getPrev() != NULL) {
			currentChannel = currentChannel->getPrev();
		}
	}

	void setChannel(int channelIndex) {
		if(channelIndex > CHANNELS_MAX) {
			channelIndex = CHANNELS_MAX;
		} else if(channelIndex < 0) {
			channelIndex = 0;
		}

		if(channelIndex < currentChannel->getIndex()) {
			while(currentChannel->getPrev() != NULL) {
				if(currentChannel->getIndex() == channelIndex) {
					break;
				}
				currentChannel = currentChannel->getPrev();
			}
		} else if(channelIndex >= currentChannel->getIndex()) {
			while(currentChannel->getNext() != NULL) {
				if(currentChannel->getIndex() == channelIndex) {
					break;
				}
				currentChannel = currentChannel->getNext();
			}
		}
	}

	void muteChannel() {
		currentChannel->setMute();
	}

	void unmuteChannel() {
		currentChannel->unsetMute();
	}

	void toggleMuteChannel() {
		currentChannel->toggleMute();
	}

	void raiseVolume() {
		currentChannel->setVolume(currentChannel->getVolume() + 10);
	}

	void lowerVolume() {
		currentChannel->setVolume(currentChannel->getVolume() - 10);
	}

	void setVolume(unsigned int volume) {
		currentChannel->setVolume(volume);
	}

	void printStatus() {
		std::cout << "channel: " << this->currentChannel->getIndex()+1<< std::endl;
		std::cout << "volume:  " << this->currentChannel->getVolume() << "%\n";
		std::cout << "mute:    "
			<< (this->currentChannel->getMute() ? "true" : "false") << std::endl;
	}
};

void printHelp() {
	std::cout
		<< "television simulator\n"
		<< "list of valid keys:\n"
		<< "  `+`: raise volume\n"
		<< "  `-`: lower volume\n"
		<< "  `m`: toggle mute\n"
		<< "  `n`: next channel\n"
		<< "  `c`: change to channel by index\n"
		<< "  `p`: previous channel\n"
		<< "  `q`: close\n\n";
}

int main () {
	Television *tv = new Television;
	bool shouldClose = false;
	char key;

	tv->printStatus();
	std::cout << "press `h` for a list of valid keys\n";
	while(!shouldClose) {
		std::cout << "tv> ";
		std::cin.get(key);

		if(std::cin.eof()) {
			shouldClose = true;
		}

		if(key == '\n') {
			continue;
		}

		switch(key) {
		case '+':
			std::cin.ignore(1);
			tv->raiseVolume();
			tv->printStatus();
			break;
		case '-':
			std::cin.ignore(1);
			tv->lowerVolume();
			tv->printStatus();
			break;
		case 'm':
			std::cin.ignore(1);
			tv->toggleMuteChannel();
			tv->printStatus();
			break;
		case 'n':
			std::cin.ignore(1);
			tv->nextChannel();
			tv->printStatus();
			break;
		case 'p':
			std::cin.ignore(1);
			tv->prevChannel();
			tv->printStatus();
			break;
		case 'c': {
			std::cin.ignore(1);
			std::string channelIndexStr;
			int newIndex;
			std::cout << "go to channel> ";
			do {
				std::cin.get(key);
				if(isdigit(key)) {
					channelIndexStr += key;
				}
			} while(key != '\n');
			std::istringstream(channelIndexStr) >> newIndex;
			try {
				tv->setChannel(newIndex-1);
			} catch (const char *error) {
				std::cout << error << std::endl;
			}
			tv->printStatus();
			break;
			}
		case 'v': {
			std::cin.ignore(1);
			std::string newVolumeStr;
			int newVolume;
			std::cout << "volume> ";
			do {
				std::cin.get(key);
				if(isdigit(key)) {
					newVolumeStr += key;
				}
			} while(key != '\n');
			std::istringstream(newVolumeStr) >> newVolume;
			try {
				tv->setVolume(newVolume);
			} catch (const char *error) {
				std::cout << error << std::endl;
			}
			tv->printStatus();
			break;
			}
		case 'q':
		case EOF:
			shouldClose = true;
			break;
		case 'h':
			std::cin.ignore(1);
			printHelp();
			tv->printStatus();
			break;
		case 10:
		default:
			std::cin.ignore(1);
			break;
		}
	}
	return 0;
}
