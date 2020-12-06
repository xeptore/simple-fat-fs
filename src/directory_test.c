#include "constants.h"
#include "directory.h"
#include "macros.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdbool.h>

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
  CU_ASSERT_EQUAL(serialized_entry[9], ' ');
  CU_ASSERT_EQUAL(serialized_entry[10], ' ');
  CU_ASSERT_EQUAL(serialized_entry[11], ' ');
  CU_ASSERT_EQUAL(serialized_entry[12], ' ');
  CU_ASSERT_EQUAL(serialized_entry[13], ' ');
  CU_ASSERT_EQUAL(serialized_entry[14], ' ');
  CU_ASSERT_EQUAL(serialized_entry[15], ' ');
  CU_ASSERT_EQUAL(serialized_entry[16], ' ');
  CU_ASSERT_EQUAL(serialized_entry[17], ' ');
  CU_ASSERT_EQUAL(serialized_entry[18], ' ');
  CU_ASSERT_EQUAL(serialized_entry[19], ' ');
  CU_ASSERT_EQUAL(serialized_entry[20], 8);
  CU_ASSERT_EQUAL(serialized_entry[21], 26);
  CU_ASSERT_EQUAL(serialized_entry[22], 7);
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
  CU_ASSERT_EQUAL(serialized_entry[15], ' ');
  CU_ASSERT_EQUAL(serialized_entry[16], ' ');
  CU_ASSERT_EQUAL(serialized_entry[17], ' ');
  CU_ASSERT_EQUAL(serialized_entry[18], ' ');
  CU_ASSERT_EQUAL(serialized_entry[19], ' ');
  CU_ASSERT_EQUAL(serialized_entry[20], 94);
  CU_ASSERT_EQUAL(serialized_entry[21], 108);
  CU_ASSERT_EQUAL(serialized_entry[22], 10);
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
  CU_ASSERT_EQUAL(serialized_entry[20], 75);
  CU_ASSERT_EQUAL(serialized_entry[21], 8);
  CU_ASSERT_EQUAL(serialized_entry[22], 0);
}

int main(void) {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Directory Library", 0, 0);
  CU_add_test(suite, "Serialize Directory Entry", test__serialize_directory_entry_1);
  CU_add_test(suite, "Serialize Directory Entry", test__serialize_directory_entry_2);
  CU_add_test(suite, "Serialize Directory Entry", test__serialize_directory_entry_3);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
