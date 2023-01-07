/**
 * @file fs.h
 *
 * @brief responsible for file system operations
 *
 * @ingroup fs_control
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 *
 */

class FileSystem {

public:
  static FileSystem& getInstance(void);
  void run(void);

  FileSystem(const FileSystem&) = delete;     // copy constructor deleted
  FileSystem(const FileSystem&&) = delete;    // move constructor deleted

private:
  FileSystem();
};