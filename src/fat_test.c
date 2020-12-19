#include "constants.h"
#include "fat.h"
#include "macros.h"
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test__serialize_fat_entry_executor(
  FatTableEntry entry,
  unsigned char expected_serialized_0,
  unsigned char expected_serialized_1,
  unsigned char expected_serialized_2
) {
  unsigned char serialized_entry[] = INITIALIZE(3, 0);
  serialize_fat_entry(entry, serialized_entry);

  CU_ASSERT_EQUAL(serialized_entry[0], expected_serialized_0);
  CU_ASSERT_EQUAL(serialized_entry[1], expected_serialized_1);
  CU_ASSERT_EQUAL(serialized_entry[2], expected_serialized_2);
}

void test__serialize_fat_entry(void) {
  test__serialize_fat_entry_executor(312528, 208, 196, 4);
  test__serialize_fat_entry_executor(710810, 154, 216, 10);
  test__serialize_fat_entry_executor(574170, 218, 194, 8);
  test__serialize_fat_entry_executor(204488, 200, 30, 3);
  test__serialize_fat_entry_executor(66667, 107, 4, 1);
  test__serialize_fat_entry_executor(467221, 21, 33, 7);
  test__serialize_fat_entry_executor(624856, 216, 136, 9);
  test__serialize_fat_entry_executor(1001213, 253, 70, 15);
  test__serialize_fat_entry_executor(273379, 227, 43, 4);
  test__serialize_fat_entry_executor(45504, 192, 177, 0);
  test__serialize_fat_entry_executor(434414, 238, 160, 6);
  test__serialize_fat_entry_executor(300923, 123, 151, 4);
  test__serialize_fat_entry_executor(297055, 95, 136, 4);
  test__serialize_fat_entry_executor(926783, 63, 36, 14);
  test__serialize_fat_entry_executor(609626, 90, 77, 9);
  test__serialize_fat_entry_executor(1047832, 24, 253, 15);
  test__serialize_fat_entry_executor(864189, 189, 47, 13);
  test__serialize_fat_entry_executor(798903, 183, 48, 12);
  test__serialize_fat_entry_executor(479341, 109, 80, 7);
  test__serialize_fat_entry_executor(200148, 212, 13, 3);
  test__serialize_fat_entry_executor(749183, 127, 110, 11);
  test__serialize_fat_entry_executor(278051, 35, 62, 4);
  test__serialize_fat_entry_executor(537337, 249, 50, 8);
  test__serialize_fat_entry_executor(910578, 242, 228, 13);
  test__serialize_fat_entry_executor(182642, 114, 201, 2);
  test__serialize_fat_entry_executor(604821, 149, 58, 9);
  test__serialize_fat_entry_executor(467450, 250, 33, 7);
  test__serialize_fat_entry_executor(409946, 90, 65, 6);
  test__serialize_fat_entry_executor(222032, 80, 99, 3);
  test__serialize_fat_entry_executor(435589, 133, 165, 6);
  test__serialize_fat_entry_executor(727645, 93, 26, 11);
  test__serialize_fat_entry_executor(977617, 209, 234, 14);
  test__serialize_fat_entry_executor(652358, 70, 244, 9);
  test__serialize_fat_entry_executor(864024, 24, 47, 13);
  test__serialize_fat_entry_executor(535244, 204, 42, 8);
  test__serialize_fat_entry_executor(235647, 127, 152, 3);
  test__serialize_fat_entry_executor(138338, 98, 28, 2);
  test__serialize_fat_entry_executor(426934, 182, 131, 6);
  test__serialize_fat_entry_executor(256262, 6, 233, 3);
  test__serialize_fat_entry_executor(870356, 212, 71, 13);
  test__serialize_fat_entry_executor(721063, 167, 0, 11);
  test__serialize_fat_entry_executor(400356, 228, 27, 6);
  test__serialize_fat_entry_executor(346556, 188, 73, 5);
  test__serialize_fat_entry_executor(593126, 230, 12, 9);
  test__serialize_fat_entry_executor(258942, 126, 243, 3);
  test__serialize_fat_entry_executor(617921, 193, 109, 9);
  test__serialize_fat_entry_executor(220090, 186, 91, 3);
  test__serialize_fat_entry_executor(534154, 138, 38, 8);
  test__serialize_fat_entry_executor(803845, 5, 68, 12);
  test__serialize_fat_entry_executor(206760, 168, 39, 3);
  test__serialize_fat_entry_executor(1032560, 112, 193, 15);
  test__serialize_fat_entry_executor(152496, 176, 83, 2);
  test__serialize_fat_entry_executor(1019358, 222, 141, 15);
  test__serialize_fat_entry_executor(597386, 138, 29, 9);
  test__serialize_fat_entry_executor(527328, 224, 11, 8);
  test__serialize_fat_entry_executor(247195, 155, 197, 3);
  test__serialize_fat_entry_executor(51320, 120, 200, 0);
  test__serialize_fat_entry_executor(669116, 188, 53, 10);
  test__serialize_fat_entry_executor(189368, 184, 227, 2);
  test__serialize_fat_entry_executor(732437, 21, 45, 11);
  test__serialize_fat_entry_executor(404849, 113, 45, 6);
  test__serialize_fat_entry_executor(302233, 153, 156, 4);
  test__serialize_fat_entry_executor(838706, 50, 204, 12);
  test__serialize_fat_entry_executor(325657, 25, 248, 4);
  test__serialize_fat_entry_executor(483111, 39, 95, 7);
  test__serialize_fat_entry_executor(401106, 210, 30, 6);
  test__serialize_fat_entry_executor(195147, 75, 250, 2);
  test__serialize_fat_entry_executor(122299, 187, 221, 1);
  test__serialize_fat_entry_executor(357095, 231, 114, 5);
}

void test__deserialize_fat_entry_executor(
  unsigned char serialized_0,
  unsigned char serialized_1,
  unsigned char serialized_2,
  FatTableEntry expected_entry
) {
  unsigned char serialized_entry[3] = { serialized_0, serialized_1, serialized_2 };
  const FatTableEntry deserialized_entry = deserialize_fat_entry(serialized_entry);

  CU_ASSERT_EQUAL(deserialized_entry, expected_entry);
}

void test__deserialize_fat_entry(void) {
  test__deserialize_fat_entry_executor(208, 196, 4, 312528);
  test__deserialize_fat_entry_executor(154, 216, 10, 710810);
  test__deserialize_fat_entry_executor(218, 194, 8, 574170);
  test__deserialize_fat_entry_executor(200, 30, 3, 204488);
  test__deserialize_fat_entry_executor(107, 4, 1, 66667);
  test__deserialize_fat_entry_executor(21, 33, 7, 467221);
  test__deserialize_fat_entry_executor(216, 136, 9, 624856);
  test__deserialize_fat_entry_executor(253, 70, 15, 1001213);
  test__deserialize_fat_entry_executor(227, 43, 4, 273379);
  test__deserialize_fat_entry_executor(192, 177, 0, 45504);
  test__deserialize_fat_entry_executor(238, 160, 6, 434414);
  test__deserialize_fat_entry_executor(123, 151, 4, 300923);
  test__deserialize_fat_entry_executor(95, 136, 4, 297055);
  test__deserialize_fat_entry_executor(63, 36, 14, 926783);
  test__deserialize_fat_entry_executor(90, 77, 9, 609626);
  test__deserialize_fat_entry_executor(24, 253, 15, 1047832);
  test__deserialize_fat_entry_executor(189, 47, 13, 864189);
  test__deserialize_fat_entry_executor(183, 48, 12, 798903);
  test__deserialize_fat_entry_executor(109, 80, 7, 479341);
  test__deserialize_fat_entry_executor(212, 13, 3, 200148);
  test__deserialize_fat_entry_executor(127, 110, 11, 749183);
  test__deserialize_fat_entry_executor(35, 62, 4, 278051);
  test__deserialize_fat_entry_executor(249, 50, 8, 537337);
  test__deserialize_fat_entry_executor(242, 228, 13, 910578);
  test__deserialize_fat_entry_executor(114, 201, 2, 182642);
  test__deserialize_fat_entry_executor(149, 58, 9, 604821);
  test__deserialize_fat_entry_executor(250, 33, 7, 467450);
  test__deserialize_fat_entry_executor(90, 65, 6, 409946);
  test__deserialize_fat_entry_executor(80, 99, 3, 222032);
  test__deserialize_fat_entry_executor(133, 165, 6, 435589);
  test__deserialize_fat_entry_executor(93, 26, 11, 727645);
  test__deserialize_fat_entry_executor(209, 234, 14, 977617);
  test__deserialize_fat_entry_executor(70, 244, 9, 652358);
  test__deserialize_fat_entry_executor(24, 47, 13, 864024);
  test__deserialize_fat_entry_executor(204, 42, 8, 535244);
  test__deserialize_fat_entry_executor(127, 152, 3, 235647);
  test__deserialize_fat_entry_executor(98, 28, 2, 138338);
  test__deserialize_fat_entry_executor(182, 131, 6, 426934);
  test__deserialize_fat_entry_executor(6, 233, 3, 256262);
  test__deserialize_fat_entry_executor(212, 71, 13, 870356);
  test__deserialize_fat_entry_executor(167, 0, 11, 721063);
  test__deserialize_fat_entry_executor(228, 27, 6, 400356);
  test__deserialize_fat_entry_executor(188, 73, 5, 346556);
  test__deserialize_fat_entry_executor(230, 12, 9, 593126);
  test__deserialize_fat_entry_executor(126, 243, 3, 258942);
  test__deserialize_fat_entry_executor(193, 109, 9, 617921);
  test__deserialize_fat_entry_executor(186, 91, 3, 220090);
  test__deserialize_fat_entry_executor(138, 38, 8, 534154);
  test__deserialize_fat_entry_executor(5, 68, 12, 803845);
  test__deserialize_fat_entry_executor(168, 39, 3, 206760);
  test__deserialize_fat_entry_executor(112, 193, 15, 1032560);
  test__deserialize_fat_entry_executor(176, 83, 2, 152496);
  test__deserialize_fat_entry_executor(222, 141, 15, 1019358);
  test__deserialize_fat_entry_executor(138, 29, 9, 597386);
  test__deserialize_fat_entry_executor(224, 11, 8, 527328);
  test__deserialize_fat_entry_executor(155, 197, 3, 247195);
  test__deserialize_fat_entry_executor(120, 200, 0, 51320);
  test__deserialize_fat_entry_executor(188, 53, 10, 669116);
  test__deserialize_fat_entry_executor(184, 227, 2, 189368);
  test__deserialize_fat_entry_executor(21, 45, 11, 732437);
  test__deserialize_fat_entry_executor(113, 45, 6, 404849);
  test__deserialize_fat_entry_executor(153, 156, 4, 302233);
  test__deserialize_fat_entry_executor(50, 204, 12, 838706);
  test__deserialize_fat_entry_executor(25, 248, 4, 325657);
  test__deserialize_fat_entry_executor(39, 95, 7, 483111);
  test__deserialize_fat_entry_executor(210, 30, 6, 401106);
  test__deserialize_fat_entry_executor(75, 250, 2, 195147);
  test__deserialize_fat_entry_executor(187, 221, 1, 122299);
  test__deserialize_fat_entry_executor(231, 114, 5, 357095);
}

void test__update_fat_entires() {
  FatTableEntry fat_table[] = INITIALIZE(16, 0);
  const FatTableEntry empty_entries[10] = { 0, 2, 4, 6, 7, 8, 9, 10, 13, 14 };
  update_fat_entires(fat_table, empty_entries);
  CU_ASSERT_EQUAL_FATAL(fat_table[0], 2);
  CU_ASSERT_EQUAL_FATAL(fat_table[2], 4);
  CU_ASSERT_EQUAL_FATAL(fat_table[4], 6);
  CU_ASSERT_EQUAL_FATAL(fat_table[6], 7);
  CU_ASSERT_EQUAL_FATAL(fat_table[7], 8);
  CU_ASSERT_EQUAL_FATAL(fat_table[8], 9);
  CU_ASSERT_EQUAL_FATAL(fat_table[9], 10);
  CU_ASSERT_EQUAL_FATAL(fat_table[10], 13);
  CU_ASSERT_EQUAL_FATAL(fat_table[13], 14);
  CU_ASSERT_EQUAL_FATAL(fat_table[14], FAT_END_OF_FILE_ENTRY);
}

void test__try_get_ten_empty_entries_should_work() {
  FatTableEntry fat_table[] = INITIALIZE(FAT_ENTRIES, FAT_EMPTY_ENTRY);
  fat_table[1] = 2;
  fat_table[2] = 7;
  fat_table[7] = 10;
  fat_table[9] = 11;
  fat_table[10] = 9;
  fat_table[11] = FAT_END_OF_FILE_ENTRY;
  FatTableEntry empty_entries[10] = { 0 };
  const bool found = try_get_ten_empty_entries(fat_table, empty_entries);
  const FatTableEntry expected_empty_entries[10] = { 0,3,4,5,6,8,12,13,14,15 };
  CU_ASSERT_TRUE(found);
  for (size_t i = 0; i < 0; i++)
  {
    CU_ASSERT_EQUAL(expected_empty_entries[i], empty_entries[i]);
  }
}

void test__try_get_ten_empty_entries_should_fail() {
  FatTableEntry fat_table[] = INITIALIZE(FAT_ENTRIES, FAT_EMPTY_ENTRY);
  for (size_t i = 0; i < FAT_ENTRIES - 1; i++)
  {
    fat_table[i] = i + 1;
  }
  fat_table[FAT_ENTRIES - 1] = FAT_END_OF_FILE_ENTRY;
  FatTableEntry empty_entries[10] = { 0 };
  const bool found = try_get_ten_empty_entries(fat_table, empty_entries);
  CU_ASSERT_FALSE(found);
}

int main(void) {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("FAT Library", 0, 0);
  CU_add_test(suite, "serialize_fat_entry", test__serialize_fat_entry);
  CU_add_test(suite, "deserialize_fat_entry", test__deserialize_fat_entry);
  CU_add_test(suite, "update_fat_entires", test__update_fat_entires);
  CU_add_test(suite, "try_get_ten_empty_entries should work", test__try_get_ten_empty_entries_should_work);
  CU_add_test(suite, "try_get_ten_empty_entries should fail", test__try_get_ten_empty_entries_should_fail);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
