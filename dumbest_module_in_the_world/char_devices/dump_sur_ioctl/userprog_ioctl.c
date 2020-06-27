#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static int send_dump_ioctl(int fd) {

	/* The magic number used in our driver. */
	const unsigned type = 42;
	/* The subcommand we wish to invoke. In our driver, we
	 * chose to implement one: number 0. */
	const unsigned nr = 0;
	/* The ioctl has no direction (IOC_NONE), so we use _IOC(). */
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

	/*
	 * Send an ioctl to the device, so it dumps its contents.
	 */
	if (send_dump_ioctl(fd)) {
		fprintf(stderr, "Failed to send ioctl; errno=%d\n", errno);
		status = 1;
		goto close_fd;
	}

	/*
	 * Cleanup
	 */
close_fd:
	close(fd);
end:
	return status;
}
