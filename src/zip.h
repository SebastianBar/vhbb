#pragma once

#include <cstdio>
#include <cstring>

#include <global_include.h>

#include <minizip/unzip.h>
#include "infoProgress.h"


class Zipfile {
public:
  explicit Zipfile(std::string zip_path);
  ~Zipfile();

  int Unzip(std::string outpath, InfoProgress progress);
  int Unzip(std::string outpath, InfoProgress *progress = nullptr);

  int UncompressedSize(InfoProgress progress);
  int UncompressedSize(InfoProgress *progress = nullptr);

private:
  unzFile zipfile_;
  uint64_t uncompressed_size_ = 0;
  unz_global_info global_info_;
};
