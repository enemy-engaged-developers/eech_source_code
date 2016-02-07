#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *f;
	char buf[256];

	if (argc != 2)
	{
		printf("Usage: %s file.exe\n", argv[0]);
		return -1;
	}

	f = fopen(argv[1], "r+b");
	if (!f)
	{
		printf("Failed to open %s\n", argv[1]);
		return -2;
	}

	if (fread(buf, 1, sizeof(buf), f) != sizeof(buf))
	{
		printf("Failed to read %s\n", argv[1]);
		return -3;
	}

	if (buf[0x86] == 0x82 && !buf[0xC8] && !buf[0xC9] && !buf[0xCA])
	{
		buf[0x86] = 0xA2;
		buf[0xC8] = 0x2F;
		buf[0xC9] = 0x0B;
		buf[0xCA] = 0x55;
	}
	else
	{
#if 0
		if (buf[0x86] == 0xA2 && buf[0xC8] == 0x2F && buf[0xC9] == 0x0B && buf[0xCA] == 0x55)
		{
			buf[0x86] = 0x82;
			buf[0xC8] = 0x00;
			buf[0xC9] = 0x00;
			buf[0xCA] = 0x00;
		}
		else
#endif
		{
			printf("Unexpected header in %s\n", argv[1]);
			return -4;
		}
	}


	fseek(f, 0, SEEK_SET);

	if (fwrite(buf, 1, sizeof(buf), f) != sizeof(buf))
	{
		printf("Failed to write %s\n", argv[1]);
		return -5;
	}

	fclose(f);

	return 0;
}
