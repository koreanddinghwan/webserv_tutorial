#include "EventBlock.conf.hpp"

EventBlock::EventBlock(std::ifstream &File) {
	this->parse(File);
}

void EventBlock::parse(std::ifstream &File) 
{
	int cur_offset = File.tellg();
	std::string buf;

	std::getline(File, buf);
	while (buf.length() == 0)
		std::getline(File, buf);

	std::cout<<buf<<std::endl;
	if (buf.find("events") == std::string::npos)
	{
		File.seekg(cur_offset);
		this->confData.worker_connections = 1024;
		std::cout<<"\033[31m"<<"worker_connection is set 1024"<< "\033[0m" <<std::endl;
		return ;
	}
	else
	{
		strSplit spl;

		std::getline(File, buf);
		strSplit::strPair splited = spl.split(buf, ' ');
		this->confData.worker_connections = std::atoi(splited.second.c_str());

		//push into next field
		while (buf.find("}") == std::string::npos)
			std::getline(File, buf);
	}
}


void *EventBlock::getConfigData() {
	return &this->confData;
}

EventBlock::~EventBlock() {}
