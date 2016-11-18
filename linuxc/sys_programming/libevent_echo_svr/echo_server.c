/* 
 * An echo unix socket server based on libevent library
 */

#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define UNIX_SOCK_PATH "/tmp/mysocket"

static void
accept_conn_cb(struct evconnlistener *listener, 
	evutil_socket_t fd, struct sockaddr *address, 
	int socklen, void *ctx);
static void accept_error_cb(struct evconnlistener *listener, void *ctx);
static void echo_read_cb(struct bufferevent *bev, void *ctx);
static void echo_event_cb(struct bufferevent *bev, short events, void *ctx);


int main(int argc, char const *argv[])
{
	struct event_base *base;
	struct evconnlistener *listener;
	struct sockaddr_un sin;

	base = event_base_new();
	if (!base) {
		puts("Couldn't open event base");
		return 1;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sun_family = AF_LOCAL;
	strcpy(sin.sun_path, UNIX_SOCK_PATH);

	listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
		LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1, 
		(struct sockaddr *)&sin, sizeof(sin));
	if (!listener) {
		perror("Couldn't create listener");
		return 1;
	}
	evconnlistener_set_error_cb(listener, accept_error_cb);

	event_base_dispatch(base);

	return 0;
}

/*
	Allow libevent to handle when a new connection is created

	Details: When an event listener got a new connection,
	then setting up a bufferevent for it. 

	@param listener	event listener
	@param fd			socket file discriptor
	@param address
	@param socklen
	@param ctx			connection buffer context	
 */
static void
accept_conn_cb(struct evconnlistener *listener, 
	evutil_socket_t fd, struct sockaddr *address, 
	int socklen, void *ctx)
{
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);

	bufferevent_enable(bev, EV_READ|EV_WRITE);

}

/*
	Allow libevent to handle what to do when the listener encounters an error

	@param listener	event listener
	@param ctx			connection buffer context		
 */
static void accept_error_cb(struct evconnlistener *listener, void *ctx)
{
	struct event_base *base = evconnlistener_get_base(listener);
	int err = EVUTIL_SOCKET_ERROR();
	fprintf(stderr, "Got an error %d(%s) on the listener. " 
		"Shutting down.\n", err, evutil_socket_error_to_string(err));

	event_base_loopexit(base, NULL);
}

/*
	This callback is invoked when there is data to read on bufferevent

	@param bev  given bufferevent
	@param ctx  connection buffer context
 */
static void echo_read_cb(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *inputbuff = bufferevent_get_input(bev);
	struct evbuffer *outputbuff = bufferevent_get_output(bev);

	size_t len = evbuffer_get_length(inputbuff);
	char *data;
	char *echo_data = NULL;
	data = (char *)malloc(len);
	evbuffer_copyout(inputbuff, data, len);

	printf("we got some data from kernel eventbuffer: %s\n", data);

	echo_data = (char *)malloc(sizeof("Welcome, client..."));
	strcpy(echo_data, "Welcome, client...");
	evbuffer_add_printf(outputbuff, "%s\n", echo_data);
	// evbuffer_add(inputbuff, "\n", sizeof("\n"));
	// evbuffer_add_buffer(outputbuff, inputbuff);/*copy all the data from the input buffer to the output buffer*/
	free(data);
	free(echo_data);
}

/*
	This event callback is triggered if either an EOF condition or another
	unrecoverable error was encountered.

	@param bev     the bufferevent for which the error condition was reached
	@param events  a conjunction of flags: BEV_EVENT_READING or BEV_EVENT_WRITING
	  to indicate if the error was encountered on the read or write path,
	  and one of the following flags: BEV_EVENT_EOF, BEV_EVENT_ERROR,
	  BEV_EVENT_TIMEOUT, BEV_EVENT_CONNECTED.
	@param ctx     the user-specified context for bufferevent bev
 */
static void echo_event_cb(struct bufferevent *bev, short events, void *ctx)
{
	if (events & BEV_EVENT_ERROR) {
		perror("Error from bufferevent");
	}
	if (events & (BEV_EVENT_EOF|BEV_EVENT_ERROR)) {
		bufferevent_free(bev);/*deallocate the storage associated with a bufferevent structure.*/
	}
}