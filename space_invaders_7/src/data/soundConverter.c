#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct wavfile
{
    char        id[4];          // should always contain "RIFF"
    int     totallength;    // total file length minus 8
    char        wavefmt[8];     // should be "WAVEfmt "
    int     format;         // 16 for PCM format
    short     pcm;            // 1 for PCM format
    short     channels;       // channels
    int     frequency;      // sampling frequency
    int     bytes_per_second;
    short     bytes_by_capture;
    short     bits_per_sample;
    char        data[4];        // should always contain "data"
    int     bytes_in_data;
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("USAGE: filein.wav fileout");
    return -1;
  }

  char *filename=argv[1];
  FILE *wav = fopen(filename,"rb");
  FILE *fo = fopen(argv[2], "w");

  struct wavfile header;

  if ( wav == NULL ) {
    fprintf(stderr,"Can't open input file %s", filename);
    exit(1);
  }

  // read header
  if ( fread(&header,sizeof(header),1,wav) < 1 )
  {
    fprintf(stderr,"Can't read file header\n");
    exit(1);
  }
  if (    header.id[0] != 'R'
    || header.id[1] != 'I' 
    || header.id[2] != 'F' 
    || header.id[3] != 'F' ) { 
    fprintf(stderr,"ERROR: Not wav format\n"); 
    exit(1); 
  }

  fprintf(stderr,"wav format\n");

  // read data
  long sum=0;
  char value=0;
    
  fprintf(fo, "%s_soundData[] = {", argv[2]);
  while( fread(&value,sizeof(value),1,wav) ) {
    if (value<0) { value=-value; }
    fprintf(fo, "%d,", value);
      //  sum += value;
  }
  //printf("%ld\n",count);
  fprintf(fo, "0};\n");
  fprintf(fo, "%s_numberOfSamples = %d;\n", argv[2], header.bytes_in_data);
  fprintf(fo, "%s_sampleRate = %d;\n", argv[2], header.bits_per_sample);

  fclose(wav);
  fclose(fo);
  exit(0);
}
