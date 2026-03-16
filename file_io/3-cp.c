#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * error_exit - prints an error message and exits with code
 * @code: exit code
 * @msg: message to print
 * @file: filename or fd value
 */
void error_exit(int code, char *msg, char *file)
{
	if (file != NULL)
		dprintf(STDERR_FILENO, "%s %s\n", msg, file);
	else
		dprintf(STDERR_FILENO, "%s\n", msg);
	exit(code);
}

/**
 * open_file_from - opens the source file for reading
 * @filename: source filename
 *
 * Return: file descriptor
 */
int open_file_from(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(98, "Error: Can't read from file", filename);
	return (fd);
}

/**
 * open_file_to - opens/creates the destination file for writing
 * @filename: destination filename
 *
 * Return: file descriptor
 */
int open_file_to(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		error_exit(99, "Error: Can't write to", filename);
	return (fd);
}

/**
 * copy_file - copies content from one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 */
void copy_file(int fd_from, int fd_to)
{
	ssize_t r, w;
	char buffer[BUFFER_SIZE];

	while ((r = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		w = write(fd_to, buffer, r);
		if (w != r)
			error_exit(99, "Error: Can't write to", NULL);
	}

	if (r == -1)
		error_exit(98, "Error: Can't read from file", NULL);
}

/**
 * close_fd - closes a file descriptor and checks for error
 * @fd: file descriptor to close
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
		error_exit(97, "Usage: cp file_from file_to", NULL);

	fd_from = open_file_from(argv[1]);
	fd_to = open_file_to(argv[2]);
	copy_file(fd_from, fd_to);
	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
