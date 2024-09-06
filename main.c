#include <mem.h>
#include <scanner.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct bfile bfile;

struct bfile
{
	unsigned char *buffer;
	size_t         len;
};

static void  run_file(const char *path);
static bfile read_file(char *path);

int main(int argc, char **argv)
{

	if (argc == 2)
		run_file(argv[1]);
	else
	{
		fprintf(stderr, "USAGE: ykes [path]\n");
		exit(69);
	}

	return 0;
}

static void run_file(const char *path)
{
	bfile buff;
	buff = read_file((char *)path);

	token t;

	int adr = 0;
	for (size_t i = 0; i < buff.len; i++)
	{

		unsigned char *b = (buff.buffer + i);
		t                = make_token(&b);
		i += t.meta.argc;

		if (i % 16 == 0 && i != 0)
			adr = i;
		printf(
		    "%06x\t\top_code: 0x%x, instruction: %s, argc: %d\n", adr, t.op,
		    t.meta.name, t.meta.argc
		);
		for (int j = 0; j < t.meta.argc; j++)
			printf(
			    "%06x\t\targ%d: 0x%x\n", adr, j + 1, *(t.meta.argv + j)
			);
	}
}

static int str_len(char *str)
{
	int   count = 0;
	char *s     = str;

	while ((*s++))
		count++;
	return count;
}

static void strip_path(char *str)
{
	int   len = str_len(str) - 1;
	char *s   = str + len;

	for (; *s != '/'; --s, --len)
		;

	str[len + 1] = '\0';
}

static char *get_name(char *path)
{
	int   len = strlen(path) - 1;
	char *tmp = path + len;

	int count;
	for (count = 0; tmp[-1] != '/'; --tmp, count++)
		;

	char *file = ALLOC((count + 1) * sizeof(char));

	strcpy(file, tmp);

	return file;
}

static char *get_full_path(char *path)
{
	// char res[PATH_MAX] = {0};

	char *ptr = NULL;
	char *tmp = NULL;
	tmp       = realpath(path, NULL);

	if (tmp)
	{
		ptr = ALLOC(strlen(tmp));
		strcpy(ptr, tmp);
	}
	else
	{
		fprintf(stderr, "Could not open file \"%s\".\n", path);
		exit(74);
	}
	return ptr;
}

static bfile read_file(char *path)
{
	FILE *file = NULL;
	bfile b;
	if (path)
		file = fopen(path, "rb");
	else if (!file)
	{
		fprintf(stderr, "Could not open file \"%s\".\n", path);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	unsigned char *buffer = NULL;
	buffer                = ALLOC(fileSize + 1);

	if (!buffer)
	{
		fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
		exit(74);
	}
	size_t bytesRead  = fread(buffer, sizeof(char), fileSize, file);
	buffer[bytesRead] = '\0';

	b.buffer = NULL;
	b.buffer = buffer;
	b.len    = bytesRead;
	fclose(file);
	FREE(path);
	return b;
}
