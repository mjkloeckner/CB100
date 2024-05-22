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
	unsigned int maxVolume;
	bool mute;

public:
	/**
	 * post: initializes the Channel
	 */
	Channel() {
		next = prev = NULL;
		index = 0;
		maxVolume = volume = 50; // initialize channel volume at 50%
		mute = false;
	}

	/**
	 * post: clears memory calling next destructor
	 */
	virtual ~Channel() {
		delete this->next;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: sets the Channel index to `index`
	 */
	void setChannelIndex(unsigned int index) {
		this->index = index;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: toggles the mute bool variable
	 */
	void toggleMute() {
		this->mute = !this->mute;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: sets the Channel mute to `true`
	 */
	void setMute() {
		this->mute = true;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: sets the Channel mute to `false`
	 */
	void unsetMute() {
		this->mute = false;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: returns the `mute` variable status
	 */
	bool getMute() {
		return this->mute;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: returns the `index` variable status
	 */
	unsigned int getIndex() {
		return this->index;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: returns the `volume` variable status
	 */
	unsigned int getVolume() {
		return this->volume;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: sets the Channel volume to `volume`
	 */
	void setVolume(int volume) {
		if(volume > 100) {
			this->volume = 100;
			maxVolume = 100;
		}
		else if(volume < 0) {
			this->volume = 0;
		} else {
			this->volume = volume;
			if(volume > (int)this->maxVolume) {
				maxVolume = volume;
			}
		}
	}

	/**
	 * pre: the Channel must be initialized
	 * post: returns the Channel `maxVolume`
	 */
	unsigned int getMaxVolume() {
		return this->maxVolume;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: sets the Channel `next` to `next`
	 */
	void setNextChannel(Channel *next) {
		this->next = next;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: sets the Channel `prev` to `prev`
	 */
	void setPrevChannel(Channel *prev) {
		this->prev = prev;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: retuns a pointer to the previous Channel
	 */
	Channel *getPrev() {
		return this->prev;
	}

	/**
	 * pre: the Channel must be initialized
	 * post: retuns a pointer to the next Channel
	 */
	Channel *getNext() {
		return this->next;
	}
};

class Television {
private:
	Channel *channelList;
	Channel *currentChannel;

public:
	/**
	 * post: initializes `Television` and all the Channels in `channelList`
	 */
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

	/**
	 * pre: `Television` must be initialized
	 * post: calls the first `channelList` destructor
	 */
	virtual ~Television() {
		delete this->channelList;
	}

	/**
	 * pre: `Television` must be initialized
	 * post: returns the `currentChannel`
	 */
	Channel *getCurrentChannel() {
		return this->currentChannel;
	}

	/**
	 * pre: `Television` must be initialized
	 * post: sets the `currentChannel` to the next channel if is not the last
	 */
	void nextChannel() {
		if(currentChannel->getNext() != NULL) {
			currentChannel = currentChannel->getNext();
		}
	}

	/**
	 * pre: `Television` must be initialized
	 * post: sets the `currentChannel` to the previous channel if is not the first
	 */
	void prevChannel() {
		if(currentChannel->getPrev() != NULL) {
			currentChannel = currentChannel->getPrev();
		}
	}

	/**
	 * pre: `Television` must be initialized
	 * post: sets the `currentChannel` to the channel with index `channelIndex`
	 */
	void setChannel(int channelIndex) {
		if(channelIndex > CHANNELS_MAX) {
			channelIndex = CHANNELS_MAX;
		} else if(channelIndex < 0) {
			channelIndex = 0;
		}

		if(channelIndex < (int)currentChannel->getIndex()) {
			while(currentChannel->getPrev() != NULL) {
				if((int)currentChannel->getIndex() == channelIndex) {
					break;
				}
				currentChannel = currentChannel->getPrev();
			}
		} else if(channelIndex >= (int)currentChannel->getIndex()) {
			while(currentChannel->getNext() != NULL) {
				if((int)currentChannel->getIndex() == channelIndex) {
					break;
				}
				currentChannel = currentChannel->getNext();
			}
		}
	}


	/**
	 * pre: `Television` must be initialized
	 * post: mutes the `currentChannel`
	 */
	void muteChannel() {
		currentChannel->setMute();
	}

	/**
	 * pre: `Television` must be initialized
	 * post: unmutes the `currentChannel`
	 */
	void unmuteChannel() {
		currentChannel->unsetMute();
	}

	/**
	 * pre: `Television` must be initialized
	 * post: toggles the mute for the `currentChannel`
	 */
	void toggleMuteChannel() {
		currentChannel->toggleMute();
	}

	/**
	 * pre: `Television` must be initialized
	 * post: raises the volume of the `currentChannel`
	 */
	void raiseVolume() {
		currentChannel->setVolume(currentChannel->getVolume() + 10);
	}

	/**
	 * pre: `Television` must be initialized
	 * post: lowers the volume of the `currentChannel`
	 */
	void lowerVolume() {
		currentChannel->setVolume(currentChannel->getVolume() - 10);
	}

	/**
	 * pre: `Television` must be initialized
	 * post: sets the volume of the `currentChannel` to `volume`
	 */
	void setVolume(unsigned int volume) {
		currentChannel->setVolume(volume);
	}

	/**
	 * pre: `Television` must be initialized
	 * post: prints the main atributes of `Television` to `stdout`
	 */
	void printStatus() {
		std::cout << "channel:    " << this->currentChannel->getIndex()+1<< std::endl;
		std::cout << "volume:   " << this->currentChannel->getVolume() << "%\n";
		std::cout << "mute:   "
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

	delete tv;
	return 0;
}
