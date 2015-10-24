#include <stdio.h>
#include <stdlib.h>

struct
{ 
	unsigned char	RIFF[4]; 
	unsigned long	FileSize; 
	unsigned char	WAVEfmt[8]; 
	unsigned long	chunksize; 
	unsigned short	wformattag; 
	unsigned short	wchannels; 
	unsigned long	dwsamplespersec; 
	unsigned long	dwavgbytespersec; 
	unsigned short	wblockalign; 
	unsigned short	wbitspersample; 
	unsigned char	data[4]; 
	unsigned long	datasize; 
} wavh =
{
	{ 'R', 'I', 'F', 'F' },
	0xffff,
	{ 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ' },
	0x10,
	0x01,
	0x01,
	44100,
	88200,
	2,
	16,
	{ 'd', 'a', 't', 'a' },
	-1
};

char buf[1024 * 1024];

int
main(int argc, char* argv[])
{
	FILE* f;
	size_t size;
	if (argc < 4)
		return -1;
	f = fopen(argv[1], "rb");
	if (!f)
		return -1;
	size = fread(buf, 1, sizeof(buf), f);
	fclose(f);
	wavh.datasize = size;
	wavh.FileSize = size + sizeof(wavh) - 8;
	wavh.wchannels = 1;
	wavh.wbitspersample = 8;
	wavh.dwsamplespersec = atoi(argv[3]);
	wavh.wblockalign = wavh.wchannels * wavh.wbitspersample / 8;
	wavh.dwavgbytespersec = wavh.wblockalign * wavh.dwsamplespersec;
	f = fopen(argv[2], "wb");
	fwrite(&wavh, 1, sizeof(wavh), f);
	fwrite(buf, 1, size, f);
	fclose(f);
	return 0;
}
