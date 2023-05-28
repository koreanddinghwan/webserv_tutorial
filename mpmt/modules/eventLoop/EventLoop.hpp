#ifndef EVENTLOOP_HPP
# define EVENTLOOP_HPP

#include "../../exceptions/httpException.hpp"
#include <cstdlib>
#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/event.h>
#include <stdexcept>
#include "../config/Config.hpp"
#include "../../interface/IBlock.hpp"
#include "../http/HttpServer.hpp"
#include "Event.hpp"
#include "../http/response.hpp"

/**
 * @brief singleton eventloop
 */
class EventLoop
{
public:
	/**
	 * @brief get instance of eventloop
	 *
	 * @return eventloop instance
	 */
	static EventLoop& getInstance();

	/**
	 * @brief init event
	 */
	void initEvent();

	/**
	 * @brief init eventloop
	 * 핵심모듈
	 */
	void initEventLoop();

private:
	int kq_fd;

	struct kevent dummyEvent;

	struct sockaddr_in dummy_addr;

private:
	EventLoop();
	~EventLoop();
	void printCurrentData();
	void registerInitialEvent(struct kevent *kev);


	void readCallback(struct kevent *e);
	void writeCallback(struct kevent *e);

	void e_serverSocketReadCallback(struct kevent *e, Event *e_udata);
	void e_clientSocketReadCallback(struct kevent *e, Event *e_udata);
	void e_pipeReadCallback(struct kevent *e, Event *e_udata);
	void e_fileReadCallback(struct kevent *e, Event *e_udata);


	void e_clientSocketWriteCallback(struct kevent *e, Event *e_udata);
	void e_pipeWriteCallback(struct kevent *e, Event *e_udata);
	void e_fileWriteCallback(struct kevent *e, Event *e_udata);

	/**
	 * kqueue에 event를 등록합니다.
	 * */
	void registerClientSocketReadEvent(Event *e);
	void registerPipeReadEvent(Event *e);
	void registerFileReadEvent(Event *e);
	void registerClientSocketWriteEvent(Event *e);
	void registerPipeWriteEvent(Event *e);
	void registerFileWriteEvent(Event *e);
	void registerRequestHttpExceptionEvent(Event *e);
	void registerResponseHttpExceptionEvent(Event *e);
};


#endif
