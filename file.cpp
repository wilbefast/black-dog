#include "file.hpp"

#include "assert.hpp"
#include "warn.hpp"

using namespace io;

int io::read_text(const char* source_file, char** destination)
{
    // Open the file
    SDL_RWops* file;
    file = SDL_RWFromFile(source_file, "r");
    ASSERT(file, "Opening text file using SDL_RWops");

    // Find the length of the file
    int file_length = SDL_RWseek(file, 0, SEEK_END);
    (*destination) = new char[file_length];

    // Reset seek to beginning of file and read text
    SDL_RWseek(file, 0, SEEK_SET);
    int n_blocks = SDL_RWread(file, (*destination), BLOCK_SIZE, MAX_BLOCKS);
    SDL_RWclose(file);
    // Make sure the operation was successful
    ASSERT(n_blocks >= 0, "Reading blocks of data from SDL_RWops");
    WARN_IF(n_blocks == MAX_BLOCKS, "Reading data from SDL_RWops",
                                    "Buffer full so may be too small for data");

    // Success!
    return EXIT_SUCCESS;
}

int io::read_music(const char* source_file, Mix_Music** music)
{
  // Attempt to open the music file
  SDL_RWops* binary_file;
  binary_file = SDL_RWFromFile(source_file, "rb"); // read binary
  ASSERT(binary_file, "Opening music file using SDL_RWops");

  // Attempt to read the file contents as music
  ASSERT_MIX((*music) = Mix_LoadMUS_RW(binary_file),
              "Extracting music from SDL_RWops structure");

  // Success !
  SDL_RWclose(binary_file);
  return EXIT_SUCCESS;
}

/*int io::read_xml(const char* file_name, TiXmlDocument* doc)
{
    #if BUFFER_XML
        // Open with SDL_RWops, read contents to a buffer
        char* file_contents = NULL;
        ASSERT(io::read_text(file_name, &file_contents) == EXIT_SUCCESS,
                "Reading XML file to buffer");

        // Pass the buffer to the TinyXML document
        ASSERT_AUX(doc->Parse(file_contents), "Parsing XML buffer",
                   doc->ErrorDesc());
        // Delete the buffer
        delete file_contents;
    #else
        // Open normally, without an intermediate buffer
        doc->SetValue(file_name);
        ASSERT_AUX(doc->LoadFile(), "Loading XML file directly",
                    doc->ErrorDesc());
    #endif

    // All clear
    return EXIT_SUCCESS;
}*/
