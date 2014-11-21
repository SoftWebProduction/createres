///
///    Load an image
///
SDL_Surface *LoadBitmap(char *resourcefilename, char *bitmapfilename)
{
  //Get the bitmap's buffer and size from the resource file
	int filesize = 0;
	char *buffer = GetBufferFromResource(resourcefilename, bitmapfilename, &filesize);

	//Load the buffer into a surface using RWops
	SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
	SDL_Surface *temp = SDL_LoadBMP_RW(rw, 1);

	//Release the bitmap buffer memory
	free(buffer);

	//Were we able to load the bitmap?
	if (temp == NULL)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		exit(1);
	}

	//Convert the image to optimal display format
	SDL_Surface *image;
	image = SDL_DisplayFormat(temp);

	//Free the temporary surface
	SDL_FreeSurface(temp);

	//Return our loaded image
	return image;
}

///
///    Load a sound using Mix_Chunk
///
Mix_Chunk *LoadSound(char *resourcefilename, char *soundfilename)
{
	//Get the sound's buffer and size from the resource file
	int filesize = 0;
	char *buffer = GetBufferFromResource(resourcefilename, soundfilename, &filesize);

	//Load the buffer into a surface using RWops
	SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
	Mix_Chunk *sound = Mix_LoadWAV_RW(rw, 1);

	//Release the buffer memory
	free(buffer);

	//Return the sound
	return sound;
}

///
///    Load a music using Mix_Music
///
Mix_Music *LoadMusic(char *resourcefilename, char *soundfilename)
{
	//Get the sound's buffer and size from the resource file
	int filesize = 0;
	char *buffer = GetBufferFromResource(resourcefilename, soundfilename, &filesize);

	//Load the buffer into a surface using RWops
	SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
	Mix_Music *sound = Mix_LoadMUS_RW(rw);

	//You can't free the buffer, otherwise the App crashes
	//free(buffer);

	//Return the sound
	return sound;
}
