#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static struct pollfd *create_pollfd(int fd) {

	struct pollfd *pfd = malloc(sizeof(*pfd) /* A single FD is needed */);
	if (! pfd) {
		fprintf(stderr, "Failed to allocate memory\n");
		return NULL;
	}

	pfd->fd = fd;
	pfd->events  = POLLIN;
	pfd->revents = 0;
	return pfd;
}

static int check_revents(struct pollfd *pfd) {

	if (pfd->revents & POLLERR  || /* Error while polling */
	    pfd->revents & POLLHUP  || /* FD was closed */
	    pfd->revents & POLLNVAL || /* Invalid polling request */
	    ! pfd->revents & POLLIN /* We want to be able to read */) {
		return 1;
	}
	return 0;
}

static int send_dump_ioctl(int fd) {

	/* The magic number used in our driver. */
	const unsigned type = 42;
	/* The subcommand we wish to invoke. In our driver, we
	 * chose to implement one: number 0. */
	const unsigned nr = 0;
	/* The ioctl has no direction (IOC_NONE), so we use _IO(). */
	const unsigned cmd = _IO(type, nr);

	if (ioctl(fd, cmd, NULL /* No args */) == -1) {
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {

	int status = 0;

	if (argc != 2) {
		fprintf(stderr, "Expected 1 argument (device path)\n");
		status = 1;
		goto end;
	}

	const char *dev = argv[1];
	int fd = open(dev, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Failed to open %s; errno=%d\n", dev, errno);
		status = 1;
		goto end;
	}

	struct pollfd *pfd = create_pollfd(fd);
	if (! pfd) {
		fprintf(stderr, "Failed to setup pollfd\n");
		status = 1;
		goto close_fd;
	}

	/*
	 * Wait indefinitely for a read to be available.
	 * We may be interrupted by a signal; in which case we fail.
	 */
	int pollres = poll(pfd, 1, -1 /* Infinite timeout */);
	if (pollres == -1) {
		fprintf(stderr, "Failed to poll event; errno=%d\n", errno);
		status = 1;
		goto free_mem;
	}

	/*
	 * Check if the events we got are what we want.
	 */
	if (check_revents(pfd)) {
		fprintf(stderr, "Polling events not as expected\n");
		status = 1;
		goto free_mem;
	}

	/*
	 * Send an ioctl to the device, so it dumps its contents.
	 */
	if (send_dump_ioctl(fd)) {
		fprintf(stderr, "Failed to send ioctl; errno=%d\n", errno);
		status = 1;
		goto free_mem;
	}

	/*
	 * Cleanup
	 */
free_mem:
	free(pfd);
close_fd:
	close(fd);
end:
	return status;
}
