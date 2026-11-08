#ifndef sdmanager_h
#define sdmanager_h
#include <FS.h>
#include <SD_MMC.h>

// Wrapper class for SD_MMC to maintain API compatibility
class SDManager {
  private:
    fs::FS* _fs;
  public:
    bool ready;
  public:
    SDManager() : _fs(&SD_MMC), ready(false) {}
    
    // Make it implicitly convertible to fs::FS&
    operator fs::FS&() { return *_fs; }
    fs::FS& getFS() { return *_fs; }
    
    bool start();
    void stop();
    bool cardPresent();
    void listSD(File &plSDfile, File &plSDindex, const char * dirname, uint8_t levels);
    void indexSDPlaylist();
  private:
    uint32_t _sdFCount;
  private:
    bool _checkNoMedia(const char* path);
    bool _endsWith (const char* base, const char* str);
};

extern SDManager sdman;
#if defined(SD_SPIPINS) || SD_HSPI
extern SPIClass  SDSPI;
#endif
#endif
