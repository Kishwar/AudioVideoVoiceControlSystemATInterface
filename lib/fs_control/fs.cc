/**
 * @file fs.cc
 *
 * @brief responsible for file system operations
 *
 * @ingroup fs_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

#include "fs.h"

static FileSystem *instance = nullptr;

FileSystem& FileSystem::getInstance() {
  if(instance == nullptr) {
    instance = new FileSystem();
  }

  return *instance;
}

void FileSystem::run(void) {
  
}