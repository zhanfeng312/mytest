#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main (void) {
	int fd = open ("trunc.txt", O_RDONLY);
	if (fd == -1) {
		perror ("open");
		return -1;
	}

	struct stat st;
	if (fstat (fd, &st) == -1) {
		perror ("fstat");
		return -1;
	}

	void* map = mmap (NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED) {
		perror ("mmap");
		return -1;
	}

	printf ("%s\n", map);

	munmap (map, st.st_size);
	close (fd);

	return 0;
}
