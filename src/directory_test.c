#include "constants.h"
#include "directory.h"
#include "macros.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <string.h>

void test__serialize_directory_entry_1() {
  const DirectoryEntry entry = {
    .filename = "image.png",
    .first_fat_table_record = 465416,
  };
  unsigned char serialized_entry[] = INITIALIZE(DIRECTORY_ENTRY_SIZE_IN_BYTES, 0);
  serialize_directory_entry(&entry, serialized_entry);
  CU_ASSERT_EQUAL(serialized_entry[0], 'i');
  CU_ASSERT_EQUAL(serialized_entry[1], 'm');
  CU_ASSERT_EQUAL(serialized_entry[2], 'a');
  CU_ASSERT_EQUAL(serialized_entry[3], 'g');
  CU_ASSERT_EQUAL(serialized_entry[4], 'e');
  CU_ASSERT_EQUAL(serialized_entry[5], '.');
  CU_ASSERT_EQUAL(serialized_entry[6], 'p');
  CU_ASSERT_EQUAL(serialized_entry[7], 'n');
  CU_ASSERT_EQUAL(serialized_entry[8], 'g');
  CU_ASSERT_EQUAL(serialized_entry[9], '\000');
  CU_ASSERT_EQUAL(serialized_entry[10], '\000');
  CU_ASSERT_EQUAL(serialized_entry[11], '\000');
  CU_ASSERT_EQUAL(serialized_entry[12], '\000');
  CU_ASSERT_EQUAL(serialized_entry[13], '\000');
  CU_ASSERT_EQUAL(serialized_entry[14], '\000');
  CU_ASSERT_EQUAL(serialized_entry[15], '\000');
  CU_ASSERT_EQUAL(serialized_entry[16], '\000');
  CU_ASSERT_EQUAL(serialized_entry[17], '\000');
  CU_ASSERT_EQUAL(serialized_entry[18], '\000');
  CU_ASSERT_EQUAL(serialized_entry[19], '\000');
  CU_ASSERT_EQUAL(serialized_entry[20], '\000');
  CU_ASSERT_EQUAL(serialized_entry[21], 8);
  CU_ASSERT_EQUAL(serialized_entry[22], 26);
  CU_ASSERT_EQUAL(serialized_entry[23], 7);
}

void test__serialize_directory_entry_2() {
  const DirectoryEntry entry = {
    .filename = "Naghibzadeh.mp3",
    .first_fat_table_record = 683102,
  };
  unsigned char serialized_entry[] = INITIALIZE(DIRECTORY_ENTRY_SIZE_IN_BYTES, 0);
  serialize_directory_entry(&entry, serialized_entry);
  CU_ASSERT_EQUAL(serialized_entry[0], 'N');
  CU_ASSERT_EQUAL(serialized_entry[1], 'a');
  CU_ASSERT_EQUAL(serialized_entry[2], 'g');
  CU_ASSERT_EQUAL(serialized_entry[3], 'h');
  CU_ASSERT_EQUAL(serialized_entry[4], 'i');
  CU_ASSERT_EQUAL(serialized_entry[5], 'b');
  CU_ASSERT_EQUAL(serialized_entry[6], 'z');
  CU_ASSERT_EQUAL(serialized_entry[7], 'a');
  CU_ASSERT_EQUAL(serialized_entry[8], 'd');
  CU_ASSERT_EQUAL(serialized_entry[9], 'e');
  CU_ASSERT_EQUAL(serialized_entry[10], 'h');
  CU_ASSERT_EQUAL(serialized_entry[11], '.');
  CU_ASSERT_EQUAL(serialized_entry[12], 'm');
  CU_ASSERT_EQUAL(serialized_entry[13], 'p');
  CU_ASSERT_EQUAL(serialized_entry[14], '3');
  CU_ASSERT_EQUAL(serialized_entry[15], '\000');
  CU_ASSERT_EQUAL(serialized_entry[16], '\000');
  CU_ASSERT_EQUAL(serialized_entry[17], '\000');
  CU_ASSERT_EQUAL(serialized_entry[18], '\000');
  CU_ASSERT_EQUAL(serialized_entry[19], '\000');
  CU_ASSERT_EQUAL(serialized_entry[20], '\000');
  CU_ASSERT_EQUAL(serialized_entry[21], 94);
  CU_ASSERT_EQUAL(serialized_entry[22], 108);
  CU_ASSERT_EQUAL(serialized_entry[23], 10);
}

void test__serialize_directory_entry_3() {
  const DirectoryEntry entry = {
    .filename = "Naghi zadeh-w lx.mp3",
    .first_fat_table_record = 2123,
  };
  unsigned char serialized_entry[] = INITIALIZE(DIRECTORY_ENTRY_SIZE_IN_BYTES, 0);
  serialize_directory_entry(&entry, serialized_entry);
  CU_ASSERT_EQUAL(serialized_entry[0], 'N');
  CU_ASSERT_EQUAL(serialized_entry[1], 'a');
  CU_ASSERT_EQUAL(serialized_entry[2], 'g');
  CU_ASSERT_EQUAL(serialized_entry[3], 'h');
  CU_ASSERT_EQUAL(serialized_entry[4], 'i');
  CU_ASSERT_EQUAL(serialized_entry[5], ' ');
  CU_ASSERT_EQUAL(serialized_entry[6], 'z');
  CU_ASSERT_EQUAL(serialized_entry[7], 'a');
  CU_ASSERT_EQUAL(serialized_entry[8], 'd');
  CU_ASSERT_EQUAL(serialized_entry[9], 'e');
  CU_ASSERT_EQUAL(serialized_entry[10], 'h');
  CU_ASSERT_EQUAL(serialized_entry[11], '-');
  CU_ASSERT_EQUAL(serialized_entry[12], 'w');
  CU_ASSERT_EQUAL(serialized_entry[13], ' ');
  CU_ASSERT_EQUAL(serialized_entry[14], 'l');
  CU_ASSERT_EQUAL(serialized_entry[15], 'x');
  CU_ASSERT_EQUAL(serialized_entry[16], '.');
  CU_ASSERT_EQUAL(serialized_entry[17], 'm');
  CU_ASSERT_EQUAL(serialized_entry[18], 'p');
  CU_ASSERT_EQUAL(serialized_entry[19], '3');
  CU_ASSERT_EQUAL(serialized_entry[20], '\000');
  CU_ASSERT_EQUAL(serialized_entry[21], 75);
  CU_ASSERT_EQUAL(serialized_entry[22], 8);
  CU_ASSERT_EQUAL(serialized_entry[23], 0);
}

const short int SERIALIZED_DIRECTORY_FILE_IN_BYTES = ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES + 2 + 2;

void test__serialize_directory_file_1() {
  const DirectoryFile file = {
    .capacity = ROOT_DIRECTORY_MAX_FILES,
    .length = 0,
  };
  unsigned char output[] = INITIALIZE(SERIALIZED_DIRECTORY_FILE_IN_BYTES, 0);

  serialize_directory_file(&file, output);

  CU_ASSERT_EQUAL(output[0], 32);
  CU_ASSERT_EQUAL(output[1], 0);
  CU_ASSERT_EQUAL(output[2], 0);
  CU_ASSERT_EQUAL(output[3], 0);
  for (size_t i = 4; i < SERIALIZED_DIRECTORY_FILE_IN_BYTES; i++) {
    CU_ASSERT_EQUAL(output[i], 0);
  }
}

void test__serialize_directory_file_2() {
  const DirectoryEntry entry = {
    .filename = "naghibzadeh.mp4",
    .first_fat_table_record = 14564,
  };
  const DirectoryFile file = {
    .capacity = ROOT_DIRECTORY_MAX_FILES,
    .length = 1,
    .directory_entries = {entry},
  };
  unsigned char output[] = INITIALIZE(SERIALIZED_DIRECTORY_FILE_IN_BYTES, 0);

  serialize_directory_file(&file, output);

  CU_ASSERT_EQUAL(output[0], 32);
  CU_ASSERT_EQUAL(output[1], 0);
  CU_ASSERT_EQUAL(output[2], 1);
  CU_ASSERT_EQUAL(output[3], 0);

  CU_ASSERT_EQUAL(output[4], 'n');
  CU_ASSERT_EQUAL(output[5], 'a');
  CU_ASSERT_EQUAL(output[6], 'g');
  CU_ASSERT_EQUAL(output[7], 'h');
  CU_ASSERT_EQUAL(output[8], 'i');
  CU_ASSERT_EQUAL(output[9], 'b');
  CU_ASSERT_EQUAL(output[10], 'z');
  CU_ASSERT_EQUAL(output[11], 'a');
  CU_ASSERT_EQUAL(output[12], 'd');
  CU_ASSERT_EQUAL(output[13], 'e');
  CU_ASSERT_EQUAL(output[14], 'h');
  CU_ASSERT_EQUAL(output[15], '.');
  CU_ASSERT_EQUAL(output[16], 'm');
  CU_ASSERT_EQUAL(output[17], 'p');
  CU_ASSERT_EQUAL(output[18], '4');
  CU_ASSERT_EQUAL(output[19], '\000');
  CU_ASSERT_EQUAL(output[20], '\000');
  CU_ASSERT_EQUAL(output[21], '\000');
  CU_ASSERT_EQUAL(output[22], '\000');
  CU_ASSERT_EQUAL(output[23], '\000');
  CU_ASSERT_EQUAL(output[24], '\000');
  CU_ASSERT_EQUAL(output[25], 228);
  CU_ASSERT_EQUAL(output[26], 56);
  CU_ASSERT_EQUAL(output[27], 0);

  for (size_t i = 27; i < SERIALIZED_DIRECTORY_FILE_IN_BYTES; i++) {
    CU_ASSERT_EQUAL(output[i], 0);
  }
}

void test__serialize_directory_file_3() {
  const DirectoryEntry entry_1 = {
    .filename = "naghibzadeh.mp4",
    .first_fat_table_record = 14564,
  };
  const DirectoryEntry entry_2 = {
    .filename = "file-test  +-x o.jpg",
    .first_fat_table_record = 684571,
  };
  const DirectoryFile file = {
    .capacity = ROOT_DIRECTORY_MAX_FILES,
    .length = 2,
    .directory_entries = {entry_1, entry_2},
  };
  unsigned char output[] = INITIALIZE(SERIALIZED_DIRECTORY_FILE_IN_BYTES, 0);

  serialize_directory_file(&file, output);

  CU_ASSERT_EQUAL(output[0], 32);
  CU_ASSERT_EQUAL(output[1], 0);
  CU_ASSERT_EQUAL(output[2], 1);
  CU_ASSERT_EQUAL(output[3], 0);

  CU_ASSERT_EQUAL(output[4], 'n');
  CU_ASSERT_EQUAL(output[5], 'a');
  CU_ASSERT_EQUAL(output[6], 'g');
  CU_ASSERT_EQUAL(output[7], 'h');
  CU_ASSERT_EQUAL(output[8], 'i');
  CU_ASSERT_EQUAL(output[9], 'b');
  CU_ASSERT_EQUAL(output[10], 'z');
  CU_ASSERT_EQUAL(output[11], 'a');
  CU_ASSERT_EQUAL(output[12], 'd');
  CU_ASSERT_EQUAL(output[13], 'e');
  CU_ASSERT_EQUAL(output[14], 'h');
  CU_ASSERT_EQUAL(output[15], '.');
  CU_ASSERT_EQUAL(output[16], 'm');
  CU_ASSERT_EQUAL(output[17], 'p');
  CU_ASSERT_EQUAL(output[18], '4');
  CU_ASSERT_EQUAL(output[19], ' ');
  CU_ASSERT_EQUAL(output[20], ' ');
  CU_ASSERT_EQUAL(output[21], ' ');
  CU_ASSERT_EQUAL(output[22], ' ');
  CU_ASSERT_EQUAL(output[23], ' ');
  CU_ASSERT_EQUAL(output[24], 228);
  CU_ASSERT_EQUAL(output[25], 56);
  CU_ASSERT_EQUAL(output[26], 0);

  CU_ASSERT_EQUAL(output[27], 'f');
  CU_ASSERT_EQUAL(output[28], 'i');
  CU_ASSERT_EQUAL(output[29], 'l');
  CU_ASSERT_EQUAL(output[30], 'e');
  CU_ASSERT_EQUAL(output[31], '-');
  CU_ASSERT_EQUAL(output[32], 't');
  CU_ASSERT_EQUAL(output[33], 'e');
  CU_ASSERT_EQUAL(output[34], 's');
  CU_ASSERT_EQUAL(output[35], 't');
  CU_ASSERT_EQUAL(output[36], ' ');
  CU_ASSERT_EQUAL(output[37], ' ');
  CU_ASSERT_EQUAL(output[38], '+');
  CU_ASSERT_EQUAL(output[39], '-');
  CU_ASSERT_EQUAL(output[40], 'x');
  CU_ASSERT_EQUAL(output[41], ' ');
  CU_ASSERT_EQUAL(output[42], 'o');
  CU_ASSERT_EQUAL(output[43], '.');
  CU_ASSERT_EQUAL(output[44], 'j');
  CU_ASSERT_EQUAL(output[45], 'p');
  CU_ASSERT_EQUAL(output[46], 'g');
  CU_ASSERT_EQUAL(output[47], 27);
  CU_ASSERT_EQUAL(output[48], 114);
  CU_ASSERT_EQUAL(output[49], 10);

  for (size_t i = 50; i < SERIALIZED_DIRECTORY_FILE_IN_BYTES; i++) {
    CU_ASSERT_EQUAL(output[i], 0);
  }
}

void test__deserialize_directory_entry_1() {
  unsigned char serialized_entry[] = INITIALIZE(DIRECTORY_ENTRY_SIZE_IN_BYTES, 'X');
  serialized_entry[0] = 'i';
  serialized_entry[1] = 'm';
  serialized_entry[2] = 'a';
  serialized_entry[3] = 'g';
  serialized_entry[4] = 'e';
  serialized_entry[5] = '.';
  serialized_entry[6] = 'p';
  serialized_entry[7] = 'n';
  serialized_entry[8] = 'g';
  serialized_entry[9] = '\000';
  serialized_entry[10] =  '\000';
  serialized_entry[11] =  '\000';
  serialized_entry[12] =  '\000';
  serialized_entry[13] =  '\000';
  serialized_entry[14] =  '\000';
  serialized_entry[15] =  '\000';
  serialized_entry[16] =  '\000';
  serialized_entry[17] =  '\000';
  serialized_entry[18] =  '\000';
  serialized_entry[19] =  '\000';
  serialized_entry[20] =  '\000';
  serialized_entry[21] =  8;
  serialized_entry[22] =  26;
  serialized_entry[23] =  7;

  const DirectoryEntry entry = deserialize_directory_entry(serialized_entry);
  CU_ASSERT_STRING_EQUAL(entry.filename, "image.png");
  CU_ASSERT_EQUAL(entry.first_fat_table_record, 465416);
}

void test__deserialize_directory_entry_2() {
  unsigned char serialized_entry[] = INITIALIZE(DIRECTORY_ENTRY_SIZE_IN_BYTES, 'X');

  serialized_entry[0] = 'n';
  serialized_entry[1] = 'a';
  serialized_entry[2] = 'g';
  serialized_entry[3] = 'h';
  serialized_entry[4] = 'i';
  serialized_entry[5] = 'b';
  serialized_entry[6] = 'z';
  serialized_entry[7] = 'a';
  serialized_entry[8] = 'd';
  serialized_entry[9] = 'e';
  serialized_entry[10] = 'h';
  serialized_entry[11] = '.';
  serialized_entry[12] = 'm';
  serialized_entry[13] = 'p';
  serialized_entry[14] = '4';
  serialized_entry[15] = '\000';
  serialized_entry[16] = '\000';
  serialized_entry[17] = '\000';
  serialized_entry[18] = '\000';
  serialized_entry[19] = '\000';
  serialized_entry[20] = '\000';
  serialized_entry[21] = 228;
  serialized_entry[22] = 56;
  serialized_entry[23] = 0;

  const DirectoryEntry entry = deserialize_directory_entry(serialized_entry);
  CU_ASSERT_STRING_EQUAL(entry.filename, "naghibzadeh.mp4");
  CU_ASSERT_EQUAL(entry.first_fat_table_record, 14564);
}

void test__deserialize_directory_entry_3() {
  unsigned char serialized_entry[] = INITIALIZE(DIRECTORY_ENTRY_SIZE_IN_BYTES, 'Z');

  serialized_entry[0] = 's';
  serialized_entry[1] = 'q';
  serialized_entry[2] = 'a';
  serialized_entry[3] = 'z';
  serialized_entry[4] = 'e';
  serialized_entry[5] = 'r';
  serialized_entry[6] = 'y';
  serialized_entry[7] = 'u';
  serialized_entry[8] = ' ';
  serialized_entry[9] = 'n';
  serialized_entry[10] = 'v';
  serialized_entry[11] = 'c';
  serialized_entry[12] = ' ';
  serialized_entry[13] = 'q';
  serialized_entry[14] = 'j';
  serialized_entry[15] = '4';
  serialized_entry[16] = '.';
  serialized_entry[17] = 'j';
  serialized_entry[18] = 'p';
  serialized_entry[19] = 'g';
  serialized_entry[20] = '\000';
  serialized_entry[21] = 230;
  serialized_entry[22] = 121;
  serialized_entry[23] = 6;

  const DirectoryEntry entry = deserialize_directory_entry(serialized_entry);
  CU_ASSERT_STRING_EQUAL(entry.filename, "sqazeryu nvc qj4.jpg");
  CU_ASSERT_EQUAL(entry.first_fat_table_record, 424422);
}

int main(void) {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Directory Library", 0, 0);
  CU_add_test(suite, "Serialize Directory Entry", test__serialize_directory_entry_1);
  CU_add_test(suite, "Serialize Directory Entry", test__serialize_directory_entry_2);
  CU_add_test(suite, "Serialize Directory Entry", test__serialize_directory_entry_3);
  CU_add_test(suite, "Serialize Directory File", test__serialize_directory_file_1);
  CU_add_test(suite, "Serialize Directory File", test__serialize_directory_file_2);
  CU_add_test(suite, "Deserialize Directory File", test__deserialize_directory_entry_1);
  CU_add_test(suite, "Deserialize Directory File", test__deserialize_directory_entry_2);
  CU_add_test(suite, "Deserialize Directory File", test__deserialize_directory_entry_3);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
